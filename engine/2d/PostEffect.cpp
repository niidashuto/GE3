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


	//�p�C�v���C���X�e�[�g�̐ݒ�
	cmdList->SetPipelineState(spriteCommon_->GetPipeLineState());

	cmdList->SetGraphicsRootSignature(spriteCommon_->GetRootSignature());

	cmdList->IASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);

	//�e�N�X�`���R�}���h
	spriteCommon_->SetTextureCommands(textureIndex_);

	//���_�o�b�t�@�r���[�̐ݒ�R�}���h
	spriteCommon_->GetDirectXCommon()->GetCommandList()->IASetVertexBuffers(0, 1, &vbView);
	//�萔�o�b�t�@�r���[(CBV)�̐ݒ�R�}���h
	spriteCommon_->GetDirectXCommon()->GetCommandList()->SetGraphicsRootConstantBufferView(0, constBuffMaterial->GetGPUVirtualAddress());
	spriteCommon_->GetDirectXCommon()->GetCommandList()->SetGraphicsRootConstantBufferView(2, constBuffTransform->GetGPUVirtualAddress());
	//�`��R�}���h
	spriteCommon_->GetDirectXCommon()->GetCommandList()->DrawInstanced(4, 1, 0, 0);//�S�Ă̒��_���g���ĕ`��
}
