#include "PreCompile.h"
#include "BossGateEffect.h"

BossGateEffect::BossGateEffect() 
{
}

BossGateEffect::~BossGateEffect() 
{
}

void BossGateEffect::Start()
{
	CreateRendererComponent("Switches and gates_gate_effect0000-Sheet.png");

	GetRenderer()->CreateFrameAnimationCutTexture("DOOR_EFFECT_ANIMATION", FrameAnimation_DESC("Switches and gates_gate_effect0000-Sheet.png", 0, 3, 0.100f, false));


	GetRenderer()->ScaleToCutTexture(0);
	GetRenderer()->ChangeFrameAnimation("DOOR_EFFECT_ANIMATION");

	GetRenderer()->AnimationBindEnd("DOOR_EFFECT_ANIMATION", [=](const FrameAnimation_DESC& _Info)
		{
			this->Death();
		});


}

void BossGateEffect::Update(float _DeltaTime)
{
}

