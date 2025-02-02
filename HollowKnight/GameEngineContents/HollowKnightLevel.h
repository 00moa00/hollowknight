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
#include "DirtmouthMap.h"
#include "AllLocalMap.h"

#include "SettingPageInfo.h"

#include "MainCameraManager.h"
#include "MapCameraManager.h"

#include "MapSmokeMaker.h"
#include "WhiteParicleMaker.h"

#include "HeartPiece.h"

#include "EffectGUIActor.h"

#include "MasterNPC.h"

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

protected:
	//void LevelStartEvent() override;
	//void LevelEndEvent() override;

private:
	float4 MainCameraPosition_;
	float4 MapSize_;

	MasterMap* MasterMap_;
	Knight* Knight_;
	Monster* Crawlid_;
	HUD* HUD_;

	KnightShadow* CurKnightShadow_;
	KnightShadow* NewKnihgtShadow_;

	SettingPage* SettingPage_;
	ForgottenCrossroadMap* ForgottenCrossroadMap_;
	DirtmouthMap* DirtmouthMap_;

	AllLocalMap* AllLocalMap_;

	SettingPageInfo* CharmPageInfo_;
	SettingPageInfo* InventoryPageInfo_;

	EffectGUIActor* EffectGUIActor_;

	MainCameraManager* MainCameraManager_;
	MapCameraManager* MapCameraManager_;

	MapSmokeMaker* MapSmokeMaker_;
	WhiteParicleMaker* WhiteParicleMaker_;

	HeartPiece* HeartPiece_;

	MasterNPC* ShopNPC_;

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
	void CreateKingsPass2Monster();

	void CreateUIActor();
	void CreateKnightShadowActor();
	void CreateSettingPageActor();

	void CreateForgottenCrossroadMap();
	void CreateDirtmouthMap();

	void CreateAllLocalMap();

	void CreateMainCameraManager();
	void CreateMapCameraManager();

	void CreateEffectGUIActor();
	void CreateIselda();
	void CreateSly();

	void CreateMapSmokeMaker();
	void CreawteMapWhiteParticleMaker();

	void CreateHeartPiece();

public:
	void CreateCharmPageInfo(GameEngineActor* ParrentPage);
	void CreateInventoryPageInfo(GameEngineActor* ParrentPage);

protected:
	//void CameraMoveWindowLimit();
	//void CameraMoveKnightLimit();

	//void SetMainMapSize(float4 _MapSize);

public :
	void PushPointActorCharm(int _Order, PointActorComponent* _PointActorComponent);
	void PushPointActorMonsterBook(int _Order, PointActorComponent* _PointActorComponent);
	void PushPointActorMap(int _Order, PointActorComponent* _PointActorComponent);
	void PushPointActorInventory(int _Order, PointActorComponent* _PointActorComponent);

	void PushNotches(Notches* _Notches, float4 _Position);

	void RePustItemInventroy(ITEM_LIST _Item);
	void PustItemInventroy(ITEM_LIST _Item);
	void PustDefultItemInventroy(ITEM_LIST _Item);

	void AllPopItemInventory();

	GameEngineCameraActor* GetMapCameraActor();
	GameEngineTransform& GetMapCameraActorTransform();

	MapCameraManager* GetMapCameraManager()
	{
		return MapCameraManager_;
	}

	GameEngineCamera* GetMapCamera()
	{
		return Cameras[static_cast<int>(CAMERAORDER::MAPCAMERA)];
	}

	MainCameraManager* GetMainCameraManager()
	{
		return MainCameraManager_;
	}

	AllLocalMap* GetAllLocalMap()
	{
		return AllLocalMap_;
	}

	ForgottenCrossroadMap* GetForgottenCrossroadMap()
	{
		return ForgottenCrossroadMap_;
	}

	DirtmouthMap* GetDirtmouthMap()
	{
		return DirtmouthMap_;
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
	SettingPage* GetSettingPage()
	{
		return SettingPage_;
	}


	EffectGUIActor* GetEffectGUIActor()
	{
		return EffectGUIActor_;
	}

	MapSmokeMaker* GetSmokeMaker()
	{
		return MapSmokeMaker_;
	}

	HeartPiece* GetHeartPiece()
	{
		return HeartPiece_;
	}

	MasterNPC* GetShopNPC()
	{
		return ShopNPC_;
	}

	HUD* GetHUD()
	{
		return HUD_;
	}

	float4 GetMapSize()
	{
		return MapSize_;
	}

	void SetMapSize(float4 _MapSize)
	{
		MapSize_ = _MapSize;

	}


};

