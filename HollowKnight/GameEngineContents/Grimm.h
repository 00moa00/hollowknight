#pragma once
#include "Monster.h"

// Ό³Έν :
class Grimm : public Monster
{
public:
	// constrcuter destructer
	Grimm();
	~Grimm();

	// delete Function
	Grimm(const Grimm& _Other) = delete;
	Grimm(Grimm&& _Other) noexcept = delete;
	Grimm& operator=(const Grimm& _Other) = delete;
	Grimm& operator=(Grimm&& _Other) noexcept = delete;

protected:

private:

};

