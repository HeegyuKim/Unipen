
#ifndef _Unipen_Bitmap_h_
#define _Unipen_Bitmap_h_


#include "Entity.h"

#include <D2D1.h>
#include <atlbase.h>

namespace unipen {

class Bitmap : public Entity {
public:
	/**
	 *@brief 비트맵을 인자로 받아서 참조를 증가시키고 비트맵 관리자에 저장하는 생성자.
	 *@param bitmap 저장할 비트맵
	 */
	Bitmap(LPCWSTR key);

	///< 비트맵의 소멸자. 비트맵을 해제한다.
	virtual ~Bitmap();


	///< 비트맵의 크기를 반환한다.
	inline D2D1_SIZE_U GetSize() const { return m_bitmap->GetPixelSize(); }

	///< 비트맵의 형식을 반환한다.
	inline D2D1_PIXEL_FORMAT GetFormat() const { return m_bitmap->GetPixelFormat(); }

	///< 비트맵의 DPI를 반환한다.
	inline D2D1_POINT_2F GetDpi() const
	{
		D2D1_POINT_2F dpi;
		m_bitmap->GetDpi(&dpi.x, &dpi.y);
		return dpi;
	}
	
	///< ID2D1Bitmap 객체를 반환한다.
	inline ID2D1Bitmap* GetD2D1Bitmap() { return m_bitmap; }
	
	///< ID2D1Bitmap 객체를 반환한다.
	inline const ID2D1Bitmap* GetD2D1Bitmap() const { return m_bitmap; }

	///< ID2D1Bitmap 객체로 캐스팅한다.
	inline operator ID2D1Bitmap*() const { return m_bitmap; }


private:
	CComPtr<ID2D1Bitmap> m_bitmap; ///< ID2D1Bitmap 객체.
};

}

#endif