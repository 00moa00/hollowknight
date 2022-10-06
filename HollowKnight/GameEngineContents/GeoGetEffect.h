#pragma once
#include "MasterEffect.h"

// Ό³Έν :
class GeoGetEffect : public MasterEffect
{
public:
	// constrcuter destructer
	GeoGetEffect();
	~GeoGetEffect();

	// delete Function
	GeoGetEffect(const GeoGetEffect& _Other) = delete;
	GeoGetEffect(GeoGetEffect&& _Other) noexcept = delete;
	GeoGetEffect& operator=(const GeoGetEffect& _Other) = delete;
	GeoGetEffect& operator=(GeoGetEffect&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _DeltaTime) override;

private:

};

