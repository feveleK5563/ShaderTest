#pragma once
#include "DxLib.h"
#include "TaskSystem.h"
#include "ImageDrawer.h"
#include "Counter.hpp"

namespace TestScene
{
	const std::string	defGroupName	("�e�X�g�p�V�[��");	//�O���[�v��
	const std::string	defTaskName		("�e�X�g�p�^�X�N");	//�^�X�N��
	const float			defPriority(0.f);	//�f�t�H���g�̏����D��x

	//----------------------------------------------
	class Task : public TaskAbstract
	{
	private:
		int pshandle;
		int pscbhandle;
		VERTEX2DSHADER vertex[4];

		Counter<float> timer;
		MATH::Vec2 mousePos;
		bool onClick;

		//�V�F�[�_�[�ɑ���l
		struct constantBuffer
		{
			FLOAT2 windowSize;
			FLOAT2 mousePos;
			float radius;
			bool onClick;
		};

	public:
		//�R���X�g���N�^
		Task();
		
		//�f�X�g���N�^
		~Task();
		
		//�^�X�N�̐���
		static std::shared_ptr<Task> Create();

		void Initialize() override;	//����������
		void Finalize() override;	//�I������
		void Update() override;		//�X�V
		void Draw() override;		//�`��
	};
}