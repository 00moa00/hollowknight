#include "PreCompile.h"
#include "Charm.h"

Charm::Charm() 
{
}

Charm::~Charm() 
{
}

void Charm::Start()
{
}

void Charm::Update(float _DeltaTime)
{
}

void Charm::CreateCharm(std::string _Name, std::string _FilePath, float4 Scale)
{
	CreateRendererComponent(Scale, _FilePath);
	CharmName_ = _Name;


}

