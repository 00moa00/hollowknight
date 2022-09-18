#pragma once
#include "MasterObject.h"
// Ό³Έν :
class TutorialBreakLargeDoor : public  MasterObject
{
public:
	// constrcuter destructer
	TutorialBreakLargeDoor();
	~TutorialBreakLargeDoor();

	// delete Function
	TutorialBreakLargeDoor(const TutorialBreakLargeDoor& _Other) = delete;
	TutorialBreakLargeDoor(TutorialBreakLargeDoor&& _Other) noexcept = delete;
	TutorialBreakLargeDoor& operator=(const TutorialBreakLargeDoor& _Other) = delete;
	TutorialBreakLargeDoor& operator=(TutorialBreakLargeDoor&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _DeltaTime) override;

private:

};

