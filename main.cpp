#include "MyGame.h"
#include <fbxsdk.h>

// Windowsアプリでのエントリーポイント(main関数)
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {

    FbxManager* fbxManager = FbxManager::Create();

    SNFramework* game = new MyGame();

    game->Run();

    delete game;

    return 0;
}