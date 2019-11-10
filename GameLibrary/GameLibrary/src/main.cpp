#include<cassert>
#include<stdexcept>
#include"DxLib.h"

#include"Geometry/Vector2.h"
#include"Geometry/Circle.h"
#include"Geometry/Edge.h"
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

		std::shared_ptr<Geometry::Shape> player(new Geometry::Edge(Geometry::Vector2::s_zero,Geometry::Vector2(30.0f,40.0f)));
		std::shared_ptr<Geometry::Shape> virtualPlayer=player->Copy();
		const size_t terrainCount=9;
		const std::array<std::shared_ptr<Geometry::Shape>,terrainCount> shapeList={
			std::shared_ptr<Geometry::Shape>(new Geometry::Circle(Geometry::Vector2(130.0f,30.0f),20.0f))
			,std::shared_ptr<Geometry::Shape>(new Geometry::Circle(Geometry::Vector2(149.0f,230.0f),60.0f))
			,std::shared_ptr<Geometry::Shape>(new Geometry::Circle(Geometry::Vector2(135.0f,165.0f),70.0f))
			,std::shared_ptr<Geometry::Shape>(new Geometry::Circle(Geometry::Vector2(420.0f,300.0f),100.0f))
			,std::shared_ptr<Geometry::Shape>(new Geometry::Circle(Geometry::Vector2(750.0f,200.0f),200.0f))
			,std::shared_ptr<Geometry::Shape>(new Geometry::Edge(Geometry::Edge::CreateWith2Point(Geometry::Vector2(20.0f,480.0f),Geometry::Vector2(180.0f,440.0f))))
			,std::shared_ptr<Geometry::Shape>(new Geometry::Edge(Geometry::Edge::CreateWith2Point(Geometry::Vector2(820.0f,80.0f),Geometry::Vector2(630.0f,90.0f))))
			,std::shared_ptr<Geometry::Shape>(new Geometry::Edge(Geometry::Edge::CreateWith2Point(Geometry::Vector2(530.0f,280.0f),Geometry::Vector2(590.0f,140.0f))))
			,std::shared_ptr<Geometry::Shape>(new Geometry::Edge(Geometry::Edge::CreateWith2Point(Geometry::Vector2(320.0f,500.0f),Geometry::Vector2(220.0f,460.0f))))
		};

		//ゲーム本体
		while(ScreenFlip() == 0 && ProcessMessage() == 0 && ClearDrawScreen() == 0) {
			//描画
			clsDx();
			player->Draw(GetColor(128,255,128),TRUE,5.0f);
			virtualPlayer->Draw(GetColor(64,64,196),FALSE,5.0f);
			for(const std::shared_ptr<Geometry::Shape> &shape:shapeList){
				unsigned int color;
				if(virtualPlayer->JudgeCross(shape.get())){
					color=GetColor(255,0,0);
				} else{
					color=GetColor(255,255,0);
				}
				shape->Draw(color,FALSE,3.0f);
				//垂直成分を描画してみる
				Geometry::Vector2 vertical=(Input::Mouse::s_mouse.GetPosition()-shape->GetPosition()).VerticalComponent(shape->GetResizeBaseVector());
				Geometry::Vector2 p1=shape->GetPosition();
				Geometry::Vector2 p2=p1+vertical;
				DrawLineAA(p1.x,p1.y,p2.x,p2.y,GetColor(128,128,255),2.0f);
			}

			//入力情報更新
			Input::Mouse::s_mouse.Update();

			//情報更新
			virtualPlayer->Warp(Input::Mouse::s_mouse.GetPosition());
			Geometry::Vector2 move=Input::Mouse::s_mouse.GetPosition()-player->GetPosition();
			if(move.SqSize()>25.0f){
				move=move.MultipleNorm(5.0f);
			}
			if(Input::Mouse::s_mouse.GetButtonCondition(MOUSE_INPUT_LEFT)!=Input::Mouse::ButtonCondition::e_pushed){
				player->Move(move);
			} else{
				//左マウスボタンを押した時のみ当たり判定処理をしてみる
				//理論上、合計の押し出し割合は(1-(1-feedbackRate)^calcCount)となる
				const size_t calcCount=25;//計算回数、多いほど計算が正確になり合計押し出し割合が1に近づくが重くなる
				const float feedbackRate=0.4f;//１回当たりの押し出し割合、大きいほど計算の正確性が低くなる
				//フィードバック分移動する
				for(size_t j=0;j<calcCount;j++){
					Geometry::Vector2 totalFeedback=Geometry::Vector2::s_zero;
					for(const std::shared_ptr<Geometry::Shape> &shape:shapeList){
						totalFeedback+=shape->CalculateFeedback(player.get(),move);
					}
					player->Move(totalFeedback*feedbackRate);
				}
				//フィードバック分の移動後、move分移動
				player->Move(move);
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
