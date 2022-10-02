#pragma once

// Ό³Έν :
class Sycophant
{
public:
	// constrcuter destructer
	Sycophant();
	~Sycophant();

	// delete Function
	Sycophant(const Sycophant& _Other) = delete;
	Sycophant(Sycophant&& _Other) noexcept = delete;
	Sycophant& operator=(const Sycophant& _Other) = delete;
	Sycophant& operator=(Sycophant&& _Other) noexcept = delete;

protected:

private:

};

