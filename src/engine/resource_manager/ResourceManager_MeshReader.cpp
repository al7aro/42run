#include "ResourceManager.hpp"

namespace FT {

	std::map<std::string, Material> ResourceManager::mesh_mtl_reader(const std::string& path)
	{
		enum LineType
		{
			COMMENT = 0,
			NEWMTL,
			NS, KA, KD, KS, KE, NI, D, ILLUM,
			MAP_KD
		};

		std::map<std::string, Material> materials;
		Material* current_mat = 0;
		std::ifstream f(path);
		if (!f.is_open())
			return (materials);
		std::string line;
		std::string word;

		std::map<std::string, LineType> line_type =
		{
			{"#", LineType::COMMENT},
			{"newmtl", LineType::NEWMTL},
			{"Ns", LineType::NS}, {"Ka", LineType::KA}, {"Kd", LineType::KD},
			{"Ks", LineType::KS}, {"Ke", LineType::KE}, {"Ni", LineType::NI},
			{"d", LineType::D}, {"illum", LineType::ILLUM},
			{"map_Kd", LineType::MAP_KD},
		};

		while (std::getline(f, line))
		{
			std::istringstream sstream(line);
			sstream >> word; // GET THE TYPE OF LINE WE ARE IN
			float x, y, z;
			float value;
			std::shared_ptr<Texture2D> tex;
			switch (line_type[word])
			{
			case LineType::NEWMTL: // Read the material file and create a material from it
				sstream >> word;
				materials[word] = Material();
				current_mat = &materials[word];
				break;
			case LineType::NS:
				sstream >> word; value = std::stof(word);
				if (current_mat)
					current_mat->SetValue(value, Material::SPECULAR);
				break;
			case LineType::KA:
				sstream >> word; x = std::stof(word);
				sstream >> word; y = std::stof(word);
				sstream >> word; z = std::stof(word);
				sstream >> word; value = std::stof(word);
				if (current_mat)
					current_mat->SetColor(FT::vec3(x, y, z), Material::AMBIENT);
				break;
			case LineType::KD:
				sstream >> word; x = std::stof(word);
				sstream >> word; y = std::stof(word);
				sstream >> word; z = std::stof(word);
				sstream >> word; value = std::stof(word);
				if (current_mat)
					current_mat->SetColor(FT::vec3(x, y, z), Material::DIFFUSE);
				break;
			case LineType::KS:
				sstream >> word; x = std::stof(word);
				sstream >> word; y = std::stof(word);
				sstream >> word; z = std::stof(word);
				sstream >> word; value = std::stof(word);
				if (current_mat)
					current_mat->SetColor(FT::vec3(x, y, z), Material::SPECULAR);
				break;
			case LineType::KE:
				sstream >> word; x = std::stof(word);
				sstream >> word; y = std::stof(word);
				sstream >> word; z = std::stof(word);
				sstream >> word; value = std::stof(word);
				if (current_mat)
					current_mat->SetColor(FT::vec3(x, y, z), Material::EMISSIVE);
				break;
			case LineType::NI:
				sstream >> word; value = std::stof(word);
				current_mat->SetValue(value, Material::REFRACTI);
				break;
			case LineType::D:
				sstream >> word; value = std::stof(word);
				if (current_mat)
					current_mat->SetValue(value, Material::OPACITY);
				break;
			case LineType::MAP_KD:
				sstream >> word;
				tex = this->LoadImage(std::filesystem::path(path).parent_path().string() + "/" + word);
				if (tex)
					current_mat->SetTexture(tex, Material::DIFFUSE_MAP);
				break;
			//case LineType::ILLUM:
			//	sstream >> word; value = std::stof(word);
			//	current_mat->SetValue(value, Material::ILLUMINATION);
			//	break;
			default:
				break;
			}
		}
		return (materials);
	}

	Vertex extract_vertex(std::string v1,
		const std::vector<FT::vec3> &pos, const std::vector<FT::vec3> &norm, const std::vector<FT::vec3> &tex)
	{
		int i;
		std::istringstream ssv1(v1);

		Vertex vertex;
		// POSITION
		std::getline(ssv1, v1, '/');
		if (!v1.empty())
		{
			i = std::stoi(v1) - 1;
			vertex.pos = pos[i];
		}
		// TEX COORDS
		std::getline(ssv1, v1, '/');
		if (!v1.empty())
		{
			i = std::stoi(v1) - 1;
			vertex.tex_coords = tex[i];
		}
		// NORMALS
		std::getline(ssv1, v1, '/');
		if (!v1.empty())
		{
			i = std::stoi(v1) - 1;
			vertex.normal = norm[i];
		}
		return (vertex);
	}

	std::vector<Mesh> ResourceManager::mesh_obj_reader(const std::string& path)
	{
		enum LineType
		{
			COMMENT = 0,
			MTLLIB,
			USEMTL,
			OBJ,
			V_POS, V_NORM, V_TEX,
			SHADING,
			FACE,
		};

		std::ifstream f(path);
		if (!f.is_open())
			return (std::vector<Mesh>());
		std::string line;
		std::string word;

		std::map<std::string, LineType> line_type =
		{
			{"#", LineType::COMMENT},
			{"mtllib", LineType::MTLLIB},
			{"usemtl", LineType::USEMTL},
			{"o", LineType::OBJ},
			{"v", LineType::V_POS}, {"vn", LineType::V_NORM}, {"vt", LineType::V_TEX},
			{"s", LineType::SHADING},
			{"f", LineType::FACE},
		};

		// TODO: for now it will only support one .mtl per .obj
		std::map<std::string, Material> materials;
		std::string current_use_material;
		std::vector<Mesh> meshes;
		Mesh* current_mesh;
		std::vector<FT::vec3> pos;
		std::vector<FT::vec3> norm;
		std::vector<FT::vec3> tex;
		std::vector<Vertex> vertices;

		LineType current_line_type = COMMENT;
		LineType prev_line_type = COMMENT;
		
		std::map<std::string, unsigned int> index_map;
		int index_cnt = 0;
		std::vector<unsigned int> indices;

		while (std::getline(f, line))
		{
			std::istringstream sstream(line);
			sstream >> word; // GET THE TYPE OF LINE WE ARE IN
			float x, y, z;
			std::string v1, v2, v3;

			prev_line_type = current_line_type;
			current_line_type = line_type[word];

			if (prev_line_type == LineType::FACE && current_line_type != LineType::FACE)
			{
				current_mesh->SetMaterial(materials[current_use_material]);
				current_mesh->SetGeometry(Geometry(vertices, indices));
			}

			switch (current_line_type)
			{
			case LineType::MTLLIB: // Read the material file and create a material from it
				sstream >> word;
				materials = mesh_mtl_reader(std::filesystem::path(path).parent_path().string() + "/" + word); // TODO: create the material absolute path
				break;
			case LineType::USEMTL: // Create a new mesh using the specified material
				meshes.push_back(Mesh());
				current_mesh = &*meshes.rbegin();
				sstream >> current_use_material;
				vertices.clear();
				indices.clear();
				index_map.clear();
				index_cnt = 0;
				break;
			case LineType::OBJ: // At this point everythign is reset and a new object is about to be read
				break;
			//case LineType::SHADING: // Ignore
			//	break;
			case LineType::FACE: // Info needed (always after usemtl) to create the new mesh
				sstream >> v1;
				sstream >> v2;
				sstream >> v3;
				// WARNING: DOES NOT WORK WITH CONCAVE FACES
				while (!sstream.fail())
				{
					// Vertex 1
					Vertex vertex = extract_vertex(v1, pos, norm, tex);
					if (index_map.find(v1) == index_map.end())
					{
						index_map[v1] = index_cnt;
						indices.push_back(index_cnt);
						vertices.push_back(vertex);
						index_cnt++;
					}
					else
						indices.push_back(index_map[v1]);
					// Vertex 2
					vertex = extract_vertex(v2, pos, norm, tex);
					if (index_map.find(v2) == index_map.end())
					{
						index_map[v2] = index_cnt;
						indices.push_back(index_cnt);
						vertices.push_back(vertex);
						index_cnt++;
					}
					else
						indices.push_back(index_map[v2]);
					// Vertex 3
					vertex = extract_vertex(v3, pos, norm, tex);
					if (index_map.find(v3) == index_map.end())
					{
						index_map[v3] = index_cnt;
						indices.push_back(index_cnt);
						vertices.push_back(vertex);
						index_cnt++;
					}
					else
						indices.push_back(index_map[v3]);
					v2 = v3;
					sstream >> v3;
				}
				break;
			case LineType::V_POS:
				sstream >> word; x = std::stof(word);
				sstream >> word; y = std::stof(word);
				sstream >> word; z = std::stof(word);
				pos.push_back(FT::vec3(x, y, z));
				break;
			case LineType::V_NORM:
				sstream >> word; x = std::stof(word);
				sstream >> word; y = std::stof(word);
				sstream >> word; z = std::stof(word);
				norm.push_back(FT::vec3(x, y, z));
				break;
			case LineType::V_TEX:
				sstream >> word; x = std::stof(word);
				sstream >> word; y = std::stof(word);
				tex.push_back(FT::vec3(x, y, 1.0));
				break;
			default:
				break;
			}
		}
		f.close();
		if (prev_line_type == LineType::FACE)
		{
			current_mesh->SetMaterial(materials[current_use_material]);
			current_mesh->SetGeometry(Geometry(vertices, indices));
		}
		// TODO: return a vector of meshes
		return (meshes);
	}
}