#pragma once
#include "MasterActor.h"

// Ό³Έν :
class KnightShadow : public MasterActor
{
public:
	// constrcuter destructer
	KnightShadow();
	~KnightShadow();

	// delete Function
	KnightShadow(const KnightShadow& _Other) = delete;
	KnightShadow(KnightShadow&& _Other) noexcept = delete;
	KnightShadow& operator=(const KnightShadow& _Other) = delete;
	KnightShadow& operator=(KnightShadow&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _DeltaTime) override;

private:


};

