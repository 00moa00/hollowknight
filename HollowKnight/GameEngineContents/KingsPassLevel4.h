#pragma once
#include <GameEngineCore/GameEngineLevel.h>
#include "HollowKnightLevel.h"

// Ό³Έν :
class KingsPassLevel4 : public HollowKnightLevel
{
public:
	// constrcuter destructer
	KingsPassLevel4();
	~KingsPassLevel4();

	// delete Function
	KingsPassLevel4(const KingsPassLevel4& _Other) = delete;
	KingsPassLevel4(KingsPassLevel4&& _Other) noexcept = delete;
	KingsPassLevel4& operator=(const KingsPassLevel4& _Other) = delete;
	KingsPassLevel4& operator=(KingsPassLevel4&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _DeltaTime) override;
	void End() override;

private:

};

