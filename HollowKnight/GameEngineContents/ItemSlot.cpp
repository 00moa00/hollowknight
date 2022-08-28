#include "PreCompile.h"
#include "ItemSlot.h"


ItemSlot::ItemSlot() 
{
}

ItemSlot::~ItemSlot() 
{
}


void ItemSlot::CreateItemSlot(std::string _Name, int _ItemNum, ITEM_LIST _Item)
{
	ItemState_.ItemName_ = _Name;
	ItemState_.ItemNum_ = _ItemNum;


	Item_ = GetLevel()->CreateActor<Item>();
	Item_->CreateItem(_Name,  _Item);

	Item_->SetParent(this);
}

void ItemSlot::CreateItemSlot(int _ItemNum, ITEM_LIST _Item, ITEM_TYPE _type)
{
	CreateRendererComponent({49,49}, "new_item_orb.png");
	ItemState_.ItemNum_ = _ItemNum;

}

void ItemSlot::PustItem(std::string _Name, ITEM_LIST _Item)
{
	Item_ = GetLevel()->CreateActor<Item>();
	Item_->CreateItem(_Name, _Item);
}
