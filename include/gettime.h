#ifndef GETTIME_H
#define GETTIME_H
#include <time.h>

#ifndef MAX_TIME_LENGTH
#define MAX_TIME_LENGTH 20
#endif // MAX_TIME_LENGTH

void get_current_datetime(char *buffer, size_t size);

#endif // GETTIME_H