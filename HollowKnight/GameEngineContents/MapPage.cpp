#include "PreCompile.h"
#include "MapPage.h"
#include "PointActorComponent.h"

MapPage::MapPage() 
{
}

MapPage::~MapPage() 
{
}

void MapPage::Start()
{
	SetPageType(PAGE_TYPE::Map);

	MapList_.push_back(GetLevel()->CreateActor<WorldMap>());
	MapList_[0]->CreateWorldMapRenderer("wide_map__0001_town.png", MAP_LIST::DIRTMOUTH);
	MapList_[0]->GetTransform().SetWorldPosition({ 21,  76 });
	MapList_[0]->SetParent(this);

	PointActorComponent* Component_ = CreateComponent<PointActorComponent>();
	Component_->PushPointerActor(0, PAGE_TYPE::Map, MapList_[0]);

	MapList_.push_back(GetLevel()->CreateActor<WorldMap>());
	MapList_[1]->CreateWorldMapRenderer("wide_map__0000_crossroads.png", MAP_LIST::CORSSROAD);
	MapList_[1]->GetTransform().SetWorldPosition({ -50, -37 });
	MapList_[1]->SetParent(this);

	Component_ = CreateComponent<PointActorComponent>();
	Component_->PushPointerActor(1, PAGE_TYPE::Map, MapList_[1]);

}

void MapPage::Update(float _DeltaTime)
{
}

