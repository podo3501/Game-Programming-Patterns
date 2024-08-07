#include "GraphNode.h"
#include <ranges>

Transform::Transform(int value) :
	m_value{ value }
{}

Transform::Transform(const Transform& transform) :
	m_value{ transform.m_value }
{}

Transform Transform::Origin()
{
	return Transform(10);
}

Transform Transform::Combine(Transform& other)
{
	return Transform(m_value + other.GetValue());
}

/////////////////////////////////////////////////////////////

void RenderMesh(Mesh* mesh, Transform transform)
{
	return;
}

GraphNode::GraphNode(Mesh* mesh) :
	m_mesh{ mesh },
	m_local{ Transform::Origin() },
	m_world{ Transform::Origin() },
	m_dirty{ false }
{}

void GraphNode::Attach(GraphNode* child)
{
	m_children.emplace_back(child);
}

void GraphNode::SetTransform(Transform local)
{
	m_local = local;
	m_dirty = true;
}

void GraphNode::Render(Transform parentWorld, bool dirty)
{
	dirty |= m_dirty;
	if (dirty)
	{
		m_world = m_local.Combine(parentWorld);
		m_dirty = false;
	}
	
	if (m_mesh) RenderMesh(m_mesh, m_world);

	for (const auto& child : m_children)
		child->Render(m_world, dirty);
}