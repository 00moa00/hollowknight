#include "PreCompile.h"
#include "SettingPointer.h"
#include "HollowKnightLevel.h"
#include "PointActorComponent.h"
#include "GlobalContentsValue.h"

#include <algorithm>


SettingPointer::SettingPointer() 
	:
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
		GameEngineInput::GetInst()->CreateKey("MoveRight", 'D');
		GameEngineInput::GetInst()->CreateKey("MoveLeft", 'A');
	}



//	SettingPointerBoxtManager_.ChangeState("ZOOM_OUT");

}

void SettingPointer::Update(float _DeltaTime)
{
	if (true == GameEngineInput::GetInst()->IsDown("MoveRight"))
	{
		PointActorComponent* PointActorComponent_ = GetLevel<HollowKnightLevel>()->PointActorListCharm.find(CurrentPosInCharmPage)->second;
		PointActorComponent_->GetTransform().GetLocalPosition();

		GetTransform().SetLocalPosition({ PointActorComponent_->GetTransform().GetLocalPosition().x
			, PointActorComponent_->GetTransform().GetLocalPosition().y
			, static_cast<float>(Z_ORDER::UI_Border) });

		++CurrentPosInCharmPage;
	}
}
