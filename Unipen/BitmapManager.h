
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
	 *@brief 싱글톤을 반환하는 메서드
	 *@return BitmapManager의 싱글톤
	 */
	inline std::shared_ptr<BitmapManager> GetInstance() { return s_instance; }

	/**@brief 비트맵들을 보관하는 지도 자료구조의 타입을 정의한다. */
	typedef std::map<std::wstring, ID2D1Bitmap*> BitmapMap;

private:
	static std::shared_ptr<BitmapManager> s_instance; ///< BitmapManager클래스의 싱글톤

public:
	///< 기본 생성자.
	BitmapManager();
	
	virtual ~BitmapManager();

	bool Load(LPCWSTR key, LPCWSTR filename, bool overwrite = true);
	
	bool Load(LPCWSTR key, void* data, UINT size, bool overwrite = true);
	
	bool Add(LPCWSTR key, ID2D1Bitmap* bitmap);
	
	bool Get(LPCWSTR key, ID2D1Bitmap** bitmap);

	/**
	 *@brief 지정된 키 값을 제거한다.
	 *@param key 제거할 키 값.
	 *@return 제거에 성공했으면 true를 반환하고, 
	 *키가 존재하지 않아 반환하지 못했다면 false를 반환한다.
	 */
	bool Remove(LPCWSTR key);
	

	/**
	 *@brief 지정된 키 값을 가지고 있는지를 반환한다.
	 *@param key 가지고 있는지 확인할 키 값.
	 *@return 가지고 있다면 true를, 그렇지 않다면 false를 반환한다.
	 */
	bool Has(LPCWSTR key);


	///< 비트맵들을 보관한 지도 객체를 반환한다.
	inline BitmapMap& GetBitmaps() { return m_bitmaps; }
	
	///< 비트맵들을 보관한 지도 객체를 반환한다.
	inline const BitmapMap& GetBitmaps() const { return m_bitmaps; }
	
	///< 렌더 타겟 객체를 반환한다.
	inline ID2D1RenderTarget* GetRenderTarget() { return m_rt; }
	
	///< 렌더 타겟 객체를 반환한다.
	inline const ID2D1RenderTarget* GetRenderTarget() const { return m_rt; }

	///< 이미지 팩토리 객체를 반환한다.
	inline IWICImagingFactory* GetImagingFactory() { return m_imagingFactory; }
	
	///< 이미지 팩토리 객체를 반환한다.
	inline const IWICImagingFactory* GetImagingFactory() const { return m_imagingFactory; }

private:
	BitmapMap m_bitmaps; ///< 비트뱁들을 보관하는 지도 자료구조

	CComPtr<ID2D1RenderTarget> m_rt; ///< 비트맵을 생성할 렌더타겟
	CComPtr<IWICImagingFactory> m_imagingFactory; ///< 비트맵을 읽어들일 WIC팩토리
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