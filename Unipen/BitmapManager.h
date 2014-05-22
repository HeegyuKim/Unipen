
#ifndef _BitmapManager_h_
#define _BitmapManager_h_

#include "Entity.h"

#include <D2D1.h>
#include <atlbase.h>
#include <wincodec.h>

#include <memory>
#include <map>
#include <string>


namespace unipen {

class BitmapManager : public Entity {
public:
	/**
	 *@brief �̱����� ��ȯ�ϴ� �޼���
	 *@return BitmapManager�� �̱���
	 */
	inline std::shared_ptr<BitmapManager> GetInstance() { return s_instance; }

	/**@brief ��Ʈ�ʵ��� �����ϴ� ���� �ڷᱸ���� Ÿ���� �����Ѵ�. */
	typedef std::map<std::wstring, ID2D1Bitmap*> BitmapMap;

private:
	static std::shared_ptr<BitmapManager> s_instance; ///< BitmapManagerŬ������ �̱���

public:
	///< �⺻ ������.
	BitmapManager();
	
	virtual ~BitmapManager();

	bool Load(LPCWSTR key, LPCWSTR filename, bool overwrite = true);
	
	bool Load(LPCWSTR key, void* data, UINT size, bool overwrite = true);
	
	bool Add(LPCWSTR key, ID2D1Bitmap* bitmap);
	
	bool Get(LPCWSTR key, ID2D1Bitmap** bitmap);

	/**
	 *@brief ������ Ű ���� �����Ѵ�.
	 *@param key ������ Ű ��.
	 *@return ���ſ� ���������� true�� ��ȯ�ϰ�, 
	 *Ű�� �������� �ʾ� ��ȯ���� ���ߴٸ� false�� ��ȯ�Ѵ�.
	 */
	bool Remove(LPCWSTR key);
	

	/**
	 *@brief ������ Ű ���� ������ �ִ����� ��ȯ�Ѵ�.
	 *@param key ������ �ִ��� Ȯ���� Ű ��.
	 *@return ������ �ִٸ� true��, �׷��� �ʴٸ� false�� ��ȯ�Ѵ�.
	 */
	bool Has(LPCWSTR key);


	///< ��Ʈ�ʵ��� ������ ���� ��ü�� ��ȯ�Ѵ�.
	inline BitmapMap& GetBitmaps() { return m_bitmaps; }
	
	///< ��Ʈ�ʵ��� ������ ���� ��ü�� ��ȯ�Ѵ�.
	inline const BitmapMap& GetBitmaps() const { return m_bitmaps; }
	
	///< ���� Ÿ�� ��ü�� ��ȯ�Ѵ�.
	inline ID2D1RenderTarget* GetRenderTarget() { return m_rt; }
	
	///< ���� Ÿ�� ��ü�� ��ȯ�Ѵ�.
	inline const ID2D1RenderTarget* GetRenderTarget() const { return m_rt; }

	///< �̹��� ���丮 ��ü�� ��ȯ�Ѵ�.
	inline IWICImagingFactory* GetImagingFactory() { return m_imagingFactory; }
	
	///< �̹��� ���丮 ��ü�� ��ȯ�Ѵ�.
	inline const IWICImagingFactory* GetImagingFactory() const { return m_imagingFactory; }

private:
	BitmapMap m_bitmaps; ///< ��Ʈ����� �����ϴ� ���� �ڷᱸ��

	CComPtr<ID2D1RenderTarget> m_rt; ///< ��Ʈ���� ������ ����Ÿ��
	CComPtr<IWICImagingFactory> m_imagingFactory; ///< ��Ʈ���� �о���� WIC���丮
};


HRESULT LoadBitmap(IWICImagingFactory* imagingFactory, 
				   ID2D1RenderTarget* rt,
				   LPCWSTR filename,
				   ID2D1Bitmap** bitmap );

HRESULT LoadBitmap(IWICImagingFactory* imagingFactory, 
				   ID2D1RenderTarget* rt,
				   void** data,
				   UINT size,
				   ID2D1Bitmap** bitmap );

}

#endif