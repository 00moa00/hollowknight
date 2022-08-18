#pragma once

// Ό³Έν :
class DetailedMapPage
{
public:
	// constrcuter destructer
	DetailedMapPage();
	~DetailedMapPage();

	// delete Function
	DetailedMapPage(const DetailedMapPage& _Other) = delete;
	DetailedMapPage(DetailedMapPage&& _Other) noexcept = delete;
	DetailedMapPage& operator=(const DetailedMapPage& _Other) = delete;
	DetailedMapPage& operator=(DetailedMapPage&& _Other) noexcept = delete;

protected:

private:

};

