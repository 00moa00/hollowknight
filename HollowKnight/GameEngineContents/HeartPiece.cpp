#include "PreCompile.h"
#include "HeartPiece.h"
#include "KnightData.h"
#include "HollowKnightLevel.h"

HeartPiece::HeartPiece()
	:
	isNewMask_(false),
	isCompleteMask_(false),

	isLevel1End_(false),
	isLevel2End_(false),
	isLevel3End_(false),
	isLevel4End_(false),
	isFuseEnd_(false),

	isFleurAppeerEnd_(false),

	Alpha_(1.f),

	CompletAlpha_(0.0f),
	CompletScale_(1.0f),

	CompleteInitScale_(),


	FleurRenderer_(nullptr),
	MaskRenderer_(nullptr),
	FlashRenderer_(nullptr),
	CompleteMaskRenderer_(nullptr)
{
}

HeartPiece::~HeartPiece() 
{
}

void HeartPiece::Start()
{
	FleurRenderer_ = CreateComponent<GameEngineUIRenderer>();
	FleurRenderer_->SetTexture("Heart Piece UI Cln_HP_UI_Fleur_appear0000-Sheet.png");
	FleurRenderer_->GetTransform().SetLocalScale({753.f, 733.f});

	FleurRenderer_->CreateFrameAnimationCutTexture("FLEUR_APPEAR", FrameAnimation_DESC("Heart Piece UI Cln_HP_UI_Fleur_appear0000-Sheet.png", 0, 6, 0.100f,false));
	
	{
		std::vector<unsigned int>BackAni;

		for (int i = 6; i > -1; --i)
		{
			BackAni.push_back(i);
		}
		FleurRenderer_->CreateFrameAnimationCutTexture("DISAPPEAR_ANIMATION", FrameAnimation_DESC("Heart Piece UI Cln_HP_UI_Fleur_appear0000-Sheet.png", BackAni, 0.100f, false));
	}

	
	FleurRenderer_->CreateFrameAnimationCutTexture("FLEUR_IDLE", FrameAnimation_DESC("Heart Piece UI Cln_HP_UI_Fleur_appear0000-Sheet.png", 6, 6, 0.100f, false));
	FleurRenderer_->ChangeFrameAnimation("FLEUR_APPEAR");

	FleurRenderer_->AnimationBindEnd("FLEUR_APPEAR", [=](const FrameAnimation_DESC& _Info)
		{
			isFleurAppeerEnd_ = true;
			FleurRenderer_->ChangeFrameAnimation("FLEUR_IDLE");
			//Alpha_ = 0.f;

			KnightData::GetInst()->AddMaskPieceCount();

		});

	FleurRenderer_->AnimationBindEnd("DISAPPEAR_ANIMATION", [=](const FrameAnimation_DESC& _Info)
		{

			FleurRenderer_->Off();

		});

	MaskRenderer_ = CreateComponent<GameEngineUIRenderer>();
	MaskRenderer_->SetTexture("Heart_Piece.png");
	MaskRenderer_->SetScaleModeImage();
	MaskRenderer_->GetTransform().SetLocalScale({ 395.f, 537.f });


	MaskRenderer_->CreateFrameAnimationCutTexture("MASK_LEVEL1_APPEAR", FrameAnimation_DESC("Heart Piece UI Cln_HP_UI_010000-Sheet.png", 0, 4, 0.100f, false));
	MaskRenderer_->CreateFrameAnimationCutTexture("MASK_LEVEL2_APPEAR", FrameAnimation_DESC("Heart Piece UI Cln_HP_UI_020000-Sheet.png", 0, 4, 0.100f, false));
	MaskRenderer_->CreateFrameAnimationCutTexture("MASK_LEVEL3_APPEAR", FrameAnimation_DESC("Heart Piece UI Cln_HP_UI_030000-Sheet.png", 0, 4, 0.100f, false));
	MaskRenderer_->CreateFrameAnimationCutTexture("MASK_LEVEL4_APPEAR", FrameAnimation_DESC("Heart Piece UI Cln_HP_UI_040000-Sheet.png", 0, 4, 0.100f, false));
	MaskRenderer_->CreateFrameAnimationCutTexture("MASK_FUSE", FrameAnimation_DESC("Heart Piece UI Cln_HP_UI_fuse0000-Sheet.png", 0, 7, 0.100f, false));

	MaskRenderer_->CreateFrameAnimationCutTexture("MASK_MOVING", FrameAnimation_DESC("Heart Piece UI Cln_moving_health0000-Sheet.png", 0, 5, 0.100f, false));


	MaskRenderer_->AnimationBindEnd("MASK_LEVEL1_APPEAR", [=](const FrameAnimation_DESC& _Info)
		{
			isLevel1End_ = true;
		});

	MaskRenderer_->AnimationBindEnd("MASK_LEVEL2_APPEAR", [=](const FrameAnimation_DESC& _Info)
		{
			isLevel2End_ = true;
		});

	MaskRenderer_->AnimationBindEnd("MASK_LEVEL3_APPEAR", [=](const FrameAnimation_DESC& _Info)
		{
			isLevel3End_ = true;
		});

	MaskRenderer_->AnimationBindEnd("MASK_LEVEL4_APPEAR", [=](const FrameAnimation_DESC& _Info)
		{
			isLevel4End_ = true;
			MaskRenderer_->ChangeFrameAnimation("MASK_FUSE");

		});

	MaskRenderer_->AnimationBindEnd("MASK_FUSE", [=](const FrameAnimation_DESC& _Info)
		{
			isFuseEnd_ = true;
		});


	FlashRenderer_ = CreateComponent<GameEngineUIRenderer>();
	FlashRenderer_->SetTexture("white_servant_death_flash0000-Sheet.png");
	FlashRenderer_->GetTransform().SetLocalScale({ 300.f * 2.0f , 500.f * 3.f });

	FlashRenderer_->CreateFrameAnimationCutTexture("FLASH", FrameAnimation_DESC("white_servant_death_flash0000-Sheet.png", 0, 3, 0.05f, false));
	FlashRenderer_->CreateFrameAnimationCutTexture("IDLE", FrameAnimation_DESC("white_servant_death_flash0000-Sheet.png", 3, 3, 0.05f, false));

	FlashRenderer_->AnimationBindEnd("FLASH", [=](const FrameAnimation_DESC& _Info)
		{
			FlashRenderer_->ChangeFrameAnimation("IDLE");
			FlashRenderer_->Off();
		});

	
	FlashRenderer_->ChangeFrameAnimation("FLASH");
	FlashRenderer_->Off();
	FlashRenderer_->GetClonePipeLine()->SetOutputMergerBlend("AddBlend");



	CompleteMaskRenderer_ = CreateComponent<GameEngineUIRenderer>();
	CompleteMaskRenderer_->SetTexture("Heart Piece UI Cln_moving_health0000-Sheet.png", 0);
	CompleteMaskRenderer_->GetTransform().SetLocalScale({ 395.f * 1.3f, 537.f * 1.3f });

	CompleteInitScale_ = { 395.f * 1.3f, 537.f * 1.3f };
	CompleteMaskRenderer_->CreateFrameAnimationCutTexture("ANIMATION", FrameAnimation_DESC("Heart Piece UI Cln_moving_health0000-Sheet.png", 0, 5, 0.100f, true));
	CompleteMaskRenderer_->ChangeFrameAnimation("ANIMATION");
	CompleteMaskRenderer_->GetTransform().SetLocalPosition({0, -90.f});
	CompleteMaskRenderer_->Off();
	CompleteMaskRenderer_->GetClonePipeLine()->SetOutputMergerBlend("AddBlend");

	//================================
	//    Create State
	//================================

	HeartManager_.CreateStateMember("IDLE"
		, std::bind(&HeartPiece::HeartIdleUpdate, this, std::placeholders::_1, std::placeholders::_2)
		, std::bind(&HeartPiece::HeartIdleStart, this, std::placeholders::_1)
		, std::bind(&HeartPiece::HeartIdleEnd, this, std::placeholders::_1));

	HeartManager_.CreateStateMember("WHITE"
		, std::bind(&HeartPiece::HeartWhiteUpdate, this, std::placeholders::_1, std::placeholders::_2)
		, std::bind(&HeartPiece::HeartWhiteStart, this, std::placeholders::_1)
		, std::bind(&HeartPiece::HeartWhiteEnd, this, std::placeholders::_1));

	HeartManager_.CreateStateMember("MOVING"
		, std::bind(&HeartPiece::HeartMovingUpdate, this, std::placeholders::_1, std::placeholders::_2)
		, std::bind(&HeartPiece::HeartMovingStart, this, std::placeholders::_1)
		, std::bind(&HeartPiece::HeartMovingEnd, this, std::placeholders::_1));

	HeartManager_.CreateStateMember("NEW_MASK"
		, std::bind(&HeartPiece::HeartNewMaskUpdate, this, std::placeholders::_1, std::placeholders::_2)
		, std::bind(&HeartPiece::HeartNewMaskStart, this, std::placeholders::_1)
		, std::bind(&HeartPiece::HeartNewMaskEnd, this, std::placeholders::_1));

	HeartManager_.ChangeState("IDLE");

	Off();
}

void HeartPiece::Update(float _DeltaTime)
{

	HeartManager_.Update(_DeltaTime);



}

void HeartPiece::SetNewMaskPiece()
{
	On();
	FleurRenderer_->On();

	Alpha_ = 0.f;
	CompletScale_ = 1.0f;
	CompletAlpha_ = 0.0f;

	FleurRenderer_->GetPixelData().MulColor.a = 1.0f;
	MaskRenderer_->GetPixelData().MulColor.a = 0.f;

	FleurRenderer_->ChangeFrameAnimation("FLEUR_APPEAR");

	isNewMask_ = false;

	CompleteMaskRenderer_->Off();
	CompleteMaskRenderer_->GetTransform().SetLocalScale({ 395.f * 1.3f, 537.f * 1.3f });
	CompleteMaskRenderer_->GetPixelData().MulColor.a = 0.f;

	GetTransform().SetWorldPosition({0,0});

	ReSetAccTime();
}

void HeartPiece::HeartIdleStart(const StateInfo& _Info)
{
}

void HeartPiece::HeartIdleUpdate(float _DeltaTime, const StateInfo& _Info)
{
	if (isFleurAppeerEnd_ == true)
	{
		if (GetAccTime() > 1.0f)
		{

			isFleurAppeerEnd_ = false;

			FlashRenderer_->On();
			FlashRenderer_->ChangeFrameAnimation("FLASH");


			int Count = KnightData::GetInst()->GetMaskPieceCount();

			if (Count == 1)
			{
				MaskRenderer_->ChangeFrameAnimation("MASK_LEVEL1_APPEAR");
				isNewMask_ = true;
			}

			if (Count == 2)
			{
				MaskRenderer_->ChangeFrameAnimation("MASK_LEVEL2_APPEAR");
				isNewMask_ = true;
			}

			if (Count == 3)
			{
				MaskRenderer_->ChangeFrameAnimation("MASK_LEVEL3_APPEAR");
				isNewMask_ = true;
			}

			if (Count == 4)
			{
				MaskRenderer_->ChangeFrameAnimation("MASK_LEVEL4_APPEAR");
				isCompleteMask_ = true;
			}

			ReSetAccTime();
		}
	}

	if (isNewMask_ == false)
	{
		Alpha_ += 2.0f * _DeltaTime;

		if (Alpha_ >= 1.f)
		{
			Alpha_ = 1.f;

		}
		MaskRenderer_->GetPixelData().MulColor.a = Alpha_;
	}

	else if (isNewMask_ == true)
	{
		if (GetAccTime() > 2.f)
		{
			Alpha_ -= 0.7f * _DeltaTime;

			if (Alpha_ <= 0.f)
			{
				Alpha_ = 0.f;
				Off();
			}

			FleurRenderer_->GetPixelData().MulColor.a = Alpha_;
			MaskRenderer_->GetPixelData().MulColor.a = Alpha_;
		}
	}

	if (isCompleteMask_ == true)
	{
		if (isFuseEnd_ == true)
		{
			FleurRenderer_->ChangeFrameAnimation("DISAPPEAR_ANIMATION");
			HeartManager_.ChangeState("WHITE");

			// ÀÌµ¿
		}
	}
}

void HeartPiece::HeartIdleEnd(const StateInfo& _Info)
{

}

void HeartPiece::HeartWhiteStart(const StateInfo& _Info)
{
	CompletAlpha_ = 0.0f;
	CompleteMaskRenderer_->On();
	CompleteMaskRenderer_->GetPixelData().MulColor.a =0.f;


}
void HeartPiece::HeartWhiteUpdate(float _DeltaTime, const StateInfo& _Info)
{

	CompletAlpha_ += 0.8f * _DeltaTime;
	if (CompletAlpha_ >= 1.0f)
	{
		CompletAlpha_ = 1.0f;
		MaskRenderer_->Off();
		HeartManager_.ChangeState("MOVING");
	}

	CompleteMaskRenderer_->GetPixelData().MulColor.a = CompletAlpha_;
}
void HeartPiece::HeartWhiteEnd(const StateInfo& _Info)
{

}

void HeartPiece::HeartMovingStart(const StateInfo& _Info)
{

}
void HeartPiece::HeartMovingUpdate(float _DeltaTime, const StateInfo& _Info)
{
	float4 Dest = {-600, 500.f};
	float4 MyPos = GetTransform().GetWorldPosition();
	float4 Dir =  Dest - MyPos;

	Dir.Normalize();

	CompletScale_ -= 1.0f * _DeltaTime;

	if (CompletScale_ <= 0.3f)
	{
		CompletScale_ = 0.3f;
	}

	GetTransform().SetWorldMove(Dir * 1000.f * _DeltaTime);
	CompleteMaskRenderer_->GetTransform().SetLocalScale({ CompleteInitScale_.x * CompletScale_, CompleteInitScale_.y * CompletScale_ });


	if (Dir.Length() < 1000.f * _DeltaTime)
	{
		HeartManager_.ChangeState("NEW_MASK");
	}


}
void HeartPiece::HeartMovingEnd(const StateInfo& _Info)
{
	CompletScale_ = 1.0f;
}
void HeartPiece::HeartNewMaskStart(const StateInfo& _Info)
{
	GetLevel<HollowKnightLevel>()->GetHUD()->NewMask();
	KnightData::GetInst()->SetisAddNewMask(true);
}

void HeartPiece::HeartNewMaskUpdate(float _DeltaTime, const StateInfo& _Info)
{
}

void HeartPiece::HeartNewMaskEnd(const StateInfo& _Info)
{
}
