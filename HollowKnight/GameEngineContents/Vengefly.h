#pragma once
#include "Monster.h"

// Ό³Έν :
class Vengefly : public Monster
{
public:
	// constrcuter destructer
	Vengefly();
	~Vengefly();

	// delete Function
	Vengefly(const Vengefly& _Other) = delete;
	Vengefly(Vengefly&& _Other) noexcept = delete;
	Vengefly& operator=(const Vengefly& _Other) = delete;
	Vengefly& operator=(Vengefly&& _Other) noexcept = delete;

protected:

private:

};

