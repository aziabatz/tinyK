#ifndef MINLIB_TIME_H
#define MINLIB_TIME_H

typedef unsigned int tick_t;
typedef unsigned int time_t;

struct tm
{
	unsigned char tm_sec;
	unsigned char tm_min;
	unsigned char tm_hour;
	unsigned char tm_mday;
	unsigned char tm_mon;
	unsigned char tm_year;
	unsigned char tm_wday;
	unsigned char tm_yday;
	unsigned char tm_isdst;//horario de verano
}

#define TICKS_PER_SECOND 18000//comprobar despues con reloj pic



#endif
