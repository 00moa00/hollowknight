#include "PreCompile.h"
#include "Iselda.h"

Iselda::Iselda()
{
}

Iselda::~Iselda()
{
}

void Iselda::Start()
{
	SetNPCName("이셀다");
	SetNPCType(NPC_TYPE::Shop);

	GetTransform().SetWorldPosition({ 1040, -760.f, static_cast<int>(Z_ORDER::NPC) });
	CreateNameFontRenderer();
	CreatePromptSet();
	//GetPromptSet()->GetTransform().SetLocalPosition({0, 150.f});
	//GetPromptSet()->GetCollision()->GetTransform().SetWorldPosition(GetTransform().GetWorldPosition());
	//GetPromptSet()->SetParent(this);

	CreateRendererComponent("Iselda Cln_idle0013-Sheet.png", 0);
	GetRenderer()->CreateFrameAnimationCutTexture("IDLE_ANIMATION", FrameAnimation_DESC("Iselda Cln_idle0013-Sheet.png", 0, 4, 0.100f));
	GetRenderer()->SetScaleModeImage();
	GetRenderer()->ChangeFrameAnimation("IDLE_ANIMATION");
	//GetRenderer()->GetPixelData().MulColor = { 1,1,1,1 };

	CreateCollisionComponent(float4{ 600, 120, 1 }, static_cast<int>(OBJECTORDER::NPC));

	CreateDialogueSet();
	
	GetDialogueSet()->PushDialogue("그 모든 곳들 중에서 우리는 하필 이 음산한 마을을 선택했어요.나는 잠깐 일 거라 생각했는데, 남편이 그 오래된 폐허에 사로잡혔어요.");
	GetDialogueSet()->PushDialogue("이제 그는 모든 시간을 저기 아래서 보내고 있어요.그는 지도 제작이 견실한 사업이라고 주장하지만, 당신 아니면 누가 사겠어요?");

	GetDialogueSet()->SetDialogueOff();

	MapShop_ = GetLevel()->CreateActor<Shop>();
	MapShop_->SetShopType(SHOP_TYPE::Map_Shop);
	MapShop_->CreateFigurehead(SHOP_TYPE::Map_Shop);
	MapShop_->GetTransform().SetWorldPosition({400, 0});

	MapShop_->GetShopItemList().push_back(GetLevel()->CreateActor<ShopItem>());
	MapShop_->GetShopItemList().back()->CreateShopItem(SHOP_ITEM::Crosslaod_Map);
	MapShop_->GetShopItemList().back()->SetParent(MapShop_);
	MapShop_->GetShopItemList().back()->SetSlideItemIndex(0);

	MapShop_->GetShopItemList().push_back(GetLevel()->CreateActor<ShopItem>());
	MapShop_->GetShopItemList().back()->CreateShopItem(SHOP_ITEM::Mark_of_Pride);
	MapShop_->GetShopItemList().back()->SetParent(MapShop_);
	MapShop_->GetShopItemList().back()->SetSlideItemIndex(1);


	MapShop_->GetShopItemList().push_back(GetLevel()->CreateActor<ShopItem>());
	MapShop_->GetShopItemList().back()->CreateShopItem(SHOP_ITEM::MaskPiece);
	MapShop_->GetShopItemList().back()->SetParent(MapShop_);
	MapShop_->GetShopItemList().back()->SetSlideItemIndex(2);

	MapShop_->GetShopItemList().push_back(GetLevel()->CreateActor<ShopItem>());
	MapShop_->GetShopItemList().back()->CreateShopItem(SHOP_ITEM::Wayward_Compass);
	MapShop_->GetShopItemList().back()->SetParent(MapShop_);
	MapShop_->GetShopItemList().back()->SetSlideItemIndex(3);

	MapShop_->GetShopItemList().push_back(GetLevel()->CreateActor<ShopItem>());
	MapShop_->GetShopItemList().back()->CreateShopItem(SHOP_ITEM::Wayward_Compass);
	MapShop_->GetShopItemList().back()->SetParent(MapShop_);
	MapShop_->GetShopItemList().back()->SetSlideItemIndex(4);

	MapShop_->GetShopItemList().push_back(GetLevel()->CreateActor<ShopItem>());
	MapShop_->GetShopItemList().back()->CreateShopItem(SHOP_ITEM::Wayward_Compass);
	MapShop_->GetShopItemList().back()->SetParent(MapShop_);
	MapShop_->GetShopItemList().back()->SetSlideItemIndex(5);

	MapShop_->SetItemListPosition();
	MapShop_->Off();
	//MapShop_->GetShopItemList().back()->GetTransform().SetWorldPosition({270,0});
	//MapShop_->GetShopItemList().back()->SetFontRendererMove();


	IseldaManager_.CreateStateMember("IDLE"
		, std::bind(&Iselda::IseldaIdleUpdate, this, std::placeholders::_1, std::placeholders::_2)
		, std::bind(&Iselda::IseldaIdleStart, this, std::placeholders::_1)
		, std::bind(&Iselda::IseldaIdleEnd, this, std::placeholders::_1));

	IseldaManager_.CreateStateMember("CHANGE_DIR"
		, std::bind(&Iselda::IseldaChangeDirUpdate, this, std::placeholders::_1, std::placeholders::_2)
		, std::bind(&Iselda::IseldaChangeDirStart, this, std::placeholders::_1)
		, std::bind(&Iselda::IseldaChangeDirEnd, this, std::placeholders::_1));

	IseldaManager_.CreateStateMember("LEAVE"
		, std::bind(&Iselda::IseldaChangeLeaveUpdate, this, std::placeholders::_1, std::placeholders::_2)
		, std::bind(&Iselda::IseldaChangeLeaveStart, this, std::placeholders::_1)
		, std::bind(&Iselda::IseldaChangeLeaveEnd, this, std::placeholders::_1));

	IseldaManager_.CreateStateMember("OPEN_SHOP"
		, std::bind(&Iselda::IseldaShopOpenUpdate, this, std::placeholders::_1, std::placeholders::_2)
		, std::bind(&Iselda::IseldaShopOpenStart, this, std::placeholders::_1)
		, std::bind(&Iselda::IseldaShopOpenEnd, this, std::placeholders::_1));


	IseldaManager_.ChangeState("IDLE");

}

void Iselda::Update(float _DeltaTime)
{
	CheckDirToKnight();
	IseldaManager_.Update(_DeltaTime);
}

bool Iselda::ThisVSKnightCollision(GameEngineCollision* _This, GameEngineCollision* _Other)
{
	return true;
}

void Iselda::IseldaWaitStart(const StateInfo& _Info)
{
}

void Iselda::IseldaWaitUpdate(float _DeltaTime, const StateInfo& _Info)
{
	if (GetCollision()->IsCollision(CollisionType::CT_OBB2D, OBJECTORDER::Knight, CollisionType::CT_OBB2D,
		std::bind(&Iselda::ThisVSKnightCollision, this, std::placeholders::_1, std::placeholders::_2)) == true)
	{
		IseldaManager_.ChangeState("IDLE");
	}
}

void Iselda::IseldaWaitEnd(const StateInfo& _Info)
{
}

void Iselda::IseldaIdleStart(const StateInfo& _Info)
{
}

void Iselda::IseldaIdleUpdate(float _DeltaTime, const StateInfo& _Info)
{
}

void Iselda::IseldaIdleEnd(const StateInfo& _Info)
{
}

void Iselda::IseldaChangeDirStart(const StateInfo& _Info)
{
}

void Iselda::IseldaChangeDirUpdate(float _DeltaTime, const StateInfo& _Info)
{
}

void Iselda::IseldaChangeDirEnd(const StateInfo& _Info)
{
}

void Iselda::IseldaChangeLeaveStart(const StateInfo& _Info)
{
}

void Iselda::IseldaChangeLeaveUpdate(float _DeltaTime, const StateInfo& _Info)
{
}

void Iselda::IseldaChangeLeaveEnd(const StateInfo& _Info)
{
}

void Iselda::IseldaShopOpenStart(const StateInfo& _Info)
{
}

void Iselda::IseldaShopOpenUpdate(float _DeltaTime, const StateInfo& _Info)
{
}

void Iselda::IseldaShopOpenEnd(const StateInfo& _Info)
{
}
