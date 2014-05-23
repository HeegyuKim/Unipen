
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
 *@author �����
 *@date 2014/05/22
 *@brief ���� �ڿ����� �����ϴ� Ŭ����.
 */
class SoundManager : public Entity {
public:

	///< ���� �������� �̱����� ��ȯ�ϴ� ���� �޼���
	inline static std::shared_ptr<SoundManager> GetInstance() { return s_instance; }
	
	///< ���� ���۸� �����ϴ� ���� �ڷᱸ��
	typedef std::map<std::wstring, std::shared_ptr<SoundBuffer>> BufferMap;

private:
	///< Ŭ������ �̱���
	static std::shared_ptr<SoundManager> s_instance;

	///< XAudio2 �ʱ�ȭ�� �����ϴ� �⺻ ������.
	SoundManager();

public:
	///< �ڿ����� �����ϴ� �⺻ �ı���
	virtual ~SoundManager();

	bool CreateVoice(LPCWSTR key, IXAudio2SourceVoice** voice);

	bool Get(LPCWSTR key, std::shared_ptr<SoundBuffer>& buffer);

	bool Remote(LPCWSTR key);

	bool Has(LPCWSTR key);

	bool Add(LPCWSTR key, std::shared_ptr<SoundBuffer> buffer, bool overwrite = true);

	bool Load(LPCWSTR key, LPCWSTR filename, bool overwrite = true);

	bool Load(LPCWSTR key, void* data, UINT size, bool overwrite);


	///< XAudio2 ��ü�� ��ȯ�Ѵ�.
	IXAudio2* GetXAudio2() const { return m_xaudio2; }
	
	///< �����͸����̽� ��ü�� ��ȯ�Ѵ�.
	IXAudio2MasteringVoice* GetMasteringVoice() const { return m_masteringVoice; }

private:
	CComPtr<IXAudio2> m_xaudio2; ///< XAudio2 ��ü
	
	IXAudio2MasteringVoice* m_masteringVoice; ///< �����ͺ��̽� ��ü

	BufferMap m_buffers; ///< ���� ���� ����
};

HRESULT LoadSoundBuffer(IXAudio2* xaudio2, LPCWSTR filename, SoundBuffer& buffer);


HRESULT LoadSoundBuffer(IXAudio2* xaudio2, void* data, UINT size, SoundBuffer& buffer);


}

#endif