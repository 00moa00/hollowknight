#pragma once
#include <GameEngineCore/CoreMinimal.h>
#include <GameEngineCore/GameEngineCollision.h>

#include "ContentsFontRenderer.h"


enum class PromptSetType
{
	TALK,
	INTER,
};

class GameEngineTextureRenderer;

// Ό³Έν :
class PromptSet : public GameEngineActor
{
public:
	// constrcuter destructer
	PromptSet();
	~PromptSet();

	// delete Function
	PromptSet(const PromptSet& _Other) = delete;
	PromptSet(PromptSet&& _Other) noexcept = delete;
	PromptSet& operator=(const PromptSet& _Other) = delete;
	PromptSet& operator=(PromptSet&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _DeltaTime) override;

private:
	GameEngineTextureRenderer* Prompt_;

	GameEngineTextureRenderer* PromptName_;
	GameEngineCollision* PromptCollision_;
	GameEngineStateManager PromptManager_;

public:
	void CreatePrompSet(PromptSetType _Type);
	void SetPrompAppear();
	void SetPrompLeave();

public:
	GameEngineCollision* GetCollision()
	{
		return PromptCollision_;
	}


private:
	bool ThisVSKnightCollision(GameEngineCollision* _This, GameEngineCollision* _Other);


	//================================
	//    Bind State
	//================================

	void PromptWaitStart(const StateInfo& _Info);
	void PromptWaitUpdate(float _DeltaTime, const StateInfo& _Info);
	void PromptWaitEnd(const StateInfo& _Info);

	void PromptIdleStart(const StateInfo& _Info);
	void PromptIdleUpdate(float _DeltaTime, const StateInfo& _Info);
	void PromptIdleEnd(const StateInfo& _Info);

	void PromptChangeDirStart(const StateInfo& _Info);
	void PromptChangeDirUpdate(float _DeltaTime, const StateInfo& _Info);
	void PromptChangeDirEnd(const StateInfo& _Info);

	void PromptChangeLeaveStart(const StateInfo& _Info);
	void PromptChangeLeaveUpdate(float _DeltaTime, const StateInfo& _Info);
	void PromptChangeLeaveEnd(const StateInfo& _Info);
};

