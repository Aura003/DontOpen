#pragma once
class iLvLEngine 
{

public:
	virtual void Initialize() = 0; //=0 makes it abstract 
	virtual void ShutDown() = 0;
	virtual void StartEngine() = 0;
	virtual void Update() = 0;
	virtual void Draw() = 0;
private:
protected:
};
