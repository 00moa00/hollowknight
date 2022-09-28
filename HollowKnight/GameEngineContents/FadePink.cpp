#include "PreCompile.h"
#include "FadePink.h"

FadePink::FadePink()
	:
	PinkRenderer_(nullptr),
	Alpha_(1.0f)
{
}

FadePink::~FadePink() 
{
}

void FadePink::Start()
{
	PinkRenderer_ = CreateComponent<GameEngineTextureRenderer>();
	PinkRenderer_->SetTexture("FadePink.png");
	PinkRenderer_->GetTransform().SetLocalScale(PinkRenderer_->GetCurTexture()->GetScale());
	PinkRenderer_->GetClonePipeLine()->SetOutputMergerBlend("LightenBlend");
	//PinkRenderer_->GetPixelData().MulColor.a = 0.f;

	PinkRenderer_->GetTransform().SetWorldPosition({ 0,0, -500 });

}

void FadePink::Update(float _DeltaTime)
{
	Alpha_ -= 1.0f * _DeltaTime;

	//PinkRenderer_->GetPixelData().MulColor.a = Alpha_;
	PinkRenderer_->GetPixelData().MulColor.r = Alpha_;
	PinkRenderer_->GetPixelData().MulColor.g = Alpha_;
	PinkRenderer_->GetPixelData().MulColor.b = Alpha_;

	if (Alpha_ <= 0.0f)
	{
		this->Death();
	}
}

