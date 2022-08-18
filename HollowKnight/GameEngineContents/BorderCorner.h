#pragma once
#include "MasterUI.h"

// Ό³Έν :
class BorderCorner : public MasterUI
{
public:
	// constrcuter destructer
	BorderCorner();
	~BorderCorner();

	// delete Function
	BorderCorner(const BorderCorner& _Other) = delete;
	BorderCorner(BorderCorner&& _Other) noexcept = delete;
	BorderCorner& operator=(const BorderCorner& _Other) = delete;
	BorderCorner& operator=(BorderCorner&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _DeltaTime) override;

private:

};

