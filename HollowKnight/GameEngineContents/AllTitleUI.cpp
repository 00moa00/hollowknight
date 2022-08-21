#include "PreCompile.h"
#include "AllTitleUI.h"

AllTitleUI::AllTitleUI() 
	:
	UIPointGameStart_(nullptr),
	UIPointMapEditor_(nullptr),
	UIPointGameExit_(nullptr),
	GameStartFont_(nullptr),
	MapEditorFont_(nullptr),
	GameExitFont_(nullptr)
{
}

AllTitleUI::~AllTitleUI() 
{
}

void AllTitleUI::Start()
{


	UIPointGameStart_ = GetLevel()->CreateActor<UIPoint>();
	UIPointGameStart_->GetTransform().SetLocalPosition({ 0, -100, 0 });

	UIPointMapEditor_ = GetLevel()->CreateActor<UIPoint>();
	UIPointMapEditor_->GetTransform().SetLocalPosition({ 0, -200, 0 });
	UIPointMapEditor_->SetPointChangeIdleAnimation();

	UIPointGameExit_ = GetLevel()->CreateActor<UIPoint>();
	UIPointGameExit_->GetTransform().SetLocalPosition({ 0, -300, 0 });
	UIPointGameExit_->SetPointChangeIdleAnimation();

	GameStartFont_ = CreateComponent<GameEngineFontRenderer>();
	
	GameStartFont_->SetText("게임 시작", "Noto Serif KR");
	GameStartFont_->SetColor({ 1.0f, 1.0f, 1.0f });
	GameStartFont_->SetScreenPostion({ GameEngineWindow::GetInst()->GetScale().hx(), (GameEngineWindow::GetInst()->GetScale().hy() + 100.0f)});
	GameStartFont_->SetSize(35);
	GameStartFont_->SetLeftAndRightSort(LeftAndRightSort::CENTER);
	GameStartFont_->SetTopAndBotSort(TopAndBotSort::VCENTER);

	MapEditorFont_ = CreateComponent<GameEngineFontRenderer>();

	MapEditorFont_->SetText("멥 에디터", "Noto Serif KR");
	MapEditorFont_->SetColor({ 1.0f, 1.0f, 1.0f });
	MapEditorFont_->SetScreenPostion({ GameEngineWindow::GetInst()->GetScale().hx(), (GameEngineWindow::GetInst()->GetScale().hy() + 200.0f) });
	MapEditorFont_->SetSize(35);
	MapEditorFont_->SetLeftAndRightSort(LeftAndRightSort::CENTER);
	MapEditorFont_->SetTopAndBotSort(TopAndBotSort::VCENTER);


	GameExitFont_ = CreateComponent<GameEngineFontRenderer>();

	GameExitFont_->SetText("게임 종료", "Noto Serif KR");
	GameExitFont_->SetColor({ 1.0f, 1.0f, 1.0f });
	GameExitFont_->SetScreenPostion({ GameEngineWindow::GetInst()->GetScale().hx(), (GameEngineWindow::GetInst()->GetScale().hy() + 300.0f) });
	GameExitFont_->SetSize(35);
	GameExitFont_->SetLeftAndRightSort(LeftAndRightSort::CENTER);
	GameExitFont_->SetTopAndBotSort(TopAndBotSort::VCENTER);

	
	//GameStartFont_->GetTransform().SetWorldPosition({ 500.0f, 100.0f,0 });


	TitleStateManager_.CreateStateMember("GameStart"
		, std::bind(&AllTitleUI::GameStartUpdate, this, std::placeholders::_1, std::placeholders::_2));

	TitleStateManager_.CreateStateMember("MapEditor"
		, std::bind(&AllTitleUI::MapEditorUpdate, this, std::placeholders::_1, std::placeholders::_2));


	TitleStateManager_.CreateStateMember("GameExit"
		, std::bind(&AllTitleUI::GameExitUpdate, this, std::placeholders::_1, std::placeholders::_2));

	TitleStateManager_.ChangeState("GameStart");


	if (false == GameEngineInput::GetInst()->IsKey("PressDown"))
	{
		GameEngineInput::GetInst()->CreateKey("PressDown", VK_DOWN);
		GameEngineInput::GetInst()->CreateKey("PressUp", VK_UP);
		GameEngineInput::GetInst()->CreateKey("PressEnter", VK_RETURN);
	}
}

void AllTitleUI::Update(float _DeltaTime)
{
	TitleStateManager_.Update(_DeltaTime);

}

void AllTitleUI::EventOffGameStart()
{

}

void AllTitleUI::EventOffMapEditor()
{
}

void AllTitleUI::EventOffGameExit()
{
}

void AllTitleUI::GameStartUpdate(float _DeltaTime, const StateInfo& _Info)
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

	if (true == GameEngineInput::GetInst()->IsDown("PressEnter"))
	{
		GEngine::ChangeLevel("DirtmouthLevel2");
	}
}

void AllTitleUI::MapEditorUpdate(float _DeltaTime, const StateInfo& _Info)
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

void AllTitleUI::GameExitUpdate(float _DeltaTime, const StateInfo& _Info)
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
