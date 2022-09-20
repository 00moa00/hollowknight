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
Output Vignette_VS(Input _Input)
{
    Output NewOutPut = (Output) 0;
    NewOutPut.Pos = _Input.Pos;
    NewOutPut.Tex = _Input.Tex;
    return NewOutPut;
}

//float Vignette(float2 uv, float size)
//{
//    float d = length((uv - 0.5f) * 2.0f) / length(float2(1.0, 0));
    
//    d /= size;
    
//    float s = d * d * (3.0f - 2.0f * d);
    
//    float v = lerp(d, s, 0.6f);
//    float re = max(0.0, 1.0f - v);
//    return re;
//}

float3 NaturalVignette(float3 color, float2 uv, float amount)
{
    float2 coord = (uv - 0.5) * (1920.f / 1080.0f) * 2.0;
    float rf = sqrt(dot(coord, coord)) * amount / 3.;
    float rf2_1 = rf * rf + 1.0;
    float vig = 1.0 / (rf2_1 * rf2_1);
    
    float3 Re = color * vig;
    return color * vig;
}


Texture2D Tex : register(t0);
SamplerState Smp : register(s0);
float4 Vignette_PS(Output _Input) : SV_Target0
{
    // 파란색
    //float2 PixelUVSize = float2(1.0f / 1920.0f, 1.0f / 1080.0f);
    //float2 PixelUVCenter = _Input.Tex.xy;
    //float2 StartUV = PixelUVCenter + (-PixelUVSize * 2);
    //float2 CurUV = StartUV;
    
    //float2 samplePoint = CurUV;
    //float4 Texture = Tex.Sample(Smp, samplePoint);
    
    //float fShade = Vignette(CurUV, 5);
    
    //float4 src = Texture *= fShade;
    //float4 Re = float4(src.rgb, 1.0);
    //return Re;
    
    //float vignette = length(float2(0.5, 0.5) - CurUV);
    //vignette = clamp(vignette - 0.2, 0, 1);
    //Texture.rgb -= vignette;
    //return Texture;
    

        
    float2 PixelUVSize = float2(1.0f / 1920.0f, 1.0f / 1080.0f);
    float2 PixelUVCenter = _Input.Tex.xy;
    float2 StartUV = PixelUVCenter + (-PixelUVSize * 2);
    float2 CurUV = StartUV;
    
    
    float4 Texture = Tex.Sample(Smp, _Input.Tex.xy);
    float4 Return;
    Return.xyz = NaturalVignette(float3(Texture.rgb), CurUV.xy, 1.f);
    Return.w = 1.0f;
    return Return;
    
    
    //float2 PixelUVSize = float2(1.0f / 1920.0f, 1.0f / 1080.0f);
    //float2 PixelUVCenter = _Input.Tex.xy;
    //float2 StartUV = PixelUVCenter + (-PixelUVSize * 2);
    //float2 CurUV = StartUV;
    
    
    //float2 uv = fragCoord.xy / iResolution.xy;
    
    //float4 Texture = Tex.Sample(Smp, _Input.Tex.xy);
    //float4 fragColor = float4(pow((CurUV *= 1.0 - CurUV.xy, CurUV.x * CurUV.y * 42.0), 0.1));
    //float4 Return;
    
    
    //Return.xyz = Texture.xyz + fragColor.xyz;
    
    //Return.w = 1.0f;
    //return Return;
    
    //float2 samplePoint = CurUV;
    //float4 Texture = Tex.Sample(Smp, samplePoint);
    //float2 coord = (samplePoint - 0.5) * (_Input.Tex.x / _Input.Tex.y) * 2.0;
    
    
    //float rf = sqrt(dot(coord, coord)) * 0.25f;
    //float rf2_1 = rf * rf + 1.0;
    //float e = 1.0 / (rf2_1 * rf2_1);
    
    //float4 src = float4(1.0, 1.0, 1.0, 0.4);
    //float4 Result = float4(src.rgb * e, 1.0);
    
    //return Re;
   
}
