#pragma once
class LvL2DTexture : public iLvLTexture
{
	LvL_DECLARE_REFCOUNTTED();

public:
	LvL2DTexture(SDL_Texture* texture, const char* name);
	virtual const char* GetName() override;
	virtual eLvLResourceType GetType() override;
	virtual void* GetHandle() override;
	virtual XMINT2 GetSize() override;

private:
	virtual ~LvL2DTexture();
	SDL_Texture* _pTexture = NULL;
	std::string _pName;

};

