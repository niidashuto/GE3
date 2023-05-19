#pragma once
#include "Sprite.h"
//#include "SpriteCommon.h"

class PostEffect :
    public Sprite
{
public:
    PostEffect();

    void Draw(ID3D12GraphicsCommandList* cmdList);
private:
    //Microsoft::WRL::ComPtr<ID3D12PipelineState> pipelineState;

    //Microsoft::WRL::ComPtr<ID3D12RootSignature> rootSignature;

   
};

