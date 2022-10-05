#include <GameEngineCore/CoreMinimal.h>
#include <GameEngineCore/GameEngineFontRenderer.h>

// 설명 :
class GeoCountFont : public GameEngineActor
{
public:
	// constrcuter destructer
	GeoCountFont();
	~GeoCountFont();

	// delete Function
	GeoCountFont(const GeoCountFont& _Other) = delete;
	GeoCountFont(GeoCountFont&& _Other) noexcept = delete;
	GeoCountFont& operator=(const GeoCountFont& _Other) = delete;
	GeoCountFont& operator=(GeoCountFont&& _Other) noexcept = delete;

protected:
	void Start()override;
	void Update(float _DeltatTime)override;

private:

	int CurrentNum_;		// 현재숫자
	int CountingNum_;		// 카운팅 할


	float CountingTimer_;

	GameEngineFontRenderer* GameEngineFontRenderer_;


private:
	void CreateFontRenderer(std::string _Text, float _FontSize, float4 _Position, bool _isdotLineBreak, bool _isTyping, int _LineBreak = 0);

public:
	//================================
	//    Getter
	//================================
	GameEngineFontRenderer* GetFontRenderer()
	{
		return GameEngineFontRenderer_;
	}

	//================================
	//    Bind State
	//================================
	void FontCountingStart(const StateInfo& _Info);
	void FontCountingUpdate(float _DeltaTime, const StateInfo& _Info);
	void FontCountingEnd(const StateInfo& _Info);

	void FontIdleStart(const StateInfo& _Info);
	void FontIdleUpdate(float _DeltaTime, const StateInfo& _Info);
	void FontIdleEnd(const StateInfo& _Info);

};

