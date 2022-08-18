#include "PreCompile.h"
#include "Soul.h"

Soul::Soul() 
	:
	isGrowEnd_(false),
	isShrinkEnd_(false),

	SoulLevel_(0),

	SoulManager_()
{
}

Soul::~Soul() 
{
}

void Soul::Start()
{

	CreateRendererComponent(float4{ 130, 125, 1 }, "HUD_Soulorb_fills_soul_idle0000-Sheet.png", 0, static_cast<int>(RENDERORDER::UI));

	EyeRenderer_ = CreateComponent<GameEngineUIRenderer>();
	EyeRenderer_->SetTexture("HUD Cln_soul_orb_eyes.png");
	EyeRenderer_->GetTransform().SetLocalScale({ 87, 33, 1 });
	EyeRenderer_->GetTransform().SetWorldPosition({65.f, -87.f, 1});


	GameEngineUIRenderer *GameEngineUIRenderer_ = CreateComponent<GameEngineUIRenderer>();
	GameEngineUIRenderer_->SetTexture("HUD Cln_soul_orb_shape.png");
	//GameEngineUIRenderer_->GetTransform().SetLocalScale({ 124, 124, 1 });
	//GameEngineUIRenderer_->GetTransform().SetWorldPosition({ 65.f, -87.f, 1 });
	GameEngineUIRenderer_->Off();
	//GameEngineUIRenderer_->SetSamplingModePoint();
	GetRenderer()->Option.IsMask = 1;
	GetRenderer()->ShaderResources.SetTexture("Test", GameEngineUIRenderer_->GetCurTexture());
	//GetRenderer()->SetSamplingModePoint();

	//================================
	//    Create Animation
	//================================
	GetRenderer()->CreateFrameAnimationCutTexture("IDLE_ANIMATION", FrameAnimation_DESC("HUD_Soulorb_fills_soul_idle0000-Sheet.png", 0, 5, 0.150f));
	GetRenderer()->CreateFrameAnimationCutTexture("GROW_ANIMATION", FrameAnimation_DESC("HUD_Soulorb_fills_soul_grow0000-Sheet.png", 0, 7, 0.100f, false));
	GetRenderer()->CreateFrameAnimationCutTexture("SHRINK_ANIMATION", FrameAnimation_DESC("HUD_Soulorb_fills_soul_shrink0000-Sheet.png", 0, 5, 0.100f, false));
	GetRenderer()->CreateFrameAnimationCutTexture("FULL_ANIMATION", FrameAnimation_DESC("HUD Cln_soul_orb_glow0000.png", 0, 0, 0.100f, false));

	GetRenderer()->SetScaleModeImage();

	GetRenderer()->ChangeFrameAnimation("IDLE_ANIMATION");
	GetRenderer()->SetPivot(PIVOTMODE::LEFTTOP);
	GetRenderer()->GetColorData().MulColor = {1,1,1,0.5f};
	

	//GetRenderer()->GetTransformData().
	
	// 
	//================================
	//    Create Bind Animation
	//================================
	GetRenderer()->AnimationBindEnd("GROW_ANIMATION", [=](const FrameAnimation_DESC& _Info)
		{
			isGrowEnd_ = true;
		});

	GetRenderer()->AnimationBindEnd("SHRINK_ANIMATION", [=](const FrameAnimation_DESC& _Info)
		{
			isShrinkEnd_ = true;
		});

	//================================
	//    Create State
	//================================
	SoulManager_.CreateStateMember("GROW",
		std::bind(&Soul::SoulGrowUpdate, this, std::placeholders::_1, std::placeholders::_2),
		std::bind(&Soul::SoulGrowStart, this, std::placeholders::_1),
		std::bind(&Soul::SoulGrowEnd, this, std::placeholders::_1));

	SoulManager_.CreateStateMember("IDLE",
		std::bind(&Soul::SoulIdleUpdate, this, std::placeholders::_1, std::placeholders::_2),
		std::bind(&Soul::SoulIdleStart, this, std::placeholders::_1),
		std::bind(&Soul::SoulIdleEnd, this, std::placeholders::_1));

	SoulManager_.CreateStateMember("SHRINK",
		std::bind(&Soul::SoulShrinkUpdate, this, std::placeholders::_1, std::placeholders::_2),
		std::bind(&Soul::SoulShrinkStart, this, std::placeholders::_1),
		std::bind(&Soul::SoulShrinkEnd, this, std::placeholders::_1));

	SoulManager_.ChangeState("IDLE");

	GetTransform().SetLocalPosition({ -(GameEngineWindow::GetInst()->GetScale().hx() - 80.f),
	GameEngineWindow::GetInst()->GetScale().hy() - 87.f, -100 });
}

void Soul::Update(float _DeltaTime)
{
	SoulManager_.Update(_DeltaTime);
}

void Soul::SetLevelPosition(int _Level)
{
	switch (_Level)
	{
	case 0:
		GetRenderer()->GetUVData().OffsetY = -0.9f;

		break;

	case 1:
		GetRenderer()->GetUVData().OffsetY = -0.8f;
		break;

	case 2:
		GetRenderer()->GetUVData().OffsetY = -0.7f;

		break;

	case 3:
		GetRenderer()->GetUVData().OffsetY = -0.6f;

		break;

	case 4:
		GetRenderer()->GetUVData().OffsetY = -0.5f;

		break;

	case 5:
		GetRenderer()->GetUVData().OffsetY = -0.4f;

		break;

	case 6:
		GetRenderer()->GetUVData().OffsetY = -0.3f;

		break;

	case 7:
		GetRenderer()->GetUVData().OffsetY = -0.2f;

		break;

	case 8 : 

		GetRenderer()->GetUVData().OffsetY = -0.1f;

		break;
	case 9:

		GetRenderer()->GetUVData().OffsetY = -0.f;

		break;
	default:
		break;
	}
}

void Soul::SoulGrowStart(const StateInfo& _Info)
{
	SetLevelPosition(SoulLevel_);
	GetRenderer()->ChangeFrameAnimation("GROW_ANIMATION");
}

void Soul::SoulGrowUpdate(float _DeltaTime, const StateInfo& _Info)
{

	if (isGrowEnd_ == true)
	{
		isGrowEnd_ = false;
		SoulManager_.ChangeState("IDLE");
	}
}

void Soul::SoulGrowEnd(const StateInfo& _Info)
{
}

void Soul::SoulIdleStart(const StateInfo& _Info)
{
	if (SoulLevel_ == 9)
	{
		EyeRenderer_->On();
		GetRenderer()->ChangeFrameAnimation("FULL_ANIMATION");
	}
	else
	{
		EyeRenderer_->Off();

		GetRenderer()->ChangeFrameAnimation("IDLE_ANIMATION");
	}
}

void Soul::SoulIdleUpdate(float _DeltaTime, const StateInfo& _Info)
{
	SetLevelPosition(SoulLevel_);
}

void Soul::SoulIdleEnd(const StateInfo& _Info)
{
}

void Soul::SoulShrinkStart(const StateInfo& _Info)
{
	GetRenderer()->ChangeFrameAnimation("SHRINK_ANIMATION");

}

void Soul::SoulShrinkUpdate(float _DeltaTime, const StateInfo& _Info)
{
	if (isShrinkEnd_ == true)
	{
		isShrinkEnd_ = true;
		SoulManager_.ChangeState("IDLE");
	}
}

void Soul::SoulShrinkEnd(const StateInfo& _Info)
{
}
