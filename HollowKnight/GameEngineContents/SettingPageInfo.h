#pragma once
#include <GameEngineCore/CoreMinimal.h>
#include <GameEngineCore/GameEngineCollision.h>

#include "ContentsFontRenderer.h"
class GameEngineUIRenderer;
// 설명 : 아이템 설명
class SettingPageInfo : public GameEngineActor
{
public:
	// constrcuter destructer
	SettingPageInfo();
	~SettingPageInfo();

	// delete Function
	SettingPageInfo(const SettingPageInfo& _Other) = delete;
	SettingPageInfo(SettingPageInfo&& _Other) noexcept = delete;
	SettingPageInfo& operator=(const SettingPageInfo& _Other) = delete;
	SettingPageInfo& operator=(SettingPageInfo&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _DeltaTime) override;

	void SetInfoNameTexture(std::string Text);
	void SetInfoTexture(std::string Text);

private:
	GameEngineUIRenderer* InfoCharmImage_;

	ContentsFontRenderer* InfoName_;
	ContentsFontRenderer* Info_;

public:

	void SetFontMove();

	void SetInfo(std::string _Info, int _LineBreak)
	{
		Info_->SetText(_Info, _LineBreak);
	}

	void SetInfoName(std::string _Info)
	{
		InfoName_->SetText(_Info);
	}

	void SetInfoImage(std::string _FileName)
	{
		InfoCharmImage_->SetTexture(_FileName);
	}

};

