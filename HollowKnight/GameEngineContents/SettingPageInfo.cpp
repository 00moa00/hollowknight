#include "PreCompile.h"
#include "SettingPageInfo.h"

SettingPageInfo::SettingPageInfo() 
{
}

SettingPageInfo::~SettingPageInfo() 
{
}

void SettingPageInfo::Start()
{

	InfoCharmImage_ = CreateComponent<GameEngineUIRenderer>();
	InfoCharmImage_->SetTexture("glass_charm_shattered_UI.png");
	InfoCharmImage_->GetTransform().SetLocalScale({0, 0});


	InfoName_ = GetLevel()->CreateActor<ContentsFontRenderer>();
	InfoName_->CreateFontRenderer("테스트 "
		, 40
		, { 200.f, (GameEngineWindow::GetInst()->GetScale().hy() - 300.0f), static_cast<float>(Z_ORDER::UI) }
	, false);
	InfoName_->GetTransform().SetWorldPosition({ 500, 300, static_cast<float>(Z_ORDER::UI) });
	InfoName_->SetScreenMove();
	InfoName_->SetParent(this);


	Info_ = GetLevel()->CreateActor<ContentsFontRenderer>();
	Info_->CreateFontRenderer("테스트 "
		, 40
		, { 200.f, (GameEngineWindow::GetInst()->GetScale().hy() - 300.0f), static_cast<float>(Z_ORDER::UI) }
	, false);
	Info_->GetTransform().SetWorldPosition({ 500, 0, static_cast<float>(Z_ORDER::UI) });
	Info_->SetScreenMove();
	Info_->SetParent(this);

}

void SettingPageInfo::Update(float _DeltaTime)
{
}

void SettingPageInfo::SetInfoNameTexture(std::string Text)
{
}

void SettingPageInfo::SetInfoTexture(std::string Text)
{
}

void SettingPageInfo::SetFontMove()
{
	InfoName_->SetScreenMove();
	Info_->SetScreenMove();

}

