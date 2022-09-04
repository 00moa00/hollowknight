#pragma once
#include <GameEngineCore/GameEngineLevel.h>
#include "Knight.h"
#include "MasterMap.h"
#include "Monster.h"
#include "Crawlid.h"
#include "HUD.h"
#include "KnightShadow.h"
#include "SettingPage.h"
#include "ItemSlot.h"
#include "Item.h"
#include "ForgottenCrossroadMap.h"
#include "SettingPageInfo.h"

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
	ForgottenCrossroadMap* ForgottenCrossroadMap_;

	SettingPageInfo* CharmPageInfo_;
	SettingPageInfo* InventoryPageInfo_;


public:
	std::map<int, PointActorComponent*> PointActorListCharm;
	std::map<int, PointActorComponent*> PointActorListMap;
	std::map<int, PointActorComponent*> PointActorListMonsterBook;
	std::map<int, PointActorComponent*> PointActorListInventory;

	std::vector<Notches*> AllNotes_;

	GameEngineRenderer* BackgroundRenderer_;

protected:
	void CraateMasterMapActor();
	void CreateKnightActor();
	void CreateKingsPass1Monster();
	void CreateUIActor();
	void CreateKnightShadowActor();
	void CreateSettingPageActor();
	void CreateForgottenCrossroadMap();

public:
	void CreateCharmPageInfo(GameEngineActor* ParrentPage);
	void CreateInventoryPageInfo(GameEngineActor* ParrentPage);

protected:
	void CameraMoveWindowLimit();
	void CameraMoveKnightLimit();

	void SetMainMapSize(float4 _MapSize);

public :
	void PushPointActorCharm(int _Order, PointActorComponent* _PointActorComponent);
	void PushPointActorMonsterBook(int _Order, PointActorComponent* _PointActorComponent);
	void PushPointActorMap(int _Order, PointActorComponent* _PointActorComponent);
	void PushPointActorInventory(int _Order, PointActorComponent* _PointActorComponent);

	void PushNotches(Notches* _Notches, float4 _Position);

	void PustItemInventroy(ITEM_LIST _Item);

	GameEngineCameraActor* GetMapCameraActor();
	GameEngineTransform& GetMapCameraActorTransform();

	ForgottenCrossroadMap* GetForgottenCrossroadMap()
	{
		return ForgottenCrossroadMap_;
	}

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

	SettingPageInfo* GetCharmPageInfo()
	{
		return 	CharmPageInfo_;
	}
		
	SettingPageInfo* GetInventoryPageInfo()
	{
		return 	InventoryPageInfo_;
	}

};

