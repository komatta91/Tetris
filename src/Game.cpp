#include "Game.h"

#define MEANER_AND_LEANER
#include <windows.h>
#include <GL/gl.h>
#include <freeglut/freeglut.h>

#include <KeyInput.h>
#include <GameKeyMapper.h>
#include <GameAction.h>
#include <glm\glm.hpp>

#include <iostream>


#include <vector>
#include <Vertex.h>
#include <glm\vec3.hpp>
#include <glm\gtx\fast_trigonometry.hpp>

#include <Timer.h>

#include <ResourceLoader.h>

#include <PhongShader.h>
#include <BasicShader.h>

#include <glm\mat4x4.hpp>

#include <GeometryGenerator.h>

Game::Game(void)
{
	KeyInput::getInstance().initialize(&gameKeyMapper, gameKeyMapper.getMaxActon());
}

void Game::init()
{
	shader = new PhongShader();

	transSky.setProjection(0.1f, 1000.0f, 800.0f, 600.0f, 70.0f); 
	transFloor.setProjection(0.1f, 1000.0f, 800.0f, 600.0f, 70.0f);
	transSpiderHead.setProjection(0.1f, 1000.0f, 800.0f, 600.0f, 70.0f);
	transSpiderAbdomen.setProjection(0.1f, 1000.0f, 800.0f, 600.0f, 70.0f);
	
	transSpiderLeg11.setProjection(0.1f, 1000.0f, 800.0f, 600.0f, 70.0f);
	transSpiderLeg12.setProjection(0.1f, 1000.0f, 800.0f, 600.0f, 70.0f);
	transSpiderLeg13.setProjection(0.1f, 1000.0f, 800.0f, 600.0f, 70.0f);
	transSpiderLeg14.setProjection(0.1f, 1000.0f, 800.0f, 600.0f, 70.0f);
	transSpiderLeg15.setProjection(0.1f, 1000.0f, 800.0f, 600.0f, 70.0f);
	transSpiderLeg16.setProjection(0.1f, 1000.0f, 800.0f, 600.0f, 70.0f);
	transSpiderLeg17.setProjection(0.1f, 1000.0f, 800.0f, 600.0f, 70.0f);
	transSpiderLeg18.setProjection(0.1f, 1000.0f, 800.0f, 600.0f, 70.0f);

	transSpiderLeg21.setProjection(0.1f, 1000.0f, 800.0f, 600.0f, 70.0f);
	transSpiderLeg22.setProjection(0.1f, 1000.0f, 800.0f, 600.0f, 70.0f);
	transSpiderLeg23.setProjection(0.1f, 1000.0f, 800.0f, 600.0f, 70.0f);
	transSpiderLeg24.setProjection(0.1f, 1000.0f, 800.0f, 600.0f, 70.0f);
	transSpiderLeg25.setProjection(0.1f, 1000.0f, 800.0f, 600.0f, 70.0f);
	transSpiderLeg26.setProjection(0.1f, 1000.0f, 800.0f, 600.0f, 70.0f);
	transSpiderLeg27.setProjection(0.1f, 1000.0f, 800.0f, 600.0f, 70.0f);
	transSpiderLeg28.setProjection(0.1f, 1000.0f, 800.0f, 600.0f, 70.0f);

	transSpiderLeg31.setProjection(0.1f, 1000.0f, 800.0f, 600.0f, 70.0f);
	transSpiderLeg32.setProjection(0.1f, 1000.0f, 800.0f, 600.0f, 70.0f);
	transSpiderLeg33.setProjection(0.1f, 1000.0f, 800.0f, 600.0f, 70.0f);
	transSpiderLeg34.setProjection(0.1f, 1000.0f, 800.0f, 600.0f, 70.0f);
	transSpiderLeg35.setProjection(0.1f, 1000.0f, 800.0f, 600.0f, 70.0f);
	transSpiderLeg36.setProjection(0.1f, 1000.0f, 800.0f, 600.0f, 70.0f);
	transSpiderLeg37.setProjection(0.1f, 1000.0f, 800.0f, 600.0f, 70.0f);
	transSpiderLeg38.setProjection(0.1f, 1000.0f, 800.0f, 600.0f, 70.0f);

	transSpiderEye1.setProjection(0.1f, 1000.0f, 800.0f, 600.0f, 70.0f);
	transSpiderEye2.setProjection(0.1f, 1000.0f, 800.0f, 600.0f, 70.0f);
	transSpiderEye3.setProjection(0.1f, 1000.0f, 800.0f, 600.0f, 70.0f);
	transSpiderEye4.setProjection(0.1f, 1000.0f, 800.0f, 600.0f, 70.0f);

	GeometryGenerator generator;
	GeometryGenerator::MeshData data;
	std::vector<Vertex> vertices;
	std::vector<int> indices;
	
	generator.CreateGrid(200,200,2,2,data);
	for(int i = 0; i < data.Vertices.size(); ++i)
	{
		Vertex v(data.Vertices[i].Position, data.Vertices[i].TexC, data.Vertices[i].Normal);
		vertices.push_back(v);
	}
	for (int i = 0; i < data.Indices.size(); ++i)
	{
		indices.push_back(data.Indices[i]);
	}

	meshFloor.addVertices(vertices, indices);

	data = GeometryGenerator::MeshData();
	vertices.clear();
	indices.clear();

	generator.CreateSphere(100, 100, 100, data);
	for(int i = 0; i < data.Vertices.size(); ++i)
	{
		Vertex v(data.Vertices[i].Position, data.Vertices[i].TexC, data.Vertices[i].Normal);
		vertices.push_back(v);
	}
	for (int i = 0; i < data.Indices.size(); ++i)
	{
		indices.push_back(data.Indices[i]);
	}

	meshSky.addVertices(vertices, indices);


	data = GeometryGenerator::MeshData();
	vertices.clear();
	indices.clear();

	generator.CreateGeosphere(10, 10, data);
	for(int i = 0; i < data.Vertices.size(); ++i)
	{
		Vertex v(data.Vertices[i].Position, data.Vertices[i].TexC, data.Vertices[i].Normal);
		vertices.push_back(v);
	}
	for (int i = 0; i < data.Indices.size(); ++i)
	{
		indices.push_back(data.Indices[i]);
	}

	meshSpiderHead.addVertices(vertices, indices);


	//SpiderHead
	data = GeometryGenerator::MeshData();
	vertices.clear();
	indices.clear();

	generator.CreateGeosphere(10, 10, data);
	for(int i = 0; i < data.Vertices.size(); ++i)
	{
		Vertex v(data.Vertices[i].Position, data.Vertices[i].TexC, data.Vertices[i].Normal);
		vertices.push_back(v);
	}
	for (int i = 0; i < data.Indices.size(); ++i)
	{
		indices.push_back(data.Indices[i]);
	}

	meshSpiderHead.addVertices(vertices, indices);

	//SpiderAbdomen
	data = GeometryGenerator::MeshData();
	vertices.clear();
	indices.clear();

	generator.CreateSphere(10, 10, 10, data);
	for(int i = 0; i < data.Vertices.size(); ++i)
	{
		Vertex v(data.Vertices[i].Position, data.Vertices[i].TexC, data.Vertices[i].Normal);
		vertices.push_back(v);
	}
	for (int i = 0; i < data.Indices.size(); ++i)
	{
		indices.push_back(data.Indices[i]);
	}

	meshSpiderAbdomen.addVertices(vertices, indices);

	//SpiderLeg1
	data = GeometryGenerator::MeshData();
	vertices.clear();
	indices.clear();

	generator.CreateCylinder(3, 2, 15, 20, 20, data);
	for(int i = 0; i < data.Vertices.size(); ++i)
	{
		Vertex v(data.Vertices[i].Position, data.Vertices[i].TexC, data.Vertices[i].Normal);
		vertices.push_back(v);
	}
	for (int i = 0; i < data.Indices.size(); ++i)
	{
		indices.push_back(data.Indices[i]);
	}

	meshSpiderLeg1.addVertices(vertices, indices);

	//SpiderLeg2
	data = GeometryGenerator::MeshData();
	vertices.clear();
	indices.clear();

	generator.CreateGeosphere(1, 20, data);
	for(int i = 0; i < data.Vertices.size(); ++i)
	{
		Vertex v(data.Vertices[i].Position, data.Vertices[i].TexC, data.Vertices[i].Normal);
		vertices.push_back(v);
	}
	for (int i = 0; i < data.Indices.size(); ++i)
	{
		indices.push_back(data.Indices[i]);
	}

	meshSpiderLeg2.addVertices(vertices, indices);

	//SpiderLeg3
	data = GeometryGenerator::MeshData();
	vertices.clear();
	indices.clear();

	generator.CreateCylinder(0, 1, 15, 20, 20, data);
	for(int i = 0; i < data.Vertices.size(); ++i)
	{
		Vertex v(data.Vertices[i].Position, data.Vertices[i].TexC, data.Vertices[i].Normal);
		vertices.push_back(v);
	}
	for (int i = 0; i < data.Indices.size(); ++i)
	{
		indices.push_back(data.Indices[i]);
	}

	meshSpiderLeg3.addVertices(vertices, indices);
	

	glm::vec3 color(1.0f, 1.0f, 1.0f);
	static_cast<PhongShader*>(shader)->setAmbientLight(glm::vec3(0.2f, 0.2f, 0.2f));

	BaseLight base(glm::vec3(1,1,0), 0.5);
	DirectionalLight light(base, glm::vec3( 0, -1, 0));
	static_cast<PhongShader*>(shader)->setDirectionalLight(light);

	matFloor = new Material("podloga.bmp", color, 1, 64);
	matSky = new Material("yYz0b.bmp", color);
	
	matSpiderLeg1 = new Material("leg.bmp", color, 0.5, 64);
	matSpiderLeg2 = new Material("knee.bmp", color, 0.5, 64);
	matSpiderLeg3 = new Material("leg1.bmp", color, 0.5, 64);
	matSpiderAbdomen = new Material("abdomen.bmp", color, 0.5, 64);
	matSpiderHead = new Material("head.bmp", color, 0.5, 64);
	matSpiderEye = new Material("black.bmp", color, 16, 256);

	camera.muve(glm::vec3(0,1,40), 1.5);
}


Game::~Game(void)
{
	if (shader)
	{
		delete shader;
	}
}

static float scale = 0.0f;
glm::vec3 additionPos(0.0f);
float amountX = 0;
float amountY = 0;

void Game::input()
{
	additionPos = glm::vec3(0.0f);
	amountX = 0;
	amountY = 0;
	KeyInput::getInstance().update();
	if (KeyInput::getInstance().actionsHot(GameAction::FORWARD))
	{
		additionPos += camera.getForward();
	}
	if (KeyInput::getInstance().actionsHot(GameAction::LEFT))
	{
		additionPos += camera.getLeft();
	}
	if (KeyInput::getInstance().actionsHot(GameAction::RIGHT))
	{
		additionPos += camera.getRight();
	}
	if (KeyInput::getInstance().actionsHot(GameAction::BACK))
	{
		additionPos += camera.getBack();
	}

	if (KeyInput::getInstance().actionsHot(GameAction::ROTATE_DOWN))
	{
		amountY -= Timer::getInstance().deltaTime();
	}
	if (KeyInput::getInstance().actionsHot(GameAction::ROTATE_LEFT))
	{
		amountX += Timer::getInstance().deltaTime();
	}
	if (KeyInput::getInstance().actionsHot(GameAction::ROTATE_RIGHT))
	{
		amountX -= Timer::getInstance().deltaTime();
	}
	if (KeyInput::getInstance().actionsHot(GameAction::ROTATE_UP))
	{
		amountY += Timer::getInstance().deltaTime();
	}
}
void Game::update()
{
	scale += Timer::getInstance().deltaTime();

	transFloor.setTranslation(0.0f, -1.0f, 0);
	
	transSpiderHead.setTranslation(0.0f, 7.0f, 0);
	transSpiderHead.setScale(0.8f, 0.6f, 1.3f);

	transSpiderAbdomen.setTranslation(1.0f, 10.0f, -20);
	transSpiderAbdomen.setScale(1.1f, 1.1f, 1.6f);

	transSpiderLeg11.setTranslation(-16.0f, 10.0f, 10);
	transSpiderLeg11.setScale(0.5f, 1.8f, 0.5f);
	transSpiderLeg11.setRotation(0, 20, 70);

	transSpiderLeg12.setTranslation(-16.0f, 10.0f, 4);
	transSpiderLeg12.setScale(0.5f, 1.8f, 0.5f);
	transSpiderLeg12.setRotation(0, 5, 70);

	transSpiderLeg13.setTranslation(-16.0f, 10.0f, -2);
	transSpiderLeg13.setScale(0.5f, 1.8f, 0.5f);
	transSpiderLeg13.setRotation(0, -10, 70);

	transSpiderLeg14.setTranslation(-16.0f, 10.0f, -8);
	transSpiderLeg14.setScale(0.5f, 1.8f, 0.5f);
	transSpiderLeg14.setRotation(0, -20, 70);

	transSpiderLeg15.setTranslation(16.0f, 10.0f, 10);
	transSpiderLeg15.setScale(0.5f, 1.8f, 0.5f);
	transSpiderLeg18.setRotation(0, 20, -70);

	transSpiderLeg16.setTranslation(16.0f, 10.0f, 4.0f);
	transSpiderLeg16.setScale(0.5f, 1.8f, 0.5f);
	transSpiderLeg17.setRotation(0, 5, -70);

	transSpiderLeg17.setTranslation(16.0f, 10.0f, -2.0f);
	transSpiderLeg17.setScale(0.5f, 1.8f, 0.5f);
	transSpiderLeg16.setRotation(0, -10, -70);

	transSpiderLeg18.setTranslation(16.0f, 10.0f, -8.0f);
	transSpiderLeg18.setScale(0.5f, 1.8f, 0.5f);
	transSpiderLeg15.setRotation(0, -20, -70);

	transSpiderLeg21.setTranslation(-27.5f, 14.4f, 14.2f);
	transSpiderLeg21.setScale(1.2f, 1.2f, 1.2f);

	transSpiderLeg22.setTranslation(-28.5f, 14.5f, 5.0f);
	transSpiderLeg22.setScale(1.2f, 1.2f, 1.2f);

	transSpiderLeg23.setTranslation(-28.5f, 14.6f, -4.2);
	transSpiderLeg23.setScale(1.2f, 1.2f, 1.2f);

	transSpiderLeg24.setTranslation(-27.5f, 14.4f, -12.2);
	transSpiderLeg24.setScale(1.2f, 1.2f, 1.2f);

	transSpiderLeg25.setTranslation(27.5f, 14.4f, 14.2f);
	transSpiderLeg25.setScale(1.2f, 1.2f, 1.2f);

	transSpiderLeg26.setTranslation(28.5f, 14.5f, 6.2f);
	transSpiderLeg26.setScale(1.2f, 1.2f, 1.2f);

	transSpiderLeg27.setTranslation(28.5f, 14.4f, -3.1);
	transSpiderLeg27.setScale(1.2f, 1.2f, 1.2f);

	transSpiderLeg28.setTranslation(27.5f, 14.4f, -12.2);
	transSpiderLeg28.setScale(1.2f, 1.2f, 1.2f);


	transSpiderLeg31.setTranslation(-47.5f, 6.6f, 21.5f);
	transSpiderLeg31.setScale(1.0f,3.0f, 1.0f);
	transSpiderLeg31.setRotation(0, 20,290);

	transSpiderLeg32.setTranslation(-49.5f, 6.7f, 6.8f);
	transSpiderLeg32.setScale(1.0f,3.0f, 1.0f);
	transSpiderLeg32.setRotation(0, 5,290);

	transSpiderLeg33.setTranslation(-49.5f, 6.7f, -7.8f);
	transSpiderLeg33.setScale(1.0f,3.0f, 1.0f);
	transSpiderLeg33.setRotation(0, -10,290);

	transSpiderLeg34.setTranslation(-47.5f, 6.6f, -19.3f);
	transSpiderLeg34.setScale(1.0f,3.0f, 1.0f);
	transSpiderLeg34.setRotation(0, -20,290);


	transSpiderLeg35.setTranslation(47.5f, 6.6f, 21.5f);
	transSpiderLeg35.setScale(1.0f,3.0f, 1.0f);
	transSpiderLeg38.setRotation(0, 20,70);

	transSpiderLeg36.setTranslation(49.5f, 6.7f, 9.8f);
	transSpiderLeg36.setScale(1.0f,3.0f, 1.0f);
	transSpiderLeg37.setRotation(0, 5,70);

	transSpiderLeg37.setTranslation(49.5f, 6.7f, -5.0f);
	transSpiderLeg37.setScale(1.0f,3.0f, 1.0f);
	transSpiderLeg36.setRotation(0, -10,70);

	transSpiderLeg38.setTranslation(47.5f, 6.6f, -19.3f);
	transSpiderLeg38.setScale(1.0f,3.0f, 1.0f);
	transSpiderLeg35.setRotation(0, -20,70);

	transSpiderEye1.setTranslation(1.5f, 10.1f, 10.5f);
	transSpiderEye1.setScale(0.7f, 0.7f, 0.7f);

	transSpiderEye2.setTranslation(-1.5f, 10.1f, 10.5f);
	transSpiderEye2.setScale(0.7f, 0.7f, 0.7f);

	transSpiderEye3.setTranslation(3.0f, 10.3f, 9.5f);
	transSpiderEye3.setScale(0.5f, 0.5f, 0.5f);

	transSpiderEye4.setTranslation(-3.0f, 10.3f, 9.5f);
	transSpiderEye4.setScale(0.5f, 0.5f, 0.5f);

	camera.muve(additionPos, Timer::getInstance().deltaTime() * 10);
	camera.rotateX(amountX * 100);
	camera.rotateY(amountY * 100);
}
void Game::render()
{
	shader->bindShader();
	
	shader->updateUniforms(transFloor.getTransformation(), transFloor.getProjectionTransformation(camera.lookAt()), camera.getPos(), *matFloor);
	meshFloor.draw();

	shader->updateUniforms(transSky.getTransformation(), transSky.getProjectionTransformation(camera.lookAt()), camera.getPos(), *matSky);
	meshSky.draw();

	shader->updateUniforms(transSpiderHead.getTransformation(), transSpiderHead.getProjectionTransformation(camera.lookAt()), camera.getPos(), *matSpiderHead);
	meshSpiderHead.draw();

	shader->updateUniforms(transSpiderAbdomen.getTransformation(), transSpiderAbdomen.getProjectionTransformation(camera.lookAt()), camera.getPos(), *matSpiderAbdomen);
	meshSpiderAbdomen.draw();

	shader->updateUniforms(transSpiderLeg11.getTransformation(), transSpiderLeg11.getProjectionTransformation(camera.lookAt()), camera.getPos(), *matSpiderLeg1);
	meshSpiderLeg1.draw();

	shader->updateUniforms(transSpiderLeg12.getTransformation(), transSpiderLeg12.getProjectionTransformation(camera.lookAt()), camera.getPos(), *matSpiderLeg1);
	meshSpiderLeg1.draw();

	shader->updateUniforms(transSpiderLeg13.getTransformation(), transSpiderLeg13.getProjectionTransformation(camera.lookAt()), camera.getPos(), *matSpiderLeg1);
	meshSpiderLeg1.draw();

	shader->updateUniforms(transSpiderLeg14.getTransformation(), transSpiderLeg14.getProjectionTransformation(camera.lookAt()), camera.getPos(), *matSpiderLeg1);
	meshSpiderLeg1.draw();

	shader->updateUniforms(transSpiderLeg15.getTransformation(), transSpiderLeg15.getProjectionTransformation(camera.lookAt()), camera.getPos(), *matSpiderLeg1);
	meshSpiderLeg1.draw();

	shader->updateUniforms(transSpiderLeg16.getTransformation(), transSpiderLeg16.getProjectionTransformation(camera.lookAt()), camera.getPos(), *matSpiderLeg1);
	meshSpiderLeg1.draw();

	shader->updateUniforms(transSpiderLeg17.getTransformation(), transSpiderLeg17.getProjectionTransformation(camera.lookAt()), camera.getPos(), *matSpiderLeg1);
	meshSpiderLeg1.draw();

	shader->updateUniforms(transSpiderLeg18.getTransformation(), transSpiderLeg18.getProjectionTransformation(camera.lookAt()), camera.getPos(), *matSpiderLeg1);
	meshSpiderLeg1.draw();

	shader->updateUniforms(transSpiderLeg21.getTransformation(), transSpiderLeg21.getProjectionTransformation(camera.lookAt()), camera.getPos(), *matSpiderLeg2);
	meshSpiderLeg2.draw();

	shader->updateUniforms(transSpiderLeg22.getTransformation(), transSpiderLeg22.getProjectionTransformation(camera.lookAt()), camera.getPos(), *matSpiderLeg2);
	meshSpiderLeg2.draw();

	shader->updateUniforms(transSpiderLeg23.getTransformation(), transSpiderLeg23.getProjectionTransformation(camera.lookAt()), camera.getPos(), *matSpiderLeg2);
	meshSpiderLeg2.draw();

	shader->updateUniforms(transSpiderLeg24.getTransformation(), transSpiderLeg24.getProjectionTransformation(camera.lookAt()), camera.getPos(), *matSpiderLeg2);
	meshSpiderLeg2.draw();

	shader->updateUniforms(transSpiderLeg25.getTransformation(), transSpiderLeg25.getProjectionTransformation(camera.lookAt()), camera.getPos(), *matSpiderLeg2);
	meshSpiderLeg2.draw();

	shader->updateUniforms(transSpiderLeg26.getTransformation(), transSpiderLeg26.getProjectionTransformation(camera.lookAt()), camera.getPos(), *matSpiderLeg2);
	meshSpiderLeg2.draw();

	shader->updateUniforms(transSpiderLeg27.getTransformation(), transSpiderLeg27.getProjectionTransformation(camera.lookAt()), camera.getPos(), *matSpiderLeg2);
	meshSpiderLeg2.draw();

	shader->updateUniforms(transSpiderLeg28.getTransformation(), transSpiderLeg28.getProjectionTransformation(camera.lookAt()), camera.getPos(), *matSpiderLeg2);
	meshSpiderLeg2.draw();

	shader->updateUniforms(transSpiderLeg31.getTransformation(), transSpiderLeg31.getProjectionTransformation(camera.lookAt()), camera.getPos(), *matSpiderLeg3);
	meshSpiderLeg3.draw();

	shader->updateUniforms(transSpiderLeg32.getTransformation(), transSpiderLeg32.getProjectionTransformation(camera.lookAt()), camera.getPos(), *matSpiderLeg3);
	meshSpiderLeg3.draw();

	shader->updateUniforms(transSpiderLeg33.getTransformation(), transSpiderLeg33.getProjectionTransformation(camera.lookAt()), camera.getPos(), *matSpiderLeg3);
	meshSpiderLeg3.draw();

	shader->updateUniforms(transSpiderLeg34.getTransformation(), transSpiderLeg34.getProjectionTransformation(camera.lookAt()), camera.getPos(), *matSpiderLeg3);
	meshSpiderLeg3.draw();

	shader->updateUniforms(transSpiderLeg35.getTransformation(), transSpiderLeg35.getProjectionTransformation(camera.lookAt()), camera.getPos(), *matSpiderLeg3);
	meshSpiderLeg3.draw();

	shader->updateUniforms(transSpiderLeg36.getTransformation(), transSpiderLeg36.getProjectionTransformation(camera.lookAt()), camera.getPos(), *matSpiderLeg3);
	meshSpiderLeg3.draw();

	shader->updateUniforms(transSpiderLeg37.getTransformation(), transSpiderLeg37.getProjectionTransformation(camera.lookAt()), camera.getPos(), *matSpiderLeg3);
	meshSpiderLeg3.draw();

	shader->updateUniforms(transSpiderLeg38.getTransformation(), transSpiderLeg38.getProjectionTransformation(camera.lookAt()), camera.getPos(), *matSpiderLeg3);
	meshSpiderLeg3.draw();

	shader->updateUniforms(transSpiderEye1.getTransformation(), transSpiderEye1.getProjectionTransformation(camera.lookAt()), camera.getPos(), *matSpiderEye);
	meshSpiderLeg2.draw();

	shader->updateUniforms(transSpiderEye2.getTransformation(), transSpiderEye2.getProjectionTransformation(camera.lookAt()), camera.getPos(), *matSpiderEye);
	meshSpiderLeg2.draw();

	shader->updateUniforms(transSpiderEye3.getTransformation(), transSpiderEye3.getProjectionTransformation(camera.lookAt()), camera.getPos(), *matSpiderEye);
	meshSpiderLeg2.draw();

	shader->updateUniforms(transSpiderEye4.getTransformation(), transSpiderEye4.getProjectionTransformation(camera.lookAt()), camera.getPos(), *matSpiderEye);
	meshSpiderLeg2.draw();
}
