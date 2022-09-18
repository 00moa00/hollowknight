#pragma once
#include <GameEngineCore/CoreMinimal.h>
#include <GameEngineCore/GameEngineCollision.h>

#include "PromptSet.h"

// Ό³Έν :
class Tablet : public GameEngineActor
{
public:
	// constrcuter destructer
	Tablet();
	~Tablet();

	// delete Function
	Tablet(const Tablet& _Other) = delete;
	Tablet(Tablet&& _Other) noexcept = delete;
	Tablet& operator=(const Tablet& _Other) = delete;
	Tablet& operator=(Tablet&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _DeltaTime) override;

private:

	float Alpha_;

	GameEngineStateManager TabletManager_;


	GameEngineTextureRenderer* BackRenderer_;
	GameEngineTextureRenderer* LightRenderer_;

	GameEngineCollision* Collision_;

	PromptSet* PromptSet_;
public:
	void CreateTablet(std::string _BackFilePath, std::string _LightFilePath, float4 _CollSize);

	void TabletIdleStart(const StateInfo& _Info);
	void TabletIdleUpdate(float _DeltaTime, const StateInfo& _Info);
	void TabletIdleEnd(const StateInfo& _Info);

	void TabletAppearStart(const StateInfo& _Info);
	void TabletAppearUpdate(float _DeltaTime, const StateInfo& _Info);
	void TabletAppearEnd(const StateInfo& _Info);


	//================================
	//    Bind 
	//================================
	bool TabletVSKnightCollision(GameEngineCollision* _This, GameEngineCollision* _Other);

};

