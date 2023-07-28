#include "PostEffectTest.hlsli"

Texture2D<float4> tex0 : register(t0);
Texture2D<float4> tex1 : register(t1);
SamplerState smp : register(s0);

float4 Blur(VSOutput i, float blurRange, Texture2D<float4> tex)
{
	float _ShiftWidth = 0.005f;
	    float _ShiftNumX = 4.0f; //num x num
	    float _ShiftNumY = 5.0f; //num x num
	
	    float4 col = float4(0.0f, 0.0f, 0.0f, 0.0f);
	    float num = 0;
	    for (float py = -_ShiftNumY / 2.0f; py <= _ShiftNumY / 2.0f; py++)
	    {
	        
	for (float px = -_ShiftNumX / 2.0f; px <= _ShiftNumX / 2.0f; px++)
	{
	    col += tex1.Sample(smp, i.uv + float2(px, py) * _ShiftWidth);
	    num++;
	}
	}
	col.rgb = col.rgb / num;
	col.a = 1.0f;

	return col;
}

float4 main(VSOutput input) : SV_TARGET
{   //デフォルト
	float4 texcolor0 = tex0.Sample(smp,input.uv);
	float4 texcolor1 = tex1.Sample(smp, input.uv);

    float4 color = float4(1, 1, 1, 1) - texcolor0;
	if (fmod(input.uv.y, 0.1f) < 0.05f)
	{
        color = Blur(input, 3, tex1);
	}
	//UVずらし
	//float4 texcolor = tex.Sample(smp, input.uv+float2(0.5f,0.0f));

	//明度変更
	//return float4(texcolor.rgb*2.0f, 1.0f);
	//色反転
	//return float4(float3(1.0f,1.0f,1.0f)-color.rgb, 1.0f);
	//デフォルト
	return float4(color.rgb, 1.0f);

//	//平均ぼかし
//    float _ShiftWidth = 0.005f;
//    float _ShiftNumX = 4.0f; //num x num
//    float _ShiftNumY = 5.0f; //num x num
//
//    float4 col = float4(0.0f, 0.0f, 0.0f, 0.0f);
//    float num = 0;
//    for (float py = -_ShiftNumY / 2.0f; py <= _ShiftNumY / 2.0f; py++)
//    {
//        //[loop]、[unroll]は書かなくていい
//for (float px = -_ShiftNumX / 2.0f; px <= _ShiftNumX / 2.0f; px++)
//{
//    col += tex1.Sample(smp, input.uv + float2(px, py) * _ShiftWidth);
//    num++;
//}
//}
//col.rgb = col.rgb / num;
//col.a = 1.0f;

//return col;
}