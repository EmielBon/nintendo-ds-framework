#include "EfficientVectorsTest.h"

// Stable libraries
#include "Framework.h"
#include "Input.h"

// Specific libraries
#include "VideoRam.h"

// 2D graphics
#include "TileSet256.h"
#include "Palette.h"
#include "Background.h"

// 3D Graphics
#include "GraphicsDevice.h"
#include "GameCamera.h"
#include "FlyingCamera.h"
#include "Mat.h"
#include "Model.h"
#include "Vec3.h"
#include "Vertex.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "Scene.h"
#include "Light.h"
#include "TextureMemory.h"

// Game classes
#include "Mario.h"

// Debug
#include "Logging.h"
#include "FPSCounter.h"
#include "DebugUI.h"
#include "Debug.h"
#include "BasicEffect.h"

namespace Test
{
	using namespace Util;
	using namespace Debug;
	using namespace Input;
	using namespace System;
	using namespace Framework3D;

	//-------------------------------------------------------------------------------------------------
	EVTest::EVTest()
	{
		graphics = GraphicsDeviceManager(this);
		camera = New<FlyingCamera>( Vector3(10, 10, 0), Vector3(0, 0, 0), 256.0f / 192.0f );
		effect = New<BasicEffect>();
		effect->TextureEnabled = false;
		quadVertices = New<VertexBuffer>();
		quadIndices = New<IndexBuffer>();
		//ASSERT2(false, (fx12(-12.3892389f).ToF32() >> 12));
	}

	//-------------------------------------------------------------------------------------------------
	void EVTest::Initialize()
	{
		//ASSERT2(false, fx12((int)(fx12(15.253f))).ToFloat());
		GraphicsDevice::Main.TextureMemory->AutomaticExpansion = false;
		GraphicsDevice::Main.TextureMemory->AssignBankToSlot(BankA, 0);
		GraphicsDevice::Main.TextureMemory->AssignBankToSlot(BankB, 1);
		GraphicsDevice::Main.TextureMemory->AssignBankToSlot(BankC, 2);
		GraphicsDevice::Main.TextureMemory->AssignBankToSlot(BankD, 3);

		// Enable 3D on the main engine
		GraphicsDevice::Main.Enable3D(true);
		// Enable background 0 (used for 3D rendering)
		auto bg0 = GraphicsDevice::Main.Backgrounds[0];
		bg0->Enable();
		bg0->SetLayer(0);
		// Set up the graphics device
		GraphicsDevice.RasterizerState.CullMode = CullMode::None;
		graphics.PreferMultiSampling = false;
		graphics.ApplyChanges();
		// Set the color for the background
		GraphicsDevice::Main.SetBackgroundColor( Color::DeepSkyBlue );

		camera->Initialize();

		super::Initialize();
	}

	//-------------------------------------------------------------------------------------------------
	void EVTest::LoadContent()
	{
		model = Content.Load<Model>("completeCube");

		for(auto mesh = model->Meshes.begin(); mesh != model->Meshes.end(); ++mesh)
			for(auto part = mesh->MeshParts.begin(); part != mesh->MeshParts.end(); ++part)
				part->Effect = effect;

		List<Vertex> vertices;
		vertices.resize(4);
		
		vertices[0].Position = Vector3(-1, 0, -1);
		vertices[1].Position = Vector3( 1, 0, -1);
		vertices[2].Position = Vector3(-1, 0,  1);
		vertices[3].Position = Vector3( 1, 0,  1);

		quadVertices->SetData(vertices);

		List<u16> indices;
		indices.resize(6);

		indices[0] = 0;
		indices[1] = 1;
		indices[2] = 2;
		indices[3] = 1;
		indices[4] = 2;
		indices[5] = 3;

		quadIndices->SetData(indices);

		

		super::LoadContent();
	}

	//-------------------------------------------------------------------------------------------------
	void EVTest::Update(const GameTime &gameTime)
	{	
		camera->Update(gameTime);

		super::Update(gameTime);
	}

	//-------------------------------------------------------------------------------------------------
	void EVTest::Draw(const GameTime &gameTime)
	{
		// Clear the render target in a predetermined color
		GraphicsDevice.Clear(ClearOptions::Target, Color::DeepSkyBlue);

		camera->SetEffectParameters(*effect);
		//effect->World = Matrix::Identity();

		//effect->Apply();
		model->Draw();
		//GraphicsDevice.VertexBuffer = quadVertices;
		//GraphicsDevice.Indices = quadIndices;
		//GraphicsDevice.DrawIndexedPrimitives(PrimitiveType::TriangleList, 0, 0, 4, 0, 2);

		super::Draw(gameTime);
	}
}