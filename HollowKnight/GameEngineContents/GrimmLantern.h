#pragma once
#include "MasterObject.h"

// Ό³Έν :
class GrimmLantern : public MasterObject
{
public:
	// constrcuter destructer
	GrimmLantern();
	~GrimmLantern();

	// delete Function
	GrimmLantern(const GrimmLantern& _Other) = delete;
	GrimmLantern(GrimmLantern&& _Other) noexcept = delete;
	GrimmLantern& operator=(const GrimmLantern& _Other) = delete;
	GrimmLantern& operator=(GrimmLantern&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _DeltaTime) override;

private:

};

