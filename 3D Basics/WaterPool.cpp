#include "WaterPool.h"

#include "PoolWall.h"
#include "WaterObject.h"

WaterPool::WaterPool(Camera  * mainCamera)
{
	camera = mainCamera;

	bottom = new PoolWall(mainCamera);
	left = new PoolWall(mainCamera);
	right = new PoolWall(mainCamera);
	front = new PoolWall(mainCamera);
	back = new PoolWall(mainCamera);
	water = new WaterObject(mainCamera);

	
	poolObjects[0] = bottom;
	poolObjects[1] = left;
	poolObjects[2] = right;
	poolObjects[3] = front;
	poolObjects[4] = back;
	poolObjects[5] = water;
}


WaterPool::~WaterPool()
{
	for (int i = 0; i < 6; i++)
	{
		delete poolObjects[i];
		poolObjects[i] = NULL;
	}
}

void WaterPool::Initialise()
{
	// Position pool
	back->transform.rotation.x = transform.rotation.x - 90.f;
	back->transform.position.z = transform.position.z + 2.0f;
	back->transform.position.y = transform.position.y - 2.0f;

	front->transform.rotation.x = transform.rotation.x + 90.f;
	front->transform.position.z = transform.position.z - 2.0f;
	front->transform.position.y = transform.position.y - 2.0f;

	right->transform.rotation.z = transform.rotation.z - 90.f;
	right->transform.position.x = transform.position.x + 2.0f;
	right->transform.position.y = transform.position.y - 2.0f;

	left->transform.rotation.z = transform.rotation.z - 90.f;
	left->transform.position.x = transform.position.x - 2.0f;
	left->transform.position.y = transform.position.y - 2.0f;

	bottom->transform.position.y = transform.position.y - 4.0f;
	water->transform.position.y = transform.position.y;

	for (int i = 0; i < 6; i++)
	{
		poolObjects[i]->Initialise();
		poolObjects[i]->transform.scale.x *= 2.0f;
		poolObjects[i]->transform.scale.z *= 2.0f;
	}
}

void WaterPool::Render(GLuint program)
{
	for (int i = 0; i < 6; i++)
	{
		poolObjects[i]->Render(program);
	}
}

void WaterPool::Update(float deltaTime)
{
	for (int i = 0; i < 6; i++)
	{
		poolObjects[i]->Update(deltaTime);
	}
}
