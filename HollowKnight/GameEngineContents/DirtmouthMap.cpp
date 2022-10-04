#include "PreCompile.h"
#include "DirtmouthMap.h"

DirtmouthMap::DirtmouthMap() 
{
}

DirtmouthMap::~DirtmouthMap() 
{
}

void DirtmouthMap::Start()
{
	DirtmouthMap_.insert({ 0, GetLevel()->CreateActor<Map>() });

	DirtmouthMap_[0]->CreateRendererComponent("Town_b.png");
	DirtmouthMap_[0]->GetTransform().SetWorldPosition({-299, 320});
	DirtmouthMap_[0]->SetParent(this);

	DirtmouthMap_.insert({ 1, GetLevel()->CreateActor<Map>() });

	DirtmouthMap_[1]->CreateRendererComponent("Tutorial_01.png");
	DirtmouthMap_[1]->GetTransform().SetWorldPosition({ -651, 285 });
	DirtmouthMap_[1]->SetParent(this);

	this->Off();

}

void DirtmouthMap::Update(float _DeltaTime)
{
}
