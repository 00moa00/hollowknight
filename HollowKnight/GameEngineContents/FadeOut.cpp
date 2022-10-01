#include "PreCompile.h"
#include "FadeOut.h"
#include "GlobalContentsValue.h"

FadeOut::FadeOut()
	:
	DeathFlag_(false),
	NoCountDeath_(false),
	Renderer_(nullptr),
	Alpha_(0.0f),
	FadeSpeed_(0.f)
{
}

FadeOut::~FadeOut() 
{
}

void FadeOut::Start()
{
	Renderer_ = CreateComponent<GameEngineUIRenderer>();
	Renderer_->SetTexture("BlackBoard.png");
	Renderer_->GetTransform().SetLocalScale(Renderer_->GetCurTexture()->GetScale());
	Renderer_->GetPixelData().MulColor.a = 0.0f;
	Renderer_->GetTransform().SetWorldPosition({0,0, -500});
	FadeSpeed_ = 1.1f;
}

void FadeOut::Update(float _DeltaTime)
{
	Alpha_ += FadeSpeed_ * _DeltaTime;

	Renderer_->GetPixelData().MulColor.a = Alpha_;


	if (Alpha_ >= 1.0f)
	{
		DeathFlag_ = true;

		if (NoCountDeath_ == true)
		{
			this->Death();
		}
		//this->Death();
	}
}

