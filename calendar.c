#include "calendar.h"
#include "stdio.h"

static uint32_t sg_time_second = 0;


static uint8_t calendar_month_days( uint8_t lpyr, uint8_t month)
{
    uint8_t days = 31, i = 0;
    uint8_t table[7] = {1,3,5,7,8,10,12};
    if(month < 1 || month > 12)
    {
        return 0;
    }
    if (month == 2)
    {
        days = (28 + lpyr);
    }
    else
    {
        for(i = 0;i < 7;i++)
        {
            if(month == table[i])
            {
                days = 31;
                break;
            }
        }
        if(i >= 7)
        {
            days = 30;
        }
    }
    return days ;
}


void calendar_set_time( uint32_t sec )
{
  sg_time_second = sec;
}


uint32_t calendar_get_utc()
{
  return sg_time_second;
}

void calendar_per_second()
{
    sg_time_second++;
}


void calendar_utc2struct( calendar_utc_struct_t *tm, uint32_t utc )
{
    uint32_t sec_in_day = utc % DAY;
    tm->seconds = sec_in_day % 60;
    tm->minutes = (sec_in_day % 3600) / 60;
    tm->hour = sec_in_day / 3600;

    uint32_t days = utc / DAY;
    tm->year = BEGYEAR;
    while ( days >= YEAR_DAYS( tm->year ) )
    {
      days -= YEAR_DAYS( tm->year );
      tm->year++;
    }
    tm->month = 1;
    while ( days >= calendar_month_days( YEAR_CHECK( tm->year ), tm->month ))
    {
      days -= calendar_month_days( YEAR_CHECK( tm->year ), tm->month );
      tm->month++;
    }
    tm->day = days + 1;
}


uint32_t calendar_struct2utc( calendar_utc_struct_t *tm )
{
    uint32_t seconds;

    seconds = (((tm->hour * 60) + tm->minutes) * 60) + tm->seconds;

    uint32_t days = tm->day - 1;
    int8_t month = tm->month;
    month--;
    while ( month > 0 )
    {
        days += calendar_month_days( YEAR_CHECK( tm->year ), month );
        month--;
    }

    uint32_t year = tm->year - 1;
    while ( year >= BEGYEAR )
    {
        days += YEAR_DAYS( year );
        year--;
    }
    
    seconds += (days * DAY);

    return seconds;
}


uint32_t calendar_change_to_next_day(calendar_utc_struct_t c_tm, calendar_utc_struct_t *tm)
{
    uint32_t second = calendar_struct2utc(&c_tm);
    uint32_t days = second / (24 * 60 * 60);
    second = (days + 1) * (24 * 60 * 60);
    if(tm != ((void *)0))
    {
        calendar_utc2struct(tm, second);
    }
    return second;
}

void calendar_get_time(calendar_utc_struct_t *tm)
{
    calendar_utc2struct(tm, sg_time_second);
}
