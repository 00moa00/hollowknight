#pragma once

// Ό³Έν :
class KnightShadow
{
public:
	// constrcuter destructer
	KnightShadow();
	~KnightShadow();

	// delete Function
	KnightShadow(const KnightShadow& _Other) = delete;
	KnightShadow(KnightShadow&& _Other) noexcept = delete;
	KnightShadow& operator=(const KnightShadow& _Other) = delete;
	KnightShadow& operator=(KnightShadow&& _Other) noexcept = delete;

protected:

private:


};

