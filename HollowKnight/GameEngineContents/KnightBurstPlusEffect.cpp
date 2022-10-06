#include "PreCompile.h"
#include "KnightBurstPlusEffect.h"

KnightBurstPlusEffect::KnightBurstPlusEffect() 
{
}

KnightBurstPlusEffect::~KnightBurstPlusEffect() 
{
}

void KnightBurstPlusEffect::Start()
{
	CreateRendererComponent("Spell Effects_burst_effect0000-Sheet.png");
	GetRenderer()->CreateFrameAnimationCutTexture("BURST", FrameAnimation_DESC("Spell Effects_burst0000-Sheet.png", 0, 6, 0.050f, false));

	GetRenderer()->CreateFrameAnimationCutTexture("IDLE", FrameAnimation_DESC("Spell Effects_burst0000-Sheet.png", 6, 6, 0.050f, false));

	GetRenderer()->GetTransform().SetWorldScale({ 266 * 3.0f,	257 * 3.0f });
	GetRenderer()->GetTransform().SetLocalPosition({ ((266.f) / 3) + 70.f , -50.f });
	//GetRenderer()->GetPixelData().MulColor.a = 0.5f;
	SetBlendMode(BlendMode::Add);
	//================================
	//    Create Bind Animation
	//================================

	GetRenderer()->AnimationBindEnd("BURST", [=](const FrameAnimation_DESC& _Info)
		{
			Death();
		});


	GetRenderer()->ChangeFrameAnimation("BURST");


}

void KnightBurstPlusEffect::Update(float _DeltaTime)
{
}

void KnightBurstPlusEffect::EffectOn()
{
	GetRenderer()->ChangeFrameAnimation("BURST");
	On();
}
