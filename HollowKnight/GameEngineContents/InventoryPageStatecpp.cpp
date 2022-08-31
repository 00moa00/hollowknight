#include "PreCompile.h"
#include "SettingPointer.h"
#include "HollowKnightLevel.h"
#include "PointActorComponent.h"
#include "GlobalContentsValue.h"
#include "KnightData.h"

#include <algorithm>

void SettingPointer::PointerInventoryPageMoveStart(const StateInfo& _Info)
{
}

void SettingPointer::PointerInventoryPageMoveUpdate(float _DeltaTime, const StateInfo& _Info)
{
	float4 MoveDir = MoveState_.Dir_ - SettingPointerBox_->GetTransform().GetWorldPosition();
	float Lenth = MoveDir.Length();

	MoveDir.Normalize();
	if (Lenth <= 3.f)
	{
		SettingPointerBox_->GetTransform().SetWorldPosition(MoveState_.Dir_);
		SettingPointerInventoryPageManager_.ChangeState(MoveState_.NextMoveStateName_);
	}

	SettingPointerBox_->GetTransform().SetWorldMove(MoveDir * PointerMoveSpeed_ * _DeltaTime);
	SettingPointerBox_->SetBoxSize({ MoveState_.Size_ });
}

void SettingPointer::PointerInventoryPageMoveEnd(const StateInfo& _Info)
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

void SettingPointer::PointerMapPageMoveStart(const StateInfo& _Info)
{
}

void SettingPointer::PointerMapPageMoveUpdate(float _DeltaTime, const StateInfo& _Info)
{
}

void SettingPointer::PointerMapPageMoveEnd(const StateInfo& _Info)
{
}

void SettingPointer::PointerMapPageIdleStart(const StateInfo& _Info)
{
}

void SettingPointer::PointerMapPageIdleUpdate(float _DeltaTime, const StateInfo& _Info)
{
}

void SettingPointer::PointerMapPageIdleEnd(const StateInfo& _Info)
{
}

void SettingPointer::PointerPageMoveLeftStart(const StateInfo& _Info)
{
}

void SettingPointer::PointerPageMoveLeftUpdate(float _DeltaTime, const StateInfo& _Info)
{
}

void SettingPointer::PointerPageMoveLeftEnd(const StateInfo& _Info)
{
}

void SettingPointer::PointerMapPageMoveRightStart(const StateInfo& _Info)
{
}

void SettingPointer::PointerMapPageMoveRightUpdate(float _DeltaTime, const StateInfo& _Info)
{
}

void SettingPointer::PointerMapPageMoveRightEnd(const StateInfo& _Info)
{
}

void SettingPointer::PointerMapPageRightArrowStart(const StateInfo& _Info)
{
}

void SettingPointer::PointerMapPageRightArrowUpdate(float _DeltaTime, const StateInfo& _Info)
{
}

void SettingPointer::PointerMapPageRightArrowEnd(const StateInfo& _Info)
{
}

void SettingPointer::PointerMapPageInLeftArrowStart(const StateInfo& _Info)
{
}

void SettingPointer::PointerMapPageInLeftArrowUpdate(float _DeltaTime, const StateInfo& _Info)
{
}

void SettingPointer::PointerMapPageInLeftArrowEnd(const StateInfo& _Info)
{
}

void SettingPointer::PointerMapPageWaitStart(const StateInfo& _Info)
{
}

void SettingPointer::PointerMapPageWaitUpdate(float _DeltaTime, const StateInfo& _Info)
{
}

void SettingPointer::PointerMapPageWaitEnd(const StateInfo& _Info)
{
}

void SettingPointer::PointerInventoryPageIdleStart(const StateInfo& _Info)
{
	PointerMoveSpeed_ = 750.f;
}

void SettingPointer::PointerInventoryPageIdleUpdate(float _DeltaTime, const StateInfo& _Info)
{
	if (true == GameEngineInput::GetInst()->IsDown("MoveRight"))
	{
		SettingPointerInventoryPageManager_.ChangeState("MOVE_RIGHT");
	}

	if (true == GameEngineInput::GetInst()->IsDown("MoveLeft"))
	{
		SettingPointerInventoryPageManager_.ChangeState("MOVE_LEFT");
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

			SettingPointerInventoryPageManager_.ChangeState("POINTER_MOVE");
			MoveState_.Dir_ = PointActorComponent_->GetPointActor()->GetTransform().GetLocalPosition();
			MoveState_.Size_ = PointActorComponent_->GetPointActor()->GetPointerSize() / 2;
			MoveState_.NextMoveStateName_ = "IDLE";
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
			
			SettingPointerInventoryPageManager_.ChangeState("POINTER_MOVE");
			MoveState_.Dir_ = PointActorComponent_->GetPointActor()->GetTransform().GetLocalPosition();
			MoveState_.Size_ = PointActorComponent_->GetPointActor()->GetPointerSize() / 2;
			MoveState_.NextMoveStateName_ = "IDLE";


		}

		//내가 지금 소비 아이템에 있다면
		else if (PrevCount > static_cast<int>(ITEM_LIST::SELL_MIN) && PrevCount < static_cast<int>(ITEM_LIST::SELL_MAX))
		{
			for (int i = static_cast<int>(ITEM_LIST::NORMAL_MAX) - 1; i > static_cast<int>(ITEM_LIST::NORMAL_MIN); --i)
			{
				PointActorComponent* PointActorComponent_ = GetLevel<HollowKnightLevel>()->PointActorListInventory.find(i)->second;
				ItemSlot* FindSlot = dynamic_cast<ItemSlot*>(PointActorComponent_->GetPointActor());

				if (FindSlot != nullptr && FindSlot->GetisItem() == true)
				{
					CurrentPosInInventoryPage = i;
					break;
				}
			}
			PointActorComponent* PointActorComponent_ = GetLevel<HollowKnightLevel>()->PointActorListInventory.find(CurrentPosInInventoryPage)->second;

			SettingPointerInventoryPageManager_.ChangeState("POINTER_MOVE");
			MoveState_.Dir_ = PointActorComponent_->GetPointActor()->GetTransform().GetLocalPosition();
			MoveState_.Size_ = PointActorComponent_->GetPointActor()->GetPointerSize() / 2;
			MoveState_.NextMoveStateName_ = "IDLE";
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

			SettingPointerInventoryPageManager_.ChangeState("POINTER_MOVE");
			MoveState_.Dir_ = PointActorComponent_->GetPointActor()->GetTransform().GetLocalPosition();
			MoveState_.Size_ = PointActorComponent_->GetPointActor()->GetPointerSize() / 2;
			MoveState_.NextMoveStateName_ = "IDLE";
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

			SettingPointerInventoryPageManager_.ChangeState("POINTER_MOVE");
			MoveState_.Dir_ = PointActorComponent_->GetPointActor()->GetTransform().GetLocalPosition();
			MoveState_.Size_ = PointActorComponent_->GetPointActor()->GetPointerSize() / 2;
			MoveState_.NextMoveStateName_ = "IDLE";
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
	if (inLeftArrow_ == false)
	{
		inRightArrow_ = false;
		int PrevCount = CurrentPosInInventoryPage;

		if ((PrevCount == static_cast<int>(ITEM_LIST::Heart_Piece)
			|| PrevCount == static_cast<int>(ITEM_LIST::Nail)
			|| PrevCount == static_cast<int>(ITEM_LIST::Item_Geo)

			) && _Info.PrevState != "IN_RIGHT_ARROW")
		{
			--CurrentPosInInventoryPage;

			PointActorComponent* PointActorComponent_ = GetLevel<HollowKnightLevel>()->PointActorListInventory.find(51)->second;

			SettingPointerInventoryPageManager_.ChangeState("POINTER_MOVE");
			PointerMoveSpeed_ = 1500.f;

			MoveState_.Dir_ = PointActorComponent_->GetPointActor()->GetTransform().GetLocalPosition();
			MoveState_.Size_ = PointActorComponent_->GetPointActor()->GetPointerSize() / 2;
			MoveState_.NextMoveStateName_ = "IN_LEFT_ARROW";
			return;
		}

		//다음 갈 곳이 스펠이다
		else if (PrevCount == 10 || PrevCount == 14 || PrevCount == 18 || PrevCount == 22)
		{
			CurrentPosInInventoryPage = static_cast<int>(ITEM_LIST::Dream_Nail);

			PointActorComponent* PointActorComponent_ = GetLevel<HollowKnightLevel>()->PointActorListInventory.find(CurrentPosInInventoryPage)->second;

			SettingPointerInventoryPageManager_.ChangeState("POINTER_MOVE");
			MoveState_.Dir_ = PointActorComponent_->GetPointActor()->GetTransform().GetLocalPosition();
			MoveState_.Size_ = PointActorComponent_->GetPointActor()->GetPointerSize() / 2;
			MoveState_.NextMoveStateName_ = "IDLE";
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

			SettingPointerInventoryPageManager_.ChangeState("POINTER_MOVE");
			MoveState_.Dir_ = PointActorComponent_->GetPointActor()->GetTransform().GetLocalPosition();
			MoveState_.Size_ = PointActorComponent_->GetPointActor()->GetPointerSize() / 2;
			MoveState_.NextMoveStateName_ = "IDLE";
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

			SettingPointerInventoryPageManager_.ChangeState("POINTER_MOVE");
			MoveState_.Dir_ = PointActorComponent_->GetPointActor()->GetTransform().GetLocalPosition();
			MoveState_.Size_ = PointActorComponent_->GetPointActor()->GetPointerSize() / 2;
			MoveState_.NextMoveStateName_ = "IDLE";
		}
	}
}

void SettingPointer::PointerInventoryPageMoveLeftUpdate(float _DeltaTime, const StateInfo& _Info)
{
	SettingPointerInventoryPageManager_.ChangeState("IDLE");
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

		if (PrevCount == static_cast<int>(ITEM_LIST::Dream_Nail) || PrevCount == static_cast<int>(ITEM_LIST::Spell_Scream) || PrevCount == static_cast<int>(ITEM_LIST::Item_Geo))
		{

			PointActorComponent* PointActorComponent_ = GetLevel<HollowKnightLevel>()->PointActorListInventory.find(10)->second;
			ItemSlot* CheckItem = dynamic_cast<ItemSlot*>(PointActorComponent_->GetPointActor());

			if (CheckItem->GetisItem() == false) // 아이템이 하나라도 없으면 aroow로 이동
			{
				++CurrentPosInInventoryPage;
				PointActorComponent_ = GetLevel<HollowKnightLevel>()->PointActorListInventory.find(50)->second;

				SettingPointerInventoryPageManager_.ChangeState("POINTER_MOVE");
				PointerMoveSpeed_ = 1500.f;

				MoveState_.Dir_ = PointActorComponent_->GetPointActor()->GetTransform().GetLocalPosition();
				MoveState_.Size_ = PointActorComponent_->GetPointActor()->GetPointerSize() / 2;

				MoveState_.NextMoveStateName_ = "IN_RIGHT_ARROW";

				return;
			}

			else
			{
				CurrentPosInInventoryPage = 10;

				PointActorComponent* PointActorComponent_ = GetLevel<HollowKnightLevel>()->PointActorListInventory.find(CurrentPosInInventoryPage)->second;

				SettingPointerInventoryPageManager_.ChangeState("POINTER_MOVE");
				MoveState_.Dir_ = PointActorComponent_->GetPointActor()->GetTransform().GetLocalPosition();
				MoveState_.Size_ = PointActorComponent_->GetPointActor()->GetPointerSize() / 2;
				MoveState_.NextMoveStateName_ = "IDLE";

			}

		}

		else if (PrevCount > static_cast<int>(ITEM_LIST::NORMAL_MIN) && PrevCount < static_cast<int>(ITEM_LIST::NORMAL_MAX)) // 내가 지금 아이템 카테고리에 있다
		{
			PointActorComponent* PointActorComponent_ = GetLevel<HollowKnightLevel>()->PointActorListInventory.find(PrevCount + 1)->second;
			ItemSlot* CheckItem = dynamic_cast<ItemSlot*>(PointActorComponent_->GetPointActor());

			if (CheckItem->GetisItem() == false) // 내가 갈 곳에 아이템이 없으면
			{
				++CurrentPosInInventoryPage;
				PointActorComponent_ = GetLevel<HollowKnightLevel>()->PointActorListInventory.find(50)->second;

				SettingPointerInventoryPageManager_.ChangeState("POINTER_MOVE");
				PointerMoveSpeed_ = 1500.f;

				MoveState_.Dir_ = PointActorComponent_->GetPointActor()->GetTransform().GetLocalPosition();
				MoveState_.Size_ = PointActorComponent_->GetPointActor()->GetPointerSize() / 2;

				MoveState_.NextMoveStateName_ = "IN_RIGHT_ARROW";
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

				SettingPointerInventoryPageManager_.ChangeState("POINTER_MOVE");
				MoveState_.Dir_ = PointActorComponent_->GetPointActor()->GetTransform().GetLocalPosition();
				MoveState_.Size_ = PointActorComponent_->GetPointActor()->GetPointerSize() / 2;
				MoveState_.NextMoveStateName_ = "IDLE";
			}

		}

		else if (PrevCount > static_cast<int>(ITEM_LIST::SELL_MIN) && PrevCount < static_cast<int>(ITEM_LIST::SELL_MAX))
		{
			if (PrevCount + 1 == static_cast<int>(ITEM_LIST::SELL_MAX))
			{
				++CurrentPosInInventoryPage;
				PointActorComponent* PointActorComponent_ = GetLevel<HollowKnightLevel>()->PointActorListInventory.find(50)->second;

				SettingPointerInventoryPageManager_.ChangeState("POINTER_MOVE");
				PointerMoveSpeed_ = 1500.f;

				MoveState_.Dir_ = PointActorComponent_->GetPointActor()->GetTransform().GetLocalPosition();
				MoveState_.Size_ = PointActorComponent_->GetPointActor()->GetPointerSize() / 2;

				MoveState_.NextMoveStateName_ = "IN_RIGHT_ARROW";

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
					PointActorComponent* PointActorComponent_ = GetLevel<HollowKnightLevel>()->PointActorListInventory.find(50)->second;

					SettingPointerInventoryPageManager_.ChangeState("POINTER_MOVE");
					PointerMoveSpeed_ = 1500.f;

					MoveState_.Dir_ = PointActorComponent_->GetPointActor()->GetTransform().GetLocalPosition();
					MoveState_.Size_ = PointActorComponent_->GetPointActor()->GetPointerSize() / 2;

					MoveState_.NextMoveStateName_ = "IN_RIGHT_ARROW";
					return;
				}
				{
					PointActorComponent* PointActorComponent_ = GetLevel<HollowKnightLevel>()->PointActorListInventory.find(CurrentPosInInventoryPage)->second;

					SettingPointerInventoryPageManager_.ChangeState("POINTER_MOVE");
					MoveState_.Dir_ = PointActorComponent_->GetPointActor()->GetTransform().GetLocalPosition();
					MoveState_.Size_ = PointActorComponent_->GetPointActor()->GetPointerSize() / 2;
					MoveState_.NextMoveStateName_ = "IDLE";
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

			SettingPointerInventoryPageManager_.ChangeState("POINTER_MOVE");
			MoveState_.Dir_ = PointActorComponent_->GetPointActor()->GetTransform().GetLocalPosition();
			MoveState_.Size_ = PointActorComponent_->GetPointActor()->GetPointerSize() / 2;
			MoveState_.NextMoveStateName_ = "IDLE";
		}
	}
}

void SettingPointer::PointerInventoryPageMoveRightUpdate(float _DeltaTime, const StateInfo& _Info)
{
	SettingPointerInventoryPageManager_.ChangeState("IDLE");
}

void SettingPointer::PointerInventoryPageMoveRightEnd(const StateInfo& _Info)
{
	CurrentPosInInventoryPage = 0;

}

void SettingPointer::PointerInInventoryPageRightArrowStart(const StateInfo& _Info)
{
	inRightArrow_ = true;

}

void SettingPointer::PointerInInventoryPageRightArrowUpdate(float _DeltaTime, const StateInfo& _Info)
{
	if (true == GameEngineInput::GetInst()->IsDown("MoveLeft"))
	{
		SettingPointerInventoryPageManager_.ChangeState("MOVE_LEFT");
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

}

void SettingPointer::PointerInventoryPageInLeftArrowUpdate(float _DeltaTime, const StateInfo& _Info)
{
	if (true == GameEngineInput::GetInst()->IsDown("MoveLeft"))
	{
		isDownLextPageLeft_ = true;
	}

	else if (true == GameEngineInput::GetInst()->IsDown("MoveRight"))
	{
		SettingPointerInventoryPageManager_.ChangeState("MOVE_RIGHT");
	}
}

void SettingPointer::PointerInventoryPageInLeftArrowEnd(const StateInfo& _Info)
{
	CurrentPosInInventoryPage = 0;
}

