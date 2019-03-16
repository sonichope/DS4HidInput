#include "DS4Device.h"

DS4Device::DS4Device()
{
	controllerNum = -1;
}

DS4Device DS4Device::Create(HidDevice device, int controllerId)
{
	this->device = device;
	this->controllerNum = controllerId;
	outputDataLength = device.GetCapabilities().OutputReportByteLength;
	inputDataLength = device.GetCapabilities().InputReportByteLength;

	for (int i = 0; i < inputDataLength; i++)
	{
		inputData[i] = 0;
	}
	for (int i = 0; i < outputDataLength; i++)
	{
		outputData[i] = 1;
	}

	outputData[0] = 0x05;//レポートID
	outputData[1] = 0x03;//モード(0:オフ,1:揺れのみ,2:光だけ,3:両方)
	outputData[2] = 0x00;//LEDモード(最下位が0:ずっと発行,1:一瞬)
	outputData[3] = 0x00;//改行
	outputData[4] = 0x00;//Rモータ
	outputData[5] = 0x00;//Lモータ

	switch (controllerId)
	{
	case 0:
		ChangeLedColor(LED::Blue());
		break;
	case 1:
		ChangeLedColor(LED::Red());
		break;
	case 2:
		ChangeLedColor(LED::Green());
		break;
	case 3:
		ChangeLedColor(LED::Purple());
		break;
	}

	SendOutputReport();

	return *this;
}

bool DS4Device::SendOutputReport()
{
	BOOL result;
	DWORD sizet = 0;
	OVERLAPPED overlapped;
	ZeroMemory(&overlapped, sizeof(OVERLAPPED));
	result = WriteFile(device.GetHandle(), outputData, outputDataLength, &sizet, &overlapped);
	return result;
}

bool DS4Device::ChangeLedColor(LED led)
{
	outputData[6] = led.red;
	outputData[7] = led.green;
	outputData[8] = led.blue;	
	return true;
}

void DS4Device::ChangeVibration(UCHAR right, UCHAR left)
{
	outputData[4] = right;
	outputData[5] = left;
}

bool DS4Device::GetInputReport()
{
	DWORD sizet = 0;
	OVERLAPPED overlapped;
	ZeroMemory(&overlapped, sizeof(OVERLAPPED));
	BOOL result = ReadFile(device.GetHandle(), inputData, inputDataLength, &sizet, &overlapped);

	//ボタンの入力の保存
	UCHAR data = inputData[5];
	status.square.ChangeStatus((data & 0x10) == 0x10 ? true : false);
	status.cross.ChangeStatus((data & 0x20) == 0x20 ? true : false);
	status.circle.ChangeStatus((data & 0x40) == 0x40 ? true : false);
	status.triangle.ChangeStatus((data & 0x80) == 0x80 ? true : false);
	data &= 0x0F;
	bool d[4] = {false, false, false, false};
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
	
	data = inputData[6];
	status.l1.ChangeStatus((data & 0x01) == 0x01 ? true : false);
	status.r1.ChangeStatus((data & 0x02) == 0x02 ? true : false);
	status.share.ChangeStatus((data & 0x10) == 0x10 ? true : false);
	status.option.ChangeStatus((data & 0x20) == 0x20 ? true : false);
	status.l3.ChangeStatus((data & 0x40) == 0x40 ? true : false);
	status.r3.ChangeStatus((data & 0x80) == 0x80 ? true : false);

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
	data = inputData[8];
	status.l2 = data / 255.0f;
	data = inputData[9];
	status.r2 = data / 255.0f;

	return true;
}

bool DS4Device::Destroy()
{
	ChangeLedColor(LED(0, 0, 0));
	SendOutputReport();
	device.Destroy();
	return true;
}

bool DS4Device::IsDS4Device()
{
	return controllerNum >= 0;
}

bool DS4Device::GetButton(DS4KeyType keyType)
{
	bool isDown = false;
	DS4ButtonStatus statusData;
	switch (keyType)
	{
	case DS4KeyType::Square:
		statusData = status.square.status;
		if (statusData == DS4ButtonStatus::Pushing || statusData == DS4ButtonStatus::Push) { isDown = true; }
		break;
	case DS4KeyType::Cross:
		statusData = status.cross.status;
		if (statusData == DS4ButtonStatus::Pushing || statusData == DS4ButtonStatus::Push) { isDown = true; }
		break;
	case DS4KeyType::Circle:
		statusData = status.circle.status;
		if (statusData == DS4ButtonStatus::Pushing || statusData == DS4ButtonStatus::Push) { isDown = true; }
		break;
	case DS4KeyType::Triangle:
		statusData = status.triangle.status;
		if (statusData == DS4ButtonStatus::Pushing || statusData == DS4ButtonStatus::Push) { isDown = true; }
		break;
	case DS4KeyType::Up:
		statusData = status.up.status;
		if (statusData == DS4ButtonStatus::Pushing || statusData == DS4ButtonStatus::Push) { isDown = true; }
		break;
	case DS4KeyType::Right:
		statusData = status.right.status;
		if (statusData == DS4ButtonStatus::Pushing || statusData == DS4ButtonStatus::Push) { isDown = true; }
		break;
	case DS4KeyType::Down:
		statusData = status.down.status;
		if (statusData == DS4ButtonStatus::Pushing || statusData == DS4ButtonStatus::Push) { isDown = true; }
		break;
	case DS4KeyType::Left:
		statusData = status.left.status;
		if (statusData == DS4ButtonStatus::Pushing || statusData == DS4ButtonStatus::Push) { isDown = true; }
		break;
	case DS4KeyType::L1:
		statusData = status.l1.status;
		if (statusData == DS4ButtonStatus::Pushing || statusData == DS4ButtonStatus::Push) { isDown = true; }
		break;
	case DS4KeyType::R1:
		statusData = status.r1.status;
		if (statusData == DS4ButtonStatus::Pushing || statusData == DS4ButtonStatus::Push) { isDown = true; }
		break;
	case DS4KeyType::SHARE:
		statusData = status.share.status;
		if (statusData == DS4ButtonStatus::Pushing || statusData == DS4ButtonStatus::Push) { isDown = true; }
		break;
	case DS4KeyType::OPTION:
		statusData = status.option.status;
		if (statusData == DS4ButtonStatus::Pushing || statusData == DS4ButtonStatus::Push) { isDown = true; }
		break;
	case DS4KeyType::L3:
		statusData = status.l3.status;
		if (statusData == DS4ButtonStatus::Pushing || statusData == DS4ButtonStatus::Push) { isDown = true; }
		break;
	case DS4KeyType::R3:
		statusData = status.r3.status;
		if (statusData == DS4ButtonStatus::Pushing || statusData == DS4ButtonStatus::Push) { isDown = true; }
		break;
	}
	return isDown;
}

bool DS4Device::GetButtonDown(DS4KeyType keyType)
{
	bool isDown = false;
	DS4ButtonStatus statusData;
	switch (keyType)
	{
	case DS4KeyType::Square:
		statusData = status.square.status;
		if (statusData == DS4ButtonStatus::Push) { isDown = true; }
		break;
	case DS4KeyType::Cross:
		statusData = status.cross.status;
		if (statusData == DS4ButtonStatus::Push) { isDown = true; }
		break;
	case DS4KeyType::Circle:
		statusData = status.circle.status;
		if (statusData == DS4ButtonStatus::Push) { isDown = true; }
		break;
	case DS4KeyType::Triangle:
		statusData = status.triangle.status;
		if (statusData == DS4ButtonStatus::Push) { isDown = true; }
		break;
	case DS4KeyType::Up:
		statusData = status.up.status;
		if (statusData == DS4ButtonStatus::Push) { isDown = true; }
		break;
	case DS4KeyType::Right:
		statusData = status.right.status;
		if (statusData == DS4ButtonStatus::Push) { isDown = true; }
		break;
	case DS4KeyType::Down:
		statusData = status.down.status;
		if (statusData == DS4ButtonStatus::Push) { isDown = true; }
		break;
	case DS4KeyType::Left:
		statusData = status.left.status;
		if (statusData == DS4ButtonStatus::Push) { isDown = true; }
		break;
	case DS4KeyType::L1:
		statusData = status.l1.status;
		if (statusData == DS4ButtonStatus::Push) { isDown = true; }
		break;
	case DS4KeyType::R1:
		statusData = status.r1.status;
		if (statusData == DS4ButtonStatus::Push) { isDown = true; }
		break;
	case DS4KeyType::SHARE:
		statusData = status.share.status;
		if (statusData == DS4ButtonStatus::Push) { isDown = true; }
		break;
	case DS4KeyType::OPTION:
		statusData = status.option.status;
		if (statusData == DS4ButtonStatus::Push) { isDown = true; }
		break;
	case DS4KeyType::L3:
		statusData = status.l3.status;
		if (statusData == DS4ButtonStatus::Push) { isDown = true; }
		break;
	case DS4KeyType::R3:
		statusData = status.r3.status;
		if (statusData == DS4ButtonStatus::Push) { isDown = true; }
		break;
	}
	return isDown;
}

bool DS4Device::GetButtonUp(DS4KeyType keyType)
{
	bool isUp = false;
	DS4ButtonStatus statusData;
	switch (keyType)
	{
	case DS4KeyType::Square:
		statusData = status.square.status;
		if (statusData == DS4ButtonStatus::UnPush) { isUp = true; }
		break;
	case DS4KeyType::Cross:
		statusData = status.cross.status;
		if (statusData == DS4ButtonStatus::UnPush) { isUp = true; }
		break;
	case DS4KeyType::Circle:
		statusData = status.circle.status;
		if (statusData == DS4ButtonStatus::UnPush) { isUp = true; }
		break;
	case DS4KeyType::Triangle:
		statusData = status.triangle.status;
		if (statusData == DS4ButtonStatus::UnPush) { isUp = true; }
		break;
	case DS4KeyType::Up:
		statusData = status.up.status;
		if (statusData == DS4ButtonStatus::UnPush) { isUp = true; }
		break;
	case DS4KeyType::Right:
		statusData = status.right.status;
		if (statusData == DS4ButtonStatus::UnPush) { isUp = true; }
		break;
	case DS4KeyType::Down:
		statusData = status.down.status;
		if (statusData == DS4ButtonStatus::UnPush) { isUp = true; }
		break;
	case DS4KeyType::Left:
		statusData = status.left.status;
		if (statusData == DS4ButtonStatus::UnPush) { isUp = true; }
		break;
	case DS4KeyType::L1:
		statusData = status.l1.status;
		if (statusData == DS4ButtonStatus::UnPush) { isUp = true; }
		break;
	case DS4KeyType::R1:
		statusData = status.r1.status;
		if (statusData == DS4ButtonStatus::UnPush) { isUp = true; }
		break;
	case DS4KeyType::SHARE:
		statusData = status.share.status;
		if (statusData == DS4ButtonStatus::UnPush) { isUp = true; }
		break;
	case DS4KeyType::OPTION:
		statusData = status.option.status;
		if (statusData == DS4ButtonStatus::UnPush) { isUp = true; }
		break;
	case DS4KeyType::L3:
		statusData = status.l3.status;
		if (statusData == DS4ButtonStatus::UnPush) { isUp = true; }
		break;
	case DS4KeyType::R3:
		statusData = status.r3.status;
		if (statusData == DS4ButtonStatus::UnPush) { isUp = true; }
		break;
	}
	return isUp;
}

float DS4Device::GetAxis(DS4AxisType axisType)
{
	switch (axisType)
	{
	case RightStickX:
		return status.rightStickX;
	case RightStickY:
		return status.rightStickY;
	case LeftStickX:
		return status.leftStickX;
	case LeftStickY:
		return status.leftStickY;
	case L2:
		return status.l2;
	case R2:
		return status.r2;
	}
	return 0.0f;
}
