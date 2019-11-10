#include<cassert>
#include<stdexcept>
#include"DxLib.h"

#include"Geometry/Vector2.h"
#include"Geometry/Circle.h"
#include"Geometry/Edge.h"
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

		//�Q�[���{��
		while(ScreenFlip() == 0 && ProcessMessage() == 0 && ClearDrawScreen() == 0) {
			//�`��
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
				//����������`�悵�Ă݂�
				Geometry::Vector2 vertical=(Input::Mouse::s_mouse.GetPosition()-shape->GetPosition()).VerticalComponent(shape->GetResizeBaseVector());
				Geometry::Vector2 p1=shape->GetPosition();
				Geometry::Vector2 p2=p1+vertical;
				DrawLineAA(p1.x,p1.y,p2.x,p2.y,GetColor(128,128,255),2.0f);
			}

			//���͏��X�V
			Input::Mouse::s_mouse.Update();

			//���X�V
			virtualPlayer->Warp(Input::Mouse::s_mouse.GetPosition());
			Geometry::Vector2 move=Input::Mouse::s_mouse.GetPosition()-player->GetPosition();
			if(move.SqSize()>25.0f){
				move=move.MultipleNorm(5.0f);
			}
			if(Input::Mouse::s_mouse.GetButtonCondition(MOUSE_INPUT_LEFT)!=Input::Mouse::ButtonCondition::e_pushed){
				player->Move(move);
			} else{
				//���}�E�X�{�^�������������̂ݓ����蔻�菈�������Ă݂�
				//���_��A���v�̉����o��������(1-(1-feedbackRate)^calcCount)�ƂȂ�
				const size_t calcCount=25;//�v�Z�񐔁A�����قǌv�Z�����m�ɂȂ荇�v�����o��������1�ɋ߂Â����d���Ȃ�
				const float feedbackRate=0.4f;//�P�񓖂���̉����o�������A�傫���قǌv�Z�̐��m�����Ⴍ�Ȃ�
				//�t�B�[�h�o�b�N���ړ�����
				for(size_t j=0;j<calcCount;j++){
					Geometry::Vector2 totalFeedback=Geometry::Vector2::s_zero;
					for(const std::shared_ptr<Geometry::Shape> &shape:shapeList){
						totalFeedback+=shape->CalculateFeedback(player.get(),move);
					}
					player->Move(totalFeedback*feedbackRate);
				}
				//�t�B�[�h�o�b�N���̈ړ���Amove���ړ�
				player->Move(move);
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
