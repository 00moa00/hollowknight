#pragma once
#include "MasterObject.h"

// Ό³Έν :
class TutorialBreakDoor : public  MasterObject
{
public:
	// constrcuter destructer
	TutorialBreakDoor();
	~TutorialBreakDoor();

	// delete Function
	TutorialBreakDoor(const TutorialBreakDoor& _Other) = delete;
	TutorialBreakDoor(TutorialBreakDoor&& _Other) noexcept = delete;
	TutorialBreakDoor& operator=(const TutorialBreakDoor& _Other) = delete;
	TutorialBreakDoor& operator=(TutorialBreakDoor&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _DeltaTime) override;

private:
	bool ObjectVSEffectCollision(GameEngineCollision* _This, GameEngineCollision* _Other);

};

