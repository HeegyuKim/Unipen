

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
 * @author �����
 * @brief �۲� ��ü���� �����ϴ� �������̴�.
 */
class FontManager : public Entity {
public:
	///< FontManager Ŭ������ �̱��� ��ü�� ��ȯ�Ѵ�.
	inline static std::shared_ptr<FontManager> GetInstance() _do(s_instance);

	typedef std::map<std::wstring, IDWriteTextFormat*> FontMap;

private:
	///< FontManager Ŭ������ �̱��� ��ü�̴�.
	static std::shared_ptr<FontManager> s_instance;

public:
	
	///< �⺻ ������. DWrite ���丮�� �����Ѵ�.
	///< @param 
	FontManager();

	///< �⺻ �ı���. DWrite ���丮�� �����Ѵ�.
	virtual ~FontManager();


	/**
	 * @brief �۲� ������ �о�鿩 Ű���� �����ϴ� �޼����̴�.
	 * @param key ������ Ű ��
	 * @param fontName �о���� �۲��� �̸�
	 * @param size �۲��� ũ��
	 * @param overwrite �̹� Ű�� ������ ���. �����ϴ� ���� ��� �������� �����ϴ� ���̴�.
	 * �⺻���� true�̴�.
	 * @return Ű�� �����ϴ� �� �����ߴ����� ��ȯ�Ѵ�.
	 */
	bool Load(LPCWSTR key, LPCWSTR fontName, float size, bool overwrite = true);

	/**
	 * @brief �۲� ������ Ű���� �����Ѵ�.
	 * @param key ������ Ű ��
	 * @param format ������ �۲� ����
	 * @param overwrite �̹� Ű�� ������ ���. �����ϴ� ���� ��� �������� �����ϴ� ���̴�.
	 * �⺻���� true�̴�.
	 * @return Ű�� �����ϴ� �� �����ߴ����� ��ȯ�Ѵ�.
	 */
	bool Add(LPCWSTR key, IDWriteTextFormat* format, bool overwrite = true);

	/**
	 * @brief ������ Ű�� �۲� ������ ����� ���� ���θ� ��ȯ�Ѵ�.
	 * @param key ���� �۲� ������ Ű
	 * @return ����� �� ���������� true��, ���������� false�� ��ȯ�Ѵ�.
	 */
	bool Remove(LPCWSTR key);


	/**
	 * @brief ������ Ű�� ������ �ִ����� ��ȯ�Ѵ�.
	 * @return Ű�� �������� true�� ��ȯ�ϰ�, �׷��� ������ false�� ��ȯ�Ѵ�.
	 */
	bool Has(LPCWSTR key);

	/**
	 * @brief �۲� ������ �����´�.
	 * @param key ������ �۲� ������ Ű ��.
	 * @param format ���� �۲� ��ü�� ����� ������.
	 * @return Ű ���� �ִٸ� true��, ���ٸ� false�� ��ȯ�ȴ�.
	 */
	bool Get(LPCWSTR key, IDWriteTextFormat** format) const;


	///< �۲� ������ ������ �ִ� �۲� ������ ��ȯ�Ѵ�.
	inline FontMap& GetFonts() _is(m_fonts);


	///< �۲� ������ ������ �ִ� �۲� ������ ��ȯ�Ѵ�.
	inline const FontMap& GetFonts() const _is(m_fonts);


	///< DWrite ���丮 ��ü�� ��ȯ�Ѵ�.
	inline IDWriteFactory* GetFactory() const _is(m_factory);
	
private:
	FontMap m_fonts; ///< �۲� ��ü���� ���� �۲� ���� ��ü.

	CComPtr<IDWriteFactory> m_factory; ///< �۲� ��ü���� ������ DWriteFactory ��ü.
};

/**
 *@brief �۲� ��ü�� �۲� �̸����κ��� �о�´�.
 *@param factory �۲� ��ü�� ������ ���丮.
 *@param fotnName �о�� �۲��� �̸�.
 *@param size ������ �۲� ��ü�� �۲� ũ��.
 *@param format �о�� �۲� ��ü�� ������ ������.
 *@return �Լ��� ���� ����� ��ȯ�Ѵ�. �����ϸ� S_OK�� ��ȯ�Ǹ�, ������ ���
 * �Ǵٸ� ������ ��ȯ�ȴ�.
 */
HRESULT LoadFont(IDWriteFactory* factory, LPCWSTR fontName, float size, IDWriteTextFormat** format);

}


#endif