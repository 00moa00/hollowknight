#include "PreCompile.h"
#include "KnightSlashAttackEffect.h"

KnightSlashAttackEffect::KnightSlashAttackEffect() 
{
}

KnightSlashAttackEffect::~KnightSlashAttackEffect() 
{
}

void KnightSlashAttackEffect::Start()
{
	CreateRendererComponent("Spell Effects_sharp_flash0000-Sheet.png");

	GetRenderer()->GetTransform().SetLocalScale({ 306.f * 2.0f, 289.f * 2.0f });

	GetRenderer()->CreateFrameAnimationCutTexture("ANIMATION", FrameAnimation_DESC("Spell Effects_sharp_flash0000-Sheet.png", 0, 3, 0.080f, false));
	GetRenderer()->CreateFrameAnimationCutTexture("IDLE", FrameAnimation_DESC("Spell Effects_sharp_flash0000-Sheet.png", 3, 3, 0.100f, false));

	//GetRenderer()->SetScaleModeImage();

	SetBlendMode(BlendMode::Add);

	GetRenderer()->AnimationBindEnd("ANIMATION", [=](const FrameAnimation_DESC& _Info)
		{
			Off();
			GetRenderer()->ChangeFrameAnimation("IDLE");
		});

	GetRenderer()->ChangeFrameAnimation("ANIMATION");
	//GetRenderer()->GetTransform().SetLocalPosition({ 0, 0, 0 });
	//GetRenderer()->SetPivot(PIVOTMODE::BOT);

	Off();
}

void KnightSlashAttackEffect::Update(float _DeltaTime)
{
}

void KnightSlashAttackEffect::EffectOn()
{
	GetRenderer()->ChangeFrameAnimation("ANIMATION");

	On();
}
