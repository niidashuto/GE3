#pragma once
#include "Sprite.h"
#include "SpriteCommon.h"


class PostEffect :
    public Sprite
{
public:
    PostEffect();

    void Initialize(SpriteCommon* spriteCommon_, uint32_t textureIndex);

    void Draw(ID3D12GraphicsCommandList* cmdList);
protected:
    //Microsoft::WRL::ComPtr<ID3D12PipelineState> pipelineState;

    //Microsoft::WRL::ComPtr<ID3D12RootSignature> rootSignature;

    Microsoft::WRL::ComPtr<ID3D12Resource> texBuff;

    Microsoft::WRL::ComPtr<ID3D12DescriptorHeap> descHeapSRV;
public:
    ID3D12DescriptorHeap* GetDescriptorHeap() { return descHeapSRV.Get(); }

   
};

