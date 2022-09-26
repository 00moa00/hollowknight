#include "PreCompile.h"
#include "GrimmGroundDashEffect.h"

GrimmGroundDashEffect::GrimmGroundDashEffect() 
{
}

GrimmGroundDashEffect::~GrimmGroundDashEffect() 
{
}

void GrimmGroundDashEffect::Start()
{
	CreateRendererComponent("Grimm Cln_ground_dash_effect0000-Sheet.png");
	GetRenderer()->CreateFrameAnimationCutTexture("GROUND_DASH_EFFECT", FrameAnimation_DESC("Grimm Cln_ground_dash_effect0000-Sheet.png", 0, 5, 0.080f, false));
	GetRenderer()->ScaleToCutTexture(0);
	GetRenderer()->GetTransform().SetWorldScale(GetTransform().GetWorldScale() * 0.7f);
	//================================
	//    Create Bind Animation
	//================================
	GetRenderer()->AnimationBindEnd("GROUND_DASH_EFFECT", [=](const FrameAnimation_DESC& _Info)
		{
			this->Death();
		});


	GetRenderer()->ChangeFrameAnimation("GROUND_DASH_EFFECT");
}

void GrimmGroundDashEffect::Update(float _DeltaTime)
{
}

