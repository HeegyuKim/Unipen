
#ifndef _Unipen_Font_h_
#define _Unipen_Font_h_


#include "Entity.h"

#include <atlbase.h>
#include <dwrite.h>

namespace unipen 
{

class Font : public Entity
{
public:
	/**
	 *@brief 키 값의 글꼴 정보를 가진 객체.
	 *@key 얻어올 글꼴 객체의 키
	 */
	Font(LPCWSTR key);

	///< 기본 소멸자
	virtual ~Font();

	///< 문자형식 객체를 반환함.
	inline IDWriteTextFormat* GetTextFormat() const { return m_tf; }

private:
	CComPtr<IDWriteTextFormat> m_tf; // 문자 포멧 객체
};

}


#endif