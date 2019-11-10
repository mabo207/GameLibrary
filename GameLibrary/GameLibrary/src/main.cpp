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

		Geometry::Vector2 vf1(1.0f,2.0f),vf2(102.3f,32.4f);
		float f=vf1.CrossSize(vf2);
		Geometry::Vector2Int vi1(1,3),vi2(32,53);
		double d=vi1.Size();
		auto v=Geometry::ConvertToVector2(vi2);
		const size_t circleCount=5;
		const Geometry::Circle c[circleCount]={
			Geometry::Circle(Geometry::Vector2(30.0f,30.0f),20.0f)
			,Geometry::Circle(Geometry::Vector2(49.0f,30.0f),20.0f)
			,Geometry::Circle(Geometry::Vector2(35.0f,65.0f),20.0f)
			,Geometry::Circle(Geometry::Vector2(120.0f,200.0f),100.0f)
			,Geometry::Circle(Geometry::Vector2(950.0f,300.0f),600.0f)
		};

		//ゲーム本体
		while(ScreenFlip() == 0 && ProcessMessage() == 0 && ClearDrawScreen() == 0) {
			//描画
			clsDx();
			for(const Geometry::Circle &circle:c){
				circle.Shape::Draw(GetColor(255,0,0),FALSE,3.0f);
			}
			DrawBox(40,40,120,120,GetColor(127,127,127),TRUE);
			printfDx("mouse:(%f,%f)\n",Input::Mouse::s_mouse.GetPosition().x,Input::Mouse::s_mouse.GetPosition().y);
			switch(Input::Mouse::s_mouse.GetButtonCondition(MOUSE_INPUT_LEFT)){
			case(Input::Mouse::ButtonCondition::e_free):
				printfDx("left free\n");
				break;
			case(Input::Mouse::ButtonCondition::e_pushed):
				printfDx("left pushed\n");
				break;
			case(Input::Mouse::ButtonCondition::e_released):
				printfDx("left released\n");
				break;
			}
			printfDx("right frame:%d\n",Input::Mouse::s_mouse.GetButtonInputFrame(MOUSE_INPUT_RIGHT));
			printfDx("wheel rot:%d\n",Input::Mouse::s_mouse.GetWheelRotation());

			//入力情報更新
			Input::Mouse::s_mouse.Update();

			//情報更新
			for(size_t i=0;i+1<circleCount;i++){
				for(size_t j=i+1;j<circleCount;j++){
					Geometry::Vector2 feedback=c[i].CalculateFeedback(&c[j],Geometry::Vector2(1.0f,0.0f));
					printfDx("[%d][%d]:cross(%s),feedback(%f,%f)\n",i,j,(c[i].JudgeCross(&c[j])?"true":"false"),feedback.x,feedback.y);
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
