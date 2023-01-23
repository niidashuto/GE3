#pragma once

#include "Input.h"
#include "WinApp.h"
#include "DirectXCommon.h"
#include "SpriteCommon.h"
#include "Sprite.h"
#include "Object3d.h"
#include "Model.h"
#include "ImGuiManager.h"
#include "imgui/imgui.h"
#include "Audio.h"
#include <fstream>
#include <wrl.h>
class MyGame
{
public:
	//������
	void Initialize();
	//�I��
	void Finalize();
	//���t���[������
	void Update();
	//�`��
	void Draw();
private:

	WinApp* winApp = nullptr;

	DirectXCommon* dxCommon = nullptr;

	Input* input = nullptr;

	SpriteCommon* spriteCommon = nullptr;

	Audio* audio = nullptr;

	ImGuiManager* imGui = nullptr;

	Sprite* sprite = nullptr;

	//OBJ���烂�f���f�[�^��ǂݍ���
	Model* model_1 = Model::LoadFromOBJ("ground");
	Model* model_2 = Model::LoadFromOBJ("triangle_mat");
	//3D�I�u�W�F�N�g����
	Object3d* object3d_1 = Object3d::Create();
	Object3d* object3d_2 = Object3d::Create();
	Object3d* object3d_3 = Object3d::Create();
};

