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
	GameEngineTextureRenderer* CollisionMap_;
public:


public:
	void CreateBackGround(std::string _FileName);
	void CreateBackGroundObject(std::string _FileName);
	void CreateFrontObject(std::string _FileName);
	void CreateTerrain(std::string _FileName);
	void CreateMapCollision(std::string _FileName);

	GameEngineTextureRenderer* GetCollisionMap() const
	{

		if (CollisionMap_ != nullptr)
		{
			return CollisionMap_;

		}

		else
		{
			return nullptr;
		}
	}

	void ChangeGrimmMap();
	void ChangeGrimmRoomMap(std::string _Front, std::string _Back, std::string _BackObject);



};

