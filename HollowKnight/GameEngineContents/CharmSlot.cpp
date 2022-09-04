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
	// 부적 슬롯
	CreateRendererComponent({68,68,1}, "charm_backboard.png");

	//부적 상태
	CharmState_.SlotNum_ = _CharmState.SlotNum_;
	CharmState_.KnihgistHas_ = _CharmState.KnihgistHas_;
	CharmState_.isUsing_ = _CharmState.isUsing_;
	CharmState_.isEquippedSlot_ = false;
	CharmState_.isEquippedSlotUsing_ = false;
	CharmState_.CharmFilePath_ = _CharmFilePath;
	CharmState_.CharmName_ = _SlotName;
	CharmState_.UsingSlotNum_ = static_cast<int>(_slot);

	//부적
	Charm_ = GetLevel()->CreateActor<Charm>();
	Charm_->CreateCharm(_SlotName, _CharmFilePath, { 131, 128, 1 });

	Charm_->SetParent(this);

	SetPointerSize(Charm_->GetRenderer()->GetCurTexture()->GetScale());

	//부적 칸 세팅
	switch (_slot)
	{
	case CHARM_SLOT::Wayward_Compass:
		CharmState_.SlotCount_ = 1;
		SetInfoName( "변덕스런 납침반");
		SetInfo( "지도가 열릴 때마다 착용자에게 위치를 속삭여 방랑자가 자신의 현재 위치를 정확히 파악할 수 있게 합니다.");

		break;
	case CHARM_SLOT::Gathering_Swarm:
		CharmState_.SlotCount_ = 1;
		SetInfoName( "수집벌레 무리");
		SetInfo( "무리가 착용자를 따라다니며, 놓친 지오를 가져옵니다.아무리 사소한 것이라도 남기는 것을 견디지 못하는 이들에게 유용합니다.");

	break;	
	case CHARM_SLOT::Stalwart_Shell:
		CharmState_.SlotCount_ = 2;
		SetInfoName( "튼튼한 껍데기");
		SetInfo( "주술자들이 주위 세계로부터 더 많은 영혼을 끌어내기 위해 사용합니다. 대못으로 적을 공격할 때 얻는 영혼의 양을 증가시킵니다.");

	break;	
	case CHARM_SLOT::Soul_Catcher:
		CharmState_.SlotCount_ = 2;
		SetInfoName( "영혼 포식자");
		SetInfo( "아직 살아있는 생명체로부터 영혼을 끌어내는 데 사용되던 잊혀진 주술사의 유물. 대못으로 적을 공격할 때 얻는 영혼의 양을 크게 증가시킵니다.");

		break;	
	case CHARM_SLOT::Shaman_Stone:
		CharmState_.SlotCount_ = 3;
		SetInfoName( "주술사의 돌");
		SetInfo( "주술사의 과거 세대 지식을 담고 있다고 합니다. 주문의 힘을 증가시켜 적에게 더 많은 피해를 가합니다.");

		break;

	case CHARM_SLOT::Soul_Eater:
		CharmState_.SlotCount_ = 4;
		SetInfoName( "영혼 포식자");
		SetInfo( "아직 살아있는 생명체로부터 영혼을 끌어내는 데 사용되던 잊혀진 주술사의 유물. 대못으로 적을 공격할 때 얻는 영혼의 양을 크게 증가시킵니다.");

		break;
	case CHARM_SLOT::Dashmaster:
		CharmState_.SlotCount_ = 4;
		SetInfoName( "대시 마스터");
		SetInfo( "'대시마스터'라고만 알려진 괴상한 곤충의 모습을 하고 있습니다. 착용자는 더 자주 대시를 할뿐만 아니라 아래로도 대시를 할 수 있습니다. 최대한 빨리 주변을 돌아다니고 싶어하는 이들에게 이상적입니다.");

		break;
	case CHARM_SLOT::Thorns_of_Agony:
		CharmState_.SlotCount_ = 2;
		SetInfoName( "고통의 가시덩굴");
		SetInfo( "착용자의 고통을 감지하면 주변을 채찍질 합니다. 피해를 받으면 주변의 적들에게 피해를 입히는 가시가 많은 덩굴이 자라납니다.");

		break;
	case CHARM_SLOT::Fury_of_the_Fallen:
		CharmState_.SlotCount_ = 2;
		SetInfoName( "전사자의 분노");
		SetInfo( "죽을 이들에 대한 분노와 영웅심을 상징합니다. 죽음에 가까워졌을 때 착용자의 힘이 증가합니다.");

		break;
	case CHARM_SLOT::Fragile_Heart:
		CharmState_.SlotCount_ = 2;
		SetInfoName( "허술한 심장");
		SetInfo( "착용자의 체력을 증가시켜 더 많은 피해를 견딜 수 있게 합니다. 이 부적은 약해서 착용자가 죽으면 깨집니다.");

		break;
	case CHARM_SLOT::Fragile_Greed:
		CharmState_.SlotCount_ = 2;
		SetInfoName( "허술한 탐욕");
		SetInfo( "착용자가 적을 물리치면 더 많은 지오를 가져다줍니다. 이 부적은 약해서 착용자가 죽으면 깨집니다.");

		break;
	case CHARM_SLOT::Fragile_Strength:
		CharmState_.SlotCount_ = 3;
		SetInfoName( "허술한 힘 ");
		SetInfo( "착용자를 강하게 하고, 대못으로 적에게 입히는 손상을 증가시킵니다. 이 부적은 약해서 착용자가 죽으면 깨집니다.");

		break;
	case CHARM_SLOT::Spell_Twister:
		CharmState_.SlotCount_ = 2;
		SetInfoName( "주문 회오리");
		SetInfo( "주문을 부리는 데 필요한 영혼 비용을 줄입니다.");

		break;
	case CHARM_SLOT::Steady_Body:
		CharmState_.SlotCount_ = 1;
		SetInfoName( "흔들림 없는 자세");
		SetInfo( "대못으로 적을 공격할 때 착용자가 뒤로 몸이 밀리지 않게 합니다. 안정적인 상태로 계속 공격을 할 수 있게 합니다.");

		break;
	case CHARM_SLOT::Heavy_Blow:
		CharmState_.SlotCount_ = 2;
		SetInfoName( "묵직한 타격");
		SetInfo( "죽은 전사의 대못으로 만들어졌습니다. 착용자의 대못의 힘을 증가시켜 적이 공격을 받았을 때 더 멀리 밀려나게 합니다.");

		break;
	case CHARM_SLOT::Quick_Slash:
		CharmState_.SlotCount_ = 3;
		SetInfoName( "빠른 참격");
		SetInfo( "함께 용해된 불완전하고 버려진 대못으로부터 태어났습니다. 대못은 여전히 휘둘러지기를 갈망합니다. 착용자는 대못으로 훨씬 더 빠르게 벨 수 있습니다.");

		break;
	case CHARM_SLOT::Longnail:
		CharmState_.SlotCount_ = 2;
		SetInfoName( "기다란 대못");
		SetInfo( "착용자의 대못 범위를 증가시켜 멀리서 적을 공격할 수 있게 합니다.");

		break;
	case CHARM_SLOT::Mark_of_Pride:
		CharmState_.SlotCount_ = 3;
		SetInfoName( "긍지의 표식");
		SetInfo( "사마귀 부족이 자신들이 존경하는 이에게 줍니다. 착용자의 대못 범위를 크게 증가시켜 멀리서 적을 공격할 수 있게 합니다.");

		break;
	case CHARM_SLOT::Baldur_Shell:
		CharmState_.SlotCount_ = 2;
		SetInfoName( "발더 껍데기");
		SetInfo( "영혼을 집중하면서 딱딱한 껍데기로 착용자를 보호합니다. 껍데기는 무적이 아니며 너무 많은 손상을 흡수하면 산산이 부서집니다.");

		break;
	case CHARM_SLOT::Flukenest:
		CharmState_.SlotCount_ = 3;
		SetInfoName( "흡충 둥지");
		SetInfo( "흡충 어미의 내장에서 태어난 살아있는 부적. 복수의 영령 주문을 변덕스러운 아기 흡충 무리로 바꿉니다.");

		break;
	case CHARM_SLOT::Defenders_Crest:
		CharmState_.SlotCount_ = 1;
		SetInfoName( "수호기사의 문장");
		SetInfo( "신성둥지의 왕이 가장 충성스러운 기사에게 수여한 독특한 부적. 긁히고 더러워졌지만 여전히 사랑받습니다. 착용자가 영웅적 냄새를 방출하게 합니다.");

		break;
	case CHARM_SLOT::Glowing_Womb:
		CharmState_.SlotCount_ = 2;
		SetInfoName( "영롱한 알집");
		SetInfo( "착용자의 영혼을 빼내 유충을 탄생시키는 데 사용합니다. 유충은 먹거나 살려는 의지가 없으며, 부모를 보호하기 위해 자신을 희생합니다.");

		break;
	case CHARM_SLOT::Quick_Focus:
		CharmState_.SlotCount_ = 3;
		SetInfoName( "쾌속 집중");
		SetInfo( "수정 렌즈를 포함하고 있는 부적. 영혼 집중의 속도를 증가시켜 착용자가 피해를 더 빨리 치유할 수 있게 합니다.");

		break;
	case CHARM_SLOT::Deep_Focus:
		CharmState_.SlotCount_ = 3;
		SetInfoName( "깊은 집중");
		SetInfo( "오랜 기간에 걸쳐 수정 안에 자연적으로 형성된 부적. 주변 공기로부터 영혼을 끌어냅니다.착용자는 더 느린 속도로 영혼을 집중하지만, 치유 효과는 두 배가 됩니다.");

		break;
	case CHARM_SLOT::Lifeblood_Heart:
		CharmState_.SlotCount_ = 2;
		SetInfoName( "생명혈 심장");
		SetInfo( "귀중한 생명혈을 스며 나오게 하는 살아있는 핵을 담고 있습니다. 휴식을 할 때 착용자는 경미한 손상으로부터 보호하는 생명혈로 코팅됩니다.");

		break;
	case CHARM_SLOT::Lifeblood_Core:
		CharmState_.SlotCount_ = 3;
		SetInfoName( "생명혈 핵");
		SetInfo( "귀중한 생명혈을 흘리는 살아있는 핵을 담고 있습니다. 휴식을 할 때 착용자는 많은 손상으로부터 보호하는 생명혈로 코팅됩니다.");

		break;
	case CHARM_SLOT::Jonis_Blessing:
		CharmState_.SlotCount_ = 4;
		SetInfoName( "조니의 축복");
		SetInfo( "친절한 이교도인 조니의 축복. 생체 유체를 파란 생명혈로 변화시킵니다. 착용자는 더 건강한 껍데기를 가지고 더 많은 손상을 견딜 수 있지만, 영혼을 집중하여 스스로를 치유할 수는 없습니다.");

		break;
	case CHARM_SLOT::Grubsong:
		CharmState_.SlotCount_ = 1;
		SetInfoName( "애벌레 노래 ");
		SetInfo( "해방된 애벌레의 감사를 담고 있습니다. 피해를 입을 때 영혼을 얻습니다.");

		break;
	case CHARM_SLOT::Grubberflys_Elegy:
		CharmState_.SlotCount_ = 3;
		SetInfoName( "애벌나비의 애가");
		SetInfo( "삶의 다음 단계로 넘어선 애벌레의 감사를 담고 있습니다. 무기에 신성한 힘을 가득 채웁니다. 착용자의 체력이 가득할 때 대못으로부터 하얀 뜨거운 에너지를 발사합니다.");

		break;
	case CHARM_SLOT::Hiveblood:
		CharmState_.SlotCount_ = 4;
		SetInfoName( "벌집의 정수");
		SetInfo( "벌집의 꿀이 굳어 형성된 귀중한 황금색 덩어리. 시간이 지남에 따라 착용자의 상처를 치유하여 영혼을 집중하지 않고 체력을 되찾을 수 있게 합니다.");

		break;
	case CHARM_SLOT::Spore_Shroom:
		CharmState_.SlotCount_ = 1;
		SetInfoName( "포자 버섯");
		SetInfo( "살아있는 곰팡이 물질로 구성되어 있습니다. 영혼에 노출되면 포자를 뿌립니다. 영혼을 집중할 때 지속적으로 적에게 피해를 입히는 포자를 방출합니다.");

		break;
	case CHARM_SLOT::Sharp_Shadow:
		CharmState_.SlotCount_ = 2;
		SetInfoName( "날카로운 그림자");
		SetInfo( "그림자를 치명적인 무기로 바꾸는 금지된 주문을 담고 있습니다. 그림자 대시를 사용할 때 착용자의 몸이 날카로워지고 적에게 피해를 입힙니다.");

		break;
	case CHARM_SLOT::Shape_of_Unn:
		CharmState_.SlotCount_ = 2;
		SetInfoName( "우운의 형상");
		SetInfo( "착용자 내에서 우운의 형상을 드러냅니다. 영혼을 집중하는 동안 착용자는 새로운 형태를 취하며, 적을 피하기 위해 자유롭게 움직일 수 있습니다.");

		break;
	case CHARM_SLOT::Nailmasters_Glory:
		CharmState_.SlotCount_ = 1;
		SetInfoName( "대못사부의 영예");
		SetInfo( "대못사부의 열정, 기술, 후회가 담겨 있습니다. 착용자의 대못 기술 숙달도를 증가시켜 자신의 힘을 더 빨리 집중하고 기술을 더 빨리 발휘할 수 있게 합니다.");

		break;
	case CHARM_SLOT::Dream_Wielder:
		CharmState_.SlotCount_ = 1;
		SetInfoName( "꿈의 주인");
		SetInfo( "몽환의 대못을 휘두르고 정수를 수집하는 이들을 위해 만들어진 부적. 착용자가 몽환의 대못을 더 빨리 충전하고 적을 공격할 때 더 많은 영혼을 수집할 수 있게 합니다.");

		break;
	case CHARM_SLOT::Kingsoul:
		CharmState_.SlotCount_ = 5;
		SetInfoName( "왕의 영혼");
		SetInfo( "천천히 영혼을 회복한다. 출생지로 들어가는 길을 열 수 있게 된다.");

		break;
	case CHARM_SLOT::Sprintmaster:
		CharmState_.SlotCount_ = 1;
		SetInfoName( "질주마스터");
		SetInfo( "질주마스터라고만 알려진 이상한 곤충의 모습을 하고 있는 부적. 착용자의 이동속도를 증가시켜서 위협을 피하거나 경쟁자를 추월할 수 있게 도와줍니다.");

		break;
	case CHARM_SLOT::Weaversong:
		CharmState_.SlotCount_ = 2;
		SetInfoName( "엮는 이의 노래");
		SetInfo( "자신의 고향으로 돌아간 엮는 이들의 작별 노래를 담고있는 비단으로 짜여진 부적. 외로운 착용자에게 친구와 수호자가 되어줄 존재를 소환합니다.");

		break;
	case CHARM_SLOT::Dreamshield:
		CharmState_.SlotCount_ = 3;
		SetInfoName( "몽환방패");
		SetInfo( "꿈을 형상화할 수 있는 부족이 사용하던 방어용 부적. 착용자를 따라다니며 지켜주는 방패를 생성합니다.");

		break;
	case CHARM_SLOT::Grimmchild:
		CharmState_.SlotCount_ = 2;
		SetInfoName( "그림의 아이");
		SetInfo( "그림 극단의 의식에 참여한 이들이 지니는 부적. 착용자는 그림의 동족들을 찾아내서 불꽃을 수집해야 합니다. 수집하지 못한 불꽃이 착용자의 지도에 표시됩니다.");

		break;
	default:
		break;
	}

	//GetRenderer()->SetParent(this);

}

void CharmSlot::CreateEquippedCharmSlot( CharmState _CharmState)
{
	// 부적 슬롯
	CreateRendererComponent({ 38, 38,1 }, "charm_cost.png");

	//부적 상태
	CharmState_.SlotNum_ = _CharmState.SlotNum_;
	CharmState_.SlotCount_ = _CharmState.SlotCount_;
	CharmState_.KnihgistHas_ = _CharmState.KnihgistHas_;
	CharmState_.isUsing_ = _CharmState.isUsing_;
	CharmState_.isEquippedSlot_ = true;
	CharmState_.isEquippedSlotUsing_ = false;


	//부적
	Charm_ = GetLevel()->CreateActor<Charm>();
	//Charm_->CreateCharm(_SlotName, _CharmFilePath, { 131, 128, 1 });

	Charm_->SetParent(this);

	SetPointerSize({ 38 , 38, 1});

}

void CharmSlot::CreateCopyCharm(GameEngineUIRenderer* _RenderData, std::string _SlotName, std::string _FilePath)
{


	CharmState_.CharmFilePath_ = _FilePath;
	CharmState_.CharmName_ = _SlotName;

	Charm_->CreateCharm(_SlotName, _FilePath, { 131, 128, 1 });
	SetPointerSize(Charm_->GetRenderer()->GetCurTexture()->GetScale());

}


void CharmSlot::CharmSetMoveLeft()
{

}