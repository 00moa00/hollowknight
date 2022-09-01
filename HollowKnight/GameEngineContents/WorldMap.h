#pragma once
#include "SettingUIMaster.h"

// Ό³Έν :
class WorldMap : public SettingUIMaster
{
public:
	// constrcuter destructer
	WorldMap();
	~WorldMap();

	// delete Function
	WorldMap(const WorldMap& _Other) = delete;
	WorldMap(WorldMap&& _Other) noexcept = delete;
	WorldMap& operator=(const WorldMap& _Other) = delete;
	WorldMap& operator=(WorldMap&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _Deltatime) override;


private:
	MAP_LIST MapType_;


private:

public:
	void CreateWorldMapRenderer(std::string _FilePath, MAP_LIST _MapType);
	void ChangeTextureIdle();
	void ChangeTextureSelect();

	MAP_LIST GetMapType()
	{
		return MapType_;
	}

	void SetMapType(MAP_LIST _MapType)
	{
		MapType_ = _MapType;
	}
};

