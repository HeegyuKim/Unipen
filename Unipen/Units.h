
#ifndef _Unipen_Units_h_
#define _Unipen_Units_h_


#include "Entity.h"
#include <math.h>


namespace unipen {
namespace units {

/*!
	초를 밀리초로 바꾼다.
	@param seconds 바꿀 초
*/
float SecondsToMilliseconds(float seconds = 1) _is(seconds * 1000);

/*!
	분을 초로 바꾼다.
	@param minutes 바꿀 분
*/
float MinutesToSeconds(float minutes = 1) _is(minutes * 60);

/*!
	시간을 분으로 바꾼다.
	@param hours 바꿀 시간
*/
float HoursToMinutes(float hours = 1) _is(hours * 60);

/*!
	일을 시간으로 바꾼다.
	@param days 바꿀 일
*/
float DaysToHours(float days = 1) _is(days * 24);

/*!
	주를 일로 바꾼다.
	@param weeks 바꿀 주
*/
float WeeksToDays(float weeks = 1) _is(weeks * 7);

/*!
	년을 달로 바꾼다.
	@param years 바꿀 년
*/
float YearsToMonths(float years = 1) _is(years * 12);

/*!
	년을 일로 바꾼다.
	@param years 바꿀 일
*/
float YearsToDays(float years = 1) _is(years * 365);

/*!
	밀리초를 초로 바꾼다.
	@param years 바꿀 밀리초
*/
float MillisecondsToSeconds(float milliseconds) _is(milliseconds / 1000.0f);

/*!
	초을 분으로 바꾼다.
	@param years 바꿀 초
*/
float SecondsToMinutes(float seconds = 1) _is(seconds / 60.0f);

/*!
	분을 시간로 바꾼다.
	@param years 바꿀 분
*/
float MinutesToHours(float minutes = 1) _is(minutes / 60.0f);

/*!
	시간을 일로 바꾼다.
	@param years 바꿀 시간
*/
float HoursToDays(float hours = 1) _is(hours / 24.0f);

/*!
	일을 주로 바꾼다.
	@param years 바꿀 일
*/
float DaysToWeeks(float days = 1) _is(days / 7.0f);

/*!
	월을 년으로 바꾼다.
	@param years 바꿀 년
*/
float MonthsToYears(float months = 1) _is(months / 12.0f);

/*!
	일을 년으로 바꾼다.
	@param years 바꿀 일
*/
float DaysToYears(float days = 1) _is(days / 365.0f);


/**
 * 호도를 각도로 바꾼다.
 * @param radians 바꿀 호도
 */
float RadiansToDegrees(float radians) _is(radians * 57.295779f);

/**
 * 각도를 호도로 바꾼다.
 * @param radians 바꿀 각도
 */
float DegreesToRadians(float degrees) _is(degrees * 0.017453f);

/**
 * 호도를 0부터 2PI 사이의 값으로 제한한다.
 */
float RefineRadians(float radians) _is(fmodf(radians, 6.283184f));

/**
 * 각도를 0부터 360 사이의 값으로 제한한다.
 */
float RefineDegrees(float degrees) _is(fmodf(degrees, 360));


}
}



#endif