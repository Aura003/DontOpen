#pragma once

class EngineAlpha : public iLvLEngine
{
public:
	// Inherited via iLvLEngine
	virtual void Initialize() override;
	virtual void ShutDown() override;
	virtual void StartEngine() override;
	virtual void Update() override;
	virtual void Draw() override;
};

