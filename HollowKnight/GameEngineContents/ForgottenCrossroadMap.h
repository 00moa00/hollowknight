#pragma once
#include "Map.h"
#include <GameEngineCore/CoreMinimal.h>


// Ό³Έν :
class ForgottenCrossroadMap : public GameEngineActor
{
public:
	// constrcuter destructer
	ForgottenCrossroadMap();
	~ForgottenCrossroadMap();

	// delete Function
	ForgottenCrossroadMap(const ForgottenCrossroadMap& _Other) = delete;
	ForgottenCrossroadMap(ForgottenCrossroadMap&& _Other) noexcept = delete;
	ForgottenCrossroadMap& operator=(const ForgottenCrossroadMap& _Other) = delete;
	ForgottenCrossroadMap& operator=(ForgottenCrossroadMap&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _DeltaTime) override;

private:
	std::map<int, Map*> ForgottenCrossroadMap_;
	std::vector<float4> MapPosition_;

//public:
//	void MapOn();
//	void MapOff();


};

