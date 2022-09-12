#pragma once
#include "MasterUI.h"
#include <GameEngineCore/GameEngineFontRenderer.h>
#include "ContentsFontRenderer.h"
#include "GlobalContentsValue.h"

struct ShopItemState
{
	std::string ItemName_;
	std::string ItemInfo_;

	CHARM_SLOT Charm_;
	ITEM_LIST Item_;

	bool InInventory_;

	int ItemPrice_;
};




class GameEngineUIRenderer;
class ShopItem : public GameEngineActor
{
public:
	// constrcuter destructer
	ShopItem();
	~ShopItem();

	// delete Function
	ShopItem(const ShopItem& _Other) = delete;
	ShopItem(ShopItem&& _Other) noexcept = delete;
	ShopItem& operator=(const ShopItem& _Other) = delete;
	ShopItem& operator=(ShopItem&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _DeltaTime) override;

private:
	GameEngineUIRenderer* ItemRenderer_;
	GameEngineUIRenderer* GeoRenderer_;
	ContentsFontRenderer* PriceRenderer_;

	ShopItemState ShopItemState_;

	int SlideItemIndex_;

public:
	void CreateShopItem(SHOP_ITEM _Item);
	void SetFontRendererMove();

public:
	//================================
	//     Getter
	//================================

	std::string GetItemInfo()
	{
		return ShopItemState_.ItemInfo_;
	}

	std::string GetItemName()
	{
		return ShopItemState_.ItemName_;
	}

	int GetItemPrice()
	{
		return ShopItemState_.ItemPrice_;
	}

	int GetSlideItemIndex()
	{
		return SlideItemIndex_;
	}

	bool GetinInventory()
	{
		return ShopItemState_.InInventory_;
	}


	CHARM_SLOT GetShopCharm()
	{
		return ShopItemState_.Charm_;
	}

	ITEM_LIST GetShopItem()
	{
		return ShopItemState_.Item_;
	}


	bool isCurrentSlideItemCenter()
	{
		if (SlideItemIndex_ == static_cast<int>(SlideItemIndex::Third))
		{
			return true;
		}
		else
		{
			return false;
		}
	}

	//================================
	//    Setter
	//================================

	void SetSlideItemIndex(int _index)
	{
		SlideItemIndex_ = _index;
	}

};

