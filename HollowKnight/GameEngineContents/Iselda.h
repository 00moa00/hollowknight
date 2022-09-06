#pragma once
#include "MasterNPC.h"
#include "Shop.h"

// ���� :
class Iselda : public MasterNPC
{
public:
	// constrcuter destructer
	Iselda();
	~Iselda();

	// delete Function
	Iselda(const Iselda& _Other) = delete;
	Iselda(Iselda&& _Other) noexcept = delete;
	Iselda& operator=(const Iselda& _Other) = delete;
	Iselda& operator=(Iselda&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _DeltaTime) override;

private:
	Shop* MapShop_;

	GameEngineStateManager IseldaManager_;

private:
	bool ThisVSKnightCollision(GameEngineCollision* _This, GameEngineCollision* _Other);


	//================================
	//    Bind State
	//================================
	void IseldaWaitStart(const StateInfo& _Info);
	void IseldaWaitUpdate(float _DeltaTime, const StateInfo& _Info);
	void IseldaWaitEnd(const StateInfo& _Info);

	void IseldaIdleStart(const StateInfo& _Info);
	void IseldaIdleUpdate(float _DeltaTime, const StateInfo& _Info);
	void IseldaIdleEnd(const StateInfo& _Info);

	void IseldaChangeDirStart(const StateInfo& _Info);
	void IseldaChangeDirUpdate(float _DeltaTime, const StateInfo& _Info);
	void IseldaChangeDirEnd(const StateInfo& _Info);

	void IseldaChangeLeaveStart(const StateInfo& _Info);
	void IseldaChangeLeaveUpdate(float _DeltaTime, const StateInfo& _Info);
	void IseldaChangeLeaveEnd(const StateInfo& _Info);

};

