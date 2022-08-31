#pragma once
#include "Map.h"
#include "MasterUI.h"

// Ό³Έν :
class ForgottenCrossroads : public MasterUI
{
public:
	// constrcuter destructer
	ForgottenCrossroads();
	~ForgottenCrossroads();

	// delete Function
	ForgottenCrossroads(const ForgottenCrossroads& _Other) = delete;
	ForgottenCrossroads(ForgottenCrossroads&& _Other) noexcept = delete;
	ForgottenCrossroads& operator=(const ForgottenCrossroads& _Other) = delete;
	ForgottenCrossroads& operator=(ForgottenCrossroads&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _DeltaTime) override;

private:
	std::map<int, Map*> ForgottenCrossroadMap_;

};

