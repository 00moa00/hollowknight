#pragma once
#include <GameEngineCore/CoreMinimal.h>
#include "VesselFrame.h"
#include "Mask.h"
#include "Geo.h"
#include "Soul.h"

// Ό³Έν :
class HUD : public GameEngineActor
{
public:
	// constrcuter destructer
	HUD();
	~HUD();

	// delete Function
	HUD(const HUD& _Other) = delete;
	HUD(HUD&& _Other) noexcept = delete;
	HUD& operator=(const HUD& _Other) = delete;
	HUD& operator=(HUD&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _DeltaTime) override;
	void LevelStartEvent() override;
	void LevelEndEvent() override;

private:

	bool MaskesAppearEnd_;

	int MaskesSize_;
	int MakesAppearCount_;

	int CurMask_;

	float MaskAppearTimer_;

	VesselFrame* VesselFrame_;
	Geo* Geo_;
	Soul* Soul_;
	std::vector<Mask*> Maskes_;

	

	GameEngineStateManager HUDManager_;

public:
	void NewMask();
	void RefillMask();
	void BreakMask();
	void AllRefillMask();
	void SetAppearAnimation();

private:

	//================================
	//    Bind State
	//================================

	void MaskAppearStart(const StateInfo& _Info);
	void MaskAppearUpdate(float _DeltaTime, const StateInfo& _Info);
	void MaskAppearEnd(const StateInfo& _Info);

	void HUDIdleStart(const StateInfo& _Info);
	void HUDIdleUpdate(float _DeltaTime, const StateInfo& _Info);
	void HUDIdleEnd(const StateInfo& _Info);

	void HUDHideStart(const StateInfo& _Info);
	void HUDHideUpdate(float _DeltaTime, const StateInfo& _Info);
	void HUDHideEnd(const StateInfo& _Info);

};

