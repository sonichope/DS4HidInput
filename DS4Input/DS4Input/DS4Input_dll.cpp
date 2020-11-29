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

EXPORT_API bool ControllerCheck(const int id)
{
	return manager.IsDevice(id);
}

EXPORT_API bool ChangeColor(const int id, const UCHAR r, const UCHAR g, const UCHAR b)
{
	manager.ChangeColor(id, r, g, b);
	return true;
}

EXPORT_API void ChangeVibration(const int id, const UCHAR right, const UCHAR left)
{
	manager.ChangeVibration(id, right, left);
}

EXPORT_API void SendOutput(const int id)
{
	manager.SendOutput(id);
}

EXPORT_API bool UpdateInputReport()
{
	manager.InputUpdate();
	return true;
}

EXPORT_API bool GetButton(const int id, const DS4KeyType keyType)
{
	return manager.GetButton(id, keyType);
}

EXPORT_API bool GetButtonDown(const int id, const DS4KeyType keyType)
{
	return manager.GetButtonDown(id,keyType);
}

EXPORT_API bool GetButtonUp(const int id, const DS4KeyType keyType)
{
	return manager.GetButtonUp(id, keyType);
}

EXPORT_API float GetAxis(const int id, const DS4AxisType keyType)
{
	return manager.GetAxis(id, keyType);
}

EXPORT_API bool EndDS4()
{
	manager.Destroy();
	return true;
}
