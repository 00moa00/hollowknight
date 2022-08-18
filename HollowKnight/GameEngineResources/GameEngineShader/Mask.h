#pragma once

// Ό³Έν :
class Mask
{
public:
	// constrcuter destructer
	Mask();
	~Mask();

	// delete Function
	Mask(const Mask& _Other) = delete;
	Mask(Mask&& _Other) noexcept = delete;
	Mask& operator=(const Mask& _Other) = delete;
	Mask& operator=(Mask&& _Other) noexcept = delete;

protected:

private:

};

