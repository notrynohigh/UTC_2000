#ifndef __CALENAR_H__
#define __CALENAR_H__

#include <stdint.h>

	
#define	YEAR_CHECK(yr)	(((yr % 400) == 0x0) || (((yr % 4) == 0) && ((yr % 100) != 0)))

#define	YEAR_DAYS(yr)	(YEAR_CHECK(yr) ? 366 : 365)
#define MAXCALCTICKS    ((uint16_t)(13105))
#define	BEGYEAR	        2000        // UTC started at 00:00:00 January 1, 2000
#define	DAY             86400UL    // 24 hours * 60 minutes * 60 seconds


typedef struct
{
  uint8_t seconds;  // 0-59
  uint8_t minutes;  // 0-59
  uint8_t hour;     // 0-23
  uint8_t day;      // 1-31
  uint8_t month;    // 1-12
  uint16_t year;    // 2000+
}calendar_utc_struct_t;


void calendar_set_time( uint32_t sec);


uint32_t calendar_get_utc(void); 
void calendar_get_time(calendar_utc_struct_t *tm);

void calendar_per_second(void);

void calendar_utc2struct(calendar_utc_struct_t *tm, uint32_t utc);
uint32_t calendar_struct2utc(calendar_utc_struct_t *tm);

void calendar_adjust_time( uint32_t sec_m );
uint32_t calendar_change_to_next_day(calendar_utc_struct_t c_tm, calendar_utc_struct_t *tm);


#endif 


