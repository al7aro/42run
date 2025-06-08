#include "Model.hpp"

namespace FT {
	Model::Model(const Model & o)
		: m_nodes(o.m_nodes), m_mesh(o.m_mesh), m_bone_cnt(o.m_bone_cnt), m_bones(o.m_bones),
			m_global_inverse(o.m_global_inverse), m_path(o.m_path)
	{
	}
	Model & Model::operator=(const Model & o)
	{
		m_nodes = o.m_nodes;
		m_mesh = o.m_mesh;
		m_bone_cnt = o.m_bone_cnt;
		m_bones = o.m_bones;
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

	void Model::SetGlobalInverse(const FT::mat4 & global_inverse)
	{
		m_global_inverse = global_inverse;
	}

	void Model::AddNode(const std::string& node, const FT::mat4 & tr, const std::string& parent)
	{
		m_nodes[node] = Node(node, tr, parent);
	}

	int Model::GetBoneId(const std::string & name)
	{
		auto it = m_bones.find(name);
		if (it == m_bones.end())
			return (-1);
		return (it->second.id);
	}

	int Model::CreateBone(const std::string & name, const std::string & node_name, const FT::mat4 & offset)
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

	FT::mat4 Model::GetNodeTransform(const std::string & name)
	{
		const auto& it = m_nodes.find(name);
		if (it == m_nodes.end())
			return (1.0);
		FT::mat4 tr = it->second.final_transform;
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
}