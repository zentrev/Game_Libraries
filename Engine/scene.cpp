#include "scene.h"
#include "entity.h"
#include <assert.h>

bool Scene::Initialize()
{
	return false;
}

void Scene::Shutdown()
{
	for (Entity* entity : m_entiites)
	{
		delete entity;
	}
	m_entiites.clear();
}

void Scene::Update()
{
	for (Entity* enity : m_entiites) {
		enity->Update();
	}
}

void Scene::Draw()
{
	for (Entity* enity : m_entiites) {
		enity->Draw();
	}
}

void Scene::AddEntity(Entity * entity)
{
	assert(std::find(m_entiites.begin(), m_entiites.end(), entity) == m_entiites.end());
	assert(entity);
	m_entiites.push_back(entity);
}

void Scene::RemoveEntity(Entity * entity)
{
	assert(std::find(m_entiites.begin(), m_entiites.end(), entity) != m_entiites.end());
	assert(entity);

	auto iter = std::find(m_entiites.begin(), m_entiites.end(), entity);
	if (iter != m_entiites.end())
	{
		m_entiites.erase(iter);
	}
}

Entity * Scene::FindEntity(const ID & id)
{
	Entity* entity = nullptr;
	for (Entity* _enity : m_entiites)
	{
		if (*_enity == id)
		{
			entity = _enity;
		}
	}
	return entity;
}
