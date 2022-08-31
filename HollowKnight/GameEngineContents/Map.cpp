#include "PreCompile.h"
#include "Map.h"

Map::Map() 
{
}

Map::~Map() 
{
}

void Map::CreateRendererComponent(std::string _FileName)
{
	MapRenderer_ = CreateComponent<MapRenderer>();
	MapRenderer_-> SetTexture(_FileName);
	MapRenderer_-> GetTransform().SetLocalScale(MapRenderer_->GetCurTexture()->GetScale());
}

