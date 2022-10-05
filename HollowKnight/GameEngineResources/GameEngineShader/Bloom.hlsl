// #include "myshader.hlsli"

// SV_POSITION 시맨틱
// 그래픽카드에게 이녀석은 이런 부류니까 니가 자동으로 처리하는 녀석이 있으면 하고.

struct Input
{
    float4 Pos : POSITION;
    float4 Tex : TEXCOORD;  
};


struct Output
{
    float4 Pos : SV_POSITION;
    
    float4 Tex : TEXCOORD;



};


// 그래픽카드에서 이뤄지는것.
Output Blur_VS(Input _Input)
{
    Output NewOutPut = (Output) 0;
    NewOutPut.Pos = _Input.Pos;
    
    NewOutPut.Tex = _Input.Tex;


    
    return NewOutPut;
}



SamplerState Smp : register(s0);
Texture2D OriTexture : register(t0);

Texture2D BloomTex : register(t1);
Texture2D BloomOriTex : register(t2);

float4 Blur_PS(Output _Input) : SV_Target0
{
    float2 PixelUVSize = float2(1.0f / 1920.0f, 1.0f / 1080.0f);
    float2 PixelUVCenter = _Input.Tex.xy;
    float2 StartUV = PixelUVCenter + (-PixelUVSize * 2);
    float2 CurUV = StartUV;
    
    
    float4 Texture = OriTexture.Sample(Smp, CurUV);
    float4 BloomTexture = BloomTex.Sample(Smp, CurUV);
    float4 BloomOriTexture = BloomOriTex.Sample(Smp, CurUV);
    
    float4 Bloom = pow(pow(abs(BloomTexture), 1.8f) + pow(abs(BloomOriTexture), 1.8f), 1.f / 1.8f);
    
    float4 Out = Texture;
    
    Out = pow(abs(Out), 2.2f);

    Bloom = pow(abs(Bloom), 2.2f);
    
    
    Out += Bloom;
    
    return pow(abs(Out), 1 / 2.2f);
    
    //return Texture;

}
