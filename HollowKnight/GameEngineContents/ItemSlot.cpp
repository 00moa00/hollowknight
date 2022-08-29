#include "PreCompile.h"
#include "ItemSlot.h"

#include <GameEngineBase/magic_enum.hpp>
#include <GameEngineBase/magic_enum_format.hpp>
#include <GameEngineBase/magic_enum_fuse.hpp>

ItemSlot::ItemSlot() 
	:
	SpellRing_(nullptr)
{
}

ItemSlot::~ItemSlot() 
{
}


void ItemSlot::CreateItemSlot(std::string _Name, int _ItemNum, ITEM_LIST _Item)
{
	if (_Item == ITEM_LIST::Spell_Fireball || _Item == ITEM_LIST::Spell_Scream)
	{
		SpellRing_ = CreateComponent<GameEngineUIRenderer>();

	}


	ItemState_.ItemName_ = _Name;
	ItemState_.ItemNum_ = _ItemNum;
	ItemState_.isItem_ = true;

	CreateRendererComponent({ 49,49 }, "new_item_orb.png");
	Item_ = GetLevel()->CreateActor<Item>();
	Item_->CreateItem(_Name,  _Item);

	Item_->SetParent(this);

	Item_->GetRenderer()->GetTransform().SetLocalScale(Item_->GetRenderer()->GetCurTexture()->GetScale() * 0.8f);

	switch (_Item)
	{
	case ITEM_LIST::Heart_Piece:
		GetTransform().SetLocalPosition({ -710.f, 220.f });

		break;
	case ITEM_LIST::Soul_Piece:
		GetTransform().SetLocalPosition({ -540.f, 200.f });

		break;
	case ITEM_LIST::Dream_Nail:
		GetTransform().SetLocalPosition({ -340.f, 200.f });


		break;
	case ITEM_LIST::Nail:
		GetTransform().SetLocalPosition({ -710.f, -150.f });
		Item_->GetRenderer()->GetPipeLine()->SetOutputMergerBlend("AlphaBlend2");


		break;
	case ITEM_LIST::Spell_Fireball:

		//SpellRing_ = CreateComponent<GameEngineUIRenderer>();
		SpellRing_->SetTexture("spell_ring.png");
		SpellRing_->GetTransform().SetLocalScale({100,100});
		SpellRing_->GetPipeLine()->SetOutputMergerBlend("AlphaBlend2");


		GetTransform().SetLocalPosition({ -500.f, -30 });


		break;
	case ITEM_LIST::Spell_Scream:

		//SpellRing_ = CreateComponent<GameEngineUIRenderer>();
		SpellRing_->SetTexture("spell_ring.png");
		SpellRing_->GetTransform().SetLocalScale({ 100,100 });
		SpellRing_->GetPipeLine()->SetOutputMergerBlend("AlphaBlend2");

		GetTransform().SetLocalPosition({ -340.f, -30 });


		break;
	case ITEM_LIST::Spell_core:

		SpellRing_ = CreateComponent<GameEngineUIRenderer>();
		SpellRing_->SetTexture("spell_ring.png");

		SpellRing_->GetTransform().SetLocalScale(Item_->GetRenderer()->GetCurTexture()->GetScale());
		SpellRing_->GetPipeLine()->SetOutputMergerBlend("AlphaBlend2");

		GetTransform().SetLocalPosition({ -420.f, -100.f });


		break;
	case ITEM_LIST::Item_Geo:
		GetTransform().SetLocalPosition({ -510.f, -400.f });


		break;
	case ITEM_LIST::Tram_Pass:
		break;

	case ITEM_LIST::Lumafly_Lantern:
		break;
	case ITEM_LIST::Mapand_Quill:
		break;
	case ITEM_LIST::Collectors_Map:
		break;
	case ITEM_LIST::Hunters_Journal:
		break;
	case ITEM_LIST::Hunters_Mark:
		break;
	case ITEM_LIST::Delicate_Flower:
		break;
	case ITEM_LIST::Godtuner:
		break;
	case ITEM_LIST::Mask_Shard:
		break;
	case ITEM_LIST::Vessel_Fragment:
		break;
	case ITEM_LIST::Salubras_Blessing:
		break;
	case ITEM_LIST::Pale_Ore:
		break;
	case ITEM_LIST::Rancid_Egg:
		break;
	case ITEM_LIST::Wanderers_Journal:

		break;
	case ITEM_LIST::hallownest_seal:

		break;
	case ITEM_LIST::Kings_idol:

		break;
	case ITEM_LIST::arcane_egg:

		break;
	default:
		break;
	}

	SetPointerSize({ Item_->GetRenderer()->GetCurTexture()->GetScale() });



}

void ItemSlot::CreateItemSlot(int _ItemNum, ITEM_LIST _Item, ITEM_TYPE _type)
{
	CreateRendererComponent({49,49}, "new_item_orb.png");
	ItemState_.ItemNum_ = _ItemNum;
	ItemState_.isItem_ = false;
	SetPointerSize({49,49,1});

}

void ItemSlot::PustItem(int _ItemNum, ITEM_LIST _Item)
{


	std::string EnumString;

	auto Name = magic_enum::enum_name(_Item);
	EnumString = static_cast<std::string>(Name);

	CreateItemSlot(EnumString, _ItemNum, _Item);

	//Item_ = GetLevel()->CreateActor<Item>();
	//Item_->CreateItem(EnumString, _Item, this);
}
