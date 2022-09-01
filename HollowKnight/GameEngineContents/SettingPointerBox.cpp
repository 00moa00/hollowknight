#include "PreCompile.h"
#include "SettingPointerBox.h"

SettingPointerBox::SettingPointerBox() 
	:
	ZommTimer_(0),

	BoxSize_(),

	LeftTopPointer_(nullptr),
	RightTopPointer_(nullptr),
	LeftBottomPointer_(nullptr),
	RightBottomPointer_(nullptr)
{
}

SettingPointerBox::~SettingPointerBox() 
{
}

void SettingPointerBox::Start()
{
	LeftTopPointer_ = CreateComponent<GameEngineUIRenderer>();
	LeftTopPointer_->SetTexture("InventoryPointer.png");
	LeftTopPointer_->ScaleToTexture();
	LeftTopPointer_->GetTransform().SetLocalPosition({ 0,0,static_cast<float>(Z_ORDER::UI_Border) });


	RightTopPointer_ = CreateComponent<GameEngineUIRenderer>();
	RightTopPointer_->SetTexture("InventoryPointer.png");
	RightTopPointer_->ScaleToTexture();
	RightTopPointer_->GetTransform().SetLocalPosition({ 0,0,static_cast<float>(Z_ORDER::UI_Border) });
	RightTopPointer_->GetTransform().PixLocalNegativeX();


	LeftBottomPointer_ = CreateComponent<GameEngineUIRenderer>();
	LeftBottomPointer_->SetTexture("InventoryPointer.png");
	LeftBottomPointer_->ScaleToTexture();
	LeftBottomPointer_->GetTransform().SetLocalScale({ GetTransform().GetLocalScale().x,-(GetTransform().GetLocalScale().y), 1 });
	SetPositiveY(LeftBottomPointer_);



	RightBottomPointer_ = CreateComponent<GameEngineUIRenderer>();
	RightBottomPointer_->SetTexture("InventoryPointer.png");
	RightBottomPointer_->ScaleToTexture();
	RightBottomPointer_->GetTransform().SetLocalScale({ GetTransform().GetLocalScale().x, -(GetTransform().GetLocalScale().y), 1 });
	SetPositiveY(RightBottomPointer_);
	RightBottomPointer_->GetTransform().PixLocalNegativeX();

	SettingPointerBoxtManager_.CreateStateMember("ZOOM_IN"
		, std::bind(&SettingPointerBox::PointerZoomInUpdate, this, std::placeholders::_1, std::placeholders::_2)
		, std::bind(&SettingPointerBox::PointerZoomInStart, this, std::placeholders::_1)
		, std::bind(&SettingPointerBox::PointerZoomInEnd, this, std::placeholders::_1));

	SettingPointerBoxtManager_.CreateStateMember("ZOOM_OUT"
		, std::bind(&SettingPointerBox::PointerZoomOutUpdate, this, std::placeholders::_1, std::placeholders::_2)
		, std::bind(&SettingPointerBox::PointerZoomOutStart, this, std::placeholders::_1)
		, std::bind(&SettingPointerBox::PointerZoomOutEnd, this, std::placeholders::_1));

		SettingPointerBoxtManager_.ChangeState("ZOOM_OUT");

}

void SettingPointerBox::Update(float _DeltaTime)
{
	SettingPointerBoxtManager_.Update(_DeltaTime);
}


void SettingPointerBox::PointerZoomInStart(const StateInfo& _Info)
{

}

void SettingPointerBox::PointerZoomInUpdate(float _DeltaTime, const StateInfo& _Info)
{
	LeftTopPointer_->GetTransform().SetLocalMove((float4::RIGHT + float4::DOWN) * 5.f * _DeltaTime);
	RightTopPointer_->GetTransform().SetLocalMove((float4::LEFT + float4::DOWN) * 5.f * _DeltaTime);
	LeftBottomPointer_->GetTransform().SetLocalMove((float4::RIGHT + float4::UP) * 5.f * _DeltaTime);
	RightBottomPointer_->GetTransform().SetLocalMove((float4::LEFT + float4::UP) * 5.f * _DeltaTime);


	ZommTimer_ += _DeltaTime;

	if (ZommTimer_ > 0.4f)
	{
		ZommTimer_ = 0.f;
		SettingPointerBoxtManager_.ChangeState("ZOOM_OUT");
	}

}

void SettingPointerBox::PointerZoomInEnd(const StateInfo& _Info)
{

}

void SettingPointerBox::PointerZoomOutStart(const StateInfo& _Info)
{

}

void SettingPointerBox::PointerZoomOutUpdate(float _DeltaTime, const StateInfo& _Info)
{
	LeftTopPointer_->GetTransform().SetLocalMove( (float4::LEFT + float4::UP) * 5.f *  _DeltaTime);
	RightTopPointer_->GetTransform().SetLocalMove((float4::RIGHT + float4::UP) * 5.f * _DeltaTime);
	LeftBottomPointer_->GetTransform().SetLocalMove((float4::LEFT + float4::DOWN) * 5.f * _DeltaTime);
	RightBottomPointer_->GetTransform().SetLocalMove((float4::RIGHT + float4::DOWN) * 5.f * _DeltaTime);

	ZommTimer_ += _DeltaTime;

	if (ZommTimer_ > 0.4f)
	{
		ZommTimer_ = 0.f;
		SettingPointerBoxtManager_.ChangeState("ZOOM_IN");
	}
}

void SettingPointerBox::PointerZoomOutEnd(const StateInfo& _Info)
{

}

void SettingPointerBox::SetPositiveY(GameEngineUIRenderer* _GameEngineUIRenderer)
{
	_GameEngineUIRenderer->GetTransform().SetLocalScale({ 60, abs(56.f), 1 });
	if (0.0f > _GameEngineUIRenderer->GetTransform().GetLocalScale().y)
	{
		return;
	}

	_GameEngineUIRenderer->GetTransform().SetLocalScale({ 60, -(56), 1 });

}

void SettingPointerBox::SetBoxSize(float4 _Size)
{
	LeftTopPointer_->GetTransform().SetLocalPosition({-_Size.x /2, +_Size.y/2, static_cast<float>(Z_ORDER::UI_Border) });
	RightTopPointer_->GetTransform().SetLocalPosition({ _Size.x/2, +_Size.y/2, static_cast<float>(Z_ORDER::UI_Border) });
	LeftBottomPointer_->GetTransform().SetLocalPosition({ -_Size.x/2, -_Size.y/2, static_cast<float>(Z_ORDER::UI_Border) });
	RightBottomPointer_->GetTransform().SetLocalPosition({ _Size.x/2, -_Size.y/2, static_cast<float>(Z_ORDER::UI_Border) });
}

void SettingPointerBox::AllPointerOn()
{
	LeftTopPointer_->On();
	RightTopPointer_->On();
	LeftBottomPointer_->On();
	RightBottomPointer_->On();
}

void SettingPointerBox::AllPointerOff()
{
	LeftTopPointer_->Off();
	RightTopPointer_->Off();
	LeftBottomPointer_->Off();
	RightBottomPointer_->Off();
}
