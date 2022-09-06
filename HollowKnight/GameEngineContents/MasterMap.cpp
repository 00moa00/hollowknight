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
	GetTransform().SetWorldPosition({0,0,0});
}

void MasterMap::CreateBackGround(std::string _FileName)
{
	BackGroundRenderer_ = CreateComponent<GameEngineTextureRenderer>();
	BackGroundRenderer_->SetTexture(_FileName);
	BackGroundRenderer_->GetTransform().SetLocalScale(BackGroundRenderer_->GetCurTexture()->GetScale());
	BackGroundRenderer_->SetPivot(PIVOTMODE::LEFTTOP);
	BackGroundRenderer_->GetTransform().SetWorldPosition({0,0, static_cast<float>(Z_ORDER::Background) });
	BackGroundRenderer_->SetSamplingModePoint();

}

void MasterMap::CreateBackGroundObject(std::string _FileName)
{
	BackGroundObjectRenderer_ = CreateComponent<GameEngineTextureRenderer>();
	BackGroundObjectRenderer_->SetTexture(_FileName);
	BackGroundObjectRenderer_->GetTransform().SetLocalScale(BackGroundObjectRenderer_->GetCurTexture()->GetScale());
	BackGroundObjectRenderer_->SetPivot(PIVOTMODE::LEFTTOP);
	BackGroundObjectRenderer_->GetTransform().SetWorldPosition({0, 0, static_cast<float>(Z_ORDER::Background_Object) });
	BackGroundObjectRenderer_->SetSamplingModePoint();

}


void MasterMap::CreateTerrain(std::string _FileName)
{
	TerrainRenderer_ = CreateComponent<GameEngineTextureRenderer>();
	TerrainRenderer_->SetTexture(_FileName);
	TerrainRenderer_->GetTransform().SetLocalScale(TerrainRenderer_->GetCurTexture()->GetScale());
	TerrainRenderer_->SetPivot(PIVOTMODE::LEFTTOP);
	TerrainRenderer_->GetTransform().SetWorldPosition({ 0, 0, static_cast<float>(Z_ORDER::Terrain) });
	TerrainRenderer_->SetSamplingModePoint();

}

void MasterMap::CreateFrontObject(std::string _FileName)
{
	FrontObjectRenderer_ = CreateComponent<GameEngineTextureRenderer>();
	FrontObjectRenderer_->SetTexture(_FileName);
	FrontObjectRenderer_->GetTransform().SetLocalScale(FrontObjectRenderer_->GetCurTexture()->GetScale());
	FrontObjectRenderer_->SetPivot(PIVOTMODE::LEFTTOP);
	FrontObjectRenderer_->GetTransform().SetWorldPosition({0,0, static_cast<float>(Z_ORDER::FrontObject) });
	FrontObjectRenderer_->SetSamplingModePoint();

}


void MasterMap::CreateMapCollision(std::string _FileName)
{
	CollisionMap_ = CreateComponent<GameEngineTextureRenderer>();
	CollisionMap_->SetTexture(_FileName);
	CollisionMap_->GetTransform().SetLocalScale(CollisionMap_->GetCurTexture()->GetScale());
	//CollisionMap_->SetPivot(PIVOTMODE::LEFTTOP);
	CollisionMap_->GetTransform().SetWorldPosition({ CollisionMap_->GetCurTexture()->GetScale().x / 2, -CollisionMap_->GetCurTexture()->GetScale().y / 2 });
	CollisionMap_->Off();

}

//void MasterMap::CreateBackGround(std::string _FileName, float4 _MapSize, int _indexX, int _indexY)
//{
//	int fileIndex = 1;
//
//	for (int y = 0; y < _indexY; ++y)
//	{
//		for (int x = 0; x < _indexX; ++x)
//		{
//			std::string fileName = _FileName;
//			fileName += std::to_string(fileIndex);
//			fileName += ".png";
//			GameEngineTextureRenderer* BackGroundRenderer_;
//
//			BackGroundRenderer_ = CreateComponent<GameEngineTextureRenderer>();
//			BackGroundRenderer_->SetTexture(fileName);
//			BackGroundRenderer_->GetTransform().SetLocalScale({ _MapSize.x, _MapSize.y, _MapSize.z });
//			BackGroundRenderer_->GetTransform().SetLocalPosition({ _MapSize.x * x , _MapSize.y * -y });
//			BackGroundRenderer_->SetOrder(static_cast<int>(RENDERORDER::Background));
//			++fileIndex;
//			fileName = "";
//
//		}	
//	}
//}
//
//void MasterMap::CreateBackGroundObject(std::string _FileName, float4 _MapSize, int _indexX, int _indexY)
//{
//	int fileIndex = 1;
//
//	for (int y = 0; y < _indexY; ++y)
//	{
//		for (int x = 0; x < _indexX; ++x)
//		{
//			std::string fileName = _FileName;
//			fileName += std::to_string(fileIndex);
//			fileName += ".png";
//			BackGroundObjectRenderer_ = CreateComponent<GameEngineTextureRenderer>();
//			BackGroundObjectRenderer_->SetTexture(fileName);
//			BackGroundObjectRenderer_->GetTransform().SetLocalScale({ _MapSize.x, _MapSize.y, _MapSize.z });
//			BackGroundObjectRenderer_->GetTransform().SetLocalPosition({ _MapSize.x * x , _MapSize.y * -y });
//			BackGroundObjectRenderer_->SetOrder(static_cast<int>(RENDERORDER::Background_Object));
//
//			++fileIndex;
//			fileName = "";
//
//		}
//	}
//}
//
//void MasterMap::CreateFrontObject(std::string _FileName, float4 _MapSize, int _indexX, int _indexY)
//{
//	int fileIndex = 1;
//
//	for (int y = 0; y < _indexY; ++y)
//	{
//		for (int x = 0; x < _indexX; ++x)
//		{
//			std::string fileName = _FileName;
//			fileName += std::to_string(fileIndex);
//			fileName += ".png";
//			FrontObjectRenderer_ = CreateComponent<GameEngineTextureRenderer>();
//			FrontObjectRenderer_->SetTexture(fileName);
//			FrontObjectRenderer_->GetTransform().SetLocalScale({ _MapSize.x, _MapSize.y, _MapSize.z });
//			FrontObjectRenderer_->GetTransform().SetLocalPosition({ _MapSize.x * x , _MapSize.y * -y });
//			FrontObjectRenderer_->SetOrder(static_cast<int>(RENDERORDER::FrontObject));
//
//			++fileIndex;
//			fileName = "";
//
//		}
//	}
//}
//
//void MasterMap::CreateTerrain(std::string _FileName, float4 _MapSize, int _indexX, int _indexY)
//{
//	int fileIndex = 1;
//
//	for (int y = 0; y < _indexY; ++y)
//	{
//		for (int x = 0; x < _indexX; ++x)
//		{
//			std::string fileName = _FileName;
//			fileName += std::to_string(fileIndex);
//			fileName += ".png";
//			TerrainRenderer_ = CreateComponent<GameEngineTextureRenderer>();
//			TerrainRenderer_->SetTexture(fileName);
//			TerrainRenderer_->GetTransform().SetLocalScale({ _MapSize.x, _MapSize.y, _MapSize.z });
//			TerrainRenderer_->GetTransform().SetLocalPosition({ _MapSize.x * x , _MapSize.y * -y });
//
//			++fileIndex;
//			fileName = "";
//
//		}
//	}
//}

//void MasterMap::CreateMapCollision(std::string _FileName, float4 _MapSize, int _indexX, int _indexY)
//{
//	CollisionMap_.reserve(_indexX * _indexY);
//
//	int fileIndex = 1;
//
//	for (int y = 0; y < _indexY; ++y)
//	{
//		for (int x = 0; x < _indexX; ++x)
//		{
//			std::string fileName = _FileName;
//			fileName += std::to_string(fileIndex);
//			fileName += ".png";
//
//
//			CollisionMap_.push_back(CreateComponent<GameEngineTextureRenderer>());
//
//			std::vector<GameEngineTextureRenderer*>::iterator Iter = --CollisionMap_.end();
//			(*Iter)->SetTexture(fileName);
//			(*Iter)->GetTransform().SetLocalScale({ _MapSize.x, _MapSize.y, _MapSize.z });
//			(*Iter)->GetTransform().SetLocalPosition({ _MapSize.x * x , _MapSize.y * -y });
//			(*Iter)->SetOrder(static_cast<int>(RENDERORDER::Monster));
//			(*Iter)->SetPivot(PIVOTMODE::LEFTTOP);
//
//
//			++fileIndex;
//			fileName = "";
//
//		}
//	}
//}
//
