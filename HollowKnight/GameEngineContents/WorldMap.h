#pragma once

// Ό³Έν :
class WorldMap
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

private:

};

