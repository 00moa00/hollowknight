#pragma once
#include <GameEngineCore/CoreMinimal.h>
#include <GameEngineCore/GameEngineCollision.h>

// Ό³Έν :
class DialogueSet : public GameEngineActor
{
public:
	// constrcuter destructer
	DialogueSet();
	~DialogueSet();

	// delete Function
	DialogueSet(const DialogueSet& _Other) = delete;
	DialogueSet(DialogueSet&& _Other) noexcept = delete;
	DialogueSet& operator=(const DialogueSet& _Other) = delete;
	DialogueSet& operator=(DialogueSet&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _DeltaTime) override;

private:
	GameEngineUIRenderer* DialogueTop_;
	GameEngineUIRenderer* DialogueBottom_;
	GameEngineUIRenderer* NextArrow_;

private:



public:
	//================================
	//     Getter
	//================================



	//================================
	//    Setter
	//================================
};

