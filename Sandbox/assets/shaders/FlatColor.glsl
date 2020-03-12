#type vertex
#version 330 core 

layout (location = 0) in vec3 a_Position;

uniform mat4 u_ViewProjection;
uniform mat4 u_Transform;

out vec3 v_Position;
out vec4 v_Color;

void main(){
	v_Position = a_Position;
	gl_Position = u_ViewProjection * u_Transform * vec4(a_Position.x, a_Position.y, a_Position.z, 1.0);	
}



#type fragment
#version 330 core 

layout (location = 0) out vec4 color;

in vec3 v_Position;

uniform vec4 u_Color; 

void main(){
	color = u_Color;	
}