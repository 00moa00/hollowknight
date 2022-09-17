#include "TransformHeader.fx"
#include "RenderOption.fx"


const float offset[] = { 0.0, 1.0, 2.0, 3.0, 4.0 };
const float weight[] =
{
    0.2270270270, 0.1945945946, 0.1216216216,
  0.0540540541, 0.0162162162
};
struct Input
{
    float4 Pos : POSITION;
    float4 Tex : TEXCOORD;
};

struct Output
{
    float4 Pos : SV_POSITION;
    float4 PosLocal : POSITION;
    float4 Tex : TEXCOORD;
};

cbuffer AtlasData : register(b1)
{
    float2 TextureFramePos;
    float2 TextureFrameSize;
    float4 PivotPos;
};

cbuffer PixelData : register(b0)
{
    float4 MulColor;
    float4 PlusColor;
    float4 Slice;
}


cbuffer BlurData : register(b2)
{
    float4 TextureSize;
}


// 그래픽카드에서 이뤄지는것.
Output Blur_VS(Input _Input)
{
    Output NewOutPut = (Output) 0;
    _Input.Pos += PivotPos;
    NewOutPut.Pos = mul(_Input.Pos, WorldViewProjection);
    NewOutPut.PosLocal = _Input.Pos;

    NewOutPut.Tex.x = (_Input.Tex.x * TextureFrameSize.x) + TextureFramePos.x;
    NewOutPut.Tex.y = (_Input.Tex.y * TextureFrameSize.y) + TextureFramePos.y;
    
    return NewOutPut;
}


Texture2D Tex : register(t0);
SamplerState Smp : register(s0);
float4 Blur_PS(Output _Input) : SV_Target0
{  
    if (_Input.Tex.x < Slice.x)
    {
        clip(-1);
    }
    
    float4 AltlasTex = (Tex.Sample(Smp, _Input.Tex.xy) * MulColor) + PlusColor;
   

    float4 Texture = AltlasTex;
    float4 BrightColor = 0.f;
    
    float Brightness = dot(Texture.rgb, float3(0.2126F, 0.7152f, 0.0722f));
    if (Brightness > 0.99)
        BrightColor = float4(Texture.rgb, 1.0);
    
    return BrightColor;

    AltlasTex = BrightColor;
   
    
  //  return (BrightTex.Sample(Smp, _Input.Tex.xy) * MulColor) + PlusColor;
    
    float2 PixelUVSize = float2(1.0f / TextureSize.x, 1.0f / TextureSize.y);
    float2 PixelUVCenter = _Input.Tex.xy;
    float2 StartUV = PixelUVCenter + (-PixelUVSize * 2);
    float2 CurUV = StartUV;
    
    
    float4 Result = (float4) 0.0f;
    
    for (int y = 0; y < 5; ++y)
    {
        for (int x = 0; x < 5; ++x)
        {
            Result += Tex.Sample(Smp, CurUV) /* * Gau[y][x]*/;
            CurUV.x += PixelUVSize.x;
        }
        
        CurUV.x = StartUV.x;
        CurUV.y += PixelUVSize.y;
    }
    
    Result /= 25.0f;
    
    // Color
    // 지금 이 색깔은?
    
    if (Result.a <= 0.0f)
    {
        clip(-1);
    }
    
    return Result;

}
