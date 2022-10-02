#pragma once
#include <GameEngineCore/GameEngineLevel.h>
#include "HollowKnightLevel.h"

// Ό³Έν :
class GrimmDirtmouthLevel1 : public HollowKnightLevel
{
public:
	// constrcuter destructer
	GrimmDirtmouthLevel1();
	~GrimmDirtmouthLevel1();

	// delete Function
	GrimmDirtmouthLevel1(const GrimmDirtmouthLevel1& _Other) = delete;
	GrimmDirtmouthLevel1(GrimmDirtmouthLevel1&& _Other) noexcept = delete;
	GrimmDirtmouthLevel1& operator=(const GrimmDirtmouthLevel1& _Other) = delete;
	GrimmDirtmouthLevel1& operator=(GrimmDirtmouthLevel1&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _DeltaTime) override;
	void End() override;

	void LevelStartEvent() override;
	void LevelEndEvent() override;

private:

};

