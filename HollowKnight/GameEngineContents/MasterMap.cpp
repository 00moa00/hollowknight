#include "PreCompile.h"
#include "MasterMap.h"
#include "GlobalContentsValue.h"

MasterMap::MasterMap() 
	:
	BackGroundRenderer_(nullptr),
	BackGroundObjectRenderer_(nullptr),
	FrontObjectRenderer_(nullptr),
	TerrainRenderer_(nullptr)
{
}

MasterMap::~MasterMap() 
{
}

void MasterMap::Start()
{
	GetTransform().SetLocalScale({ 1, 1, 1 });
}

void MasterMap::CreateBackGround(std::string _FileName, float4 _MapSize, int _indexX, int _indexY)
{
	int fileIndex = 1;

	for (int y = 0; y < _indexY; ++y)
	{
		for (int x = 0; x < _indexX; ++x)
		{
			std::string fileName = _FileName;
			fileName += std::to_string(fileIndex);
			fileName += ".png";
			GameEngineTextureRenderer* BackGroundRenderer_;

			BackGroundRenderer_ = CreateComponent<GameEngineTextureRenderer>();
			BackGroundRenderer_->SetTexture(fileName);
			BackGroundRenderer_->GetTransform().SetLocalScale({ _MapSize.x, _MapSize.y, _MapSize.z });
			BackGroundRenderer_->GetTransform().SetLocalPosition({ _MapSize.x * x , _MapSize.y * -y });
			BackGroundRenderer_->SetOrder(static_cast<int>(RENDERORDER::Background));
			++fileIndex;
			fileName = "";

		}	
	}
}

void MasterMap::CreateBackGroundObject(std::string _FileName, float4 _MapSize, int _indexX, int _indexY)
{
	int fileIndex = 1;

	for (int y = 0; y < _indexY; ++y)
	{
		for (int x = 0; x < _indexX; ++x)
		{
			std::string fileName = _FileName;
			fileName += std::to_string(fileIndex);
			fileName += ".png";
			BackGroundObjectRenderer_ = CreateComponent<GameEngineTextureRenderer>();
			BackGroundObjectRenderer_->SetTexture(fileName);
			BackGroundObjectRenderer_->GetTransform().SetLocalScale({ _MapSize.x, _MapSize.y, _MapSize.z });
			BackGroundObjectRenderer_->GetTransform().SetLocalPosition({ _MapSize.x * x , _MapSize.y * -y });
			BackGroundObjectRenderer_->SetOrder(static_cast<int>(RENDERORDER::Background_Object));

			++fileIndex;
			fileName = "";

		}
	}
}

void MasterMap::CreateFrontObject(std::string _FileName, float4 _MapSize, int _indexX, int _indexY)
{
	int fileIndex = 1;

	for (int y = 0; y < _indexY; ++y)
	{
		for (int x = 0; x < _indexX; ++x)
		{
			std::string fileName = _FileName;
			fileName += std::to_string(fileIndex);
			fileName += ".png";
			FrontObjectRenderer_ = CreateComponent<GameEngineTextureRenderer>();
			FrontObjectRenderer_->SetTexture(fileName);
			FrontObjectRenderer_->GetTransform().SetLocalScale({ _MapSize.x, _MapSize.y, _MapSize.z });
			FrontObjectRenderer_->GetTransform().SetLocalPosition({ _MapSize.x * x , _MapSize.y * -y });
			FrontObjectRenderer_->SetOrder(static_cast<int>(RENDERORDER::FrontObject));

			++fileIndex;
			fileName = "";

		}
	}
}

void MasterMap::CreateTerrain(std::string _FileName, float4 _MapSize, int _indexX, int _indexY)
{
	int fileIndex = 1;

	for (int y = 0; y < _indexY; ++y)
	{
		for (int x = 0; x < _indexX; ++x)
		{
			std::string fileName = _FileName;
			fileName += std::to_string(fileIndex);
			fileName += ".png";
			TerrainRenderer_ = CreateComponent<GameEngineTextureRenderer>();
			TerrainRenderer_->SetTexture(fileName);
			TerrainRenderer_->GetTransform().SetLocalScale({ _MapSize.x, _MapSize.y, _MapSize.z });
			TerrainRenderer_->GetTransform().SetLocalPosition({ _MapSize.x * x , _MapSize.y * -y });
			TerrainRenderer_->SetOrder(static_cast<int>(RENDERORDER::Terrain));

			++fileIndex;
			fileName = "";

		}
	}
}

