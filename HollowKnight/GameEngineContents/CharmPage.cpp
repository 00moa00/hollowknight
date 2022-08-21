#include "PreCompile.h"
#include "CharmPage.h"
#include "GlobalContentsValue.h"
#include <GameEngineBase/magic_enum.hpp>
#include <GameEngineBase/magic_enum_format.hpp>
#include <GameEngineBase/magic_enum_fuse.hpp>
#include "PointActorComponent.h"

CharmPage::CharmPage() 
{
}

CharmPage::~CharmPage() 
{
}

void CharmPage::Start()
{


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
			AllCharmSlot_[ValueNum]->GetTransform().SetLocalPosition({ ( - 750.f + AddMaginX) + MaginX , -60.f + MaginY, static_cast<float>(Z_ORDER::UI)});
			//AllCharmSlot_[ValueNum]->SetParent(this);
				
			PointActorComponent* Component_ = CreateComponent<PointActorComponent>();
			Component_->PushPointerActor(ValueNum, PAGE_TYPE::Charm, AllCharmSlot_[ValueNum]);


			MaginX += 90.f;
			++SlotNum;
		}
		MaginX = 0.f;
		MaginY -= 80.f;


	}



	int CharmSlotNum = 0;








	//CreateRendererComponent(float4{ 1920, 1080, 1 }, "Black.png");

}

void CharmPage::Update(float _DeltaTime)
{
}

void CharmPage::AllOff()
{
	this->Off();

	for (int i = 0; i < AllCharmSlot_.size(); ++i)
	{
		AllCharmSlot_[i]->Off();
	}

}

void CharmPage::AllOn()
{
	this->On();
	
	for (int i = 0; i < AllCharmSlot_.size(); ++i)
	{
		AllCharmSlot_[i]->On();
	}



}

