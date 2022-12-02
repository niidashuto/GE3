#pragma once
#include <DirectXMath.h>
#include "SpriteCommon.h"


//�X�v���C�g
class Sprite
{
private:
	const int window_width = 1280;
	const int window_height = 720;
public:
	//�萔�o�b�t�@�f�[�^�\����(�}�e���A��)
	struct ConstBufferDataMaterial {
		DirectX::XMFLOAT4 color;
	};

	//�萔�o�b�t�@�f�[�^�\����(3D�ϊ��s��)
	struct ConstBufferDataTransform {
		DirectX::XMMATRIX mat;//3D�ϊ��s��
	};

	//���_�f�[�^
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

	Microsoft::WRL::ComPtr<ID3D12Resource> constBuffTransform;
	ConstBufferDataTransform* constMapTransform = nullptr;
};