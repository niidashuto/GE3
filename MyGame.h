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
#include "SNFramework.h"

class MyGame : public SNFramework
{
public:
	//初期化
	void Initialize() override;
	//終了
	void Finalize() override;
	//毎フレーム処理
	void Update() override;
	//描画
	void Draw() override;

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

