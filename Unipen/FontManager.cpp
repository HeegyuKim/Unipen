

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


///< 기본 생성자. DWrite 팩토리를 생성한다.
FontManager::FontManager()
{
	DWriteCreateFactory(
		DWRITE_FACTORY_TYPE_SHARED,
		__uuidof(IDWriteFactory),
		(IUnknown**)&m_factory.p);
}

///< 기본 파괴자. DWrite 팩토리를 해제한다.
FontManager::~FontManager() {
	
}

/**
	* @brief 글꼴 정보를 읽어들여 키값에 저장하는 메서드이다.
	* @param key 저장할 키 값
	* @param fontName 읽어들일 글꼴의 이름
	* @param size 글꼴의 크기
	*/
bool FontManager::Load(LPCWSTR key, LPCWSTR fontName, float size, bool overwrite) 
{
	auto it = m_fonts.find(key);

	// 키가 이미 존재하는지 확인
	if(it == m_fonts.end()) {
		if(overwrite)
			SafeRelease(it->second);
		else
			return false;
	}

	// 글꼴 객체를 읽어들여서 적재한다.
	IDWriteTextFormat *format = nullptr;

	// 글꼴 읽기에 성공하면
	if(SUCCEEDED(LoadFont(m_factory, fontName, size, &format))) 
	{
		it->second = format;
		return true;
	}

	return false;
}

/**
	* @brief 글꼴 정보를 키값에 저장한다.
	* @param key 저장할 키 값
	* @param format 저장할 글꼴 정보
	*/
bool  FontManager::Add(LPCWSTR key, IDWriteTextFormat* format, bool overwrite) 
{
	auto it = m_fonts.find(key);

	// 키가 이미 존재하는지 확인
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
	* @brief 지정된 키의 글꼴 정보를 지우고 성공 여부를 반환한다.
	* @param key 지울 글꼴 정보의 키
	* @return 지우는 데 성공했으면 true를, 실패했으면 false를 반환한다.
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
	* @brief 글꼴 정보를 가져온다.
	* @param key 가져올 글꼴 정보의 키 값.
	* @return 키값으로 찾은 글꼴 객체. 없다면 nulllptr이 반환된다.
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


