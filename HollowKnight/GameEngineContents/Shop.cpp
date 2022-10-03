#include "PreCompile.h"
#include "Shop.h"
#include "KnightData.h"

#include "HollowKnightLevel.h"

Shop::Shop() 
	:


	ShopBackboardRenderer_ (nullptr) ,
	ShopTopRenderer_(nullptr),
	ShopBottomRenderer_(nullptr),
	ShopBottomMaskRederer(nullptr),
	ShopTopMaskRenderer_(nullptr),

	ShopCurrentItemBackboardRenderer_(nullptr),
	ShopTopDividerRenderer_(nullptr),
	ShopBottomDividerRenderer_(nullptr),

	FigureheadRenderer_(nullptr),

	ItemName_(nullptr),
	ItemInfo_(nullptr),


	ShopArrow_(nullptr),
	isLimitMoveUP_(false),
	isLimitMoveDown_(false)
{
}

Shop::~Shop() 
{
}

void Shop::Start()
{
	ShopBackboardRenderer_ = CreateComponent<GameEngineUIRenderer>();
	ShopBackboardRenderer_->SetTexture("msk_generic_soft.png");
	ShopBackboardRenderer_->GetTransform().SetLocalScale({750,800});
	//ShopBackboardRenderer_->GetPixelData().MulColor.a = 0.9f;
	ShopBackboardRenderer_->GetTransform().SetLocalPosition({ 0, -50 });

	ShopCurrentItemBackboardRenderer_ = CreateComponent<GameEngineUIRenderer>();
	ShopCurrentItemBackboardRenderer_->SetTexture("itemBack.png");
	ShopCurrentItemBackboardRenderer_->GetTransform().SetLocalScale(ShopCurrentItemBackboardRenderer_->GetCurTexture()->GetScale());
	ShopCurrentItemBackboardRenderer_->GetTransform().SetWorldPosition({ -200, 20 });

	ShopTopDividerRenderer_ = CreateComponent<GameEngineUIRenderer>();
	ShopTopDividerRenderer_->SetTexture("Inv_0017_divider.png");
	ShopTopDividerRenderer_->GetTransform().SetLocalScale({ ShopCurrentItemBackboardRenderer_->GetCurTexture()->GetScale().x , 3.f});
	ShopTopDividerRenderer_->GetTransform().SetWorldPosition({ -200, 68 });

	ShopBottomDividerRenderer_ = CreateComponent<GameEngineUIRenderer>();
	ShopBottomDividerRenderer_->SetTexture("Inv_0017_divider.png");
	ShopBottomDividerRenderer_->GetTransform().SetLocalScale({ ShopCurrentItemBackboardRenderer_->GetCurTexture()->GetScale().x , 3.f });
	ShopBottomDividerRenderer_->GetTransform().SetWorldPosition({ -200, -30 });

	ShopBottomMaskRederer = CreateComponent<GameEngineUIRenderer>();
	ShopBottomMaskRederer->SetTexture("shop_mask_bottom.png");
	ShopBottomMaskRederer->GetTransform().SetLocalScale({600, 400});
	ShopBottomMaskRederer->GetTransform().SetLocalPosition({ -50, -500, -100 });
	ShopBottomMaskRederer->SetSamplingModePoint();

	ShopTopMaskRenderer_ = CreateComponent<GameEngineUIRenderer>();
	ShopTopMaskRenderer_->SetTexture("shop_mask_top.png");
	ShopTopMaskRenderer_->GetTransform().SetLocalScale({ 600, 400 });
	ShopTopMaskRenderer_->GetTransform().SetLocalPosition({ -50, 400, -100 });
	ShopTopMaskRenderer_->SetSamplingModePoint();

	ShopTopRenderer_ = CreateComponent<GameEngineUIRenderer>();
	ShopTopRenderer_->SetTexture("UI_shops_animated_Shop_Menu_top0000-Sheet.png");
	ShopTopRenderer_->GetTransform().SetLocalScale(ShopTopRenderer_->GetCurTexture()->GetScale());
	ShopTopRenderer_->CreateFrameAnimationCutTexture("POPUP_ANIMATION", FrameAnimation_DESC("UI_shops_animated_Shop_Menu_top0000-Sheet.png", 0, 8, 0.100f, false));
	ShopTopRenderer_->CreateFrameAnimationCutTexture("IDLE_ANIMATION", FrameAnimation_DESC("UI_shops_animated_Shop_Menu_top0000-Sheet.png", 8, 8, 0.100f, false));
	
	{
		std::vector<unsigned int>BackAni;

		for (int i = 8; i > -1; --i)
		{
			BackAni.push_back(i);
		}
		ShopTopRenderer_->CreateFrameAnimationCutTexture("POPDOWN_ANIMATION", FrameAnimation_DESC("UI_shops_animated_Shop_Menu_top0000-Sheet.png", BackAni, 0.070f, false));
	}
	
	ShopTopRenderer_->ChangeFrameAnimation("POPUP_ANIMATION");
	ShopTopRenderer_->SetScaleModeImage();
	ShopTopRenderer_->GetTransform().SetLocalPosition({ 0,190 , -100 });

	ShopTopRenderer_->AnimationBindEnd("POPUP_ANIMATION", [=](const FrameAnimation_DESC& _Info)
		{
			ShopTopRenderer_->ChangeFrameAnimation("IDLE_ANIMATION");
		});

	ShopBottomRenderer_ = CreateComponent<GameEngineUIRenderer>();
	ShopBottomRenderer_->SetTexture("UI_shops_animated_Shop_Menu_bottom0000-Sheet.png");
	ShopBottomRenderer_->GetTransform().SetLocalScale(ShopBottomRenderer_->GetCurTexture()->GetScale());
	ShopBottomRenderer_->CreateFrameAnimationCutTexture("POPUP_ANIMATION", FrameAnimation_DESC("UI_shops_animated_Shop_Menu_bottom0000-Sheet.png", 0, 8, 0.100f, false));
	ShopBottomRenderer_->CreateFrameAnimationCutTexture("IDLE_ANIMATION", FrameAnimation_DESC("UI_shops_animated_Shop_Menu_bottom0000-Sheet.png", 8, 8, 0.100f, false));

	{
		std::vector<unsigned int>BackAni;

		for (int i = 8; i > -1; --i)
		{
			BackAni.push_back(i);
		}
		ShopBottomRenderer_->CreateFrameAnimationCutTexture("POPDOWN_ANIMATION", FrameAnimation_DESC("UI_shops_animated_Shop_Menu_bottom0000-Sheet.png", BackAni, 0.070f, false));
	}


	ShopBottomRenderer_->ChangeFrameAnimation("POPUP_ANIMATION");
	ShopBottomRenderer_->SetScaleModeImage();
	ShopBottomRenderer_->GetTransform().SetLocalPosition({ 0, -350, -100 });

	ShopBottomRenderer_->AnimationBindEnd("POPUP_ANIMATION", [=](const FrameAnimation_DESC& _Info)
		{
			ShopBottomRenderer_->ChangeFrameAnimation("IDLE_ANIMATION");
		});

	ShopBottomRenderer_->AnimationBindEnd("POPDOWN_ANIMATION", [=](const FrameAnimation_DESC& _Info)
		{

			this->Off();

			//ShopBottomRenderer_->ChangeFrameAnimation("IDLE_ANIMATION");
		});


	ShopArrow_ = GetLevel()->CreateActor<ShopArrow>();
	ShopArrow_->GetTransform().SetWorldPosition({ -200, 20, -500 });
	ShopArrow_->SetParent(this);
	ShopArrow_->SetCurrentPointItemIndex(2);

	ItemName_ = GetLevel()->CreateActor<ContentsFontRenderer>();
	ItemName_->CreateFontRenderer("아이템 이름"
		, 34
		, { 0, 0, 0 }
		,false
		, false);
	ItemName_->GetTransform().SetWorldPosition({ 370,  230, static_cast<float>(Z_ORDER::UI_Border) });
	ItemName_->SetScreenMove();
	ItemName_->SetParent(this);

	ItemInfo_ = GetLevel()->CreateActor<ContentsFontRenderer>();
	ItemInfo_->CreateFontRenderer("아이템 설명"
		, 28
		, { 0, 0, 0 }
		,false
		, false
		, 11);
	ItemInfo_->GetTransform().SetWorldPosition({ 370,  150, static_cast<float>(Z_ORDER::UI_Border) });
	ItemInfo_->SetScreenMove();
	ItemInfo_->SetParent(this);


	//================================
	//    CreateKey
	//================================
	if (false == GameEngineInput::GetInst()->IsKey("ItemSlideUp"))
	{
		GameEngineInput::GetInst()->CreateKey("ItemSlideUp", VK_UP);
	}

	if (false == GameEngineInput::GetInst()->IsKey("ItemSlideDown"))
	{
		GameEngineInput::GetInst()->CreateKey("ItemSlideDown", VK_DOWN);
	}

	if (false == GameEngineInput::GetInst()->IsKey("ItemBuy"))
	{
		GameEngineInput::GetInst()->CreateKey("ItemBuy", VK_RETURN);
	}

	ShopManager_.CreateStateMember("SHOP_STILL"
		, std::bind(&Shop::ShopStillUpdate, this, std::placeholders::_1, std::placeholders::_2)
		, std::bind(&Shop::ShopStillStart, this, std::placeholders::_1)
		, std::bind(&Shop::ShopStillEnd, this, std::placeholders::_1));

	ShopManager_.CreateStateMember("SHOP_IDLE"
		, std::bind(&Shop::ShopIdleUpdate, this, std::placeholders::_1, std::placeholders::_2)
		, std::bind(&Shop::ShopIdleStart, this, std::placeholders::_1)
		, std::bind(&Shop::ShopIdleEnd, this, std::placeholders::_1));

	ShopManager_.CreateStateMember("SHOP_POP_DOWN"
		, std::bind(&Shop::ShopPopDownUpdate, this, std::placeholders::_1, std::placeholders::_2)
		, std::bind(&Shop::ShopPopDownStart, this, std::placeholders::_1)
		, std::bind(&Shop::ShopPopDownEnd, this, std::placeholders::_1));

	ShopManager_.CreateStateMember("SHOP_MOVE_UP"
		, std::bind(&Shop::ShopMoveUpUpdate, this, std::placeholders::_1, std::placeholders::_2)
		, std::bind(&Shop::ShopMoveUpStart, this, std::placeholders::_1)
		, std::bind(&Shop::ShopMoveUpEnd, this, std::placeholders::_1));

	ShopManager_.CreateStateMember("SHOP_MOVE_DOWN"
		, std::bind(&Shop::ShopMoveDownUpdate, this, std::placeholders::_1, std::placeholders::_2)
		, std::bind(&Shop::ShopMoveDownStart, this, std::placeholders::_1)
		, std::bind(&Shop::ShopMoveDownEnd, this, std::placeholders::_1));

	ShopManager_.CreateStateMember("BUY_ITEM_MOVE_UP"
		, std::bind(&Shop::ShopBuyItemMoveUpUpdate, this, std::placeholders::_1, std::placeholders::_2)
		, std::bind(&Shop::ShopBuyItemMoveUpStart, this, std::placeholders::_1)
		, std::bind(&Shop::ShopBuyItemMoveUpEnd, this, std::placeholders::_1));

	ShopManager_.CreateStateMember("BUY_ITEM_MOVE_DOWN"
		, std::bind(&Shop::ShopBuyItemMoveDownUpdate, this, std::placeholders::_1, std::placeholders::_2)
		, std::bind(&Shop::ShopBuyItemMoveDownStart, this, std::placeholders::_1)
		, std::bind(&Shop::ShopBuyItemMoveDownEnd, this, std::placeholders::_1));

	ShopManager_.CreateStateMember("MOVE_LIMIT"
		, std::bind(&Shop::ShopItemMoveLimitUpdate, this, std::placeholders::_1, std::placeholders::_2)
		, std::bind(&Shop::ShopItemMoveLimitStart, this, std::placeholders::_1)
		, std::bind(&Shop::ShopItemMoveLimitEnd, this, std::placeholders::_1));

	ShopManager_.CreateStateMember("MOVE_LIMIT_RETURN"
		, std::bind(&Shop::ShopItemMoveLimitReturnUpdate, this, std::placeholders::_1, std::placeholders::_2)
		, std::bind(&Shop::ShopItemMoveLimitReturnStart, this, std::placeholders::_1)
		, std::bind(&Shop::ShopItemMoveLimitReturnEnd, this, std::placeholders::_1));

	ShopManager_.ChangeState("SHOP_IDLE");

}

void Shop::Update(float _DeltaTime)
{
	ShopManager_.Update(_DeltaTime);
}

void Shop::CreateFigurehead(SHOP_TYPE _Type)
{
	switch (_Type)
	{

	case SHOP_TYPE::Sly_Shop:

		FigureheadRenderer_ = CreateComponent<GameEngineUIRenderer>();
		FigureheadRenderer_->SetTexture("UI_shops_animated_Shop_Menu_figurehead_sly0000-Sheet.png");
		FigureheadRenderer_->GetTransform().SetLocalScale(FigureheadRenderer_->GetCurTexture()->GetScale());

		FigureheadRenderer_->CreateFrameAnimationCutTexture("POPUP_ANIMATION", FrameAnimation_DESC("UI_shops_animated_Shop_Menu_figurehead_sly0000-Sheet.png", 0, 6, 0.100f, false));
		FigureheadRenderer_->CreateFrameAnimationCutTexture("IDLE_ANIMATION", FrameAnimation_DESC("UI_shops_animated_Shop_Menu_figurehead_sly0000-Sheet.png", 6, 6, 0.100f, false));
		
		{
			std::vector<unsigned int>BackAni;

			for (int i = 6; i > -1; --i)
			{
				BackAni.push_back(i);
			}
			FigureheadRenderer_->CreateFrameAnimationCutTexture("POPDOWN_ANIMATION", FrameAnimation_DESC("UI_shops_animated_Shop_Menu_figurehead_sly0000-Sheet.png", BackAni, 0.070f, false));
		}


		FigureheadRenderer_->AnimationBindEnd("POPUP_ANIMATION", [=](const FrameAnimation_DESC& _Info)
			{
				FigureheadRenderer_->ChangeFrameAnimation("IDLE_ANIMATION");
			});

		FigureheadRenderer_->ChangeFrameAnimation("POPUP_ANIMATION");
		FigureheadRenderer_->SetScaleModeImage();
		FigureheadRenderer_->GetTransform().SetLocalPosition({ 0, 390, -300 });

		break;
	case SHOP_TYPE::Map_Shop:

		FigureheadRenderer_ = CreateComponent<GameEngineUIRenderer>();
		FigureheadRenderer_->SetTexture("UI_shops_animated_Shop_Menu_figurehead_Mapperwife0000-Sheet.png");
		FigureheadRenderer_->GetTransform().SetLocalScale(FigureheadRenderer_->GetCurTexture()->GetScale());

		FigureheadRenderer_->CreateFrameAnimationCutTexture("POPUP_ANIMATION", FrameAnimation_DESC("UI_shops_animated_Shop_Menu_figurehead_Mapperwife0000-Sheet.png", 0, 11, 0.100f, false));
		FigureheadRenderer_->CreateFrameAnimationCutTexture("IDLE_ANIMATION", FrameAnimation_DESC("UI_shops_animated_Shop_Menu_figurehead_Mapperwife0000-Sheet.png", 11, 11, 0.100f, false));
		
		{
			std::vector<unsigned int>BackAni;

			for (int i = 11; i > -1; --i)
			{
				BackAni.push_back(i);
			}
			FigureheadRenderer_->CreateFrameAnimationCutTexture("POPDOWN_ANIMATION", FrameAnimation_DESC("UI_shops_animated_Shop_Menu_figurehead_Mapperwife0000-Sheet.png", BackAni, 0.100f, false));
		}

		FigureheadRenderer_->AnimationBindEnd("POPUP_ANIMATION", [=](const FrameAnimation_DESC& _Info)
			{
				FigureheadRenderer_->ChangeFrameAnimation("IDLE_ANIMATION");
			});

		FigureheadRenderer_->ChangeFrameAnimation("POPUP_ANIMATION");
		FigureheadRenderer_->SetScaleModeImage();
		FigureheadRenderer_->GetTransform().SetLocalPosition({ 0, 390, -300 });
		
		break;
	default:
		break;
	}
}

void Shop::SetItemListPosition()
{
	for (int i = 0; i < ShopItemList_.size(); ++i)
	{
		if (ShopItemList_[i]->GetSlideItemIndex() == static_cast<int>(SlideItemIndex::First))
		{
			ShopItemList_[i]->GetTransform().SetWorldPosition({ 200, 220 });
			ShopItemList_[i]->SetFontRendererMove();
		}
		if (ShopItemList_[i]->GetSlideItemIndex() == static_cast<int>(SlideItemIndex::Second))
		{
			ShopItemList_[i]->GetTransform().SetWorldPosition({ 200, 120 });
			ShopItemList_[i]->SetFontRendererMove();
		}
		if (ShopItemList_[i]->GetSlideItemIndex() == static_cast<int>(SlideItemIndex::Third))
		{
			ShopItemList_[i]->GetTransform().SetWorldPosition({ 200, 20 });
			ShopItemList_[i]->SetFontRendererMove();
		}
		if (ShopItemList_[i]->GetSlideItemIndex() == static_cast<int>(SlideItemIndex::Fourth))
		{
			ShopItemList_[i]->GetTransform().SetWorldPosition({ 200, -80 });
			ShopItemList_[i]->SetFontRendererMove();
		}
		if (ShopItemList_[i]->GetSlideItemIndex() == static_cast<int>(SlideItemIndex::Fifth))
		{
			ShopItemList_[i]->GetTransform().SetWorldPosition({ 200, -180 });
			ShopItemList_[i]->SetFontRendererMove();
		}
		if (ShopItemList_[i]->GetSlideItemIndex() == static_cast<int>(SlideItemIndex::Sixth))
		{
			ShopItemList_[i]->GetTransform().SetWorldPosition({ 200, -280 });
			ShopItemList_[i]->SetFontRendererMove();
		}
		if (ShopItemList_[i]->GetSlideItemIndex() > static_cast<int>(SlideItemIndex::Sixth))
		{
			ShopItemList_[i]->GetTransform().SetWorldPosition({ 200, -380 });
			ShopItemList_[i]->SetFontRendererMove();
		}
	}
}

void Shop::SetItemListUpdatePosition()
{
	if (ShopArrow_->GetCurrentPointItemIndex() == 1)
	{

		ShopItemList_[ShopArrow_->GetCurrentPointItemIndex() - 1]->GetTransform().SetWorldPosition({ 200, 120 });
		ShopItemList_[ShopArrow_->GetCurrentPointItemIndex() - 1]->SetFontRendererMove();

	}

	else if (ShopArrow_->GetCurrentPointItemIndex() == 0)
	{

	}

	else
	{
		ShopItemList_[ShopArrow_->GetCurrentPointItemIndex() - 2]->GetTransform().SetWorldPosition({ 200, 220 });
		ShopItemList_[ShopArrow_->GetCurrentPointItemIndex() - 2]->SetFontRendererMove();

		ShopItemList_[ShopArrow_->GetCurrentPointItemIndex() - 1]->GetTransform().SetWorldPosition({ 200, 120 });
		ShopItemList_[ShopArrow_->GetCurrentPointItemIndex() - 1]->SetFontRendererMove();
	}

	
	ShopItemList_[ShopArrow_->GetCurrentPointItemIndex()]->GetTransform().SetWorldPosition({ 200, 20 });
	ShopItemList_[ShopArrow_->GetCurrentPointItemIndex()]->SetFontRendererMove();


	if (ShopArrow_->GetCurrentPointItemIndex() + 3 == ShopItemList_.size() -1)
	{
		ShopItemList_[ShopArrow_->GetCurrentPointItemIndex() + 1]->GetTransform().SetWorldPosition({ 200, -80 });
		ShopItemList_[ShopArrow_->GetCurrentPointItemIndex() + 1]->SetFontRendererMove();

		ShopItemList_[ShopArrow_->GetCurrentPointItemIndex() + 2]->GetTransform().SetWorldPosition({ 200, -180 });
		ShopItemList_[ShopArrow_->GetCurrentPointItemIndex() + 2]->SetFontRendererMove();

		ShopItemList_[ShopArrow_->GetCurrentPointItemIndex() + 3]->GetTransform().SetWorldPosition({ 200, -280 });
		ShopItemList_[ShopArrow_->GetCurrentPointItemIndex() + 3]->SetFontRendererMove();
	}

	if (ShopArrow_->GetCurrentPointItemIndex() + 2 == ShopItemList_.size() - 1)
	{
		ShopItemList_[ShopArrow_->GetCurrentPointItemIndex() + 1]->GetTransform().SetWorldPosition({ 200, -80 });
		ShopItemList_[ShopArrow_->GetCurrentPointItemIndex() + 1]->SetFontRendererMove();

		ShopItemList_[ShopArrow_->GetCurrentPointItemIndex() + 2]->GetTransform().SetWorldPosition({ 200, -180 });
		ShopItemList_[ShopArrow_->GetCurrentPointItemIndex() + 2]->SetFontRendererMove();
	}

	if (ShopArrow_->GetCurrentPointItemIndex() + 1 == ShopItemList_.size() - 1)
	{
		ShopItemList_[ShopArrow_->GetCurrentPointItemIndex() + 1]->GetTransform().SetWorldPosition({ 200, -80 });
		ShopItemList_[ShopArrow_->GetCurrentPointItemIndex() + 1]->SetFontRendererMove();
	}
}

void Shop::ShopStillStart(const StateInfo& _Info)
{
}

void Shop::ShopStillUpdate(float _DeltaTime, const StateInfo& _Info)
{
}

void Shop::ShopStillEnd(const StateInfo& _Info)
{
}

void Shop::ShopIdleStart(const StateInfo& _Info)
{

	if (ShopItemList_.size() > 0)
	{
		ItemName_->SetText(ShopItemList_[ShopArrow_->GetCurrentPointItemIndex()]->GetItemName(), 0);
		ItemInfo_->SetText(ShopItemList_[ShopArrow_->GetCurrentPointItemIndex()]->GetItemInfo(), 13);
	}

}

void Shop::ShopIdleUpdate(float _DeltaTime, const StateInfo& _Info)
{
	if (GetAccTime() > 0.5f)
	{
		if (true == GameEngineInput::GetInst()->IsDown("ItemSlideUp"))
		{
			if (ShopArrow_->GetCurrentPointItemIndex() > 0)
			{
				ShopArrow_->SetCurrentPointItemIndex(ShopArrow_->GetCurrentPointItemIndex() - 1);
				ShopArrow_->MoveArrowUp();
				ShopManager_.ChangeState("SHOP_MOVE_UP");
				return;
			}
			else
			{
				isLimitMoveUP_ = true;
				ShopArrow_->MoveArrowUp();

				ShopManager_.ChangeState("MOVE_LIMIT");
				return;
			}
		}

		if (true == GameEngineInput::GetInst()->IsDown("ItemSlideDown"))
		{
			if (ShopArrow_->GetCurrentPointItemIndex() < ShopItemList_.size() - 1)
			{
				ShopArrow_->SetCurrentPointItemIndex(ShopArrow_->GetCurrentPointItemIndex() + 1);
				ShopArrow_->MoveArrowDown();

				ShopManager_.ChangeState("SHOP_MOVE_DOWN");
				return;
			}

			else
			{
				isLimitMoveDown_ = true;
				ShopManager_.ChangeState("MOVE_LIMIT");
				return;

			}
		}

		if (true == GameEngineInput::GetInst()->IsDown("ItemBuy"))
		{

			if (ShopArrow_->GetCurrentPointItemIndex() == ShopItemList_.size() - 1)
			{
				
				CHARM_SLOT Charm =  ShopItemList_[ShopArrow_->GetCurrentPointItemIndex()]->GetShopCharm();
				ITEM_LIST Item = ShopItemList_[ShopArrow_->GetCurrentPointItemIndex()]->GetShopItem();

				if (Charm != CHARM_SLOT::None)
				{
					KnightData::GetInst()->PushKnihgtCharList(Charm);
				}

				if (Item != ITEM_LIST::NONE)
				{
					KnightData::GetInst()->PushKnihgtItemList(Item);
				}

				ShopItemList_[ShopArrow_->GetCurrentPointItemIndex()]->Death();

				ShopItemList_.erase(ShopItemList_.begin() + ShopArrow_->GetCurrentPointItemIndex());

				if (ShopItemList_.size() == 0)
				{
					SetShopPopDown();
					return;
				}

				ShopArrow_->SetCurrentPointItemIndex(ShopArrow_->GetCurrentPointItemIndex() - 1);
				ShopManager_.ChangeState("BUY_ITEM_MOVE_DOWN");
				return;
			}

			else
			{
				CHARM_SLOT Charm = ShopItemList_[ShopArrow_->GetCurrentPointItemIndex()]->GetShopCharm();
				ITEM_LIST Item = ShopItemList_[ShopArrow_->GetCurrentPointItemIndex()]->GetShopItem();

				if (Charm != CHARM_SLOT::None)
				{
					KnightData::GetInst()->PushKnihgtCharList(Charm);
				}

				if (Item != ITEM_LIST::NONE)
				{
					KnightData::GetInst()->PushKnihgtItemList(Item);
				}

				ShopItemList_[ShopArrow_->GetCurrentPointItemIndex()]->Death();

				for (int i = ShopArrow_->GetCurrentPointItemIndex() + 1; i < ShopItemList_.size(); ++i)
				{
					ShopItemList_[i]->SetSlideItemIndex(i - 1);
				}
				ShopItemList_.erase(ShopItemList_.begin() + ShopArrow_->GetCurrentPointItemIndex());

				if (ShopItemList_.size() == 0)
				{
					SetShopPopDown();
					return;
				}

				ShopManager_.ChangeState("BUY_ITEM_MOVE_UP");
				return;
			}
			

		}
	}
}

	

void Shop::ShopIdleEnd(const StateInfo& _Info)
{
}

void Shop::ShopPopDownStart(const StateInfo& _Info)
{
}

void Shop::ShopPopDownUpdate(float _DeltaTime, const StateInfo& _Info)
{
}

void Shop::ShopPopDownEnd(const StateInfo& _Info)
{
}

void Shop::ShopMoveUpStart(const StateInfo& _Info)
{




//	if(ShopArrow_->GetCurrentPointItemIndex() )
}

void Shop::ShopMoveUpUpdate(float _DeltaTime, const StateInfo& _Info)
{
	for (int i = 0; i < ShopItemList_.size(); ++i)
	{

		if (ShopItemList_[ShopArrow_->GetCurrentPointItemIndex()]->GetTransform().GetWorldPosition().y < ShopCurrentItemBackboardRenderer_->GetTransform().GetLocalPosition().y)
		{
			ShopManager_.ChangeState("SHOP_IDLE");
			return;

		}

		float4 CurrentPos = ShopItemList_[i]->GetTransform().GetWorldPosition();
		float4 Move = float4::DOWN  * _DeltaTime * 1000.f ;
		float4 DestPos = ShopItemList_[i]->GetTransform().GetWorldPosition() + Move;
		float4 LerpMove = float4::Lerp(CurrentPos, DestPos, GameEngineTime::GetDeltaTime() * 20.f);

		ShopItemList_[i]->GetTransform().SetWorldPosition(LerpMove);
		ShopItemList_[i]->SetFontRendererMove();

	}
}

void Shop::ShopMoveUpEnd(const StateInfo& _Info)
{
	SetItemListUpdatePosition();
	ItemName_->SetText(ShopItemList_[ShopArrow_->GetCurrentPointItemIndex()]->GetItemName(), 0);
	ItemInfo_->SetText(ShopItemList_[ShopArrow_->GetCurrentPointItemIndex()]->GetItemInfo(), 13);

}

void Shop::ShopMoveDownStart(const StateInfo& _Info)
{

}

void Shop::ShopMoveDownUpdate(float _DeltaTime, const StateInfo& _Info)
{
	for (int i = 0; i < ShopItemList_.size(); ++i)
	{

		//if (ShopItemList_[i]->GetTransform().GetWorldPosition().y > 220 || ShopItemList_[i]->GetTransform().GetWorldPosition().y < -280)
		//{
		//	ShopItemList_[i]->Off();
		//}

		//else
		//{
		//	ShopItemList_[i]->On();
		//}


		float4 CurrentPos = ShopItemList_[i]->GetTransform().GetWorldPosition();
		float4 Move = float4::UP * _DeltaTime * 1000.f;
		float4 DestPos = ShopItemList_[i]->GetTransform().GetWorldPosition() + Move;
		float4 LerpMove = float4::Lerp(CurrentPos, DestPos, GameEngineTime::GetDeltaTime() * 20.f);

		if (ShopItemList_[ShopArrow_->GetCurrentPointItemIndex()]->GetTransform().GetWorldPosition().y > ShopCurrentItemBackboardRenderer_->GetTransform().GetLocalPosition().y)
		{
			ShopManager_.ChangeState("SHOP_IDLE");
			return;
		}

		ShopItemList_[i]->GetTransform().SetWorldPosition(LerpMove);
		ShopItemList_[i]->SetFontRendererMove();

	}
}

void Shop::ShopMoveDownEnd(const StateInfo& _Info)
{
	SetItemListUpdatePosition();
	ItemName_->SetText(ShopItemList_[ShopArrow_->GetCurrentPointItemIndex()]->GetItemName(), 0);
	ItemInfo_->SetText(ShopItemList_[ShopArrow_->GetCurrentPointItemIndex()]->GetItemInfo(), 13);

}

void Shop::ShopBuyItemMoveUpStart(const StateInfo& _Info)
{



}

void Shop::ShopBuyItemMoveUpUpdate(float _DeltaTime, const StateInfo& _Info)
{

	for (int i = ShopArrow_->GetCurrentPointItemIndex(); i < ShopItemList_.size(); ++i)
	{

		//if (ShopItemList_[i]->GetTransform().GetWorldPosition().y > 220 || ShopItemList_[i]->GetTransform().GetWorldPosition().y < -280)
		//{
		//	ShopItemList_[i]->Off();
		//}

		//else
		//{
		//	ShopItemList_[i]->On();
		//}


		if (ShopItemList_[ShopArrow_->GetCurrentPointItemIndex()]->GetTransform().GetWorldPosition().y > ShopCurrentItemBackboardRenderer_->GetTransform().GetLocalPosition().y)
		{
			ShopManager_.ChangeState("SHOP_IDLE");
			return;
		}

		float4 CurrentPos = ShopItemList_[i]->GetTransform().GetWorldPosition();
		float4 Move = float4::UP * _DeltaTime * 700.f;
		float4 DestPos = ShopItemList_[i]->GetTransform().GetWorldPosition() + Move;
		float4 LerpMove = float4::Lerp(CurrentPos, DestPos, GameEngineTime::GetDeltaTime() * 20.f);



		ShopItemList_[i]->GetTransform().SetWorldPosition(LerpMove);
		ShopItemList_[i]->SetFontRendererMove();

	}

}

void Shop::ShopBuyItemMoveUpEnd(const StateInfo& _Info)
{
	SetItemListUpdatePosition();

}

void Shop::ShopBuyItemMoveDownStart(const StateInfo& _Info)
{
}

void Shop::ShopBuyItemMoveDownUpdate(float _DeltaTime, const StateInfo& _Info)
{
	for (int i = 0; i < ShopItemList_.size(); ++i)
	{
		//if (ShopItemList_[i]->GetTransform().GetWorldPosition().y < -280 || ShopItemList_[i]->GetTransform().GetWorldPosition().y > 220)
		//{
		//	ShopItemList_[i]->Off();
		//}

		//else
		//{
		//	ShopItemList_[i]->On();
		//}


		if (ShopItemList_[ShopArrow_->GetCurrentPointItemIndex()]->GetTransform().GetWorldPosition().y < ShopCurrentItemBackboardRenderer_->GetTransform().GetLocalPosition().y)
		{
			ShopManager_.ChangeState("SHOP_IDLE");
			return;

		}

		float4 CurrentPos = ShopItemList_[i]->GetTransform().GetWorldPosition();
		float4 Move = float4::DOWN * _DeltaTime * 700.f;
		float4 DestPos = ShopItemList_[i]->GetTransform().GetWorldPosition() + Move;
		float4 LerpMove = float4::Lerp(CurrentPos, DestPos, GameEngineTime::GetDeltaTime() * 20.f);

		ShopItemList_[i]->GetTransform().SetWorldPosition(LerpMove);
		ShopItemList_[i]->SetFontRendererMove();

	}
}

void Shop::ShopBuyItemMoveDownEnd(const StateInfo& _Info)
{
}

void Shop::ShopItemMoveLimitStart(const StateInfo& _Info)
{
}

void Shop::ShopItemMoveLimitUpdate(float _DeltaTime, const StateInfo& _Info)
{
	LimitMoveTimer_ += _DeltaTime;

	if (isLimitMoveDown_ == true)
	{
		for (int i = 0; i < ShopItemList_.size(); ++i)
		{

	
			float4 CurrentPos = ShopItemList_[i]->GetTransform().GetWorldPosition();
			float4 Move = float4::UP * _DeltaTime * 900.f;
			float4 DestPos = ShopItemList_[i]->GetTransform().GetWorldPosition() + Move;
			float4 LerpMove = float4::Lerp(CurrentPos, DestPos, GameEngineTime::GetDeltaTime() * 20.f);

			ShopItemList_[i]->GetTransform().SetWorldPosition(LerpMove);
			ShopItemList_[i]->SetFontRendererMove();

		}
	}

	if (isLimitMoveUP_ == true)
	{
		for (int i = 0; i < ShopItemList_.size(); ++i)
		{

			float4 CurrentPos = ShopItemList_[i]->GetTransform().GetWorldPosition();
			float4 Move = float4::DOWN * _DeltaTime * 900.f;
			float4 DestPos = ShopItemList_[i]->GetTransform().GetWorldPosition() + Move;
			float4 LerpMove = float4::Lerp(CurrentPos, DestPos, GameEngineTime::GetDeltaTime() * 20.f);

			ShopItemList_[i]->GetTransform().SetWorldPosition(LerpMove);
			ShopItemList_[i]->SetFontRendererMove();
		}
	}

	if (LimitMoveTimer_ > 0.2f)
	{
		LimitMoveTimer_ = 0.0f;
		ShopManager_.ChangeState("MOVE_LIMIT_RETURN");

	}
}

void Shop::ShopItemMoveLimitEnd(const StateInfo& _Info)
{
}

void Shop::ShopItemMoveLimitReturnStart(const StateInfo& _Info)
{
}

void Shop::ShopItemMoveLimitReturnUpdate(float _DeltaTime, const StateInfo& _Info)
{
	LimitMoveTimer_ += _DeltaTime;

	if (isLimitMoveDown_ == true)
	{
		for (int i = 0; i < ShopItemList_.size(); ++i)
		{


			float4 CurrentPos = ShopItemList_[i]->GetTransform().GetWorldPosition();
			float4 Move = float4::DOWN *_DeltaTime * 900.f;
			float4 DestPos = ShopItemList_[i]->GetTransform().GetWorldPosition() + Move;
			float4 LerpMove = float4::Lerp(CurrentPos, DestPos, GameEngineTime::GetDeltaTime() * 20.f);

			ShopItemList_[i]->GetTransform().SetWorldPosition(LerpMove);
			ShopItemList_[i]->SetFontRendererMove();

		}
	}

	if (isLimitMoveUP_ == true)
	{
		for (int i = 0; i < ShopItemList_.size(); ++i)
		{

			float4 CurrentPos = ShopItemList_[i]->GetTransform().GetWorldPosition();
			float4 Move = float4::UP * _DeltaTime * 900.f;
			float4 DestPos = ShopItemList_[i]->GetTransform().GetWorldPosition() + Move;
			float4 LerpMove = float4::Lerp(CurrentPos, DestPos, GameEngineTime::GetDeltaTime() * 20.f);

			ShopItemList_[i]->GetTransform().SetWorldPosition(LerpMove);
			ShopItemList_[i]->SetFontRendererMove();
		}
	}

	if (LimitMoveTimer_ > 0.2f)
	{
		LimitMoveTimer_ = 0.0f;
		ShopManager_.ChangeState("SHOP_IDLE");

	}
}

void Shop::ShopItemMoveLimitReturnEnd(const StateInfo& _Info)
{
	SetItemListUpdatePosition();

	isLimitMoveDown_ = false;
	isLimitMoveDown_ = false;

}
