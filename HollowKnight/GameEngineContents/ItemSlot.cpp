#include "PreCompile.h"
#include "ItemSlot.h"


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
	ItemState_.ItemName_ = _Name;
	ItemState_.ItemNum_ = _ItemNum;

	CreateRendererComponent({ 49,49 }, "new_item_orb.png");
	Item_ = GetLevel()->CreateActor<Item>();
	Item_->CreateItem(_Name,  _Item, this);

	Item_->SetParent(this);

	Item_->GetRenderer()->GetTransform().SetLocalScale(Item_->GetRenderer()->GetCurTexture()->GetScale() * 0.8f);

	switch (_Item)
	{
	case ITEM_LIST::Heart_Piece:
		GetTransform().SetLocalPosition({ -700.f, 250.f });

		break;
	case ITEM_LIST::Soul_Piece:
		GetTransform().SetLocalPosition({ -550.f, 220.f });

		break;
	case ITEM_LIST::Dream_Nail:
		GetTransform().SetLocalPosition({ -250.f, 200.f });


		break;
	case ITEM_LIST::Nail:
		GetTransform().SetLocalPosition({ -700.f, -150.f });
		Item_->GetRenderer()->GetPipeLine()->SetOutputMergerBlend("AlphaBlend2");


		break;
	case ITEM_LIST::Spell_Fireball:



		//SpellRingBack_ = CreateComponent<GameEngineUIRenderer>();
		//SpellRingBack_->SetTexture("spell_ring_back.png");
		//SpellRingBack_->GetTransform().SetLocalScale(SpellRingBack_->GetCurTexture()->GetScale());
		////SpellRingBack_->Off();
		//SpellRingBack_->GetPipeLine()->SetOutputMergerBlend("AddBlend");


		SpellRing_ = CreateComponent<GameEngineUIRenderer>();
		SpellRing_->SetTexture("spell_ring.png");
		SpellRing_->GetTransform().SetLocalScale(SpellRing_->GetCurTexture()->GetScale());
		SpellRing_->GetPipeLine()->SetOutputMergerBlend("AlphaBlend2");



		GetTransform().SetLocalPosition({ -550.f, 0 });
		//SpellRing_->GetTransform().SetLocalPosition({ SpellRing_->GetTransform().GetLocalPosition().x, SpellRing_->GetTransform().GetLocalPosition().y, static_cast<float>(Z_ORDER::UI_BackBoard)});


		break;
	case ITEM_LIST::Spell_Scream:

		SpellRing_ = CreateComponent<GameEngineUIRenderer>();
		SpellRing_->SetTexture("spell_ring.png");
		SpellRing_->GetTransform().SetLocalScale(SpellRing_->GetCurTexture()->GetScale());
		SpellRing_->GetPipeLine()->SetOutputMergerBlend("AlphaBlend2");

		GetTransform().SetLocalPosition({ -350.f, 0 });


		break;
	case ITEM_LIST::Spell_core:

		SpellRing_ = CreateComponent<GameEngineUIRenderer>();
		SpellRing_->SetTexture("spell_ring.png");

		SpellRing_->GetTransform().SetLocalScale(SpellRing_->GetCurTexture()->GetScale());
		SpellRing_->GetPipeLine()->SetOutputMergerBlend("AlphaBlend2");

		GetTransform().SetLocalPosition({ -450.f, -100.f });


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

	SetPointerSize({ Item_->GetRenderer()->GetCurTexture()->GetScale() });



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
