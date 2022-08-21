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
	//GetTransform().SetLocalPosition({-500.f, 0, static_cast<float>(Z_ORDER::UI)});
}

void Charm::Update(float _DeltaTime)
{
}

void Charm::CreateCharm(std::string _Name, std::string _FilePath, float4 Scale)
{
	CreateRendererComponent(Scale, _FilePath);

	GetRenderer()->GetTransform().SetLocalScale({ GetRenderer()->GetCurTexture()->GetScale().x * 0.55f ,  GetRenderer()->GetCurTexture()->GetScale().y * 0.55f , 1});

	CharmName_ = _Name;


}

