#include "PreCompile.h"
#include "ShopArrow.h"

ShopArrow::ShopArrow() 
	:
	CurrentPointItemIndex_(0)
{
}

ShopArrow::~ShopArrow() 
{
}

void ShopArrow::Start()
{
	TopArrowRenderer_ = CreateComponent<GameEngineUIRenderer>();
	TopArrowRenderer_->SetTexture("shop_up_down_arrow.png");
	TopArrowRenderer_->GetTransform().SetLocalScale(TopArrowRenderer_->GetCurTexture()->GetScale());
	TopArrowRenderer_->GetTransform().SetLocalPosition({0, 70});


	BottomArrowRenderer_ = CreateComponent<GameEngineUIRenderer>();
	BottomArrowRenderer_->SetTexture("shop_up_down_arrow.png");
	BottomArrowRenderer_->GetTransform().SetLocalScale(BottomArrowRenderer_->GetCurTexture()->GetScale());
	BottomArrowRenderer_->GetTransform().SetLocalPosition({ 0, -70 });
	//BottomArrowRenderer_->GetTransform().SetWorldScale({ GetTransform().GetLocalScale().x, -(GetTransform().GetLocalScale().y) });

	PixLocalNegativeY(BottomArrowRenderer_);


}

void ShopArrow::Update(float _DeltaTime)
{
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

