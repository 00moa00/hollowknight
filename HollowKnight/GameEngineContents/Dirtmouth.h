#pragma once

// Ό³Έν :
class Dirtmouth
{
public:
	// constrcuter destructer
	Dirtmouth();
	~Dirtmouth();

	// delete Function
	Dirtmouth(const Dirtmouth& _Other) = delete;
	Dirtmouth(Dirtmouth&& _Other) noexcept = delete;
	Dirtmouth& operator=(const Dirtmouth& _Other) = delete;
	Dirtmouth& operator=(Dirtmouth&& _Other) noexcept = delete;

protected:

private:

};

