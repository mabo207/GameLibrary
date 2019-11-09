#include<cassert>
#include<stdexcept>
#include"DxLib.h"

#include"Geometry/Vector2.h"

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

		Geometry::Vector2 vf1(1.0f,2.0f),vf2(102.3f,32.4f);
		float f=vf1.CrossSize(vf2);
		Geometry::Vector2Int vi1(1,3),vi2(32,53);
		double d=vi1.Size();
		auto v=Geometry::ConvertToVector2(vi2);

		//�Q�[���{��
		while(ScreenFlip() == 0 && ProcessMessage() == 0 && ClearDrawScreen() == 0) {
			//���͏��X�V

			//�`��
			clsDx();
			DrawBox(40,40,120,120,GetColor(127,127,127),TRUE);

			//���X�V


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
