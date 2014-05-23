
#include "Bitmap.h"
#include "BitmapManager.h"

using namespace unipen;


Bitmap::Bitmap(LPCWSTR key) 
{
	auto manager = BitmapManager::GetInstance();
	manager->Get(key, &m_bitmap.p);
}


Bitmap::~Bitmap() 
{
}


