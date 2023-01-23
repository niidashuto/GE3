#include "MyGame.h"


// Windowsアプリでのエントリーポイント(main関数)
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {

    MyGame game;

    //ゲームの初期化
    game.Initialize();

    // ゲームループ
    while (true) {

    }

    return 0;
}