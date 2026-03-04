#shader vertex
#version 410 core
layout (location = 0) in vec3 a_pos;
layout (location = 1) in vec3 a_tex_coord;
layout (location = 2) in vec3 a_normal;
layout (location = 3) in vec4 a_col;
layout (location = 4) in ivec4 a_bone_id;
layout (location = 5) in vec4 a_bone_weight;

out DATA
{
	vec4 pos;
	vec3 normal;
	vec4 col;
	vec2 tex_coord;
} vs_out;

const int MAX_BONES = 100;
const int MAX_BONES_PER_VERTEX = 4;
uniform mat4 bone_matrix[MAX_BONES];

uniform mat4 model_mat = mat4(1.0);
uniform mat4 proj_mat = mat4(1.0);
uniform mat4 view_mat = mat4(1.0);
uniform int enabled_bone;

void main()
{
    vec4 totalPosition = vec4(0.0f);
    for(int i = 0 ; i < MAX_BONES_PER_VERTEX ; i++)
    {
        if(a_bone_id[i] == -1) 
            continue;
        if(a_bone_id[i] >=MAX_BONES) 
        {
            totalPosition = vec4(a_pos,1.0f);
            break;
        }
        vec4 localPosition = bone_matrix[a_bone_id[i]] * vec4(a_pos,1.0f);
        totalPosition += localPosition * a_bone_weight[i];
        // vec3 localNormal = mat3(finalBonesMatrices[boneIds[i]]) * norm;
    }
		
    mat4 viewModel = view_mat * model_mat;
    gl_Position =  proj_mat * viewModel * totalPosition;
    vs_out.tex_coord = vec2(a_tex_coord.x, -a_tex_coord.y);
}

#shader fragment
#version 410 core
out vec4 frag_color;

in DATA
{
	vec4 pos;
	vec3 normal;
	vec4 col;
	vec2 tex_coord;
} fs_in;

uniform sampler2D texture_map;
uniform sampler2D diffuse_map;
uniform vec2 mouse_pos;
uniform vec4 flat_color;

void main()
{
	vec2 tc = vec2(fs_in.tex_coord.x, fs_in.tex_coord.y);
	frag_color = texture(diffuse_map, tc);
}
