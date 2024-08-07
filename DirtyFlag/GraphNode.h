#pragma once
#include <vector>

class Transform
{
public:
	Transform(int value);
	Transform(const Transform& transform);

	static Transform Origin();
	Transform Combine(Transform& other);
	int GetValue() { return m_value; }

private:
	int m_value{ 0 };
};

class Mesh
{};

class GraphNode
{
public:
	GraphNode(Mesh* mesh);

	void Attach(GraphNode* child);
	void SetTransform(Transform local);
	Transform GetTransform() { return m_world; }
	void Render(Transform parentWorld, bool dirty);

private:
	Transform m_local;
	Mesh* m_mesh;
	std::vector<GraphNode*> m_children;

	Transform m_world;
	bool m_dirty;
};