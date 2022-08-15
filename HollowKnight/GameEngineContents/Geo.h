#pragma once
#include "MasterUI.h"

// Ό³Έν :
class Geo : public MasterUI
{
public:
	// constrcuter destructer
	Geo();
	~Geo();

	// delete Function
	Geo(const Geo& _Other) = delete;
	Geo(Geo&& _Other) noexcept = delete;
	Geo& operator=(const Geo& _Other) = delete;
	Geo& operator=(Geo&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _DeltaTime) override;

private:
	bool isAppearEnd_;
	bool isGetEnd_;
	bool isIdleEnd_;
	bool isBreakEnd_;

	GameEngineStateManager GeoManager_;

public:
	void SetAppearState()
	{
		GeoManager_.ChangeState("APPEAR");

	}

	void SetGetState()
	{
		GeoManager_.ChangeState("GET");

	}

	void SetIdleState()
	{
		GeoManager_.ChangeState("IDLE");

	}

	void SetBreakState()
	{
		GeoManager_.ChangeState("BREAK");

	}

private:

	//================================
	//    Bind State
	//================================
	void GeoAppearStart(const StateInfo& _Info);
	void GeoAppearUpdate(float _DeltaTime, const StateInfo& _Info);
	void GeoAppearEnd(const StateInfo& _Info);

	void GeoGetStart(const StateInfo& _Info);
	void GeoGetUpdate(float _DeltaTime, const StateInfo& _Info);
	void GeoGetEnd(const StateInfo& _Info);

	void GeoIdleStart(const StateInfo& _Info);
	void GeoIdleUpdate(float _DeltaTime, const StateInfo& _Info);
	void GeoIdleEnd(const StateInfo& _Info);

	void GeoBreakStart(const StateInfo& _Info);
	void GeoBreakUpdate(float _DeltaTime, const StateInfo& _Info);
	void GeoBreakEnd(const StateInfo& _Info);

	void GeoBrokenStart(const StateInfo& _Info);
	void GeoBrokenUpdate(float _DeltaTime, const StateInfo& _Info);
	void GeoBrokenEnd(const StateInfo& _Info);

};

