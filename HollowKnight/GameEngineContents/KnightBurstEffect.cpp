#include "PreCompile.h"
#include "KnightBurstEffect.h"

KnightBurstEffect::KnightBurstEffect() 
{
}

KnightBurstEffect::~KnightBurstEffect() 
{
}

void KnightBurstEffect::Start()
{
	CreateRendererComponent("Spell Effects_burst_effect0000-Sheet.png");

	GetRenderer()->CreateFrameAnimationCutTexture("BURST", FrameAnimation_DESC("Spell Effects_burst_effect0000-Sheet.png", 0, 1, 0.100f, false));

	//================================
	//    Create Bind Animation
	//================================

	GetRenderer()->AnimationBindEnd("BURST", [=](const FrameAnimation_DESC& _Info)
		{
			this->Death();
		});

	GetRenderer()->ChangeFrameAnimation("BURST");

	//GetRenderer()->GetTransform().SetWorldPosition({ 0, 0, 0 });
	//GetRenderer()->GetTransform().SetWorldScale({ 699 * 1.3f,140 * 1.3f });
	//GetRenderer()->GetTransform().SetWorldPosition({ 0, 80,  0 });
}

void KnightBurstEffect::Update(float _DeltaTime)
{
}

