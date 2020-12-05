#include "DSenseDevice.h"
#include "DSAxisType.h"

DSenseDevice::DSenseDevice(HidDevice device, int controllerId)
{
	this->device = device;
	this->controllerId = controllerId;
	outputDataLength = device.GetCapabilities().OutputReportByteLength;
	inputDataLength = device.GetCapabilities().InputReportByteLength;

	for (int i = 0; i < inputDataLength; i++)
	{
		inputData[i] = 0;
	}
	for (int i = 0; i < outputDataLength; i++)
	{
		outputData[i] = 0x00;
	}

	outputData[0] = 0x2;//レポートID
	outputData[1] = 0xff;//ff固定か
	outputData[2] = 0x17;//ライトバー プレイヤーランプ設定  : 0x08 : 充電 

	outputData[3] = 0x00;//Rモータ 0～FF
	outputData[4] = 0x00;//Lモータ 0～FF

	outputData[9] = 0x00;// マイクミュートライト 0 : 消灯 , 1 : 点灯, 2 : 点滅

	outputData[10] = 0x00;// LRフラグ

	outputData[11] = 0x0; // Rトリガー 1:抵抗 2:ロック
	outputData[12] = 0x00; //Rトリガー 上位bitがロックの位置値が大きくなると位置が下になる

	outputData[22] = 0x00; // Lトリガー
	outputData[23] = 0x00; // Lトリガー

	outputData[44] = 0x00; // プレイヤーライト1bitづつで点灯する、最大5bit

	outputData[45] = 0x00; // 赤
	outputData[46] = 0x00; // 緑
	outputData[47] = 0x00; // 青


	switch (controllerId)
	{
	case 0:
		ChangeLedColor(LED::Blue());
		ChangePlayerLight(4);
		break;
	case 1:
		ChangeLedColor(LED::Red());
		ChangePlayerLight(6);
		break;
	case 2:
		ChangeLedColor(LED::Green());
		ChangePlayerLight(14);
		break;
	case 3:
		ChangeLedColor(LED::Purple());
		ChangePlayerLight(0x1f);
		break;
	}

	SendOutputReport();
}

bool DSenseDevice::ChangeLedColor(const LED& led) noexcept
{
	outputData[45] = led.red;
	outputData[46] = led.green;
	outputData[47] = led.blue;
	return true;
}

bool DSenseDevice::GetInputReport()
{
	DWORD sizet = 0;
	OVERLAPPED overlapped;
	ZeroMemory(&overlapped, sizeof(OVERLAPPED));
	BOOL result = ReadFile(device.GetHandle(), inputData, inputDataLength, &sizet, &overlapped);
	device.isDevice = result;
	if (!result) return false;
	

#ifdef DEBUG
	for (int i = 0; i < 11; i++) {
		printf(" %d ", inputData[i]);
	}
	printf("\n");
#endif // DEBUG

	UCHAR data = inputData[8];
	status.square.ChangeStatus((data & 0x10) == 0x10 ? true : false);
	status.cross.ChangeStatus((data & 0x20) == 0x20 ? true : false);
	status.circle.ChangeStatus((data & 0x40) == 0x40 ? true : false);
	status.triangle.ChangeStatus((data & 0x80) == 0x80 ? true : false);
	data &= 0x0F;
	bool d[4] = { false, false, false, false };
	switch (data)
	{
	case 0:
		d[0] = true;
		break;
	case 1:
		d[0] = true;
		d[1] = true;
		break;
	case 2:
		d[1] = true;
		break;
	case 3:
		d[1] = true;
		d[2] = true;
		break;
	case 4:
		d[2] = true;
		break;
	case 5:
		d[2] = true;
		d[3] = true;
		break;
	case 6:
		d[3] = true;
		break;
	case 7:
		d[3] = true;
		d[0] = true;
		break;
	}
	status.up.ChangeStatus(d[0]);
	status.right.ChangeStatus(d[1]);
	status.down.ChangeStatus(d[2]);
	status.left.ChangeStatus(d[3]);

	data = inputData[9];
	status.l1.ChangeStatus((data & 0x01) == 0x01 ? true : false);
	status.r1.ChangeStatus((data & 0x02) == 0x02 ? true : false);
	status.share.ChangeStatus((data & 0x10) == 0x10 ? true : false);
	status.option.ChangeStatus((data & 0x20) == 0x20 ? true : false);
	status.l3.ChangeStatus((data & 0x40) == 0x40 ? true : false);
	status.r3.ChangeStatus((data & 0x80) == 0x80 ? true : false);
	data = inputData[10];
	status.home.ChangeStatus(data == 0x01 ? true : false);

	//左スティックの入力の保存
	data = inputData[1];
	status.leftStickX = (data - 127) / 127.0f;
	data = inputData[2];
	status.leftStickY = (data - 127) / 127.0f;

	//右スティックの入力の保存
	data = inputData[3];
	status.rightStickX = (data - 127) / 127.0f;
	data = inputData[4];
	status.rightStickY = (data - 127) / 127.0f;

	//L2とR2の入力の保存
	data = inputData[5];
	status.l2 = data / 255.0f;
	data = inputData[6];
	status.r2 = data / 255.0f;

	return true;
}

bool DSenseDevice::Destroy()
{
	ChangeLedColor(LED(0, 0, 0));
	ChangeVibration(0, 0);
	ChangeTriggerLock(0, 0, 0, 0);
	ChangePlayerLight(0);
	SendOutputReport();
	device.Destroy();
	controllerId = -1;
	return true;
}

void DSenseDevice::ChangeVibration(UCHAR right, UCHAR left)
{
	outputData[3] = right;
	outputData[4] = left;
}

void DSenseDevice::ChangeTriggerLock(UCHAR rMode, UCHAR right, UCHAR lMode, UCHAR left)
{
	outputData[11] = rMode;
	outputData[12] = right; //Rトリガー 上位bitがロックの位置値が大きくなると位置が下になる

	outputData[22] = lMode; // Lトリガー
	outputData[23] = left; // Lトリガー
}

void DSenseDevice::ChangePlayerLight(UCHAR val)
{
	outputData[44] = val & 0x1f;
}

bool DSenseDevice::SendOutputReport()
{
	BOOL result;
	DWORD sizet = 0;
	OVERLAPPED overlapped;
	ZeroMemory(&overlapped, sizeof(OVERLAPPED));
	result = WriteFile(device.GetHandle(), outputData, outputDataLength, &sizet, &overlapped);
	device.isDevice = result;
	return result;
}

bool DSenseDevice::GetButton(UCHAR keyType)
{
	const DSButtonStatus& statusData = status.data[keyType].status;
	return statusData == DSButtonStatus::Pushing || statusData == DSButtonStatus::Push;
}

bool DSenseDevice::GetButtonDown(UCHAR keyType)
{
	const DSButtonStatus& statusData = status.data[keyType].status;
	return statusData == DSButtonStatus::Push;
}

bool DSenseDevice::GetButtonUp(UCHAR keyType)
{
	const DSButtonStatus& statusData = status.data[keyType].status;
	return statusData == DSButtonStatus::UnPush;
}

float DSenseDevice::GetAxis(UCHAR axisType)
{
	if (axisType < 0 || axisType >= NUM) return 0.0f;
	return status.axisVals[axisType];
}

void DSenseDevice::Reset() noexcept
{
	ChangeVibration(0, 0);
	ChangeTriggerLock(0, 0, 0, 0);
	switch (controllerId)
	{
	case 0:
		ChangeLedColor(LED::Blue());
		ChangePlayerLight(4);
		break;
	case 1:
		ChangeLedColor(LED::Red());
		ChangePlayerLight(6);
		break;
	case 2:
		ChangeLedColor(LED::Green());
		ChangePlayerLight(14);
		break;
	case 3:
		ChangeLedColor(LED::Purple());
		ChangePlayerLight(0x1f);
		break;
	}
	SendOutputReport();
}
