#include <string.h>
#include "stm32f4xx_hal.h"
#include "fifo.h"

void fifo_init(struct fifo *fifo, size_t item_size, unsigned size, void *memory)
{
	fifo->write = memory;
	fifo->read = NULL;
	volatile struct header * h = memory;
  
	// Create the linked list of empty cells
	for (unsigned i = 0; i < size; i++) {
		h->next = (i == size - 1) ? NULL : (volatile struct header *)((char *)(h + 1) + item_size);
		h = h->next;
	}
}

bool fifo_write(struct fifo *fifo, const void *item)
{
	volatile struct header *h;
  
	// Unlink the head cell from the write list
	do {
		h = (volatile struct header *)__LDREXW((volatile uint32_t *)&fifo->write);
		if (h == NULL) { // FIFO full?
			return false;
		}
		// while condition always true in non preemptable context with single core
	} while (!__STREXW((uint32_t)h->next, (volatile uint32_t *)&fifo->write));

	// Data memory barrier necessary to ensure correct order of memory accesses.
	__DMB();
  
	// The cell pointed to by h is now only accessible by us, we can perform the
	// actual writing.
	memcpy((void *)(h + 1), item, fifo->item_size);

	// Data memory barrier necessary to ensure correct order of memory accesses.
	__DMB();
  
	// Insert the item as the head of the read list, to make it available to
	// readers
	do {
		h->next = (volatile struct header *)__LDREXW((volatile uint32_t *)&fifo->read);
		// while condition always true in non preemptable context with single core
	} while (!__STREXW((uint32_t)h, (volatile uint32_t *)&fifo->read));

	return true;
}

bool fifo_read(struct fifo *fifo, void *item)
{
	if (fifo->read == NULL)
		return false; // nothing to read
  
	while (true) {
		// Walk through the list to the tail cell, which was inserted
		// first, and remember its address of the previous cell, in
		// order to unlink the tail from it.
		volatile struct header * volatile *prev = &fifo->read;
		volatile struct header *h = *prev;
		while (h->next != NULL) {
			prev = &h->next;
			h = h->next;
		}

	}
	return false; // Will not be reached
}
