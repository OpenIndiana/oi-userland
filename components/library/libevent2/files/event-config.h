#if defined(_LP64) || defined(__amd64) || defined(__sparcv9)
#include <event2/event-config-64.h>
#else
#include <event2/event-config-32.h>
#endif
