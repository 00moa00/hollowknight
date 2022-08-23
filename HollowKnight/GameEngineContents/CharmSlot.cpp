#include "PreCompile.h"
#include "CharmSlot.h"

CharmSlot::CharmSlot() 
	:
	Charm_(nullptr)
{
}

CharmSlot::~CharmSlot() 
{
}

void CharmSlot::Start()
{
}

void CharmSlot::Update(float _Deltatime)
{
}

void CharmSlot::CreateCharmSlot(std::string _SlotName, std::string _CharmFilePath, CharmState _CharmState, CHARM_SLOT _slot)
{
	// 何利 浇吩
	CreateRendererComponent({68,68,1}, "charm_backboard.png");

	//何利 惑怕
	CharmState_.SlotNum_ = _CharmState.SlotNum_;
	CharmState_.KnihgistHas_ = _CharmState.KnihgistHas_;
	CharmState_.isUsing_ = _CharmState.isUsing_;
	CharmState_.isEquipped_ = false;
	CharmState_.isEquippedUsing_ = false;
	CharmState_.CharmFilePath_ = _CharmFilePath;
	CharmState_.CharmName_ = _SlotName;

	//何利
	Charm_ = GetLevel()->CreateActor<Charm>();
	Charm_->CreateCharm(_SlotName, _CharmFilePath, { 131, 128, 1 });

	Charm_->SetParent(this);

	//何利 沫 技泼
	switch (_slot)
	{
	case CHARM_SLOT::Wayward_Compass:
		CharmState_.SlotCount_ = 1;

		break;
	case CHARM_SLOT::Gathering_Swarm:
		CharmState_.SlotCount_ = 1;

	break;	
	case CHARM_SLOT::Stalwart_Shell:
		CharmState_.SlotCount_ = 2;

	break;	
	case CHARM_SLOT::Soul_Catcher:
		CharmState_.SlotCount_ = 2;

		break;	
	case CHARM_SLOT::Shaman_Stone:
		CharmState_.SlotCount_ = 3;

		break;

	case CHARM_SLOT::Soul_Eater:
		CharmState_.SlotCount_ = 4;

		break;
	case CHARM_SLOT::Dashmaster:
		CharmState_.SlotCount_ = 4;

		break;
	case CHARM_SLOT::Thorns_of_Agony:
		CharmState_.SlotCount_ = 2;

		break;
	case CHARM_SLOT::Fury_of_the_Fallen:
		CharmState_.SlotCount_ = 2;

		break;
	case CHARM_SLOT::Fragile_Heart:
		CharmState_.SlotCount_ = 2;

		break;
	case CHARM_SLOT::Fragile_Greed:
		CharmState_.SlotCount_ = 2;

		break;
	case CHARM_SLOT::Fragile_Strength:
		CharmState_.SlotCount_ = 3;

		break;
	case CHARM_SLOT::Spell_Twister:
		CharmState_.SlotCount_ = 2;

		break;
	case CHARM_SLOT::Steady_Body:
		CharmState_.SlotCount_ = 1;

		break;
	case CHARM_SLOT::Heavy_Blow:
		CharmState_.SlotCount_ = 2;

		break;
	case CHARM_SLOT::Quick_Slash:
		CharmState_.SlotCount_ = 3;

		break;
	case CHARM_SLOT::Longnail:
		CharmState_.SlotCount_ = 2;

		break;
	case CHARM_SLOT::Mark_of_Pride:
		CharmState_.SlotCount_ = 3;

		break;
	case CHARM_SLOT::Baldur_Shell:
		CharmState_.SlotCount_ = 2;

		break;
	case CHARM_SLOT::Flukenest:
		CharmState_.SlotCount_ = 3;

		break;
	case CHARM_SLOT::Defenders_Crest:
		CharmState_.SlotCount_ = 1;

		break;
	case CHARM_SLOT::Glowing_Womb:
		CharmState_.SlotCount_ = 2;

		break;
	case CHARM_SLOT::Quick_Focus:
		CharmState_.SlotCount_ = 3;

		break;
	case CHARM_SLOT::Deep_Focus:
		CharmState_.SlotCount_ = 3;

		break;
	case CHARM_SLOT::Lifeblood_Heart:
		CharmState_.SlotCount_ = 2;

		break;
	case CHARM_SLOT::Lifeblood_Core:
		CharmState_.SlotCount_ = 3;

		break;
	case CHARM_SLOT::Jonis_Blessing:
		CharmState_.SlotCount_ = 4;

		break;
	case CHARM_SLOT::Grubsong:
		CharmState_.SlotCount_ = 1;

		break;
	case CHARM_SLOT::Grubberflys_Elegy:
		CharmState_.SlotCount_ = 3;

		break;
	case CHARM_SLOT::Hiveblood:
		CharmState_.SlotCount_ = 4;

		break;
	case CHARM_SLOT::Spore_Shroom:
		CharmState_.SlotCount_ = 1;

		break;
	case CHARM_SLOT::Sharp_Shadow:
		CharmState_.SlotCount_ = 2;

		break;
	case CHARM_SLOT::Shape_of_Unn:
		CharmState_.SlotCount_ = 2;

		break;
	case CHARM_SLOT::Nailmasters_Glory:
		CharmState_.SlotCount_ = 1;

		break;
	case CHARM_SLOT::Dream_Wielder:
		CharmState_.SlotCount_ = 1;

		break;
	case CHARM_SLOT::Kingsoul:
		CharmState_.SlotCount_ = 5;

		break;
	case CHARM_SLOT::Sprintmaster:
		CharmState_.SlotCount_ = 1;

		break;
	case CHARM_SLOT::Weaversong:
		CharmState_.SlotCount_ = 2;

		break;
	case CHARM_SLOT::Dreamshield:
		CharmState_.SlotCount_ = 3;

		break;
	case CHARM_SLOT::Grimmchild:
		CharmState_.SlotCount_ = 2;

		break;
	default:
		break;
	}

	//GetRenderer()->SetParent(this);

}

void CharmSlot::CreateEquippedCharmSlot( CharmState _CharmState)
{
	// 何利 浇吩
	CreateRendererComponent({ 38, 38,1 }, "charm_cost.png");

	//何利 惑怕
	CharmState_.SlotNum_ = _CharmState.SlotNum_;
	CharmState_.SlotCount_ = _CharmState.SlotCount_;
	CharmState_.KnihgistHas_ = _CharmState.KnihgistHas_;
	CharmState_.isUsing_ = _CharmState.isUsing_;
	CharmState_.isEquipped_ = true;
	CharmState_.isEquippedUsing_ = false;


	//何利
	Charm_ = GetLevel()->CreateActor<Charm>();
	//Charm_->CreateCharm(_SlotName, _CharmFilePath, { 131, 128, 1 });

	Charm_->SetParent(this);


}

void CharmSlot::CreateCopyCharm(GameEngineUIRenderer* _RenderData, std::string _SlotName, std::string _FilePath)
{
	Charm_->CreateCharm(_SlotName, _FilePath, { 131, 128, 1 });
	
}
