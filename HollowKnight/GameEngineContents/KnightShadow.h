#pragma once
#include "MasterActor.h"

// Ό³Έν :
class KnightShadow : public MasterActor
{
public:
	// constrcuter destructer
	KnightShadow();
	~KnightShadow();

	// delete Function
	KnightShadow(const KnightShadow& _Other) = delete;
	KnightShadow(KnightShadow&& _Other) noexcept = delete;
	KnightShadow& operator=(const KnightShadow& _Other) = delete;
	KnightShadow& operator=(KnightShadow&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _DeltaTime) override;

private:
	bool isApearEnd_;
	bool isStartleEnd_;
	bool isDeathEnd_;
	bool isSlashEnd_;

	GameEngineStateManager KnightShadowManager_;

private:
	//================================
	//    Bind State
	//================================

	void ShadowAppearStart(const StateInfo& _Info);
	void ShadowAppearUpdate(float _DeltaTime, const StateInfo& _Info);
	void ShadowAppearEnd(const StateInfo& _Info);

	void ShadowIdleStart(const StateInfo& _Info);
	void ShadowIdleUpdate(float _DeltaTime, const StateInfo& _Info);
	void ShadowIdleEnd(const StateInfo& _Info);

	void ShadowStartleStart(const StateInfo& _Info);
	void ShadowStartleUpdate(float _DeltaTime, const StateInfo& _Info);
	void ShadowStartleEnd(const StateInfo& _Info);

	void ShadowDeathStart(const StateInfo& _Info);
	void ShadowDeathUpdate(float _DeltaTime, const StateInfo& _Info);
	void ShadowDeathEnd(const StateInfo& _Info);

	void ShadowFlyStart(const StateInfo& _Info);
	void ShadowFlyUpdate(float _DeltaTime, const StateInfo& _Info);
	void ShadowFlyEnd(const StateInfo& _Info);

	void ShadowSlashStart(const StateInfo& _Info);
	void ShadowSlashUpdate(float _DeltaTime, const StateInfo& _Info);
	void ShadowSlashEnd(const StateInfo& _Info);

	void ShadowTurnStart(const StateInfo& _Info);
	void ShadowTurnUpdate(float _DeltaTime, const StateInfo& _Info);
	void ShadowTurnEnd(const StateInfo& _Info);

};

