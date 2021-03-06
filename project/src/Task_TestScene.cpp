#include "Task_TestScene.h"
#include "ImageLoader.h"
#include "InputState.h"
#include "SystemDefine.h"

namespace TestScene
{
	//☆★☆★☆★☆★☆★☆★☆★☆★☆★☆★☆★☆★☆★☆★☆★☆★☆★☆★☆★☆★☆★☆★☆★
	//★☆★☆★☆★☆★☆★☆★☆★☆★☆★☆★☆★☆★☆★☆★☆★☆★☆★☆★☆★☆★☆★☆★☆

	//----------------------------------------------
	//タスクのコンストラクタ
	Task::Task():
		TaskAbstract(defGroupName, defTaskName, defPriority),
		timer(40.f),
		mousePos(0, 0),
		onClick(false)
	{
	}
	//----------------------------------------------
	//タスクのデストラクタ
	Task::~Task()
	{

	}
	//----------------------------------------------
	//タスクの生成
	std::shared_ptr<Task> Task::Create()
	{
		std::shared_ptr<Task> task = 
			std::make_shared<Task>();
		TaskSystem::GetInstance().AddTask(task);

		task->Initialize();
		return task;
	}

	//◇◆◇◆◇◆◇◆◇◆◇◆◇◆◇◆◇◆◇◆◇◆◇◆◇◆◇◆◇◆◇◆◇◆◇◆◇◆◇◆◇◆◇◆◇◆
	//◆◇◆◇◆◇◆◇◆◇◆◇◆◇◆◇◆◇◆◇◆◇◆◇◆◇◆◇◆◇◆◇◆◇◆◇◆◇◆◇◆◇◆◇◆◇

	//----------------------------------------------
	//初期化処理
	//----------------------------------------------
	void Task::Initialize()
	{
		//constantBufferのサイズは24だが、なんか2の累乗じゃないと正常に確保してくれないっぽいので32だけ確保
		pscbhandle = CreateShaderConstantBuffer(32);
		pshandle = LoadPixelShader("data/shader11/circle.pso");

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
	//終了処理
	//----------------------------------------------
	void Task::Finalize()
	{
		DeleteShader(pshandle);
		DeleteShaderConstantBuffer(pscbhandle);
	}

	//----------------------------------------------
	//更新
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
	//描画
	//----------------------------------------------
	void Task::Draw()
	{
		//ピクセルシェーダー用の定数バッファのアドレスを取得
		constantBuffer* cb = (constantBuffer*)GetBufferShaderConstantBuffer(pscbhandle);

		//各値を取得したアドレスに書き込み
		cb->windowSize.u = (float)SYSDEF::SizeX;
		cb->windowSize.v = (float)SYSDEF::SizeY;
		cb->mousePos.u = mousePos.x;
		cb->mousePos.v = mousePos.y;
		cb->radius = timer.GetNow();
		cb->onClick = onClick;
		//ピクセルシェーダー用の定数バッファを更新して書き込んだ内容を反映する
		UpdateShaderConstantBuffer(pscbhandle);
		//ピクセルシェーダー用の定数バッファを定数バッファレジスタ0にセット
		SetShaderConstantBuffer(pscbhandle, DX_SHADERTYPE_PIXEL, 0);
		
		//ピクセルシェーダのセット
		SetUsePixelShader(pshandle);
		//描画
		DrawPrimitive2DToShader(vertex, 4, DX_PRIMTYPE_TRIANGLESTRIP);
	}
}