#include "PreCompile.h"
#include "GeoGetEffect.h"
#include <GameEngineBase/GameEngineRandom.h>

GeoGetEffect::GeoGetEffect() 
{
}

GeoGetEffect::~GeoGetEffect() 
{
}

void GeoGetEffect::Start()
{
	CreateRendererComponent("Spell Effects_sharp_flash0000-Sheet.png");

	GetRenderer()->GetTransform().SetLocalScale({ 306.f * 1.2f, 289.f * 0.8f });

	GetRenderer()->CreateFrameAnimationCutTexture("ANIMATION", FrameAnimation_DESC("Spell Effects_sharp_flash0000-Sheet.png", 0, 3, 0.040f, false));
	GetRenderer()->CreateFrameAnimationCutTexture("IDLE", FrameAnimation_DESC("Spell Effects_sharp_flash0000-Sheet.png", 3, 3, 0.100f, false));

	//GetRenderer()->SetScaleModeImage();

	SetBlendMode(BlendMode::Add);

	GetRenderer()->AnimationBindEnd("ANIMATION", [=](const FrameAnimation_DESC& _Info)
		{
			Death();
		});

	GetRenderer()->ChangeFrameAnimation("ANIMATION");
	GetRenderer()->GetTransform().SetLocalPosition({ 0, 10.f, 0 });

	float RamRo = GameEngineRandom::MainRandom.RandomFloat(-30, 30);
	GetRenderer()->GetTransform().SetLocalRotation({ 0, 0, RamRo });



}

void GeoGetEffect::Update(float _DeltaTime)
{
}

