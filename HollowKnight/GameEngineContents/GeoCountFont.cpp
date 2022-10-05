#include "PreCompile.h"
#include "GeoCountFont.h"
#include "KnightData.h"
#include <sstream>

GeoCountFont::GeoCountFont() 
	:

	isPossibleCounting_(false),
	
	CurrentNum_(0),
	CountingNum_(0),
	PrevNum_(0),

	CountingTimer_(0.f),

	GameEngineFontRenderer_(nullptr)

{
}

GeoCountFont::~GeoCountFont() 
{
}

void GeoCountFont::Start()
{
	CountingTimer_ = 0.05f;


	FontStateManager_.CreateStateMember("COUNTUING_UPDATE"
		, std::bind(&GeoCountFont::FontCountingUpdate, this, std::placeholders::_1, std::placeholders::_2)
		, std::bind(&GeoCountFont::FontCountingStart, this, std::placeholders::_1)
		, std::bind(&GeoCountFont::FontCountingEnd, this, std::placeholders::_1));

	FontStateManager_.CreateStateMember("COUNTUING_IDLE"
		, std::bind(&GeoCountFont::FontIdleUpdate, this, std::placeholders::_1, std::placeholders::_2)
		, std::bind(&GeoCountFont::FontIdleStart, this, std::placeholders::_1)
		, std::bind(&GeoCountFont::FontIdleEnd, this, std::placeholders::_1));


	FontStateManager_.ChangeState("COUNTUING_IDLE");
}

void GeoCountFont::Update(float _DeltatTime)
{
	FontStateManager_.Update(_DeltatTime);
}

void GeoCountFont::LevelStartEvent()
{
	CurrentNum_ = KnightData::GetInst()->GetCurrentGeo();

	std::stringstream ssInt;
	ssInt << CurrentNum_;
	GameEngineFontRenderer_->SetText(ssInt.str(), "Noto Serif KR");
}

void GeoCountFont::LevelEndEvent()
{
	KnightData::GetInst()->SetCurrentGeo(CurrentNum_);


}


void GeoCountFont::CreateFontRenderer(int _Num, float _FontSize, float4 _Position)
{
	GameEngineFontRenderer_ = CreateComponent<GameEngineFontRenderer>();
	GameEngineFontRenderer_->ChangeCamera(CAMERAORDER::UICAMERA);

	GameEngineFontRenderer_->SetColor({ 1.0f, 1.0f, 1.0f });
	GameEngineFontRenderer_->SetScreenPostion(_Position);
	GameEngineFontRenderer_->SetSize(_FontSize);

	CurrentNum_ = _Num;

	std::stringstream ssInt;
	ssInt << _Num;
	GameEngineFontRenderer_->SetText(ssInt.str(), "Noto Serif KR");
}

void GeoCountFont::SetCountingFont(int _CoutingNum)
{
	if (isPossibleCounting_ == true)
	{
		PrevNum_ = CurrentNum_;
		CountingNum_ = _CoutingNum;
		FontStateManager_.ChangeState("COUNTUING_UPDATE");
	}
}

void GeoCountFont::FontCountingStart(const StateInfo& _Info)
{
	ReSetAccTime();
}

void GeoCountFont::FontCountingUpdate(float _DeltaTime, const StateInfo& _Info)
{
	if (GetAccTime() > CountingTimer_)
	{
		ReSetAccTime();
		++CurrentNum_;

		std::stringstream ssInt;
		ssInt << CurrentNum_;
		GameEngineFontRenderer_->SetText(ssInt.str(), "Noto Serif KR");


		if (CurrentNum_ >= PrevNum_ + CountingNum_)
		{
			CurrentNum_ = PrevNum_ + CountingNum_;


			std::stringstream ssInt;
			ssInt << CurrentNum_;
			GameEngineFontRenderer_->SetText(ssInt.str(), "Noto Serif KR");

			FontStateManager_.ChangeState("COUNTUING_IDLE");
			return;
		}
		
	}
}

void GeoCountFont::FontCountingEnd(const StateInfo& _Info)
{
	//PrevNum_ = 0;
	CountingNum_ = 0;
}

void GeoCountFont::FontIdleStart(const StateInfo& _Info)
{
}

void GeoCountFont::FontIdleUpdate(float _DeltaTime, const StateInfo& _Info)
{
}

void GeoCountFont::FontIdleEnd(const StateInfo& _Info)
{
}

