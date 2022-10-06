#include "PreCompile.h"
#include "Iselda.h"

#include "HollowKnightLevel.h"

Iselda::Iselda()
	:
	ShopToIdleEnd_(false),
	OpenShop_(false),

	ShopIndexCount_(0),

	PrevDir_(),

	MapShop_(nullptr)
{
}

Iselda::~Iselda()
{
}

void Iselda::Start()
{
	SetNPCName("이셀다");
	SetNPCType(NPC_TYPE::Shop);

	GetTransform().SetWorldPosition({ 1100, -730.f, static_cast<int>(Z_ORDER::NPC) });
	CreateNameFontRenderer();
	CreatePromptSet();

	PromptSet* ShopPromptSet_ = GetLevel()->CreateActor<PromptSet>();
	ShopPromptSet_->CreatePrompSet(PromptSetType::SHOP);
	ShopPromptSet_->SetParent(this);
	ShopPromptSet_->GetTransform().SetLocalPosition({ -220.f, 220.f });
	ShopPromptSet_->GetCollision()->GetTransform().SetLocalPosition({ 0.f, -300.f });
	ShopPromptSet_->GetCollision()->GetTransform().SetLocalScale({ 200.f, 100.f });


	GetPromptSet()->GetTransform().SetLocalPosition({50.f, 220.f});
	GetPromptSet()->GetCollision()->GetTransform().SetLocalPosition({ 0, -300.f });
	GetPromptSet()->GetCollision()->GetTransform().SetLocalScale({ 280.f, 100.f });
	//GetPromptSet()->SetParent(this);

	CreateRendererComponent("Iselda Cln_idle0013-Sheet.png", 0);
	GetRenderer()->CreateFrameAnimationCutTexture("IDLE_ANIMATION", FrameAnimation_DESC("Iselda Cln_idle0013-Sheet.png", 0, 4, 0.100f));
	
	GetRenderer()->CreateFrameAnimationCutTexture("IDLE_RIGHT_ANIMATION", FrameAnimation_DESC("Iselda Cln_turn0001-Sheet.png", 4, 4, 0.100f));

	
	GetRenderer()->CreateFrameAnimationCutTexture("CHANGE_DIR_ANIMATION", FrameAnimation_DESC("Iselda Cln_turn0001-Sheet.png", 0, 4, 0.100f, false));
	
	{
		std::vector<unsigned int> CustomAni;

		for (int i = 4; i > -1 ; --i)
		{
			CustomAni.push_back(i);
		}

		GetRenderer()->CreateFrameAnimationCutTexture("CHANGE_RETURN_DIR_ANIMATION", FrameAnimation_DESC("Iselda Cln_turn0001-Sheet.png", CustomAni, 0.100f, false));
	}
	
	
	
	GetRenderer()->CreateFrameAnimationCutTexture("TALK_START_ANIMATION", FrameAnimation_DESC("Iselda Cln_talk_right0000-Sheet.png", 0, 1, 0.100f, false));
	GetRenderer()->CreateFrameAnimationCutTexture("TALK_ANIMATION", FrameAnimation_DESC("Iselda Cln_talk_right0000-Sheet.png", 2, 7, 0.100f, true));

	
	GetRenderer()->CreateFrameAnimationCutTexture("SHOP_IDLE_ANIMATION", FrameAnimation_DESC("Iselda Cln_Shop_0006-Sheet.png", 0, 5, 0.100f));
	GetRenderer()->CreateFrameAnimationCutTexture("IDLE_TO_SHOP_ANIMATION", FrameAnimation_DESC("Iselda Cln_idle_to_Shop0000-Sheet.png", 0, 5, 0.100f));
	GetRenderer()->CreateFrameAnimationCutTexture("SHOP_TO_IDLE_ANIMATION", FrameAnimation_DESC("Iselda Cln_Shop_to_idle0000-Sheet.png", 0, 4, 0.100f));

	GetRenderer()->AnimationBindEnd("IDLE_TO_SHOP_ANIMATION", [=](const FrameAnimation_DESC& _Info)
		{
			GetRenderer()->ChangeFrameAnimation("SHOP_IDLE_ANIMATION");

		});

	GetRenderer()->AnimationBindEnd("SHOP_TO_IDLE_ANIMATION", [=](const FrameAnimation_DESC& _Info)
		{
			ShopToIdleEnd_ = true;

			//GetRenderer()->ChangeFrameAnimation("SHOP_IDLE_ANIMATION");

		});

	GetRenderer()->AnimationBindEnd("TALK_START_ANIMATION", [=](const FrameAnimation_DESC& _Info)
		{
			GetRenderer()->ChangeFrameAnimation("TALK_ANIMATION");

			//GetRenderer()->ChangeFrameAnimation("SHOP_IDLE_ANIMATION");

		});


	GetRenderer()->AnimationBindEnd("CHANGE_DIR_ANIMATION", [=](const FrameAnimation_DESC& _Info)
		{

		
			GetRenderer()->ChangeFrameAnimation("IDLE_RIGHT_ANIMATION");

		});

	GetRenderer()->AnimationBindEnd("CHANGE_RETURN_DIR_ANIMATION", [=](const FrameAnimation_DESC& _Info)
		{
			GetRenderer()->ChangeFrameAnimation("IDLE_ANIMATION");

		});

	GetRenderer()->SetScaleModeImage();
	GetRenderer()->ChangeFrameAnimation("IDLE_ANIMATION");
	//GetRenderer()->GetPixelData().MulColor = { 1,1,1,1 };

	CreateCollisionComponent(float4{ 600, 120, 1 }, static_cast<int>(COLLISION_ORDER::NPC));

	CreateDialogueSet();
	
	GetDialogueSet()->PushDialogue("그 모든 곳들 중에서 우리는 하필 이 음산한 마을을 선택했어요.나는 잠깐 일 거라 생각했는데, 남편이 그 오래된 폐허에 사로잡혔어요.");
	GetDialogueSet()->PushDialogue("이제 그는 모든 시간을 저기 아래서 보내고 있어요.그는 지도 제작이 견실한 사업이라고 주장하지만, 당신 아니면 누가 사겠어요?");

	GetDialogueSet()->SetDialogueOff();

	MapShop_ = GetLevel()->CreateActor<Shop>();
	MapShop_->SetShopType(SHOP_TYPE::Map_Shop);
	MapShop_->CreateFigurehead(SHOP_TYPE::Map_Shop);
	MapShop_->GetTransform().SetWorldPosition({400, 0});

	//MapShop_->GetShopItemList().push_back(GetLevel()->CreateActor<ShopItem>());
	//MapShop_->GetShopItemList().back()->CreateShopItem(SHOP_ITEM::MaskPiece);
	//MapShop_->GetShopItemList().back()->SetParent(MapShop_);
	//MapShop_->GetShopItemList().back()->SetSlideItemIndex(0);

	//MapShop_->GetShopItemList().push_back(GetLevel()->CreateActor<ShopItem>());
	//MapShop_->GetShopItemList().back()->CreateShopItem(SHOP_ITEM::MaskPiece);
	//MapShop_->GetShopItemList().back()->SetParent(MapShop_);
	//MapShop_->GetShopItemList().back()->SetSlideItemIndex(1);

	//MapShop_->GetShopItemList().push_back(GetLevel()->CreateActor<ShopItem>());
	//MapShop_->GetShopItemList().back()->CreateShopItem(SHOP_ITEM::MaskPiece);
	//MapShop_->GetShopItemList().back()->SetParent(MapShop_);
	//MapShop_->GetShopItemList().back()->SetSlideItemIndex(2);

	//MapShop_->GetShopItemList().push_back(GetLevel()->CreateActor<ShopItem>());
	//MapShop_->GetShopItemList().back()->CreateShopItem(SHOP_ITEM::MaskPiece);
	//MapShop_->GetShopItemList().back()->SetParent(MapShop_);
	//MapShop_->GetShopItemList().back()->SetSlideItemIndex(3);

	MapShop_->GetShopItemList().push_back(GetLevel()->CreateActor<ShopItem>());
	MapShop_->GetShopItemList().back()->CreateShopItem(SHOP_ITEM::Crosslaod_Map);
	MapShop_->GetShopItemList().back()->SetParent(MapShop_);
	MapShop_->GetShopItemList().back()->SetSlideItemIndex(0);

	MapShop_->GetShopItemList().push_back(GetLevel()->CreateActor<ShopItem>());
	MapShop_->GetShopItemList().back()->CreateShopItem(SHOP_ITEM::Wayward_Compass);
	MapShop_->GetShopItemList().back()->SetParent(MapShop_);
	MapShop_->GetShopItemList().back()->SetSlideItemIndex(1);

	MapShop_->GetShopItemList().push_back(GetLevel()->CreateActor<ShopItem>());
	MapShop_->GetShopItemList().back()->CreateShopItem(SHOP_ITEM::Dreamshield);
	MapShop_->GetShopItemList().back()->SetParent(MapShop_);
	MapShop_->GetShopItemList().back()->SetSlideItemIndex(2);


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

	IseldaManager_.CreateStateMember("TALKING"
		, std::bind(&Iselda::IseldaTalkingUpdate, this, std::placeholders::_1, std::placeholders::_2)
		, std::bind(&Iselda::IseldaTalkingStart, this, std::placeholders::_1)
		, std::bind(&Iselda::IseldaTalkingEnd, this, std::placeholders::_1));


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

void Iselda::CheckDirToKnight()
{
	float4 KnightPos = GetLevel<HollowKnightLevel>()->GetKnight()->GetTransform().GetWorldPosition();
	float4 DirPos = KnightPos - this->GetTransform().GetWorldPosition();
	DirPos.Normalize();



	if (DirPos.x > 0.0f)
	{
		SetMoveDirection(float4::RIGHT);

		if (PrevDir_.CompareInt2D(float4::RIGHT) == false)
		{
			GetRenderer()->ChangeFrameAnimation("CHANGE_DIR_ANIMATION");

			//IseldaManager_.ChangeState("CHANGE_DIR");
			//return;
		}

		PrevDir_ = float4::RIGHT;

		//GetRenderer()->GetTransform().PixLocalNegativeX();
	}

	else if (DirPos.x < 0.0f)
	{
		SetMoveDirection(float4::LEFT);
		
		if (PrevDir_.CompareInt2D(float4::LEFT) == false)
		{
			GetRenderer()->ChangeFrameAnimation("CHANGE_RETURN_DIR_ANIMATION");

			//IseldaManager_.ChangeState("CHANGE_DIR");
			//return;
		}

		PrevDir_ = float4::LEFT;
	}

}

void Iselda::StartTalking()
{
	int RamSound = GameEngineRandom::MainRandom.RandomInt(0, 2);

	if (RamSound == 0)
	{
		GameEngineSound::SoundPlayOneShot("Iselda_Shop_talk_01.ogg");
	}
	else if (RamSound == 1)
	{
		GameEngineSound::SoundPlayOneShot("Iselda_Shop_talk_02.ogg");

	}
	else if (RamSound == 2)
	{
		GameEngineSound::SoundPlayOneShot("Iselda_Shop_talk_03.ogg");
	}

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
	if (GetCollision()->IsCollision(CollisionType::CT_OBB2D, COLLISION_ORDER::Knight, CollisionType::CT_OBB2D,
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
	if (_Info.PrevState != "TALKING")
	{
		GetRenderer()->ChangeFrameAnimation("IDLE_ANIMATION");

	}

}

void Iselda::IseldaIdleUpdate(float _DeltaTime, const StateInfo& _Info)
{
	if (isTalking() == true)
	{
		IseldaManager_.ChangeState("TALKING");

	}
}

void Iselda::IseldaIdleEnd(const StateInfo& _Info)
{
}

void Iselda::IseldaChangeDirStart(const StateInfo& _Info)
{
//	GetRenderer()->ChangeFrameAnimation("CHANGE_DIR_ANIMATION");

	if (_Info.PrevState == "IDLE")
	{
		if (GetMoveDirection().CompareInt2D(float4::RIGHT))
		{
			GetRenderer()->ChangeFrameAnimation("CHANGE_DIR_ANIMATION");

		}
		else
		{
			GetRenderer()->ChangeFrameAnimation("CHANGE_RETURN_DIR_ANIMATION");

		}
	}
	{
		GetRenderer()->ChangeFrameAnimation("TALK_ANIMATION");

	}

}

void Iselda::IseldaChangeDirUpdate(float _DeltaTime, const StateInfo& _Info)
{

}

void Iselda::IseldaChangeDirEnd(const StateInfo& _Info)
{
}



void Iselda::IseldaShopOpenStart(const StateInfo& _Info)
{
	GetRenderer()->ChangeFrameAnimation("IDLE_TO_SHOP_ANIMATION");

}

void Iselda::IseldaShopOpenUpdate(float _DeltaTime, const StateInfo& _Info)
{
	if (ShopToIdleEnd_ == true)
	{
		ShopToIdleEnd_ = false;
		IseldaManager_.ChangeState("IDLE");
	}
	//GetiShop
}

void Iselda::IseldaShopOpenEnd(const StateInfo& _Info)
{

}

void Iselda::IseldaTalkingStart(const StateInfo& _Info)
{
	GetRenderer()->ChangeFrameAnimation("TALK_START_ANIMATION");

}

void Iselda::IseldaTalkingUpdate(float _DeltaTime, const StateInfo& _Info)
{
	if (isTalking() == false)
	{
		IseldaManager_.ChangeState("IDLE");
		GetRenderer()->ChangeFrameAnimation("TALK_ANIMATION");
	}
}

void Iselda::IseldaTalkingEnd(const StateInfo& _Info)
{
}
