#include "PreCompile.h"
#include "CharmPage.h"
#include "GlobalContentsValue.h"
#include "PointActorComponent.h"

#include "KnightData.h"

#include <GameEngineBase/magic_enum.hpp>
#include <GameEngineBase/magic_enum_format.hpp>
#include <GameEngineBase/magic_enum_fuse.hpp>

CharmPage::CharmPage() 
	:
	CharmSize_(0),

	NotchesFont_(nullptr),
	Line_(nullptr)
{
}

CharmPage::~CharmPage() 
{
}

void CharmPage::Start()
{
	//何利 浇吩
	AllCharmSlot_.reserve(40);

	float MaginY = 0.f;
	float MaginX = 0.f;
	float AddMaginX = 0.0f;

	int SlotNum = 0;

	for (int y = 0; y < 4; ++y)
	{
		for (int x = 0; x < 10; ++x)
		{
			if (y == 1 || y == 3)
			{
				AddMaginX = 70.f;
			}
			else
			{
				AddMaginX = 0.f;
			}

			int ValueNum = SlotNum;
			auto CharmEnum = magic_enum::enum_cast<CHARM_SLOT>(ValueNum);

			std::string EnumString;

			auto Name = magic_enum::enum_name(CharmEnum.value());
			EnumString = static_cast<std::string>(Name);

			
			std::string FilePathNum = std::to_string(ValueNum);
			AllCharmSlot_.push_back(GetLevel()->CreateActor<CharmSlot>());
			AllCharmSlot_[ValueNum]->CreateCharmSlot(EnumString, "Charm_" + FilePathNum + ".png", CharmState{ValueNum , 0, false, false}, CharmEnum.value());
			AllCharmSlot_[ValueNum]->GetTransform().SetLocalPosition({ ( - 750.f + AddMaginX) + MaginX , -60.f + MaginY, static_cast<float>(Z_ORDER::UI_Border)});
			
			AllCharmSlot_[ValueNum]->SetParent(this);
				
			PointActorComponent* Component_ = CreateComponent<PointActorComponent>();
			Component_->PushPointerActor(ValueNum, PAGE_TYPE::Charm, AllCharmSlot_[ValueNum]);

			MaginX += 90.f;
			++SlotNum;
			CharmSize_ = SlotNum;
		}

		MaginX = 0.f;
		MaginY -= 80.f;
	}

	 MaginX = 0;

	 //厘馒 浇吩
	for (int i = 40; i < 50; ++i)
	{
		AllCharmSlot_.push_back(GetLevel()->CreateActor<CharmSlot>());
		AllCharmSlot_[i]->CreateEquippedCharmSlot(CharmState{ i , 0, false, false });
		AllCharmSlot_[i]->GetTransform().SetLocalPosition({ -750.f + MaginX , 200.f , static_cast<float>(Z_ORDER::UI_Border) });
		AllCharmSlot_[i]->SetParent(this);

		if (i != 40)
		{
			AllCharmSlot_[i]->GetRenderer()->Off();
		}
	
		PointActorComponent* Component_ = CreateComponent<PointActorComponent>();
		Component_->PushPointerActor(i, PAGE_TYPE::Charm, AllCharmSlot_[i]);

		MaginX += 90.f;
	}

	//畴摹
	MaginX = 0;

	for (int i = 0; i < 5; ++i)
	{
		GetLevel<HollowKnightLevel>()->PushNotches(GetLevel()->CreateActor<Notches>(),
			{ -750.f + MaginX, 60.f , static_cast<float>(Z_ORDER::UI_Border) });
		GetLevel<HollowKnightLevel>()->AllNotes_[i]->SetParent(this);
		MaginX += 50.f;
	}

	NotchesFont_ = GetLevel() -> CreateActor<ContentsFontRenderer>();
	NotchesFont_->CreateFontRenderer("何利 沫"
		, 34
		, { 0, 0, 0 }
		,
		false
	, false);
	NotchesFont_->GetTransform().SetWorldPosition({ -700,  150, static_cast<float>(Z_ORDER::UI_Border) });
	NotchesFont_->SetScreenMove();
	NotchesFont_->SetParent(this);

	EquippedSlotFont_ = GetLevel()->CreateActor<ContentsFontRenderer>();
	EquippedSlotFont_->CreateFontRenderer("厘馒等 何利"
		, 40
		, { 200.f, (GameEngineWindow::GetInst()->GetScale().hy() - 300.0f), static_cast<float>(Z_ORDER::UI_Border) }
		, false
		, false);
	EquippedSlotFont_->GetTransform().SetWorldPosition({ -700,  300, static_cast<float>(Z_ORDER::UI_Border) });
	EquippedSlotFont_->SetScreenMove();
	EquippedSlotFont_->SetParent(this);

	Line_ = CreateComponent<GameEngineUIRenderer>();
	Line_->SetTexture("Inv_0017_divider.png");
	Line_->GetTransform().SetWorldScale({1021, 5});
	Line_->GetTransform().SetWorldPosition({ -380.f  , 15.f , static_cast<float>(Z_ORDER::UI_Border) });


	SetPageType(PAGE_TYPE::Charm);
	SetPageName("何利");

	GetLevel<HollowKnightLevel>()->CreateCharmPageInfo(this);
}

void CharmPage::Update(float _DeltaTime)
{
	EquippedSlotFont_->SetScreenMove();

	NotchesFont_->SetScreenMove();

}

void CharmPage::LevelStartEvent()
{

	



}

void CharmPage::AllOff()
{
	this->Off();

	for (int i = 0; i < AllCharmSlot_.size(); ++i)
	{
		AllCharmSlot_[i]->Off();
	}


	for (int i = 0; i < GetLevel<HollowKnightLevel>()->AllNotes_.size(); ++i)
	{
		GetLevel<HollowKnightLevel>()->AllNotes_[i]->Off();
	}

}

void CharmPage::AllOn()
{
	this->On();
	
	for (int i = 0; i < AllCharmSlot_.size(); ++i)
	{
		AllCharmSlot_[i]->On();
	}

	for (int i = 0; i < GetLevel<HollowKnightLevel>()->AllNotes_.size(); ++i)
	{
		GetLevel<HollowKnightLevel>()->AllNotes_[i]->On();
	}

	for (int i = 0; i < CharmSize_; ++i)
	{
		int ValueNum = i;
		auto CharmEnum = magic_enum::enum_cast<CHARM_SLOT>(ValueNum);

		std::string EnumString;

		auto Name = magic_enum::enum_name(CharmEnum.value());
		EnumString = static_cast<std::string>(Name);

		//std::string FilePathNum = std::to_string(ValueNum);

		if (KnightData::GetInst()->FindKnightCharmList(CharmEnum.value()) == true)
		{
			AllCharmSlot_[ValueNum]->SetCharmisHas(true);

		}



	}

	PointActorComponent* PointActorComponent_ = GetLevel<HollowKnightLevel>()->PointActorListCharm.find(0)->second;
	CharmSlot* findSlot = dynamic_cast<CharmSlot*>(PointActorComponent_->GetPointActor());
	if (findSlot != nullptr && findSlot->GetKnightHas() == true)
	{
		GetLevel<HollowKnightLevel>()->GetCharmPageInfo()->SetInfoImage(findSlot->GetFilePath());

		GetLevel<HollowKnightLevel>()->GetCharmPageInfo()->SetInfo(findSlot->GetInfo(), 21);
		GetLevel<HollowKnightLevel>()->GetCharmPageInfo()->SetInfoName(findSlot->GetInfoName());
	}

}

void CharmPage::CreateEquippedCharm(GameEngineUIRenderer* _CopyRenderer)
{


}

