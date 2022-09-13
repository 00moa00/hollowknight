#include "PreCompile.h"
#include "KnihgtShadowSlashEffect.h"

KnihgtShadowSlashEffect::KnihgtShadowSlashEffect() 
{
}

KnihgtShadowSlashEffect::~KnihgtShadowSlashEffect() 
{
}

void KnihgtShadowSlashEffect::Start()
{
	CreateCollisionComponent(float4{ 140, 120, 10000 }, static_cast<int>(COLLISION_ORDER::Knight_Shadow_Slash));
	CreateRendererComponent(float4{ 431, 287, 1 }, "Hollow Shade Cln_slash_effect007-Sheet.png", 2, static_cast<int>(RENDERORDER::Knight));

	GetRenderer()->SetScaleModeImage();

	GetRenderer()->CreateFrameAnimationCutTexture("SLASH", FrameAnimation_DESC("Hollow Shade Cln_slash_effect007-Sheet.png", 0, 1, 0.100f, false));
	GetRenderer()->ChangeFrameAnimation("SLASH");

}

void KnihgtShadowSlashEffect::Update(float _DeltaTime)
{
}

