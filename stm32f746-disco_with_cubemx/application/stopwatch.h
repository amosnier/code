#ifndef APPLICATION_STOPWATCH_H_
#define APPLICATION_STOPWATCH_H_

#include <stdbool.h>

void stopwatch_start(void);
bool stopwatch_step(void);
void stopwatch_stop(void);

inline const char * stopwatch_name(void)
{
	return "stopwatch";
}


#endif /* APPLICATION_STOPWATCH_H_ */
