#type vertex
#version 330 core 
			
layout (location = 0) in vec3 a_Position;
			
uniform mat4 u_ViewProjection;
uniform mat4 u_Model;

out vec3 v_Position;

void main(){
	v_Position = a_Position;
	gl_Position = u_ViewProjection * u_Model * vec4(a_Position.x, a_Position.y, a_Position.z, 1.0);	
}


#type fragment
#version 330 core 
			
layout (location = 0) out vec4 color;
			
in vec3 v_Position;

void main(){
	color = vec4(v_Position.x + 0.5, v_Position.y + 0.1, 0.5, 1.0);	
}