#include "OBJShaderHeader.hlsli"

VSOutput main(float4 pos : POSITION, float3 normal : NORMAL, float2 uv : TEXCOORD)
{
	

	//�E�A���A�������������C�g
	float3 lightdir = float3(1, -1, 1);
	lightdir = normalize(lightdir);
	//���C�g�̐F(��)
	float3 lightcolor = float3(0.5f, 0, 0);
	//�s�N�Z���V�F�[�_�[�ɓn���l
	VSOutput output;
	output.svpos = mul(mat, pos);
	//Lambert���˂̌v�Z
	//output.color.rgb = dot(-lightdir, normal) * m_diffuse * lightcolor;
	//output.color.a = m_alpha;
	//output.uv = uv;
	
	
	float intensity =
		saturate(dot(normalize(normal), lightdir));
	//�����ˌ�
	float3 ambient = m_ambient;
	//�g�U���ˌ�
	float3 diffuse = dot(-lightdir, normal) * step(0.1, intensity) * m_diffuse;
	//���_���W
	const float3 eye = float3(0, 0, 0);
	//����x
	const float shininess = 20.0f;
	//���_���王�_�ւ̕����x�N�g��
	float3 eyedir = normalize(eye - pos.xyz);
	//���ˌ��x�N�g��
	float3 reflect = -lightdir + 2 * normal * dot(normal, lightdir);
	//���ʔ��ˌ�
	float3 specular = pow(saturate(dot(reflect, eyedir)), shininess) * m_specular;
	//�S�ĉ��Z����
	output.color.rgb = (ambient + diffuse + step(0.1,specular)) * lightcolor;
	output.color.a = m_alpha;
	output.uv = uv;

	return output;
}