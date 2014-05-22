
#ifndef _Unipen_SoundManager_h_
#define _Unipen_SoundManager_h_


#include "Entity.h"

#include <XAudio2.h>
#include <atlbase.h>

#include <memory>
#include <map>
#include <string>

namespace unipen {

class SoundManager : public Entity {
public:
	inline static std::shared_ptr<SoundManager> GetInstance() { return s_instance; }
	
	typedef std::map<std::wstring, XAUDIO2_BUFFER> BufferMap;

private:
	static std::shared_ptr<SoundManager> s_instance;

	SoundManager();
public:
	virtual ~SoundManager();


private:
	CComPtr<IXAudio2> m_xaudio2; ///< XAudio2 객체
	CComPtr<IXAudio2MasteringVoice> m_masteringVoice; // 마스터보이스 객체
	BufferMap m_buffers; ///< 사운드 버퍼 모음
};

#endif