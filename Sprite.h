#pragma once
#include <DirectXMath.h>
#include "SpriteCommon.h"


//スプライト
class Sprite
{
private:
	const int window_width = 1280;
	const int window_height = 720;
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

	void Draw();

private:
	//スプライト情報
	DirectX::XMFLOAT4 color = { 1,0,0,0.5f };

	SpriteCommon* spriteCommon_;

	Microsoft::WRL::ComPtr<ID3D12Resource> vertBuff;

	D3D12_VERTEX_BUFFER_VIEW vbView{};

	Microsoft::WRL::ComPtr<ID3D12Resource> constBuffMaterial;
	ConstBufferDataMaterial* constMapMaterial = nullptr;

	Microsoft::WRL::ComPtr<ID3D12Resource> constBuffTransform;
	ConstBufferDataTransform* constMapTransform = nullptr;
};