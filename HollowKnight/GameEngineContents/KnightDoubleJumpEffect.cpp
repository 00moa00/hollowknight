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

	GetRenderer()->CreateFrameAnimationCutTexture("FOCUS_APPEAR", FrameAnimation_DESC("Spell Effects 2_double_jump_wings0000-Sheet.png", 0, 5, 0.100f, false));

	//================================
	//    Create Bind Animation
	//================================

	GetRenderer()->AnimationBindEnd("FOCUS_APPEAR", [=](const FrameAnimation_DESC& _Info)
		{
			GetRenderer()->ChangeFrameAnimation("FOCUS");
		});

	GetRenderer()->ChangeFrameAnimation("FOCUS_APPEAR");
}

void KnightDoubleJumpEffect::Update(float _DeltaTime)
{
}

