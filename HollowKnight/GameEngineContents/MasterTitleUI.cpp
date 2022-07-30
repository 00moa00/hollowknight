#include "PreCompile.h"
#include "MasterTitleUI.h"

MasterTitleUI::MasterTitleUI() 
	:
	UIPointGameStart_(nullptr),
	UIPointMapEditor_(nullptr),
	UIPointGameExit_(nullptr)
{
}

MasterTitleUI::~MasterTitleUI() 
{
}

void MasterTitleUI::Start()
{
	UIPointGameStart_ = GetLevel()->CreateActor<UIPoint>();
	UIPointGameStart_->GetTransform().SetLocalPosition({ 0, -100, 0 });

	UIPointMapEditor_ = GetLevel()->CreateActor<UIPoint>();
	UIPointMapEditor_->GetTransform().SetLocalPosition({ 0, -200, 0 });
	UIPointMapEditor_->SetPointChangeIdleAnimation();

	UIPointGameExit_ = GetLevel()->CreateActor<UIPoint>();
	UIPointGameExit_->GetTransform().SetLocalPosition({ 0, -300, 0 });
	UIPointGameExit_->SetPointChangeIdleAnimation();

	TitleStateManager_.CreateStateMember("GameStart", this, &MasterTitleUI::GameStartUpdate);
	TitleStateManager_.CreateStateMember("MapEditor", this, &MasterTitleUI::MapEditorUpdate);
	TitleStateManager_.CreateStateMember("GameExit", this, &MasterTitleUI::GameExitUpdate);
	TitleStateManager_.ChangeState("GameStart");


	if (false == GameEngineInput::GetInst()->IsKey("PressDown"))
	{
		GameEngineInput::GetInst()->CreateKey("PressDown", VK_DOWN);
		GameEngineInput::GetInst()->CreateKey("PressUp", VK_UP);
		GameEngineInput::GetInst()->CreateKey("PressEnter", VK_RETURN);
	}
}

void MasterTitleUI::Update(float _DeltaTime)
{
	TitleStateManager_.Update(_DeltaTime);

}

void MasterTitleUI::EventOffGameStart()
{

}

void MasterTitleUI::EventOffMapEditor()
{
}

void MasterTitleUI::EventOffGameExit()
{
}

void MasterTitleUI::GameStartUpdate(float _DeltaTime, const StateInfo& _Info)
{
	if (true == GameEngineInput::GetInst()->IsDown("PressUp"))
	{
		UIPointGameExit_->SetPointChangeUpdateAnimation();
		TitleStateManager_.ChangeState("GameExit");
	}

	if (true == GameEngineInput::GetInst()->IsDown("PressDown"))
	{
		UIPointMapEditor_->SetPointChangeUpdateAnimation();
		TitleStateManager_.ChangeState("MapEditor");
	}
}

void MasterTitleUI::MapEditorUpdate(float _DeltaTime, const StateInfo& _Info)
{
	if (true == GameEngineInput::GetInst()->IsDown("PressUp"))
	{
		UIPointGameStart_->SetPointChangeUpdateAnimation();
		TitleStateManager_.ChangeState("GameStart");
	}

	if (true == GameEngineInput::GetInst()->IsDown("PressDown"))
	{
		UIPointGameExit_->SetPointChangeUpdateAnimation();
		TitleStateManager_.ChangeState("GameExit");
	}
}

void MasterTitleUI::GameExitUpdate(float _DeltaTime, const StateInfo& _Info)
{
	if (true == GameEngineInput::GetInst()->IsDown("PressUp"))
	{
		UIPointMapEditor_->SetPointChangeUpdateAnimation();
		TitleStateManager_.ChangeState("MapEditor");
	}

	if (true == GameEngineInput::GetInst()->IsDown("PressDown"))
	{
		UIPointGameStart_->SetPointChangeUpdateAnimation();
		TitleStateManager_.ChangeState("GameStart");
	}
}
