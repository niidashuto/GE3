#include "PostEffect.h"
#include <d3dx12.h>


using namespace DirectX;

PostEffect::PostEffect()
	:Sprite()
{

}

void PostEffect::Draw(ID3D12GraphicsCommandList* cmdList)
{
	if (isInvisible_)
	{
		return;
	}


	//パイプラインステートの設定
	cmdList->SetPipelineState(spriteCommon_->GetPipeLineState());

	cmdList->SetGraphicsRootSignature(spriteCommon_->GetRootSignature());

	cmdList->IASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);

	//テクスチャコマンド
	spriteCommon_->SetTextureCommands(textureIndex_);

	//頂点バッファビューの設定コマンド
	spriteCommon_->GetDirectXCommon()->GetCommandList()->IASetVertexBuffers(0, 1, &vbView);
	//定数バッファビュー(CBV)の設定コマンド
	spriteCommon_->GetDirectXCommon()->GetCommandList()->SetGraphicsRootConstantBufferView(0, constBuffMaterial->GetGPUVirtualAddress());
	spriteCommon_->GetDirectXCommon()->GetCommandList()->SetGraphicsRootConstantBufferView(2, constBuffTransform->GetGPUVirtualAddress());
	//描画コマンド
	spriteCommon_->GetDirectXCommon()->GetCommandList()->DrawInstanced(4, 1, 0, 0);//全ての頂点を使って描画
}
