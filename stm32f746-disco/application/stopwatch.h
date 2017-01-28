#ifndef APPLICATION_STOPWATCH_H_
#define APPLICATION_STOPWATCH_H_

#include <stdbool.h>

void stopwatch_reset(void);
bool stopwatch_step(void);

inline const char * stopwatch_name(void)
{
	return "stopwatch";
}


#endif /* APPLICATION_STOPWATCH_H_ */
