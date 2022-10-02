#include "PreCompile.h"
#include "KnightDashEffect.h"

KnightDashEffect::KnightDashEffect() 
{
}

KnightDashEffect::~KnightDashEffect() 
{
}

void KnightDashEffect::Start()
{
	CreateRendererComponent("Knight_dash_effect0000-Sheet.png");

	GetRenderer()->GetTransform().SetLocalScale({ 401.f * 1.2f , 217.f });

	GetRenderer()->CreateFrameAnimationCutTexture("ANIMATION", FrameAnimation_DESC("Knight_dash_effect0000-Sheet.png", 0, 7, 0.050f, false));
	GetRenderer()->CreateFrameAnimationCutTexture("IDLE", FrameAnimation_DESC("Knight_dash_effect0000-Sheet.png", 7, 7, 0.010f, false));

	//GetRenderer()->SetScaleModeImage();

	//SetBlendMode(BlendMode::Add);

	GetRenderer()->AnimationBindEnd("ANIMATION", [=](const FrameAnimation_DESC& _Info)
		{
			Off();
			GetRenderer()->ChangeFrameAnimation("IDLE");
		});

	GetRenderer()->ChangeFrameAnimation("ANIMATION");
	//GetRenderer()->GetTransform().SetLocalPosition({ 0, 175.f / 2, 0 });

	Off();
}

void KnightDashEffect::Update(float _DeltaTime)
{
}

void KnightDashEffect::EffectOn(float4 _Dir)
{
	if (_Dir.x < 0.f)
	{
		GetRenderer()->GetTransform().SetLocalPosition({ 250.f, 50.f, 0 });
		GetRenderer()->GetTransform().PixLocalNegativeX();

	}

	else if (_Dir.x > 0.f)
	{
		GetRenderer()->GetTransform().SetLocalPosition({ -250.f, 50.f, 0 });
		GetRenderer()->GetTransform().PixLocalPositiveX();

	}



	GetRenderer()->ChangeFrameAnimation("ANIMATION");

	On();
}
