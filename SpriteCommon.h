#pragma once
#include <d3d12.h>
#include <wrl.h>
#include "DirectXCommon.h"

//スプライト共通部
class SpriteCommon
{
public://メンバ関数
	//初期化
	void Initialize(DirectXCommon* dxCommon);

	void PreDraw();

	DirectXCommon* GetDirectXCommon() { return dxCommon_; }
private:
	DirectXCommon* dxCommon_;

	Microsoft::WRL::ComPtr<ID3D12PipelineState> pipelineState;

	Microsoft::WRL::ComPtr<ID3D12RootSignature> rootSignature;
};