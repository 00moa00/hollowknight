#include "PreCompile.h"
#include "MonsterHitEffect.h"

MonsterHitEffect::MonsterHitEffect() 
	:
	SacleY(0)
{
}

MonsterHitEffect::~MonsterHitEffect() 
{
}

void MonsterHitEffect::Start()
{

	LeftTop1Renderer = CreateComponent<GameEngineTextureRenderer>();
	LeftTop1Renderer->SetTexture("Stun_Effect_Particle2.png");
	LeftTop1Renderer->GetTransform().SetLocalScale({ 146 * 1.5, 40 * 1.5 });
	PixLocalNegativeY(LeftTop1Renderer);
	LeftTop1Renderer->GetTransform().PixLocalNegativeX();
	LeftTop1Renderer->GetTransform().SetWorldRotation({0,0,-30});

	LeftTop1Renderer->SetPivot(PIVOTMODE::CUSTOM);
	LeftTop1Renderer->GetAtlasData().PivotPos = float4(0.4f, -0.5f, 0.0f, 0.0f);


	LeftTop2Renderer = CreateComponent<GameEngineTextureRenderer>();
	LeftTop2Renderer->SetTexture("Stun_Effect_Particle1.png");
	LeftTop2Renderer->GetTransform().SetLocalScale({ 144 * 1.5, 29 * 1.5 });
	PixLocalNegativeY(LeftTop2Renderer);
	LeftTop2Renderer->GetTransform().PixLocalNegativeX();
	LeftTop2Renderer->GetTransform().SetWorldRotation({ 0,0,-20 });

	LeftTop2Renderer->SetPivot(PIVOTMODE::CUSTOM);
	LeftTop2Renderer->GetAtlasData().PivotPos = float4(0.4f,  -0.5f, 0.0f, 0.0f);



	RightTop1Renderer = CreateComponent<GameEngineTextureRenderer>();
	RightTop1Renderer->SetTexture("Stun_Effect_Particle2.png");
	RightTop1Renderer->GetTransform().SetLocalScale({ 146 * 1.5, 40 * 1.5 });

	RightTop1Renderer->SetPivot(PIVOTMODE::CUSTOM);
	RightTop1Renderer->GetAtlasData().PivotPos = float4(0.3f, 0.5f, 0.0f, 0.0f);


	RightTop2Renderer = CreateComponent<GameEngineTextureRenderer>();
	RightTop2Renderer->SetTexture("Stun_Effect_Particle2.png");
	RightTop2Renderer->GetTransform().SetLocalScale({ 146 * 1.5, 40 * 1.5 });
	RightTop2Renderer->GetTransform().SetWorldRotation({ 0,0,10 });

	RightTop2Renderer->SetPivot(PIVOTMODE::CUSTOM);
	RightTop2Renderer->GetAtlasData().PivotPos = float4(0.3f, 0.5f, 0.0f, 0.0f);



	LeftBottom1Renderer = CreateComponent<GameEngineTextureRenderer>();
	LeftBottom1Renderer->SetTexture("Stun_Effect_Particle2.png");
	LeftBottom1Renderer->GetTransform().SetLocalScale({ 146 * 1.5, 40 * 1.5 });
	LeftBottom1Renderer->GetTransform().SetWorldRotation({ 0,0,10 });
	LeftBottom1Renderer->GetTransform().PixLocalNegativeX();

	LeftBottom1Renderer->SetPivot(PIVOTMODE::CUSTOM);
	LeftBottom1Renderer->GetAtlasData().PivotPos = float4(0.3f, 0.5f, 0.0f, 0.0f);

	LeftBottom2Renderer = CreateComponent<GameEngineTextureRenderer>();
	LeftBottom2Renderer->SetTexture("Stun_Effect_Particle2.png");
	LeftBottom2Renderer->GetTransform().SetLocalScale({ 146 * 1.5, 40 * 1.5 });
	LeftBottom2Renderer->GetTransform().SetWorldRotation({ 0,0,30 });
	LeftBottom2Renderer->GetTransform().PixLocalNegativeX();

	LeftBottom2Renderer->SetPivot(PIVOTMODE::CUSTOM);
	LeftBottom2Renderer->GetAtlasData().PivotPos = float4(0.3f, 0.5f, 0.0f, 0.0f);


	RightBottom1Renderer = CreateComponent<GameEngineTextureRenderer>();
	RightBottom1Renderer->SetTexture("Stun_Effect_Particle2.png");
	RightBottom1Renderer->GetTransform().SetLocalScale({ 146 * 1.5, 40 * 1.5 });
	RightBottom1Renderer->GetTransform().SetWorldRotation({ 0,0, -40 });

	RightBottom1Renderer->SetPivot(PIVOTMODE::CUSTOM);
	RightBottom1Renderer->GetAtlasData().PivotPos = float4(0.2f, 0.25f, 0.0f, 0.0f);


	RightBottom2Renderer = CreateComponent<GameEngineTextureRenderer>();
	RightBottom2Renderer->SetTexture("Stun_Effect_Particle1.png");
	RightBottom2Renderer->GetTransform().SetLocalScale({ 144 * 1.5, 29 * 1.5 });
	RightBottom2Renderer->GetTransform().SetWorldRotation({ 0,0, -30 });

	RightBottom2Renderer->SetPivot(PIVOTMODE::CUSTOM);
	RightBottom2Renderer->GetAtlasData().PivotPos = float4(0.18f, 0.4f, 0.0f, 0.0f);

}

void MonsterHitEffect::Update(float _DeltaTime)
{
	SacleY += 100.f * _DeltaTime;
	float4 MoveLeftTop = float4{ -1.0f, 0.3f };


	LeftTop1Renderer->GetTransform().SetWorldMove(MoveLeftTop * 1300.f *_DeltaTime);
	LeftTop1Renderer->GetTransform().SetWorldScale({ LeftTop1Renderer->GetTransform().GetWorldScale().x - SacleY, LeftTop1Renderer->GetTransform().GetWorldScale().y });
	
	LeftTop2Renderer->GetTransform().SetWorldMove(MoveLeftTop * 1300.f * _DeltaTime);
	LeftTop2Renderer->GetTransform().SetWorldScale({ LeftTop2Renderer->GetTransform().GetWorldScale().x - SacleY, LeftTop2Renderer->GetTransform().GetWorldScale().y  });



	LeftTop2Renderer->GetTransform().SetWorldMove(MoveLeftTop * 1300.f * _DeltaTime);
	LeftTop2Renderer->GetTransform().SetWorldScale({ LeftTop1Renderer->GetTransform().GetWorldScale().x - SacleY, LeftTop1Renderer->GetTransform().GetWorldScale().y });

	LeftTop2Renderer->GetTransform().SetWorldMove(MoveLeftTop * 1300.f * _DeltaTime);
	LeftTop2Renderer->GetTransform().SetWorldScale({ LeftTop2Renderer->GetTransform().GetWorldScale().x - SacleY, LeftTop2Renderer->GetTransform().GetWorldScale().y });



	float4 MoveLeftBottom = float4{ -1.0f, -0.3f };


	LeftBottom1Renderer->GetTransform().SetWorldMove(MoveLeftBottom * 1300.f * _DeltaTime);
	LeftBottom1Renderer->GetTransform().SetWorldScale({ LeftBottom1Renderer->GetTransform().GetWorldScale().x - SacleY, LeftBottom1Renderer->GetTransform().GetWorldScale().y });

	LeftBottom1Renderer->GetTransform().SetWorldMove(MoveLeftBottom * 1300.f * _DeltaTime);
	LeftBottom1Renderer->GetTransform().SetWorldScale({ LeftBottom1Renderer->GetTransform().GetWorldScale().x - SacleY, LeftBottom1Renderer->GetTransform().GetWorldScale().y });


	LeftBottom2Renderer->GetTransform().SetWorldMove(MoveLeftBottom * 1300.f * _DeltaTime);
	LeftBottom2Renderer->GetTransform().SetWorldScale({ LeftBottom2Renderer->GetTransform().GetWorldScale().x - SacleY, LeftBottom2Renderer->GetTransform().GetWorldScale().y });

	LeftBottom2Renderer->GetTransform().SetWorldMove(MoveLeftBottom * 1300.f * _DeltaTime);
	LeftBottom2Renderer->GetTransform().SetWorldScale({ LeftBottom2Renderer->GetTransform().GetWorldScale().x - SacleY, LeftBottom2Renderer->GetTransform().GetWorldScale().y });



	float4 MoveRightTop = float4{ 1.0f, 0.3f };

	RightTop1Renderer->GetTransform().SetWorldMove(MoveRightTop * 1300.f * _DeltaTime);
	RightTop1Renderer->GetTransform().SetWorldScale({ RightTop1Renderer->GetTransform().GetWorldScale().x + SacleY, RightTop1Renderer->GetTransform().GetWorldScale().y });

	RightTop1Renderer->GetTransform().SetWorldMove(MoveRightTop * 1300.f * _DeltaTime);
	RightTop1Renderer->GetTransform().SetWorldScale({ RightTop1Renderer->GetTransform().GetWorldScale().x + SacleY, RightTop1Renderer->GetTransform().GetWorldScale().y });


	RightTop2Renderer->GetTransform().SetWorldMove(MoveRightTop * 1300.f * _DeltaTime);
	RightTop2Renderer->GetTransform().SetWorldScale({ RightTop2Renderer->GetTransform().GetWorldScale().x + SacleY, RightTop2Renderer->GetTransform().GetWorldScale().y });

	RightTop2Renderer->GetTransform().SetWorldMove(MoveRightTop * 1300.f * _DeltaTime);
	RightTop2Renderer->GetTransform().SetWorldScale({ RightTop2Renderer->GetTransform().GetWorldScale().x + SacleY, RightTop2Renderer->GetTransform().GetWorldScale().y });


	float4 MoveRightBottom = float4{ 1.0f, -0.4f };

	RightBottom1Renderer->GetTransform().SetWorldMove(MoveRightBottom * 1300.f * _DeltaTime);
	RightBottom1Renderer->GetTransform().SetWorldScale({ RightBottom1Renderer->GetTransform().GetWorldScale().x + SacleY, RightBottom1Renderer->GetTransform().GetWorldScale().y });

	RightBottom1Renderer->GetTransform().SetWorldMove(MoveRightBottom * 1300.f * _DeltaTime);
	RightBottom1Renderer->GetTransform().SetWorldScale({ RightBottom1Renderer->GetTransform().GetWorldScale().x + SacleY, RightBottom1Renderer->GetTransform().GetWorldScale().y });


	RightBottom2Renderer->GetTransform().SetWorldMove(MoveRightBottom * 1300.f * _DeltaTime);
	RightBottom2Renderer->GetTransform().SetWorldScale({ RightBottom2Renderer->GetTransform().GetWorldScale().x + SacleY, RightBottom2Renderer->GetTransform().GetWorldScale().y });

	RightBottom2Renderer->GetTransform().SetWorldMove(MoveRightBottom * 1300.f * _DeltaTime);
	RightBottom2Renderer->GetTransform().SetWorldScale({ RightBottom2Renderer->GetTransform().GetWorldScale().x + SacleY, RightBottom2Renderer->GetTransform().GetWorldScale().y });


	if (GetAccTime() > 0.4f)
	{
		this->Death();
	}
}

