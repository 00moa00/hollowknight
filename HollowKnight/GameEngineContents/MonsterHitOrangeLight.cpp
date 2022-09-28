#include "PreCompile.h"
#include "MonsterHitOrangeLight.h"

MonsterHitOrangeLight::MonsterHitOrangeLight() 
	:
	Alpha_(1.0f)
{
}

MonsterHitOrangeLight::~MonsterHitOrangeLight() 
{
}

void MonsterHitOrangeLight::Start()
{
	CreateRendererComponent(float4{ 1, 1, 1 }, "white_light.png");

	//SetBlendMode(BlendMode::Add);
	//GetRenderer()->GetPixelData().MulColor.a = 0.6f;
	GetRenderer()->GetTransform().SetWorldPosition({ 0, 0, static_cast<float>(Z_ORDER::Effect)});
	//GetRenderer()->SetPivot(PIVOTMODE::BOT);
	SetMulColor({1.0f, 0.3f, 0.0f, 1.0f});
	//SetPlusColor({ 1.0f, 0.3f, 0.0f, 1.0f });

//	SetPlusColor(GetLevel<HollowKnightLevel>()->GetEffectGUIActor()->GetMainLightPlusColor());
}

void MonsterHitOrangeLight::Update(float _DeltaTime)
{
	Alpha_ -= 0.8f * _DeltaTime;
	GetRenderer()->GetPixelData().MulColor.a = Alpha_;
	//GetRenderer()->GetPixelData().PlusColor.a = Alpha_;

	if (Alpha_ <= 0.f)
	{
		Alpha_ = 0.f;
		Death();
	}
}

