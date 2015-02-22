/* Lock-less FIFO implementation for the ARMv7-M architecture.
 * Terminology: in the code, a cell is what contains a data item in the FIFO. It
 * can either be:
 * - available for writing (empty) or
 * - filled with an item's data, ready to be read. After a filled cell is read,
 * it is returned to the list of cells available for writing.
 */

#include <stdbool.h>
#include <stddef.h>

/* Header = cell pointer. In memory, it will always be followed by the item's
 * data, of arbitrary size (the item data size is however constant accross a
 * given FIFO instance).
 * The type is volatile because the pointer will be updated by ARM's exclusive
 * access facilities, that require a volatile type.
 */
struct header {
	volatile struct header * next;
};

/* Actual FIFO. */
struct fifo {
	// Linked list of empty cells, available to be writen. A cell to be written
	// is first unlinked from the write list, then written, and then linked to the
	// read list below.
	volatile struct header * write;

	// Linked list of written items. The newest item is always inserted first.
	// Items are read in a FIFO fashion, which implies walking through to the end
	// of the list to read the next item. Read cells are then unlinked from this
	// list and linked back to the write list.
	volatile struct header * read;

	size_t item_size;
};

/* Memory size macro to be used by the invoker when allocating static/dynamic
 * memory for the FIFO.
 */
#define FIFO_MEMORY_SIZE(item_size, size) ((size) * (sizeof(struct header) + (item_size)))

void fifo_init(struct fifo *fifo, size_t item_size, unsigned size, void *memory);
bool fifo_write(struct fifo *fifo, const void *item);
bool fifo_read(struct fifo *fifo, void *item);
