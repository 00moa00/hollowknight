#include "PreCompile.h"
#include "CharmPage.h"
#include "GlobalContentsValue.h"
#include <GameEngineBase/magic_enum.hpp>
#include <GameEngineBase/magic_enum_format.hpp>
#include <GameEngineBase/magic_enum_fuse.hpp>

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

	int SlotNum = 0;

	for (int y = 0; y < 4; ++y)
	{
		for (int x = 0; x < 10; ++x)
		{
			int ValueNum = SlotNum;
			auto CharmEnum = magic_enum::enum_cast<CHARM_SLOT>(ValueNum);

			std::string EnumString;

			auto Name = magic_enum::enum_name(CharmEnum.value());
			EnumString = static_cast<std::string>(Name);

			
			std::string FilePathNum = std::to_string(ValueNum);
			AllCharmSlot_.push_back(GetLevel()->CreateActor<CharmSlot>());
			AllCharmSlot_[ValueNum]->CreateCharmSlot(EnumString, "Charm_" + FilePathNum + ".png", CharmState{ValueNum , 0, false, false});
			AllCharmSlot_[ValueNum]->GetTransform().SetLocalPosition({ MaginX , MaginY, static_cast<float>(Z_ORDER::UI)});

			MaginX += 100.f;
			++SlotNum;
		}
		MaginX = 0.f;
		MaginY += 150.f;


	}



	int CharmSlotNum = 0;








	//CreateRendererComponent(float4{ 1920, 1080, 1 }, "Black.png");

}

void CharmPage::Update(float _DeltaTime)
{
}

