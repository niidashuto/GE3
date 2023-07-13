#pragma once
#include "SpriteCommon.h"
#include "Object3d.h"
#include "ParticleManager.h"
#include "DirectXCommon.h"
#include "Audio.h"

class GamePlayScene
{
public://メンバ関数

	//初期化
	void Initialize();

	//終了
	void Finalize();

	//毎フレーム処理
	void Update();

	//描画
	void Draw();

private:

	static DirectXCommon* dxCommon_;

	static SpriteCommon* spriteCommon_;

};

