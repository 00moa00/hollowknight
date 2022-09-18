#pragma once
#include "MasterObject.h"
#include "FadeOut.h"
#include "FadeIn.h"

enum class FadeMode
{
	FadeIn,
	FadeOut,
	Max
};

// Ό³Έν :
class Potal : public  MasterObject
{
public:
	// constrcuter destructer
	Potal();
	~Potal();

	// delete Function
	Potal(const Potal& _Other) = delete;
	Potal(Potal&& _Other) noexcept = delete;
	Potal& operator=(const Potal& _Other) = delete;
	Potal& operator=(Potal&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _DeltaTime) override;

private:
	std::string Level_;
	FadeOut* FadeOut_;
	FadeIn* FadeIn_;

	FadeMode FadeMode_;
//	float MoveTimer


public:

	void CreatePotal(std::string _ChangeLevel, FadeMode _Mode);

private:
	//================================
	//    Bind 
	//================================

	bool PotalVSKnightCollision(GameEngineCollision* _This, GameEngineCollision* _Other);


};

