#pragma once

#include "FbxModel.h"
#include "Camera.h"

#include <Windows.h>
#include <wrl.h>
#include <d3d12.h>
#include <d3dx12.h>
#include <DirectXMath.h>
#include <string>

class FbxObject
{
protected://エイリアス
	//Microsoft::WRL::を省略
	template <class T>using ComPtr =
		Microsoft::WRL::ComPtr<T>;
	//DirectXを省略
	using XMFLOAT2 = DirectX::XMFLOAT2;
	using XMFLOAT3 = DirectX::XMFLOAT3;
	using XMFLOAT4 = DirectX::XMFLOAT4;
	using XMMATRIX = DirectX::XMMATRIX;

public:
	struct ConstBufferDataTransform
	{
		XMMATRIX viewproj;
		XMMATRIX world;
		XMFLOAT3 cameraPos;
	};
public://メンバ関数

	void Initialize();
	//setter
	static void SetDevice(ID3D12Device* device) { FbxObject::device_ = device; }

	static void SetCamera(Camera* camera) { FbxObject::camera_ = camera; }
protected:
	ComPtr<ID3D12Resource> constBuffTransform;

private://静的メンバ変数
	//デバイス
	static ID3D12Device* device_;
	//カメラ
	static Camera* camera_;

};

