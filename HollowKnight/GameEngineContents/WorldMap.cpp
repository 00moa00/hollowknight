#include "PreCompile.h"
#include "WorldMap.h"

WorldMap::WorldMap() 
{
}

WorldMap::~WorldMap() 
{
}

void WorldMap::Start()
{

}

void WorldMap::Update(float _Deltatime)
{
}

void WorldMap::CreateWorldMapRenderer(std::string _FilePath, MAP_LIST _MapType)
{
	MapType_ = _MapType;

	CreateRendererComponent(_FilePath);
}