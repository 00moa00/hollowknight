#pragma once
#include "MasterObject.h"

// Ό³Έν :
class TutorialGate : public  MasterObject
{
public:
	// constrcuter destructer
	TutorialGate();
	~TutorialGate();

	// delete Function
	TutorialGate(const TutorialGate& _Other) = delete;
	TutorialGate(TutorialGate&& _Other) noexcept = delete;
	TutorialGate& operator=(const TutorialGate& _Other) = delete;
	TutorialGate& operator=(TutorialGate&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _DeltaTime) override;

private:
	bool ObjectVSEffectCollision(GameEngineCollision* _This, GameEngineCollision* _Other);

};

