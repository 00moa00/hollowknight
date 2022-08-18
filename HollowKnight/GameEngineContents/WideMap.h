#pragma once
#include "MasterUI.h"
#include <GameEngineCore/GameEngineFontRenderer.h>

// 설명 : 간략된 맵 생성용
class WideMap : public MasterUI
{
public:
	// constrcuter destructer
	WideMap();
	~WideMap();

	// delete Function
	WideMap(const WideMap& _Other) = delete;
	WideMap(WideMap&& _Other) noexcept = delete;
	WideMap& operator=(const WideMap& _Other) = delete;
	WideMap& operator=(WideMap&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _DeltaTime) override;

private:
	GameEngineFontRenderer* MapFont_;

public:
	void CreateWideMap(std::string _Path, std::string _Name);
};

