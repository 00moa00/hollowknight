#include "PreCompile.h"
#include "GrimmLantern.h"

#include "GrimmFlameEffect.h"

GrimmLantern::GrimmLantern() 
{
}

GrimmLantern::~GrimmLantern() 
{
}

void GrimmLantern::Start()
{

	GrimmFlameEffect* GrimmFlameEffect_ = GetLevel()->CreateActor<GrimmFlameEffect>();
	GrimmFlameEffect_->SetParent(this);
	GrimmFlameEffect_->GetTransform().SetLocalPosition({ -10.f, -140.f });

	CreateRendererComponent({ 111, 538, 1 }, "Grimm_tent_ext_0007_6.png");
	GetRenderer()->GetTransform().SetLocalRotation({0,0,-180});


}

void GrimmLantern::Update(float _DeltaTime)
{
}

