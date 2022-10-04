#pragma once
#include "Map.h"
#include <GameEngineCore/CoreMinimal.h>

// Ό³Έν :
class DirtmouthMap : public GameEngineActor
{
public:
	// constrcuter destructer
	DirtmouthMap();
	~DirtmouthMap();

	// delete Function
	DirtmouthMap(const DirtmouthMap& _Other) = delete;
	DirtmouthMap(DirtmouthMap&& _Other) noexcept = delete;
	DirtmouthMap& operator=(const DirtmouthMap& _Other) = delete;
	DirtmouthMap& operator=(DirtmouthMap&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _DeltaTime) override;

private:
	std::map<int, Map*> DirtmouthMap_;

};

