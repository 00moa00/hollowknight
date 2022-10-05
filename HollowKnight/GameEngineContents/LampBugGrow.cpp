#include "PreCompile.h"
#include "LampBugGrow.h"

LampBugGrow::LampBugGrow() 
{
}

LampBugGrow::~LampBugGrow() 
{
}

void LampBugGrow::Start()
{
	CreateRendererComponent("elev_lamp_glow.png");
	GetRenderer()->GetTransform().SetLocalScale({400.f, 400.f});

	GetRenderer()->GetPixelData().MulColor.a = 0.6f;

}

void LampBugGrow::Update(float _DeltaTime)
{
}

