#pragma once
#include <GameEngineCore/CoreMinimal.h>

// Ό³Έν :
class LowHealth : public GameEngineActor
{
public:
	// constrcuter destructer
	LowHealth();
	~LowHealth();

	// delete Function
	LowHealth(const LowHealth& _Other) = delete;
	LowHealth(LowHealth&& _Other) noexcept = delete;
	LowHealth& operator=(const LowHealth& _Other) = delete;
	LowHealth& operator=(LowHealth&& _Other) noexcept = delete;

protected:
	void Start();
	void Update(float _DeltaTime);

private:
	float ScaleTimer_;

	float4 MaxScale_;
	float4 MinScale_;

	GameEngineUIRenderer* vignette_;

	GameEngineStateManager LowHealthManager_;

private:
	//================================
	//    Bind State
	//================================
	void AddScaleStart(const StateInfo& _Info);
	void AddScaleUpdate(float _DeltaTime, const StateInfo& _Info);
	void AddScaleEnd(const StateInfo& _Info);

	void SubScaleStart(const StateInfo& _Info);
	void SubScaleUpdate(float _DeltaTime, const StateInfo& _Info);
	void SubScaleEnd(const StateInfo& _Info);

};

