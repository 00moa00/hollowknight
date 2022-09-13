#include "PreCompile.h"
#include "KnightStunEffect.h"

KnightStunEffect::KnightStunEffect() 
{
}

KnightStunEffect::~KnightStunEffect() 
{
}

void KnightStunEffect::Start()
{
	CreateRendererComponent( "hit_crack_simple0000-Sheet.png");
	GetRenderer()->GetTransform().SetWorldPosition({ 0, 0, 0 });
	GetRenderer()->SetScaleModeImage();
	GetRenderer()->GetTransform().SetWorldPosition({ 0, 80,  0 });


	GetRenderer()->CreateFrameAnimationCutTexture("STUN_ANIMATION", FrameAnimation_DESC("hit_crack_simple0000-Sheet.png", 0, 2, 0.070f, false));
	GetRenderer()->CreateFrameAnimationCutTexture("STUN_IDLE_ANIMATION", FrameAnimation_DESC("hit_crack_simple0000-Sheet.png", 2, 2, 0.070f, false));

	//================================
	//    Create Bind Animation
	//================================

	//GetRenderer()->AnimationBindEnd("STUN_ANIMATION", [=](const FrameAnimation_DESC& _Info)
	//	{
	//		this->Off();
	//	});

	GetRenderer()->ChangeFrameAnimation("STUN_ANIMATION");

}

void KnightStunEffect::Update(float _DeltaTime)
{
}

void KnightStunEffect::StunEffectOn()
{
	this->On();
	GetRenderer()->ChangeFrameAnimation("STUN_ANIMATION");

}

void KnightStunEffect::StunEffectOff()
{
	GetRenderer()->ChangeFrameAnimation("STUN_IDLE_ANIMATION");
	this->Off();
}

