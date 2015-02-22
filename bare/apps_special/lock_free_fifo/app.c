#include <string.h>
#include <stdbool.h>
#include "led.h"
#include "clock_init.h"

struct link {
	struct link *next;
};

bool bad_linked_list(void);
bool good_linked_list(void);

int main(void)
{
	clock_init();

	bool error = false;
	if (!good_linked_list())
		error = true;
	if (!bad_linked_list())
		error = true;

	Led_TypeDef led = error ? LED_RED : LED_GREEN;

	BSP_LED_Init(led);

	for (;;) {
		BSP_LED_Toggle(led);
		HAL_Delay(1000); // ms
	}
}

bool good_linked_list(void)
{
	const size_t item_size = 4;
	const unsigned size = 3; // number of items in the list

	char memory[100];
	if (sizeof memory < (size * (sizeof(struct link) + item_size)))
		return false;

	// Writing the list
	
	struct link * l = (struct link *)memory;

	l->next = (struct link *)((char *)(l + 1) + item_size);
	char *p = (char *)(l + 1);
	*p++ = 'a';
	*p++ = 'b';
	*p++ = 'c';
	*p = 'd';
	l = l->next;

	l->next = (struct link *)((char *)(l + 1) + item_size);
	p = (char *)(l + 1);
	*p++ = 'e';
	*p++ = 'f';
	*p++ = 'g';
	*p = 'h';
	l = l->next;

	l->next = NULL;
	p = (char *)(l + 1);
	*p++ = 'i';
	*p++ = 'j';
	*p++ = 'k';
	*p = 'l';

	// Reading back the list
	l = (struct link *)memory;

	p = (char *)(l + 1);
	if (*p++ != 'a') return false;
	if (*p++ != 'b') return false;
	if (*p++ != 'c') return false;
	if (*p != 'd') return false;
	l = l->next;

	p = (char *)(l + 1);
	if (*p++ != 'e') return false;
	if (*p++ != 'f') return false;
	if (*p++ != 'g') return false;
	if (*p != 'h') return false;
	l = l->next;

	p = (char *)(l + 1);
	if (*p++ != 'i') return false;
	if (*p++ != 'j') return false;
	if (*p++ != 'k') return false;
	if (*p != 'l') return false;

	return true;
}

bool bad_linked_list(void)
{
	const size_t item_size = 3; // not a multiple of 4
	const unsigned size = 2; // number of items in the list

	char memory[100];
	if (sizeof memory < (size * (sizeof(struct link) + item_size)))
		return false;

	// Writing the list
	
	struct link * l = (struct link *)memory;

	l->next = (struct link *)((char *)(l + 1) + item_size);
	char *p = (char *)(l + 1);
	*p++ = 'a';
	*p++ = 'b';
	*p = 'c';
	l = l->next;

	l->next = (struct link *)((char *)(l + 1) + item_size);
	p = (char *)(l + 1);
	*p++ = 'd';
	*p++ = 'e';
	*p = 'f';
	l = l->next;

	l->next = NULL;
	p = (char *)(l + 1);
	*p++ = 'g';
	*p++ = 'h';
	*p = 'i';

	// Reading back the list
	l = (struct link *)memory;

	p = (char *)(l + 1);
	if (*p++ != 'a') return false;
	if (*p++ != 'b') return false;
	if (*p != 'c') return false;
	l = l->next;

	p = (char *)(l + 1);
	if (*p++ != 'd') return false;
	if (*p++ != 'e') return false;
	if (*p != 'f') return false;
	l = l->next;

	p = (char *)(l + 1);
	if (*p++ != 'g') return false;
	if (*p++ != 'h') return false;
	if (*p != 'i') return false;

	return true;
}
