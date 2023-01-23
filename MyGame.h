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
	//初期化
	void Initialize();
	//終了
	void Finalize();
	//毎フレーム処理
	void Update();
	//描画
	void Draw();
private:

	WinApp* winApp = nullptr;

	DirectXCommon* dxCommon = nullptr;

	Input* input = nullptr;

	SpriteCommon* spriteCommon = nullptr;

	Audio* audio = nullptr;

	ImGuiManager* imGui = nullptr;

	Sprite* sprite = nullptr;

	//OBJからモデルデータを読み込む
	Model* model_1 = Model::LoadFromOBJ("ground");
	Model* model_2 = Model::LoadFromOBJ("triangle_mat");
	//3Dオブジェクト生成
	Object3d* object3d_1 = Object3d::Create();
	Object3d* object3d_2 = Object3d::Create();
	Object3d* object3d_3 = Object3d::Create();
};

