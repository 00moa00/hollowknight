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
class PointActorComponent;
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

public:
	std::map<int, PointActorComponent*> PointActorListCharm;
	std::map<int, PointActorComponent*> PointActorListMap;
	std::map<int, PointActorComponent*> PointActorListMonsterBook;

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

public :
	void PushPointActorCharm(int _Order, PointActorComponent* _PointActorComponent);
	void PushPointActorMonsterBook(int _Order, PointActorComponent* _PointActorComponent);
	void PushPointActorMap(int _Order, PointActorComponent* _PointActorComponent);



	void SortPointActor();

	//bool PointActorXSort(SettingUIMaster* _Left, SettingUIMaster* _Right)
	//{
	//	return _Left->GetTransform().GetWorldPosition().x < _Right->GetTransform().GetWorldPosition().x;
	//}

	//bool PointActorYSort(SettingUIMaster* _Left, SettingUIMaster* _Right)
	//{
	//	return _Left->GetTransform().GetWorldPosition().y > _Right->GetTransform().GetWorldPosition().y;
	//}
};

