

#ifndef _Unipen_Audio_Buffer_h_
#define _Unipen_Audio_Buffer_h_


#include <Windows.h>
#include <XAudio2.h>



namespace unipen {


	struct AudioBuffer 
	{
		WAVEFORMATEXTENSIBLE wfx;
		void* data;
		UINT dataSize;
	};

}
#endif