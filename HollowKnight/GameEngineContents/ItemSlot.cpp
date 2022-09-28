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
	
	SetInfoName(" ");
	SetInfo(" ");

	switch (_Item)
	{
	case ITEM_LIST::Heart_Piece:
		GetTransform().SetLocalPosition({ -710.f, 220.f });
		SetInfoName("가면 조각");
		SetInfo("위해로부터 자신을 보호하기 위해 착용하는 고대 가면의 조각.");

		break;
	case ITEM_LIST::Soul_Piece:
		GetTransform().SetLocalPosition({ -540.f, 200.f });
		SetInfoName("그릇 파편");
		SetInfo("영혼을 담기 위해 만들어진 흰 그릇의 파편.");

		break;
	case ITEM_LIST::Dream_Nail:
		GetTransform().SetLocalPosition({ -340.f, 200.f });
		SetInfoName("몽환의 대못");
		SetInfo("꿈과 현실 사이의 장벽을 벨 수 있게 합니다. 숨겨진 꿈을 드러내거나 관문을 여는 데 사용할 수 있습니다. 몽환의 대못은 소망과 꿈의 잔재인 정수를 수집할 수 있습니다.");


		break;
	case ITEM_LIST::Nail:
		GetTransform().SetLocalPosition({ -710.f, -150.f });
		Item_->GetRenderer()->GetClonePipeLine()->SetOutputMergerBlend("AlphaBlend2");

		SetInfoName("낡은 대못");
		SetInfo("신성둥지의 전통적인 무기. 세월과 마모로 인해 날이 무디어져 있습니다.");

		break;
	case ITEM_LIST::Spell_Fireball:

		//SpellRing_ = CreateComponent<GameEngineUIRenderer>();
		SpellRing_->SetTexture("spell_ring.png");
		SpellRing_->GetTransform().SetLocalScale({ 100,100 });
		SpellRing_->GetClonePipeLine()->SetOutputMergerBlend("AlphaBlend2");

		GetTransform().SetLocalPosition({ -500.f, -30 });

		SetInfoName("울부짖는 원혼들");
		SetInfo("비명을 지르는 영혼으로 적을 공격합니다. 원혼을 부리기 위해서는 영혼이 필요합니다. 적을 공격하여 영혼을 모으십시오.");
		break;
	case ITEM_LIST::Spell_Scream:

		//SpellRing_ = CreateComponent<GameEngineUIRenderer>();
		SpellRing_->SetTexture("spell_ring.png");
		SpellRing_->GetTransform().SetLocalScale({ 100,100 });
		SpellRing_->GetClonePipeLine()->SetOutputMergerBlend("AlphaBlend2");

		GetTransform().SetLocalPosition({ -340.f, -30 });

		SetInfoName("복수의 영령");
		SetInfo("앞으로 날아가면서 적을 불태우는 영령을 불러냅니다. 영령을 부리기 위해서는 영혼이 필요합니다. 적을 공격하여 영혼을 모으십시오.");


		break;
	case ITEM_LIST::Spell_core:

		SpellRing_ = CreateComponent<GameEngineUIRenderer>();
		SpellRing_->SetTexture("spell_ring.png");

		SpellRing_->GetTransform().SetLocalScale(Item_->GetRenderer()->GetCurTexture()->GetScale());
		SpellRing_->GetClonePipeLine()->SetOutputMergerBlend("AlphaBlend2");

		GetTransform().SetLocalPosition({ -420.f, -100.f });

		SetInfoName("집중");
		SetInfo("집중하여 수집한 영혼으로 껍데기를 수리하고 상처를 치유합니다. 적을 공격하여 영혼을 모으십시오.");

		break;
	case ITEM_LIST::Item_Geo:
		GetTransform().SetLocalPosition({ -510.f, -400.f });

		SetInfoName("지오");
		SetInfo("다양한 형태의 화석화된 겁데기로 만든 신성둥지의 화폐. 물건과 교환하거나 여러 가지의 오래된 장치에서 통행료로 사용될 수 있습니다.");

		break;
	case ITEM_LIST::Tram_Pass:

		SetInfoName("노면전차 탑승권");
		SetInfo("신성둥지의 몇몇 부분을 연결하는 노면 전차의 평생 탑승권. 이 탑승권은 엄청난 양의 지오로 구매가 가능했고, 각 구매는 왕의 승인이 요구되었습니다.");

		break;

	case ITEM_LIST::Lumafly_Lantern:

		SetInfoName("빛파리 등불");
		SetInfo("빛파리가 담긴 수정 등불. 길을 찾을 수 있도록 어두운 동굴을 밝힙니다.");

		break;
	case ITEM_LIST::Mapand_Quill:

		SetInfoName(" ");
		SetInfo(" ");

		break;
	case ITEM_LIST::Collectors_Map:

		SetInfoName(" ");
		SetInfo(" ");

		break;
	case ITEM_LIST::Map_and_Quill:

		SetInfoName("지도와 깃펜");
		SetInfo("신성둥지의 지도. 의자나 다른 곳에서 쉴 때 깃펜을 사용하여 새로 발견된 지역을 지도에 갱신할 수 있습니다.");

		break;
	case ITEM_LIST::Hunters_Journal:

		SetInfoName(" ");
		SetInfo(" ");

		break;
	case ITEM_LIST::Hunters_Mark:

		SetInfoName(" ");
		SetInfo(" ");

		break;
	case ITEM_LIST::Delicate_Flower:

		SetInfoName(" ");
		SetInfo(" ");

		break;
	case ITEM_LIST::Godtuner:

		SetInfoName(" ");
		SetInfo(" ");

		break;
	case ITEM_LIST::Mask_Shard:

		SetInfoName(" ");
		SetInfo(" ");

		break;
	case ITEM_LIST::Vessel_Fragment:

		SetInfoName(" ");
		SetInfo(" ");

		break;
	case ITEM_LIST::Salubras_Blessing:

		SetInfoName(" ");
		SetInfo(" ");

		break;
	case ITEM_LIST::Pale_Ore:

		SetInfoName("");
		SetInfo("얼음같은 차가움을 발산하는 희귀하고 창백한 금속. 무기를 만드는 이들이 소중하게 여깁니다.");

		break;
	case ITEM_LIST::Rancid_Egg:

		SetInfoName(" ");
		SetInfo(" ");

		break;
	case ITEM_LIST::Wanderers_Journal:

		SetInfoName("방랑자의 일지");
		SetInfo("오래전에 죽은 방랑자가 남긴 일지. 내용은 잊혀진 방언으로 쓰여있어서 이해하기 어렵습니다. 신성둥지의 과거로부터의 유물. 이 물건은 왕국의 역사에 전념하는 이들에게만 가치가 있습니다.");


		break;
	case ITEM_LIST::hallownest_seal:

		SetInfoName("신성둥지의 문양");
		SetInfo("왕과 그 기사단의 권위를 상징하는 신성둥지 왕국의 공식 문양. 신성둥지의 과거로부터의 유물. 이 물건은 왕국의 역사에 전념하는 이들에게만 가치가 있습니다.");


		break;
	case ITEM_LIST::Kings_idol:

		SetInfoName("왕의 우상");
		SetInfo("신성둥지의 왕을 묘사한 백색 우상. 흔히 볼 수 없던 왕은 이 조각을 통해 숭배되었습니다. 신성둥지의 과거로부터의 유물. 이 물건은 왕국의 역사에 전념하는 이들에게만 가치가 있습니다.");


		break;
	case ITEM_LIST::arcane_egg:

		SetInfoName(" ");
		SetInfo(" ");

		break;

	case ITEM_LIST::Shade_Cloak:

		SetInfoName("나방날개 망토");
		SetInfo("나방날개 가닥으로 꼰 망토. 착용자가 지면을 따라 또는 공기를 통해 앞으로 돌진할 수 있게 합니다.");

		break;
	case ITEM_LIST::Witches_eye:

		SetInfoName(" ");
		SetInfo(" ");

		break;

	case ITEM_LIST::Storeroom_key:

		SetInfoName(" ");
		SetInfo(" ");

		break;
	case ITEM_LIST::Quill_combined:

		SetInfoName(" ");
		SetInfo(" ");

		break;
	case ITEM_LIST::Monarch_Wings:

		SetInfoName("제왕의 날개");
		SetInfo("어둠 속에서 반짝이는 천상의 물질로 만든 날개. 공중에서 다시 점프할 수 있게 합니다.");

		break;
	case ITEM_LIST::Mender_key:

		SetInfoName(" ");
		SetInfo(" ");

		break;
	case ITEM_LIST::Acid_armour:

		SetInfoName(" ");
		SetInfo(" ");

		break;
	case ITEM_LIST::Crystal_heart:

		SetInfoName(" ");
		SetInfo(" ");

		break;
	case ITEM_LIST::Rancid_egg:

		SetInfoName(" ");
		SetInfo(" ");

		break;
	case ITEM_LIST::Area_map:

		SetInfoName(" ");
		SetInfo(" ");

		break;
	case ITEM_LIST::Treasure_map:

		SetInfoName(" ");
		SetInfo(" ");

		break;
	case ITEM_LIST::Mantis_Cloak:

		SetInfoName("사마귀 갈고리");
		SetInfo("뼈를 갈아 만든 발톱. 착용자가 벽에 붙어서 도약할 수 있게 합니다.");

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
