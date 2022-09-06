#include "PreCompile.h"
#include "Shop.h"

Shop::Shop() 
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
	ShopBackboardRenderer_->GetPixelData().MulColor.a = 0.7f;
	ShopBackboardRenderer_->GetTransform().SetLocalPosition({ 0, -50 });

	ShopCurrentItemBackboardRenderer_ = CreateComponent<GameEngineUIRenderer>();
	ShopCurrentItemBackboardRenderer_->SetTexture("itemBack.png");
	ShopCurrentItemBackboardRenderer_->GetTransform().SetLocalScale(ShopCurrentItemBackboardRenderer_->GetCurTexture()->GetScale());
	ShopCurrentItemBackboardRenderer_->GetTransform().SetWorldPosition({ -100, 20 });

	ShopTopDividerRenderer_ = CreateComponent<GameEngineUIRenderer>();
	ShopTopDividerRenderer_->SetTexture("Inv_0017_divider.png");
	ShopTopDividerRenderer_->GetTransform().SetLocalScale(ShopTopDividerRenderer_->GetCurTexture()->GetScale());
	ShopTopDividerRenderer_->GetTransform().SetWorldPosition({ -100, 0 });

	ShopBottomDividerRenderer_ = CreateComponent<GameEngineUIRenderer>();
	ShopBottomDividerRenderer_->SetTexture("Inv_0017_divider.png");
	ShopBottomDividerRenderer_->GetTransform().SetLocalScale(ShopBottomDividerRenderer_->GetCurTexture()->GetScale());
	ShopBottomDividerRenderer_->GetTransform().SetWorldPosition({ -100, 0 });

	ShopBottomMaskRederer = CreateComponent<GameEngineUIRenderer>();
	ShopBottomMaskRederer->SetTexture("shop_mask_bottom.png");
	ShopBottomMaskRederer->GetTransform().SetLocalScale({600, 200});
	ShopBottomMaskRederer->GetTransform().SetLocalPosition({ 0, -350 });

	ShopTopMaskRenderer_ = CreateComponent<GameEngineUIRenderer>();
	ShopTopMaskRenderer_->SetTexture("shop_mask_top.png");
	ShopTopMaskRenderer_->GetTransform().SetLocalScale({ 600, 200 });
	ShopTopMaskRenderer_->GetTransform().SetLocalPosition({ 0,190 });

	ShopTopRenderer_ = CreateComponent<GameEngineUIRenderer>();
	ShopTopRenderer_->SetTexture("UI_shops_animated_Shop_Menu_top0000-Sheet.png");
	ShopTopRenderer_->GetTransform().SetLocalScale(ShopTopRenderer_->GetCurTexture()->GetScale());
	ShopTopRenderer_->CreateFrameAnimationCutTexture("POPUP_ANIMATION", FrameAnimation_DESC("UI_shops_animated_Shop_Menu_top0000-Sheet.png", 0, 8, 0.100f, false));
	ShopTopRenderer_->CreateFrameAnimationCutTexture("IDLE_ANIMATION", FrameAnimation_DESC("UI_shops_animated_Shop_Menu_top0000-Sheet.png", 8, 8, 0.100f, false));
	ShopTopRenderer_->ChangeFrameAnimation("POPUP_ANIMATION");
	ShopTopRenderer_->SetScaleModeImage();
	ShopTopRenderer_->GetTransform().SetLocalPosition({ 0,190 });

	ShopTopRenderer_->AnimationBindEnd("POPUP_ANIMATION", [=](const FrameAnimation_DESC& _Info)
		{
			ShopTopRenderer_->ChangeFrameAnimation("IDLE_ANIMATION");
		});

	ShopBottomRenderer_ = CreateComponent<GameEngineUIRenderer>();
	ShopBottomRenderer_->SetTexture("UI_shops_animated_Shop_Menu_bottom0000-Sheet.png");
	ShopBottomRenderer_->GetTransform().SetLocalScale(ShopBottomRenderer_->GetCurTexture()->GetScale());
	ShopBottomRenderer_->CreateFrameAnimationCutTexture("POPUP_ANIMATION", FrameAnimation_DESC("UI_shops_animated_Shop_Menu_bottom0000-Sheet.png", 0, 8, 0.100f, false));
	ShopBottomRenderer_->CreateFrameAnimationCutTexture("IDLE_ANIMATION", FrameAnimation_DESC("UI_shops_animated_Shop_Menu_bottom0000-Sheet.png", 8, 8, 0.100f, false));
	ShopBottomRenderer_->ChangeFrameAnimation("POPUP_ANIMATION");
	ShopBottomRenderer_->SetScaleModeImage();
	ShopBottomRenderer_->GetTransform().SetLocalPosition({ 0, -350 });

	ShopBottomRenderer_->AnimationBindEnd("POPUP_ANIMATION", [=](const FrameAnimation_DESC& _Info)
		{
			ShopBottomRenderer_->ChangeFrameAnimation("IDLE_ANIMATION");
		});

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

		FigureheadRenderer_->AnimationBindEnd("POPUP_ANIMATION", [=](const FrameAnimation_DESC& _Info)
			{
				FigureheadRenderer_->ChangeFrameAnimation("IDLE_ANIMATION");
			});

		FigureheadRenderer_->ChangeFrameAnimation("POPUP_ANIMATION");

		FigureheadRenderer_->SetScaleModeImage();
		FigureheadRenderer_->GetTransform().SetLocalPosition({ 0, 390 });
		break;
	case SHOP_TYPE::Map_Shop:

		FigureheadRenderer_ = CreateComponent<GameEngineUIRenderer>();
		FigureheadRenderer_->SetTexture("UI_shops_animated_Shop_Menu_figurehead_Mapperwife0000-Sheet.png");
		FigureheadRenderer_->GetTransform().SetLocalScale(FigureheadRenderer_->GetCurTexture()->GetScale());

		FigureheadRenderer_->CreateFrameAnimationCutTexture("POPUP_ANIMATION", FrameAnimation_DESC("UI_shops_animated_Shop_Menu_figurehead_Mapperwife0000-Sheet.png", 0, 11, 0.100f, false));
		FigureheadRenderer_->CreateFrameAnimationCutTexture("IDLE_ANIMATION", FrameAnimation_DESC("UI_shops_animated_Shop_Menu_figurehead_Mapperwife0000-Sheet.png", 11, 11, 0.100f, false));
		
		FigureheadRenderer_->AnimationBindEnd("POPUP_ANIMATION", [=](const FrameAnimation_DESC& _Info)
			{
				FigureheadRenderer_->ChangeFrameAnimation("IDLE_ANIMATION");
			});

		FigureheadRenderer_->ChangeFrameAnimation("POPUP_ANIMATION");

		FigureheadRenderer_->SetScaleModeImage();
		FigureheadRenderer_->GetTransform().SetLocalPosition({ 0, 390 });
		
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
			ShopItemList_[i]->GetTransform().SetWorldPosition({ 270, 220 });
			ShopItemList_[i]->SetFontRendererMove();
		}
		if (ShopItemList_[i]->GetSlideItemIndex() == static_cast<int>(SlideItemIndex::Second))
		{
			ShopItemList_[i]->GetTransform().SetWorldPosition({ 270, 120 });
			ShopItemList_[i]->SetFontRendererMove();
		}
		if (ShopItemList_[i]->GetSlideItemIndex() == static_cast<int>(SlideItemIndex::Third))
		{
			ShopItemList_[i]->GetTransform().SetWorldPosition({ 270, 20 });
			ShopItemList_[i]->SetFontRendererMove();
		}
		if (ShopItemList_[i]->GetSlideItemIndex() == static_cast<int>(SlideItemIndex::Fourth))
		{
			ShopItemList_[i]->GetTransform().SetWorldPosition({ 270, -80 });
			ShopItemList_[i]->SetFontRendererMove();
		}
		if (ShopItemList_[i]->GetSlideItemIndex() == static_cast<int>(SlideItemIndex::Fifth))
		{
			ShopItemList_[i]->GetTransform().SetWorldPosition({ 270, -180 });
			ShopItemList_[i]->SetFontRendererMove();
		}
		if (ShopItemList_[i]->GetSlideItemIndex() == static_cast<int>(SlideItemIndex::Sixth))
		{
			ShopItemList_[i]->GetTransform().SetWorldPosition({ 270, -280 });
			ShopItemList_[i]->SetFontRendererMove();
		}
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
}

void Shop::ShopIdleUpdate(float _DeltaTime, const StateInfo& _Info)
{
	if (true == GameEngineInput::GetInst()->IsDown("ItemSlideUp"))
	{
		ShopManager_.ChangeState("SHOP_MOVE_UP");
		return;
	}

	if (true == GameEngineInput::GetInst()->IsDown("ItemSlideDown"))
	{
		ShopManager_.ChangeState("SHOP_MOVE_DOWN");
		return;
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
	for (int i = 0; i < ShopItemList_.size(); ++i)
	{
		int Setindex = (static_cast<int>(ShopItemList_[i]->isCurrentSlideItemCenter())) - 1;

		if (Setindex == (static_cast<int>(SlideItemIndex::Min)))
		{
			Setindex = (static_cast<int>(SlideItemIndex::First));
		}

		else if (Setindex == (ShopItemList_.size()))
		{
			Setindex = ShopItemList_.size() - 1;
		}

		ShopItemList_[i]->SetSlideItemIndex(Setindex);
	}
}

void Shop::ShopMoveUpUpdate(float _DeltaTime, const StateInfo& _Info)
{
	for (int i = 0; i < ShopItemList_.size(); ++i)
	{
		if (ShopItemList_[i]->isCurrentSlideItemCenter() == true)
		{
			if (ShopItemList_[i]->GetTransform().GetWorldPosition().y > 20)
			{
				ShopManager_.ChangeState("IDLE");
			}
		}

		ShopItemList_[i]->GetTransform().SetWorldMove(float4::DOWN * _DeltaTime * 700.f);
	}
}

void Shop::ShopMoveUpEnd(const StateInfo& _Info)
{
}

void Shop::ShopMoveDownStart(const StateInfo& _Info)
{
}

void Shop::ShopMoveDownUpdate(float _DeltaTime, const StateInfo& _Info)
{
}

void Shop::ShopMoveDownEnd(const StateInfo& _Info)
{
}
