#include "PreCompile.h"
#include "GrimmBeam.h"

GrimmBeam::GrimmBeam() 
{
}

GrimmBeam::~GrimmBeam() 
{
}

void GrimmBeam::Start()
{
	CreateRendererComponent("grimm_tent_beam.png");
	GetRenderer()->GetTransform().SetLocalScale({ 280, 1200 });

	//GetRenderer()->GetPixelData().MulColor = { 1,1,1,0.3f };
	SetBlendMode(BlendMode::Lighten);

	//GetRenderer()->GetTransform().SetWorldPosition({ 0, 186 / 2, 0 });
}

void GrimmBeam::Update(float _DeltaTime)
{
}

