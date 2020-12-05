#ifdef DEBUG
#include "DSManager.h"

int main()
{
	DS4Manager ds4manager;
	ds4manager.GetDevice();
	int a = 0;
	scanf_s("%d", &a);
	while ( a)
	{
		ds4manager.InputUpdate();
		scanf_s("%d", &a);
	}
	
	ds4manager.Destroy();

	return 0;
}
#endif