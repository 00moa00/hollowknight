#include "PreCompile.h"
#include "RoomPotal.h"
#include "GlobalContentsValue.h"

RoomPotal::RoomPotal() 
	:
	PromptSet_(nullptr),

	FadeOut_(nullptr),
	FadeIn_(nullptr)
{
}

RoomPotal::~RoomPotal() 
{
}

void RoomPotal::Start()
{

}

void RoomPotal::Update(float _DeltaTime)
{
	if (GetCollision()->IsCollision(CollisionType::CT_OBB2D, COLLISION_ORDER::Knight, CollisionType::CT_OBB2D,
		std::bind(&RoomPotal::PotalVSKnightCollision, this, std::placeholders::_1, std::placeholders::_2)) == true
		)
	{

		if (FadeOut_ == nullptr)
		{
			FadeOut_ = GetLevel()->CreateActor<FadeOut>();

		}
		//return;
	}

}

void RoomPotal::CreatePotal(POTAL_TYPE _Type, bool isPromt)
{
	if (isPromt == true)
	{
		PromptSet_ = GetLevel()->CreateActor<PromptSet>();
		PromptSet_->SetParent(this);

		PromptSet_->GetCollision()->GetTransform().SetLocalScale(float4{ 400, 200, 1 });
		PromptSet_->CreatePrompSet(PromptSetType::INTER);
	}


	CreateCollisionComponent(float4{ 300, 200, 1 }, static_cast<int>(COLLISION_ORDER::Potal));
	PotalType_ = _Type;
}

void RoomPotal::LevelStartEvent()
{

}

void RoomPotal::LevelEndEvent()
{
	if (FadeOut_ != nullptr)
	{
		if (FadeOut_->GetDeathflag() == true)
		{
			//	GEngine::ChangeLevel(Level_);
			FadeOut_->Death();
			FadeOut_ = nullptr;
		}
	}
}

bool RoomPotal::PotalVSKnightCollision(GameEngineCollision* _This, GameEngineCollision* _Other)
{
	if (GameEngineInput::GetInst()->IsDown("KnightUp") == true)
	{
		return true;
	}

	else
	{
		return false;
	}

}
