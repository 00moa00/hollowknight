// #include "myshader.hlsli"

// SV_POSITION 시맨틱
// 그래픽카드에게 이녀석은 이런 부류니까 니가 자동으로 처리하는 녀석이 있으면 하고.


//cbuffer BloomData : register(b3)
//{
//    float4 iMouse;
//    float4 iResolution;
//};

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




Texture2D Tex : register(t0);
SamplerState Smp : register(s0);
float4 Blur_PS(Output _Input) : SV_Target0
{
    float2 PixelUVSize = float2(1.0f / 1920.0f, 1.0f / 1080.0f);
    float2 PixelUVCenter = _Input.Tex.xy;
    float2 StartUV = PixelUVCenter + (-PixelUVSize * 1.5);
    float2 CurUV = StartUV;

    float4 Texture = Tex.Sample(Smp, CurUV);
    float BrightColor = 0.f;

    float brightness = dot(Texture.rgb, float3(0.2126f, 0.7152f, 0.0722f));
    if (brightness > 0.99)
        BrightColor = float4(Texture.rgb, 1.0);
    
    return BrightColor;
    
    //const vec3 W = vec3(0.2125, 0.7154, 0.721);
    //float luminosidad = dot(fragColor.xyz, W);
    
    //if (luminosidad > LUMINANCIA)
    //{
      	
        
    //    fragColor = texture(iChannel0, uv);
        
    	
    
	
    //}
    //else
    //{
    //    fragColor = texture(iChannel1, uv);
    //}
   

}
