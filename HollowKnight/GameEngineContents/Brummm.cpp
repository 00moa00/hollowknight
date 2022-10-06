#include "PreCompile.h"
#include "Brummm.h"

Brummm::Brummm() 
{
}

Brummm::~Brummm() 
{
}

void Brummm::Start()
{
	SetNPCName(" ");
	SetNPCType(NPC_TYPE::Normal);

	GetTransform().SetWorldPosition({ 2060.f, -960.f, static_cast<int>(Z_ORDER::NPC) });
	CreateNameFontRenderer();
	CreatePromptSet();
	GetPromptSet()->GetTransform().SetLocalPosition({ 0, 400 });
	GetPromptSet()->GetCollision()->GetTransform().SetLocalPosition({0, -300});
	//GetPromptSet()->SetParent(this);

	CreateRendererComponent("Brum Cln_grimmkin_accordian0000-Sheet.png");
	GetRenderer()->CreateFrameAnimationCutTexture("IDLE_ANIMATION", FrameAnimation_DESC("Brum Cln_grimmkin_accordian0000-Sheet.png", 0, 10, 0.100f));
	GetRenderer()->ChangeFrameAnimation("IDLE_ANIMATION");
	GetRenderer()->SetScaleModeImage();


	CreateCollisionComponent(float4{ 600, 120, 1 }, static_cast<int>(COLLISION_ORDER::NPC));

	CreateDialogueSet();
	//GetDialogueSet()->SetParent(this);
	GetDialogueSet()->PushDialogue("À¸À½.¿ì¸®¸¦ ºÒ·¶³ª?");
	GetDialogueSet()->PushDialogue("´ÜÀå´Ô°ú ¾ê±âÇØ¶ó.");


	GetDialogueSet()->SetDialogueOff();
}

void Brummm::Update(float _DeltaTime)
{
}

void Brummm::StartTalking()
{
	int RamSound = GameEngineRandom::MainRandom.RandomInt(0, 2);

	if (RamSound == 0)
	{
		GameEngineSound::SoundPlayOneShot("Brumm_talk_01.ogg");
	}
	else if (RamSound == 1)
	{
		GameEngineSound::SoundPlayOneShot("Brumm_talk_02.ogg");

	}
	else if (RamSound == 2)
	{
		GameEngineSound::SoundPlayOneShot("Brumm_talk_03.ogg");
	}

}

bool Brummm::ThisVSKnightCollision(GameEngineCollision* _This, GameEngineCollision* _Other)
{
    return false;
}
