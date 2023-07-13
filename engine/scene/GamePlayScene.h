#pragma once
#include "SpriteCommon.h"
#include "Object3d.h"
#include "ParticleManager.h"
#include "DirectXCommon.h"
#include "Audio.h"

class GamePlayScene
{
public://�����o�֐�

	//������
	void Initialize();

	//�I��
	void Finalize();

	//���t���[������
	void Update();

	//�`��
	void Draw();

private:

	static DirectXCommon* dxCommon_;

	static SpriteCommon* spriteCommon_;

};

