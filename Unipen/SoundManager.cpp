
#include "SoundManager.h"

using namespace unipen;
using namespace std;

SoundManager::SoundManager()
	: m_masteringVoice(nullptr)
{
	HRESULT hr = S_OK;

	hr = XAudio2Create(&m_xaudio2.p, 0, XAUDIO2_DEFAULT_PROCESSOR);
	
	if(SUCCEEDED(hr))
	{
		hr = m_xaudio2->CreateMasteringVoice (&m_masteringVoice);
	}

	if(FAILED(hr))
		; // TODO: what should i do?
}


SoundManager::~SoundManager()
{
	if(m_masteringVoice)
	{
		m_masteringVoice->DestroyVoice();
		m_masteringVoice = nullptr;
	}
}



bool SoundManager::CreateVoice(LPCWSTR key, IXAudio2SourceVoice** voice)
{
	shared_ptr<SoundBuffer> buffer;
	HRESULT hr = S_OK;

	if(Get(key, buffer))
	{
		hr = m_xaudio2->CreateSourceVoice(voice, &buffer->wfx.Format);
	}

	if(SUCCEEDED(hr))
	{
		hr = (*voice)->SubmitSourceBuffer(&buffer->buffer);
	}
	
}

bool SoundManager::Get(LPCWSTR key, std::shared_ptr<SoundBuffer>& buffer);

bool SoundManager::Remote(LPCWSTR key);

bool SoundManager::Add(LPCWSTR key, std::shared_ptr<SoundBuffer> buffer, bool overwrite = true);

bool SoundManager::Load(LPCWSTR key, LPCWSTR filename, bool overwrite = true);

bool SoundManager::Load(LPCWSTR key, void* data, UINT size, bool overwrite);


HRESULT LoadSoundBuffer(IXAudio2* xaudio2, LPCWSTR filename, SoundBuffer& buffer)
{

	return E_NOTIMPL;
}

HRESULT LoadSoundBuffer(IXAudio2* xaudio2, void* data, UINT size, SoundBuffer& buffer)
{

	return E_NOTIMPL;
}