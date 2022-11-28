#pragma once
#include <DirectXMath.h>
#include "SpriteCommon.h"


//スプライト
class Sprite
{
public://メンバ関数
	//初期化
	void Initialize(SpriteCommon* spriteCommon);

	void Draw();

private:
	SpriteCommon* spriteCommon_;

	Microsoft::WRL::ComPtr<ID3D12Resource> vertBuff;

	D3D12_VERTEX_BUFFER_VIEW vbView{};
};