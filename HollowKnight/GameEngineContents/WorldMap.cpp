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

	GetRenderer()->GetPixelData().MulColor.r = 0.5f;
	GetRenderer()->GetPixelData().MulColor.g = 0.5f;
	GetRenderer()->GetPixelData().MulColor.b = 0.5f;
}

void WorldMap::ChangeTextureIdle()
{
	GetRenderer()->GetPixelData().MulColor.r = 0.5f;
	GetRenderer()->GetPixelData().MulColor.g = 0.5f;
	GetRenderer()->GetPixelData().MulColor.b = 0.5f;
}

void WorldMap::ChangeTextureSelect()
{

	GetRenderer()->GetPixelData().MulColor.r = 1.0f;
	GetRenderer()->GetPixelData().MulColor.g = 1.0f;
	GetRenderer()->GetPixelData().MulColor.b = 1.0f;

}
