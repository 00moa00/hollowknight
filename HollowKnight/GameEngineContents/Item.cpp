#include "PreCompile.h"
#include "Item.h"
#include "ItemSlot.h"

Item::Item() 
{
}

Item::~Item() 
{
}

void Item::Start()
{
}

void Item::Update(float _DeltaTime)
{
}

void Item::CreateItem(std::string _Name, ITEM_LIST _Item)
{
	CreateRendererComponent(_Name + ".png");
}

