#include <GameEngineCore/CoreMinimal.h>

// Ό³Έν :
class TitleWhitePartlcle : public GameEngineActor
{
public:
	// constrcuter destructer
	TitleWhitePartlcle();
	~TitleWhitePartlcle();

	// delete Function
	TitleWhitePartlcle(const TitleWhitePartlcle& _Other) = delete;
	TitleWhitePartlcle(TitleWhitePartlcle&& _Other) noexcept = delete;
	TitleWhitePartlcle& operator=(const TitleWhitePartlcle& _Other) = delete;
	TitleWhitePartlcle& operator=(TitleWhitePartlcle&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _DeltaTime) override;

private:
	float AliveTimer_;
	float Alpha_;
	float Scale_;
	float Speed_;


	float4 Dir_;

	GameEngineTextureRenderer* ParticleRenderer_;

};

