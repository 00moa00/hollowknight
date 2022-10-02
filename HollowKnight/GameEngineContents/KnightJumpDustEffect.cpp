#include "PreCompile.h"
#include "KnightJumpDustEffect.h"

KnightJumpDustEffect::KnightJumpDustEffect() 
{
}

KnightJumpDustEffect::~KnightJumpDustEffect() 
{
}

void KnightJumpDustEffect::Start()
{
	CreateRendererComponent("Dust Effects_jump_puff0001-Sheet.png");

	GetRenderer()->GetTransform().SetLocalScale({ 147.f , 175.f });

	GetRenderer()->CreateFrameAnimationCutTexture("ANIMATION", FrameAnimation_DESC("Dust Effects_jump_puff0001-Sheet.png", 0, 3, 0.090f, false));
	GetRenderer()->CreateFrameAnimationCutTexture("IDLE", FrameAnimation_DESC("Dust Effects_jump_puff0001-Sheet.png", 3, 3, 0.100f, false));

	//GetRenderer()->SetScaleModeImage();

	//SetBlendMode(BlendMode::Add);

	GetRenderer()->AnimationBindEnd("ANIMATION", [=](const FrameAnimation_DESC& _Info)
		{
			Off();
			GetRenderer()->ChangeFrameAnimation("IDLE");
		});

	GetRenderer()->ChangeFrameAnimation("ANIMATION");
	GetRenderer()->GetTransform().SetLocalPosition({ 0, 175.f/2, 0 });

	Off();
}

void KnightJumpDustEffect::Update(float _DeltaTime)
{
}

void KnightJumpDustEffect::EffectOn(float4 _Dir)
{
	if (_Dir.x < 0.f)
	{
		GetRenderer()->GetTransform().SetWorldRotation({ 0,0, 15.f });


		//	GetWallCollision()->GetTransform().SetLocalPosition({ -10, 50 });
	//	GetRenderer()->GetTransform().PixLocalPositiveX();
		//GetRenderer()->GetTransform().SetLocalPosition({ 0, 0, 0 });

	}

	else if (_Dir.x > 0.f)
	{

		GetRenderer()->GetTransform().SetWorldRotation({ 0,0, -8.f });

		//GetWallCollision()->GetTransform().SetLocalPosition({ 10, 50 });
		//GetRenderer()->GetTransform().PixLocalNegativeX();

	}

	else 
	{
		GetRenderer()->GetTransform().SetWorldRotation({ 0,0,0 });

	}
	GetRenderer()->ChangeFrameAnimation("ANIMATION");

	On();
}
