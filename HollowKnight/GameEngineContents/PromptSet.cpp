#include "PreCompile.h"
#include "PromptSet.h"

#include "GlobalContentsValue.h"

PromptSet::PromptSet() 
{
}

PromptSet::~PromptSet() 
{
}

void PromptSet::Start()
{
	PromptBack_ = CreateComponent<GameEngineTextureRenderer>();
	PromptBack_->SetTexture("black_fader.png");
	PromptBack_->GetTransform().SetWorldScale({250,150});
	PromptBack_-> GetPixelData().MulColor = { 1,1,1,0.6f };
	PromptBack_->SetScaleModeImage();
	PromptBack_->GetTransform().SetLocalPosition({ 0, 20 });

	GetTransform().SetLocalPosition({ 0, 150.f });

	PromptCollision_ = CreateComponent<GameEngineCollision>();
	PromptCollision_->GetTransform().SetLocalScale({ 600, 120 });
	PromptCollision_->ChangeOrder(COLLISION_ORDER::Prompt);

	GetCollision()->GetTransform().SetLocalPosition({ 0, -150.f });

	Prompt_ = CreateComponent<GameEngineTextureRenderer>();
	Prompt_->SetTexture("Prompts Cln_prompt_appear0000-Sheet.png", 0);
	Prompt_->GetTransform().SetWorldScale(Prompt_->GetCurTexture()->GetScale());
	Prompt_->SetScaleModeImage();

	Prompt_->CreateFrameAnimationCutTexture("APPEAR_ANIMATION", FrameAnimation_DESC("Prompts Cln_prompt_appear0000-Sheet.png", 0, 9, 0.050f, true));
	Prompt_->CreateFrameAnimationCutTexture("LEAVE_ANIMATION", FrameAnimation_DESC("Prompts Cln_prompt_appear0009-Sheet.png", 0, 9, 0.070f, false));
	Prompt_->CreateFrameAnimationCutTexture("IDLE_ANIMATION", FrameAnimation_DESC("Prompts Cln_prompt_idle0000-Sheet.png", 0, 4, 0.050f));
	

	Prompt_->AnimationBindEnd("APPEAR_ANIMATION", [=](const FrameAnimation_DESC& _Info)
		{
			Prompt_->ChangeFrameAnimation("IDLE_ANIMATION");
		});

	Prompt_->AnimationBindEnd("LEAVE_ANIMATION", [=](const FrameAnimation_DESC& _Info)
		{
			Prompt_->Off();
			PromptName_->Off();
			PromptBack_->Off();
		});

	Prompt_->ChangeFrameAnimation("APPEAR_ANIMATION");

	PromptName_ = CreateComponent<GameEngineTextureRenderer>();
	PromptName_->SetTexture("TalkFont.png");
	PromptName_->GetTransform().SetLocalScale(PromptName_->GetCurTexture()->GetScale());
	PromptName_->GetTransform().SetLocalPosition({0, 20});


	PromptManager_.CreateStateMember("WAIT"
		, std::bind(&PromptSet::PromptWaitUpdate, this, std::placeholders::_1, std::placeholders::_2)
		, std::bind(&PromptSet::PromptWaitStart, this, std::placeholders::_1)
		, std::bind(&PromptSet::PromptWaitEnd, this, std::placeholders::_1));

	PromptManager_.CreateStateMember("IDLE"
		, std::bind(&PromptSet::PromptIdleUpdate, this, std::placeholders::_1, std::placeholders::_2)
		, std::bind(&PromptSet::PromptIdleStart, this, std::placeholders::_1)
		, std::bind(&PromptSet::PromptIdleEnd, this, std::placeholders::_1));

	PromptManager_.CreateStateMember("LEAVE"
		, std::bind(&PromptSet::PromptChangeLeaveUpdate, this, std::placeholders::_1, std::placeholders::_2)
		, std::bind(&PromptSet::PromptChangeLeaveStart, this, std::placeholders::_1)
		, std::bind(&PromptSet::PromptChangeLeaveEnd, this, std::placeholders::_1));

	PromptManager_.ChangeState("WAIT");

	Prompt_->Off();
	PromptName_->Off();
	PromptBack_->Off();



	if (false == GameEngineInput::GetInst()->IsKey("PromptEnter"))
	{
		GameEngineInput::GetInst()->CreateKey("PromptEnter", VK_UP);
	}


	//PromptName_->SetScaleModeImage();

}

void PromptSet::Update(float _DeltaTime)
{
	PromptManager_.Update(_DeltaTime);
}

void PromptSet::CreatePrompSet(PromptSetType _Type)
{
	switch (_Type)
	{
	case PromptSetType::TALK:
		PromptName_->SetTexture("TalkFont.png");
		PromptName_->GetTransform().SetLocalScale(PromptName_->GetCurTexture()->GetScale());
		PromptSetType_ = _Type;

		break;
	case PromptSetType::INTER:
		PromptName_->SetTexture("InterFont.png");
		PromptName_->GetTransform().SetWorldScale({121, 42});
		PromptSetType_ = _Type;

		break;

	case PromptSetType::SEARCH:
		PromptName_->SetTexture("Search.png");
		PromptName_->GetTransform().SetLocalScale(PromptName_->GetCurTexture()->GetScale());
		PromptSetType_ = _Type;

		break;

	default:
		break;
	}
}

void PromptSet::SetPrompAppear()
{
	Prompt_->ChangeFrameAnimation("APPEAR_ANIMATION");
}

void PromptSet::SetPrompLeave()
{
	Prompt_->ChangeFrameAnimation("LEAVE_ANIMATION");
}

bool PromptSet::ThisVSKnightCollision(GameEngineCollision* _This, GameEngineCollision* _Other)
{
	return true;
}

void PromptSet::PromptWaitStart(const StateInfo& _Info)
{

}

void PromptSet::PromptWaitUpdate(float _DeltaTime, const StateInfo& _Info)
{
	if (PromptCollision_ ->IsCollision(CollisionType::CT_OBB2D, COLLISION_ORDER::Knight, CollisionType::CT_OBB2D,
		std::bind(&PromptSet::ThisVSKnightCollision, this, std::placeholders::_1, std::placeholders::_2)) == true)
	{
		PromptManager_.ChangeState("IDLE");
	}
}

void PromptSet::PromptWaitEnd(const StateInfo& _Info)
{
}

void PromptSet::PromptIdleStart(const StateInfo& _Info)
{
	Prompt_->On();
	PromptName_->On();
	PromptBack_->On();
	Prompt_->ChangeFrameAnimation("APPEAR_ANIMATION");

}

void PromptSet::PromptIdleUpdate(float _DeltaTime, const StateInfo& _Info)
{
	//if (true == GameEngineInput::GetInst()->IsDown("PromptEnter"))
	//{
	//	switch (PromptSetType_)
	//	{
	//	case PromptSetType::TALK:


	//		break;
	//	case PromptSetType::INTER:
	//		break;
	//	default:
	//		break;
	//	}
	//}

	if (PromptCollision_->IsCollision(CollisionType::CT_OBB2D, COLLISION_ORDER::Knight, CollisionType::CT_OBB2D,
		std::bind(&PromptSet::ThisVSKnightCollision, this, std::placeholders::_1, std::placeholders::_2)) == false)
	{
		PromptManager_.ChangeState("LEAVE");
	}
}

void PromptSet::PromptIdleEnd(const StateInfo& _Info)
{
	Prompt_->ChangeFrameAnimation("LEAVE_ANIMATION");
}

void PromptSet::PromptChangeLeaveStart(const StateInfo& _Info)
{
}

void PromptSet::PromptChangeLeaveEnd(const StateInfo& _Info)
{
}

void PromptSet::PromptChangeLeaveUpdate(float _DeltaTime, const StateInfo& _Info)
{
	PromptManager_.ChangeState("WAIT");
}

