#include "PreCompile.h"
#include "GrimmFlameEffect.h"

GrimmFlameEffect::GrimmFlameEffect()
	:
	LightRenderer_(nullptr)
{
}

GrimmFlameEffect::~GrimmFlameEffect() 
{
}

void GrimmFlameEffect::Start()
{
	CreateRendererComponent("grimm_particle_flame.png");
	GetRenderer()->ScaleToCutTexture(0);
	GetRenderer()->GetTransform().SetLocalScale({ 87.f * 1.8f, 82.f * 1.8f });

	GetRenderer()->CreateFrameAnimationCutTexture("ANIMATION", FrameAnimation_DESC("grimm_particle_flame.png", 4, 7, 0.080f, true));

	GetRenderer()->ChangeFrameAnimation("ANIMATION");
	GetRenderer()->GetTransform().SetLocalPosition({ 0, 0, 0 });

	LightRenderer_ = CreateComponent<GameEngineTextureRenderer>();
	LightRenderer_->SetTexture("shop_lamp_bug0001-Sheet.png");
	LightRenderer_->CreateFrameAnimationCutTexture("ANIMATION", FrameAnimation_DESC("Ambient Life_bug_glow0000-Sheet2.png", 0, 5, 0.080f, true));
	LightRenderer_->ChangeFrameAnimation("ANIMATION");
	LightRenderer_->GetTransform().SetWorldScale({
	596.f * 0.8f
	,539.f * 0.8f }
	);

	LightRenderer_->GetClonePipeLine()->SetOutputMergerBlend("AddBlend");
	LightRenderer_->GetPixelData().MulColor.r = 1.0f;
	LightRenderer_->GetPixelData().MulColor.a = 0.8f;
}

void GrimmFlameEffect::Update(float _DeltaTime)
{
	//static float timer = 0; // 0 - 4(sec)
	//timer += _DeltaTime;
	//LightRenderer_->GetPixelData().MulColor.a = fabsf(sinf(3.141592f * timer * 0.4f * 0.4f));
}

