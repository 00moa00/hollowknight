#pragma once
#include "Monster.h"
// Ό³Έν :
class Crawlid : public Monster
{
public:
	// constrcuter destructer
	Crawlid();
	~Crawlid();

	// delete Function
	Crawlid(const Crawlid& _Other) = delete;
	Crawlid(Crawlid&& _Other) noexcept = delete;
	Crawlid& operator=(const Crawlid& _Other) = delete;
	Crawlid& operator=(Crawlid&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _DeltaTime) override;

public:
	void SetMonsterHit(int _Damage, float4 _StunDir, float4 _KnightDir) override;

private:
	bool isTurnEnd_;
	bool isDeathEnd_;

	float CrawildKnockbackTimer_;


	GameEngineStateManager CrawlidManager_;

	//GameEngineRenderer* GameEngineRenderer_;

private:
	//================================
	//    Bind State
	//================================
	void CrawlidStillStart(const StateInfo& _Info);
	void CrawlidStillUpdate(float _DeltaTime, const StateInfo& _Info);
	void CrawlidStillEnd(float _DeltaTime, const StateInfo& _Info);

	void CrawlidWalkStart(const StateInfo& _Info);
	void CrawlidWalkUpdate(float _DeltaTime, const StateInfo& _Info);
	void CrawlidWalkEnd(const StateInfo& _Info);

	void CrawlidFallStart(const StateInfo& _Info);
	void CrawlidFallUpdate(float _DeltaTime, const StateInfo& _Info);
	void CrawlidFallEnd(const StateInfo& _Info);

	void CrawlidTurnStart(const StateInfo& _Info);
	void CrawlidTurnUpdate(float _DeltaTime, const StateInfo& _Info);
	void CrawlidTurnEnd(const StateInfo& _Info);

	void CrawlidStunStart(const StateInfo& _Info);
	void CrawlidStunUpdate(float _DeltaTime, const StateInfo& _Info);
	void CrawlidStunEnd(const StateInfo& _Info);

	void CrawlidDeathStart(const StateInfo& _Info);
	void CrawlidDeathUpdate(float _DeltaTime, const StateInfo& _Info);
	void CrawlidDeathEnd(const StateInfo& _Info);

	//================================
	//    Bind
	//================================
	bool MonsterVSWallCollision(GameEngineCollision* _This, GameEngineCollision* _Other);	//Ί®

};

