#include "PreCompile.h"
#include "KnightDoubleJumpEffect.h"

KnightDoubleJumpEffect::KnightDoubleJumpEffect() 
{
}

KnightDoubleJumpEffect::~KnightDoubleJumpEffect() 
{
}

void KnightDoubleJumpEffect::Start()
{
	CreateRendererComponent("Spell Effects 2_double_jump_wings0000-Sheet.png");

	GetRenderer()->CreateFrameAnimationCutTexture("ANIMAION", FrameAnimation_DESC("Spell Effects 2_double_jump_wings0000-Sheet.png", 0, 5, 0.100f, false));
	GetRenderer()->CreateFrameAnimationCutTexture("IDLE_ANIMAION", FrameAnimation_DESC("Spell Effects 2_double_jump_wings0000-Sheet.png", 5, 5, 0.080f, false));

	GetRenderer()->SetScaleModeImage();
	SetBlendMode(BlendMode::Add);

	GetRenderer()->GetTransform().SetLocalPosition({0,356.f/4,static_cast<float>(Z_ORDER::Back_Effect)});

	//================================
	//    Create Bind Animation
	//================================

	GetRenderer()->AnimationBindEnd("ANIMAION", [=](const FrameAnimation_DESC& _Info)
		{
			GetRenderer()->ChangeFrameAnimation("IDLE_ANIMAION");
			this->Off();
		});

	GetRenderer()->ChangeFrameAnimation("ANIMAION");
}

void KnightDoubleJumpEffect::Update(float _DeltaTime)
{
}

void KnightDoubleJumpEffect::SetEffectOn()
{
	GetRenderer()->ChangeFrameAnimation("ANIMAION");

	this->On();
}

