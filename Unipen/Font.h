
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
	 *@brief Ű ���� �۲� ������ ���� ��ü.
	 *@key ���� �۲� ��ü�� Ű
	 */
	Font(LPCWSTR key);

	///< �⺻ �Ҹ���
	virtual ~Font();

	///< �������� ��ü�� ��ȯ��.
	inline IDWriteTextFormat* GetTextFormat() const { return m_tf; }

private:
	CComPtr<IDWriteTextFormat> m_tf; // ���� ���� ��ü
};

}


#endif