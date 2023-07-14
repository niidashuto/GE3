#include "PostEffectTest.hlsli"

Texture2D<float4> tex : register(t0);
SamplerState smp : register(s0);

float4 main(VSOutput input) : SV_TARGET
{   //デフォルト
	float4 texcolor = tex.Sample(smp,input.uv);
	//UVずらし
	//float4 texcolor = tex.Sample(smp, input.uv+float2(0.5f,0.0f));

	//明度変更
	//return float4(texcolor.rgb*2.0f, 1.0f);
	//色反転
	//return float4(float3(1.0f,1.0f,1.0f)-texcolor.rgb, 1.0f);
	//デフォルト
	return float4(texcolor.rgb, 1.0f);

	//平均ぼかし
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
//    col += tex.Sample(smp, input.uv + float2(px, py) * _ShiftWidth);
//    num++;
//}
//}
//col.rgb = col.rgb / num;
//col.a = 1.0f;
//
//return col;
}