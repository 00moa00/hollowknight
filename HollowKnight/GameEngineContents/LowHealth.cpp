#include "PreCompile.h"
#include "LowHealth.h"

LowHealth::LowHealth() 
	:
	MaxScale_(),
	MinScale_(),

	ScaleTimer_(0),

	vignette_(nullptr),

	LowHealthManager_()
{
}

LowHealth::~LowHealth() 
{
}

void LowHealth::Start()
{
	vignette_ = CreateComponent<GameEngineUIRenderer>();
	vignette_->SetTexture("vignette_low_health2.png");
	vignette_->GetTransform().SetWorldScale({1920 * 1.4f,1080 * 1.4f });
	vignette_->ChangeCamera(CAMERAORDER::UICAMERA);
	//vignette_->SetWro
	//vignette_->GetTransform().SetWorldScale({});
	//vignette_->GetPixelData().MulColor.a = 0.5f;

	//MinScale_ = vignette_->GetTransform().GetWorldScale();
	//MaxScale_ = vignette_->GetTransform().GetWorldScale();

	LowHealthManager_.CreateStateMember("ADD_SCALE"
		, std::bind(&LowHealth::AddScaleUpdate, this, std::placeholders::_1, std::placeholders::_2)
		, std::bind(&LowHealth::AddScaleStart, this, std::placeholders::_1)
		, std::bind(&LowHealth::AddScaleEnd, this, std::placeholders::_1));

	LowHealthManager_.CreateStateMember("SUB_SCALE"
		, std::bind(&LowHealth::SubScaleUpdate, this, std::placeholders::_1, std::placeholders::_2)
		, std::bind(&LowHealth::SubScaleStart, this, std::placeholders::_1)
		, std::bind(&LowHealth::SubScaleEnd, this, std::placeholders::_1));


	LowHealthManager_.ChangeState("ADD_SCALE");

	//SetLevelOverOn();

}

void LowHealth::Update(float _DeltaTime)
{
	LowHealthManager_.Update(_DeltaTime);
}

void LowHealth::AddScaleStart(const StateInfo& _Info)
{
	MaxScale_ += 70.f;
}

void LowHealth::AddScaleUpdate(float _DeltaTime, const StateInfo& _Info)
{

	ScaleTimer_ += _DeltaTime;

	if (ScaleTimer_ > 1.f)
	{

		ScaleTimer_ = 0.f;
		LowHealthManager_.ChangeState("SUB_SCALE");
	}

	//float4 AddScale;
	//AddScale += 300.f * _DeltaTime;

	vignette_->GetTransform().SetWorldScale( vignette_ ->GetTransform().GetWorldScale() + (MaxScale_ * _DeltaTime * 12.f));
//	vignette_->GetTransform().SetWorldPosition({0,0, 100});
}

void LowHealth::AddScaleEnd(const StateInfo& _Info)
{
}

void LowHealth::SubScaleStart(const StateInfo& _Info)
{
	MinScale_ = -20.f;

}

void LowHealth::SubScaleUpdate(float _DeltaTime, const StateInfo& _Info)
{
	ScaleTimer_ += _DeltaTime;

	if (ScaleTimer_ > 1.f)
	{
		ScaleTimer_ = 0.f;
		LowHealthManager_.ChangeState("ADD_SCALE");

	}

	//float4 SubScale;
	//SubScale -= 300.f * _DeltaTime;

	vignette_->GetTransform().SetWorldScale(vignette_->GetTransform().GetWorldScale() + (MinScale_ * _DeltaTime * 12.f));

}

void LowHealth::SubScaleEnd(const StateInfo& _Info)
{

}

  