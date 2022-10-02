#pragma once
#include <GameEngineCore/GameEngineLevel.h>
#include "HollowKnightLevel.h"

// Ό³Έν :
class GrimmDirtmouthLevel3 : public HollowKnightLevel
{
public:
	// constrcuter destructer
	GrimmDirtmouthLevel3();
	~GrimmDirtmouthLevel3();

	// delete Function
	GrimmDirtmouthLevel3(const GrimmDirtmouthLevel3& _Other) = delete;
	GrimmDirtmouthLevel3(GrimmDirtmouthLevel3&& _Other) noexcept = delete;
	GrimmDirtmouthLevel3& operator=(const GrimmDirtmouthLevel3& _Other) = delete;
	GrimmDirtmouthLevel3& operator=(GrimmDirtmouthLevel3&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _DeltaTime) override;
	void End() override;

	void LevelStartEvent() override;
	void LevelEndEvent() override;

private:

};

