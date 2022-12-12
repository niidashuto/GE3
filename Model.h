#pragma once
#include <d3d12.h>
#include <wrl.h>
#include <DirectXMath.h>
#include <string>
#include <vector>
#include <d3dx12.h>

using namespace DirectX;

//3Dモデル
class Model
{
public:
	//マテリアル
	struct Material
	{
		std::string name;//マテリアル名
		XMFLOAT3 ambient;//アンビエント影響度
		XMFLOAT3 diffuse;//ディフューズ影響度
		XMFLOAT3 specular;//スペキュラー影響度
		float alpha;//アルファ
		std::string textureFilename;//テクスチャファイル名
		//コンストラクタ
		Material() {
			ambient = { 0.3f,0.3f,0.3f };
			diffuse = { 0.0f,0.0f,0.0f };
			specular = { 0.0f,0.0f,0.0f };
			alpha = 1.0f;
		}
	};
	// 頂点データ構造体
	struct VertexPosNormalUv
	{
		XMFLOAT3 pos; // xyz座標
		XMFLOAT3 normal; // 法線ベクトル
		XMFLOAT2 uv;  // uv座標
	};

public://静的メンバ関数
	//OBJファイルから3Dモデルを読み込む
	static Model* LoadFromOBJ();

private:
	/// <summary>
	/// マテリアル読み込み
	/// </summary>
	void LoadMaterial(const std::string& directoryPath, const std::string& filename);

	/// <summary>
	/// テクスチャ読み込み
	/// </summary>
	void LoadTexture(const std::string& directoryPath, const std::string& filename);

	/// <summary>
	/// デスクリプタヒープの初期化
	/// </summary>
	void InitializeDescriptorHeap();

	/// <summary>
	/// 各種バッファ生成
	/// </summary>
	void CreateBuffers();

private://メンバ変数
	// 頂点インデックス配列
	std::vector<unsigned short> indices;

	//マテリアル
	Material material;

	//頂点データ配列
	std::vector<VertexPosNormalUv> vertices;

	// テクスチャバッファ
	Microsoft::WRL::ComPtr<ID3D12Resource> texbuff;

	// シェーダリソースビューのハンドル(CPU)
	CD3DX12_CPU_DESCRIPTOR_HANDLE cpuDescHandleSRV;
	// シェーダリソースビューのハンドル(CPU)
	CD3DX12_GPU_DESCRIPTOR_HANDLE gpuDescHandleSRV;
	// デスクリプタヒープ
	Microsoft::WRL::ComPtr<ID3D12DescriptorHeap> descHeap;
	// デスクリプタサイズ
	UINT descriptorHandleIncrementSize;
	// 頂点バッファ
	Microsoft::WRL::ComPtr<ID3D12Resource> vertBuff;
	// インデックスバッファ
	Microsoft::WRL::ComPtr<ID3D12Resource> indexBuff;
	// 頂点バッファビュー
	D3D12_VERTEX_BUFFER_VIEW vbView;
	// インデックスバッファビュー
	D3D12_INDEX_BUFFER_VIEW ibView;
private://静的メンバ変数
	//デバイス
	static ID3D12Device* device;

private://非公開のメンバ関数
	//OBJファイルから3Dモデルを読み込む(非公開)
	void LoadFromOBJInternal();
public:
	//setter
	static void SetDevice(ID3D12Device* device) { Model::device = device; }
};