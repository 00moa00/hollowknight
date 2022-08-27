#pragma once
#include "SettingUIMaster.h"
#include "Item.h"

struct ItemSlotPos
{
public:
	int SlotNum_;
	float4 SlotPos_;
};

struct ItemState
{
public:
	int ItemNum_;		//슬롯 번호
	std::string ItemName_;
};

// 설명 :
class ItemSlot : public SettingUIMaster
{
public:
	// constrcuter destructer
	ItemSlot();
	~ItemSlot();

	// delete Function
	ItemSlot(const ItemSlot& _Other) = delete;
	ItemSlot(ItemSlot&& _Other) noexcept = delete;
	ItemSlot& operator=(const ItemSlot& _Other) = delete;
	ItemSlot& operator=(ItemSlot&& _Other) noexcept = delete;

protected:
	Item* Item_;
	ItemState ItemState_;

public:
	void CreateItem(std::string _Name, int _ItemNum, ITEM_LIST _Item);



	//================================
	//    Getter 
	//================================

	int GetItemNum()
	{
		return ItemState_.ItemNum_;
	}


	std::string& GetItemName()
	{
		return ItemState_.ItemName_;
	}

	//================================
	//    Setter 
	//================================


};

