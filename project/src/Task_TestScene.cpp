#include "Task_TestScene.h"
#include "ImageLoader.h"
#include "InputState.h"
#include "SystemDefine.h"

namespace TestScene
{
	std::weak_ptr<Resource> Resource::instance;
	//----------------------------------------------
	//\[XÌRXgN^
	Resource::Resource()
	{
		auto& imageLoader = ImageLoader::GetInstance();
		imageName = "Art";
		imageLoader.LoadOneImage(imageName, "data/image/art.png");
	}
	//----------------------------------------------
	//\[XÌfXgN^
	Resource::~Resource()
	{
		auto& imageLoader = ImageLoader::GetInstance();
		imageLoader.DeleteImageData(imageName);
	}
	//----------------------------------------------
	//\[XÌĥĴ
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

	//
	//

	//----------------------------------------------
	//^XNÌRXgN^
	Task::Task():
		TaskAbstract(defGroupName, defTaskName, defPriority),
		res(Resource::Create()),
		timer(40.f),
		mousePos(0, 0),
		onClick(false)
	{
	}
	//----------------------------------------------
	//^XNÌfXgN^
	Task::~Task()
	{

	}
	//----------------------------------------------
	//^XNÌĥĴ
	std::shared_ptr<Task> Task::Create()
	{
		std::shared_ptr<Task> task = 
			std::make_shared<Task>();
		TaskSystem::GetInstance().AddTask(task);

		task->Initialize();
		return task;
	}

	//
	//

	//----------------------------------------------
	//úğ
	//----------------------------------------------
	void Task::Initialize()
	{
		graph = LoadGraph("data/image/art2.png");
		shaderhandle = LoadPixelShader("data/shader/circle.pso");

		float x = (float)SYSDEF::SizeX, y = (float)SYSDEF::SizeY;
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
	//Iı
	//----------------------------------------------
	void Task::Finalize()
	{

	}

	//----------------------------------------------
	//XV
	//----------------------------------------------
	void Task::Update()
	{
		timer.Run();

		auto& mouse = InputDXL::GetMouse();
		if (mouse[MouseButton::LEFT] == DOWN)
		{
			mousePos = mouse.GetPos();
			onClick = !onClick;
			timer.Reset();
		}
	}

	//----------------------------------------------
	//`ĉ
	//----------------------------------------------
	void Task::Draw()
	{
		float tmp[6]{ 
			(float)SYSDEF::SizeX,	//ĉÊTCYX
			(float)SYSDEF::SizeY,	//ĉÊTCYY
			timer.GetNow(),			//Ô
			(float)onClick,			//NbNµ½İÛİ
			mousePos.x,				//}EXÀWX
			mousePos.y				//}EXÀWY
		};

		SetPSConstSFArray(0, tmp, 6);


		//sNZVF[_ÌZbg
		SetUsePixelShader(shaderhandle);
		//`ĉ
		DrawPrimitive2DToShader(vertex, 4, DX_PRIMTYPE_TRIANGLESTRIP);
	}
}