#include "PreCompile.h"
#include "ItemSlot.h"


ItemSlot::ItemSlot() 
{
}

ItemSlot::~ItemSlot() 
{
}


void ItemSlot::CreateItemSlot(std::string _Name, int _ItemNum, ITEM_LIST _Item)
{
	ItemState_.ItemName_ = _Name;
	ItemState_.ItemNum_ = _ItemNum;

	CreateRendererComponent({ 49,49 }, "new_item_orb.png");
	Item_ = GetLevel()->CreateActor<Item>();
	Item_->CreateItem(_Name,  _Item, this);

	Item_->SetParent(this);

	SetPointerSize({ Item_->GetRenderer()->GetCurTexture()->GetScale()});


	switch (_Item)
	{
	case ITEM_LIST::Heart_Piece:
		GetTransform().SetLocalPosition({ -600.f, 300.f });

		break;
	case ITEM_LIST::Soul_Piece:
		GetTransform().SetLocalPosition({ -550.f, 250.f });

		break;
	case ITEM_LIST::Dream_Nail:
		GetTransform().SetLocalPosition({ -500.f, 300.f });


		break;
	case ITEM_LIST::Nail:
		GetTransform().SetLocalPosition({ -600.f, 50.f });


		break;
	case ITEM_LIST::Spell_Fireball:
		GetTransform().SetLocalPosition({ -500.f, 100.f });


		break;
	case ITEM_LIST::Spell_Scream:
		GetTransform().SetLocalPosition({ -400.f, 100.f });


		break;
	case ITEM_LIST::Spell_core:
		GetTransform().SetLocalPosition({ -450.f, 0.f });


		break;
	case ITEM_LIST::Item_Geo:
		GetTransform().SetLocalPosition({ -500.f, -200.f });


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




}

void ItemSlot::CreateItemSlot(int _ItemNum, ITEM_LIST _Item, ITEM_TYPE _type)
{
	CreateRendererComponent({49,49}, "new_item_orb.png");
	ItemState_.ItemNum_ = _ItemNum;
	SetPointerSize({49,49,1});

}

void ItemSlot::PustItem(std::string _Name, ITEM_LIST _Item)
{
	Item_ = GetLevel()->CreateActor<Item>();
	Item_->CreateItem(_Name, _Item, this);
}
