#include "scene.h"
#include "entity.h"
#include <assert.h>
#include <vector>

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

	std::list<Entity*>::iterator iter = m_entites.begin();
	while (iter != m_entites.end())
	{
		if ((*iter)->GetState() == Entity::DESTORY)
		{
			iter = RemoveEntity(*iter);
		}
		else
		{
			iter++;
		}
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

std::list<Entity*>::iterator Scene::RemoveEntity(Entity * entity, bool destory)
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
		iter = m_entites.erase(iter);
	}
	return iter;
}

Entity * Scene::GetEntityWithID(const ID & id)
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

std::vector<Entity*> Scene::GetEnitiesWithTag(const ID & tag)
{

	std::vector<Entity*> entities;

	for (Entity* entity : m_entites)
	{
		if (entity->GetTag() == tag)
		{
			entities.push_back(entity);
		}
	}

	return entities;
}
