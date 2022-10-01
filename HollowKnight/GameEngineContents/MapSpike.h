#pragma once
#include "Monster.h"
// Ό³Έν :
class MapSpike : public Monster
{
public:
	// constrcuter destructer
	MapSpike();
	~MapSpike();

	// delete Function
	MapSpike(const MapSpike& _Other) = delete;
	MapSpike(MapSpike&& _Other) noexcept = delete;
	MapSpike& operator=(const MapSpike& _Other) = delete;
	MapSpike& operator=(MapSpike&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _DeltaTime) override;

private:
	//================================
	//    Bind
	//================================
};

