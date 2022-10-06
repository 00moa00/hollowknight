#include "PreCompile.h"
#include "KnightInvincibilityEffect.h"

KnightInvincibilityEffect::KnightInvincibilityEffect() 
{
}

KnightInvincibilityEffect::~KnightInvincibilityEffect() 
{
}

void KnightInvincibilityEffect::Start()
{
	CreateRendererComponent("Spell Effects_burst_effect0000-Sheet.png");
	GetRenderer()->CreateFrameAnimationCutTexture("BURST", FrameAnimation_DESC("Spell Effects_burst0000-Sheet.png", 0, 6, 0.050f, false));

	{
		std::vector<unsigned int>BackAni;

		for (int i = 6; i > -1; --i)
		{
			BackAni.push_back(i);
		}

		GetRenderer()->CreateFrameAnimationCutTexture("BACK_BURST", FrameAnimation_DESC("Spell Effects_burst0000-Sheet.png", BackAni, 0.050f, false));
	}
	GetRenderer()->CreateFrameAnimationCutTexture("IDLE", FrameAnimation_DESC("Spell Effects_burst0000-Sheet.png", 6, 6, 0.050f, false));

	GetRenderer()->GetTransform().SetWorldScale({ 266 * 2.0f,	257 * 2.0f });
	GetRenderer()->GetTransform().SetLocalPosition({ ((266.f )/2) -  25.f, -50.f});
	GetRenderer()->GetPixelData().MulColor.a = 0.5f;
	SetBlendMode(BlendMode::Add);
	//================================
	//    Create Bind Animation
	//================================

	GetRenderer()->AnimationBindEnd("BURST", [=](const FrameAnimation_DESC& _Info)
		{
			GetRenderer()->ChangeFrameAnimation("BACK_BURST");		
		});

	GetRenderer()->AnimationBindEnd("BACK_BURST", [=](const FrameAnimation_DESC& _Info)
		{
			GetRenderer()->ChangeFrameAnimation("BURST");
		});

	GetRenderer()->ChangeFrameAnimation("IDLE");

	Off();
}

void KnightInvincibilityEffect::Update(float _DeltaTime)
{
}

void KnightInvincibilityEffect::EffectOn()
{
	GetRenderer()->ChangeFrameAnimation("BURST");
	On();

}

void KnightInvincibilityEffect::EffectOff()
{
	GetRenderer()->ChangeFrameAnimation("IDLE");
	Off();

}

