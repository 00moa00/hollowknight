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

// 데이터 관리 : KnightData에 모든 정보가 들어있다.
// 레벨 변경 할 때에 정보를 넣어주는 형식으로 간다.
// 스펠아이템과 소비 아이템은 모두 생성해두고 on오프만 하기 때문에 상관없음.
// 일반 아이템의 경우 순서가 달라지는데 모든 아이템의 경우 생성이 되어있으나
// 가지고 있는 아이템만 랜더 on이 되어있기 때문에 
//문제 : 플레이어가 해당 아이템을 가지고 있는지 아닌지 글로벌로 체크해야함. 

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
	std::map<int, PointActorComponent*> PointActorListInventory;

	std::map<int, Item>* AllItem_;


	std::vector<Notches*> AllNotes_;



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
	void PushPointActorInventory(int _Order, PointActorComponent* _PointActorComponent);

	void PushNotches(Notches* _Notches, float4 _Position);

	void PustItemInventroy(ITEM_LIST _Item);

	GameEngineCameraActor* GetUser0CameraActor();
	GameEngineTransform& GetUser0CameraActorTransform();


};

