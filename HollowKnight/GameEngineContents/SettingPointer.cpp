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

	CurrentPosInCharmPage(0),
	CurrentPosInMapPage(0),
	CurrentPosInCMonsterPage(0)


{
}

SettingPointer::~SettingPointer() 
{
}

void SettingPointer::Start()
{


	SettingPointerBox_ = GetLevel()->CreateActor<SettingPointerBox>();

	//================================
	//    CreateKey
	//================================
	if (false == GameEngineInput::GetInst()->IsKey("MoveRight"))
	{
		GameEngineInput::GetInst()->CreateKey("MoveRight", VK_RIGHT);
		GameEngineInput::GetInst()->CreateKey("MoveLeft", VK_LEFT);
		GameEngineInput::GetInst()->CreateKey("MoveDown", VK_DOWN);
		GameEngineInput::GetInst()->CreateKey("MoveUp", VK_UP);
		GameEngineInput::GetInst()->CreateKey("Select", VK_RETURN);
	}

	SettingPointeManager_.CreateStateMember("IDLE"
		, std::bind(&SettingPointer::PointerIdleUpdate, this, std::placeholders::_1, std::placeholders::_2)
		, std::bind(&SettingPointer::PointerIdleStart, this, std::placeholders::_1)
		, std::bind(&SettingPointer::PointerIdleEnd, this, std::placeholders::_1));

	SettingPointeManager_.CreateStateMember("MOVE_RIGHT"
		, std::bind(&SettingPointer::PointerMoveRightUpdate, this, std::placeholders::_1, std::placeholders::_2)
		, std::bind(&SettingPointer::PointerMoveRightStart, this, std::placeholders::_1)
		, std::bind(&SettingPointer::PointerMoveRightEnd, this, std::placeholders::_1));

	SettingPointeManager_.CreateStateMember("MOVE_LEFT"
		, std::bind(&SettingPointer::PointerMoveLeftUpdate, this, std::placeholders::_1, std::placeholders::_2)
		, std::bind(&SettingPointer::PointerMoveLeftStart, this, std::placeholders::_1)
		, std::bind(&SettingPointer::PointerMoveLeftEnd, this, std::placeholders::_1));

	SettingPointeManager_.CreateStateMember("IN_RIGHT_ARROW"
		, std::bind(&SettingPointer::PointerInRightArrowUpdate, this, std::placeholders::_1, std::placeholders::_2)
		, std::bind(&SettingPointer::PointerInRightArrowStart, this, std::placeholders::_1)
		, std::bind(&SettingPointer::PointerInRightArrowEnd, this, std::placeholders::_1));

	SettingPointeManager_.CreateStateMember("IN_LEFT_ARROW"
		, std::bind(&SettingPointer::PointerInLeftArrowUpdate, this, std::placeholders::_1, std::placeholders::_2)
		, std::bind(&SettingPointer::PointerInLeftArrowStart, this, std::placeholders::_1)
		, std::bind(&SettingPointer::PointerInLeftArrowEnd, this, std::placeholders::_1));



	SettingPointeManager_.ChangeState("IDLE");

}

void SettingPointer::Update(float _DeltaTime)
{

	SettingPointeManager_.Update(_DeltaTime);


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

	SettingPointerBox_->SetBoxSize({ PointActorComponent_->GetPointActor()->GetRenderer()->GetTransform().GetLocalScale() });
}

void SettingPointer::SetFirstPosMapPage()
{

	PointActorComponent* PointActorComponent_ = GetLevel<HollowKnightLevel>()->PointActorListMap.find(1)->second;

	SettingPointerBox_->GetTransform().SetWorldPosition({ PointActorComponent_->GetPointActor()->GetTransform().GetLocalPosition().x
		, PointActorComponent_->GetPointActor()->GetTransform().GetLocalPosition().y
		, static_cast<float>(Z_ORDER::UI_Border) });

	SettingPointerBox_->SetBoxSize({ PointActorComponent_->GetPointActor()->GetRenderer()->GetTransform().GetLocalScale() });
}

void SettingPointer::SetFirstPosMonsterBookPage()
{
	PointActorComponent* PointActorComponent_ = GetLevel<HollowKnightLevel>()->PointActorListMonsterBook.find(1)->second;

	SettingPointerBox_->GetTransform().SetWorldPosition({ PointActorComponent_->GetPointActor()->GetTransform().GetLocalPosition().x
		, PointActorComponent_->GetPointActor()->GetTransform().GetLocalPosition().y
		, static_cast<float>(Z_ORDER::UI_Border) });

	SettingPointerBox_->SetBoxSize({ PointActorComponent_->GetPointActor()->GetRenderer()->GetTransform().GetLocalScale() });
}

void SettingPointer::PointerIdleStart(const StateInfo& _Info)
{
}

void SettingPointer::PointerIdleUpdate(float _DeltaTime, const StateInfo& _Info)
{
	if (true == GameEngineInput::GetInst()->IsDown("MoveRight"))
	{
		SettingPointeManager_.ChangeState("MOVE_RIGHT");
	}

	if (true == GameEngineInput::GetInst()->IsDown("MoveLeft"))
	{
		SettingPointeManager_.ChangeState("MOVE_LEFT");

	}

	if (true == GameEngineInput::GetInst()->IsDown("MoveUp"))
	{

		int PrevCount = CurrentPosInCharmPage;
		CurrentPosInCharmPage -= 10;

		if (CurrentPosInCharmPage < 0)
		{
			CurrentPosInCharmPage = PrevCount;

		}

		PointActorComponent* PointActorComponent_ = GetLevel<HollowKnightLevel>()->PointActorListCharm.find(CurrentPosInCharmPage)->second;

		SettingPointerBox_->GetTransform().SetWorldPosition({ PointActorComponent_->GetPointActor()->GetTransform().GetLocalPosition().x
			, PointActorComponent_->GetPointActor()->GetTransform().GetLocalPosition().y
			, static_cast<float>(Z_ORDER::UI_Border) });

		SettingPointerBox_->SetBoxSize({ PointActorComponent_->GetPointActor()->GetRenderer()->GetTransform().GetLocalScale() });
	}

	if (true == GameEngineInput::GetInst()->IsDown("MoveDown"))
	{

		int PrevCount = CurrentPosInCharmPage;
		CurrentPosInCharmPage += 10;

		if (CurrentPosInCharmPage > CharmPageActorCount)
		{
			CurrentPosInCharmPage = PrevCount;

		}

		PointActorComponent* PointActorComponent_ = GetLevel<HollowKnightLevel>()->PointActorListCharm.find(CurrentPosInCharmPage)->second;

		SettingPointerBox_->GetTransform().SetWorldPosition({ PointActorComponent_->GetPointActor()->GetTransform().GetLocalPosition().x
			, PointActorComponent_->GetPointActor()->GetTransform().GetLocalPosition().y
			, static_cast<float>(Z_ORDER::UI_Border) });

		SettingPointerBox_->SetBoxSize({ PointActorComponent_->GetPointActor()->GetRenderer()->GetTransform().GetLocalScale() });
	}


	if (true == GameEngineInput::GetInst()->IsDown("Select"))
	{

		PointActorComponent* PointActorComponent_ = GetLevel<HollowKnightLevel>()->PointActorListCharm.find(CurrentPosInCharmPage)->second;
		CharmSlot* slot = dynamic_cast<CharmSlot*>(PointActorComponent_->GetPointActor());


		// 부적 장착이 가능한지 && 내가 선택한 부적이 사용중이 아닌건지
		if (KnightData::GetInst()->SubUsingCharmNotches(slot->GetSlotCount()) == true && slot->GetisUsing() == false)
		{
			for (int i = 40; i < 50; ++i)
			{
				PointActorComponent* PointActorComponent_ = GetLevel<HollowKnightLevel>()->PointActorListCharm.find(i)->second;

				CharmSlot* NotesSlot = dynamic_cast<CharmSlot*>(PointActorComponent_->GetPointActor());

				//부적 칸을 사용하지 않다면
				if (NotesSlot->GetisEquippedUsing() == false)
				{
					NotesSlot->CreateCopyCharm(slot->GetRenderer(), slot->GetCharmName(), slot->GetFilePath());
					NotesSlot->SetisEquippedUsing(true);
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

		
	}


}

void SettingPointer::PointerIdleEnd(const StateInfo& _Info)
{
}

void SettingPointer::PointerMoveLeftStart(const StateInfo& _Info)
{
	if (true == GameEngineInput::GetInst()->IsDown("MoveLeft") && inLeftArrow_ == false)
	{
		inRightArrow_ = false;
		int PrevCount = CurrentPosInCharmPage;


		if ((PrevCount == 0 || PrevCount == 10 || PrevCount == 20 || PrevCount == 30) && _Info.PrevState != "IN_RIGHT_ARROW")
		{

			--CurrentPosInCharmPage;
			SettingPointeManager_.ChangeState("IN_LEFT_ARROW");
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

			SettingPointerBox_->SetBoxSize({ PointActorComponent_->GetPointActor()->GetRenderer()->GetTransform().GetLocalScale() });
		}



	}

	
}

void SettingPointer::PointerMoveLeftUpdate(float _DeltaTime, const StateInfo& _Info)
{
	SettingPointeManager_.ChangeState("IDLE");

	
}

void SettingPointer::PointerMoveLeftEnd(const StateInfo& _Info)
{
}

void SettingPointer::PointerMoveRightStart(const StateInfo& _Info)
{
	if (true == GameEngineInput::GetInst()->IsDown("MoveRight") && inRightArrow_ == false)
	{
		inLeftArrow_ = false;
		int PrevCount = CurrentPosInCharmPage;

		if ((PrevCount == 9 || PrevCount == 19 || PrevCount == 29 || PrevCount == 39) && _Info.PrevState != "IN_LEFT_ARROW")
		{
			++CurrentPosInCharmPage;
			SettingPointeManager_.ChangeState("IN_RIGHT_ARROW");
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

			SettingPointerBox_->SetBoxSize({ PointActorComponent_->GetPointActor()->GetRenderer()->GetTransform().GetLocalScale() });

		}


	}
}

void SettingPointer::PointerMoveRightUpdate(float _DeltaTime, const StateInfo& _Info)
{
	SettingPointeManager_.ChangeState("IDLE");

}

void SettingPointer::PointerMoveRightEnd(const StateInfo& _Info)
{

}

void SettingPointer::PointerInRightArrowStart(const StateInfo& _Info)
{
	inRightArrow_ = true;

	PointActorComponent* PointActorComponent_ = GetLevel<HollowKnightLevel>()->PointActorListCharm.find(50)->second;

	SettingPointerBox_->GetTransform().SetWorldPosition({ PointActorComponent_->GetPointActor()->GetTransform().GetLocalPosition().x
		, PointActorComponent_->GetPointActor()->GetTransform().GetLocalPosition().y
		, static_cast<float>(Z_ORDER::UI_Border) });

	SettingPointerBox_->SetBoxSize({ PointActorComponent_->GetPointActor()->GetRenderer()->GetTransform().GetLocalScale() });
}

void SettingPointer::PointerInRightArrowUpdate(float _DeltaTime, const StateInfo& _Info)
{
	if (true == GameEngineInput::GetInst()->IsDown("MoveLeft"))
	{
		SettingPointeManager_.ChangeState("MOVE_LEFT");
	}
}

void SettingPointer::PointerInRightArrowEnd(const StateInfo& _Info)
{
}

void SettingPointer::PointerInLeftArrowStart(const StateInfo& _Info)
{
	inLeftArrow_ = true;
	PointActorComponent* PointActorComponent_ = GetLevel<HollowKnightLevel>()->PointActorListCharm.find(51)->second;

	SettingPointerBox_->GetTransform().SetWorldPosition({ PointActorComponent_->GetPointActor()->GetTransform().GetLocalPosition().x
		, PointActorComponent_->GetPointActor()->GetTransform().GetLocalPosition().y
		, static_cast<float>(Z_ORDER::UI_Border) });

	SettingPointerBox_->SetBoxSize({ PointActorComponent_->GetPointActor()->GetRenderer()->GetTransform().GetLocalScale() });
}

void SettingPointer::PointerInLeftArrowUpdate(float _DeltaTime, const StateInfo& _Info)
{
	if (true == GameEngineInput::GetInst()->IsDown("MoveRight"))
	{
		SettingPointeManager_.ChangeState("MOVE_RIGHT");
	}

}

void SettingPointer::PointerInLeftArrowEnd(const StateInfo& _Info)
{
}
