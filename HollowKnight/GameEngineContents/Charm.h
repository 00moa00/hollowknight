#pragma once
#include "MasterUI.h"
// Ό³Έν :
class Charm : public MasterUI
{
public:
	// constrcuter destructer
	Charm();
	~Charm();

	// delete Function
	Charm(const Charm& _Other) = delete;
	Charm(Charm&& _Other) noexcept = delete;
	Charm& operator=(const Charm& _Other) = delete;
	Charm& operator=(Charm&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _DeltaTime) override;

private:
	std::string CharmName_;


public:
	void CreateCharm(std::string _Name, std::string _FilePath, float4 Scale);
	//void CreateEquippedCharm(std::string _Name, std::string _FilePath, float4 Scale);

};

