#pragma once

#include"Geometry/Vector2.h"
#include<array>

namespace Input{
	//�}�E�X��\������֐�
	class Mouse{
	public:
		//�\����
		enum class ButtonCondition{
			e_free//������Ă��Ȃ�����e_released�łȂ�
			,e_pushed//������Ă���
			,e_released//�����ꂽ�u�Ԃł���
		};

		//�֐�
		Mouse();
		~Mouse()=default;
		void Update();//�ϐ��̍X�V
		//���݂̃}�E�X�̈ʒu�̎擾
		Geometry::Vector2 GetPosition()const;
		Geometry::Vector2Int GetPositionInt()const{
			return m_position;
		}
		//���t���[���ł̃}�E�X���ǂ̂悤�Ɉړ���������2�����x�N�g���Ŏ擾
		Geometry::Vector2 GetMoveVector()const;
		Geometry::Vector2Int GetMoveVectorInt()const{
			return m_move;
		}
		//���t���[���Ń}�E�X�z�C�[�����ǂ̂悤�Ɉړ����������擾
		int GetWheelRotation()const{
			//>0:��ɉ񂵂� <0:���ɉ񂵂�
			return m_wheelRotation;
		}
		//�}�E�X�{�^���Ɋւ���֐�
		size_t GetButtonInputFrame(int buttonCode)const;//�}�E�X�̃{�^�������t���[������������ꂽ�����擾
		ButtonCondition GetButtonCondition(int buttonCode)const;//�}�E�X�̃{�^���̏��

		//�ÓI�ϐ�
		static Mouse s_mouse;//�v���O���������s����Ă���R���s���[�^�ɐڑ�����Ă���}�E�X�i�P�����j

	private:
		//�֐�
		void UpdatePosition();//�ʒu���X�V���鏈����2�ӏ��o�Ă��邽�ߊ֐������Ă���
		size_t GetButtonIndex(int buttonCode)const;//�{�^���R�[�h����z��ԍ����擾���邽�߂̊֐�(�{�^���R�[�h�̓V�t�g���Z�ɓs���̗ǂ��ϐ������蓖�Ă��Ă��ăL���C�ɔz��ԍ����ɂȂ�Ȃ�)
		//�萔
		static const size_t buttonNum=8;
		//�ϐ�
		Geometry::Vector2Int m_position;//�ʒu
		Geometry::Vector2Int m_move;//�ړ��x�N�g��
		std::array<size_t,buttonNum> m_buttonFrame;//�{�^���̓��̓t���[��
		std::array<ButtonCondition,buttonNum> m_buttonCondition;//�{�^���̏��
		int m_wheelRotation;//�z�C�[���̉�]��
	};
}
