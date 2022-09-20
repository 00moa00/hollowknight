#include "PreCompile.h"
#include "GrimmCrowd.h"

GrimmCrowd::GrimmCrowd() 
	:
	CrowdRenderer(nullptr)
{
}

GrimmCrowd::~GrimmCrowd() 
{
}

void GrimmCrowd::Start()
{
	CrowdRenderer = CreateComponent<GameEngineTextureRenderer>();
	CrowdRenderer->SetTexture("Grimm_crowd0000-Sheet.png");
	CrowdRenderer->GetTransform().SetLocalScale(CrowdRenderer->GetCurTexture()->GetScale());
	CrowdRenderer->CreateFrameAnimationCutTexture("CROWD_ANIMATION", FrameAnimation_DESC("Grimm_crowd0000-Sheet.png", 0, 7, 0.050f, true));
	CrowdRenderer->ChangeFrameAnimation("CROWD_ANIMATION");
	CrowdRenderer->SetScaleModeImage();
	//CrowdRenderer->SetPivot(PIVOTMODE::BOT)
}

void GrimmCrowd::Update(float _DeltaTime)
{
}

void GrimmCrowd::SetScaleNegativeX()
{
	CrowdRenderer->GetTransform().PixLocalNegativeX();
}

