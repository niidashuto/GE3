#pragma once
#include <DirectXMath.h>
#include "SpriteCommon.h"


//スプライト
class Sprite
{
public:
	//定数バッファデータ構造体
	struct ConstBufferDataMaterial {
		DirectX::XMFLOAT4 color;
	};

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


};