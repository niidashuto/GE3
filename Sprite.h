#pragma once
#include <DirectXMath.h>
#include "SpriteCommon.h"


//スプライト
class Sprite
{
public:
	//定数バッファデータ構造体(マテリアル)
	struct ConstBufferDataMaterial {
		DirectX::XMFLOAT4 color;
	};

	//定数バッファデータ構造体(3D変換行列)
	struct ConstBufferDataTransform {
		DirectX::XMMATRIX mat;//3D変換行列
	};

	//頂点データ
	struct Vertex {
		DirectX::XMFLOAT3 pos;
		DirectX::XMFLOAT2 uv;
	};

public://メンバ関数
	//初期化
	void Initialize(SpriteCommon* spriteCommon);

	void Update();

	void Draw();

private:
	//スプライト情報
	DirectX::XMFLOAT4 color = { 1,0,0,0.5f };

	float rotationZ;
	DirectX::XMFLOAT3 position;

	SpriteCommon* spriteCommon_;

	Microsoft::WRL::ComPtr<ID3D12Resource> vertBuff;

	D3D12_VERTEX_BUFFER_VIEW vbView{};

	Microsoft::WRL::ComPtr<ID3D12Resource> constBuffMaterial;
	ConstBufferDataMaterial* constMapMaterial = nullptr;

	Microsoft::WRL::ComPtr<ID3D12Resource> constBuffTransform;
	ConstBufferDataTransform* constMapTransform = nullptr;
};