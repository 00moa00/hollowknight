#include "TransformHeader.fx"
#include "RenderOption.fx"


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


// 그래픽카드에서 이뤄지는것.
Output Blur2_VS(Input _Input)
{
    Output NewOutPut = (Output) 0;
    _Input.Pos += PivotPos;
    NewOutPut.Pos = mul(_Input.Pos, WorldViewProjection);
    NewOutPut.PosLocal = _Input.Pos;
    
    // 버텍스가 몇번째 버텍스 인지 알수가 없다.
    // NewOutPut.Tex
    // 00    10
    
    //// 10    11
    
    //TextureFrameSize.x -= 0.5f;
    //TextureFrameSize.y -= 0.5f;
    //TextureFramePos.x -= 0.5f;
    //TextureFramePos.y -= 0.5f;
    
    NewOutPut.Tex.x = (_Input.Tex.x * TextureFrameSize.x) + TextureFramePos.x;
    NewOutPut.Tex.y = (_Input.Tex.y * TextureFrameSize.y) + TextureFramePos.y;
    
    return NewOutPut;
}

// 1000
// 0100
// 2010
// 0301

// 1020
// 0103
// 0010
// 0001

//static float Gau[5][5] =
//{
//    {  }
//};

Texture2D Tex : register(t0);
SamplerState Smp : register(s0);
float4 Blur_PS(Output _Input) : SV_Target0
{
    if (_Input.Tex.x < Slice.x)
    {
        clip(-1);
    }
    
   // float4 Tex = (Tex.Sample(Smp, _Input.Tex.xy) * MulColor) + PlusColor;
    float4 AltlasTex = (Tex.Sample(Smp, _Input.Tex.xy) * MulColor) + PlusColor;
    
    
    float2 PixelUVSize = float2(1.0f / 1280.0f, 1.0f / 720.0f);
    float2 PixelUVCenter = _Input.Tex.xy;
    float2 StartUV = PixelUVCenter + (-PixelUVSize * 2);
    float2 CurUV = StartUV;
    
    float4 Result = (float4) 0.0f;
    
    for (int y = 0; y < 5; ++y)
    {
        for (int x = 0; x < 5; ++x)
        {
            Result +=  AltlasTex /* * Gau[y][x]*/;
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
    
    return (Tex.Sample(Smp, _Input.Tex.xy) * MulColor) + PlusColor;
}
