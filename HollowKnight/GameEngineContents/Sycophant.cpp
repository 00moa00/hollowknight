#include "PreCompile.h"
#include "Sycophant.h"

Sycophant::Sycophant() 
{
}

Sycophant::~Sycophant() 
{
}

void Sycophant::Start()
{
	SetNPCName(" ");
	SetNPCType(NPC_TYPE::Normal);

	GetTransform().SetWorldPosition({ 5602.f, -936.f, static_cast<int>(Z_ORDER::NPC) });
	CreateNameFontRenderer();
	CreatePromptSet();
	GetPromptSet()->GetTransform().SetLocalPosition({0, 200.f});
	//GetPromptSet()->GetCollision()->GetTransform().SetWorldPosition(GetTransform().GetWorldPosition());
	//GetPromptSet()->SetParent(this);

	CreateRendererComponent("grimm_sycophant.png");

	CreateCollisionComponent(float4{ 600, 120, 1 }, static_cast<int>(COLLISION_ORDER::NPC));

	CreateDialogueSet();
	//GetDialogueSet()->SetParent(this);
	GetDialogueSet()->PushDialogue("큰 벌레의 시체.");


	GetDialogueSet()->SetDialogueOff();
}

void Sycophant::Update(float _DeltaTime)
{
}

bool Sycophant::ThisVSKnightCollision(GameEngineCollision* _This, GameEngineCollision* _Other)
{
	return false;
}
