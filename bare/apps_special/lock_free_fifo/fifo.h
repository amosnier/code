#include <stdbool.h>
#include <stddef.h>

struct link {
	volatile struct link * next;
};

struct fifo {
	volatile struct link * write;
	volatile struct link * read;
	size_t item_size;
};

#define FIFO_MEMORY_SIZE(item_size, size) ((size) * (sizeof(struct link) + (item_size)))

void fifo_init(struct fifo *fifo, size_t item_size, unsigned size, void *memory);
bool fifo_write(struct fifo *fifo, const void *item);
bool fifo_read(struct fifo *fifo, void *item);
