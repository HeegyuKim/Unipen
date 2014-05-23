
#include "BitmapManager.h"

using namespace unipen;

std::shared_ptr<BitmapManager> BitmapManager::s_instance(
		new BitmapManager);

HRESULT unipen::LoadBitmap(IWICImagingFactory* imagingFactory, 
				   ID2D1RenderTarget* rt,
				   LPCWSTR filename,
				   ID2D1Bitmap** bitmap ) 
{
	CComPtr<IWICFormatConverter> converter;
	CComPtr<IWICBitmapDecoder> decoder;
	CComPtr<IWICBitmapFrameDecode> frame;

	HRESULT hr = S_OK;

	// �����̸����κ��� ���ڴ� ����
	hr = imagingFactory->CreateDecoderFromFilename (
					filename,
					nullptr,
					GENERIC_READ,
					WICDecodeMetadataCacheOnDemand,
					&decoder.p);
	if(FAILED(hr)) return hr;

	// ������ ������
	hr = decoder->GetFrame(0, &frame.p);
	if(FAILED(hr)) return hr;

	// ���� ��ȯ�� ����
	hr = imagingFactory->CreateFormatConverter (
					&converter.p );
	if(FAILED(hr)) return hr;
				
	// ���� ��ȯ�� �ʱ�ȭ
	hr = converter->Initialize (
			frame,
			GUID_WICPixelFormat32bppPBGRA,
			WICBitmapDitherTypeNone,
			nullptr,
			1.0,
			WICBitmapPaletteTypeCustom );
	if(FAILED(hr)) return hr;

	// Direct2D ��Ʈ�� ����.
	hr = rt->CreateBitmapFromWicBitmap (
			converter,
			bitmap );

	return hr;
}

HRESULT unipen::LoadBitmap(IWICImagingFactory* imagingFactory, 
				   ID2D1RenderTarget* rt,
				   void* data,
				   UINT size,
				   ID2D1Bitmap** bitmap )
{
	
	CComPtr<IWICFormatConverter> converter;
	CComPtr<IWICBitmapDecoder> decoder;
	CComPtr<IWICBitmapFrameDecode> frame;
	CComPtr<IWICStream> stream;
	HRESULT hr = S_OK;

	// ��Ʈ�� ����
	hr = imagingFactory->CreateStream(&stream.p);
	if(FAILED(hr)) return hr;

	// ��Ʈ�� �ʱ�ȭ
	hr = stream->InitializeFromMemory (
					(WICInProcPointer)data,
					size );
	if(FAILED(hr)) return hr;

	// �����̸����κ��� ���ڴ� ����
	hr = imagingFactory->CreateDecoderFromStream (
		stream,
		nullptr,
		WICDecodeMetadataCacheOnLoad,
		&decoder.p);
	if(FAILED(hr)) return hr;

	// ������ ������
	hr = decoder->GetFrame(0, &frame.p);
	if(FAILED(hr)) return hr;

	// ���� ��ȯ�� ����
	hr = imagingFactory->CreateFormatConverter (
					&converter.p );
	if(FAILED(hr)) return hr;
				
	// ���� ��ȯ�� �ʱ�ȭ
	hr = converter->Initialize (
			frame,
			GUID_WICPixelFormat32bppPBGRA,
			WICBitmapDitherTypeNone,
			nullptr,
			1.0,
			WICBitmapPaletteTypeCustom );
	if(FAILED(hr)) return hr;

	// Direct2D ��Ʈ�� ����.
	hr = rt->CreateBitmapFromWicBitmap (
			converter,
			bitmap );

	return hr;
}


BitmapManager::BitmapManager(){}
BitmapManager::~BitmapManager(){}


bool BitmapManager::Load(LPCWSTR key, LPCWSTR filename, bool overwrite)
{
	auto it = m_bitmaps.find(key);
	if(it != m_bitmaps.end())
	{
		if(!overwrite)
			return false;
		else
			SafeRelease(it->second);
	}

	ID2D1Bitmap* bitmap = nullptr;
	HRESULT hr = LoadBitmap(
			m_imagingFactory,
			m_rt,
			filename,
			&bitmap );
	if(FAILED(hr)) return false;

	m_bitmaps.insert(std::make_pair(std::wstring(key), bitmap));

	return true;
}
	
bool BitmapManager::Load(LPCWSTR key, void* data, UINT size, bool overwrite)
{
	auto it = m_bitmaps.find(key);
	if(it != m_bitmaps.end())
	{
		if(!overwrite)
			return false;
		else
			SafeRelease(it->second);
	}

	ID2D1Bitmap* bitmap = nullptr;
	HRESULT hr = LoadBitmap(
				m_imagingFactory,
				m_rt,
				data,
				size,
				&bitmap );

	if(FAILED(hr)) return false;

	m_bitmaps.insert(std::make_pair(std::wstring(key), bitmap));

	return true;
}
	
bool BitmapManager::Add(LPCWSTR key, ID2D1Bitmap* bitmap, bool overwrite)
{
	auto it = m_bitmaps.find(key);
	if(it != m_bitmaps.end())
	{
		if(!overwrite)
			return false;
		else
			SafeRelease(it->second);
	}

	m_bitmaps.insert(std::make_pair(std::wstring(key), bitmap));

	return true;
}
	
bool BitmapManager::Get(LPCWSTR key, ID2D1Bitmap** bitmap) {
	auto it = m_bitmaps.find(key);
	if(it != m_bitmaps.end())
	{
		*bitmap = it->second;
		if(it->second)
			it->second->AddRef();
		return true;
	}
	else return false;
}
	
bool BitmapManager::Remove(LPCWSTR key)
{
	auto it = m_bitmaps.find(key);
	if(it != m_bitmaps.end())
	{
		SafeRelease(it->second);
		m_bitmaps.erase(it);
		return true;
	}
	else return false;
}

bool BitmapManager::Has(LPCWSTR key)
{
	auto it = m_bitmaps.find(key);
	return it != m_bitmaps.end();
}