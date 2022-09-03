#pragma once
#include <GameEngineCore/CoreMinimal.h>
#include <GameEngineCore/GameEngineCollision.h>

#include <GameEngineCore/GameEngineFontRenderer.h>

struct FontState
{
	std::string Text_;
	float FontSize_;
	int TextSize_;

	bool isTyping_;
};

// 설명 : 문장을 전부 받으면 델타타임과 fsm을 이용해서 타이핑을 한다

class ContentsFontRenderer : public GameEngineActor
{
public:
	// constrcuter destructer
	ContentsFontRenderer();
	~ContentsFontRenderer();

	// delete Function
	ContentsFontRenderer(const ContentsFontRenderer& _Other) = delete;
	ContentsFontRenderer(ContentsFontRenderer&& _Other) noexcept = delete;
	ContentsFontRenderer& operator=(const ContentsFontRenderer& _Other) = delete;
	ContentsFontRenderer& operator=(ContentsFontRenderer&& _Other) noexcept = delete;

protected:
	void Start()override;
	void Update(float _DeltatTime)override;


private:
	int TypingCount_;

	float TypingTimer_;

	FontState FontState_;

	GameEngineFontRenderer* GameEngineFontRenderer_;

	GameEngineStateManager FontStateManager_;

public:
	void CreateFontRenderer(std::string _Text, float _FontSize, float4 _Position, bool _isTyping, int _LineBreak = 0);

	void SetActorToScreenPosition(float4 _ActorPos, float4 _CameraPos);

	void FontOn();

	void FontOff();
public:	
	//================================
	//    Bind State
	//================================
	void FontTypingStart(const StateInfo& _Info);
	void FontTypingUpdate(float _DeltaTime, const StateInfo& _Info);
	void FontTypingEnd(const StateInfo& _Info);

	void FontTypingIdleStart(const StateInfo& _Info);
	void FontTypingIdleUpdate(float _DeltaTime, const StateInfo& _Info);
	void FontTypingIdleEnd(const StateInfo& _Info);


	//================================
	//    Getter
	//================================

	//================================
	//    Setter
	//================================
	void SetTypingTextString(std::string _Text)
	{
		FontState_.Text_ = _Text;
		//GameEngineFontRenderer_->SetText(TypingText_, "Noto Serif KR");
	}

	void SetTypingTextSize(float _Size)
	{
		FontState_.FontSize_ = _Size;
		//GameEngineFontRenderer_->SetSize(_Size);
	}

};

