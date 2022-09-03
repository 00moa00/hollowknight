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
}

void ContentsFontRenderer::CreateFontRenderer(std::string _Text, float _FontSize, float4 _Position, bool _isTyping)
{
	GameEngineFontRenderer_ = CreateComponent<GameEngineFontRenderer>();
	GameEngineFontRenderer_->SetColor({ 1.0f, 1.0f, 1.0f });
	GameEngineFontRenderer_->SetScreenPostion(_Position);
	GameEngineFontRenderer_->SetSize(_FontSize);
	GameEngineFontRenderer_->SetLeftAndRightSort(LeftAndRightSort::CENTER);
	GameEngineFontRenderer_->SetTopAndBotSort(TopAndBotSort::VCENTER);
	GameEngineFontRenderer_->SetText(_Text, "Noto Serif KR");

	FontState_.FontSize_ = _FontSize;
	FontState_.Text_ = _Text;
	FontState_.isTyping_ = _isTyping;
	FontState_.TextSize_ = _Text.size();

}

void ContentsFontRenderer::FontOn()
{
	if (FontState_.isTyping_ == true)
	{
		FontStateManager_.ChangeState("TYPING_UPDATE");
		GameEngineFontRenderer_->SetText("", "Noto Serif KR");

	}
}

void ContentsFontRenderer::FontOff()
{
}



void ContentsFontRenderer::FontTypingStart(const StateInfo& _Info)
{
	TypingCount_ = 0;
}

void ContentsFontRenderer::FontTypingUpdate(float _DeltaTime, const StateInfo& _Info)
{
	TypingTimer_ += _DeltaTime;

	if (TypingCount_ >= FontState_.TextSize_)
	{
		FontStateManager_.ChangeState("TYPING_IDLE");
	}

	if (TypingTimer_ > 0.5f)
	{
		GameEngineFontRenderer_->SetText(FontState_.Text_.substr(TypingCount_), "Noto Serif KR");

		++TypingCount_;
	}
}

void ContentsFontRenderer::FontTypingEnd(const StateInfo& _Info)
{
	TypingCount_ = 0;
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
