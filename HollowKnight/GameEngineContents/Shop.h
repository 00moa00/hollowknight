#pragma once
#include <GameEngineCore/CoreMinimal.h>
#include <GameEngineCore/GameEngineCollision.h>

#include <GameEngineCore/GameEngineFontRenderer.h>
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

	}

	void SetShopPopDown()
	{

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
};

