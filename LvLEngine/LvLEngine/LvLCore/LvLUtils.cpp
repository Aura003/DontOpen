#include "stdafx.h"
#include"LvLResourceManager.h"
#include "iLvLTexture.h"
#include "iLvLEngine.h"
#include "LvLUtils.h"

XMINT2 LvLUtils::GetTextureSize(iLvLEngine* engine, const char* resourceID, float pixelRaito)
{
	XMINT2 size(0, 0);
	iLvLResource* res = engine->GetResourceManager()->Get(resourceID);
	if (res && res->GetType() == eLvLResourceType::rtTexture)
	{
		size = ((iLvLTexture*)res)->GetSize();
	}
	size.x = (int)(size.x * pixelRaito);
	size.y = (int)(size.y * pixelRaito);
	return size;
}
