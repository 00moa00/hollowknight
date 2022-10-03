#include "PreCompile.h"
#include "HeartPiece.h"
#include "KnightData.h"

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

	FleurRenderer_(nullptr),
	MaskRenderer_(nullptr),
	FlashRenderer_(nullptr)
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
	FleurRenderer_->CreateFrameAnimationCutTexture("FLEUR_IDLE", FrameAnimation_DESC("Heart Piece UI Cln_HP_UI_Fleur_appear0000-Sheet.png", 6, 6, 0.100f, false));
	FleurRenderer_->ChangeFrameAnimation("FLEUR_APPEAR");

	FleurRenderer_->AnimationBindEnd("FLEUR_APPEAR", [=](const FrameAnimation_DESC& _Info)
		{
			isFleurAppeerEnd_ = true;
			FleurRenderer_->ChangeFrameAnimation("FLEUR_IDLE");
			//Alpha_ = 0.f;

			KnightData::GetInst()->AddMaskPieceCount();

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

	//MaskRenderer_->ChangeFrameAnimation("MASK_LEVEL1_APPEAR");

	FlashRenderer_ = CreateComponent<GameEngineUIRenderer>();
	FlashRenderer_->SetTexture("white_servant_death_flash0000-Sheet.png");
	//FlashRenderer_->SetScaleModeImage();
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

	Off();
}

void HeartPiece::Update(float _DeltaTime)
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

	if (isNewMask_ == true)
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
			// ÀÌµ¿
		}
	}

}

void HeartPiece::SetNewMaskPiece()
{
	On();

	Alpha_ = 0.f;

	FleurRenderer_->GetPixelData().MulColor.a = 1.0f;
	//MaskRenderer_->GetPixelData().MulColor.a = 1.0f;
	MaskRenderer_->GetPixelData().MulColor.a = 0.f;

	FleurRenderer_->ChangeFrameAnimation("FLEUR_APPEAR");

	ReSetAccTime();
	isNewMask_ = false;
}

