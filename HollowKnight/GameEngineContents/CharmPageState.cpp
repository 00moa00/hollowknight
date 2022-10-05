#include "PreCompile.h"
#include "SettingPointer.h"
#include "HollowKnightLevel.h"
#include "PointActorComponent.h"
#include "GlobalContentsValue.h"
#include "KnightData.h"

#include <algorithm>


void SettingPointer::PointerCharmPageMoveStart(const StateInfo& _Info)
{

}

void SettingPointer::PointerCharmPageMoveUpdate(float _DeltaTime, const StateInfo& _Info)
{
	float4 MoveDir;
	MoveDir.x = MoveState_.Dir_.x - SettingPointerBox_->GetTransform().GetWorldPosition().x;
	MoveDir.y = MoveState_.Dir_.y - SettingPointerBox_->GetTransform().GetWorldPosition().y;
	MoveDir.z = 0;

	float Lenth = MoveDir.Length();

	MoveDir.Normalize();
	if (Lenth < PointerMoveSpeed_ * _DeltaTime)
	{
		SettingPointerBox_->GetTransform().SetWorldPosition({MoveState_.Dir_.x, MoveState_.Dir_ .y , -100});
		SettingPointerCharmPageManager_.ChangeState(MoveState_.NextMoveStateName_);
		return;
	}

	float4 Move = MoveDir * PointerMoveSpeed_ * _DeltaTime;
	SettingPointerBox_->GetTransform().SetWorldMove({ Move.x, Move.y});
	SettingPointerBox_->SetBoxSize({ MoveState_.Size_ });	

	SettingPointerBox_->GetTransform().SetWorldPosition({
	SettingPointerBox_->GetTransform().GetWorldPosition().x
	, SettingPointerBox_->GetTransform().GetWorldPosition().y
	, -100
			});

}

void SettingPointer::PointerCharmPageMoveEnd(const StateInfo& _Info)
{



}

void SettingPointer::PointerCharmPageIdleStart(const StateInfo& _Info)
{

	//GetLevel<HollowKnightLevel>()->GetCharmPageInfo()->SetInfoImage(findSlot->GetFilePath());
	//CurrentPosInCharmPage = 0;

	GetLevel<HollowKnightLevel>()->GetCharmPageInfo()->SetInfo(" ", 21);
	GetLevel<HollowKnightLevel>()->GetCharmPageInfo()->SetInfoName(" ");

	Sort_ = 0;
	PointerMoveSpeed_ = 750.f;

	PointActorComponent* PointActorComponent_ = GetLevel<HollowKnightLevel>()->PointActorListCharm.find(CurrentPosInCharmPage)->second;
	CharmSlot* findSlot = dynamic_cast<CharmSlot*>(PointActorComponent_->GetPointActor());

	if (findSlot->GetisEquippedSlotUsing())
	{
		PointActorComponent_ = GetLevel<HollowKnightLevel>()->PointActorListCharm.find(findSlot->GetUsingSlotNum())->second;
		findSlot = dynamic_cast<CharmSlot*>(PointActorComponent_->GetPointActor());

		GetLevel<HollowKnightLevel>()->GetCharmPageInfo()->SetInfoImage(findSlot->GetFilePath());

		GetLevel<HollowKnightLevel>()->GetCharmPageInfo()->SetInfo(findSlot->GetInfo(), 21);
		GetLevel<HollowKnightLevel>()->GetCharmPageInfo()->SetInfoName(findSlot->GetInfoName());

	}

	if (findSlot->GetKnightHas() == true)
	{
		GetLevel<HollowKnightLevel>()->GetCharmPageInfo()->SetInfoImage(findSlot->GetFilePath());

		GetLevel<HollowKnightLevel>()->GetCharmPageInfo()->SetInfo(findSlot->GetInfo(), 21);
		GetLevel<HollowKnightLevel>()->GetCharmPageInfo()->SetInfoName(findSlot->GetInfoName());
	}

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

		else if (CurrentPosInCharmPage >= 40) //위에서 10씩 더해주고있으니까 생각하고 있는 인덱스 + 10
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
						PointActorComponent* PointActorComponent_ = GetLevel<HollowKnightLevel>()->PointActorListCharm.find(i + 1)->second;
						CharmSlot* EmptyNotesSlot = dynamic_cast<CharmSlot*>(PointActorComponent_->GetPointActor());
						EmptyNotesSlot->GetRenderer()->On();
					}

					NotesSlot->GetCharm()->SetRenderMove(
						slot->GetCharm()->GetRenderer()->GetTransform().GetWorldPosition()
						, NotesSlot->GetRenderer()->GetTransform().GetWorldPosition());

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

					Charm* NewCharmRenderer = GetLevel()->CreateActor<Charm>();
					NewCharmRenderer->CreateCharm(slot->GetCharmName(), slot->GetFilePath(), slot->GetRenderer()->GetCurTexture()->GetScale());
					NewCharmRenderer->GetTransform().SetWorldPosition({ slot->GetTransform().GetWorldPosition() });
					NewCharmRenderer->SetCharmPointer(SearchSlot->GetCharm());

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


		if ((PrevCount % 10 == 0) && _Info.PrevState != "IN_RIGHT_ARROW")
		{
			--CurrentPosInCharmPage;

			PointActorComponent* PointActorComponent_ = GetLevel<HollowKnightLevel>()->PointActorListCharm.find(51)->second;

			SettingPointerCharmPageManager_.ChangeState("POINTER_MOVE");
			PointerMoveSpeed_ = 1500.f;

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
			PointerMoveSpeed_ = 1500.f;

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
	//CurrentPosInCharmPage = 1;

	////CurrentPosInCharmPage = -1;

	//PointActorComponent* PointActorComponent_ = GetLevel<HollowKnightLevel>()->PointActorListCharm.find(CurrentPosInCharmPage)->second;

	//SettingPointerBox_->GetTransform().SetWorldPosition({ PointActorComponent_->GetPointActor()->GetTransform().GetLocalPosition().x
	//	, PointActorComponent_->GetPointActor()->GetTransform().GetLocalPosition().y
	//	, static_cast<float>(Z_ORDER::UI_Border) });

	//SettingPointerBox_->SetBoxSize({ PointActorComponent_->GetPointActor()->GetPointerSize() / 2 });

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
	//CurrentPosInCharmPage = 1;

	//PointActorComponent* PointActorComponent_ = GetLevel<HollowKnightLevel>()->PointActorListCharm.find(CurrentPosInCharmPage)->second;

	//SettingPointerBox_->GetTransform().SetWorldPosition({ PointActorComponent_->GetPointActor()->GetTransform().GetLocalPosition().x
	//	, PointActorComponent_->GetPointActor()->GetTransform().GetLocalPosition().y
	//	, static_cast<float>(Z_ORDER::UI_Border) });

	//SettingPointerBox_->SetBoxSize({ PointActorComponent_->GetPointActor()->GetPointerSize() / 2 });
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

	PointActorComponent* PointActorComponent_ = GetLevel<HollowKnightLevel>()->PointActorListCharm.find(CurrentPosInCharmPage)->second;
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
	slot->GetCharm()->GetTransform().SetWorldPosition({ slot->GetTransform().GetWorldPosition() });
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
}

void SettingPointer::PointerChramPageSortSlotUpdate(float _DeltaTime, const StateInfo& _Info)
{
	SettingPointerCharmPageManager_.ChangeState("IDLE");

}

void SettingPointer::PointerChramPageSortSlotEnd(const StateInfo& _Info)
{

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

}

void  SettingPointer::PointerChramPageMoveRendererMoveUpdate(float _DeltaTime, const StateInfo& _Info)
{

}
void  SettingPointer::PointerChramPageMoveRendererMoveEnd(const StateInfo& _Info)
{
	//CharmMovePointer_->GetCharm()->GetRenderer()->GetTransform().SetWorldPosition(RendererMove_.EndDir_);

	CharmMovePointer_ = nullptr;
	isMoveRendererDeath_ = false;
}
