#include "PreCompile.h"
#include "GrimmAirDashEffect.h"

GrimmAirDashEffect::GrimmAirDashEffect() 
{
}

GrimmAirDashEffect::~GrimmAirDashEffect() 
{
}

void GrimmAirDashEffect::Start()
{
	CreateRendererComponent("Grimm Cln_air_dash_effects0000-Sheet.png");

	std::vector<unsigned int> BackAni;

	BackAni.push_back(4);
	BackAni.push_back(3);
	BackAni.push_back(2);
	BackAni.push_back(1);
	BackAni.push_back(0);

	GetRenderer()->CreateFrameAnimationCutTexture("AIR_DASH_EFFECT", FrameAnimation_DESC("Grimm Cln_air_dash_effects0000-Sheet.png", BackAni, 0.080f, false));

	//================================
	//    Create Bind Animation
	//================================
	GetRenderer()->AnimationBindEnd("AIR_DASH_EFFECT", [=](const FrameAnimation_DESC& _Info)
		{
			this->Death();
		});
	GetRenderer()->GetTransform().SetWorldPosition({ -GetRenderer()->GetCurTexture()->GetScale().x / 2, GetRenderer()->GetCurTexture()->GetScale().y / 2 });


	GetRenderer()->ChangeFrameAnimation("AIR_DASH_EFFECT");
}

void GrimmAirDashEffect::Update(float _DeltaTime)
{
}

