#pragma once
#include <GameEngineCore/CoreMinimal.h>


// Ό³Έν :
class MonsterHitEffect : public GameEngineActor
{
public:
	// constrcuter destructer
	MonsterHitEffect();
	~MonsterHitEffect();

	// delete Function
	MonsterHitEffect(const MonsterHitEffect& _Other) = delete;
	MonsterHitEffect(MonsterHitEffect&& _Other) noexcept = delete;
	MonsterHitEffect& operator=(const MonsterHitEffect& _Other) = delete;
	MonsterHitEffect& operator=(MonsterHitEffect&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _DeltaTime) override;

private:

	float SacleY ;

	GameEngineTextureRenderer* LeftTop1Renderer;
	GameEngineTextureRenderer* LeftTop2Renderer;


	GameEngineTextureRenderer* LeftBottom1Renderer;
	GameEngineTextureRenderer* LeftBottom2Renderer;

	GameEngineTextureRenderer* RightTop1Renderer;
	GameEngineTextureRenderer* RightTop2Renderer;

	GameEngineTextureRenderer* RightBottom1Renderer;
	GameEngineTextureRenderer* RightBottom2Renderer;


	void PixLocalNegativeY(GameEngineTextureRenderer* _Renderer)
	{
		_Renderer->GetTransform().SetLocalScale({ _Renderer->GetTransform().GetLocalScale().x, abs(_Renderer->GetTransform().GetLocalScale().y), 1 });
		if (0.0f > _Renderer->GetTransform().GetLocalScale().y)
		{
			return;
		}

		_Renderer->GetTransform().SetLocalScale({ _Renderer->GetTransform().GetLocalScale().x, -(_Renderer->GetTransform().GetLocalScale().y), 1 });
	}

	void PixLocalPositiveY(GameEngineTextureRenderer* _Renderer)
	{

		if (0.0f < _Renderer->GetTransform().GetLocalScale().y)
		{
			return;
		}

	}


};

