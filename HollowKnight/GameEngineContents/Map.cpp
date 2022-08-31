#include "PreCompile.h"
#include "Map.h"

Map::Map() 
{
}

Map::~Map() 
{
}

void Map::CreateRendererComponent(float4 _LocalScale, std::string _FileName)
{
	MapRenderer_ = CreateComponent<MapRenderer>();
	MapRenderer_-> SetTexture(_FileName);
	MapRenderer_-> GetTransform().SetLocalScale(MapRenderer_->GetCurTexture()->GetScale());
}

