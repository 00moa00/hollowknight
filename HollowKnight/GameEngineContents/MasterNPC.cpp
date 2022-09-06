#include "PreCompile.h"
#include "MasterNPC.h"

MasterNPC::MasterNPC() 
	:
	isOpenShop_(false)
{
}

MasterNPC::~MasterNPC() 
{
}

void MasterNPC::CreateNameFontRenderer()
{

	//GetRenderer()->Get
	NPCNameFontRenderer_;
	NPCNameFontRenderer_ = GetLevel()->CreateActor<ContentsFontRenderer>();
	NPCNameFontRenderer_->CreateFontRenderer(NPCState_.NPCName_
		, 40
		, { 100, 900, static_cast<float>(Z_ORDER::UI_Border) }
		, false
		, false);

	NPCNameFontRenderer_->SetParent(this);
}

void MasterNPC::CreatePromptSet()
{
	PromptSet_ = GetLevel()->CreateActor<PromptSet>();
	PromptSet_->CreatePrompSet(PromptSetType::TALK);
	PromptSet_->SetParent(this);
}

void MasterNPC::CreateDialogueSet()
{
	DialogueSet_ = GetLevel()->CreateActor<DialogueSet>();
}
