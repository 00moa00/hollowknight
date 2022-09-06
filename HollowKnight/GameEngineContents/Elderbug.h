#pragma once
#include "MasterNPC.h"

// Ό³Έν :
class Elderbug : public MasterNPC
{
public:
	// constrcuter destructer
	Elderbug();
	~Elderbug();

	// delete Function
	Elderbug(const Elderbug& _Other) = delete;
	Elderbug(Elderbug&& _Other) noexcept = delete;
	Elderbug& operator=(const Elderbug& _Other) = delete;
	Elderbug& operator=(Elderbug&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _DeltaTime) override;

private:
	GameEngineStateManager ElderManager_;

private:
	bool ThisVSKnightCollision(GameEngineCollision* _This, GameEngineCollision* _Other);


	//================================
	//    Bind State
	//================================

	void ElderWaitStart(const StateInfo& _Info);
	void ElderWaitUpdate(float _DeltaTime, const StateInfo& _Info);
	void ElderWaitEnd(const StateInfo& _Info);

	void ElderIdleStart(const StateInfo& _Info);
	void ElderIdleUpdate(float _DeltaTime, const StateInfo& _Info);
	void ElderIdleEnd(const StateInfo& _Info);

	void ElderChangeDirStart(const StateInfo& _Info);
	void ElderChangeDirUpdate(float _DeltaTime, const StateInfo& _Info);
	void ElderChangeDirEnd(const StateInfo& _Info);

	void ElderChangeLeaveStart(const StateInfo& _Info);
	void ElderChangeLeaveUpdate(float _DeltaTime, const StateInfo& _Info);
	void ElderChangeLeaveEnd(const StateInfo& _Info);
};

