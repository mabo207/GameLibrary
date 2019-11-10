#include<cassert>
#include<stdexcept>
#include"DxLib.h"

#include"Geometry/Vector2.h"
#include"Geometry/Circle.h"
#include"Input/Mouse.h"

int WINAPI WinMain(HINSTANCE,HINSTANCE,LPSTR,int){
	try{
		//dx���C�u�����̏�����
		//��ʃ��[�h�̐ݒ�(�ꉞ����Ȋ���)
		SetGraphMode(960,540,16);
		//�E�C���h�E�T�C�Y�̕ύX
		SetWindowSizeExtendRate(1.0);
		//�^�C�g�����j���[����
		SetMainWindowText("�Q�[�����C�u�����̃e�X�g");
		//�E�C���h�E�T�C�Y�̕ύX���ł���悤�ɂ���
		SetWindowSizeChangeEnableFlag(TRUE);
		//�A�C�R���̐ݒ�
		SetWindowIconID(101);
		//��A�N�e�B�u��Ԃł̏����̑��s�̃t���O
		SetAlwaysRunFlag(FALSE);
		//�w�i�F�̐ݒ�
		SetBackgroundColor(0,0,0);
		//�}�E�X�\���ݒ�
		SetMouseDispFlag(TRUE);
		//DX�A�[�J�C�o�̎g�p
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

		//�Q�[���{��
		while(ScreenFlip() == 0 && ProcessMessage() == 0 && ClearDrawScreen() == 0) {
			//�`��
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

			//���͏��X�V
			Input::Mouse::s_mouse.Update();

			//���X�V
			virtualPlayer.Warp(Input::Mouse::s_mouse.GetPosition());
			Geometry::Vector2 move=Input::Mouse::s_mouse.GetPosition()-player.GetPosition();
			if(move.SqSize()>25.0f){
				move=move.MultipleNorm(5.0f);
			}
			if(Input::Mouse::s_mouse.GetButtonCondition(MOUSE_INPUT_LEFT)!=Input::Mouse::ButtonCondition::e_pushed){
				player.Move(move);
			} else{
				//���}�E�X�{�^�������������̂ݓ����蔻�菈�������Ă݂�
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

			//�J�ڏ���


			//�I�����o

		}

		//�f�ނ̉��

		//�I������
		DxLib_End();
		return 0;
	} catch(const std::exception &e){
		assert(e.what());
		return 1;
	}
}
