#pragma once
#include <GameEngineCore/CoreMinimal.h>
#include <GameEngineCore/GameEngineCollision.h>

// 설명 : 울부짖는 비명? 이펙트
class KnightScreamCastEffect : public GameEngineActor
{
public:
	// constrcuter destructer
	KnightScreamCastEffect();
	~KnightScreamCastEffect();

	// delete Function
	KnightScreamCastEffect(const KnightScreamCastEffect& _Other) = delete;
	KnightScreamCastEffect(KnightScreamCastEffect&& _Other) noexcept = delete;
	KnightScreamCastEffect& operator=(const KnightScreamCastEffect& _Other) = delete;
	KnightScreamCastEffect& operator=(KnightScreamCastEffect&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _DeltaTime) override;

private:
	GameEngineTextureRenderer* NeutralRenderer_;
	GameEngineTextureRenderer* ScreamRenderer_;

	GameEngineCollision* MainCollision_;

public:
	void EffectOn();

	bool EffectVSMonsterCollision(GameEngineCollision* _This, GameEngineCollision* _Other);

};

