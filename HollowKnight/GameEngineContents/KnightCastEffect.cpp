#include "PreCompile.h"
#include "KnightCastEffect.h"

KnightCastEffect::KnightCastEffect() 
	:
	Dir_(float4::ZERO)
{
}

KnightCastEffect::~KnightCastEffect() 
{
}

void KnightCastEffect::Start()
{
	CreateRendererComponent("Spell Effects_blast_effect_v020000-Sheet.png");

	GetRenderer()->GetTransform().SetLocalScale({ 306.f * 2.0f, 289.f * 2.0f });

	GetRenderer()->CreateFrameAnimationCutTexture("ANIMATION", FrameAnimation_DESC("Spell Effects_blast_effect_v020000-Sheet.png", 0, 7, 0.080f, false));
	GetRenderer()->CreateFrameAnimationCutTexture("IDLE", FrameAnimation_DESC("Spell Effects_blast_effect_v020000-Sheet.png", 7, 7, 0.100f, false));

	//GetRenderer()->SetScaleModeImage();

	SetBlendMode(BlendMode::Add);

	GetRenderer()->AnimationBindEnd("ANIMATION", [=](const FrameAnimation_DESC& _Info)
		{
			Off();
			GetRenderer()->ChangeFrameAnimation("IDLE");
		});

	GetRenderer()->ChangeFrameAnimation("ANIMATION");
	GetRenderer()->GetTransform().SetLocalPosition({ 0, 0, 0 });

	Off();
}

void KnightCastEffect::Update(float _DeltaTime)
{
}

void KnightCastEffect::EffectOn(float4 _Dir)
{
	Dir_ = _Dir;
	if (_Dir.x <= 0.f)
	{
		//	GetWallCollision()->GetTransform().SetLocalPosition({ -10, 50 });
		GetRenderer()->GetTransform().PixLocalPositiveX();
		//GetRenderer()->GetTransform().SetLocalPosition({ 0, 0, 0 });

	}

	if (_Dir.x >= 0.f)
	{
		//GetWallCollision()->GetTransform().SetLocalPosition({ 10, 50 });
		GetRenderer()->GetTransform().PixLocalNegativeX();

	}
	GetRenderer()->ChangeFrameAnimation("ANIMATION");

	On();
}
