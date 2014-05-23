
#include "SoundManager.h"

using namespace unipen;

SoundManager::SoundManager()
{
	HRESULT hr = S_OK;

	hr = XAudio2Create(&m_xaudio2.p, 0, XAUDIO2_DEFAULT_PROCESSOR);
	
	if(SUCCEEDED(hr))
	{
		hr = m_xaudio2->CreateMasteringVoice (&m_masteringVoice.p);
	}

	if(FAILED(hr))
		; // TODO: what should i do?
}