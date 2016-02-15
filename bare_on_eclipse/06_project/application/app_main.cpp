#include "app_main.h"
#include <stdio.h>

struct Test {
	static bool constructed;
	bool exists;
	Test()
	: exists(true)
	{
		constructed = true;
	};

} test;

bool Test::constructed = false;

int app_main(void)
{
	printf("Test::constructed = %d, test.exists = %d\n", Test::constructed, test.exists);
	while (1)
		;
	return 0;
}
