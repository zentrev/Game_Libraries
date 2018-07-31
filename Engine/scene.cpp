#include "scene.h"
#include "entity.h"
#include <assert.h>

bool Scene::Initialize()
{
	return false;
}

void Scene::Shutdown()
{
	for (Entity* entity : m_entites)
	{
		delete entity;
	}
	m_entites.clear();
}

void Scene::Update()
{
	size_t size = m_entites.size();
	for (Entity* entity : m_entites)
	{
		entity->Update();
	}	
}

void Scene::Draw()
{
	for (Entity* enity : m_entites) {
		enity->Draw();
	}
}

void Scene::AddEntity(Entity * entity)
{
	assert(std::find(m_entites.begin(), m_entites.end(), entity) == m_entites.end());
	assert(entity);
	m_entites.push_back(entity);
}

void Scene::RemoveEntity(Entity * entity, bool destory)
{
	assert(std::find(m_entites.begin(), m_entites.end(), entity) != m_entites.end());
	assert(entity);

	auto iter = std::find(m_entites.begin(), m_entites.end(), entity);
	if (iter != m_entites.end())
	{
		if (destory)
		{
			(*iter)->Destory();
			delete *iter;
		}
		m_entites.erase(iter);
	}
}

Entity * Scene::FindEntity(const ID & id)
{
	Entity* entity = nullptr;
	for (Entity* _enity : m_entites)
	{
		if (*_enity == id)
		{
			entity = _enity;
		}
	}
	return entity;
}
