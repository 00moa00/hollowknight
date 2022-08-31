#include "PreCompile.h"
#include "InventoryPage.h"
#include "HollowKnightLevel.h"
#include"PointActorComponent.h"

#include <GameEngineBase/magic_enum.hpp>
#include <GameEngineBase/magic_enum_format.hpp>
#include <GameEngineBase/magic_enum_fuse.hpp>

InventoryPage::InventoryPage() 
{
}

InventoryPage::~InventoryPage() 
{
}

void InventoryPage::Start()
{
	SetPageType(PAGE_TYPE::Inventory);

	//스펠 아이템 등록

	{
		int SlotNum = 0;

		for (int i = 0; i < 8; ++i)
		{
			int ValueNum = SlotNum;
			auto ItemEnum = magic_enum::enum_cast<ITEM_LIST>(ValueNum);

			std::string EnumString;

			auto Name = magic_enum::enum_name(ItemEnum.value());
			EnumString = static_cast<std::string>(Name);


			AllItem_.insert({ SlotNum, GetLevel()->CreateActor<ItemSlot>() });
			AllItem_[SlotNum]->CreateItemSlot(EnumString, SlotNum, ItemEnum.value());

			AllItem_[SlotNum]->SetParent(this);



			PointActorComponent* Component_ = CreateComponent<PointActorComponent>();
			Component_->PushPointerActor(ValueNum, PAGE_TYPE::Inventory, AllItem_[ValueNum]);

			++SlotNum;
		}	
	}

	// 일반 아이템 등록

	{
		float MaginX = 0.0f;
		float MaginY = 0.f;
		int SlotNum = 10;

		for (int j = 0; j < 3; ++j)
		{

			for (int i = 0;i < 4; ++i)
			{
				int ValueNum = SlotNum;
				auto ItemEnum = magic_enum::enum_cast<ITEM_LIST>(ValueNum);

				std::string EnumString;

				auto Name = magic_enum::enum_name(ItemEnum.value());
				EnumString = static_cast<std::string>(Name);


				AllItem_.insert({ SlotNum, GetLevel()->CreateActor<ItemSlot>() });
				AllItem_[SlotNum]->CreateItemSlot(SlotNum, ItemEnum.value(), ITEM_TYPE::Normal_Item);

				AllItem_[SlotNum]->SetParent(this);
				AllItem_[SlotNum]->GetTransform().SetLocalPosition({-150.f + MaginX, 200.f + MaginY , static_cast<float>(Z_ORDER::UI) });


				PointActorComponent* Component_ = CreateComponent<PointActorComponent>();
				Component_->PushPointerActor(SlotNum, PAGE_TYPE::Inventory, AllItem_[SlotNum]);

				++SlotNum;
				MaginX += 120.f;

			}
			MaginX = 0.f;
			MaginY -= 100.f;
		}
	}

	GetLevel<HollowKnightLevel>()->PustItemInventroy(ITEM_LIST::Shade_Cloak);
	GetLevel<HollowKnightLevel>()->PustItemInventroy(ITEM_LIST::Mantis_Cloak);


	//소비 아이템 등록
	{
		int SlotNum = 40;
		float MaginX = 0.0f;

		for (int i = 40; i < 44; ++i)
		{
			int ValueNum = SlotNum;
			auto ItemEnum = magic_enum::enum_cast<ITEM_LIST>(ValueNum);

			std::string EnumString;

			auto Name = magic_enum::enum_name(ItemEnum.value());
			EnumString = static_cast<std::string>(Name);

			AllItem_.insert({ SlotNum, GetLevel()->CreateActor<ItemSlot>() });
			AllItem_[SlotNum]->CreateItemSlot(EnumString, SlotNum, ItemEnum.value());
			AllItem_[SlotNum]->SetParent(this);
			AllItem_[SlotNum]->GetTransform().SetLocalPosition({ 0 + MaginX, -200.f  , static_cast<float>(Z_ORDER::UI) });

			PointActorComponent* Component_ = CreateComponent<PointActorComponent>();
			Component_->PushPointerActor(SlotNum, PAGE_TYPE::Inventory, AllItem_[SlotNum]);

			++SlotNum;
			MaginX += 120.f;
		}
	}
}

void InventoryPage::Update(float _DeltaTime)
{
}

