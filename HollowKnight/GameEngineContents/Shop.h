#pragma once
#include <GameEngineCore/CoreMinimal.h>
#include <GameEngineCore/GameEngineCollision.h>

#include "ContentsFontRenderer.h"

#include "ShopItem.h"
#include "ShopArrow.h"

enum class SHOP_TYPE
{
	Sly_Shop,
	Map_Shop
};



// 설명 :
class Shop : public GameEngineActor
{
public:
	// constrcuter destructer
	Shop();
	~Shop();

	// delete Function
	Shop(const Shop& _Other) = delete;
	Shop(Shop&& _Other) noexcept = delete;
	Shop& operator=(const Shop& _Other) = delete;
	Shop& operator=(Shop&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _DeltaTime) override;

private:
	
	bool isLimitMoveUP_;
	bool isLimitMoveDown_;

	float LimitMoveTimer_;

	float MoveSpeed_;
	float LimitSpeed_;

	GameEngineUIRenderer* ShopBackboardRenderer_;
	GameEngineUIRenderer* ShopTopRenderer_;
	GameEngineUIRenderer* ShopBottomRenderer_;
	GameEngineUIRenderer* ShopBottomMaskRederer;
	GameEngineUIRenderer* ShopTopMaskRenderer_;

	GameEngineUIRenderer* ShopCurrentItemBackboardRenderer_;
	GameEngineUIRenderer* ShopTopDividerRenderer_;
	GameEngineUIRenderer* ShopBottomDividerRenderer_;

	GameEngineUIRenderer* FigureheadRenderer_;

	ShopArrow* ShopArrow_;

	ContentsFontRenderer* ItemName_;
	ContentsFontRenderer* ItemInfo_;

	SHOP_TYPE ShopType_;

	GameEngineStateManager ShopManager_;


	std::vector<ShopItem*> ShopItemList_;

public:
	std::vector<ShopItem*>& GetShopItemList()
	{
		return ShopItemList_;
	}

	SHOP_TYPE GetShopType()
	{
		return ShopType_;
	}

	void SetShopType(SHOP_TYPE _ShopType)
	{
		ShopType_ = _ShopType;
	}

	void SetShopPopup()
	{
		ShopTopRenderer_->ChangeFrameAnimation("POPUP_ANIMATION");
		ShopBottomRenderer_->ChangeFrameAnimation("POPUP_ANIMATION");
		FigureheadRenderer_->ChangeFrameAnimation("POPUP_ANIMATION");

		ShopManager_.ChangeState("SHOP_IDLE");

	}

	void SetShopPopDown()
	{
		ShopTopRenderer_->ChangeFrameAnimation("POPDOWN_ANIMATION");
		ShopBottomRenderer_->ChangeFrameAnimation("POPDOWN_ANIMATION");
		FigureheadRenderer_->ChangeFrameAnimation("POPDOWN_ANIMATION");

	}

	void CreateFigurehead(SHOP_TYPE _Type);

	void SetItemListPosition();
	void SetItemListUpdatePosition();

	//================================
	//    Bind State
	//================================
	// ---- 기본 ----

	void ShopStillStart(const StateInfo& _Info);
	void ShopStillUpdate(float _DeltaTime, const StateInfo& _Info);
	void ShopStillEnd(const StateInfo& _Info);

	void ShopIdleStart(const StateInfo& _Info);
	void ShopIdleUpdate(float _DeltaTime, const StateInfo& _Info);
	void ShopIdleEnd(const StateInfo& _Info);

	void ShopPopDownStart(const StateInfo& _Info);
	void ShopPopDownUpdate(float _DeltaTime, const StateInfo& _Info);
	void ShopPopDownEnd(const StateInfo& _Info);

	void ShopMoveUpStart(const StateInfo& _Info);
	void ShopMoveUpUpdate(float _DeltaTime, const StateInfo& _Info);
	void ShopMoveUpEnd(const StateInfo& _Info);

	void ShopMoveDownStart(const StateInfo& _Info);
	void ShopMoveDownUpdate(float _DeltaTime, const StateInfo& _Info);
	void ShopMoveDownEnd(const StateInfo& _Info);

	void ShopBuyItemMoveUpStart(const StateInfo& _Info);
	void ShopBuyItemMoveUpUpdate(float _DeltaTime, const StateInfo& _Info);
	void ShopBuyItemMoveUpEnd(const StateInfo& _Info);

	void ShopBuyItemMoveDownStart(const StateInfo& _Info);
	void ShopBuyItemMoveDownUpdate(float _DeltaTime, const StateInfo& _Info);
	void ShopBuyItemMoveDownEnd(const StateInfo& _Info);

	void ShopItemMoveLimitStart(const StateInfo& _Info);
	void ShopItemMoveLimitUpdate(float _DeltaTime, const StateInfo& _Info);
	void ShopItemMoveLimitEnd(const StateInfo& _Info);

	void ShopItemMoveLimitReturnStart(const StateInfo& _Info);
	void ShopItemMoveLimitReturnUpdate(float _DeltaTime, const StateInfo& _Info);
	void ShopItemMoveLimitReturnEnd(const StateInfo& _Info);


};

