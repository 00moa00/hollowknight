#pragma once
#include "MasterUI.h"


// Ό³Έν :
class BorderTop : public MasterUI
{
public:
	// constrcuter destructer
	BorderTop();
	~BorderTop();

	// delete Function
	BorderTop(const BorderTop& _Other) = delete;
	BorderTop(BorderTop&& _Other) noexcept = delete;
	BorderTop& operator=(const BorderTop& _Other) = delete;
	BorderTop& operator=(BorderTop&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _DeltaTime) override;

private:
	bool AnimationEnd_;
	

public:
};

