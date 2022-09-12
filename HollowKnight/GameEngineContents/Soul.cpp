#include "PreCompile.h"
#include "Soul.h"

Soul::Soul() 
	:
	isGrowEnd_(false),
	isShrinkEnd_(false),

	SoulLevel_(4),

	SoulManager_()
{
}

Soul::~Soul() 
{
}

void Soul::Start()
{

	//CreateRendererComponent(float4{ 130, 125, 1 }, "HUD_Soulorb_fills_soul_idle0000-Sheet.png", 0, static_cast<int>(RENDERORDER::UI));

	EyeRenderer_ = CreateComponent<GameEngineUIRenderer>();
	EyeRenderer_->SetTexture("HUD Cln_soul_orb_eyes.png");
	EyeRenderer_->GetTransform().SetLocalScale({ 87, 33, 1 });
	EyeRenderer_->GetTransform().SetWorldPosition({65.f, -87.f, 1});


	GameEngineUIRenderer *GameEngineUIRenderer_ = CreateComponent<GameEngineUIRenderer>();
	GameEngineUIRenderer_->SetTexture("HUD Cln_soul_orb_shape.png");
	GameEngineUIRenderer_->Off();


	Soul_ = CreateComponent<MaskRenderer>();
	Soul_->SetTexture("HUD Cln_soul_orb_eyes.png");
	Soul_->GetTransform().SetLocalScale({ 130, 125, 1 });

	//Soul_->Option.IsMask = 1;
	Soul_->ShaderResources.SetTexture("Test", GameEngineUIRenderer_->GetCurTexture());

	//Soul_->SetSamplingModePoint();

	//================================
	//    Create Animation
	//================================
	Soul_->CreateFrameAnimationCutTexture("IDLE_ANIMATION", FrameAnimation_DESC("HUD_Soulorb_fills_soul_idle0000-Sheet.png", 0, 5, 0.150f));
	Soul_->CreateFrameAnimationCutTexture("GROW_ANIMATION", FrameAnimation_DESC("HUD_Soulorb_fills_soul_grow0000-Sheet.png", 0, 7, 0.100f, false));
	Soul_->CreateFrameAnimationCutTexture("SHRINK_ANIMATION", FrameAnimation_DESC("HUD_Soulorb_fills_soul_shrink0000-Sheet.png", 0, 5, 0.100f, false));
	Soul_->CreateFrameAnimationCutTexture("FULL_ANIMATION", FrameAnimation_DESC("HUD Cln_soul_orb_glow0000.png", 0, 0, 0.100f, false));

	Soul_->SetScaleModeImage();

	Soul_->ChangeFrameAnimation("IDLE_ANIMATION");
	Soul_->SetPivot(PIVOTMODE::LEFTTOP);
	//Soul_->GetPixelData().MulColor = {1,1,1,0.5f};
	

	//Soul_->GetTransformData().
	
	// 
	//================================
	//    Create Bind Animation
	//================================
	Soul_->AnimationBindEnd("GROW_ANIMATION", [=](const FrameAnimation_DESC& _Info)
		{
			isGrowEnd_ = true;
		});

	Soul_->AnimationBindEnd("SHRINK_ANIMATION", [=](const FrameAnimation_DESC& _Info)
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

	SoulLevel_ = 4;
}

void Soul::Update(float _DeltaTime)
{
	SoulManager_.Update(_DeltaTime);
}

void Soul::SetSoul(int _Level)
{

	SoulLevel_ = _Level;
	SetLevelPosition(SoulLevel_);

}

void Soul::SetLevelPosition(int _Level)
{
	switch (_Level)
	{
	case 0:
		Soul_->GetUVData().OffsetY = -0.9f;

		break;

	case 1:
		Soul_->GetUVData().OffsetY = -0.8f;
		break;

	case 2:
		Soul_->GetUVData().OffsetY = -0.7f;

		break;

	case 3:
		Soul_->GetUVData().OffsetY = -0.6f;

		break;

	case 4:
		Soul_->GetUVData().OffsetY = -0.5f;

		break;

	case 5:
		Soul_->GetUVData().OffsetY = -0.4f;

		break;

	case 6:
		Soul_->GetUVData().OffsetY = -0.3f;

		break;

	case 7:
		Soul_->GetUVData().OffsetY = -0.2f;

		break;

	case 8 : 

		Soul_->GetUVData().OffsetY = -0.1f;

		break;
	case 9:

		Soul_->GetUVData().OffsetY = -0.f;

		break;
	default:
		break;
	}
}

void Soul::SoulGrowStart(const StateInfo& _Info)
{
	SetLevelPosition(SoulLevel_);
	Soul_->ChangeFrameAnimation("GROW_ANIMATION");
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
		Soul_->ChangeFrameAnimation("FULL_ANIMATION");
	}
	else
	{
		EyeRenderer_->Off();

		Soul_->ChangeFrameAnimation("IDLE_ANIMATION");
	}
}

void Soul::SoulIdleUpdate(float _DeltaTime, const StateInfo& _Info)
{
	SetLevelPosition(4);
}

void Soul::SoulIdleEnd(const StateInfo& _Info)
{
}

void Soul::SoulShrinkStart(const StateInfo& _Info)
{
	Soul_->ChangeFrameAnimation("SHRINK_ANIMATION");

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
