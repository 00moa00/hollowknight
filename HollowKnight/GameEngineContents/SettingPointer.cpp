#include "PreCompile.h"
#include "SettingPointer.h"
#include "HollowKnightLevel.h"
#include "PointActorComponent.h"
#include "GlobalContentsValue.h"
#include "KnightData.h"

#include <algorithm>


SettingPointer::SettingPointer() 
	:

	isMoveRenderer_(false),

	inRightArrow_(false),
	inLeftArrow_(false),

	isMoveRendererDeath_(false),

	isDownLextPageLeft_(false),
	isDownNextPageRight_(false),

	CurrentPosInCharmPage(0),
	CurrentPosInMapPage(0),
	CurrentPosInMonsterPage(0),
	PointerMoveSpeed_(750.f),

	CharmMovePointer_(nullptr)

{
}

SettingPointer::~SettingPointer() 
{
}

void SettingPointer::Start()
{
	SettingPointerBox_ = GetLevel()->CreateActor<SettingPointerBox>();

	//=========================================
	//    CreateKey
	//=========================================
	if (false == GameEngineInput::GetInst()->IsKey("MoveRight"))
	{
		GameEngineInput::GetInst()->CreateKey("MoveRight", VK_RIGHT);
		GameEngineInput::GetInst()->CreateKey("MoveLeft", VK_LEFT);
		GameEngineInput::GetInst()->CreateKey("MoveDown", VK_DOWN);
		GameEngineInput::GetInst()->CreateKey("MoveUp", VK_UP);
		GameEngineInput::GetInst()->CreateKey("Select", VK_RETURN);
	}

	//=========================================
	//    SettingPointerCharmPageManager
	//=========================================

	SettingPointerCharmPageManager_.CreateStateMember("POINTER_MOVE"
		, std::bind(&SettingPointer::PointerCharmPageMoveUpdate, this, std::placeholders::_1, std::placeholders::_2)
		, std::bind(&SettingPointer::PointerCharmPageMoveStart, this, std::placeholders::_1)
		, std::bind(&SettingPointer::PointerCharmPageMoveEnd, this, std::placeholders::_1));

	SettingPointerCharmPageManager_.CreateStateMember("IDLE"
		, std::bind(&SettingPointer::PointerCharmPageIdleUpdate, this, std::placeholders::_1, std::placeholders::_2)
		, std::bind(&SettingPointer::PointerCharmPageIdleStart, this, std::placeholders::_1)
		, std::bind(&SettingPointer::PointerCharmPageIdleEnd, this, std::placeholders::_1));

	SettingPointerCharmPageManager_.CreateStateMember("MOVE_RIGHT"
		, std::bind(&SettingPointer::PointerCharmPageMoveRightUpdate, this, std::placeholders::_1, std::placeholders::_2)
		, std::bind(&SettingPointer::PointerCharmPageMoveRightStart, this, std::placeholders::_1)
		, std::bind(&SettingPointer::PointerCharmPageMoveRightEnd, this, std::placeholders::_1));

	SettingPointerCharmPageManager_.CreateStateMember("MOVE_LEFT"
		, std::bind(&SettingPointer::PointerCharmPageMoveLeftUpdate, this, std::placeholders::_1, std::placeholders::_2)
		, std::bind(&SettingPointer::PointerCharmPageMoveLeftStart, this, std::placeholders::_1)
		, std::bind(&SettingPointer::PointerCharmPageMoveLeftEnd, this, std::placeholders::_1));

	SettingPointerCharmPageManager_.CreateStateMember("IN_RIGHT_ARROW"
		, std::bind(&SettingPointer::PointerInCharmPageRightArrowUpdate, this, std::placeholders::_1, std::placeholders::_2)
		, std::bind(&SettingPointer::PointerInCharmPageRightArrowStart, this, std::placeholders::_1)
		, std::bind(&SettingPointer::PointerInCharmPageRightArrowEnd, this, std::placeholders::_1));

	SettingPointerCharmPageManager_.CreateStateMember("IN_LEFT_ARROW"
		, std::bind(&SettingPointer::PointerCharmPageInLeftArrowUpdate, this, std::placeholders::_1, std::placeholders::_2)
		, std::bind(&SettingPointer::PointerCharmPageInLeftArrowStart, this, std::placeholders::_1)
		, std::bind(&SettingPointer::PointerCharmPageInLeftArrowEnd, this, std::placeholders::_1));

	SettingPointerCharmPageManager_.CreateStateMember("WAIT"
		, std::bind(&SettingPointer::PointerCharmPageWaitUpdate, this, std::placeholders::_1, std::placeholders::_2)
		, std::bind(&SettingPointer::PointerCharmPageWaitStart, this, std::placeholders::_1)
		, std::bind(&SettingPointer::PointerCharmPageWaitEnd, this, std::placeholders::_1));

	SettingPointerCharmPageManager_.CreateStateMember("SORT_SLOT"
		, std::bind(&SettingPointer::PointerChramPageSortSlotUpdate, this, std::placeholders::_1, std::placeholders::_2)
		, std::bind(&SettingPointer::PointerChramPageSortSlotStart, this, std::placeholders::_1)
		, std::bind(&SettingPointer::PointerChramPageSortSlotEnd, this, std::placeholders::_1));

	SettingPointerCharmPageManager_.CreateStateMember("NEXT_SORT_SLOT"
		, std::bind(&SettingPointer::PointerChramPageNextSortSlotUpdate, this, std::placeholders::_1, std::placeholders::_2)
		, std::bind(&SettingPointer::PointerChramPageNextSortSlotStart, this, std::placeholders::_1)
		, std::bind(&SettingPointer::PointerChramPageNextSortSlotEnd, this, std::placeholders::_1));

	SettingPointerCharmPageManager_.CreateStateMember("MOVE_RENDERDER"
		, std::bind(&SettingPointer::PointerChramPageMoveRendererMoveUpdate, this, std::placeholders::_1, std::placeholders::_2)
		, std::bind(&SettingPointer::PointerChramPageMoveRendererMoveStart, this, std::placeholders::_1)
		, std::bind(&SettingPointer::PointerChramPageMoveRendererMoveEnd, this, std::placeholders::_1));

	SettingPointerCharmPageManager_.ChangeState("IDLE");


	//=========================================
	//    SettingPointerInventoyPageManager
	//=========================================
	SettingPointerInventoryPageManager_.CreateStateMember("POINTER_MOVE"
		, std::bind(&SettingPointer::PointerInventoryPageMoveUpdate, this, std::placeholders::_1, std::placeholders::_2)
		, std::bind(&SettingPointer::PointerInventoryPageMoveStart, this, std::placeholders::_1)
		, std::bind(&SettingPointer::PointerInventoryPageMoveEnd, this, std::placeholders::_1));


	SettingPointerInventoryPageManager_.CreateStateMember("IDLE"
		, std::bind(&SettingPointer::PointerInventoryPageIdleUpdate, this, std::placeholders::_1, std::placeholders::_2)
		, std::bind(&SettingPointer::PointerInventoryPageIdleStart, this, std::placeholders::_1)
		, std::bind(&SettingPointer::PointerInventoryPageIdleEnd, this, std::placeholders::_1));

	SettingPointerInventoryPageManager_.CreateStateMember("MOVE_LEFT"
		, std::bind(&SettingPointer::PointerInventoryPageMoveLeftUpdate, this, std::placeholders::_1, std::placeholders::_2)
		, std::bind(&SettingPointer::PointerInventoryPageMoveLeftStart, this, std::placeholders::_1)
		, std::bind(&SettingPointer::PointerInventoryPageMoveLeftEnd, this, std::placeholders::_1));

	SettingPointerInventoryPageManager_.CreateStateMember("MOVE_RIGHT"
		, std::bind(&SettingPointer::PointerInventoryPageMoveRightUpdate, this, std::placeholders::_1, std::placeholders::_2)
		, std::bind(&SettingPointer::PointerInventoryPageMoveRightStart, this, std::placeholders::_1)
		, std::bind(&SettingPointer::PointerInventoryPageMoveRightEnd, this, std::placeholders::_1));

	SettingPointerInventoryPageManager_.CreateStateMember("IN_RIGHT_ARROW"
		, std::bind(&SettingPointer::PointerInInventoryPageRightArrowUpdate, this, std::placeholders::_1, std::placeholders::_2)
		, std::bind(&SettingPointer::PointerInInventoryPageRightArrowStart, this, std::placeholders::_1)
		, std::bind(&SettingPointer::PointerInInventoryPageRightArrowEnd, this, std::placeholders::_1));

	SettingPointerInventoryPageManager_.CreateStateMember("IN_LEFT_ARROW"
		, std::bind(&SettingPointer::PointerInventoryPageInLeftArrowUpdate, this, std::placeholders::_1, std::placeholders::_2)
		, std::bind(&SettingPointer::PointerInventoryPageInLeftArrowStart, this, std::placeholders::_1)
		, std::bind(&SettingPointer::PointerInventoryPageInLeftArrowEnd, this, std::placeholders::_1));

	SettingPointerInventoryPageManager_.CreateStateMember("WAIT"
		, std::bind(&SettingPointer::PointerInventoryPageWaitUpdate, this, std::placeholders::_1, std::placeholders::_2)
		, std::bind(&SettingPointer::PointerInventoryPageWaitStart, this, std::placeholders::_1)
		, std::bind(&SettingPointer::PointerInventoryPageWaitEnd, this, std::placeholders::_1));

	SettingPointerInventoryPageManager_.ChangeState("WAIT");


	//=========================================
	//    SettingPointerInventoyPageManager
	//=========================================

	SettingPointerMapPageManager_.CreateStateMember("IDLE"
		, std::bind(&SettingPointer::PointerMapPageIdleUpdate, this, std::placeholders::_1, std::placeholders::_2)
		, std::bind(&SettingPointer::PointerMapPageIdleStart, this, std::placeholders::_1)
		, std::bind(&SettingPointer::PointerMapPageIdleEnd, this, std::placeholders::_1));

	SettingPointerMapPageManager_.CreateStateMember("MOVE_LEFT"
		, std::bind(&SettingPointer::PointerPageMoveLeftUpdate, this, std::placeholders::_1, std::placeholders::_2)
		, std::bind(&SettingPointer::PointerPageMoveLeftStart, this, std::placeholders::_1)
		, std::bind(&SettingPointer::PointerPageMoveLeftEnd, this, std::placeholders::_1));

	SettingPointerMapPageManager_.CreateStateMember("MOVE_RIGHT"
		, std::bind(&SettingPointer::PointerMapPageMoveRightUpdate, this, std::placeholders::_1, std::placeholders::_2)
		, std::bind(&SettingPointer::PointerMapPageMoveRightStart, this, std::placeholders::_1)
		, std::bind(&SettingPointer::PointerMapPageMoveRightEnd, this, std::placeholders::_1));

	SettingPointerMapPageManager_.CreateStateMember("IN_RIGHT_ARROW"
		, std::bind(&SettingPointer::PointerMapPageRightArrowUpdate, this, std::placeholders::_1, std::placeholders::_2)
		, std::bind(&SettingPointer::PointerMapPageRightArrowStart, this, std::placeholders::_1)
		, std::bind(&SettingPointer::PointerMapPageRightArrowEnd, this, std::placeholders::_1));

	SettingPointerMapPageManager_.CreateStateMember("IN_LEFT_ARROW"
		, std::bind(&SettingPointer::PointerMapPageInLeftArrowUpdate, this, std::placeholders::_1, std::placeholders::_2)
		, std::bind(&SettingPointer::PointerMapPageInLeftArrowStart, this, std::placeholders::_1)
		, std::bind(&SettingPointer::PointerMapPageInLeftArrowEnd, this, std::placeholders::_1));

	SettingPointerMapPageManager_.CreateStateMember("WAIT"
		, std::bind(&SettingPointer::PointerMapPageWaitUpdate, this, std::placeholders::_1, std::placeholders::_2)
		, std::bind(&SettingPointer::PointerMapPageWaitStart, this, std::placeholders::_1)
		, std::bind(&SettingPointer::PointerMapPageWaitEnd, this, std::placeholders::_1));

	SettingPointerMapPageManager_.CreateStateMember("WIDE"
		, std::bind(&SettingPointer::PointerMapPageWideMapUpdate, this, std::placeholders::_1, std::placeholders::_2)
		, std::bind(&SettingPointer::PointerMapPageWideMapStart, this, std::placeholders::_1)
		, std::bind(&SettingPointer::PointerMapPageWideMapEnd, this, std::placeholders::_1));


	SettingPointerMapPageManager_.ChangeState("WAIT");



	CurrentPage_ = PAGE_TYPE::Charm;

}

void SettingPointer::Update(float _DeltaTime)
{
	switch (CurrentPage_)
	{
	case PAGE_TYPE::Charm:
		SettingPointerCharmPageManager_.Update(_DeltaTime);
		break;

	case PAGE_TYPE::Map:
		SettingPointerMapPageManager_.Update(_DeltaTime);

		break;
	case PAGE_TYPE::Inventory:
		SettingPointerInventoryPageManager_.Update(_DeltaTime);
		break;
	default:
		break;
	}
}

void SettingPointer::SetCharmPageActorMax()
{
	CharmPageActorCount = GetLevel<HollowKnightLevel>()->PointActorListCharm.size()-3 ;
}

void SettingPointer::SetMapPageActorMax()
{
	MapPageActorCount = GetLevel<HollowKnightLevel>()->PointActorListMap.size(); 
}

void SettingPointer::SetMonsterBookActorMax()
{
	MonsterPageActorCount = GetLevel<HollowKnightLevel>()->PointActorListMonsterBook.size() ;
}

void SettingPointer::PointerBoxRenderOn()
{
	SettingPointerBox_->AllPointerOn();
}

void SettingPointer::PointerBoxRenderOff()
{
	SettingPointerBox_->AllPointerOff();
}

void SettingPointer::AllOn()
{
	this->On();
	SettingPointerBox_->On();
}

void SettingPointer::AllOff()
{
	this->Off();
	SettingPointerBox_->Off();
}

void SettingPointer::SetFirstPosCharmPage()
{
	PointActorComponent* PointActorComponent_ = GetLevel<HollowKnightLevel>()->PointActorListCharm.find(0)->second;

	SettingPointerBox_->GetTransform().SetWorldPosition({ PointActorComponent_->GetPointActor()->GetTransform().GetLocalPosition().x
		, PointActorComponent_->GetPointActor()->GetTransform().GetLocalPosition().y
		, static_cast<float>(Z_ORDER::UI_Border) });

	SettingPointerBox_->SetBoxSize({ PointActorComponent_->GetPointActor()->GetPointerSize()/2 });
}


void SettingPointer::SetCurrentPage(PAGE_TYPE _PageType)
{
	PrevPage_ = CurrentPage_;
	CurrentPage_ = _PageType;
	PointActorComponent* PointActorComponent_;

	switch (_PageType)
	{
	case PAGE_TYPE::Charm:
		SettingPointerBox_->AllPointerOn();

		if (PrevPage_ == PAGE_TYPE::Map)
		{
			inRightArrow_ = false;
			CurrentPosInCharmPage = 0;


			//CurrentPosInCharmPage = static_cast<int>(CHAR_PAGE_ACTOR::LeftArrow);

			SettingPointerCharmPageManager_.ChangeState("IDLE");
			SettingPointerInventoryPageManager_.ChangeState("WAIT");
			SettingPointerMapPageManager_.ChangeState("WAIT");

			PointActorComponent_ = GetLevel<HollowKnightLevel>()->PointActorListCharm.find(0)->second;

			SettingPointerBox_->GetTransform().SetWorldPosition({ PointActorComponent_->GetPointActor()->GetTransform().GetLocalPosition().x
				, PointActorComponent_->GetPointActor()->GetTransform().GetLocalPosition().y
				, static_cast<float>(Z_ORDER::UI_Border) });

			SettingPointerBox_->SetBoxSize({ PointActorComponent_->GetPointActor()->GetPointerSize() / 2 });
		}

		if (PrevPage_ == PAGE_TYPE::Inventory)
		{
			inLeftArrow_ = false;

			//CurrentPosInCharmPage = static_cast<int>(CHAR_PAGE_ACTOR::RightArrow);
			CurrentPosInCharmPage = 0;

			SettingPointerCharmPageManager_.ChangeState("IDLE");
			SettingPointerInventoryPageManager_.ChangeState("WAIT");
			SettingPointerMapPageManager_.ChangeState("WAIT");

			PointActorComponent_ = GetLevel<HollowKnightLevel>()->PointActorListCharm.find(0)->second;

			SettingPointerBox_->GetTransform().SetWorldPosition({ PointActorComponent_->GetPointActor()->GetTransform().GetLocalPosition().x
				, PointActorComponent_->GetPointActor()->GetTransform().GetLocalPosition().y
				, static_cast<float>(Z_ORDER::UI_Border) });

			SettingPointerBox_->SetBoxSize({ PointActorComponent_->GetPointActor()->GetPointerSize() / 2 });
		}

		break;
	case PAGE_TYPE::Inventory:
		SettingPointerBox_->AllPointerOn();

		if (PrevPage_ == PAGE_TYPE::Charm)
		{
			inRightArrow_ = false;

			CurrentPosInInventoryPage = 0;

			SettingPointerInventoryPageManager_.ChangeState("IDLE");
			SettingPointerCharmPageManager_.ChangeState("WAIT");
			SettingPointerMapPageManager_.ChangeState("WAIT");


			PointActorComponent_ = GetLevel<HollowKnightLevel>()->PointActorListInventory.find(0)->second;

			SettingPointerBox_->GetTransform().SetWorldPosition({ PointActorComponent_->GetPointActor()->GetTransform().GetLocalPosition().x
				, PointActorComponent_->GetPointActor()->GetTransform().GetLocalPosition().y
				, static_cast<float>(Z_ORDER::UI_Border) });

			SettingPointerBox_->SetBoxSize({ PointActorComponent_->GetPointActor()->GetPointerSize() / 2 });

		}

		if (PrevPage_ == PAGE_TYPE::Map)
		{
			inLeftArrow_ = false;

			CurrentPosInInventoryPage = 0;

			SettingPointerInventoryPageManager_.ChangeState("IDLE");
			SettingPointerCharmPageManager_.ChangeState("WAIT");
			SettingPointerMapPageManager_.ChangeState("WAIT");


			PointActorComponent_ = GetLevel<HollowKnightLevel>()->PointActorListInventory.find(0)->second;

			SettingPointerBox_->GetTransform().SetWorldPosition({ PointActorComponent_->GetPointActor()->GetTransform().GetLocalPosition().x
				, PointActorComponent_->GetPointActor()->GetTransform().GetLocalPosition().y
				, static_cast<float>(Z_ORDER::UI_Border) });

			SettingPointerBox_->SetBoxSize({ PointActorComponent_->GetPointActor()->GetPointerSize() / 2 });

		}


	

		break;
	case PAGE_TYPE::Map:
		if (PrevPage_ == PAGE_TYPE::Inventory)
		{
			inRightArrow_ = false;

			CurrentPosInMapPage = 0;

			SettingPointerMapPageManager_.ChangeState("IDLE");

			SettingPointerCharmPageManager_.ChangeState("WAIT");
			SettingPointerInventoryPageManager_.ChangeState("WAIT");
			PointActorComponent_ = GetLevel<HollowKnightLevel>()->PointActorListMap.find(0)->second;

			SettingPointerBox_->GetTransform().SetWorldPosition({ PointActorComponent_->GetPointActor()->GetTransform().GetLocalPosition().x
				, PointActorComponent_->GetPointActor()->GetTransform().GetLocalPosition().y
				, static_cast<float>(Z_ORDER::UI_Border) });

			SettingPointerBox_->SetBoxSize({ PointActorComponent_->GetPointActor()->GetPointerSize() / 2 });

			WorldMap* FindMap = dynamic_cast<WorldMap*>(PointActorComponent_->GetPointActor());
			FindMap->ChangeTextureSelect();
		}

		if (PrevPage_ == PAGE_TYPE::Charm)
		{
			inLeftArrow_ = false;

			CurrentPosInMapPage = 0;


			SettingPointerMapPageManager_.ChangeState("IDLE");

			SettingPointerCharmPageManager_.ChangeState("WAIT");
			SettingPointerInventoryPageManager_.ChangeState("WAIT");

			PointActorComponent_ = GetLevel<HollowKnightLevel>()->PointActorListMap.find(0)->second;

			SettingPointerBox_->GetTransform().SetWorldPosition({ PointActorComponent_->GetPointActor()->GetTransform().GetLocalPosition().x
				, PointActorComponent_->GetPointActor()->GetTransform().GetLocalPosition().y
				, static_cast<float>(Z_ORDER::UI_Border) });

			SettingPointerBox_->SetBoxSize({ PointActorComponent_->GetPointActor()->GetPointerSize() / 2 });

			WorldMap* FindMap = dynamic_cast<WorldMap*>(PointActorComponent_->GetPointActor());
			FindMap->ChangeTextureSelect();
		}


		break;

	default:
		break;
	}

}
