#pragma once
#include <GameEngineCore/CoreMinimal.h>
#include <GameEngineCore/GameEngineCollision.h>

#include "PromptSet.h"
#include "TabletDialogue.h"

#include "ContentsFontRenderer.h"
#include "SpellFocusInfo.h"

enum class TabletType
{

	FocusSpell,
	Tu_Story

};

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

	bool isOpenDialogue_;

	float Alpha_;


	GameEngineTextureRenderer* BackRenderer_;
	GameEngineTextureRenderer* LightRenderer_;

	GameEngineCollision* Collision_;

	PromptSet* PromptSet_;

	TabletDialogue* TabletDialogue_;
	SpellFocusInfo* SpellFocusInfo_;



	//TabletType TabletType_;
	GameEngineStateManager TabletManager_;

public:
	void CreateTablet(std::string _BackFilePath, std::string _LightFilePath, float4 _CollSize, TabletType _TabletType);

	void TabletDialogueOn();
	void TabletDialogueOff();

	bool GetisOpenDialogue() const
	{
		return isOpenDialogue_;
	}

	TabletDialogue* GetTabletDialogue() const
	{
		return TabletDialogue_;
	}

	PromptSet* GetPromptSet() const
	{
		return PromptSet_;
	}


private:


	void SetFocusSpell();

	//================================
	//    Bind 
	//================================
	void TabletIdleStart(const StateInfo& _Info);
	void TabletIdleUpdate(float _DeltaTime, const StateInfo& _Info);
	void TabletIdleEnd(const StateInfo& _Info);

	void TabletAppearStart(const StateInfo& _Info);
	void TabletAppearUpdate(float _DeltaTime, const StateInfo& _Info);
	void TabletAppearEnd(const StateInfo& _Info);

	void TabletOnDialougueStart(const StateInfo& _Info);
	void TabletOnDialougueUpdate(float _DeltaTime, const StateInfo& _Info);
	void TabletOnDialougueEnd(const StateInfo& _Info);


	void TabletOffDialougueStart(const StateInfo& _Info);
	void TabletOffDialougueUpdate(float _DeltaTime, const StateInfo& _Info);
	void TabletOffDialougueEnd(const StateInfo& _Info);


	//================================
	//    Bind 
	//================================
	bool TabletVSKnightCollision(GameEngineCollision* _This, GameEngineCollision* _Other);

};

