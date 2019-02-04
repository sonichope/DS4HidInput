#include "DS4Input_dll.h"

DS4Manager manager;

EXPORT_API bool StartDS4()
{
	manager = DS4Manager();
	return true;
}

EXPORT_API bool GetController()
{
	manager.GetDevice();
	return true;
}

EXPORT_API bool ControllerChack(int id)
{
	return manager.IsDevice(id);
}

EXPORT_API bool ChangeColor(int id, const UCHAR r, const UCHAR g, const UCHAR b)
{
	manager.ChangeColor(id, r, g, b);
	return true;
}

EXPORT_API void ChangeVibration(int id, UCHAR right, UCHAR left)
{
	manager.ChangeVibration(id, right, left);
}

EXPORT_API void SendOutput(int id)
{
	manager.SendOutput(id);
	return;
}

EXPORT_API bool UpdateInputReport()
{
	manager.InputUpdate();
	return true;
}

EXPORT_API bool GetButton(int id, DS4KeyType keyType)
{
	return manager.GetButton(id, keyType);
}

EXPORT_API bool GetButtonDown(int id, DS4KeyType keyType)
{
	return manager.GetButtonDown(id,keyType);
}

EXPORT_API bool GetButtonUp(int id, DS4KeyType keyType)
{
	return manager.GetButtonUp(id, keyType);
}

EXPORT_API float GetAxis(int id, DS4AxisType keyType)
{
	return manager.GetAxis(id, keyType);
}

EXPORT_API bool EndDS4()
{
	manager.Destroy();
	return true;
}
