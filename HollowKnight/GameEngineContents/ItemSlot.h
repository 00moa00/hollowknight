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
	bool isItem_;		//해당 슬롯에 아이템이 있는지
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

	GameEngineUIRenderer* SpellRing_;
	GameEngineUIRenderer* SpellRingBack_;
public:
	void CreateItemSlot(std::string _Name, int _ItemNum, ITEM_LIST _Item);
	void CreateItemSlot(int _ItemNum, ITEM_LIST _Item, ITEM_TYPE _type);
	void PustItem(int _ItemNum, ITEM_LIST _Item);
	void BackItem(int _ItemNum, ITEM_LIST _Item);

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

	bool GetisItem()
	{
		return ItemState_.isItem_;
	}

	Item* GetItem()
	{
		return Item_;
	}


	//================================
	//    Setter 
	//================================

	void SetisItem(bool _b)
	{
		ItemState_.isItem_ = _b;
	}

};

