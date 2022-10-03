#pragma once
#include <GameEngineCore/CoreMinimal.h>


// 현재 가진 가면 조각 갯수에 따라서 애니메이션 처리
// 일정 시간 지나면 알파값이 내려가면서 Off
// fsm 으로 만들기 싫어서 if문으로 처리했는데 그냥 fsm으로 만들어야할 듯
class HeartPiece : public GameEngineActor
{
public:
	// constrcuter destructer
	HeartPiece();
	~HeartPiece();

	// delete Function
	HeartPiece(const HeartPiece& _Other) = delete;
	HeartPiece(HeartPiece&& _Other) noexcept = delete;
	HeartPiece& operator=(const HeartPiece& _Other) = delete;
	HeartPiece& operator=(HeartPiece&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _DeltaTime) override;

private:
	bool isNewMask_;		// 마스크가 새로 생겼을때
	bool isCompleteMask_;	// 마스크가 완성 됐을때

	bool isFleurAppeerEnd_;

	bool isLevel1End_;
	bool isLevel2End_;
	bool isLevel3End_;
	bool isLevel4End_;
	bool isFuseEnd_;

	float Alpha_;

	GameEngineUIRenderer* FleurRenderer_;
	GameEngineUIRenderer* MaskRenderer_;
	GameEngineUIRenderer* FlashRenderer_;

public:
	void SetNewMaskPiece();

};

