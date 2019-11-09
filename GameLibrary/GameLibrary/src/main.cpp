#include<cassert>
#include<stdexcept>
#include"DxLib.h"

#include"Geometry/Vector2.h"

int WINAPI WinMain(HINSTANCE,HINSTANCE,LPSTR,int){
	try{
		//dxライブラリの初期化
		//画面モードの設定(一応こんな感じ)
		SetGraphMode(960,540,16);
		//ウインドウサイズの変更
		SetWindowSizeExtendRate(1.0);
		//タイトルメニュー文字
		SetMainWindowText("ゲームライブラリのテスト");
		//ウインドウサイズの変更をできるようにする
		SetWindowSizeChangeEnableFlag(TRUE);
		//アイコンの設定
		SetWindowIconID(101);
		//非アクティブ状態での処理の続行のフラグ
		SetAlwaysRunFlag(FALSE);
		//背景色の設定
		SetBackgroundColor(0,0,0);
		//マウス表示設定
		SetMouseDispFlag(TRUE);
		//DXアーカイバの使用
		SetUseDXArchiveFlag(TRUE);
		
		if(ChangeWindowMode(TRUE) != 0) {
			throw(std::runtime_error("ChangeWindowMode(TRUE) failed."));
		}
		if(DxLib_Init() != 0) {
			throw(std::runtime_error("DxLib_Init() failed."));
		}
		if(SetDrawScreen(DX_SCREEN_BACK) != 0) {
			DxLib_End();
			throw(std::runtime_error("SetDrawScreen(DX_SCREEN_BACK) failed."));
		}

		Geometry::Vector2 vf1(1.0f,2.0f),vf2(102.3f,32.4f);
		float f=vf1.CrossSize(vf2);
		Geometry::Vector2Int vi1(1,3),vi2(32,53);
		double d=vi1.Size();
		auto v=Geometry::ConvertToVector2(vi2);

		//ゲーム本体
		while(ScreenFlip() == 0 && ProcessMessage() == 0 && ClearDrawScreen() == 0) {
			//入力情報更新

			//描画
			clsDx();
			DrawBox(40,40,120,120,GetColor(127,127,127),TRUE);

			//情報更新


			//遷移処理


			//終了検出
			
		}

		//素材の解放

		//終了処理
		DxLib_End();
		return 0;
	} catch(const std::exception &e){
		assert(e.what());
		return 1;
	}
}
