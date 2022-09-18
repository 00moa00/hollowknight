#include "PreCompile.h"
#include "Tablet.h"
#include "GlobalContentsValue.h"

Tablet::Tablet() 
	:
	Alpha_(0.0f),

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
	TabletManager_.CreateStateMember("IDLE"
		, std::bind(&Tablet::TabletIdleUpdate, this, std::placeholders::_1, std::placeholders::_2)
		, std::bind(&Tablet::TabletIdleStart, this, std::placeholders::_1)
		, std::bind(&Tablet::TabletIdleEnd, this, std::placeholders::_1));

	TabletManager_.CreateStateMember("APPEAR"
		, std::bind(&Tablet::TabletAppearUpdate, this, std::placeholders::_1, std::placeholders::_2)
		, std::bind(&Tablet::TabletAppearStart, this, std::placeholders::_1)
		, std::bind(&Tablet::TabletAppearEnd, this, std::placeholders::_1));

	TabletManager_.ChangeState("IDLE");

}

void Tablet::Update(float _DeltaTime)
{
	TabletManager_.Update(_DeltaTime);
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
	LightRenderer_->GetPixelData().MulColor.a = 0.0f;

	LightRenderer_->Off();

	Collision_ = CreateComponent<GameEngineCollision>();
	Collision_->GetTransform().SetLocalScale(_CollSize);
	Collision_->ChangeOrder(COLLISION_ORDER::Tablet);

	PromptSet_ = GetLevel()->CreateActor<PromptSet>();
	PromptSet_->CreatePrompSet(PromptSetType::SEARCH);
	PromptSet_->SetParent(this);
	PromptSet_->GetTransform().SetLocalPosition({0, 350});
	PromptSet_->GetCollision()->GetTransform().SetLocalPosition({0, -350});
}

void Tablet::TabletIdleStart(const StateInfo& _Info)
{
}

void Tablet::TabletIdleUpdate(float _DeltaTime, const StateInfo& _Info)
{
	Alpha_ -= _DeltaTime * 0.7f;
	LightRenderer_->GetPixelData().MulColor.a = Alpha_;

	if (Alpha_ <= 0.0f)
	{
		Alpha_ = 0.0f;
	}

	if (Collision_->IsCollision(CollisionType::CT_OBB2D, COLLISION_ORDER::Knight, CollisionType::CT_OBB2D,
		std::bind(&Tablet::TabletVSKnightCollision, this, std::placeholders::_1, std::placeholders::_2)) == true
		)
	{
		TabletManager_.ChangeState("APPEAR");
		return;
	}
}

void Tablet::TabletIdleEnd(const StateInfo& _Info)
{
}

void Tablet::TabletAppearStart(const StateInfo& _Info)
{
	LightRenderer_->On();
}

void Tablet::TabletAppearUpdate(float _DeltaTime, const StateInfo& _Info)
{
	Alpha_ += _DeltaTime * 0.7f;
	LightRenderer_->GetPixelData().MulColor.a = Alpha_;

	if (Alpha_ >= 1.0f)
	{
		Alpha_ = 1.0f;
	}

	if (Collision_->IsCollision(CollisionType::CT_OBB2D, COLLISION_ORDER::Knight, CollisionType::CT_OBB2D,
		std::bind(&Tablet::TabletVSKnightCollision, this, std::placeholders::_1, std::placeholders::_2)) == false
		)
	{
		TabletManager_.ChangeState("IDLE");
		return;
	}


}

void Tablet::TabletAppearEnd(const StateInfo& _Info)
{
	//Alpha_ = 1.0f;
}

bool Tablet::TabletVSKnightCollision(GameEngineCollision* _This, GameEngineCollision* _Other)
{
	return true;
}
