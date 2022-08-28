#include "PreCompile.h"
#include "Item.h"

Item::Item() 
{
}

Item::~Item() 
{
}

void Item::Start()
{
}

void Item::Update(float _DeltaTime)
{
}

void Item::CreateItem(std::string _Name, ITEM_LIST _Item)
{


	float4 Scale = {100,100,1};

	switch (_Item)
	{
	case ITEM_LIST::Heart_Piece:
		Scale = { 395, 538, 1 };
		GetTransform().SetLocalPosition({ -600.f, 300.f });

		break;
	case ITEM_LIST::Soul_Piece:
		Scale = { 83, 116, 1 };
		GetTransform().SetLocalPosition({ -550.f, 250.f });

		break;
	case ITEM_LIST::Dream_Nail:
		Scale = { 155, 230, 1 };
		GetTransform().SetLocalPosition({ -500.f, 300.f });


		break;
	case ITEM_LIST::Nail:
		Scale = { 125, 458, 1 };
		GetTransform().SetLocalPosition({ -600.f, 50.f });


		break;
	case ITEM_LIST::Spell_Fireball:
		Scale = { 115, 72, 1 };
		GetTransform().SetLocalPosition({ -500.f, 100.f });


		break;
	case ITEM_LIST::Spell_Scream:
		Scale = { 83, 107, 1 };
		GetTransform().SetLocalPosition({ -400.f, 100.f });


		break;
	case ITEM_LIST::Spell_core:
		Scale = { 202, 201, 1 };
		GetTransform().SetLocalPosition({ -450.f, 0.f });


		break;
	case ITEM_LIST::Item_Geo:
		Scale = { 58, 61, 1 };
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
		Scale = { 93, 112, 1 };

		break;
	case ITEM_LIST::hallownest_seal:
		Scale = { 135, 137, 1 };

		break;
	case ITEM_LIST::Kings_idol:
		Scale = { 86, 116, 1 };

		break;
	case ITEM_LIST::arcane_egg:
		Scale = { 102, 102, 1 };

		break;
	default:
		break;
	}

	CreateRendererComponent(Scale, _Name + ".png");

}

