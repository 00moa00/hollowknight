// #include "myshader.hlsli"

// SV_POSITION 시맨틱
// 그래픽카드에게 이녀석은 이런 부류니까 니가 자동으로 처리하는 녀석이 있으면 하고.

#include "TransformHeader.fx"
#include "RenderOption.fx"

// 0                                                                                                1 
// 0□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□1

struct Input
{
    float4 Pos : POSITION;
    float4 Tex : TEXCOORD;
};

struct Output
{
    float4 Pos : SV_POSITION;
    float4 PosLocal : POSITION;
    float4 Tex0 : TEXCOORD0;
    float4 Tex1 : TEXCOORD1; //마스크 기준이 될 텍스처
};

// 1000
// 0100
// 2010
// 0301

// 1020
// 0103
// 0010
// 0001

cbuffer AtlasData : register(b1)
{
    float2 TextureFramePos;
    float2 TextureFrameSize;
    float4 PivotPos;
};

cbuffer UVData : register(b2)
{
    float OffsetX;
    float OffsetY;
    float Dummy0;
    float Dummy1;
};



Output TextureAtlas_VS(Input _Input)
{
    Output NewOutPut = (Output)0;
    _Input.Pos += PivotPos;
    NewOutPut.Pos = mul(_Input.Pos, WorldViewProjection);
    NewOutPut.PosLocal = _Input.Pos;
    
    // 버텍스가 몇번째 버텍스 인지 알수가 없다.
    // NewOutPut.Tex
    // 00    10
    
    // 10    11
    
    NewOutPut.Tex0.x = (_Input.Tex.x  * TextureFrameSize.x) + (TextureFramePos.x);
    NewOutPut.Tex0.y = (_Input.Tex.y * TextureFrameSize.y) + (TextureFramePos.y + OffsetY);

    NewOutPut.Tex1 = _Input.Tex; // uv값을 그대로 넣었다.
    
    return NewOutPut;
}

cbuffer PixelData : register(b0)
{
    float4 MulColor;
    float4 PlusColor;
    float4 Slice;
}

Texture2D Tex : register(t0);
SamplerState Smp : register(s0);
Texture2D Test : register(t1);

float4 TextureAtlas_PS(Output _Input) : SV_Target0
{
    if (_Input.Tex0.x < Slice.x)
    {
        clip(-1);
    }
    
    float4 MaskColor = Test.Sample(Smp, _Input.Tex1.xy); //기준이 될 아이의 색상 정보를 가져와
    
    if (MaskColor.a == 0.f) //투명하지 않은 부분은 그려내지 않을거야
    {
        discard;
    }
    
    
    return (Tex.Sample(Smp, _Input.Tex0.xy) * MulColor) + PlusColor;
}
    
    
    
