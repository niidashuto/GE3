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

	//終了フラグのチェック
	bool IsEndRequest() { return endRequest_; }
private:

	WinApp* winApp = nullptr;

	DirectXCommon* dxCommon = nullptr;

	Input* input = nullptr;

	SpriteCommon* spriteCommon = nullptr;

	Audio* audio = nullptr;

	ImGuiManager* imGui = nullptr;

	Sprite* sprite = nullptr;

	Model* model_1 = nullptr;
	Model* model_2 = nullptr;

	//3Dオブジェクト生成
	Object3d* object3d_1 = nullptr;
	Object3d* object3d_2 = nullptr;
	Object3d* object3d_3 = nullptr;

	//ゲーム終了フラグ
	bool endRequest_ = false;

};

