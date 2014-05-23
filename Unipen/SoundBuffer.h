

#ifndef _Unipen_Audio_Buffer_h_
#define _Unipen_Audio_Buffer_h_


#include <Windows.h>
#include <XAudio2.h>



namespace unipen {


	struct SoundBuffer 
	{
		WAVEFORMATEXTENSIBLE wfx;
		XAUDIO2_BUFFER buffer;
	};

}
#endif