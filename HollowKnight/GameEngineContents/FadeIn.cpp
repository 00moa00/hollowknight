#include "PreCompile.h"
#include "FadeIn.h"

FadeIn::FadeIn() 
	:
	DeathFlag_(false),

	Renderer_(nullptr),
	Alpha_(1.0f)
{
}

FadeIn::~FadeIn() 
{
}

void FadeIn::Start()
{
	Renderer_ = CreateComponent<GameEngineUIRenderer>();
	Renderer_->SetTexture("BlackBoard.png");
	Renderer_->GetTransform().SetLocalScale(Renderer_->GetCurTexture()->GetScale());
	Renderer_->GetPixelData().MulColor.a = 1.0f;
	Renderer_->GetTransform().SetWorldPosition({ 0,0, -500 });
}

void FadeIn::Update(float _DeltaTime)
{
	Alpha_ -= 0.7f * _DeltaTime;

	Renderer_->GetPixelData().MulColor.a = Alpha_;


	if (Alpha_ <= 0.0f)
	{
		this->Death();
	}
}

