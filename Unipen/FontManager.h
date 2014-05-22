

#ifndef _Unipen_FontManager_h_
#define _Unipen_FontManager_h_


#include "Entity.h"

#include <memory>
#include <map>
#include <string>

#include <DWrite.h>
#include <atlbase.h>

namespace unipen {

/**
 * @class FontManager
 * @date 2014/05/21
 * @author 김희규
 * @brief 글꼴 객체들을 관리하는 관리자이다.
 */
class FontManager : public Entity {
public:
	///< FontManager 클래스의 싱글톤 객체를 반환한다.
	inline static std::shared_ptr<FontManager> GetInstance() _do(s_instance);

	typedef std::map<std::wstring, IDWriteTextFormat*> FontMap;

private:
	///< FontManager 클래스의 싱글톤 객체이다.
	static std::shared_ptr<FontManager> s_instance;

public:
	
	///< 기본 생성자. DWrite 팩토리를 생성한다.
	///< @param 
	FontManager();

	///< 기본 파괴자. DWrite 팩토리를 해제한다.
	virtual ~FontManager();


	/**
	 * @brief 글꼴 정보를 읽어들여 키값에 저장하는 메서드이다.
	 * @param key 저장할 키 값
	 * @param fontName 읽어들일 글꼴의 이름
	 * @param size 글꼴의 크기
	 * @param overwrite 이미 키가 존재할 경우. 존재하는 값을 덮어쓸 것인지를 지정하는 값이다.
	 * 기본값은 true이다.
	 * @return 키를 저장하는 데 성공했는지를 반환한다.
	 */
	bool Load(LPCWSTR key, LPCWSTR fontName, float size, bool overwrite = true);

	/**
	 * @brief 글꼴 정보를 키값에 저장한다.
	 * @param key 저장할 키 값
	 * @param format 저장할 글꼴 정보
	 * @param overwrite 이미 키가 존재할 경우. 존재하는 값을 덮어쓸 것인지를 지정하는 값이다.
	 * 기본값은 true이다.
	 * @return 키를 저장하는 데 성공했는지를 반환한다.
	 */
	bool Add(LPCWSTR key, IDWriteTextFormat* format, bool overwrite = true);

	/**
	 * @brief 지정된 키의 글꼴 정보를 지우고 성공 여부를 반환한다.
	 * @param key 지울 글꼴 정보의 키
	 * @return 지우는 데 성공했으면 true를, 실패했으면 false를 반환한다.
	 */
	bool Remove(LPCWSTR key);


	/**
	 * @brief 지정된 키를 가지고 있는지를 반환한다.
	 * @return 키를 가졌으면 true를 반환하고, 그렇지 않으면 false를 반환한다.
	 */
	bool Has(LPCWSTR key);

	/**
	 * @brief 글꼴 정보를 가져온다.
	 * @param key 가져올 글꼴 정보의 키 값.
	 * @param format 얻어온 글꼴 객체가 저장될 포인터.
	 * @return 키 값이 있다면 true를, 없다면 false이 반환된다.
	 */
	bool Get(LPCWSTR key, IDWriteTextFormat** format) const;


	///< 글꼴 정보를 가지고 있는 글꼴 지도를 반환한다.
	inline FontMap& GetFonts() _is(m_fonts);


	///< 글꼴 정보를 가지고 있는 글꼴 지도를 반환한다.
	inline const FontMap& GetFonts() const _is(m_fonts);


	///< DWrite 팩토리 객체를 반환한다.
	inline IDWriteFactory* GetFactory() const _is(m_factory);
	
private:
	FontMap m_fonts; ///< 글꼴 객체들을 가진 글꼴 지도 객체.

	CComPtr<IDWriteFactory> m_factory; ///< 글꼴 객체들을 생성할 DWriteFactory 객체.
};

/**
 *@brief 글꼴 객체를 글꼴 이름으로부터 읽어온다.
 *@param factory 글꼴 객체를 생성할 팩토리.
 *@param fotnName 읽어올 글꼴의 이름.
 *@param size 생성할 글꼴 객체의 글꼴 크기.
 *@param format 읽어온 글꼴 객체를 저장할 포인터.
 *@return 함수의 실행 결과를 반환한다. 성공하면 S_OK가 반환되며, 실패할 경우
 * 또다른 값들이 반환된다.
 */
HRESULT LoadFont(IDWriteFactory* factory, LPCWSTR fontName, float size, IDWriteTextFormat** format);

}


#endif