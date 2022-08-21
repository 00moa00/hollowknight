#pragma once
#include <GameEngineCore/GameEngineLevel.h>
#include "HollowKnightLevel.h"

// Ό³Έν :
class DirtmouthLevel3 : public HollowKnightLevel
{
public:
	// constrcuter destructer
	DirtmouthLevel3();
	~DirtmouthLevel3();

	// delete Function
	DirtmouthLevel3(const DirtmouthLevel3& _Other) = delete;
	DirtmouthLevel3(DirtmouthLevel3&& _Other) noexcept = delete;
	DirtmouthLevel3& operator=(const DirtmouthLevel3& _Other) = delete;
	DirtmouthLevel3& operator=(DirtmouthLevel3&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _DeltaTime) override;
	void End() override;

private:

};

