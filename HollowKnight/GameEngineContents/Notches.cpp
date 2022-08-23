#include "PreCompile.h"
#include "Notches.h"

Notches::Notches() 
	:
	isNotchesUsed_(false)
{
}

Notches::~Notches() 
{
}

void Notches::Start()
{
	CreateRendererComponent({28,28,1},"charm_UI__0001_charm_cost_02_unlit.png");
}

void Notches::Update(float _DeltaTime)
{
}

