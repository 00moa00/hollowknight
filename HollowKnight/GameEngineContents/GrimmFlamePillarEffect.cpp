#include "PreCompile.h"
#include "GrimmFlamePillarEffect.h"

GrimmFlamePillarEffect::GrimmFlamePillarEffect() 
{
}

GrimmFlamePillarEffect::~GrimmFlamePillarEffect() 
{
}

void GrimmFlamePillarEffect::Start()
{
	CreateRendererComponent("Grimm Cln_Flame_Pillar_flash0000-Sheet.png");
	GetRenderer()->CreateFrameAnimationCutTexture("FLASH_EFFECT", FrameAnimation_DESC("Grimm Cln_Flame_Pillar_flash0000-Sheet.png", 0, 5, 0.050f, false));
	GetRenderer()->ScaleToCutTexture(0);
	//GetRenderer()->GetTransform().SetWorldScale(GetTransform().GetWorldScale() * 0.7f);
	//================================
	//    Create Bind Animation
	//================================
	GetRenderer()->AnimationBindEnd("FLASH_EFFECT", [=](const FrameAnimation_DESC& _Info)
		{
			this->Death();
		});


	GetRenderer()->ChangeFrameAnimation("FLASH_EFFECT");
}

void GrimmFlamePillarEffect::Update(float _DeltaTime)
{
}

