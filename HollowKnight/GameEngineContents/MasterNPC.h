#pragma once
#include <GameEngineCore/CoreMinimal.h>
#include <GameEngineCore/GameEngineCollision.h>

#include "ContentsFontRenderer.h"
#include "MasterActor.h"
#include "PromptSet.h"
#include "DialogueSet.h"

struct NPCState
{
	std::string NPCName_;
};

// Ό³Έν :
class MasterNPC : public MasterActor
{
public:
	// constrcuter destructer
	MasterNPC();
	~MasterNPC();

	// delete Function
	MasterNPC(const MasterNPC& _Other) = delete;
	MasterNPC(MasterNPC&& _Other) noexcept = delete;
	MasterNPC& operator=(const MasterNPC& _Other) = delete;
	MasterNPC& operator=(MasterNPC&& _Other) noexcept = delete;

protected:
	DialogueSet* DialogueSet_;

	ContentsFontRenderer* NPCNameFontRenderer_;

private:
	NPCState NPCState_;
	PromptSet* PromptSet_;

	bool isTalking_;
	bool isOpenShop_;

public:

	//================================
	//     Getter
	//================================
	std::string& GetNPCName()
	{
		return NPCState_.NPCName_;
	}

	PromptSet* GetPromptSet()
	{
		return PromptSet_;
	}

	DialogueSet* GetDialogueSet()
	{
		return DialogueSet_;
	}

	ContentsFontRenderer* GetNameFontRenderer()
	{
		return  NPCNameFontRenderer_;
	}

	bool isTalking()
	{
		return isTalking_;
	}

	//================================
	//    Setter
	//================================
	void SetNPCName(std::string _Name)
	{
		NPCState_.NPCName_ = _Name;
	}

	void SetisTalking(bool b)
	{
		isTalking_ = b;
	}

	void SetisShop(bool b)
	{
		isOpenShop_ = b;
	}

	void CreateNameFontRenderer();
	void CreatePromptSet();
	void CreateDialogueSet();

};

