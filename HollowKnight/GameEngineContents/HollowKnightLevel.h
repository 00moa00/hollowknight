#pragma once
#include <GameEngineCore/GameEngineLevel.h>
#include "Knight.h"
#include "MasterMap.h"
#include "Monster.h"
#include "Crawlid.h"
#include "HUD.h"
#include "KnightShadow.h"
#include "SettingPage.h"

// Ό³Έν :
class GameEngineTextureRenderer;
class HollowKnightLevel : public GameEngineLevel
{
public:
	// constrcuter destructer
	HollowKnightLevel();
	~HollowKnightLevel();

	// delete Function
	HollowKnightLevel(const HollowKnightLevel& _Other) = delete;
	HollowKnightLevel(HollowKnightLevel&& _Other) noexcept = delete;
	HollowKnightLevel& operator=(const HollowKnightLevel& _Other) = delete;
	HollowKnightLevel& operator=(HollowKnightLevel&& _Other) noexcept = delete;

protected:

private:
	float4 MainCameraPosition_;
	float4 MainMapSize_;

	MasterMap* MasterMap_;
	Knight* Knight_;
	Monster* Crawlid_;
	HUD* HUD_;

	KnightShadow* CurKnightShadow_;
	KnightShadow* NewKnihgtShadow_;

	SettingPage* SettingPage_;

	GameEngineRenderer* BackgroundRenderer_;

protected:
	void CraateMasterMapActor();
	void CreateKnightActor();
	void CreateKingsPass1Monster();
	void CreateUIActor();
	void CreateKnightShadowActor();
	void CreateSettingPageActor();

	void CameraMoveWindowLimit();
	void CameraMoveKnightLimit();

	MasterMap* GetMasterMap() const
	{
		return MasterMap_;
	}

	Knight* GetKnight() const
	{
		return Knight_;
	}

	Monster* GetCrawlid() const
	{
		return Crawlid_;
	}

	void SetMainMapSize(float4 _MapSize);

};

