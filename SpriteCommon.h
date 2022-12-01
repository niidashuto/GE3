#pragma once
#include <DirectXMath.h>
#include <d3d12.h>
#include <wrl.h>

#include "DirectXCommon.h"

//�X�v���C�g���ʕ�
class SpriteCommon
{
public:
	//�������s�N�Z����
	const size_t textureWidth = 256;
	//�c�����s�N�Z����
	const size_t textureHeight = 256;
	//�z��̗v�f��
	const size_t imageDataCount = textureWidth * textureHeight;
public://�����o�֐�
	//������
	void Initialize(DirectXCommon* dxCommon);

	void PreDraw();

	DirectXCommon* GetDirectXCommon() { return dxCommon_; }
private:
	DirectXCommon* dxCommon_;

	Microsoft::WRL::ComPtr<ID3D12PipelineState> pipelineState;

	Microsoft::WRL::ComPtr<ID3D12RootSignature> rootSignature;

	Microsoft::WRL::ComPtr<ID3D12Resource> texBuff;

	Microsoft::WRL::ComPtr<ID3D12DescriptorHeap> srvHeap;
	//�摜
	DirectX::XMFLOAT4* imageData;
};