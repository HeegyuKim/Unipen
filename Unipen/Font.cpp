
#include "Font.h"
#include "FontManager.h"

using namespace unipen;

Font::Font(LPCWSTR key) 
{
	auto manager = FontManager::GetInstance();
	manager->Get(key, &m_tf.p);
}

Font::~Font()
{
}



