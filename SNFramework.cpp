#include "SNFramework.h"

void SNFramework::Initialize()
{
}

void SNFramework::Finalize()
{
}

void SNFramework::Update()
{
}

void SNFramework::Run()
{
	//ゲームの初期化
	Initialize();

	while (true)//ゲームループ
	{
		//毎フレーム更新
		Update();
		//終了リクエストが来たら抜ける
		if (IsEndRequest())
		{
			break;
		}
		//描画
		Draw();
	}
	//ゲームの終了
	Finalize();
}
