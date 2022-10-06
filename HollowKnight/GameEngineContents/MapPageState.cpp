#include "PreCompile.h"
#include "SettingPointer.h"
#include "HollowKnightLevel.h"
#include "PointActorComponent.h"
#include "GlobalContentsValue.h"
#include "KnightData.h"

#include <algorithm>


void SettingPointer::PointerMapPageIdleStart(const StateInfo& _Info)
{
	SettingPointerBox_->AllPointerOff();
	GameEngineSound::SoundPlayOneShot("ui_change_selection.ogg");

}

void SettingPointer::PointerMapPageIdleUpdate(float _DeltaTime, const StateInfo& _Info)
{
	if (true == GameEngineInput::GetInst()->IsDown("MoveRight"))
	{
		SettingPointerMapPageManager_.ChangeState("MOVE_RIGHT");
	}

	if (true == GameEngineInput::GetInst()->IsDown("MoveLeft"))
	{
		SettingPointerMapPageManager_.ChangeState("MOVE_LEFT");
	}

	if (true == GameEngineInput::GetInst()->IsDown("MoveUp"))
	{
		CurrentPosInMapPage = 0;

		for (int i = 0; i < 2; ++i)
		{
			PointActorComponent* PointActorComponent_ = GetLevel<HollowKnightLevel>()->PointActorListMap.find(i)->second;
			WorldMap* FindMap = dynamic_cast<WorldMap*>(PointActorComponent_->GetPointActor());

			if (CurrentPosInMapPage == i)
			{
				FindMap->ChangeTextureSelect();
			}
			else
			{
				FindMap->ChangeTextureIdle();
			}
		}
	}

	if (true == GameEngineInput::GetInst()->IsDown("MoveDown"))
	{
		CurrentPosInMapPage = 1;

		for (int i = 0; i < 2; ++i)
		{
			PointActorComponent* PointActorComponent_ = GetLevel<HollowKnightLevel>()->PointActorListMap.find(i)->second;
			WorldMap* FindMap = dynamic_cast<WorldMap*>(PointActorComponent_->GetPointActor());

			if (CurrentPosInMapPage == i)
			{
				FindMap->ChangeTextureSelect();
			}
			else
			{
				FindMap->ChangeTextureIdle();
			}
		}
	}

	if (true == GameEngineInput::GetInst()->IsDown("Select"))
	{
		SettingPointerMapPageManager_.ChangeState("WIDE");
	}
}

void SettingPointer::PointerMapPageIdleEnd(const StateInfo& _Info)
{
}

void SettingPointer::PointerPageMoveLeftStart(const StateInfo& _Info)
{
	SettingPointerBox_->AllPointerOff();
	if (inLeftArrow_ == false)
	{
		inRightArrow_ = false;
		int PrevCount = CurrentPosInMapPage;

		if ((PrevCount == static_cast<int>(MAP_LIST::DIRTMOUTH) || PrevCount == static_cast<int>(MAP_LIST::CORSSROAD)) && _Info.PrevState != "IN_LEFT_ARROW")
		{
			SettingPointerMapPageManager_.ChangeState("IN_LEFT_ARROW");

			return;
		}

		else
		{
			--CurrentPosInMapPage;
			for (int i = 0; i < 2; ++i)
			{
				PointActorComponent* PointActorComponent_ = GetLevel<HollowKnightLevel>()->PointActorListMap.find(i)->second;
				WorldMap* FindMap = dynamic_cast<WorldMap*>(PointActorComponent_->GetPointActor());

				if (CurrentPosInMapPage == i)
				{
					FindMap->ChangeTextureSelect();
				}
				else
				{
					FindMap->ChangeTextureIdle();
				}
			}
		}

	}
}

void SettingPointer::PointerPageMoveLeftUpdate(float _DeltaTime, const StateInfo& _Info)
{
	SettingPointerMapPageManager_.ChangeState("IDLE");
}

void SettingPointer::PointerPageMoveLeftEnd(const StateInfo& _Info)
{
}

void SettingPointer::PointerMapPageMoveRightStart(const StateInfo& _Info)
{
	SettingPointerBox_->AllPointerOff();
	if (inRightArrow_ == false)
	{
		inLeftArrow_ = false;
		int PrevCount = CurrentPosInMapPage;

		if ((PrevCount == static_cast<int>(MAP_LIST::DIRTMOUTH) || PrevCount == static_cast<int>(MAP_LIST::CORSSROAD)) && _Info.PrevState != "IN_RIGHT_ARROW")
		{
			//CurrentPosInMapPage = 2;
			SettingPointerMapPageManager_.ChangeState("IN_RIGHT_ARROW");

			return;
		}

		else
		{
			++CurrentPosInMapPage;

			for (int i = 0; i < 2; ++i)
			{
				PointActorComponent* PointActorComponent_ = GetLevel<HollowKnightLevel>()->PointActorListMap.find(i)->second;
				WorldMap* FindMap = dynamic_cast<WorldMap*>(PointActorComponent_->GetPointActor());

				if (CurrentPosInMapPage == i)
				{
					FindMap->ChangeTextureSelect();
				}

				else
				{
					FindMap->ChangeTextureIdle();
				}
			}
		}
	}
}

void SettingPointer::PointerMapPageMoveRightUpdate(float _DeltaTime, const StateInfo& _Info)
{
	SettingPointerMapPageManager_.ChangeState("IDLE");
}

void SettingPointer::PointerMapPageMoveRightEnd(const StateInfo& _Info)
{
}

void SettingPointer::PointerMapPageRightArrowStart(const StateInfo& _Info)
{
	inRightArrow_ = true;

	SettingPointerBox_->AllPointerOn();

	PointActorComponent* PointActorComponent_ = GetLevel<HollowKnightLevel>()->PointActorListMap.find(50)->second;
	SettingPointerBox_->GetTransform().SetWorldPosition({ PointActorComponent_->GetPointActor()->GetTransform().GetLocalPosition().x
		, PointActorComponent_->GetPointActor()->GetTransform().GetLocalPosition().y
		, static_cast<float>(Z_ORDER::UI_Border) });

	SettingPointerBox_->SetBoxSize({ PointActorComponent_->GetPointActor()->GetPointerSize() / 2 });


	for (int i = 0; i < 2; ++i)
	{
		PointActorComponent* PointActorComponent_ = GetLevel<HollowKnightLevel>()->PointActorListMap.find(i)->second;
		WorldMap* FindMap = dynamic_cast<WorldMap*>(PointActorComponent_->GetPointActor());

		FindMap->ChangeTextureIdle();
	}
}

void SettingPointer::PointerMapPageRightArrowUpdate(float _DeltaTime, const StateInfo& _Info)
{
	if (true == GameEngineInput::GetInst()->IsDown("MoveLeft"))
	{
		SettingPointerMapPageManager_.ChangeState("MOVE_LEFT");
	}

	else if (true == GameEngineInput::GetInst()->IsDown("MoveRight"))
	{
		isDownNextPageRight_ = true;
	}
}

void SettingPointer::PointerMapPageRightArrowEnd(const StateInfo& _Info)
{
	CurrentPosInMapPage = 2;
}

void SettingPointer::PointerMapPageInLeftArrowStart(const StateInfo& _Info)
{
	inLeftArrow_ = true;

	SettingPointerBox_->AllPointerOn();

	PointActorComponent* PointActorComponent_ = GetLevel<HollowKnightLevel>()->PointActorListMap.find(51)->second;
	SettingPointerBox_->GetTransform().SetWorldPosition({ PointActorComponent_->GetPointActor()->GetTransform().GetLocalPosition().x
		, PointActorComponent_->GetPointActor()->GetTransform().GetLocalPosition().y
		, static_cast<float>(Z_ORDER::UI_Border) });

	SettingPointerBox_->SetBoxSize({ PointActorComponent_->GetPointActor()->GetPointerSize() / 2 });

	for (int i = 0; i < 2; ++i)
	{
		PointActorComponent* PointActorComponent_ = GetLevel<HollowKnightLevel>()->PointActorListMap.find(i)->second;
		WorldMap* FindMap = dynamic_cast<WorldMap*>(PointActorComponent_->GetPointActor());

		FindMap->ChangeTextureIdle();
	}
}

void SettingPointer::PointerMapPageInLeftArrowUpdate(float _DeltaTime, const StateInfo& _Info)
{
	if (true == GameEngineInput::GetInst()->IsDown("MoveLeft"))
	{
		isDownLextPageLeft_ = true;
	}
	else if (true == GameEngineInput::GetInst()->IsDown("MoveRight"))
	{
		SettingPointerMapPageManager_.ChangeState("MOVE_RIGHT");
	}
}

void SettingPointer::PointerMapPageInLeftArrowEnd(const StateInfo& _Info)
{
	CurrentPosInMapPage = -1;
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

void SettingPointer::PointerMapPageWideMapStart(const StateInfo& _Info)
{
	for (int i = 0; i < 2; ++i)
	{
		PointActorComponent* PointActorComponent_ = GetLevel<HollowKnightLevel>()->PointActorListMap.find(i)->second;
		WorldMap* FindMap = dynamic_cast<WorldMap*>(PointActorComponent_->GetPointActor());

		FindMap->Off();
	}



	PointActorComponent* PointActorComponent_ = GetLevel<HollowKnightLevel>()->PointActorListMap.find(CurrentPosInMapPage)->second;
	WorldMap* FindMap = dynamic_cast<WorldMap*>(PointActorComponent_->GetPointActor());

	float4 Pivot = { 0,0,0,0 };

	MAP_LIST MapType = FindMap->GetMapType();
	switch (MapType)
	{

	case MAP_LIST::DIRTMOUTH:
		Pivot = { -200, 200 };

		break;
	case MAP_LIST::CORSSROAD:

		break;

	default:
		break;
	}

	//BackGround_->Off();
	GetLevel<HollowKnightLevel>()->GetAllLocalMap()->OpenAllLocalMap(Pivot);
	GetLevel<HollowKnightLevel>()->GetSettingPage()->SetBackGroundOff();
	BackGround_->On();
}

void SettingPointer::PointerMapPageWideMapUpdate(float _DeltaTime, const StateInfo& _Info)
{
	if (true == GameEngineInput::GetInst()->IsDown("Select"))
	{
		SettingPointerMapPageManager_.ChangeState("IDLE");
	}
}

void SettingPointer::PointerMapPageWideMapEnd(const StateInfo& _Info)
{
	for (int i = 0; i < 2; ++i)
	{
		PointActorComponent* PointActorComponent_ = GetLevel<HollowKnightLevel>()->PointActorListMap.find(i)->second;
		WorldMap* FindMap = dynamic_cast<WorldMap*>(PointActorComponent_->GetPointActor());

		FindMap->On();
	}



	GetLevel<HollowKnightLevel>()->GetAllLocalMap()->CloseAllLocalMap();
	GetLevel<HollowKnightLevel>()->GetSettingPage()->SetBackGroundOn();
	BackGround_->Off();

}
