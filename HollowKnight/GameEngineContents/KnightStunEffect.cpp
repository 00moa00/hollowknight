#include "PreCompile.h"
#include "KnightStunEffect.h"

KnightStunEffect::KnightStunEffect() 
	:
	AddScaleX_(0)
{
}

KnightStunEffect::~KnightStunEffect() 
{
}

void KnightStunEffect::Start()
{
	CreateRendererComponent( "hit_crack_simple0000-Sheet.png");
	GetRenderer()->GetTransform().SetWorldPosition({ 0, 0, 0 });
	GetRenderer()->GetTransform().SetWorldScale({699 * 1.3f,140 * 1.3f });
	GetRenderer()->GetTransform().SetWorldPosition({ 0, 80,  0 });


	std::vector<unsigned int> CustomFrame;

	CustomFrame.push_back(0);
	CustomFrame.push_back(0);
	CustomFrame.push_back(0);
	CustomFrame.push_back(0);
	CustomFrame.push_back(1);
	CustomFrame.push_back(2);

	GetRenderer()->CreateFrameAnimationCutTexture("STUN_ANIMATION", FrameAnimation_DESC("hit_crack_simple0000-Sheet.png", CustomFrame, 0.010f, false));
	GetRenderer()->CreateFrameAnimationCutTexture("STUN_IDLE_ANIMATION", FrameAnimation_DESC("hit_crack_simple0000-Sheet.png", 2, 2, 0.042f, false));
	PrevScale_ = GetRenderer()->GetTransform().GetWorldScale();
	
	
	


	
	
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
	AddScaleX_ += (200.f * _DeltaTime);
	GetRenderer()->GetTransform().SetWorldScale({ GetRenderer()->GetTransform().GetWorldScale().x + AddScaleX_, GetRenderer()->GetTransform().GetWorldScale().y, 1 });
}

void KnightStunEffect::StunEffectOn()
{
	this->On();
	GetRenderer()->ChangeFrameAnimation("STUN_ANIMATION");

}

void KnightStunEffect::StunEffectOff()
{
	AddScaleX_ = 0;
	GetRenderer()->GetTransform().SetWorldScale(PrevScale_);



	GetRenderer()->ChangeFrameAnimation("STUN_IDLE_ANIMATION");
	this->Off();


}

