#include "PreCompile.h"
#include "SettingPointer.h"
#include "HollowKnightLevel.h"
#include "PointActorComponent.h"
#include "GlobalContentsValue.h"
#include "KnightData.h"

#include <algorithm>


SettingPointer::SettingPointer() 
	:

	inRightArrow_(false),
	inLeftArrow_(false),

	isDownLextPageLeft_(false),
	isDownNextPageRight_(false),

	CurrentPosInCharmPage(0),
	CurrentPosInMapPage(0),
	CurrentPosInMonsterPage(0)


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




	SettingPointerCharmPageManager_.ChangeState("IDLE");



	//=========================================
	//    SettingPointerInventoyPageManager
	//=========================================

	SettingPointerInventoyPageManager_.CreateStateMember("IDLE"
		, std::bind(&SettingPointer::PointerInventoryPageIdleUpdate, this, std::placeholders::_1, std::placeholders::_2)
		, std::bind(&SettingPointer::PointerInventoryPageIdleStart, this, std::placeholders::_1)
		, std::bind(&SettingPointer::PointerInventoryPageIdleEnd, this, std::placeholders::_1));

	SettingPointerInventoyPageManager_.CreateStateMember("MOVE_LEFT"
		, std::bind(&SettingPointer::PointerInventoryPageMoveLeftUpdate, this, std::placeholders::_1, std::placeholders::_2)
		, std::bind(&SettingPointer::PointerInventoryPageMoveLeftStart, this, std::placeholders::_1)
		, std::bind(&SettingPointer::PointerInventoryPageMoveLeftEnd, this, std::placeholders::_1));

	SettingPointerInventoyPageManager_.CreateStateMember("MOVE_RIGHT"
		, std::bind(&SettingPointer::PointerInventoryPageMoveRightUpdate, this, std::placeholders::_1, std::placeholders::_2)
		, std::bind(&SettingPointer::PointerInventoryPageMoveRightStart, this, std::placeholders::_1)
		, std::bind(&SettingPointer::PointerInventoryPageMoveRightEnd, this, std::placeholders::_1));

	SettingPointerInventoyPageManager_.CreateStateMember("IN_RIGHT_ARROW"
		, std::bind(&SettingPointer::PointerInInventoryPageRightArrowUpdate, this, std::placeholders::_1, std::placeholders::_2)
		, std::bind(&SettingPointer::PointerInInventoryPageRightArrowStart, this, std::placeholders::_1)
		, std::bind(&SettingPointer::PointerInInventoryPageRightArrowEnd, this, std::placeholders::_1));

	SettingPointerInventoyPageManager_.CreateStateMember("IN_LEFT_ARROW"
		, std::bind(&SettingPointer::PointerInventoryPageInLeftArrowUpdate, this, std::placeholders::_1, std::placeholders::_2)
		, std::bind(&SettingPointer::PointerInventoryPageInLeftArrowStart, this, std::placeholders::_1)
		, std::bind(&SettingPointer::PointerInventoryPageInLeftArrowEnd, this, std::placeholders::_1));

	SettingPointerInventoyPageManager_.CreateStateMember("WAIT"
		, std::bind(&SettingPointer::PointerInventoryPageWaitUpdate, this, std::placeholders::_1, std::placeholders::_2)
		, std::bind(&SettingPointer::PointerInventoryPageWaitStart, this, std::placeholders::_1)
		, std::bind(&SettingPointer::PointerInventoryPageWaitEnd, this, std::placeholders::_1));



	SettingPointerInventoyPageManager_.ChangeState("IDLE");


	CurrentPage_ = PAGE_TYPE::Charm;

}

void SettingPointer::Update(float _DeltaTime)
{
	switch (CurrentPage_)
	{
	case PAGE_TYPE::Charm:
		SettingPointerCharmPageManager_.Update(_DeltaTime);
		break;
	case PAGE_TYPE::MonsterBook:
		break;
	case PAGE_TYPE::Map:
		break;
	case PAGE_TYPE::Inventory:
		SettingPointerInventoyPageManager_.Update(_DeltaTime);
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

void SettingPointer::SetFirstPosMapPage()
{

	PointActorComponent* PointActorComponent_ = GetLevel<HollowKnightLevel>()->PointActorListMap.find(1)->second;

	SettingPointerBox_->GetTransform().SetWorldPosition({ PointActorComponent_->GetPointActor()->GetTransform().GetLocalPosition().x
		, PointActorComponent_->GetPointActor()->GetTransform().GetLocalPosition().y
		, static_cast<float>(Z_ORDER::UI_Border) });

	SettingPointerBox_->SetBoxSize({ PointActorComponent_->GetPointActor()->GetPointerSize() / 2 });
}

void SettingPointer::SetFirstPosMonsterBookPage()
{
	PointActorComponent* PointActorComponent_ = GetLevel<HollowKnightLevel>()->PointActorListMonsterBook.find(1)->second;

	SettingPointerBox_->GetTransform().SetWorldPosition({ PointActorComponent_->GetPointActor()->GetTransform().GetLocalPosition().x
		, PointActorComponent_->GetPointActor()->GetTransform().GetLocalPosition().y
		, static_cast<float>(Z_ORDER::UI_Border) });

	SettingPointerBox_->SetBoxSize({ PointActorComponent_->GetPointActor()->GetPointerSize() / 2 });
}

void SettingPointer::SetCurrentPage(PAGE_TYPE _PageType)
{
	PrevPage_ = CurrentPage_;
	CurrentPage_ = _PageType;
	PointActorComponent* PointActorComponent_;

	switch (_PageType)
	{
	case PAGE_TYPE::Charm:
		if (PrevPage_ == PAGE_TYPE::Map)
		{
			CurrentPosInCharmPage = static_cast<int>(CHAR_PAGE_ACTOR::LeftArrow);
			SettingPointerCharmPageManager_.ChangeState("IN_LEFT_ARROW");
			SettingPointerInventoyPageManager_.ChangeState("WAIT");

		}

		if (PrevPage_ == PAGE_TYPE::Inventory)
		{
			CurrentPosInCharmPage = static_cast<int>(CHAR_PAGE_ACTOR::RightArrow);
			inLeftArrow_ = false;

			SettingPointerCharmPageManager_.ChangeState("IN_RIGHT_ARROW");
			SettingPointerInventoyPageManager_.ChangeState("WAIT");

		}


		PointActorComponent_ = GetLevel<HollowKnightLevel>()->PointActorListCharm.find(CurrentPosInCharmPage)->second;

		SettingPointerBox_->GetTransform().SetWorldPosition({ PointActorComponent_->GetPointActor()->GetTransform().GetLocalPosition().x
			, PointActorComponent_->GetPointActor()->GetTransform().GetLocalPosition().y
			, static_cast<float>(Z_ORDER::UI_Border) });

		SettingPointerBox_->SetBoxSize({ PointActorComponent_->GetPointActor()->GetPointerSize() / 2 });

		break;
	case PAGE_TYPE::Inventory:

		if (PrevPage_ == PAGE_TYPE::Charm)
		{
			CurrentPosInInventoryPage = static_cast<int>(CHAR_PAGE_ACTOR::LeftArrow);
			inRightArrow_ = false;
			SettingPointerInventoyPageManager_.ChangeState("IN_LEFT_ARROW");
			SettingPointerCharmPageManager_.ChangeState("WAIT");

		}

		if (PrevPage_ == PAGE_TYPE::Map)
		{
			CurrentPosInInventoryPage = static_cast<int>(CHAR_PAGE_ACTOR::RightArrow);
			SettingPointerInventoyPageManager_.ChangeState("IN_RIGHT_ARROW");
			SettingPointerCharmPageManager_.ChangeState("WAIT");

		}


		PointActorComponent_ = GetLevel<HollowKnightLevel>()->PointActorListInventory.find(CurrentPosInInventoryPage)->second;

		SettingPointerBox_->GetTransform().SetWorldPosition({ PointActorComponent_->GetPointActor()->GetTransform().GetLocalPosition().x
			, PointActorComponent_->GetPointActor()->GetTransform().GetLocalPosition().y
			, static_cast<float>(Z_ORDER::UI_Border) });

		SettingPointerBox_->SetBoxSize({ PointActorComponent_->GetPointActor()->GetPointerSize() / 2 });

		break;
	case PAGE_TYPE::MonsterBook:
		break;
	case PAGE_TYPE::Map:
		break;
	default:
		break;
	}

}

void SettingPointer::PointerCharmPageIdleStart(const StateInfo& _Info)
{
}

void SettingPointer::PointerCharmPageIdleUpdate(float _DeltaTime, const StateInfo& _Info)
{
	if (true == GameEngineInput::GetInst()->IsDown("MoveRight"))
	{
		SettingPointerCharmPageManager_.ChangeState("MOVE_RIGHT");
	}

	if (true == GameEngineInput::GetInst()->IsDown("MoveLeft"))
	{
		SettingPointerCharmPageManager_.ChangeState("MOVE_LEFT");

	}

	if (true == GameEngineInput::GetInst()->IsDown("MoveUp"))
	{

		int PrevCount = CurrentPosInCharmPage;
		CurrentPosInCharmPage -= 10;

		if (CurrentPosInCharmPage < 0)
		{
			CurrentPosInCharmPage += 50;
		}
		else if (CurrentPosInCharmPage >= 30)
		{
			CurrentPosInCharmPage = PrevCount;
		}

		PointActorComponent* PointActorComponent_ = GetLevel<HollowKnightLevel>()->PointActorListCharm.find(CurrentPosInCharmPage)->second;

		SettingPointerBox_->GetTransform().SetWorldPosition({ PointActorComponent_->GetPointActor()->GetTransform().GetLocalPosition().x
			, PointActorComponent_->GetPointActor()->GetTransform().GetLocalPosition().y
			, static_cast<float>(Z_ORDER::UI_Border) });

		SettingPointerBox_->SetBoxSize({ PointActorComponent_->GetPointActor()->GetPointerSize() / 2 });
	}

	if (true == GameEngineInput::GetInst()->IsDown("MoveDown"))
	{

		int PrevCount = CurrentPosInCharmPage;
		CurrentPosInCharmPage += 10;

		if (CurrentPosInCharmPage > CharmPageActorCount)
		{
			if (CurrentPosInCharmPage >= 50)
			{
				CurrentPosInCharmPage -= 50;
			}
		}

		else if(CurrentPosInCharmPage >= 40) //위에서 10씩 더해주고있으니까 생각하고 있는 인덱스 + 10
		{
			CurrentPosInCharmPage = PrevCount;
		}

		PointActorComponent* PointActorComponent_ = GetLevel<HollowKnightLevel>()->PointActorListCharm.find(CurrentPosInCharmPage)->second;

		SettingPointerBox_->GetTransform().SetWorldPosition({ PointActorComponent_->GetPointActor()->GetTransform().GetLocalPosition().x
			, PointActorComponent_->GetPointActor()->GetTransform().GetLocalPosition().y
			, static_cast<float>(Z_ORDER::UI_Border) });

		SettingPointerBox_->SetBoxSize({ PointActorComponent_->GetPointActor()->GetPointerSize() / 2 });
	}


	if (true == GameEngineInput::GetInst()->IsDown("Select"))
	{

		PointActorComponent* PointActorComponent_ = GetLevel<HollowKnightLevel>()->PointActorListCharm.find(CurrentPosInCharmPage)->second;
		CharmSlot* slot = dynamic_cast<CharmSlot*>(PointActorComponent_->GetPointActor());


		// 부적 장착이 가능한지 && 내가 선택한 부적이 사용중이 아닌건지 && 부적 슬롯이 아니다
		if (KnightData::GetInst()->SubUsingCharmNotches(slot->GetSlotCount()) == true
			&& slot->GetisUsing() == false 
			&& slot->GetisEquippedSlot() == false)
		{
			for (int i = 40; i < 50; ++i)
			{
				//NotesSlot : 장착 가능한 슬롯, slot: 현재 포인트 하고있는 슬롯
				PointActorComponent* PointActorComponent_ = GetLevel<HollowKnightLevel>()->PointActorListCharm.find(i)->second;
				CharmSlot* NotesSlot = dynamic_cast<CharmSlot*>(PointActorComponent_->GetPointActor());

				//부적 장착중이 아니라면
				if (NotesSlot->GetisEquippedSlotUsing() == false)
				{
					NotesSlot->CreateCopyCharm(slot->GetRenderer(), slot->GetCharmName(), slot->GetFilePath());
					NotesSlot->SetisEquippedSlotUsing(true);
					NotesSlot->SetUsingSlotNum(slot->GetSlotNum());

					slot->SetisUsing(true);

					//사용 가능한 부적 칸 수(노치) 갱신
					for (int j = 0; j < KnightData::GetInst()->GetUsingCharmNotches(); ++j)
					{
						GetLevel<HollowKnightLevel>()->AllNotes_[j]->SetNotchesUsed();
					}

					//위에 모든걸 적용하고도 다음에 부적이 또 달 수있는 남은 칸이 있다면, 뒤에있는 빈 슬롯을 표시한다
					if (KnightData::GetInst()->GetUsingCharmNotches() > 0)
					{
						PointActorComponent* PointActorComponent_ = GetLevel<HollowKnightLevel>()->PointActorListCharm.find(i+1)->second;
						CharmSlot* NotesSlot = dynamic_cast<CharmSlot*>(PointActorComponent_->GetPointActor());
						NotesSlot->GetRenderer()->On();
					}

					break;
				}
			}
		}
		
		else if(slot->GetisEquippedSlotUsing() == true)
		{

			//해당 부적을 사용하고 있지 않음으로 바꿔야한다.
			PointActorComponent* PointActorComponent_ = GetLevel<HollowKnightLevel>()->PointActorListCharm.find(slot->GetUsingSlotNum())->second;
			CharmSlot* SearchSlot = dynamic_cast<CharmSlot*>(PointActorComponent_->GetPointActor());

			KnightData::GetInst()->AddUsingCharmNotches(SearchSlot->GetSlotCount());
			SearchSlot->SetisUsing(false);

			slot->SetUsingSlotNum(-1);
			slot->SetisEquippedSlotUsing(false);
			slot->GetCharm()->GetRenderer()->Death();

			//사용 가능한 부적 칸 수(노치) 갱신
			for (int j = KnightData::GetInst()->GetCharmNotches()-1; j > KnightData::GetInst()->GetUsingCharmNotches()-1; --j)
			{
				GetLevel<HollowKnightLevel>()->AllNotes_[j]->SetNotchesNotUsed();
			}
		}
	}

}

void SettingPointer::PointerCharmPageIdleEnd(const StateInfo& _Info)
{
}

void SettingPointer::PointerCharmPageMoveLeftStart(const StateInfo& _Info)
{
	if (true == GameEngineInput::GetInst()->IsDown("MoveLeft") && inLeftArrow_ == false)
	{
		inRightArrow_ = false;
		int PrevCount = CurrentPosInCharmPage;


		if ((PrevCount % 10 == 0 ) && _Info.PrevState != "IN_RIGHT_ARROW")
		{
			--CurrentPosInCharmPage;
			SettingPointerCharmPageManager_.ChangeState("IN_LEFT_ARROW");
			return;
		}

		else
		{
			--CurrentPosInCharmPage;

			if (CurrentPosInCharmPage < 0)
			{
				CurrentPosInCharmPage = CharmPageActorCount;
			}

			PointActorComponent* PointActorComponent_ = GetLevel<HollowKnightLevel>()->PointActorListCharm.find(CurrentPosInCharmPage)->second;

			SettingPointerBox_->GetTransform().SetWorldPosition({ PointActorComponent_->GetPointActor()->GetTransform().GetLocalPosition().x
				, PointActorComponent_->GetPointActor()->GetTransform().GetLocalPosition().y
				, static_cast<float>(Z_ORDER::UI_Border) });

			SettingPointerBox_->SetBoxSize({ PointActorComponent_->GetPointActor()->GetPointerSize() / 2 });
		}
	}

}

void SettingPointer::PointerCharmPageMoveLeftUpdate(float _DeltaTime, const StateInfo& _Info)
{
	SettingPointerCharmPageManager_.ChangeState("IDLE");

}

void SettingPointer::PointerCharmPageMoveLeftEnd(const StateInfo& _Info)
{

}

void SettingPointer::PointerCharmPageMoveRightStart(const StateInfo& _Info)
{
	if (true == GameEngineInput::GetInst()->IsDown("MoveRight") && inRightArrow_ == false)
	{
		inLeftArrow_ = false;
		int PrevCount = CurrentPosInCharmPage;

		if ((PrevCount == 9 || PrevCount == 19 || PrevCount == 29 || PrevCount == 39) && _Info.PrevState != "IN_LEFT_ARROW")
		{
			++CurrentPosInCharmPage;
			SettingPointerCharmPageManager_.ChangeState("IN_RIGHT_ARROW");
			return;
		}

		else
		{
			++CurrentPosInCharmPage;

			if (CurrentPosInCharmPage > CharmPageActorCount)
			{
				CurrentPosInCharmPage = 0;
			}

			PointActorComponent* PointActorComponent_ = GetLevel<HollowKnightLevel>()->PointActorListCharm.find(CurrentPosInCharmPage)->second;

			SettingPointerBox_->GetTransform().SetWorldPosition({ PointActorComponent_->GetPointActor()->GetTransform().GetLocalPosition().x
				, PointActorComponent_->GetPointActor()->GetTransform().GetLocalPosition().y
				, static_cast<float>(Z_ORDER::UI_Border) });

			SettingPointerBox_->SetBoxSize({ PointActorComponent_->GetPointActor()->GetPointerSize() / 2 });
		}

	}
}

void SettingPointer::PointerCharmPageMoveRightUpdate(float _DeltaTime, const StateInfo& _Info)
{
	SettingPointerCharmPageManager_.ChangeState("IDLE");
}

void SettingPointer::PointerCharmPageMoveRightEnd(const StateInfo& _Info)
{
}

void SettingPointer::PointerInCharmPageRightArrowStart(const StateInfo& _Info)
{
	inRightArrow_ = true;

	PointActorComponent* PointActorComponent_ = GetLevel<HollowKnightLevel>()->PointActorListCharm.find(50)->second;

	SettingPointerBox_->GetTransform().SetWorldPosition({ PointActorComponent_->GetPointActor()->GetTransform().GetLocalPosition().x
		, PointActorComponent_->GetPointActor()->GetTransform().GetLocalPosition().y
		, static_cast<float>(Z_ORDER::UI_Border) });

	SettingPointerBox_->SetBoxSize({ PointActorComponent_->GetPointActor()->GetPointerSize() / 2 });
}

void SettingPointer::PointerInCharmPageRightArrowUpdate(float _DeltaTime, const StateInfo& _Info)
{
	if (true == GameEngineInput::GetInst()->IsDown("MoveLeft"))
	{
		SettingPointerCharmPageManager_.ChangeState("MOVE_LEFT");
	}

	else if (true == GameEngineInput::GetInst()->IsDown("MoveRight"))
	{
		isDownNextPageRight_ = true;
	}
}

void SettingPointer::PointerInCharmPageRightArrowEnd(const StateInfo& _Info)
{
}

void SettingPointer::PointerCharmPageInLeftArrowStart(const StateInfo& _Info)
{
	inLeftArrow_ = true;
	PointActorComponent* PointActorComponent_ = GetLevel<HollowKnightLevel>()->PointActorListCharm.find(51)->second;

	SettingPointerBox_->GetTransform().SetWorldPosition({ PointActorComponent_->GetPointActor()->GetTransform().GetLocalPosition().x
		, PointActorComponent_->GetPointActor()->GetTransform().GetLocalPosition().y
		, static_cast<float>(Z_ORDER::UI_Border) });

	SettingPointerBox_->SetBoxSize({ PointActorComponent_->GetPointActor()->GetPointerSize() / 2 });
}

void SettingPointer::PointerCharmPageInLeftArrowUpdate(float _DeltaTime, const StateInfo& _Info)
{
	if (true == GameEngineInput::GetInst()->IsDown("MoveRight"))
	{
		SettingPointerCharmPageManager_.ChangeState("MOVE_RIGHT");
	}


	else if (true == GameEngineInput::GetInst()->IsDown("MoveLeft"))
	{
		isDownLextPageLeft_ = true;
	}

}

void SettingPointer::PointerCharmPageInLeftArrowEnd(const StateInfo& _Info)
{
}

void SettingPointer::PointerCharmPageWaitStart(const StateInfo& _Info)
{
}

void SettingPointer::PointerCharmPageWaitUpdate(float _DeltaTime, const StateInfo& _Info)
{
}

void SettingPointer::PointerCharmPageWaitEnd(const StateInfo& _Info)
{
}

void SettingPointer::PointerInventoryPageIdleStart(const StateInfo& _Info)
{
}

void SettingPointer::PointerInventoryPageIdleUpdate(float _DeltaTime, const StateInfo& _Info)
{
	if (true == GameEngineInput::GetInst()->IsDown("MoveRight"))
	{
		SettingPointerInventoyPageManager_.ChangeState("MOVE_RIGHT");
	}

	if (true == GameEngineInput::GetInst()->IsDown("MoveLeft"))
	{
		SettingPointerInventoyPageManager_.ChangeState("MOVE_LEFT");

	}
}

void SettingPointer::PointerInventoryPageIdleEnd(const StateInfo& _Info)
{
}

void SettingPointer::PointerInventoryPageMoveLeftStart(const StateInfo& _Info)
{
}

void SettingPointer::PointerInventoryPageMoveLeftUpdate(float _DeltaTime, const StateInfo& _Info)
{
}

void SettingPointer::PointerInventoryPageMoveLeftEnd(const StateInfo& _Info)
{
}

void SettingPointer::PointerInventoryPageMoveRightStart(const StateInfo& _Info)
{

	if (true == GameEngineInput::GetInst()->IsDown("MoveRight") && inRightArrow_ == false)
	{
		inLeftArrow_ = false;
		int PrevCount = CurrentPosInInventoryPage;

		if ((PrevCount == 9 || PrevCount == 19 || PrevCount == 29 || PrevCount == 39) && _Info.PrevState != "IN_LEFT_ARROW")
		{
			++CurrentPosInInventoryPage;
			SettingPointerInventoyPageManager_.ChangeState("IN_RIGHT_ARROW");
			return;
		}

		else
		{
			++CurrentPosInInventoryPage;

			if (CurrentPosInInventoryPage > CharmPageActorCount)
			{
				CurrentPosInInventoryPage = 0;
			}

			PointActorComponent* PointActorComponent_ = GetLevel<HollowKnightLevel>()->PointActorListInventory.find(CurrentPosInInventoryPage)->second;

			SettingPointerBox_->GetTransform().SetWorldPosition({ PointActorComponent_->GetPointActor()->GetTransform().GetLocalPosition().x
				, PointActorComponent_->GetPointActor()->GetTransform().GetLocalPosition().y
				, static_cast<float>(Z_ORDER::UI_Border) });

			SettingPointerBox_->SetBoxSize({ PointActorComponent_->GetPointActor()->GetPointerSize() / 2   });
		}

	}
}

void SettingPointer::PointerInventoryPageMoveRightUpdate(float _DeltaTime, const StateInfo& _Info)
{
	SettingPointerInventoyPageManager_.ChangeState("IDLE");

}

void SettingPointer::PointerInventoryPageMoveRightEnd(const StateInfo& _Info)
{
}

void SettingPointer::PointerInInventoryPageRightArrowStart(const StateInfo& _Info)
{
}

void SettingPointer::PointerInInventoryPageRightArrowUpdate(float _DeltaTime, const StateInfo& _Info)
{
	if (true == GameEngineInput::GetInst()->IsDown("MoveLeft"))
	{
		SettingPointerInventoyPageManager_.ChangeState("MOVE_LEFT");
	}

	else if (true == GameEngineInput::GetInst()->IsDown("MoveRight"))
	{
		isDownNextPageRight_ = true;
	}
}

void SettingPointer::PointerInInventoryPageRightArrowEnd(const StateInfo& _Info)
{
}

void SettingPointer::PointerInventoryPageInLeftArrowStart(const StateInfo& _Info)
{
}

void SettingPointer::PointerInventoryPageInLeftArrowUpdate(float _DeltaTime, const StateInfo& _Info)
{
	if (true == GameEngineInput::GetInst()->IsDown("MoveLeft"))
	{
		isDownLextPageLeft_ = true;
	}

	else if (true == GameEngineInput::GetInst()->IsDown("MoveRight"))
	{
		SettingPointerInventoyPageManager_.ChangeState("MOVE_RIGHT");
	}
}

void SettingPointer::PointerInventoryPageInLeftArrowEnd(const StateInfo& _Info)
{
}

void SettingPointer::PointerInventoryPageWaitStart(const StateInfo& _Info)
{
}

void SettingPointer::PointerInventoryPageWaitUpdate(float _DeltaTime, const StateInfo& _Info)
{
}

void SettingPointer::PointerInventoryPageWaitEnd(const StateInfo& _Info)
{
}
