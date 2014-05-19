
#ifndef _Unipen_Units_h_
#define _Unipen_Units_h_


#include "Entity.h"
#include <math.h>


namespace unipen {
namespace units {

/*!
	�ʸ� �и��ʷ� �ٲ۴�.
	@param seconds �ٲ� ��
*/
float SecondsToMilliseconds(float seconds = 1) _is(seconds * 1000);

/*!
	���� �ʷ� �ٲ۴�.
	@param minutes �ٲ� ��
*/
float MinutesToSeconds(float minutes = 1) _is(minutes * 60);

/*!
	�ð��� ������ �ٲ۴�.
	@param hours �ٲ� �ð�
*/
float HoursToMinutes(float hours = 1) _is(hours * 60);

/*!
	���� �ð����� �ٲ۴�.
	@param days �ٲ� ��
*/
float DaysToHours(float days = 1) _is(days * 24);

/*!
	�ָ� �Ϸ� �ٲ۴�.
	@param weeks �ٲ� ��
*/
float WeeksToDays(float weeks = 1) _is(weeks * 7);

/*!
	���� �޷� �ٲ۴�.
	@param years �ٲ� ��
*/
float YearsToMonths(float years = 1) _is(years * 12);

/*!
	���� �Ϸ� �ٲ۴�.
	@param years �ٲ� ��
*/
float YearsToDays(float years = 1) _is(years * 365);

/*!
	�и��ʸ� �ʷ� �ٲ۴�.
	@param years �ٲ� �и���
*/
float MillisecondsToSeconds(float milliseconds) _is(milliseconds / 1000.0f);

/*!
	���� ������ �ٲ۴�.
	@param years �ٲ� ��
*/
float SecondsToMinutes(float seconds = 1) _is(seconds / 60.0f);

/*!
	���� �ð��� �ٲ۴�.
	@param years �ٲ� ��
*/
float MinutesToHours(float minutes = 1) _is(minutes / 60.0f);

/*!
	�ð��� �Ϸ� �ٲ۴�.
	@param years �ٲ� �ð�
*/
float HoursToDays(float hours = 1) _is(hours / 24.0f);

/*!
	���� �ַ� �ٲ۴�.
	@param years �ٲ� ��
*/
float DaysToWeeks(float days = 1) _is(days / 7.0f);

/*!
	���� ������ �ٲ۴�.
	@param years �ٲ� ��
*/
float MonthsToYears(float months = 1) _is(months / 12.0f);

/*!
	���� ������ �ٲ۴�.
	@param years �ٲ� ��
*/
float DaysToYears(float days = 1) _is(days / 365.0f);


/**
 * ȣ���� ������ �ٲ۴�.
 * @param radians �ٲ� ȣ��
 */
float RadiansToDegrees(float radians) _is(radians * 57.295779f);

/**
 * ������ ȣ���� �ٲ۴�.
 * @param radians �ٲ� ����
 */
float DegreesToRadians(float degrees) _is(degrees * 0.017453f);

/**
 * ȣ���� 0���� 2PI ������ ������ �����Ѵ�.
 */
float RefineRadians(float radians) _is(fmodf(radians, 6.283184f));

/**
 * ������ 0���� 360 ������ ������ �����Ѵ�.
 */
float RefineDegrees(float degrees) _is(fmodf(degrees, 360));


}
}



#endif