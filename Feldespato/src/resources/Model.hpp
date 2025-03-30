#pragma once

#include <map>
#include <string>

#include <glm/glm.hpp>

#include "Mesh.hpp"
#include "Animation.hpp"
#include "../Bone.hpp"

namespace FT {
	class Model
	{
	public:
		struct Node
		{
			std::string name;
			glm::mat4 transform;
			std::string parent;
			glm::mat4 final_transform;
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
			Node(const std::string& n, glm::mat4 tr, const std::string& p)
				: name(n), transform(tr), parent(p), final_transform(tr)
			{
			}
		};
	private:
		std::map<std::string, Node> m_nodes; /* <name, node> */

		std::vector<Mesh> m_mesh;
		unsigned int m_bone_cnt;
		std::map<std::string, Bone> m_bones;
		std::map<std::string, Animation> m_animations;
		glm::mat4 m_global_inverse;
		std::string m_path;

		
	public:
		Model();
		Model(const Model & o);
		Model & operator=(const Model & o);
		Model(const Mesh & mesh);
		~Model();

		/* Model Path */
		void 		SetPath(const std::string & path);
		std::string GetPath();

		/* Model Transform */
		glm::mat4 	GetGlobalInverse();
		void 		SetGlobalInverse(const glm::mat4 & global_inverse);
		
		/* Model Hirearchy */
		void 								AddNode(const std::string& node, const glm::mat4 & tr, const std::string& parent);
		glm::mat4 							GetNodeTransform(const std::string & name);
		std::map<std::string, Bone> 		GetBones();
		int 								GetBoneId(const std::string & name);
		int 								CreateBone(const std::string & name, const std::string & node_name, const glm::mat4 & offset);
		std::vector<Mesh> GetMeshes();
		void 								AddMesh(const Mesh & mesh);
		
		/* Model Animation */
		void 								AddAnimation(Animation anim);
		std::map<std::string, Animation> 	GetAnimations();
		void 								RestPose();
		void 								Animate(const std::string & animation, float time);
		void 								Animate(float time);
	};
}