#include "PreCompile.h"
#include "KnightCastImpactEffect.h"

KnightCastImpactEffect::KnightCastImpactEffect() 
{
}

KnightCastImpactEffect::~KnightCastImpactEffect() 
{
}

void KnightCastImpactEffect::Start()
{
	CreateRendererComponent(float4{ 349, 186, 1 }, "Spell Effects_fireball_wall_impact_effect0000-Sheet.png");
	//GetRenderer()->SetScaleModeImage();
	GetRenderer()->GetTransform().SetLocalScale({ 259.f * 3.0f, 204.f * 3.0f });

	SetBlendMode(BlendMode::Add);

	GetRenderer()->CreateFrameAnimationCutTexture("ANIMATION", FrameAnimation_DESC("Spell Effects_fireball_wall_impact_effect0000-Sheet.png", 0, 6, 0.070f, false));
	GetRenderer()->ChangeFrameAnimation("ANIMATION");

	GetRenderer()->AnimationBindEnd("ANIMATION", [=](const FrameAnimation_DESC& _Info)
		{
			this->Death();
		});

}

void KnightCastImpactEffect::Update(float _DeltaTime)
{
	int a = 0;
}

