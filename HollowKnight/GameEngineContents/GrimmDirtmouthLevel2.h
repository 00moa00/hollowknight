#pragma once
#include <GameEngineCore/GameEngineLevel.h>
#include "HollowKnightLevel.h"
#include "Elderbug.h"
#include "RoomPotal.h"

// Ό³Έν :
class GrimmDirtmouthLevel2 : public HollowKnightLevel
{
public:
	// constrcuter destructer
	GrimmDirtmouthLevel2();
	~GrimmDirtmouthLevel2();

	// delete Function
	GrimmDirtmouthLevel2(const GrimmDirtmouthLevel2& _Other) = delete;
	GrimmDirtmouthLevel2(GrimmDirtmouthLevel2&& _Other) noexcept = delete;
	GrimmDirtmouthLevel2& operator=(const GrimmDirtmouthLevel2& _Other) = delete;
	GrimmDirtmouthLevel2& operator=(GrimmDirtmouthLevel2&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _DeltaTime) override;
	void End() override;

	void LevelStartEvent() override;
	void LevelEndEvent() override;

private:
	Elderbug* Elderbug_;
	RoomPotal* MapShopPotal_;
	RoomPotal* SlyShopPotal_;

	GameEnginePostEffect* GameEnginePostEffect_;

};

