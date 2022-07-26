#pragma once
#include <GameEngineCore/CoreMinimal.h>

#include <vector>

// ¼³¸í : ¸Ê°ü¸®
class GameEngineTextureRenderer;
class MasterMap : public GameEngineActor
{
public:
	// constrcuter destructer
	MasterMap();
	~MasterMap();

	// delete Function
	MasterMap(const MasterMap& _Other) = delete;
	MasterMap(MasterMap&& _Other) noexcept = delete;
	MasterMap& operator=(const MasterMap& _Other) = delete;
	MasterMap& operator=(MasterMap&& _Other) noexcept = delete;

protected:
	void Start();
	
private:
	GameEngineTextureRenderer* BackGroundRenderer_;
	GameEngineTextureRenderer* BackGroundObjectRenderer_;
	GameEngineTextureRenderer* FrontObjectRenderer_;
	GameEngineTextureRenderer* TerrainRenderer_;
	//GameEngineTextureRenderer* CollisionMap_;

	std::vector<GameEngineTextureRenderer*> CollisionMap_;
	

public:
	void CreateBackGround(std::string _FileName, float4 _MapSize, int _indexX, int _indexY);
	void CreateBackGroundObject(std::string _FileName, float4 _MapSize, int _indexX, int _indexY);
	void CreateFrontObject(std::string _FileName, float4 _MapSize, int _indexX, int _indexY);
	void CreateTerrain(std::string _FileName, float4 _MapSize, int _indexX, int _indexY);
	void CreateMapCollision(std::string _FileName, float4 _MapSize, int _indexX, int _indexY);

	std::vector<GameEngineTextureRenderer*> GetCollisionMap()
	{
		return CollisionMap_;
	}
};

