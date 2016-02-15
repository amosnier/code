#ifndef APPLICATION_HEADERS_APP_MAIN_H_
#define APPLICATION_HEADERS_APP_MAIN_H_

#ifdef __cplusplus
extern "C" {
#endif

// exceptional: fault.h is not needed here but in main.c,
// that we want to change as little as possible
#include "fault.h"

int app_main(void);

#ifdef __cplusplus
}
#endif

#endif /* APPLICATION_HEADERS_APP_MAIN_H_ */