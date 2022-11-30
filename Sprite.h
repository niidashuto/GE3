#pragma once
#include <DirectXMath.h>
#include "SpriteCommon.h"


//�X�v���C�g
class Sprite
{
public:
	//�萔�o�b�t�@�f�[�^�\����
	struct ConstBufferDataMaterial {
		DirectX::XMFLOAT4 color;
	};

	struct Vertex {
		DirectX::XMFLOAT3 pos;
		DirectX::XMFLOAT2 uv;
	};

public://�����o�֐�
	//������
	void Initialize(SpriteCommon* spriteCommon);

	void Draw();

private:
	//�X�v���C�g���
	DirectX::XMFLOAT4 color = { 1,0,0,0.5f };

	SpriteCommon* spriteCommon_;

	Microsoft::WRL::ComPtr<ID3D12Resource> vertBuff;

	D3D12_VERTEX_BUFFER_VIEW vbView{};

	Microsoft::WRL::ComPtr<ID3D12Resource> constBuffMaterial;
	ConstBufferDataMaterial* constMapMaterial = nullptr;


};