#pragma once
#include "MasterMapItem.h"

// Ό³Έν :
class DropGeo : public MasterMapItem
{
public:
	// constrcuter destructer
	DropGeo();
	~DropGeo();

	// delete Function
	DropGeo(const DropGeo& _Other) = delete;
	DropGeo(DropGeo&& _Other) noexcept = delete;
	DropGeo& operator=(const DropGeo& _Other) = delete;
	DropGeo& operator=(DropGeo&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _DeltaTime) override;

private:
	float4 MoveDirection_;


	GameEngineStateManager DropGeoManager_;

private:

	//================================
	//    Bind State
	//================================
	void DropGeoAirStart(const StateInfo& _Info);
	void DropGeoAirUpdate(float _DeltaTime, const StateInfo& _Info);
	void DropGeoAirEnd(const StateInfo& _Info);

	void DropDeoOnGroundStart(const StateInfo& _Info);
	void DropDeoOnGroundUpdate(float _DeltaTime, const StateInfo& _Info);
	void DropDeoOnGroundEnd(const StateInfo& _Info);
};

