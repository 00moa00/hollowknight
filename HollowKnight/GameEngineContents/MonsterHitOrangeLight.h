#pragma once
#include "MasterEffect.h"

// Ό³Έν :
class MonsterHitOrangeLight : public MasterEffect
{
public:
	// constrcuter destructer
	MonsterHitOrangeLight();
	~MonsterHitOrangeLight();

	// delete Function
	MonsterHitOrangeLight(const MonsterHitOrangeLight& _Other) = delete;
	MonsterHitOrangeLight(MonsterHitOrangeLight&& _Other) noexcept = delete;
	MonsterHitOrangeLight& operator=(const MonsterHitOrangeLight& _Other) = delete;
	MonsterHitOrangeLight& operator=(MonsterHitOrangeLight&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _DeltaTime) override;


private:
	float Alpha_;
};

