#pragma once

#include <d3d12.h>
#include <dxgi1_6.h>
#include <wrl.h>
#include "WinApp.h"
#include <vector>
#include <chrono>

//DirectX基盤
class DirectXCommon
{
public://メンバ関数
	//初期化
	void Initialize(WinApp* winApp);
	//描画前処理
	void PreDraw();
	//描画後処理
	void PostDraw();

	ID3D12Device* GetDevice() const { return device.Get(); }

	ID3D12GraphicsCommandList* GetCommandList() const { return commandList.Get(); }

private://メンバ関数

	void InitializeDevice();

	void InitializeCommand();

	void InitializeSwapChain();

	void InitializeRenderTargetView();

	void InitializeDepthBuffer();

	void InitializeFence();

	//FPS固定初期化
	void InitializeFixFPS();
	//FPS固定更新
	void UpdateFixFPS();

	//記録時間(FPS固定)
	std::chrono::steady_clock::time_point reference_;

private:
	//DirectX12デバイス
	Microsoft::WRL::ComPtr<ID3D12Device> device;
	//DXGIファクトリ
	Microsoft::WRL::ComPtr<IDXGIFactory7> dxgiFactory;

	Microsoft::WRL::ComPtr<ID3D12CommandAllocator> commandAllocator;

	Microsoft::WRL::ComPtr<ID3D12GraphicsCommandList> commandList;

	Microsoft::WRL::ComPtr<ID3D12CommandQueue> commandQueue;

	Microsoft::WRL::ComPtr<IDXGISwapChain4> swapChain;
	//WindowsAPI
	WinApp* winApp = nullptr;
	//バックバッファ
	std::vector<Microsoft::WRL::ComPtr<ID3D12Resource>> backBuffers;
	// フェンスの生成
	Microsoft::WRL::ComPtr<ID3D12Fence> fence;

	DXGI_SWAP_CHAIN_DESC1 swapChainDesc{};

	Microsoft::WRL::ComPtr<ID3D12DescriptorHeap> rtvHeap;

	Microsoft::WRL::ComPtr<ID3D12Resource> depthBuff;

	Microsoft::WRL::ComPtr<ID3D12DescriptorHeap> dsvHeap;

	UINT64 fenceVal = 0;
};