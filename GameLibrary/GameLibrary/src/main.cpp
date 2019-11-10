#include<cassert>
#include<stdexcept>
#include"DxLib.h"

#include"Geometry/Vector2.h"
#include"Geometry/Circle.h"
#include"Input/Mouse.h"

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

		Geometry::Circle player(Geometry::Vector2::s_zero,30.0f);
		Geometry::Circle virtualPlayer=player;
		const size_t terrainCount=5;
		const Geometry::Circle c[terrainCount]={
			Geometry::Circle(Geometry::Vector2(130.0f,30.0f),20.0f)
			,Geometry::Circle(Geometry::Vector2(149.0f,230.0f),60.0f)
			,Geometry::Circle(Geometry::Vector2(135.0f,165.0f),70.0f)
			,Geometry::Circle(Geometry::Vector2(420.0f,300.0f),100.0f)
			,Geometry::Circle(Geometry::Vector2(750.0f,200.0f),200.0f)
		};

		//ゲーム本体
		while(ScreenFlip() == 0 && ProcessMessage() == 0 && ClearDrawScreen() == 0) {
			//描画
			clsDx();
			player.Shape::Draw(GetColor(128,128,255),TRUE,1.0f);
			virtualPlayer.Shape::Draw(GetColor(64,64,196),FALSE,5.0f);
			for(const Geometry::Circle &circle:c){
				unsigned int color;
				if(virtualPlayer.JudgeCross(&circle)){
					color=GetColor(255,0,0);
				} else{
					color=GetColor(255,255,0);
				}
				circle.Shape::Draw(color,FALSE,3.0f);
			}

			//入力情報更新
			Input::Mouse::s_mouse.Update();

			//情報更新
			virtualPlayer.Warp(Input::Mouse::s_mouse.GetPosition());
			Geometry::Vector2 move=Input::Mouse::s_mouse.GetPosition()-player.GetPosition();
			if(move.SqSize()>25.0f){
				move=move.MultipleNorm(5.0f);
			}
			if(Input::Mouse::s_mouse.GetButtonCondition(MOUSE_INPUT_LEFT)!=Input::Mouse::ButtonCondition::e_pushed){
				player.Move(move);
			} else{
				//左マウスボタンを押した時のみ当たり判定処理をしてみる
				Geometry::Vector2 totalFeedback=Geometry::Vector2::s_zero;
				const size_t calcCount=25;
				const float moveRate=1.0f/((float)calcCount);
				const Geometry::Vector2 miniMove=move*moveRate;
				for(size_t j=0;j<calcCount;j++){
					for(size_t i=0;i<terrainCount;i++){
						totalFeedback+=c[i].CalculateFeedback(&player,miniMove);
					}
					player.Move(miniMove+totalFeedback*moveRate);
				}
			}

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
