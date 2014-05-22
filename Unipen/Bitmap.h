
#ifndef _Unipen_Bitmap_h_
#define _Unipen_Bitmap_h_


#include "Entity.h"

#include <D2D1.h>
#include <atlbase.h>

namespace unipen {

class Bitmap : public Entity {
public:
	/**
	 *@brief ��Ʈ���� ���ڷ� �޾Ƽ� ������ ������Ű�� ��Ʈ�� �����ڿ� �����ϴ� ������.
	 *@param bitmap ������ ��Ʈ��
	 */
	Bitmap(LPCWSTR key);

	///< ��Ʈ���� �Ҹ���. ��Ʈ���� �����Ѵ�.
	virtual ~Bitmap();


	///< ��Ʈ���� ũ�⸦ ��ȯ�Ѵ�.
	inline D2D1_SIZE_U GetSize() const { return m_bitmap->GetPixelSize(); }

	///< ��Ʈ���� ������ ��ȯ�Ѵ�.
	inline D2D1_PIXEL_FORMAT GetFormat() const { return m_bitmap->GetPixelFormat(); }

	///< ��Ʈ���� DPI�� ��ȯ�Ѵ�.
	inline D2D1_POINT_2F GetDpi() const
	{
		D2D1_POINT_2F dpi;
		m_bitmap->GetDpi(&dpi.x, &dpi.y);
		return dpi;
	}
	
	///< ID2D1Bitmap ��ü�� ��ȯ�Ѵ�.
	inline ID2D1Bitmap* GetD2D1Bitmap() { return m_bitmap; }
	
	///< ID2D1Bitmap ��ü�� ��ȯ�Ѵ�.
	inline const ID2D1Bitmap* GetD2D1Bitmap() const { return m_bitmap; }

	///< ID2D1Bitmap ��ü�� ĳ�����Ѵ�.
	inline operator ID2D1Bitmap*() const { return m_bitmap; }


private:
	CComPtr<ID2D1Bitmap> m_bitmap; ///< ID2D1Bitmap ��ü.
};

}

#endif