#pragma once

#include <iostream>
#include <vector>
#include <variant>
#include <unordered_map>
#include "glm/glm.hpp"


enum ComponentType {
	EMPTY,
	TRANSFORM,
	RENDER
};

struct Transform {
	std::vector<glm::vec3> m_position;
	std::vector<glm::vec3> m_rotation;
	std::vector<glm::vec3> m_scale;

};

struct Entity {
	std::vector<ComponentType> m_componentID;
	uint32_t m_ID;
};

extern uint32_t g_entityCount = 0;

class ECS {

public:
	std::unordered_map<std::string, Entity> m_entities;

	//template<typename T>
	std::unordered_map<ComponentType, std::variant<>> m_components;


	void createEnity(const std::string& name) {
		uint32_t id = g_entityCount;
		g_entityCount++;

		if (m_entities.find(name) != m_entities.end())
		{
			std::cout << "Enity ID already exits\n";
			return;
		}
		
		m_entities[name] = { {EMPTY}, id};
		m_entities[name].m_componentID.clear();
	}

	void addComponent(const std::string& name, const ComponentType& ComponentType) {

		if (m_entities.find(name) == m_entities.end())
		{
			std::cout << "Enity doesnt exit\n";
			return;
		}

		if (m_components.find(ComponentType) == m_components.end())
		{
			std::cout << "Component doesnt exit\n";
			return;
		}

		m_entities[name].m_componentID.push_back(ComponentType);
	}

};
