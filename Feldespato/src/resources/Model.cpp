#include "Model.hpp"

namespace FT {
	Model::Model(const Model & o)
		: m_nodes(o.m_nodes), m_mesh(o.m_mesh), m_bone_cnt(o.m_bone_cnt), m_bones(o.m_bones),
			m_animations(o.m_animations), m_global_inverse(o.m_global_inverse), m_path(o.m_path)
	{
	}
	Model & Model::operator=(const Model & o)
	{
		m_nodes = o.m_nodes;
		m_mesh = o.m_mesh;
		m_bone_cnt = o.m_bone_cnt;
		m_bones = o.m_bones;
		m_animations = o.m_animations;
		m_global_inverse = o.m_global_inverse;
		m_path = o.m_path;
		return (*this);
	}

	Model::Model(const Mesh & mesh)
		: m_bone_cnt(0)
	{
		AddMesh(mesh);
	}
	Model::Model()
		: m_bone_cnt(0) {}
		Model::~Model() {}

	void Model::SetPath(const std::string & path)
	{
		m_path = path;
	}

	std::string Model::GetPath()
	{
		return (m_path);
	}

	void Model::SetGlobalInverse(const glm::mat4 & global_inverse)
	{
		m_global_inverse = global_inverse;
	}

	void Model::AddNode(const std::string& node, const glm::mat4 & tr, const std::string& parent)
	{
		m_nodes[node] = Node(node, tr, parent);
	}

	void Model::AddAnimation(Animation anim)
	{
		m_animations[anim.GetName()] = anim;
	}

	int Model::GetBoneId(const std::string & name)
	{
		auto it = m_bones.find(name);
		if (it == m_bones.end())
			return (-1);
		return (it->second.id);
	}

	int Model::CreateBone(const std::string & name, const std::string & node_name, const glm::mat4 & offset)
	{
		auto it = m_bones.find(name);
		if (it == m_bones.end())
		{
			m_bone_cnt++;
			m_bones[name] = Bone(name, node_name, m_bone_cnt - 1, offset);
			return (m_bone_cnt - 1);
		}
		return (it->second.id);
	}

	void Model::AddMesh(const Mesh & mesh)
	{
		m_mesh.push_back(mesh);
	}

	glm::mat4 Model::GetNodeTransform(const std::string & name)
	{
		const auto& it = m_nodes.find(name);
		if (it == m_nodes.end())
			return (1.0);
		glm::mat4 tr = it->second.final_transform;
		if (it->second.parent.empty())
			return (tr);
		tr = GetNodeTransform(it->second.parent) * tr;
		return (tr);
	}

	std::vector<Mesh> Model::GetMeshes()
	{
		return (m_mesh);
	}

	std::map<std::string, Bone> Model::GetBones()
	{
		return (m_bones);
	}

	std::map<std::string, Animation> Model::GetAnimations()
	{
		return (m_animations);
	}

	void Model::RestPose()
	{
		/* UPDATE NODES */
		for (auto& node : m_nodes) // REST POSE
			node.second.final_transform = node.second.transform;

		/* UPDATE BONES */
		for (auto& pair : m_bones)
		{
			Bone& b = pair.second;
			glm::mat4 parent_tr = GetNodeTransform(pair.first);
			b.final_transform = m_global_inverse * parent_tr * b.offset;
		}
	}

	void Model::Animate(const std::string & animation, float time)
	{
		auto anim = m_animations.find(animation);
		/* UPDATE NODES */
		if (animation.empty() || m_animations.size() < 1 || anim == m_animations.end())
		{
			for (auto& node : m_nodes) // REST POSE
				node.second.final_transform = node.second.transform;
		}
		else
		{
			for (auto& node : m_nodes)
				node.second.final_transform = anim->second.GetKeyTransform(node.first, time);
				//MAL------->>>>> node.second.final_transform = node.second.transform * m_animations[0].GetKeyTransform(node.first, time);
		}

		/* UPDATE BONES */
		for (auto& pair : m_bones)
		{
			Bone& b = pair.second;
			glm::mat4 parent_tr = GetNodeTransform(pair.first);
			b.final_transform = m_global_inverse * parent_tr * b.offset;
		}
	}

	void Model::Animate(float time)
	{
		/* UPDATE NODES */
		if (m_animations.size() < 1)
		{
			for (auto& node : m_nodes) // REST POSE
				node.second.final_transform = node.second.transform;
		}
		else
		{
			for (auto& node : m_nodes)
				node.second.final_transform = m_animations.begin()->second.GetKeyTransform(node.first, time);
			//MAL------->>>>> node.second.final_transform = node.second.transform * m_animations[0].GetKeyTransform(node.first, time);
		}

		/* UPDATE BONES */
		for (auto& pair : m_bones)
		{
			Bone& b = pair.second;
			glm::mat4 parent_tr = GetNodeTransform(pair.first);
			b.final_transform = m_global_inverse * parent_tr * b.offset;
		}
	}
}