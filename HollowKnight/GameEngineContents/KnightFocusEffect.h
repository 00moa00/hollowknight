#pragma once
#include "MasterEffect.h"

// Ό³Έν :
class KnightFocusEffect : public MasterEffect
{
public:
	// constrcuter destructer
	KnightFocusEffect();
	~KnightFocusEffect();

	// delete Function
	KnightFocusEffect(const KnightFocusEffect& _Other) = delete;
	KnightFocusEffect(KnightFocusEffect&& _Other) noexcept = delete;
	KnightFocusEffect& operator=(const KnightFocusEffect& _Other) = delete;
	KnightFocusEffect& operator=(KnightFocusEffect&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _DeltaTime) override;

private:

};

