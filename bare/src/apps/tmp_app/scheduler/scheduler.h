#ifndef SCHEDULER_H
#define SCHEDULER_H

#include "stdint.h"

void schedule(void (f)(void), uint32_t period);

#endif /* SCHEDULER_H */
