#pragma once

#include <map>
#include <string>

#include "Mesh.hpp"
#include "../Bone.hpp"

namespace FT {
	class Model
	{
	public:
		struct Node
		{
			std::string name;
			FT::mat4 transform;
			std::string parent;
			FT::mat4 final_transform;
			Node()
			{
			}
			Node(const Node  & o)
				: name(o.name), transform(o.transform), parent(o.parent), final_transform(o.final_transform)
			{
			}
			Node & operator=(const Node & o)
			{
				name = o.name;
				transform = o.transform;
				parent = o.parent;
				final_transform = o.final_transform;
				return (*this);
			}
			Node(const std::string& n, FT::mat4 tr, const std::string& p)
				: name(n), transform(tr), parent(p), final_transform(tr)
			{
			}
		};
	private:
		std::map<std::string, Node> m_nodes; /* <name, node> */

		std::vector<Mesh> m_mesh;
		unsigned int m_bone_cnt;
		std::map<std::string, Bone> m_bones;
		FT::mat4 m_global_inverse;
		std::string m_path;

		
	public:
		Model();
		Model(const Model & o);
		Model & operator=(const Model & o);
		Model(const std::vector<Mesh>& meshes);
		Model(const Mesh & mesh);
		~Model();

		/* Model Path */
		void 		SetPath(const std::string & path);
		std::string GetPath();

		/* Model Transform */
		FT::mat4 	GetGlobalInverse();
		void 		SetGlobalInverse(const FT::mat4 & global_inverse);
		
		/* Model Hirearchy */
		void 								AddNode(const std::string& node, const FT::mat4 & tr, const std::string& parent);
		FT::mat4 							GetNodeTransform(const std::string & name);
		std::map<std::string, Bone> 		GetBones();
		int 								GetBoneId(const std::string & name);
		int 								CreateBone(const std::string & name, const std::string & node_name, const FT::mat4 & offset);
		std::vector<Mesh> GetMeshes();
		void 								AddMesh(const Mesh & mesh);

	};
}