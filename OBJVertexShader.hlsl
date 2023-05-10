#include "OBJShaderHeader.hlsli"

VSOutput main(float4 pos : POSITION, float3 normal : NORMAL, float2 uv : TEXCOORD)
{
	

	//右、下、奥を向いたライト
	float3 lightdir = float3(1, -1, 1);
	lightdir = normalize(lightdir);
	//ライトの色(白)
	float3 lightcolor = float3(0.5f, 0, 0);
	//ピクセルシェーダーに渡す値
	VSOutput output;
	output.svpos = mul(mat, pos);
	//Lambert反射の計算
	//output.color.rgb = dot(-lightdir, normal) * m_diffuse * lightcolor;
	//output.color.a = m_alpha;
	//output.uv = uv;
	
	
	float intensity =
		saturate(dot(normalize(normal), lightdir));
	//環境反射光
	float3 ambient = m_ambient;
	//拡散反射光
	float3 diffuse = dot(-lightdir, normal) * step(0.1, intensity) * m_diffuse;
	//視点座標
	const float3 eye = float3(0, 0, 0);
	//光沢度
	const float shininess = 20.0f;
	//頂点から視点への方向ベクトル
	float3 eyedir = normalize(eye - pos.xyz);
	//反射光ベクトル
	float3 reflect = -lightdir + 2 * normal * dot(normal, lightdir);
	//鏡面反射光
	float3 specular = pow(saturate(dot(reflect, eyedir)), shininess) * m_specular;
	//全て加算する
	output.color.rgb = (ambient + diffuse + step(0.1,specular)) * lightcolor;
	output.color.a = m_alpha;
	output.uv = uv;

	return output;
}