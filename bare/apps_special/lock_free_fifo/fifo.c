#include <string.h>
#include "stm32f4xx_hal.h"
#include "fifo.h"

static inline volatile struct link * load_exclusive(volatile struct link * const *location)
{
	return (volatile struct link *)__LDREXW((volatile uint32_t *)location);
}

static inline bool store_exclusive(volatile struct link *link, volatile struct link **location)
{
	return (bool)!__STREXW((uint32_t)link, (volatile uint32_t *)location);
}

void fifo_init(struct fifo *fifo, size_t item_size, unsigned size, void *memory)
{
	fifo->write = memory;
	fifo->read = NULL;
	volatile struct link * l = memory;
  
	// Create the linked list of empty cells
	for (unsigned i = 0; i < size; i++) {
		l->next = (i == size - 1) ? NULL : (volatile struct link *)((char *)(l + 1) + item_size);
		l = l->next;
	}
}

bool fifo_write(struct fifo *fifo, const void *item)
{
	volatile struct link *l;
  
	// Unlink the head cell from the write list
	do {
		l = load_exclusive(&fifo->write);
		if (l == NULL) { // FIFO full?
			return false;
		}
		// while condition always true in non preemptable context with single core.
	} while (store_exclusive(l->next, &fifo->write));

	// Data memory barrier necessary to ensure correct order of memory accesses.
	__DMB();
  
	// The cell pointed to by l is now only accessible by us, we can perform the
	// actual writing.
	memcpy((void *)(l + 1), item, fifo->item_size);

	// Data memory barrier necessary to ensure correct order of memory accesses.
	__DMB();
  
	// Insert the item as the head of the read list, to make it available to
	// readers.
	do {
		l->next = load_exclusive(&fifo->read);
		// while condition always true in non preemptable context with single core.
	} while (store_exclusive(l, &fifo->read));

	return true;
}

bool fifo_read(struct fifo *fifo, void *item)
{
	if (fifo->read == NULL)
		return false; // nothing to read
  
	while (true) {
		// Walk through the list to the tail cell, which was inserted
		// first, and remember the link pointing to it, in order to
		// unlink it.
		volatile struct link * volatile *prev = &fifo->read;
		volatile struct link *l = fifo->read;
		while (l->next != NULL) {
			prev = &l->next;
			l = l->next;
		}

		(void)prev;
		// to be continued...

	}
	return false; // Never reached!
}
