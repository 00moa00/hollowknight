#include "PreCompile.h"
#include "Tablet.h"
#include "GlobalContentsValue.h"

Tablet::Tablet() 
	:
	BackRenderer_(nullptr),
	LightRenderer_(nullptr),

	Collision_(nullptr),
	PromptSet_(nullptr)
{
}

Tablet::~Tablet() 
{
}

void Tablet::Start()
{
}

void Tablet::Update(float _DeltaTime)
{
}

void Tablet::CreateTablet(std::string _BackFilePath, std::string _LightFilePath, float4 _CollSize)
{
	BackRenderer_ = CreateComponent<GameEngineTextureRenderer>();
	BackRenderer_->SetTexture(_BackFilePath);
	BackRenderer_->GetTransform().SetLocalScale(BackRenderer_->GetCurTexture()->GetScale());
	BackRenderer_->SetPivot(PIVOTMODE::BOT);

	LightRenderer_ = CreateComponent<GameEngineTextureRenderer>();
	LightRenderer_->SetTexture(_LightFilePath);
	LightRenderer_->GetTransform().SetLocalScale(LightRenderer_->GetCurTexture()->GetScale());
	LightRenderer_->SetPivot(PIVOTMODE::BOT);

	Collision_ = CreateComponent<GameEngineCollision>();
	Collision_->GetTransform().SetLocalScale(_CollSize);
	Collision_->ChangeOrder(COLLISION_ORDER::Tablet);

}
