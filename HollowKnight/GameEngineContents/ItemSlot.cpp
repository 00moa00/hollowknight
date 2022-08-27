#include "PreCompile.h"
#include "ItemSlot.h"


ItemSlot::ItemSlot() 
{
}

ItemSlot::~ItemSlot() 
{
}


void ItemSlot::CreateItem(std::string _Name, int _ItemNum, ITEM_LIST _Item)
{



	ItemState_.ItemName_ = _Name;
	ItemState_.ItemNum_ = _ItemNum;



	Item_ = GetLevel()->CreateActor<Item>();
	Item_->CreateItem(_Name,  _ItemNum, _Item);

	Item_->SetParent(this);
}
