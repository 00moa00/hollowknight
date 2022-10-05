#include "PreCompile.h"
#include "ShopLampBug.h"

ShopLampBug::ShopLampBug() 
{
}

ShopLampBug::~ShopLampBug() 
{
}

void ShopLampBug::Start()
{
	CreateRendererComponent("shop_lamp_bug0000-Sheet.png");

	GetRenderer()->CreateFrameAnimationCutTexture("FLY", FrameAnimation_DESC("shop_lamp_bug0000-Sheet.png", 0, 7, 0.100f, true));
	//GetRenderer()->SetScaleModeImage();

	GetRenderer()->GetTransform().SetWorldScale({ 105.f * 1.2f /** 0.4f*/, 105.f * 1.2f/** 0.4f */});
	//GetRenderer()->GetTransform().SetWorldPosition({ 0, 105.f * 3 });

	GetRenderer()->ChangeFrameAnimation("FLY");
}

void ShopLampBug::Update(float _DeltaTime)
{
}

