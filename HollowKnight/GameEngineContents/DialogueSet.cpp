#include "PreCompile.h"
#include "DialogueSet.h"

DialogueSet::DialogueSet() 
	:

	isDialougueFull_(false),

	CurrentDialoguePage_(0),

	DialogueTop_(nullptr),
	DialogueBottom_(nullptr),
	DialogueBack_(nullptr),
	NextArrow_(nullptr)
{
}

DialogueSet::~DialogueSet() 
{
}

void DialogueSet::Start()
{
	DialogueBack_ = CreateComponent<GameEngineUIRenderer>();
	DialogueBack_->SetTexture("Dialoguebackboard.png");
	DialogueBack_->GetTransform().SetLocalScale({1000, 400});
	DialogueBack_->GetPixelData().MulColor.a = 0.5f;
	DialogueBack_->GetTransform().SetLocalPosition({ 0, 200 });

	DialogueTop_ = CreateComponent<GameEngineUIRenderer>();
	DialogueTop_->SetTexture("Dialogue Cln_dialogue_fleur_top0000-Sheet.png");
	DialogueTop_->GetTransform().SetLocalScale(DialogueTop_->GetCurTexture()->GetScale());
	DialogueTop_->SetScaleModeImage();

	DialogueTop_->CreateFrameAnimationCutTexture("TOP_APPEAR_ANIMATION", FrameAnimation_DESC("Dialogue Cln_dialogue_fleur_top0000-Sheet.png", 0, 7, 0.050f, false));
	DialogueTop_->CreateFrameAnimationCutTexture("TOP_IDLE_ANIMATION", FrameAnimation_DESC("Dialogue Cln_dialogue_fleur_top0000-Sheet.png", 7, 7, 0.050f, false));
	DialogueTop_->ChangeFrameAnimation("TOP_IDLE_ANIMATION");

	DialogueTop_->AnimationBindEnd("TOP_APPEAR_ANIMATION", [=](const FrameAnimation_DESC& _Info)
		{
			DialogueTop_->ChangeFrameAnimation("TOP_IDLE_ANIMATION");

		});

	DialogueTop_->GetTransform().SetLocalPosition({0, 400});

	DialogueBottom_ = CreateComponent<GameEngineUIRenderer>();
	DialogueBottom_->SetTexture("Dialogue Cln_dialogue_fleur_bottom0000-Sheet.png");
	DialogueBottom_->GetTransform().SetLocalScale(DialogueBottom_->GetCurTexture()->GetScale());
	DialogueBottom_->SetScaleModeImage();

	DialogueBottom_->CreateFrameAnimationCutTexture("BOTTOM_APPEAR_ANIMATION", FrameAnimation_DESC("Dialogue Cln_dialogue_fleur_bottom0000-Sheet.png", 0, 7, 0.100f, false));
	DialogueBottom_->CreateFrameAnimationCutTexture("BOTTOM_IDLE_ANIMATION", FrameAnimation_DESC("Dialogue Cln_dialogue_fleur_bottom0000-Sheet.png", 7, 7, 0.100f, false));
	DialogueBottom_->ChangeFrameAnimation("BOTTOM_IDLE_ANIMATION");

	DialogueBottom_->AnimationBindEnd("BOTTOM_APPEAR_ANIMATION", [=](const FrameAnimation_DESC& _Info)
		{
			DialogueBottom_->ChangeFrameAnimation("BOTTOM_IDLE_ANIMATION");

		});

	NextArrow_ = CreateComponent<GameEngineUIRenderer>();
	NextArrow_->SetTexture("Dialogue Cln_arrow_down0000-Sheet.png");
	NextArrow_->GetTransform().SetLocalScale(NextArrow_->GetCurTexture()->GetCutScale(0));

	NextArrow_->CreateFrameAnimationCutTexture("ARROW_NEXT_ANIMATION", FrameAnimation_DESC("Dialogue Cln_arrow_down0000-Sheet.png", 0, 5, 0.050f));
	NextArrow_->CreateFrameAnimationCutTexture("ARROW_FULL_ANIMATION", FrameAnimation_DESC("Dialogue Cln_fullstop0000-Sheet.png", 0, 3, 0.050f));
	NextArrow_->ChangeFrameAnimation("ARROW_NEXT_ANIMATION");


}

void DialogueSet::Update(float _DeltaTime)
{
}

