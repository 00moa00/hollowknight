#include "PreCompile.h"
#include "MasterNPC.h"
#include "KnightData.h"

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

void MasterNPC::CheckDirToKnight()
{
	float4 KnightPos = KnightData::GetInst()->GetKnightPosition();
	float4 DirPos = KnightPos - this->GetTransform().GetWorldPosition();
	DirPos.Normalize();

	SetMoveDirection(DirPos);

	if (DirPos.CompareInt2D(float4::RIGHT))
	{
		GetRenderer()->GetTransform().PixLocalNegativeX();
	}

	else if (DirPos.CompareInt2D(float4::LEFT))
	{
		GetRenderer()->GetTransform().PixLocalPositiveX();
	}

}
