
#ifndef _Unipen_SoundManager_h_
#define _Unipen_SoundManager_h_


#include "Entity.h"
#include "SoundBuffer.h"

#include <XAudio2.h>
#include <atlbase.h>

#include <memory>
#include <map>
#include <string>

namespace unipen {

/**
 *@class SoundManager
 *@author 김희규
 *@date 2014/05/22
 *@brief 사운드 자원들을 관리하는 클래스.
 */
class SoundManager : public Entity {
public:

	///< 사운드 관리자의 싱글톤을 반환하는 정적 메서드
	inline static std::shared_ptr<SoundManager> GetInstance() { return s_instance; }
	
	///< 사운드 버퍼를 관리하는 지도 자료구조
	typedef std::map<std::wstring, std::shared_ptr<SoundBuffer>> BufferMap;

private:
	///< 클래스의 싱글톤
	static std::shared_ptr<SoundManager> s_instance;

	///< XAudio2 초기화를 수행하는 기본 생성자.
	SoundManager();

public:
	///< 자원들을 해제하는 기본 파괴자
	virtual ~SoundManager();

	bool CreateVoice(LPCWSTR key, IXAudio2SourceVoice** voice);

	bool Get(LPCWSTR key, std::shared_ptr<SoundBuffer>& buffer);

	bool Remote(LPCWSTR key);

	bool Has(LPCWSTR key);

	bool Add(LPCWSTR key, std::shared_ptr<SoundBuffer> buffer, bool overwrite = true);

	bool Load(LPCWSTR key, LPCWSTR filename, bool overwrite = true);

	bool Load(LPCWSTR key, void* data, UINT size, bool overwrite);


	///< XAudio2 객체를 반환한다.
	IXAudio2* GetXAudio2() const { return m_xaudio2; }
	
	///< 마스터링보이스 객체를 반환한다.
	IXAudio2MasteringVoice* GetMasteringVoice() const { return m_masteringVoice; }

private:
	CComPtr<IXAudio2> m_xaudio2; ///< XAudio2 객체
	
	IXAudio2MasteringVoice* m_masteringVoice; ///< 마스터보이스 객체

	BufferMap m_buffers; ///< 사운드 버퍼 모음
};

HRESULT LoadSoundBuffer(IXAudio2* xaudio2, LPCWSTR filename, SoundBuffer& buffer);


HRESULT LoadSoundBuffer(IXAudio2* xaudio2, void* data, UINT size, SoundBuffer& buffer);


}

#endif