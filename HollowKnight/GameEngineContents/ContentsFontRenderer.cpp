#include "PreCompile.h"
#include "ContentsFontRenderer.h"

ContentsFontRenderer::ContentsFontRenderer() 
	:
	TypingCount_(0)
{
}

ContentsFontRenderer::~ContentsFontRenderer() 
{
}

void ContentsFontRenderer::Start()
{

	FontStateManager_.CreateStateMember("TYPING_UPDATE"
		, std::bind(&ContentsFontRenderer::FontTypingUpdate, this, std::placeholders::_1, std::placeholders::_2)
		, std::bind(&ContentsFontRenderer::FontTypingStart, this, std::placeholders::_1)
		, std::bind(&ContentsFontRenderer::FontTypingEnd, this, std::placeholders::_1));

	FontStateManager_.CreateStateMember("TYPING_IDLE"
		, std::bind(&ContentsFontRenderer::FontTypingIdleUpdate, this, std::placeholders::_1, std::placeholders::_2)
		, std::bind(&ContentsFontRenderer::FontTypingIdleStart, this, std::placeholders::_1)
		, std::bind(&ContentsFontRenderer::FontTypingIdleEnd, this, std::placeholders::_1));


	FontStateManager_.ChangeState("TYPING_IDLE");

}

void ContentsFontRenderer::Update(float _DeltatTime)
{
	FontStateManager_.Update(_DeltatTime);
}

void ContentsFontRenderer::CreateFontRenderer(std::string _Text, float _FontSize, float4 _Position, bool _isTyping, int _LineBreak )
{
	if (_LineBreak > 0)
	{
		_Text.insert(_LineBreak, "\n");
	}

	for (int i = 0; i < _Text.size(); ++i)
	{
		std::string line = _Text.substr(i, 1);
		if (line == ".")
		{
			_Text.insert(i + 1, "\n\n");
			break;
		}
	}

	FontState_.Text_ = _Text;
	FontState_.FontSize_ = _FontSize;
	FontState_.isTyping_ = _isTyping;
	FontState_.TextSize_ = _Text.size();

	GameEngineFontRenderer_ = CreateComponent<GameEngineFontRenderer>();
	GameEngineFontRenderer_->ChangeCamera(CAMERAORDER::UICAMERA);

	GameEngineFontRenderer_->SetColor({ 1.0f, 1.0f, 1.0f });
	GameEngineFontRenderer_->SetScreenPostion(_Position);
	GameEngineFontRenderer_->SetSize(_FontSize);
	GameEngineFontRenderer_->SetText(_Text, "Noto Serif KR");

}

void ContentsFontRenderer::SetActorToScreenPosition(float4 _ActorPos, float4 _CameraPos)
{

	GameEngineFontRenderer_->SetScreenPostion({ _ActorPos.x - _CameraPos.x + GameEngineWindow::GetScale().x / 2 
		, ( _CameraPos.y - _ActorPos.y  + GameEngineWindow::GetScale().y /2)});


}

void ContentsFontRenderer::SetThisToScreenPosition(float4 _CameraPos)
{
	GameEngineFontRenderer_->SetScreenPostion({ GetTransform().GetWorldPosition().x - _CameraPos.x + GameEngineWindow::GetScale().x / 2
	, (_CameraPos.y - GetTransform().GetWorldPosition().y + GameEngineWindow::GetScale().y / 2) });
}

void ContentsFontRenderer::SetText(std::string _Text, int _LineBreak)
{
	if (_LineBreak > 0)
	{
		_Text.insert(_LineBreak, "\n");
	}

	for (int i = 0; i < _Text.size(); ++i)
	{
		std::string line = _Text.substr(i, 1);
		if (line == ".")
		{
			_Text.insert(i + 1, "\n\n");
			break;
		}
	}

	FontState_.Text_ = _Text;
	GameEngineFontRenderer_->SetText(_Text, "Noto Serif KR");
}

void ContentsFontRenderer::SetScreenMove()
{
	//float4 Position;

	//if (GetTransform().GetWorldPosition().x > 0)
	//{
	//	Position.x = GetTransform().GetWorldPosition().x + GameEngineWindow::GetScale().x / 2;
	//}
	//else if (GetTransform().GetWorldPosition().x == 0)
	//{
	//	Position.x = GameEngineWindow::GetScale().x / 2;
	//}
	//else
	//{
	//	Position.x =  (GetTransform().GetWorldPosition().x) * -1;
	//}

	//if (GetTransform().GetWorldPosition().y > 0)
	//{
	//	Position.y = (GameEngineWindow::GetScale().y / 2 ) - GetTransform().GetWorldPosition().y;
	//}
	//else if (GetTransform().GetWorldPosition().y == 0)
	//{
	//	Position.y = GameEngineWindow::GetScale().y / 2;
	//}
	//else
	//{
	//	Position.y = GetTransform().GetWorldPosition().y * -1 + (GameEngineWindow::GetScale().y / 2);

	//}


	//GameEngineFontRenderer_->SetScreenPostion(Position);

	GameEngineFontRenderer_->SetScreenPostion({ GetTransform().GetWorldPosition().x + GameEngineWindow::GetScale().x / 2 
, (GameEngineWindow::GetScale().y / 2) - GetTransform().GetWorldPosition().y });


}

void ContentsFontRenderer::FontOn()
{
	if (FontState_.isTyping_ == true)
	{
		FontStateManager_.ChangeState("TYPING_UPDATE");
		GameEngineFontRenderer_->SetText(" ", "Noto Serif KR");

	}
}

void ContentsFontRenderer::FontOff()
{
}

void ContentsFontRenderer::FontTypingStart(const StateInfo& _Info)
{
	TypingCount_ = 2;
}

void ContentsFontRenderer::FontTypingUpdate(float _DeltaTime, const StateInfo& _Info)
{
	TypingTimer_ += _DeltaTime;

	if (TypingCount_ > FontState_.TextSize_)
	{
		FontStateManager_.ChangeState("TYPING_IDLE");
	}
	if (TypingTimer_ > 0.5f)
	{
		TypingTimer_ = 0.f;

		std::string test = FontState_.Text_.substr(0, TypingCount_);
		GameEngineFontRenderer_->SetText(test
			, "Noto Serif KR");

		int C = TypingCount_ ;
		std::string Check = FontState_.Text_.substr(TypingCount_, 1);
		if (Check == "\n")
		{
			TypingCount_ += 1;
		}
		else
		{

			TypingCount_ += 2;
		}

	}
}

void ContentsFontRenderer::FontTypingEnd(const StateInfo& _Info)
{
	TypingCount_ = 2;
}

void ContentsFontRenderer::FontTypingIdleStart(const StateInfo& _Info)
{
}

void ContentsFontRenderer::FontTypingIdleUpdate(float _DeltaTime, const StateInfo& _Info)
{
}

void ContentsFontRenderer::FontTypingIdleEnd(const StateInfo& _Info)
{
}
