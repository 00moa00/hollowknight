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

void SettingPointer::PointerCharmPageMoveStart(const StateInfo& _Info)
{

}

void SettingPointer::PointerCharmPageMoveUpdate(float _DeltaTime, const StateInfo& _Info)
{
	float4 MoveDir = MoveState_.Dir_ - SettingPointerBox_->GetTransform().GetWorldPosition();
	float Lenth = MoveDir.Length();

	MoveDir.Normalize();
	if (Lenth <= 2.f)
	{
		SettingPointerBox_->GetTransform().SetWorldPosition(MoveState_.Dir_);
		SettingPointerCharmPageManager_.ChangeState(MoveState_.NextMoveStateName_);
	}

	SettingPointerBox_->GetTransform().SetWorldMove(MoveDir * 550.f * _DeltaTime);
	SettingPointerBox_->SetBoxSize({ MoveState_.Size_ });
}

void SettingPointer::PointerCharmPageMoveEnd(const StateInfo& _Info)
{

}

void SettingPointer::PointerCharmPageIdleStart(const StateInfo& _Info)
{
	Sort_ = 0;
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
			PointActorComponent* FindActorComponent_ = GetLevel<HollowKnightLevel>()->PointActorListCharm.find(40)->second;

			CharmSlot* findSlot = dynamic_cast<CharmSlot*>(FindActorComponent_->GetPointActor());

			if (findSlot->GetisEquippedSlotUsing() == true)
			{
				CurrentPosInCharmPage = 40;

				PointActorComponent* PointActorComponent_ = GetLevel<HollowKnightLevel>()->PointActorListCharm.find(CurrentPosInCharmPage)->second;

				SettingPointerCharmPageManager_.ChangeState("POINTER_MOVE");
				MoveState_.Dir_ = PointActorComponent_->GetPointActor()->GetTransform().GetLocalPosition();
				MoveState_.Size_ = PointActorComponent_->GetPointActor()->GetPointerSize() / 2;
				MoveState_.NextMoveStateName_ = "IDLE";
			}
			else
			{
				CurrentPosInCharmPage = PrevCount;
			}
		}
		else if (PrevCount > 39 && PrevCount < 50)
		{
			CurrentPosInCharmPage = PrevCount;
		}

		else
		{
			PointActorComponent* PointActorComponent_ = GetLevel<HollowKnightLevel>()->PointActorListCharm.find(CurrentPosInCharmPage)->second;

			SettingPointerCharmPageManager_.ChangeState("POINTER_MOVE");
			MoveState_.Dir_ = PointActorComponent_->GetPointActor()->GetTransform().GetLocalPosition();
			MoveState_.Size_ = PointActorComponent_->GetPointActor()->GetPointerSize() / 2;
			MoveState_.NextMoveStateName_ = "IDLE";
		}
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

		SettingPointerCharmPageManager_.ChangeState("POINTER_MOVE");
		MoveState_.Dir_ = PointActorComponent_->GetPointActor()->GetTransform().GetLocalPosition();
		MoveState_.Size_ = PointActorComponent_->GetPointActor()->GetPointerSize() / 2;
		MoveState_.NextMoveStateName_ = "IDLE";
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
						CharmSlot* EmptyNotesSlot = dynamic_cast<CharmSlot*>(PointActorComponent_->GetPointActor());
						EmptyNotesSlot->GetRenderer()->On();
					}

					NotesSlot->GetCharm()->SetRenderMove(
						slot->GetCharm()->GetRenderer()->GetTransform().GetWorldPosition()
						, NotesSlot->GetRenderer()->GetTransform().GetWorldPosition());
					
					/*CharmMovePointer_ = NotesSlot;
					RendererMove_.StartDir_ = slot->GetCharm()->GetRenderer()->GetTransform().GetWorldPosition();
					RendererMove_.EndDir_ = NotesSlot->GetRenderer()->GetTransform().GetWorldPosition();*/


					//SettingPointerCharmPageManager_.ChangeState("MOVE_RENDERDER");
					break;
				}
			}
		}
		
		else if (slot->GetisEquippedSlotUsing() == true)
		{
			{

				PointActorComponent* PointActorComponent_ = GetLevel<HollowKnightLevel>()->PointActorListCharm.find(CurrentPosInCharmPage + 1)->second;
				CharmSlot* SearchNextSlot = dynamic_cast<CharmSlot*>(PointActorComponent_->GetPointActor());

				if (SearchNextSlot != nullptr && SearchNextSlot->GetisEquippedSlotUsing() == true)
				{
					SettingPointerCharmPageManager_.ChangeState("SORT_SLOT");
				}

				else
				{

					//해당 부적을 사용하고 있지 않음으로 바꿔야한다.
					PointActorComponent* PointActorComponent_ = GetLevel<HollowKnightLevel>()->PointActorListCharm.find(slot->GetUsingSlotNum())->second;
					CharmSlot* SearchSlot = dynamic_cast<CharmSlot*>(PointActorComponent_->GetPointActor());

					KnightData::GetInst()->AddUsingCharmNotches(SearchSlot->GetSlotCount());
					SearchSlot->SetisUsing(false);

					slot->SetUsingSlotNum(-1);
					slot->SetisEquippedSlotUsing(false);

					//isMoveRendererDeath_ = true;

					//CharmMovePointer_ = slot;
					//RendererMove_.StartDir_ = slot->GetCharm()->GetRenderer()->GetTransform().GetWorldPosition();
					//RendererMove_.EndDir_ = SearchSlot->GetRenderer()->GetTransform().GetWorldPosition();


					Charm* NewCharmRenderer = GetLevel()->CreateActor<Charm>();
					NewCharmRenderer->CreateCharm(slot->GetCharmName(), slot->GetFilePath(), slot->GetRenderer()->GetCurTexture()->GetScale());
					NewCharmRenderer->GetTransform().SetWorldPosition({ slot->GetTransform().GetWorldPosition() });
					NewCharmRenderer->SetCharmPointer(SearchSlot->GetCharm());

					//NewCharmRenderer->SetCharmPointer(slot->GetCharm());
					slot->GetCharm()->GetRenderer()->Death();

					NewCharmRenderer->SetRenderMove(
						NewCharmRenderer->GetRenderer()->GetTransform().GetWorldPosition()
						, SearchSlot->GetRenderer()->GetTransform().GetWorldPosition()
						, true
						, true);
				}

				//사용 가능한 부적 칸 수(노치) 갱신
				for (int j = KnightData::GetInst()->GetCharmNotches() - 1; j > KnightData::GetInst()->GetUsingCharmNotches() - 1; --j)
				{
					GetLevel<HollowKnightLevel>()->AllNotes_[j]->SetNotchesNotUsed();
				}

				//++CurrentPosInCharmPage;
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

			PointActorComponent* PointActorComponent_ = GetLevel<HollowKnightLevel>()->PointActorListCharm.find(51)->second;

			SettingPointerCharmPageManager_.ChangeState("POINTER_MOVE");
			MoveState_.Dir_ = PointActorComponent_->GetPointActor()->GetTransform().GetLocalPosition();
			MoveState_.Size_ = PointActorComponent_->GetPointActor()->GetPointerSize() / 2;
			MoveState_.NextMoveStateName_ = "IN_LEFT_ARROW";

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

			SettingPointerCharmPageManager_.ChangeState("POINTER_MOVE");
			MoveState_.Dir_ = PointActorComponent_->GetPointActor()->GetTransform().GetLocalPosition();
			MoveState_.Size_ = PointActorComponent_->GetPointActor()->GetPointerSize() / 2;
			MoveState_.NextMoveStateName_ = "IDLE";
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

			PointActorComponent* PointActorComponent_ = GetLevel<HollowKnightLevel>()->PointActorListCharm.find(50)->second;

			SettingPointerCharmPageManager_.ChangeState("POINTER_MOVE");
			MoveState_.Dir_ = PointActorComponent_->GetPointActor()->GetTransform().GetLocalPosition();
			MoveState_.Size_ = PointActorComponent_->GetPointActor()->GetPointerSize() / 2;
			MoveState_.NextMoveStateName_ = "IN_RIGHT_ARROW";

			return;
		}

		else if (PrevCount > 39 && PrevCount < 50)
		{

			PointActorComponent* FindActorComponent_ = GetLevel<HollowKnightLevel>()->PointActorListCharm.find(PrevCount + 1)->second;

			CharmSlot* findSlot = dynamic_cast<CharmSlot*>(FindActorComponent_->GetPointActor());

			if (findSlot->GetisEquippedSlotUsing() == true)
			{
				++CurrentPosInCharmPage;
			}

			FindActorComponent_ = GetLevel<HollowKnightLevel>()->PointActorListCharm.find(CurrentPosInCharmPage)->second;

			SettingPointerCharmPageManager_.ChangeState("POINTER_MOVE");
			MoveState_.Dir_ = FindActorComponent_->GetPointActor()->GetTransform().GetLocalPosition();
			MoveState_.Size_ = FindActorComponent_->GetPointActor()->GetPointerSize() / 2;
			MoveState_.NextMoveStateName_ = "IDLE";
		}

		else
		{
			++CurrentPosInCharmPage;

			if (CurrentPosInCharmPage > CharmPageActorCount)
			{
				CurrentPosInCharmPage = 0;
			}

			PointActorComponent* PointActorComponent_ = GetLevel<HollowKnightLevel>()->PointActorListCharm.find(CurrentPosInCharmPage)->second;

			SettingPointerCharmPageManager_.ChangeState("POINTER_MOVE");
			MoveState_.Dir_ = PointActorComponent_->GetPointActor()->GetTransform().GetLocalPosition();
			MoveState_.Size_ = PointActorComponent_->GetPointActor()->GetPointerSize() / 2;
			MoveState_.NextMoveStateName_ = "IDLE";
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

void SettingPointer::PointerChramPageSortSlotStart(const StateInfo& _Info)
{

	PointActorComponent* PointActorComponent_ = GetLevel<HollowKnightLevel>()->PointActorListCharm.find(CurrentPosInCharmPage )->second;
	CharmSlot* slot = dynamic_cast<CharmSlot*>(PointActorComponent_->GetPointActor());

	//다음 슬롯
	PointActorComponent_ = GetLevel<HollowKnightLevel>()->PointActorListCharm.find(CurrentPosInCharmPage + 1)->second;
	CharmSlot* SearchNextSlot = dynamic_cast<CharmSlot*>(PointActorComponent_->GetPointActor());

	//다음 슬롯의 부적
	PointActorComponent_ = GetLevel<HollowKnightLevel>()->PointActorListCharm.find(SearchNextSlot->GetUsingSlotNum())->second;
	CharmSlot* SearchNextCharm = dynamic_cast<CharmSlot*>(PointActorComponent_->GetPointActor());


	// 쓰던 부적의 초기화
	PointActorComponent* DestPointActorComponent_ = GetLevel<HollowKnightLevel>()->PointActorListCharm.find(slot->GetUsingSlotNum())->second;
	CharmSlot* SearchDestCharm = dynamic_cast<CharmSlot*>(DestPointActorComponent_->GetPointActor());

	KnightData::GetInst()->AddUsingCharmNotches(SearchDestCharm->GetSlotCount());
	SearchDestCharm->SetisUsing(false);

	// 부적 복사해서 원래 부적자리로 
	Charm* NewCharmRenderer = GetLevel()->CreateActor<Charm>();
	NewCharmRenderer->CreateCharm(slot->GetCharmName(), slot->GetFilePath(), slot->GetRenderer()->GetCurTexture()->GetScale());
	NewCharmRenderer->GetTransform().SetWorldPosition({ slot->GetTransform().GetWorldPosition() });
	NewCharmRenderer->SetRenderMove(
	NewCharmRenderer->GetRenderer()->GetTransform().GetWorldPosition()
	, SearchDestCharm->GetRenderer()->GetTransform().GetWorldPosition()
	, true
	, true);

	NewCharmRenderer->SetCharmPointer(slot->GetCharm());


	// 다음 슬롯 복사해서 이동
	SearchNextSlot->GetCharm()->GetRenderer()->Death();
	NewCharmRenderer = GetLevel()->CreateActor<Charm>();
	NewCharmRenderer->CreateCharm(SearchNextSlot->GetCharmName(), SearchNextSlot->GetFilePath(), SearchNextSlot->GetRenderer()->GetCurTexture()->GetScale());
	NewCharmRenderer->GetTransform().SetWorldPosition({ SearchNextSlot->GetTransform().GetWorldPosition() });
	NewCharmRenderer->SetCharmPointer(slot->GetCharm());

	NewCharmRenderer->SetRenderMove(
		NewCharmRenderer->GetRenderer()->GetTransform().GetWorldPosition()
		, slot->GetRenderer()->GetTransform().GetWorldPosition()
		, true
		, true);





	slot->GetCharm()->GetRenderer()->Death();
	slot->CreateCopyCharm(SearchNextCharm->GetRenderer(), SearchNextCharm->GetCharmName(), SearchNextCharm->GetFilePath());
	slot->SetisEquippedSlotUsing(true);
	slot->SetUsingSlotNum(SearchNextCharm->GetUsingSlotNum());
	slot->GetCharm()->GetTransform().SetWorldPosition({ slot-> GetTransform().GetWorldPosition()});
	slot->GetCharm()->GetRenderer()->Off();


	PointActorComponent_ = GetLevel<HollowKnightLevel>()->PointActorListCharm.find(CurrentPosInCharmPage + 2)->second;
	CharmSlot* SearchNextAfterSlot = dynamic_cast<CharmSlot*>(PointActorComponent_->GetPointActor());

	if (SearchNextAfterSlot != nullptr && SearchNextAfterSlot->GetisEquippedSlotUsing() == true)
	{
		SettingPointerCharmPageManager_.ChangeState("NEXT_SORT_SLOT");
	}

	else
	{
		SearchNextSlot->SetUsingSlotNum(-1);
		SearchNextSlot->SetisEquippedSlotUsing(false);
	}




	//사용 가능한 부적 칸 수(노치) 갱신
	for (int j = KnightData::GetInst()->GetCharmNotches() - 1; j > KnightData::GetInst()->GetUsingCharmNotches() - 1; --j)
	{
		GetLevel<HollowKnightLevel>()->AllNotes_[j]->SetNotchesNotUsed();
	}


	//else
	//{
	//	Sort_ = 0;
	//}

}

void SettingPointer::PointerChramPageSortSlotUpdate(float _DeltaTime, const StateInfo& _Info)
{
	SettingPointerCharmPageManager_.ChangeState("IDLE");

}

void SettingPointer::PointerChramPageSortSlotEnd(const StateInfo& _Info)
{


	//Sort_ = 0;
}


void SettingPointer::PointerChramPageNextSortSlotStart(const StateInfo& _Info)
{
	PointActorComponent* PointActorComponent_ = GetLevel<HollowKnightLevel>()->PointActorListCharm.find(CurrentPosInCharmPage + 1 + Sort_)->second;
	CharmSlot* SearchNextSlot = dynamic_cast<CharmSlot*>(PointActorComponent_->GetPointActor());

	PointActorComponent_ = GetLevel<HollowKnightLevel>()->PointActorListCharm.find(CurrentPosInCharmPage + 2 + Sort_)->second;
	CharmSlot* SearchNextAfterSlot = dynamic_cast<CharmSlot*>(PointActorComponent_->GetPointActor());

	PointActorComponent_ = GetLevel<HollowKnightLevel>()->PointActorListCharm.find(SearchNextAfterSlot->GetUsingSlotNum())->second;
	CharmSlot* SearchNextAfterCharm = dynamic_cast<CharmSlot*>(PointActorComponent_->GetPointActor());

	// 다음 슬롯 복사해서 이동
	SearchNextAfterSlot->GetCharm()->GetRenderer()->Death();

	Charm* NewCharmRenderer = GetLevel()->CreateActor<Charm>();
	NewCharmRenderer->CreateCharm(SearchNextAfterSlot->GetCharmName(), SearchNextAfterSlot->GetFilePath(), SearchNextAfterSlot->GetRenderer()->GetCurTexture()->GetScale());
	NewCharmRenderer->GetTransform().SetWorldPosition({ SearchNextAfterSlot->GetTransform().GetWorldPosition() });
	NewCharmRenderer->SetCharmPointer(SearchNextSlot->GetCharm());

	NewCharmRenderer->SetRenderMove(
		NewCharmRenderer->GetRenderer()->GetTransform().GetWorldPosition()
		, SearchNextSlot->GetRenderer()->GetTransform().GetWorldPosition()
		, true
		, true);


	//slot->GetCharm()->GetRenderer()->Death();
	SearchNextSlot->CreateCopyCharm(SearchNextAfterSlot->GetRenderer(), SearchNextAfterSlot->GetCharmName(), SearchNextAfterSlot->GetFilePath());
	SearchNextSlot->SetisEquippedSlotUsing(true);
	SearchNextSlot->SetUsingSlotNum(SearchNextAfterSlot->GetUsingSlotNum());
	SearchNextSlot->GetCharm()->GetTransform().SetWorldPosition({ SearchNextSlot->GetTransform().GetWorldPosition() });
	SearchNextSlot->GetCharm()->GetRenderer()->Off();


	PointActorComponent_ = GetLevel<HollowKnightLevel>()->PointActorListCharm.find(CurrentPosInCharmPage + 3 + Sort_)->second;
	CharmSlot* LoopCheck = dynamic_cast<CharmSlot*>(PointActorComponent_->GetPointActor());

	if (LoopCheck != nullptr && LoopCheck->GetisEquippedSlotUsing() == true)
	{
		++Sort_;
		SettingPointerCharmPageManager_.ChangeState("NEXT_SORT_SLOT");

	}

	else
	{
		SearchNextAfterSlot->SetUsingSlotNum(-1);
		SearchNextAfterSlot->SetisEquippedSlotUsing(false);
	}



}

void SettingPointer::PointerChramPageNextSortSlotUpdate(float _DeltaTime, const StateInfo& _Info)
{
	SettingPointerCharmPageManager_.ChangeState("IDLE");

}


void SettingPointer::PointerChramPageNextSortSlotEnd(const StateInfo& _Info)
{

	
}



void  SettingPointer::PointerChramPageMoveRendererMoveStart(const StateInfo& _Info)
{
	//CharmMovePointer_->GetCharm()->GetRenderer()->GetTransform().SetWorldPosition(RendererMove_.StartDir_);
}
void  SettingPointer::PointerChramPageMoveRendererMoveUpdate(float _DeltaTime, const StateInfo& _Info)
{

	if (CharmMovePointer_ != nullptr)
	{



	}
}
void  SettingPointer::PointerChramPageMoveRendererMoveEnd(const StateInfo& _Info)
{
	//CharmMovePointer_->GetCharm()->GetRenderer()->GetTransform().SetWorldPosition(RendererMove_.EndDir_);

	CharmMovePointer_ = nullptr;
	isMoveRendererDeath_ = false;
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


	if (true == GameEngineInput::GetInst()->IsDown("MoveUp"))
	{

		int PrevCount = CurrentPosInInventoryPage;

		//내가 지금 스펠에 있다면

		if (PrevCount > static_cast<int>(ITEM_LIST::SPELL_MIN) && PrevCount < static_cast<int>(ITEM_LIST::SPELL_MAX))
		{


			if (PrevCount == static_cast<int>(ITEM_LIST::Nail))
			{
				CurrentPosInInventoryPage = static_cast<int>(ITEM_LIST::Heart_Piece);
			}

			if (PrevCount == static_cast<int>(ITEM_LIST::Item_Geo))
			{
				CurrentPosInInventoryPage = static_cast<int>(ITEM_LIST::Spell_core);
			}


			if (PrevCount == static_cast<int>(ITEM_LIST::Heart_Piece))
			{
				CurrentPosInInventoryPage = PrevCount;
			}

			if (PrevCount == static_cast<int>(ITEM_LIST::Spell_core))
			{
				CurrentPosInInventoryPage = static_cast<int>(ITEM_LIST::Spell_Fireball);
			}

			if (PrevCount == static_cast<int>(ITEM_LIST::Spell_Fireball) || PrevCount == static_cast<int>(ITEM_LIST::Spell_Scream))
			{
				CurrentPosInInventoryPage -= 4;
			}


			PointActorComponent* PointActorComponent_ = GetLevel<HollowKnightLevel>()->PointActorListInventory.find(CurrentPosInInventoryPage)->second;

			SettingPointerBox_->GetTransform().SetWorldPosition({ PointActorComponent_->GetPointActor()->GetTransform().GetLocalPosition().x
				, PointActorComponent_->GetPointActor()->GetTransform().GetLocalPosition().y
				, static_cast<float>(Z_ORDER::UI_Border) });

			SettingPointerBox_->SetBoxSize({ PointActorComponent_->GetPointActor()->GetPointerSize() / 2 });
		}


		//내가 지금 일반 아이템에 있다면 

		else if (PrevCount > static_cast<int>(ITEM_LIST::NORMAL_MIN) && PrevCount < static_cast<int>(ITEM_LIST::NORMAL_MAX))
		{

			CurrentPosInInventoryPage -= 4;

			if (CurrentPosInInventoryPage < static_cast<int>(ITEM_LIST::NORMAL_MIN))
			{
				CurrentPosInInventoryPage = PrevCount;
			}

			PointActorComponent* PointActorComponent_ = GetLevel<HollowKnightLevel>()->PointActorListInventory.find(CurrentPosInInventoryPage)->second;

			SettingPointerBox_->GetTransform().SetWorldPosition({ PointActorComponent_->GetPointActor()->GetTransform().GetLocalPosition().x
				, PointActorComponent_->GetPointActor()->GetTransform().GetLocalPosition().y
				, static_cast<float>(Z_ORDER::UI_Border) });

			SettingPointerBox_->SetBoxSize({ PointActorComponent_->GetPointActor()->GetPointerSize() / 2 });

		}

		//내가 지금 소비 아이템에 있다면
		else if (PrevCount > static_cast<int>(ITEM_LIST::SELL_MIN) && PrevCount < static_cast<int>(ITEM_LIST::SELL_MAX))
		{

			for (int i = static_cast<int>(ITEM_LIST::NORMAL_MAX) -1; i > static_cast<int>(ITEM_LIST::NORMAL_MIN); --i)
			{
				PointActorComponent* PointActorComponent_ = GetLevel<HollowKnightLevel>()->PointActorListInventory.find(i)->second;
				ItemSlot* FindSlot = dynamic_cast<ItemSlot*>(PointActorComponent_->GetPointActor());

				if (FindSlot != nullptr && FindSlot->GetisItem() == true)
				{
					CurrentPosInInventoryPage = i;
					break;
				}


			}


			//CurrentPosInInventoryPage -= 8;

			PointActorComponent* PointActorComponent_ = GetLevel<HollowKnightLevel>()->PointActorListInventory.find(CurrentPosInInventoryPage)->second;

			SettingPointerBox_->GetTransform().SetWorldPosition({ PointActorComponent_->GetPointActor()->GetTransform().GetLocalPosition().x
				, PointActorComponent_->GetPointActor()->GetTransform().GetLocalPosition().y
				, static_cast<float>(Z_ORDER::UI_Border) });

			SettingPointerBox_->SetBoxSize({ PointActorComponent_->GetPointActor()->GetPointerSize() / 2 });
		}

	}

	if (true == GameEngineInput::GetInst()->IsDown("MoveDown"))
	{

		int PrevCount = CurrentPosInInventoryPage;

		//내가 지금 스펠에 있다면

		if (PrevCount > static_cast<int>(ITEM_LIST::SPELL_MIN) && PrevCount < static_cast<int>(ITEM_LIST::SPELL_MAX))
		{
			if (PrevCount == static_cast<int>(ITEM_LIST::Nail))
			{
				CurrentPosInInventoryPage = static_cast<int>(ITEM_LIST::Item_Geo);
			}

			if (PrevCount == static_cast<int>(ITEM_LIST::Item_Geo))
			{
				CurrentPosInInventoryPage = PrevCount;
			}

			if (PrevCount == static_cast<int>(ITEM_LIST::Spell_core))
			{
				CurrentPosInInventoryPage = static_cast<int>(ITEM_LIST::Item_Geo);
			}

			if (PrevCount == static_cast<int>(ITEM_LIST::Heart_Piece))
			{
				CurrentPosInInventoryPage = static_cast<int>(ITEM_LIST::Nail);
			}

			if (PrevCount == static_cast<int>(ITEM_LIST::Spell_Fireball) || PrevCount == static_cast<int>(ITEM_LIST::Spell_Scream))
			{
				CurrentPosInInventoryPage = static_cast<int>(ITEM_LIST::Spell_core);
			}

			if (PrevCount == static_cast<int>(ITEM_LIST::Soul_Piece) || PrevCount == static_cast<int>(ITEM_LIST::Dream_Nail))
			{
				CurrentPosInInventoryPage = static_cast<int>(ITEM_LIST::Spell_Fireball);
			}


			PointActorComponent* PointActorComponent_ = GetLevel<HollowKnightLevel>()->PointActorListInventory.find(CurrentPosInInventoryPage)->second;

			SettingPointerBox_->GetTransform().SetWorldPosition({ PointActorComponent_->GetPointActor()->GetTransform().GetLocalPosition().x
				, PointActorComponent_->GetPointActor()->GetTransform().GetLocalPosition().y
				, static_cast<float>(Z_ORDER::UI_Border) });

			SettingPointerBox_->SetBoxSize({ PointActorComponent_->GetPointActor()->GetPointerSize() / 2 });
		}


		//내가 지금 일반 아이템에 있다면 

		else if (PrevCount > static_cast<int>(ITEM_LIST::NORMAL_MIN) && PrevCount < static_cast<int>(ITEM_LIST::NORMAL_MAX))
		{

			CurrentPosInInventoryPage += 4;

			if (CurrentPosInInventoryPage < static_cast<int>(ITEM_LIST::NORMAL_MAX))
			{
				CurrentPosInInventoryPage = static_cast<int>(ITEM_LIST::Wanderers_Journal);
			}

			PointActorComponent* PointActorComponent_ = GetLevel<HollowKnightLevel>()->PointActorListInventory.find(CurrentPosInInventoryPage)->second;

			SettingPointerBox_->GetTransform().SetWorldPosition({ PointActorComponent_->GetPointActor()->GetTransform().GetLocalPosition().x
				, PointActorComponent_->GetPointActor()->GetTransform().GetLocalPosition().y
				, static_cast<float>(Z_ORDER::UI_Border) });

			SettingPointerBox_->SetBoxSize({ PointActorComponent_->GetPointActor()->GetPointerSize() / 2 });

		}

		// 내가 지금 소비 아이템에 있으면 내려갈 수가 없다
		else if (PrevCount > static_cast<int>(ITEM_LIST::SELL_MIN) && PrevCount < static_cast<int>(ITEM_LIST::SELL_MAX))
		{
			CurrentPosInInventoryPage = static_cast<int>(ITEM_LIST::Wanderers_Journal);
		}
	}

}

void SettingPointer::PointerInventoryPageIdleEnd(const StateInfo& _Info)
{
}

void SettingPointer::PointerInventoryPageMoveLeftStart(const StateInfo& _Info)
{
	if ( inLeftArrow_ == false)
	{
		inRightArrow_ = false;
		int PrevCount = CurrentPosInInventoryPage;

		
		if ((PrevCount == static_cast<int>(ITEM_LIST::Heart_Piece) 
			|| PrevCount == static_cast<int>(ITEM_LIST::Nail)
			|| PrevCount == static_cast<int>(ITEM_LIST::Item_Geo)

			)&& _Info.PrevState != "IN_RIGHT_ARROW")
		{
			--CurrentPosInInventoryPage;
			SettingPointerInventoyPageManager_.ChangeState("IN_LEFT_ARROW");
			return;
		}

		//다음 갈 곳이 스펠이다
		else if (PrevCount == 10 || PrevCount == 14 || PrevCount == 18 || PrevCount == 22)
		{
			CurrentPosInInventoryPage = static_cast<int>(ITEM_LIST::Dream_Nail);

			PointActorComponent* PointActorComponent_ = GetLevel<HollowKnightLevel>()->PointActorListInventory.find(CurrentPosInInventoryPage)->second;

			SettingPointerBox_->GetTransform().SetWorldPosition({ PointActorComponent_->GetPointActor()->GetTransform().GetLocalPosition().x
				, PointActorComponent_->GetPointActor()->GetTransform().GetLocalPosition().y
				, static_cast<float>(Z_ORDER::UI_Border) });


			SettingPointerBox_->SetBoxSize({ PointActorComponent_->GetPointActor()->GetPointerSize() / 2 });
		}

		//난 지금 소비 아이템 안에 있다
		else if (PrevCount > static_cast<int>(ITEM_LIST::SELL_MIN) && PrevCount < static_cast<int>(ITEM_LIST::SELL_MAX))
		{

			--CurrentPosInInventoryPage;

			if (PrevCount - 1 == static_cast<int>(ITEM_LIST::SELL_MIN))
			{
				CurrentPosInInventoryPage = static_cast<int>(ITEM_LIST::Dream_Nail);
			}

			PointActorComponent* PointActorComponent_ = GetLevel<HollowKnightLevel>()->PointActorListInventory.find(CurrentPosInInventoryPage)->second;

			SettingPointerBox_->GetTransform().SetWorldPosition({ PointActorComponent_->GetPointActor()->GetTransform().GetLocalPosition().x
				, PointActorComponent_->GetPointActor()->GetTransform().GetLocalPosition().y
				, static_cast<float>(Z_ORDER::UI_Border) });


			SettingPointerBox_->SetBoxSize({ PointActorComponent_->GetPointActor()->GetPointerSize() / 2 });
		}

		else
		{
			--CurrentPosInInventoryPage;

			if (PrevCount == static_cast<int>(ITEM_LIST::Spell_core))
			{
				CurrentPosInInventoryPage = static_cast<int>(ITEM_LIST::Spell_Fireball);
			}

			if (PrevCount == static_cast<int>(ITEM_LIST::Spell_Fireball))
			{
				CurrentPosInInventoryPage = static_cast<int>(ITEM_LIST::Nail);
			}

			PointActorComponent* PointActorComponent_ = GetLevel<HollowKnightLevel>()->PointActorListInventory.find(CurrentPosInInventoryPage)->second;

			SettingPointerBox_->GetTransform().SetWorldPosition({ PointActorComponent_->GetPointActor()->GetTransform().GetLocalPosition().x
				, PointActorComponent_->GetPointActor()->GetTransform().GetLocalPosition().y
				, static_cast<float>(Z_ORDER::UI_Border) });


			SettingPointerBox_->SetBoxSize({ PointActorComponent_->GetPointActor()->GetPointerSize() / 2 });
		}
	}


}

void SettingPointer::PointerInventoryPageMoveLeftUpdate(float _DeltaTime, const StateInfo& _Info)
{
	SettingPointerInventoyPageManager_.ChangeState("IDLE");

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

		//다음 아이템이 아무것도 없다면
		//if ( (PrevCount > static_cast<int>(ITEM_LIST::NORMAL_MIN) && PrevCount < static_cast<int>(ITEM_LIST::NORMAL_MAX))
		//	&& _Info.PrevState != "IN_LEFT_ARROW")  //내가 다음 갈 곳이 화살표라면
		//{



		//	//if (PrevCount == static_cast<int>(ITEM_LIST::NORMAL_MAX) - 1)
		//	//{		
		//	//	++CurrentPosInInventoryPage;
		//	//	SettingPointerInventoyPageManager_.ChangeState("IN_RIGHT_ARROW");
		//	//}





		//	++CurrentPosInInventoryPage;
		//	SettingPointerInventoyPageManager_.ChangeState("IN_RIGHT_ARROW");
		//	return;
		//}

		////다음 갈 곳이 아이템이다
		//else 
			if (PrevCount == static_cast<int>(ITEM_LIST::Dream_Nail) || PrevCount == static_cast<int>(ITEM_LIST::Spell_Scream) || PrevCount == static_cast<int>(ITEM_LIST::Item_Geo))
		{
			
			PointActorComponent* PointActorComponent_ = GetLevel<HollowKnightLevel>()->PointActorListInventory.find(10)->second;
			ItemSlot* CheckItem = dynamic_cast<ItemSlot*>(PointActorComponent_->GetPointActor());

			if (CheckItem->GetisItem() == false) // 아이템이 하나라도 없으면 aroow로 이동
			{
				++CurrentPosInInventoryPage;
				SettingPointerInventoyPageManager_.ChangeState("IN_RIGHT_ARROW");
				return;
			}

			else
			{
				CurrentPosInInventoryPage = 10;

				PointActorComponent* PointActorComponent_ = GetLevel<HollowKnightLevel>()->PointActorListInventory.find(CurrentPosInInventoryPage)->second;

				SettingPointerBox_->GetTransform().SetWorldPosition({ PointActorComponent_->GetPointActor()->GetTransform().GetLocalPosition().x
					, PointActorComponent_->GetPointActor()->GetTransform().GetLocalPosition().y
					, static_cast<float>(Z_ORDER::UI_Border) });


				SettingPointerBox_->SetBoxSize({ PointActorComponent_->GetPointActor()->GetPointerSize() / 2 });

			}

		}

		else if (PrevCount > static_cast<int>(ITEM_LIST::NORMAL_MIN)  && PrevCount < static_cast<int>(ITEM_LIST::NORMAL_MAX)) // 내가 지금 아이템 카테고리에 있다
		{
			PointActorComponent* PointActorComponent_ = GetLevel<HollowKnightLevel>()->PointActorListInventory.find(PrevCount + 1)->second;
			ItemSlot* CheckItem = dynamic_cast<ItemSlot*>(PointActorComponent_->GetPointActor());

			if (CheckItem->GetisItem() == false) // 내가 갈 곳에 아이템이 없으면
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

				SettingPointerBox_->SetBoxSize({ PointActorComponent_->GetPointActor()->GetPointerSize() / 2 });
			}

		}

		else if (PrevCount > static_cast<int>(ITEM_LIST::SELL_MIN) && PrevCount < static_cast<int>(ITEM_LIST::SELL_MAX))
		{
			if (PrevCount + 1 == static_cast<int>(ITEM_LIST::SELL_MAX))
			{
				++CurrentPosInInventoryPage;
				SettingPointerInventoyPageManager_.ChangeState("IN_RIGHT_ARROW");
				return;
			}


			{
				PointActorComponent* PointActorComponent_ = GetLevel<HollowKnightLevel>()->PointActorListInventory.find(PrevCount + 1)->second;
				ItemSlot* FindSlot = dynamic_cast<ItemSlot*>(PointActorComponent_->GetPointActor());


				if (FindSlot->GetisItem() == true)
				{
					++CurrentPosInInventoryPage;
				}

				else
				{
					++CurrentPosInInventoryPage;
					SettingPointerInventoyPageManager_.ChangeState("IN_RIGHT_ARROW");
					return;
				}
				{
					PointActorComponent* PointActorComponent_ = GetLevel<HollowKnightLevel>()->PointActorListInventory.find(CurrentPosInInventoryPage)->second;

					SettingPointerBox_->GetTransform().SetWorldPosition({ PointActorComponent_->GetPointActor()->GetTransform().GetLocalPosition().x
						, PointActorComponent_->GetPointActor()->GetTransform().GetLocalPosition().y
						, static_cast<float>(Z_ORDER::UI_Border) });

					SettingPointerBox_->SetBoxSize({ PointActorComponent_->GetPointActor()->GetPointerSize() / 2 });
				}
			}
		}


		else
		{		
			
			++CurrentPosInInventoryPage;

			if (PrevCount == static_cast<int>(ITEM_LIST::Nail))
			{
				CurrentPosInInventoryPage = static_cast<int>(ITEM_LIST::Spell_Fireball);
			}

			if (PrevCount == static_cast<int>(ITEM_LIST::Spell_core))
			{
				CurrentPosInInventoryPage = static_cast<int>(ITEM_LIST::Spell_Scream);
			}


			if (CurrentPosInInventoryPage > CharmPageActorCount)
			{
				CurrentPosInInventoryPage = 0;
			}

			PointActorComponent* PointActorComponent_ = GetLevel<HollowKnightLevel>()->PointActorListInventory.find(CurrentPosInInventoryPage)->second;

			SettingPointerBox_->GetTransform().SetWorldPosition({ PointActorComponent_->GetPointActor()->GetTransform().GetLocalPosition().x
				, PointActorComponent_->GetPointActor()->GetTransform().GetLocalPosition().y
				, static_cast<float>(Z_ORDER::UI_Border) });

			SettingPointerBox_->SetBoxSize({ PointActorComponent_->GetPointActor()->GetPointerSize() / 2 });

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
	inRightArrow_ = true;
	PointActorComponent* PointActorComponent_ = GetLevel<HollowKnightLevel>()->PointActorListInventory.find(50)->second;

	SettingPointerBox_->GetTransform().SetWorldPosition({ PointActorComponent_->GetPointActor()->GetTransform().GetLocalPosition().x
		, PointActorComponent_->GetPointActor()->GetTransform().GetLocalPosition().y
		, static_cast<float>(Z_ORDER::UI_Border) });

	SettingPointerBox_->SetBoxSize({ PointActorComponent_->GetPointActor()->GetPointerSize() / 2 });
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
	inLeftArrow_ = true;
	PointActorComponent* PointActorComponent_ = GetLevel<HollowKnightLevel>()->PointActorListInventory.find(51)->second;

	SettingPointerBox_->GetTransform().SetWorldPosition({ PointActorComponent_->GetPointActor()->GetTransform().GetLocalPosition().x
		, PointActorComponent_->GetPointActor()->GetTransform().GetLocalPosition().y
		, static_cast<float>(Z_ORDER::UI_Border) });

	SettingPointerBox_->SetBoxSize({ PointActorComponent_->GetPointActor()->GetPointerSize() / 2 });
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
