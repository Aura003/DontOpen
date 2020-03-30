#pragma once

class LvLEngineAlpha : public iLvLEngine
{
public:
	virtual void Initialize() override;
	virtual void ShutDown() override;
	virtual void StartEngine() override;
	virtual void Update() override;
	virtual void Draw() override;
};

