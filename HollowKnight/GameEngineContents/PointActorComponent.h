#pragma once
#include <GameEngineBase/GameEngineTransform.h>
#include <GameEngineCore/GameEngineTransformComponent.h>
#include "SettingUIMaster.h"
#include "SettingPointer.h"
#include "HollowKnightLevel.h"


// Ό³Έν :
class PointActorComponent : public GameEngineTransformComponent
{
public:
	// constrcuter destructer
	PointActorComponent();
	~PointActorComponent();

	// delete Function
	PointActorComponent(const PointActorComponent& _Other) = delete;
	PointActorComponent(PointActorComponent&& _Other) noexcept = delete;
	PointActorComponent& operator=(const PointActorComponent& _Other) = delete;
	PointActorComponent& operator=(PointActorComponent&& _Other) noexcept = delete;

protected:

	void Start() override;

private:
	SettingUIMaster* SettingUIMasterPointer_;
public:

	SettingUIMaster* GetPointActor()
	{
		return SettingUIMasterPointer_;
	}


	void PushPointerActor(int _Order, PAGE_TYPE _PageType, SettingUIMaster* _SettingUIMasterPointer_)
	{

		switch (_PageType)
		{
		case PAGE_TYPE::Charm:
			GetActor()->GetLevel<HollowKnightLevel>()->PushPointActorCharm(_Order, this);
			SettingUIMasterPointer_ = _SettingUIMasterPointer_;
			break;
		case PAGE_TYPE::MonsterBook:
			GetActor()->GetLevel<HollowKnightLevel>()->PushPointActorMonsterBook(_Order, this);
			SettingUIMasterPointer_ = _SettingUIMasterPointer_;

			break;
		case PAGE_TYPE::Map:
			GetActor()->GetLevel<HollowKnightLevel>()->PushPointActorMap(_Order, this);
			SettingUIMasterPointer_ = _SettingUIMasterPointer_;

			break;
		case PAGE_TYPE::Inventory:
			GetActor()->GetLevel<HollowKnightLevel>()->PushPointActorInventory(_Order, this);
			SettingUIMasterPointer_ = _SettingUIMasterPointer_;

			break;
		default:
			break;
		}
	}

};

