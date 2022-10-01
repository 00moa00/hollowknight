#pragma once
#include <GameEngineCore/CoreMinimal.h>

// Ό³Έν :
class WhiteParicleMaker : public GameEngineActor
{
public:
	// constrcuter destructer
	WhiteParicleMaker();
	~WhiteParicleMaker();

	// delete Function
	WhiteParicleMaker(const WhiteParicleMaker& _Other) = delete;
	WhiteParicleMaker(WhiteParicleMaker&& _Other) noexcept = delete;
	WhiteParicleMaker& operator=(const WhiteParicleMaker& _Other) = delete;
	WhiteParicleMaker& operator=(WhiteParicleMaker&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _DeltaTime) override;

private:

};

