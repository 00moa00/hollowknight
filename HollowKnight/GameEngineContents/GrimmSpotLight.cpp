#include "PreCompile.h"
#include "GrimmSpotLight.h"
#include "GlobalContentsValue.h"

GrimmSpotLight::GrimmSpotLight() 
{
}

GrimmSpotLight::~GrimmSpotLight() 
{
}

void GrimmSpotLight::Start()
{
	CreateRendererComponent("grimm_spotlight.png");
	//..GetRenderer()->GetPixelData
	SetBlendMode(BlendMode::Lighten);
	//GetTransform().P

}

void GrimmSpotLight::Update(float _DeltaTime)
{
}

