#include "ResourceManager.hpp"

namespace FT {
	std::vector<std::shared_ptr<Texture2D> > ResourceManager::load_textures(aiMaterial * mat, aiTextureType type, const std::string & model_path)
	{
		std::vector<std::shared_ptr<Texture2D> > ret;

		if (!mat->GetTextureCount(type))
			return ret;
		for (unsigned int i = 0; i < mat->GetTextureCount(type); i++)
		{
			aiString texture_path;
			mat->GetTexture(type, i, &texture_path);
			std::filesystem::path relative_path(texture_path.C_Str());
			std::filesystem::path parent_path(model_path);
			std::filesystem::path absolute_path(parent_path.parent_path() / relative_path);
			std::shared_ptr<Texture2D> tex = this->LoadImage(absolute_path.string());
			if (tex)
				ret.push_back(tex);
		}
		return (ret);
	}

	Material ResourceManager::process_material(const aiScene* scene, aiMesh* mesh, const std::string & model_path)
	{
		Material material;
		const std::string m_name = mesh->mName.C_Str();

		aiMaterial * mat = scene->mMaterials[mesh->mMaterialIndex];
		std::vector<std::shared_ptr<Texture2D> > diff = this->load_textures(mat, aiTextureType_DIFFUSE, model_path);
		if (!diff.empty())
			material.SetTexture(diff[0], Material::DIFFUSE_MAP);
		std::vector<std::shared_ptr<Texture2D> > spec = this->load_textures(mat, aiTextureType_SPECULAR, model_path);
		if (!spec.empty())
			material.SetTexture(spec[0], Material::SPECULAR_MAP);
		std::vector<std::shared_ptr<Texture2D> > norm = this->load_textures(mat, aiTextureType_NORMALS, model_path);
		if (!norm.empty())
			material.SetTexture(norm[0], Material::NORMAL_MAP);

		/* RETRIEVE MATERIAL PROPERTIES */
		aiColor3D c;
		float value;
			/* DIFFUSE */
		c = aiColor3D(0.0f, 0.0f, 0.0f);
		mat->Get(AI_MATKEY_COLOR_DIFFUSE, c);
		material.SetColor(FT::vec3(c.r, c.g, c.b));
		material.SetColor(FT::vec3(c.r, c.g, c.b), Material::DIFFUSE);
			/* SPECULAR */
		c = aiColor3D(0.0f, 0.0f, 0.0f);
		mat->Get(AI_MATKEY_COLOR_SPECULAR, c);
		material.SetColor(FT::vec3(c.r, c.g, c.b), Material::SPECULAR);
			/* AMBIENT */
		c = aiColor3D(0.0f, 0.0f, 0.0f);
		mat->Get(AI_MATKEY_COLOR_AMBIENT, c);
		material.SetColor(FT::vec3(c.r, c.g, c.b), Material::AMBIENT);
			/* EMISSIVE */
		c = aiColor3D(0.0f, 0.0f, 0.0f);
		mat->Get(AI_MATKEY_COLOR_EMISSIVE, c);
		material.SetColor(FT::vec3(c.r, c.g, c.b), Material::EMISSIVE);
			/* TRANSPARENT */
		c = aiColor3D(0.0f, 0.0f, 0.0f);
		mat->Get(AI_MATKEY_COLOR_TRANSPARENT, c);
		material.SetColor(FT::vec3(c.r, c.g, c.b), Material::TRANSPARENT);
			/* OPACITY */
		value = 0.0;
		mat->Get(AI_MATKEY_OPACITY, value);
		material.SetValue(value, Material::OPACITY);
			/* SHININESS */
		value = 0.0;
		mat->Get(AI_MATKEY_SHININESS, value);
		material.SetValue(value, Material::SHININESS);
			/* SHININESS_STRENGTH */
		value = 0.0;
		mat->Get(AI_MATKEY_SHININESS_STRENGTH, value);
		material.SetValue(value, Material::SHININESS_STRENGTH);
			/* REFRACTI */
		value = 0.0;
		mat->Get(AI_MATKEY_REFRACTI, value);
		material.SetValue(value, Material::REFRACTI);
		
		return material;
	}

	Geometry ResourceManager::process_geometry(const aiScene* scene, aiMesh* mesh)
	{
		std::vector<unsigned int> indices;
		std::vector<Vertex> vertices;
		(void)scene;

		/* Process Mesh */
		const std::string m_name = mesh->mName.C_Str();

		// PROCESS VERTICES
		for (size_t v = 0; v < mesh->mNumVertices; v++)
		{
			Vertex vertex;
			// POSITION
			aiVector3D ai_pos = mesh->mVertices[v];
			vertex.pos = FT::vec3(ai_pos.x, ai_pos.y, ai_pos.z);
			// COLOR
			if (mesh->HasVertexColors(0))
			{
				aiColor4D ai_col = mesh->mColors[0][v];
				vertex.color = FT::vec4(ai_col.r, ai_col.g, ai_col.b, ai_col.a);
			}
			// NORMAL
			if (mesh->HasNormals())
			{
				aiVector3D ai_norm = mesh->mNormals[v];
				vertex.normal = FT::vec3(ai_norm.x, ai_norm.y, ai_norm.z);
			}
			// TEX COORDS
			if (mesh->HasTextureCoords(0))
			{
				aiVector3D ai_tex = mesh->mTextureCoords[0][v];
				vertex.tex_coords = FT::vec3(ai_tex.x, ai_tex.y, ai_tex.z);
			}
			vertices.push_back(vertex);
		}
		// PROCESS INDICES
		for (size_t f = 0; f < mesh->mNumFaces; f++)
			for (size_t i = 0; i < mesh->mFaces[f].mNumIndices; i++)
				indices.push_back(mesh->mFaces[f].mIndices[i]);
		return (Geometry(vertices, indices));
	}

	void ResourceManager::process_mesh(const aiScene* scene, aiMesh* mesh, Model & model, const std::string& node_name)
	{
		Geometry geom = process_geometry(scene, mesh);
		std::vector<Vertex>& vertices = geom.GetVerticesRef();
		Material mat = process_material(scene, mesh, model.GetPath());

		// Extract Bones
		int bone_id_current = 0;
		for (size_t i = 0; i < mesh->mNumBones; i++)
		{
			aiBone* bone = mesh->mBones[i];
			std::string bone_name = bone->mName.C_Str();

			FT::mat4 tr;
			std::memcpy(tr.data, (float*)&bone->mOffsetMatrix, sizeof(tr.data));

			bone_id_current = model.CreateBone(bone_name, node_name, FT::transpose(tr));
			for (size_t w = 0; w < mesh->mBones[i]->mNumWeights; w++)
			{
				aiVertexWeight* weight = mesh->mBones[i]->mWeights;
				size_t vert_id = weight[w].mVertexId;
				float vert_weight = weight[w].mWeight;
				if (vert_id < vertices.size())
					VertexFormat::SetVertexBoneData(vertices[vert_id], bone_id_current, vert_weight);
			}
		}
		Mesh new_mesh(geom, mat);
		new_mesh.SetNodeName(node_name);
		model.AddMesh(new_mesh);
	}

	void ResourceManager::process_node(const aiScene* scene, aiNode* node, aiNode* node_parent, Model & model)
	{
		FT::mat4 tr;
		std::memcpy(tr.data, (float*)&node->mTransformation, sizeof(tr.data));

		std::string node_name = node->mName.C_Str();
		std::string parent_node_name;
		if (node != node_parent)
			parent_node_name = node_parent->mName.C_Str();
		else
			parent_node_name = "";
		model.AddNode(node_name, FT::transpose(tr), parent_node_name);
		for (unsigned int i = 0; i < node->mNumMeshes; i++)
			process_mesh(scene, scene->mMeshes[node->mMeshes[i]], model, node_name);
		for (unsigned int i = 0; i < node->mNumChildren; i++)
			process_node(scene, node->mChildren[i], node, model);
	}

	Model ResourceManager::LoadModel(const std::string & path)
	{
		Model model;
		const struct aiScene * scene = aiImportFile(path.c_str(),
    		aiProcess_CalcTangentSpace       |
    		aiProcess_Triangulate            |
			aiProcess_JoinIdenticalVertices  |
			aiProcess_PopulateArmatureData   |
    		aiProcess_SortByPType);
		if (!scene)
			return (Model(load_cube()));
		model.SetPath(path);

		FT::mat4 tr;
		std::memcpy(tr.data, (float*)&scene->mRootNode->mTransformation, sizeof(tr.data));

		model.SetGlobalInverse(FT::transpose(tr));
		process_node(scene, scene->mRootNode, scene->mRootNode, model);
		aiReleaseImport(scene);
		return (model);
	}
}