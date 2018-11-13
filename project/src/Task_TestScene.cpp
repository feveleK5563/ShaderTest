#include "Task_TestScene.h"
#include "ImageLoader.h"
#include "InputState.h"
#include "SystemDefine.h"

namespace TestScene
{
	std::weak_ptr<Resource> Resource::instance;
	//----------------------------------------------
	//���\�[�X�̃R���X�g���N�^
	Resource::Resource()
	{
		auto& imageLoader = ImageLoader::GetInstance();
		imageName = "Art";
		imageLoader.LoadOneImage(imageName, "data/image/art.png");
	}
	//----------------------------------------------
	//���\�[�X�̃f�X�g���N�^
	Resource::~Resource()
	{
		auto& imageLoader = ImageLoader::GetInstance();
		imageLoader.DeleteImageData(imageName);
	}
	//----------------------------------------------
	//���\�[�X�̐���
	std::shared_ptr<Resource> Resource::Create()
	{
		auto sp = instance.lock();
		if (!sp)
		{
			sp = std::make_shared<Resource>();
			instance = sp;
		}
		return sp;
	}

	//��������������������������������������������������������������������������������������������
	//��������������������������������������������������������������������������������������������

	//----------------------------------------------
	//�^�X�N�̃R���X�g���N�^
	Task::Task():
		TaskAbstract(defGroupName, defTaskName, defPriority),
		res(Resource::Create())
	{
	}
	//----------------------------------------------
	//�^�X�N�̃f�X�g���N�^
	Task::~Task()
	{

	}
	//----------------------------------------------
	//�^�X�N�̐���
	std::shared_ptr<Task> Task::Create()
	{
		std::shared_ptr<Task> task = 
			std::make_shared<Task>();
		TaskSystem::GetInstance().AddTask(task);

		task->Initialize();
		return task;
	}

	//��������������������������������������������������������������������������������������������
	//��������������������������������������������������������������������������������������������

	//----------------------------------------------
	//����������
	//----------------------------------------------
	void Task::Initialize()
	{
		graph = LoadGraph("data/image/art2.png");
		shaderhandle = LoadPixelShader("data/shader/test.pso");

		float x = 1280.f, y = 720;
		vertex[0].pos = VGet(-1.f,	-1.f,	0.f);
		vertex[1].pos = VGet(x,		-1.f,	0.f);
		vertex[2].pos = VGet(-1.f,	y,		0.f);
		vertex[3].pos = VGet(x,		y,		0.f);

		for (int i = 0; i < 4; ++i)
		{
			vertex[i].rhw = 1.f;
			vertex[i].dif = GetColorU8(255, 255, 255, 255);
			vertex[i].spc = GetColorU8(0, 0, 0, 0);
			vertex[i].u  = float(i % 2);
			vertex[i].su = float(i % 2);
			vertex[i].v  = float(i / 2);
			vertex[i].sv = float(i / 2);
		}
	}

	//----------------------------------------------
	//�I������
	//----------------------------------------------
	void Task::Finalize()
	{

	}

	//----------------------------------------------
	//�X�V
	//----------------------------------------------
	void Task::Update()
	{

	}

	//----------------------------------------------
	//�`��
	//----------------------------------------------
	void Task::Draw()
	{
		//DrawGraph(0, 0, graph, false);

		//SetUseDivGraphFlag(FALSE);
		//�V�F�[�_�Ŏg���e�N�X�`�����Z�b�g
		SetUseTextureToShader(0, graph);
		//�s�N�Z���V�F�[�_�̃Z�b�g
		SetUsePixelShader(shaderhandle);
		//�`��
		DrawPrimitive2DToShader(vertex, 4, DX_PRIMTYPE_TRIANGLESTRIP);
	}
}