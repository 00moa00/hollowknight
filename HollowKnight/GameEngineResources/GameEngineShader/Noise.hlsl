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

cbuffer NoiseData : register(b3)
{
    float Time;
    float Dummy0;
    float Dummy1;
    float Dummy2;
};

// 그래픽카드에서 이뤄지는것.
Output Blur_VS(Input _Input)
{
    Output NewOutPut = (Output) 0;
    NewOutPut.Pos = _Input.Pos;
    NewOutPut.Tex = _Input.Tex;
    return NewOutPut;
}

float WhiteNoise(float2 coord)
{
    return frac(sin(dot(coord, float2(8.7819, 3.255))) * 437.645);
}

Texture2D Tex : register(t0);
SamplerState Smp : register(s0);
float4 Blur_PS(Output _Input) : SV_Target0
{
    // 파란색
    
    float2 PixelUVSize = float2(1.0f / 1920.0f, 1.0f / 1080.0f);
    float2 PixelUVCenter = _Input.Tex.xy;
    float2 StartUV = PixelUVCenter + (-PixelUVSize * 2);
    float2 CurUV = StartUV;
    
    float4 Result = (float4) 0.0f;
     
    float2 samplePoint = CurUV;
    float4 Texture = Tex.Sample(Smp, samplePoint);
    float noise = WhiteNoise(CurUV * Time) - 0.5;
    Texture.rgb += float3(noise, noise, noise);
    return Texture;
    
    
}
