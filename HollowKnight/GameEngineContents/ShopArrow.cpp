#include "PreCompile.h"
#include "ShopArrow.h"

ShopArrow::ShopArrow() 
	:
	CurrentPointItemIndex_(0)

	, MoveTimer_(0)
	, TopArrowMove_(false)
	, BottomArrowMove_(false)
{
}

ShopArrow::~ShopArrow() 
{
}

void ShopArrow::Start()
{
	TopArrowRenderer_ = CreateComponent<GameEngineUIRenderer>();
	TopArrowRenderer_->SetTexture("shop_up_down_arrow.png");
	TopArrowRenderer_->GetTransform().SetLocalScale(TopArrowRenderer_->GetCurTexture()->GetScale() * 0.6f);
	TopArrowRenderer_->GetTransform().SetLocalPosition({0, 70});


	BottomArrowRenderer_ = CreateComponent<GameEngineUIRenderer>();
	BottomArrowRenderer_->SetTexture("shop_up_down_arrow.png");
	BottomArrowRenderer_->GetTransform().SetLocalScale(BottomArrowRenderer_->GetCurTexture()->GetScale() * 0.6f);
	BottomArrowRenderer_->GetTransform().SetLocalPosition({ 0, -70 });
	//BottomArrowRenderer_->GetTransform().SetWorldScale({ GetTransform().GetLocalScale().x, -(GetTransform().GetLocalScale().y) });

	PixLocalNegativeY(BottomArrowRenderer_);


	ArrowManager_.CreateStateMember("IDLE"
		, std::bind(&ShopArrow::ArrowIdleUpdate, this, std::placeholders::_1, std::placeholders::_2)
		, std::bind(&ShopArrow::ArrowIdleStart, this, std::placeholders::_1)
		, std::bind(&ShopArrow::ArrowIdleEnd, this, std::placeholders::_1));

	ArrowManager_.CreateStateMember("MOVE"
		, std::bind(&ShopArrow::ArrowMoveUpdate, this, std::placeholders::_1, std::placeholders::_2)
		, std::bind(&ShopArrow::ArrowMoveStart, this, std::placeholders::_1)
		, std::bind(&ShopArrow::ArrowMoveEnd, this, std::placeholders::_1));

	ArrowManager_.CreateStateMember("MOVE_RETURN"
		, std::bind(&ShopArrow::ArrowMoveReturnUpdate, this, std::placeholders::_1, std::placeholders::_2)
		, std::bind(&ShopArrow::ArrowMoveReturnStart, this, std::placeholders::_1)
		, std::bind(&ShopArrow::ArrowMoveReturnEnd, this, std::placeholders::_1));


	ArrowManager_.ChangeState("IDLE");

}

void ShopArrow::Update(float _DeltaTime)
{
	ArrowManager_.Update(_DeltaTime);
}

void ShopArrow::PixLocalNegativeY(GameEngineUIRenderer* _Renderer)
{
	_Renderer->GetTransform().SetLocalScale({ _Renderer->GetTransform().GetLocalScale().x, abs(_Renderer->GetTransform().GetLocalScale().y), 1 });
	if (0.0f > _Renderer->GetTransform().GetLocalScale().y)
	{
		return;
	}

	_Renderer->GetTransform().SetLocalScale({ _Renderer->GetTransform().GetLocalScale().x, -(_Renderer->GetTransform().GetLocalScale().y), 1 });
}

void ShopArrow::PixLocalPositiveY(GameEngineUIRenderer* _Renderer)
{
	if (0.0f < _Renderer->GetTransform().GetLocalScale().y)
	{
		return;
	}
}

void ShopArrow::ArrowIdleStart(const StateInfo& _Info)
{
}

void ShopArrow::ArrowIdleUpdate(float _DeltaTime, const StateInfo& _Info)
{
}

void ShopArrow::ArrowIdleEnd(const StateInfo& _Info)
{
}

void ShopArrow::ArrowMoveStart(const StateInfo& _Info)
{
}

void ShopArrow::ArrowMoveUpdate(float _DeltaTime, const StateInfo& _Info)
{
	MoveTimer_ += _DeltaTime;

	if (TopArrowMove_ == true)
	{
		float4 CurrentPos = TopArrowRenderer_->GetTransform().GetLocalPosition();
		float4 Move = float4::UP * 400.f * _DeltaTime;
		float4 DestPos = TopArrowRenderer_->GetTransform().GetLocalPosition() + Move;
		float4 LerpMove = float4::Lerp(CurrentPos, DestPos, GameEngineTime::GetDeltaTime() * 20.f);

		TopArrowRenderer_->GetTransform().SetLocalPosition(LerpMove);
	}

	if (BottomArrowMove_ == true)
	{
		float4 CurrentPos = BottomArrowRenderer_->GetTransform().GetLocalPosition();
		float4 Move = float4::DOWN * 400.f * _DeltaTime;
		float4 DestPos = BottomArrowRenderer_->GetTransform().GetLocalPosition() + Move;
		float4 LerpMove = float4::Lerp(CurrentPos, DestPos, GameEngineTime::GetDeltaTime() * 20.f);

		BottomArrowRenderer_->GetTransform().SetLocalPosition(LerpMove);
	}


	if (MoveTimer_ > 0.1f)
	{
		MoveTimer_ = 0.f;
		ArrowManager_.ChangeState("MOVE_RETURN");
	}
}

void ShopArrow::ArrowMoveEnd(const StateInfo& _Info)
{
}

void ShopArrow::ArrowMoveReturnStart(const StateInfo& _Info)
{
}

void ShopArrow::ArrowMoveReturnUpdate(float _DeltaTime, const StateInfo& _Info)
{
	MoveTimer_ += _DeltaTime;
	if (TopArrowMove_ == true)
	{

		float4 CurrentPos = TopArrowRenderer_->GetTransform().GetLocalPosition();
		float4 Move = float4::DOWN * 400.f * _DeltaTime;
		float4 DestPos = TopArrowRenderer_->GetTransform().GetLocalPosition() + Move;
		float4 LerpMove = float4::Lerp(CurrentPos, DestPos, GameEngineTime::GetDeltaTime() * 20.f);



		TopArrowRenderer_->GetTransform().SetLocalPosition(LerpMove);

		//TopArrowRenderer_->GetTransform().SetLocalMove(float4::DOWN * 400.f * _DeltaTime);
	}

	if (BottomArrowMove_ == true)
	{

		float4 CurrentPos = BottomArrowRenderer_->GetTransform().GetLocalPosition();
		float4 Move = float4::UP * 400.f * _DeltaTime;
		float4 DestPos = BottomArrowRenderer_->GetTransform().GetLocalPosition() + Move;
		float4 LerpMove = float4::Lerp(CurrentPos, DestPos, GameEngineTime::GetDeltaTime() * 20.f);



		BottomArrowRenderer_->GetTransform().SetLocalPosition(LerpMove);


	//	BottomArrowRenderer_->GetTransform().SetLocalMove(float4::UP * 400.f * _DeltaTime);
	}


	if (MoveTimer_ > 0.1f)
	{
		MoveTimer_ = 0.f;
		ArrowManager_.ChangeState("IDLE");

	}
}

void ShopArrow::ArrowMoveReturnEnd(const StateInfo& _Info)
{
	TopArrowMove_ = false;
	BottomArrowMove_ = false;

	TopArrowRenderer_->GetTransform().SetLocalPosition({ 0, 70 });
	BottomArrowRenderer_->GetTransform().SetLocalPosition({ 0, -70 });

}

