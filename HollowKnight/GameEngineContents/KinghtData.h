#pragma once

// Ό³Έν :
class KinghtData
{
public:
	// constrcuter destructer
	KinghtData();
	~KinghtData();

	// delete Function
	KinghtData(const KinghtData& _Other) = delete;
	KinghtData(KinghtData&& _Other) noexcept = delete;
	KinghtData& operator=(const KinghtData& _Other) = delete;
	KinghtData& operator=(KinghtData&& _Other) noexcept = delete;

protected:

private:

};

