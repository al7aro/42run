#shader vertex
#version 410 core
layout (location = 0) in vec3 a_pos;
layout (location = 1) in vec2 a_tex_coord;
layout (location = 3) in vec3 a_col;
layout (location = 4) in ivec4 a_bone_id;
layout (location = 5) in vec4 a_bone_weight;

out DATA
{
	vec4 pos;
	vec4 col;
	vec2 tex_coord;
} vs_out;

uniform mat4 model_mat = mat4(1.0);
uniform mat4 proj_mat = mat4(1.0);
uniform mat4 view_mat = mat4(1.0);

void main()
{
    vs_out.pos = model_mat * vec4(a_pos, 1.0);
    vs_out.col = vec4(a_col.xyz, 1.0);
    vs_out.tex_coord = vec2(a_tex_coord.x, -a_tex_coord.y);

	vec4 p = proj_mat * view_mat * vs_out.pos;
    gl_Position = p;
}

#shader fragment
#version 410 core
out vec4 frag_color;

in DATA
{
	vec4 pos;
	vec4 col;
	vec2 tex_coord;
} fs_in;

struct Material
{
	vec3 col;
	vec3 diffuse;
	vec3 specular;
	vec3 ambient;
	vec3 emissive;
	vec3 transparent;
	float opacity;
	float shininess;
	float shininess_strength;
	float refracti;
};

uniform sampler2D texture_map;
uniform sampler2D diffuse_map;
uniform sampler2D specular_map;
uniform sampler2D normal_map;
uniform vec4 flat_color;
uniform Material mat;

uniform int texture_map_enabled;
uniform int diffuse_map_enabled;
uniform int specular_map_enabled;
uniform int normal_map_enabled;

void main()
{
	if (diffuse_map_enabled == 1)
		frag_color = texture(diffuse_map, fs_in.tex_coord);
	else
		frag_color = vec4(mat.diffuse, 1.0);
}