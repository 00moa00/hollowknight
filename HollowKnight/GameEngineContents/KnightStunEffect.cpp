#include "PreCompile.h"
#include "KnightStunEffect.h"

KnightStunEffect::KnightStunEffect() 
{
}

KnightStunEffect::~KnightStunEffect() 
{
}

void KnightStunEffect::Start()
{
	CreateRendererComponent( "hit_crack_simple0000-Sheet.png");
	GetRenderer()->GetTransform().SetWorldPosition({ 0, 0, 0 });
	GetRenderer()->SetScaleModeImage();

}

void KnightStunEffect::Update(float _DeltaTime)
{
}

