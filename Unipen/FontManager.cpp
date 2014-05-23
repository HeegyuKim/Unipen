

#include "FontManager.h"

using namespace unipen;


HRESULT unipen::LoadFont(
	IDWriteFactory* factory, 
	LPCWSTR fontName, 
	float size, 
	IDWriteTextFormat** format
	)
{
	return factory->CreateTextFormat (
			fontName,
			nullptr,
			DWRITE_FONT_WEIGHT_NORMAL,
			DWRITE_FONT_STYLE_NORMAL,
			DWRITE_FONT_STRETCH_NORMAL,
			size,
			L"ko-kr",
			format );
}


///< �⺻ ������. DWrite ���丮�� �����Ѵ�.
FontManager::FontManager()
{
	DWriteCreateFactory(
		DWRITE_FACTORY_TYPE_SHARED,
		__uuidof(IDWriteFactory),
		(IUnknown**)&m_factory.p);
}

///< �⺻ �ı���. DWrite ���丮�� �����Ѵ�.
FontManager::~FontManager() {
	
}

/**
	* @brief �۲� ������ �о�鿩 Ű���� �����ϴ� �޼����̴�.
	* @param key ������ Ű ��
	* @param fontName �о���� �۲��� �̸�
	* @param size �۲��� ũ��
	*/
bool FontManager::Load(LPCWSTR key, LPCWSTR fontName, float size, bool overwrite) 
{
	auto it = m_fonts.find(key);

	// Ű�� �̹� �����ϴ��� Ȯ��
	if(it == m_fonts.end()) {
		if(overwrite)
			SafeRelease(it->second);
		else
			return false;
	}

	// �۲� ��ü�� �о�鿩�� �����Ѵ�.
	IDWriteTextFormat *format = nullptr;

	// �۲� �б⿡ �����ϸ�
	if(SUCCEEDED(LoadFont(m_factory, fontName, size, &format))) 
	{
		it->second = format;
		return true;
	}

	return false;
}

/**
	* @brief �۲� ������ Ű���� �����Ѵ�.
	* @param key ������ Ű ��
	* @param format ������ �۲� ����
	*/
bool  FontManager::Add(LPCWSTR key, IDWriteTextFormat* format, bool overwrite) 
{
	auto it = m_fonts.find(key);

	// Ű�� �̹� �����ϴ��� Ȯ��
	if(it == m_fonts.end() && overwrite) 
	{
		SafeRelease(it->second);
		it->second = format;
		return true;
	}
	else
		return false;
}

/**
	* @brief ������ Ű�� �۲� ������ ����� ���� ���θ� ��ȯ�Ѵ�.
	* @param key ���� �۲� ������ Ű
	* @return ����� �� ���������� true��, ���������� false�� ��ȯ�Ѵ�.
	*/
bool FontManager::Remove(LPCWSTR key) {
	auto it = m_fonts.find(key);

	if(it == m_fonts.end())
		return false;
	else {
		// null test
		if(it->second)
			it->second->Release();
		m_fonts.erase(it);
		return true;
	}
}

/**
	* @brief �۲� ������ �����´�.
	* @param key ������ �۲� ������ Ű ��.
	* @return Ű������ ã�� �۲� ��ü. ���ٸ� nulllptr�� ��ȯ�ȴ�.
	*/
bool FontManager::Get(LPCWSTR key, IDWriteTextFormat** format ) const 
{
	auto it = m_fonts.find(key);

	if(it == m_fonts.end()) {
		return false;
	} else { 
		if(it->second)
			it->second->AddRef();
		*format = it->second;
		return true;
	}
}


