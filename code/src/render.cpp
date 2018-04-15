#include <GL\glew.h>
#include <glm\gtc\type_ptr.hpp>
#include <glm\gtc\matrix_transform.hpp>
#include <iostream>
#include <cstdio>
#include <cassert>
#include <SDL.h>
#include <time.h>
#include <math.h>
#include "GL_framework.h"

///////// fw decl
namespace ImGui {
	void Render();
}
namespace Box {
	void setupCube();
	void cleanupCube();
	void drawCube();
}
namespace Axis {
	void setupAxis();
	void cleanupAxis();
	void drawAxis();
}

namespace Cube {
	void setupCube();
	void cleanupCube();
	void updateCube(const glm::mat4& transform);
	void drawCube();
}

namespace MyFirstShader {
	void myInitCode(void);
	GLuint cubeShader(void);
	GLuint octocahedronShader(void);

	void myCleanupCode(void);
	void myRenderCode(double currentTime);
	GLuint myRenderProgram[7];
	GLuint myVAO[7];

}

namespace ej1 {
	glm::vec3 pos1;
	glm::vec3 pos2;
}

namespace ej2 {
	int octoAmount = 4;
	float mySize = 1.334;
	glm::vec3* pos = new glm::vec3[octoAmount]{		{ 0, 0, -mySize/2 },
													{ 0, 0, mySize / 2 },
													{ mySize/2, -mySize / 2, 0 },
													{ -mySize / 2, -mySize / 2, 0 }
	};
}

namespace ej3 {
	glm::vec3 seed1;
	glm::vec3 seed2;
	float speed;
}

namespace ej4 {
	int octoAmount = 35;
	glm::vec3* seeds = new glm::vec3[octoAmount];
	float* seedR = new float[octoAmount];
	glm::vec3* degRot = new glm::vec3[octoAmount];
	float speed;
	float lastTime = 0;
}

namespace ej5 {
	int octoAmount = 150;
	glm::vec3* seeds = new glm::vec3[octoAmount];
	float* seedR = new float[octoAmount];
	glm::vec3* degRot = new glm::vec3[octoAmount];
	float speed;
	float lastTime = 0;
	glm::vec3* colores = new glm::vec3[octoAmount];
	bool Ejercicio5;
}

namespace ej6a {
	int octoAmount = 17;

	glm::vec3* pos = new glm::vec3[octoAmount]{ { 0, 0, 0 },
	{ 1.333, 0, 0 },
	{ -0.667, 0.667, -0.667 },
	{ -1.333, 0, 0 },
	{ 0, 1.333, 0 },
	{ 0, -1.333, 0 },
	{ -0.667, 0.667, 0.667 },
	{ 0.667, 0.667, -0.667 },
	{ 1.333, 1.333, 0 },
	{ 1.333, -1.333, 0 },
	{ -1.333, 1.333, 0 },
	{ -1.333, -1.333, 0 },
	{ 0.667, 0.667, 0.667 },
	{ 0.667, -0.667, 0.667 },
	{ -0.667, -0.667, 0.667 },
	{ 0.667, -0.667, -0.667 },
	{ -0.667, -0.667, -0.667 }
	};
	bool Ejercicio5;
}

namespace ej6b {
	int HoneyComb = 17;
	bool samePos[35] = { false };


	glm::vec3* pos = new glm::vec3[HoneyComb]{ { 0, 0, 0 },
												{ 1.333*75, 0, 0 },
												{ -0.667 * 75, 0.667 * 75, -0.667 * 75 },
												{ -1.333 * 75, 0, 0 },
												{ 0, 1.333 * 75, 0 },
												{ 0, -1.333 * 75, 0 },
												{ -0.667 * 75, 0.667 * 75, 0.667 * 75 },
												{ 0.667 * 75, 0.667 * 75, -0.667 * 75 },
												{ 1.333 * 75, 1.333 * 75, 0 },
												{ 1.333 * 75, -1.333 * 75, 0 },
												{ -1.333 * 75, 1.333 * 75, 0 },
												{ -1.333 * 75, -1.333 * 75, 0 },
												{ 0.667 * 75, 0.667 * 75, 0.667 * 75 },
												{ 0.667 * 75, -0.667 * 75, 0.667 * 75 },
												{ -0.667 * 75, -0.667 * 75, 0.667 * 75 },
												{ 0.667 * 75, -0.667 * 75, -0.667 * 75 },
												{ -0.667 * 75, -0.667 * 75, -0.667 * 75 }
	};

}

namespace ej9 {     //En veritat es el 7
	int octoAmount = 17;

	glm::vec3* pos = new glm::vec3[octoAmount]{ { 0, 0, 0 },
	{ 1.333, 0, 0 },
	{ -0.667, 0.667, -0.667 },
	{ -1.333, 0, 0 },
	{ 0, 1.333, 0 },
	{ 0, -1.333, 0 },
	{ -0.667, 0.667, 0.667 },
	{ 0.667, 0.667, -0.667 },
	{ 1.333, 1.333, 0 },
	{ 1.333, -1.333, 0 },
	{ -1.333, 1.333, 0 },
	{ -1.333, -1.333, 0 },
	{ 0.667, 0.667, 0.667 },
	{ 0.667, -0.667, 0.667 },
	{ -0.667, -0.667, 0.667 },
	{ 0.667, -0.667, -0.667 },
	{ -0.667, -0.667, -0.667 }
	};

	bool Ejercicio9;
}

////////////////

namespace RenderVars {
	const float FOV = glm::radians(65.f);
	const float zNear = 1.f;
	const float zFar = 100.f;
	const float width = 800.f;
	const float height = 600.f;

	glm::mat4 _projection;
	glm::mat4 _modelView;
	glm::mat4 _MVP;
	glm::mat4 _inv_modelview;
	glm::vec4 _cameraPoint;

	struct prevMouse {
		float lastx, lasty;
		MouseEvent::Button button = MouseEvent::Button::None;
		bool waspressed = false;
	} prevMouse;

	float panv[3] = { 0.f, -5.f, -15.f };
	float rota[2] = { 0.f, 0.f };
}
namespace RV = RenderVars;

void GLResize(int width, int height) {
	glViewport(0, 0, width, height);
	if (height != 0) RV::_projection = glm::perspective(RV::FOV, (float)width / (float)height, RV::zNear, RV::zFar);
	else RV::_projection = glm::perspective(RV::FOV, 0.f, RV::zNear, RV::zFar);
}

void GLmousecb(MouseEvent ev) {
	if (RV::prevMouse.waspressed && RV::prevMouse.button == ev.button) {
		float diffx = ev.posx - RV::prevMouse.lastx;
		float diffy = ev.posy - RV::prevMouse.lasty;
		switch (ev.button) {
		case MouseEvent::Button::Left: // ROTATE
			RV::rota[0] += diffx * 0.005f;
			RV::rota[1] += diffy * 0.005f;
			break;
		case MouseEvent::Button::Right: // MOVE XY
			RV::panv[0] += diffx * 0.03f;
			RV::panv[1] -= diffy * 0.03f;
			break;
		case MouseEvent::Button::Middle: // MOVE Z
			RV::panv[2] += diffy * 0.05f;
			break;
		default: break;
		}
	}
	else {
		RV::prevMouse.button = ev.button;
		RV::prevMouse.waspressed = true;
	}
	RV::prevMouse.lastx = ev.posx;
	RV::prevMouse.lasty = ev.posy;
}

void GLinit(int width, int height) {
	glViewport(0, 0, width, height);
	glClearColor(0.2f, 0.2f, 0.2f, 1.f);
	glClearDepth(1.f);
	glDepthFunc(GL_LEQUAL);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);

	RV::_projection = glm::perspective(RV::FOV, (float)width / (float)height, RV::zNear, RV::zFar);

	// Setup shaders & geometry
	/*Box::setupCube();
	Axis::setupAxis();
	Cube::setupCube();*/
	MyFirstShader::myInitCode();
}

void GLcleanup() {
	/*Box::cleanupCube();
	Axis::cleanupAxis();
	Cube::cleanupCube();
	*/
	MyFirstShader::myCleanupCode();
}

void GLrender(double currentTime) {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	RV::_modelView = glm::mat4(1.f);
	RV::_modelView = glm::translate(RV::_modelView, glm::vec3(RV::panv[0], RV::panv[1], RV::panv[2]));
	RV::_modelView = glm::rotate(RV::_modelView, RV::rota[1], glm::vec3(1.f, 0.f, 0.f));
	RV::_modelView = glm::rotate(RV::_modelView, RV::rota[0], glm::vec3(0.f, 1.f, 0.f));


	// render code
	/*Box::drawCube();
	Axis::drawAxis();
	Cube::drawCube();*/
	MyFirstShader::myRenderCode(currentTime);


	RV::_MVP = RV::_projection * RV::_modelView;

	ImGui::Render();
}


//////////////////////////////////// COMPILE AND LINK
GLuint compileShader(const char* shaderStr, GLenum shaderType, const char* name = "") {
	GLuint shader = glCreateShader(shaderType);
	glShaderSource(shader, 1, &shaderStr, NULL);
	glCompileShader(shader);
	GLint res;
	glGetShaderiv(shader, GL_COMPILE_STATUS, &res);
	if (res == GL_FALSE) {
		glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &res);
		char *buff = new char[res];
		glGetShaderInfoLog(shader, res, &res, buff);
		fprintf(stderr, "Error Shader %s: %s", name, buff);
		delete[] buff;
		glDeleteShader(shader);
		return 0;
	}
	return shader;
}
void linkProgram(GLuint program) {
	glLinkProgram(program);
	GLint res;
	glGetProgramiv(program, GL_LINK_STATUS, &res);
	if (res == GL_FALSE) {
		glGetProgramiv(program, GL_INFO_LOG_LENGTH, &res);
		char *buff = new char[res];
		glGetProgramInfoLog(program, res, &res, buff);
		fprintf(stderr, "Error Link: %s", buff);
		delete[] buff;
	}
}
/////////////////////////////////////////////MY FIRST SHADER
namespace MyFirstShader {
	void myCleanupCode(void) {
		for (int i = 0; i < 7; ++i) {
			glDeleteVertexArrays(1, &myVAO[i]);
			glDeleteProgram(myRenderProgram[i]);
		}
	}
	///EXERCICI 1
	GLuint cubeShader(void) {

		static const GLchar * vertex_shader_source[] =
		{
			"#version 330														\n\
		void main() {															\n\
			const vec4 vertices[3] = vec4[3](	vec4( 0.25,-0.25, 0.5, 1.0),	\n\
												vec4( 0.25, 0.25, 0.5, 1.0),	\n\
												vec4(-0.25,-0.25, 0.5, 1.0));	\n\
			gl_Position = vertices[gl_VertexID];								\n\
		}"
		};

		static const GLchar * geom_shader_source[] =
		{
			"#version 330																						\n\
			uniform vec3 pos;																					\n\
			uniform float size;																					\n\
			vec4 truePos=vec4(pos.x, pos.y, pos.z, 1);															\n\
			uniform mat4 rotation;																				\n\
			layout(triangles) in;																				\n\
			layout(triangle_strip, max_vertices = 24) out;														\n\
			void main() {																						\n\
				 vec4 vertices[4] =	vec4[4](vec4( size,-size, size, 1.0),										\n\
													vec4( size, size, size, 1.0),								\n\
													vec4(-size,-size, size, 1.0),								\n\
													vec4(-size, size, size, 1.0));								\n\
				for (int i = 0; i < 4; ++i) {																	\n\
					gl_Position = (rotation * vertices[i] ) + truePos;											\n\
					gl_PrimitiveID = 0;\n\
					EmitVertex();																				\n\
				}																								\n\
				EndPrimitive();																					\n\
				 vec4 vertices2[4] =	vec4[4](vec4(-size,-size, -size, 1.0),								\n\
													vec4(-size, size, -size, 1.0),								\n\
													vec4( size,-size, -size, 1.0),								\n\
													vec4( size, size, -size, 1.0));								\n\
				for (int i = 0; i < 4; ++i) {																	\n\
					gl_Position = (rotation * vertices2[i] ) + truePos;							\n\
					gl_PrimitiveID = 1;\n\
					EmitVertex();																				\n\
				}																								\n\
				EndPrimitive();																					\n\
				 vec4 vertices3[4] =	vec4[4](vec4( -size,-size, size, 1.0),								\n\
													vec4( -size, size, size, 1.0),								\n\
													vec4(-size,-size, -size, 1.0),								\n\
													vec4(-size, size, -size, 1.0));								\n\
				for (int i = 0; i < 4; ++i) {																	\n\
					gl_Position = (rotation * vertices3[i] ) + truePos;							\n\
					gl_PrimitiveID = 2;\n\
					EmitVertex();																				\n\
				}																								\n\
				EndPrimitive();																					\n\
				 vec4 vertices4[4] =	vec4[4](vec4( size,-size, -size, 1.0),								\n\
													vec4( size, size, -size, 1.0),								\n\
													vec4(size,-size, size, 1.0),								\n\
													vec4(size, size, size, 1.0));								\n\
				for (int i = 0; i < 4; ++i) {																	\n\
					gl_Position = (rotation * vertices4[i] ) + truePos;							\n\
					gl_PrimitiveID = 3;\n\
					EmitVertex();																				\n\
				}																								\n\
				EndPrimitive();																					\n\
				 vec4 vertices5[4] =	vec4[4](vec4(size, size, size, 1.0),								\n\
													vec4( size, size, -size, 1.0),								\n\
													vec4(-size, size, size, 1.0),								\n\
													vec4(-size, size, -size, 1.0));								\n\
				for (int i = 0; i < 4; ++i) {																	\n\
					gl_Position = (rotation * vertices5[i] ) + truePos;							\n\
					gl_PrimitiveID = 4;\n\
					EmitVertex();																				\n\
				}																								\n\
				EndPrimitive();																					\n\
				 vec4 vertices6[4] =	vec4[4](vec4( size, -size, -size, 1.0),								\n\
													vec4( size, -size, size, 1.0),								\n\
													vec4(-size, -size, -size, 1.0),								\n\
													vec4(-size, -size, size, 1.0));								\n\
				for (int i = 0; i < 4; ++i) {																	\n\
					gl_Position = (rotation * vertices6[i] ) + truePos;							\n\
					gl_PrimitiveID = 5;\n\
					EmitVertex();																				\n\
				}																								\n\
				EndPrimitive();																					\n\
			}"
		};

		static const GLchar * fragment_shader_source[] =
		{
			"#version 330\n\
			\n\
			out vec4 color;\n\
			\n\
			void main() {\n\
				const vec4 colors[6] = vec4[6](	vec4(0.90,0.0,0.13,1.0),\n\
												vec4(0.80,0.0,0.13,1.0),\n\
												vec4(1.0,0.1,0.13,1.0),\n\
												vec4(0.14,0.2,0.829,1.0),\n\
												vec4(0.14,0.17,0.829,1.0),\n\
												vec4(0.1,0.21,0.823,1.0));\n\
				color=colors[gl_PrimitiveID];\n\
			}"
		};

		GLuint vertex_shader;
		GLuint fragment_shader;
		GLuint geom_shader;
		GLuint program;

		vertex_shader = glCreateShader(GL_VERTEX_SHADER);
		glShaderSource(vertex_shader, 1, vertex_shader_source, NULL);
		glCompileShader(vertex_shader);

		geom_shader = glCreateShader(GL_GEOMETRY_SHADER);
		glShaderSource(geom_shader, 1, geom_shader_source, NULL);
		glCompileShader(geom_shader);

		fragment_shader = glCreateShader(GL_FRAGMENT_SHADER);
		glShaderSource(fragment_shader, 1, fragment_shader_source, NULL);
		glCompileShader(fragment_shader);

		program = glCreateProgram();
		glAttachShader(program, vertex_shader);
		glAttachShader(program, geom_shader);
		glAttachShader(program, fragment_shader);
		glLinkProgram(program);

		glDeleteShader(vertex_shader);
		glDeleteShader(geom_shader);
		glDeleteShader(fragment_shader);

		return program;
	}

	GLuint octocahedronShader(void) {

		static const GLchar * overtex_shader_source[] =
		{
			"#version 330														\n\
		void main() {															\n\
			const vec4 vertices[3] = vec4[3](	vec4( 0.25,-0.25, 0.5, 1.0),	\n\
												vec4( 0.25, 0.25, 0.5, 1.0),	\n\
												vec4(-0.25,-0.25, 0.5, 1.0));	\n\
			gl_Position = vertices[gl_VertexID];								\n\
		}"
		};

		static GLchar * ogeom_shader_source[] =
		{
			"#version 330																						\n\
			uniform float mySize;																				\n\
			uniform float time;																					\n\
			uniform bool Ejercicio9;																			\n\
			uniform vec3 pos;																					\n\
			vec4 truePos=vec4(pos.x, pos.y, pos.z, 1);															\n\
			vec4 truePos1=vec4(pos.x+time, pos.y, pos.z+time, 1);															\n\
			vec4 truePos2=vec4(pos.x+time, pos.y, pos.z-time, 1);															\n\
			vec4 truePos3=vec4(pos.x-time, pos.y, pos.z+time, 1);															\n\
			vec4 truePos4=vec4(pos.x-time, pos.y, pos.z-time, 1);															\n\
			vec4 fix= vec4(0, mySize, 0, 0);																	\n\
			uniform mat4 rotation;																				\n\
			uniform mat4 scale;																					\n\
			uniform bool localRot;																				\n\
			layout(triangles) in;																				\n\
			layout(triangle_strip, max_vertices = 104) out;														\n\
			void main() {																						\n\
			if (Ejercicio9 == false){																			\n\
				vec4 vertices[4] =	vec4[4](vec4( 0, mySize/3, -mySize/3, 1.0),									\n\
													vec4( mySize/3, mySize/3, 0, 1.0),							\n\
													vec4( -mySize/3, mySize/3, 0, 1.0),							\n\
													vec4( 0, mySize/3, mySize/3, 1.0));							\n\
				for (int i = 0; i < 4; ++i) {																	\n\
					if(localRot)																				\n\
						gl_Position = (rotation * (vertices[i]  + truePos));									\n\
					else																						\n\
						gl_Position = (rotation * (vertices[i]-fix))  + truePos;								\n\
					gl_PrimitiveID = 0;																			\n\
					EmitVertex();																				\n\
				}																								\n\
				EndPrimitive();																					\n\
				vec4 vertices2[4] =	vec4[4](vec4( 0, 5*mySize/3, -mySize/3, 1.0),								\n\
													vec4( -mySize/3, 5*mySize/3, 0, 1.0),						\n\
													vec4( mySize/3, 5*mySize/3, 0, 1.0),						\n\
													vec4( 0, 5*mySize/3, mySize/3, 1.0));						\n\
				for (int i = 0; i < 4; ++i) {																	\n\
					if(localRot)																				\n\
						gl_Position = rotation * (vertices2[i]  + truePos);										\n\
					else																						\n\
						gl_Position = (rotation * (vertices2[i]-fix))  + truePos;								\n\
					gl_PrimitiveID = 0;																			\n\
					EmitVertex();																				\n\
				}																								\n\
				EndPrimitive();																					\n\
				vec4 vertices3[4] =	vec4[4](vec4( 0, 2*mySize/3, 2*mySize/3, 1.0),								\n\
													vec4( mySize/3, mySize, 2*mySize/3, 1.0),					\n\
													vec4( -mySize/3, mySize, 2*mySize/3, 1.0),					\n\
													vec4( 0, 4*mySize/3, 2*mySize/3, 1.0));						\n\
				for (int i = 0; i < 4; ++i) {																	\n\
					if(localRot)																				\n\
						gl_Position = rotation * (vertices3[i]  + truePos);										\n\
					else																						\n\
						gl_Position = (rotation * (vertices3[i]-fix))  + truePos;								\n\
					gl_PrimitiveID = 0;																			\n\
					EmitVertex();																				\n\
				}																								\n\
				EndPrimitive();																					\n\
				vec4 vertices4[4] =	vec4[4](vec4( 0, 2*mySize/3, -2*mySize/3, 1.0),								\n\
													vec4( -mySize/3, mySize, -2*mySize/3, 1.0),					\n\
													vec4( mySize/3, mySize, -2*mySize/3, 1.0),					\n\
													vec4( 0, 4*mySize/3, -2*mySize/3, 1.0));					\n\
				for (int i = 0; i < 4; ++i) {																	\n\
					if(localRot)																				\n\
						gl_Position = rotation * (vertices4[i]  + truePos);										\n\
					else																						\n\
						gl_Position = (rotation * (vertices4[i]-fix))  + truePos;								\n\
					gl_PrimitiveID = 0;																			\n\
					EmitVertex();																				\n\
				}																								\n\
				EndPrimitive();																					\n\
				vec4 vertices5[4] =	vec4[4](vec4(-2*mySize/3, 2*mySize/3, 0, 1.0),								\n\
													vec4(-2*mySize/3, mySize, mySize/3, 1.0),					\n\
													vec4(-2*mySize/3, mySize, -mySize/3, 1.0),					\n\
													vec4(-2*mySize/3, 4*mySize/3, 0, 1.0));						\n\
				for (int i = 0; i < 4; ++i) {																	\n\
					if(localRot)																				\n\
						gl_Position = rotation * (vertices5[i]  + truePos);										\n\
					else																						\n\
						gl_Position = (rotation * (vertices5[i]-fix))  + truePos;								\n\
					gl_PrimitiveID = 0;																			\n\
					EmitVertex();																				\n\
				}																								\n\
				EndPrimitive();																					\n\
				vec4 vertices6[4] =	vec4[4](vec4(2*mySize/3, 2*mySize/3, 0, 1.0),								\n\
													vec4(2*mySize/3, mySize, -mySize/3, 1.0),					\n\
													vec4(2*mySize/3, mySize, mySize/3, 1.0),					\n\
													vec4(2*mySize/3, 4*mySize/3, 0, 1.0));						\n\
				for (int i = 0; i < 4; ++i) {																	\n\
					if(localRot)																				\n\
						gl_Position = rotation * (vertices6[i]  + truePos);										\n\
					else																						\n\
						gl_Position = (rotation * (vertices6[i]-fix))  + truePos;								\n\
					gl_PrimitiveID = 0;																			\n\
					EmitVertex();																				\n\
				}																								\n\
				EndPrimitive();																					\n\
				vec4 vertices7[4] =	vec4[4](vec4( mySize/3, mySize/3, 0, 1.0),									\n\
													vec4( 2*mySize/3, mySize, mySize/3, 1.0),					\n\
													vec4( 0, mySize/3, mySize/3, 1.0),							\n\
													vec4( mySize/3, mySize, 2*mySize/3, 1.0));					\n\
				for (int i = 0; i < 4; ++i) {																	\n\
					if(localRot)																				\n\
						gl_Position = rotation * (vertices7[i]  + truePos);										\n\
					else																						\n\
						gl_Position = (rotation * (vertices7[i]-fix))  + truePos;								\n\
					gl_PrimitiveID = 1;																			\n\
					EmitVertex();																				\n\
				}																								\n\
				EndPrimitive();																					\n\
				vec4 vertices8[3] =	vec4[3](vec4( 0, mySize/3, mySize/3, 1.0),									\n\
													vec4( mySize/3, mySize, 2*mySize/3, 1.0),					\n\
													vec4( 0, 2*mySize/3, 2*mySize/3, 1.0));						\n\
				for (int i = 0; i < 3; ++i) {																	\n\
					if(localRot)																				\n\
						gl_Position = rotation * (vertices8[i]  + truePos);										\n\
					else																						\n\
						gl_Position = (rotation * (vertices8[i]-fix))  + truePos;								\n\
					gl_PrimitiveID = 1;																			\n\
					EmitVertex();																				\n\
				}																								\n\
				EndPrimitive();																					\n\
				vec4 vertices9[3] =	vec4[3](vec4( mySize/3, mySize/3, 0, 1.0),									\n\
													vec4( 2*mySize/3, 2*mySize/3, 0, 1.0),						\n\
													vec4( 2*mySize/3, mySize, mySize/3, 1.0));					\n\
				for (int i = 0; i < 3; ++i) {																	\n\
					if(localRot)																				\n\
						gl_Position = rotation * (vertices9[i]  + truePos);										\n\
					else																						\n\
						gl_Position = (rotation * (vertices9[i]-fix))  + truePos;								\n\
					gl_PrimitiveID = 1;																			\n\
					EmitVertex();																				\n\
				}																								\n\
				EndPrimitive();"

			"vec4 vertices10[4] =	vec4[4](vec4( 0, mySize/3, mySize/3, 1.0),									\n\
													vec4( -mySize/3, mySize, 2*mySize/3, 1.0),					\n\
													vec4( -mySize/3, mySize/3, 0, 1.0),							\n\
													vec4( -2*mySize/3, mySize, mySize/3, 1.0));					\n\
				for (int i = 0; i < 4; ++i) {																	\n\
					if(localRot)																				\n\
						gl_Position = rotation * (vertices10[i]  + truePos);									\n\
					else																						\n\
						gl_Position = (rotation * (vertices10[i]-fix))  + truePos;								\n\
					gl_PrimitiveID = 2;																			\n\
					EmitVertex();																				\n\
				}																								\n\
				EndPrimitive();																					\n\
				 vec4 vertices11[3] =	vec4[3](vec4( 0, mySize/3, mySize/3, 1.0),								\n\
													vec4( 0, 2*mySize/3, 2*mySize/3, 1.0),						\n\
													vec4( -mySize/3, mySize, 2*mySize/3, 1.0));					\n\
				for (int i = 0; i < 3; ++i) {																	\n\
					if(localRot)																				\n\
						gl_Position = rotation * (vertices11[i]  + truePos);									\n\
					else																						\n\
						gl_Position = (rotation * (vertices11[i]-fix))  + truePos;								\n\
					gl_PrimitiveID = 2;																			\n\
					EmitVertex();																				\n\
				}																								\n\
				EndPrimitive();																					\n\
				 vec4 vertices12[3] =	vec4[3](vec4( -mySize/3, mySize/3, 0, 1.0),								\n\
													vec4( -2*mySize/3, mySize, mySize/3, 1.0),					\n\
													vec4( -2*mySize/3, 2*mySize/3, 0, 1.0));					\n\
				for (int i = 0; i < 3; ++i) {																	\n\
					if(localRot)																				\n\
						gl_Position = rotation * (vertices12[i]  + truePos);									\n\
					else																						\n\
						gl_Position = (rotation * (vertices12[i]-fix))  + truePos;								\n\
					gl_PrimitiveID = 2;																			\n\
					EmitVertex();																				\n\
				}																								\n\
				EndPrimitive();																					\n\
				 vec4 vertices13[4] =	vec4[4](vec4( 0, mySize/3, -mySize/3, 1.0),								\n\
													vec4( -mySize/3, mySize/3, 0, 1.0),							\n\
													vec4( -mySize/3, mySize, -2*mySize/3, 1.0),					\n\
													vec4( -2*mySize/3, mySize, -mySize/3, 1.0));				\n\
				for (int i = 0; i < 4; ++i) {																	\n\
					if(localRot)																				\n\
						gl_Position = rotation * (vertices13[i]  + truePos);									\n\
					else																						\n\
						gl_Position = (rotation * (vertices13[i]-fix))  + truePos;								\n\
					gl_PrimitiveID = 1;																			\n\
					EmitVertex();																				\n\
				}																								\n\
				EndPrimitive();																					\n\
				 vec4 vertices14[3] =	vec4[3](vec4( -mySize/3, mySize, -2*mySize/3, 1.0),						\n\
													vec4( 0, 2*mySize/3, -2*mySize/3, 1.0),						\n\
													vec4( 0, mySize/3, -mySize/3, 1.0));						\n\
				for (int i = 0; i < 3; ++i) {																	\n\
					if(localRot)																				\n\
						gl_Position = rotation * (vertices14[i]  + truePos);									\n\
					else																						\n\
						gl_Position = (rotation * (vertices14[i]-fix))  + truePos;								\n\
					gl_PrimitiveID = 1;																			\n\
					EmitVertex();																				\n\
				}																								\n\
				EndPrimitive();																					\n\
				 vec4 vertices15[3] =	vec4[3](vec4( -2*mySize/3, 2*mySize/3, 0, 1.0),							\n\
													vec4( -2*mySize/3, mySize, -mySize/3, 1.0),					\n\
													vec4( -mySize/3, mySize/3, 0, 1.0));						\n\
				for (int i = 0; i < 3; ++i) {																	\n\
					if(localRot)																				\n\
						gl_Position = rotation * (vertices15[i]  + truePos);									\n\
					else																						\n\
						gl_Position = (rotation * (vertices15[i]-fix))  + truePos;								\n\
					gl_PrimitiveID = 1;																			\n\
					EmitVertex();																				\n\
				}																								\n\
				EndPrimitive();																					\n\
				 vec4 vertices16[4] =	vec4[4](vec4( mySize/3, mySize/3, 0, 1.0),								\n\
													vec4( 0, mySize/3, -mySize/3, 1.0),							\n\
													vec4( 2*mySize/3, mySize, -mySize/3, 1.0),					\n\
													vec4( mySize/3, mySize, -2*mySize/3, 1.0));					\n\
				for (int i = 0; i < 4; ++i) {																	\n\
					if(localRot)																				\n\
						gl_Position = rotation * (vertices16[i]  + truePos);									\n\
					else																						\n\
						gl_Position = (rotation * (vertices16[i]-fix))  + truePos;								\n\
					gl_PrimitiveID = 2;																			\n\
					EmitVertex();																				\n\
				}																								\n\
				EndPrimitive();																					\n\
				 vec4 vertices17[3] =	vec4[3](vec4( 0, 2*mySize/3, -2*mySize/3, 1.0),							\n\
													vec4( mySize/3, mySize, -2*mySize/3, 1.0),					\n\
													vec4( 0, mySize/3, -mySize/3, 1.0));						\n\
				for (int i = 0; i < 3; ++i) {																	\n\
					if(localRot)																				\n\
						gl_Position = rotation * (vertices17[i]  + truePos);									\n\
					else																						\n\
						gl_Position = (rotation * (vertices17[i]-fix))  + truePos;								\n\
					gl_PrimitiveID = 2;																			\n\
					EmitVertex();																				\n\
				}																								\n\
				EndPrimitive();																					\n\
				 vec4 vertices18[3] =	vec4[3](vec4( 2*mySize/3, mySize, -mySize/3, 1.0),						\n\
													vec4( 2*mySize/3, 2*mySize/3, 0, 1.0),						\n\
													vec4( mySize/3, mySize/3, 0, 1.0));							\n\
				for (int i = 0; i < 3; ++i) {																	\n\
					if(localRot)																				\n\
						gl_Position = rotation * (vertices18[i]  + truePos);									\n\
					else																						\n\
						gl_Position = (rotation * (vertices18[i]-fix))  + truePos;								\n\
					gl_PrimitiveID = 2;																			\n\
					EmitVertex();																				\n\
				}																								\n\
				EndPrimitive();																					\n\
				 vec4 vertices19[4] =	vec4[4](vec4( mySize/3, 5*mySize/3, 0, 1.0),							\n\
													vec4( 0, 5*mySize/3, mySize/3, 1.0),						\n\
													vec4( 2*mySize/3, mySize, mySize/3, 1.0),					\n\
													vec4( mySize/3, mySize, 2*mySize/3, 1.0));					\n\
				for (int i = 0; i < 4; ++i) {																	\n\
					if(localRot)																				\n\
						gl_Position = rotation * (vertices19[i]  + truePos);									\n\
					else																						\n\
						gl_Position = (rotation * (vertices19[i]-fix))  + truePos;								\n\
					gl_PrimitiveID = 2;																			\n\
					EmitVertex();																				\n\
				}																								\n\
				EndPrimitive();																					\n\
				 vec4 vertices20[3] =	vec4[3](vec4( 0, 4*mySize/3, 2*mySize/3, 1.0),							\n\
													vec4( mySize/3, mySize, 2*mySize/3, 1.0),					\n\
													vec4( 0, 5*mySize/3, mySize/3, 1.0));						\n\
				for (int i = 0; i < 3; ++i) {																	\n\
					if(localRot)																				\n\
						gl_Position = rotation * (vertices20[i]  + truePos);									\n\
					else																						\n\
						gl_Position = (rotation * (vertices20[i]-fix))  + truePos;								\n\
					gl_PrimitiveID = 2;																			\n\
					EmitVertex();																				\n\
				}																								\n\
				EndPrimitive();																					\n\
				vec4 vertices21[3] =	vec4[3](vec4( 2*mySize/3, mySize, mySize/3, 1.0),						\n\
													vec4( 2*mySize/3, 4*mySize/3, 0, 1.0),						\n\
													vec4( mySize/3, 5*mySize/3, 0, 1.0));						\n\
				for (int i = 0; i < 3; ++i) {																	\n\
					if(localRot)																				\n\
						gl_Position = rotation * (vertices21[i]  + truePos);									\n\
					else																						\n\
						gl_Position = (rotation * (vertices21[i]-fix))  + truePos;								\n\
					gl_PrimitiveID = 2;																			\n\
					EmitVertex();																				\n\
				}																								\n\
				EndPrimitive();																					\n\
				 vec4 vertices22[4] =	vec4[4](vec4( 0, 5*mySize/3, mySize/3, 1.0),							\n\
													vec4( -mySize/3, 5*mySize/3, 0, 1.0),						\n\
													vec4( -mySize/3, mySize, 2*mySize/3, 1.0),					\n\
													vec4( -2*mySize/3, mySize, mySize/3, 1.0));					\n\
				for (int i = 0; i < 4; ++i) {																	\n\
					if(localRot)																				\n\
						gl_Position = rotation * (vertices22[i]  + truePos);									\n\
					else																						\n\
						gl_Position = (rotation * (vertices22[i]-fix))  + truePos;								\n\
					gl_PrimitiveID = 1;																			\n\
					EmitVertex();																				\n\
				}																								\n\
				EndPrimitive();																					\n\
				 vec4 vertices23[3] =	vec4[3](vec4( -mySize/3, mySize, 2*mySize/3, 1.0),						\n\
													vec4( 0, 4*mySize/3, 2*mySize/3, 1.0),						\n\
													vec4( 0, 5*mySize/3, mySize/3, 1.0));						\n\
				for (int i = 0; i < 3; ++i) {																	\n\
					if(localRot)																				\n\
						gl_Position = rotation * (vertices23[i]  + truePos);									\n\
					else																						\n\
						gl_Position = (rotation * (vertices23[i]-fix))  + truePos;								\n\
					gl_PrimitiveID = 1;																			\n\
					EmitVertex();																				\n\
				}																								\n\
				EndPrimitive();																					\n\
				 vec4 vertices24[3] =	vec4[3](vec4( -2*mySize/3, 4*mySize/3, 0, 1.0),							\n\
													vec4( -2*mySize/3, mySize, mySize/3, 1.0),					\n\
													vec4( -mySize/3, 5*mySize/3, 0, 1.0));						\n\
				for (int i = 0; i < 3; ++i) {																	\n\
					if(localRot)																				\n\
						gl_Position = rotation * (vertices24[i]  + truePos);									\n\
					else																						\n\
						gl_Position = (rotation * (vertices24[i]-fix))  + truePos;								\n\
					gl_PrimitiveID = 1;																			\n\
					EmitVertex();																				\n\
				}																								\n\
				EndPrimitive();																					\n\
				 vec4 vertices25[4] =	vec4[4](vec4( 0, 5*mySize/3, -mySize/3, 1.0),							\n\
													vec4( -mySize/3, mySize, -2*mySize/3, 1.0),					\n\
													vec4( -mySize/3, 5*mySize/3, 0, 1.0),						\n\
													vec4( -2*mySize/3, mySize, -mySize/3, 1.0));				\n\
				for (int i = 0; i < 4; ++i) {																	\n\
					if(localRot)																				\n\
						gl_Position = rotation * (vertices25[i]  + truePos);									\n\
					else																						\n\
						gl_Position = (rotation * (vertices25[i]-fix))  + truePos;								\n\
					gl_PrimitiveID = 2;																			\n\
					EmitVertex();																				\n\
				}																								\n\
				EndPrimitive();																					\n\
				 vec4 vertices26[3] =	vec4[3](vec4( 0, 5*mySize/3, -mySize/3, 1.0),							\n\
													vec4( 0, 4*mySize/3, -2*mySize/3, 1.0),						\n\
													vec4( -mySize/3, mySize, -2*mySize/3, 1.0));				\n\
				for (int i = 0; i < 3; ++i) {																	\n\
					if(localRot)																				\n\
						gl_Position = rotation * (vertices26[i]  + truePos);									\n\
					else																						\n\
						gl_Position = (rotation * (vertices26[i]-fix))  + truePos;								\n\
					gl_PrimitiveID = 2;																			\n\
					EmitVertex();																				\n\
				}																								\n\
				EndPrimitive();																					\n\
				 vec4 vertices27[3] =	vec4[3](vec4( -mySize/3, 5*mySize/3, 0, 1.0),							\n\
													vec4( -2*mySize/3, mySize, -mySize/3, 1.0),					\n\
													vec4( -2*mySize/3, 4*mySize/3, 0, 1.0));					\n\
				for (int i = 0; i < 3; ++i) {																	\n\
					if(localRot)																				\n\
						gl_Position = rotation * (vertices27[i]  + truePos);									\n\
					else																						\n\
						gl_Position = (rotation * (vertices27[i]-fix))  + truePos;								\n\
					gl_PrimitiveID = 2;																			\n\
					EmitVertex();																				\n\
				}																								\n\
				EndPrimitive();																					\n\
				 vec4 vertices28[4] =	vec4[4](vec4( mySize/3, 5*mySize/3, 0, 1.0),							\n\
													vec4( 2*mySize/3, mySize, -mySize/3, 1.0),					\n\
													vec4( 0, 5*mySize/3, -mySize/3, 1.0),						\n\
													vec4( mySize/3, mySize, -2*mySize/3, 1.0));					\n\
				for (int i = 0; i < 4; ++i) {																	\n\
					if(localRot)																				\n\
						gl_Position = rotation * (vertices28[i]  + truePos);									\n\
					else																						\n\
						gl_Position = (rotation * (vertices28[i]-fix))  + truePos;								\n\
					gl_PrimitiveID = 1;																			\n\
					EmitVertex();																				\n\
				}																								\n\
				EndPrimitive();																					\n\
				 vec4 vertices29[3] =	vec4[3](vec4( 0, 5*mySize/3, -mySize/3, 1.0),							\n\
													vec4( mySize/3, mySize, -2*mySize/3, 1.0),					\n\
													vec4( 0, 4*mySize/3, -2*mySize/3, 1.0));					\n\
				for (int i = 0; i < 3; ++i) {																	\n\
					if(localRot)																				\n\
						gl_Position = rotation * (vertices29[i]  + truePos);									\n\
					else																						\n\
						gl_Position = (rotation * (vertices29[i]-fix))  + truePos;								\n\
					gl_PrimitiveID = 1;																			\n\
					EmitVertex();																				\n\
				}																								\n\
				EndPrimitive();																					\n\
				 vec4 vertices30[3] =	vec4[3](vec4( mySize/3, 5*mySize/3, 0, 1.0),							\n\
													vec4( 2*mySize/3, 4*mySize/3, 0, 1.0),						\n\
													vec4( 2*mySize/3, mySize, -mySize/3, 1.0));					\n\
				for (int i = 0; i < 3; ++i) {																	\n\
					if(localRot)																				\n\
						gl_Position = rotation * (vertices30[i]  + truePos);									\n\
					else																						\n\
						gl_Position = (rotation * (vertices30[i]-fix))  + truePos;								\n\
					gl_PrimitiveID = 1;																			\n\
					EmitVertex();																				\n\
				}																								\n\
				EndPrimitive();																					\n\
			}"

			"else{																								\n\
				vec4 vertices[4] =	vec4[4](vec4( 0, mySize/3, -mySize/3, 1.0),									\n\
													vec4( mySize/3, mySize/3, 0, 1.0),							\n\
													vec4( -mySize/3, mySize/3, 0, 1.0),							\n\
													vec4( 0, mySize/3, mySize/3, 1.0));							\n\
				for (int i = 0; i < 4; ++i) {																	\n\
					if(localRot)																				\n\
						gl_Position = (rotation * (vertices[i]  + truePos1));									\n\
					else																						\n\
						gl_Position = (rotation * (vertices[i]-fix))  + truePos1;								\n\
					gl_PrimitiveID = 0;																			\n\
					EmitVertex();																				\n\
				}																								\n\
				EndPrimitive();																					\n\
				vec4 vertices2[4] =	vec4[4](vec4( 0, 5*mySize/3, -mySize/3, 1.0),								\n\
													vec4( -mySize/3, 5*mySize/3, 0, 1.0),						\n\
													vec4( mySize/3, 5*mySize/3, 0, 1.0),						\n\
													vec4( 0, 5*mySize/3, mySize/3, 1.0));						\n\
				for (int i = 0; i < 4; ++i) {																	\n\
					if(localRot)																				\n\
						gl_Position = rotation * (vertices2[i]  + truePos1);										\n\
					else																						\n\
						gl_Position = (rotation * (vertices2[i]-fix))  + truePos1;								\n\
					gl_PrimitiveID = 0;																			\n\
					EmitVertex();																				\n\
				}																								\n\
				EndPrimitive();																					\n\
				vec4 vertices3[4] =	vec4[4](vec4( 0, 2*mySize/3, 2*mySize/3, 1.0),								\n\
													vec4( mySize/3, mySize, 2*mySize/3, 1.0),					\n\
													vec4( -mySize/3, mySize, 2*mySize/3, 1.0),					\n\
													vec4( 0, 4*mySize/3, 2*mySize/3, 1.0));						\n\
				for (int i = 0; i < 4; ++i) {																	\n\
					if(localRot)																				\n\
						gl_Position = rotation * (vertices3[i]  + truePos1);										\n\
					else																						\n\
						gl_Position = (rotation * (vertices3[i]-fix))  + truePos1;								\n\
					gl_PrimitiveID = 0;																			\n\
					EmitVertex();																				\n\
				}																								\n\
				EndPrimitive();																					\n\
				vec4 vertices4[4] =	vec4[4](vec4( 0, 2*mySize/3, -2*mySize/3, 1.0),								\n\
													vec4( -mySize/3, mySize, -2*mySize/3, 1.0),					\n\
													vec4( mySize/3, mySize, -2*mySize/3, 1.0),					\n\
													vec4( 0, 4*mySize/3, -2*mySize/3, 1.0));					\n\
				for (int i = 0; i < 4; ++i) {																	\n\
					if(localRot)																				\n\
						gl_Position = rotation * (vertices4[i]  + truePos1);										\n\
					else																						\n\
						gl_Position = (rotation * (vertices4[i]-fix))  + truePos1;								\n\
					gl_PrimitiveID = 0;																			\n\
					EmitVertex();																				\n\
				}																								\n\
				EndPrimitive();																					\n\
				vec4 vertices5[4] =	vec4[4](vec4(-2*mySize/3, 2*mySize/3, 0, 1.0),								\n\
													vec4(-2*mySize/3, mySize, mySize/3, 1.0),					\n\
													vec4(-2*mySize/3, mySize, -mySize/3, 1.0),					\n\
													vec4(-2*mySize/3, 4*mySize/3, 0, 1.0));						\n\
				for (int i = 0; i < 4; ++i) {																	\n\
					if(localRot)																				\n\
						gl_Position = rotation * (vertices5[i]  + truePos1);										\n\
					else																						\n\
						gl_Position = (rotation * (vertices5[i]-fix))  + truePos1;								\n\
					gl_PrimitiveID = 0;																			\n\
					EmitVertex();																				\n\
				}																								\n\
				EndPrimitive();																					\n\
				vec4 vertices6[4] =	vec4[4](vec4(2*mySize/3, 2*mySize/3, 0, 1.0),								\n\
													vec4(2*mySize/3, mySize, -mySize/3, 1.0),					\n\
													vec4(2*mySize/3, mySize, mySize/3, 1.0),					\n\
													vec4(2*mySize/3, 4*mySize/3, 0, 1.0));						\n\
				for (int i = 0; i < 4; ++i) {																	\n\
					if(localRot)																				\n\
						gl_Position = rotation * (vertices6[i]  + truePos1);										\n\
					else																						\n\
						gl_Position = (rotation * (vertices6[i]-fix))  + truePos1;								\n\
					gl_PrimitiveID = 0;																			\n\
					EmitVertex();																				\n\
				}																								\n\
				EndPrimitive();																					\n\
				vec4 vertices7[4] =	vec4[4](vec4( mySize/3, mySize/3, 0, 1.0),									\n\
													vec4( 2*mySize/3, mySize, mySize/3, 1.0),					\n\
													vec4( 0, mySize/3, mySize/3, 1.0),							\n\
													vec4( mySize/3, mySize, 2*mySize/3, 1.0));					\n\
				for (int i = 0; i < 4; ++i) {																	\n\
					if(localRot)																				\n\
						gl_Position = rotation * (vertices7[i]  + truePos1);										\n\
					else																						\n\
						gl_Position = (rotation * (vertices7[i]-fix))  + truePos1;								\n\
					gl_PrimitiveID = 1;																			\n\
					EmitVertex();																				\n\
				}																								\n\
				EndPrimitive();																					\n\
				vec4 vertices8[3] =	vec4[3](vec4( 0, mySize/3, mySize/3, 1.0),									\n\
													vec4( mySize/3, mySize, 2*mySize/3, 1.0),					\n\
													vec4( 0, 2*mySize/3, 2*mySize/3, 1.0));						\n\
				for (int i = 0; i < 3; ++i) {																	\n\
					if(localRot)																				\n\
						gl_Position = rotation * (vertices8[i]  + truePos1);										\n\
					else																						\n\
						gl_Position = (rotation * (vertices8[i]-fix))  + truePos1;								\n\
					gl_PrimitiveID = 1;																			\n\
					EmitVertex();																				\n\
				}																								\n\
				EndPrimitive();																					\n\
				vec4 vertices9[3] =	vec4[3](vec4( mySize/3, mySize/3, 0, 1.0),									\n\
													vec4( 2*mySize/3, 2*mySize/3, 0, 1.0),						\n\
													vec4( 2*mySize/3, mySize, mySize/3, 1.0));					\n\
				for (int i = 0; i < 3; ++i) {																	\n\
					if(localRot)																				\n\
						gl_Position = rotation * (vertices9[i]  + truePos1);										\n\
					else																						\n\
						gl_Position = (rotation * (vertices9[i]-fix))  + truePos1;								\n\
					gl_PrimitiveID = 1;																			\n\
					EmitVertex();																				\n\
				}																								\n\
				EndPrimitive();"

			"vec4 vertices10[4] =	vec4[4](vec4( 0, mySize/3, mySize/3, 1.0),									\n\
													vec4( -mySize/3, mySize, 2*mySize/3, 1.0),					\n\
													vec4( -mySize/3, mySize/3, 0, 1.0),							\n\
													vec4( -2*mySize/3, mySize, mySize/3, 1.0));					\n\
				for (int i = 0; i < 4; ++i) {																	\n\
					if(localRot)																				\n\
						gl_Position = rotation * (vertices10[i]  + truePos1);									\n\
					else																						\n\
						gl_Position = (rotation * (vertices10[i]-fix))  + truePos1;								\n\
					gl_PrimitiveID = 2;																			\n\
					EmitVertex();																				\n\
				}																								\n\
				EndPrimitive();																					\n\
				 vec4 vertices11[3] =	vec4[3](vec4( 0, mySize/3, mySize/3, 1.0),								\n\
													vec4( 0, 2*mySize/3, 2*mySize/3, 1.0),						\n\
													vec4( -mySize/3, mySize, 2*mySize/3, 1.0));					\n\
				for (int i = 0; i < 3; ++i) {																	\n\
					if(localRot)																				\n\
						gl_Position = rotation * (vertices11[i]  + truePos1);									\n\
					else																						\n\
						gl_Position = (rotation * (vertices11[i]-fix))  + truePos1;								\n\
					gl_PrimitiveID = 2;																			\n\
					EmitVertex();																				\n\
				}																								\n\
				EndPrimitive();																					\n\
				 vec4 vertices12[3] =	vec4[3](vec4( -mySize/3, mySize/3, 0, 1.0),								\n\
													vec4( -2*mySize/3, mySize, mySize/3, 1.0),					\n\
													vec4( -2*mySize/3, 2*mySize/3, 0, 1.0));					\n\
				for (int i = 0; i < 3; ++i) {																	\n\
					if(localRot)																				\n\
						gl_Position = rotation * (vertices12[i]  + truePos1);									\n\
					else																						\n\
						gl_Position = (rotation * (vertices12[i]-fix))  + truePos1;								\n\
					gl_PrimitiveID = 2;																			\n\
					EmitVertex();																				\n\
				}																								\n\
				EndPrimitive();																					\n\
				 vec4 vertices13[4] =	vec4[4](vec4( 0, mySize/3, -mySize/3, 1.0),								\n\
													vec4( -mySize/3, mySize/3, 0, 1.0),							\n\
													vec4( -mySize/3, mySize, -2*mySize/3, 1.0),					\n\
													vec4( -2*mySize/3, mySize, -mySize/3, 1.0));				\n\
				for (int i = 0; i < 4; ++i) {																	\n\
					if(localRot)																				\n\
						gl_Position = rotation * (vertices13[i]  + truePos1);									\n\
					else																						\n\
						gl_Position = (rotation * (vertices13[i]-fix))  + truePos1;								\n\
					gl_PrimitiveID = 1;																			\n\
					EmitVertex();																				\n\
				}																								\n\
				EndPrimitive();																					\n\
				 vec4 vertices14[3] =	vec4[3](vec4( -mySize/3, mySize, -2*mySize/3, 1.0),						\n\
													vec4( 0, 2*mySize/3, -2*mySize/3, 1.0),						\n\
													vec4( 0, mySize/3, -mySize/3, 1.0));						\n\
				for (int i = 0; i < 3; ++i) {																	\n\
					if(localRot)																				\n\
						gl_Position = rotation * (vertices14[i]  + truePos1);									\n\
					else																						\n\
						gl_Position = (rotation * (vertices14[i]-fix))  + truePos1;								\n\
					gl_PrimitiveID = 1;																			\n\
					EmitVertex();																				\n\
				}																								\n\
				EndPrimitive();																					\n\
				 vec4 vertices15[3] =	vec4[3](vec4( -2*mySize/3, 2*mySize/3, 0, 1.0),							\n\
													vec4( -2*mySize/3, mySize, -mySize/3, 1.0),					\n\
													vec4( -mySize/3, mySize/3, 0, 1.0));						\n\
				for (int i = 0; i < 3; ++i) {																	\n\
					if(localRot)																				\n\
						gl_Position = rotation * (vertices15[i]  + truePos1);									\n\
					else																						\n\
						gl_Position = (rotation * (vertices15[i]-fix))  + truePos1;								\n\
					gl_PrimitiveID = 1;																			\n\
					EmitVertex();																				\n\
				}																								\n\
				EndPrimitive();																					\n\
				 vec4 vertices16[4] =	vec4[4](vec4( mySize/3, mySize/3, 0, 1.0),								\n\
													vec4( 0, mySize/3, -mySize/3, 1.0),							\n\
													vec4( 2*mySize/3, mySize, -mySize/3, 1.0),					\n\
													vec4( mySize/3, mySize, -2*mySize/3, 1.0));					\n\
				for (int i = 0; i < 4; ++i) {																	\n\
					if(localRot)																				\n\
						gl_Position = rotation * (vertices16[i]  + truePos1);									\n\
					else																						\n\
						gl_Position = (rotation * (vertices16[i]-fix))  + truePos1;								\n\
					gl_PrimitiveID = 2;																			\n\
					EmitVertex();																				\n\
				}																								\n\
				EndPrimitive();																					\n\
				 vec4 vertices17[3] =	vec4[3](vec4( 0, 2*mySize/3, -2*mySize/3, 1.0),							\n\
													vec4( mySize/3, mySize, -2*mySize/3, 1.0),					\n\
													vec4( 0, mySize/3, -mySize/3, 1.0));						\n\
				for (int i = 0; i < 3; ++i) {																	\n\
					if(localRot)																				\n\
						gl_Position = rotation * (vertices17[i]  + truePos1);									\n\
					else																						\n\
						gl_Position = (rotation * (vertices17[i]-fix))  + truePos1;								\n\
					gl_PrimitiveID = 2;																			\n\
					EmitVertex();																				\n\
				}																								\n\
				EndPrimitive();																					\n\
				 vec4 vertices18[3] =	vec4[3](vec4( 2*mySize/3, mySize, -mySize/3, 1.0),						\n\
													vec4( 2*mySize/3, 2*mySize/3, 0, 1.0),						\n\
													vec4( mySize/3, mySize/3, 0, 1.0));							\n\
				for (int i = 0; i < 3; ++i) {																	\n\
					if(localRot)																				\n\
						gl_Position = rotation * (vertices18[i]  + truePos1);									\n\
					else																						\n\
						gl_Position = (rotation * (vertices18[i]-fix))  + truePos1;								\n\
					gl_PrimitiveID = 2;																			\n\
					EmitVertex();																				\n\
				}																								\n\
				EndPrimitive();																					\n\
				 vec4 vertices19[4] =	vec4[4](vec4( mySize/3, 5*mySize/3, 0, 1.0),							\n\
													vec4( 0, 5*mySize/3, mySize/3, 1.0),						\n\
													vec4( 2*mySize/3, mySize, mySize/3, 1.0),					\n\
													vec4( mySize/3, mySize, 2*mySize/3, 1.0));					\n\
				for (int i = 0; i < 4; ++i) {																	\n\
					if(localRot)																				\n\
						gl_Position = rotation * (vertices19[i]  + truePos1);									\n\
					else																						\n\
						gl_Position = (rotation * (vertices19[i]-fix))  + truePos1;								\n\
					gl_PrimitiveID = 2;																			\n\
					EmitVertex();																				\n\
				}																								\n\
				EndPrimitive();																					\n\
				 vec4 vertices20[3] =	vec4[3](vec4( 0, 4*mySize/3, 2*mySize/3, 1.0),							\n\
													vec4( mySize/3, mySize, 2*mySize/3, 1.0),					\n\
													vec4( 0, 5*mySize/3, mySize/3, 1.0));						\n\
				for (int i = 0; i < 3; ++i) {																	\n\
					if(localRot)																				\n\
						gl_Position = rotation * (vertices20[i]  + truePos1);									\n\
					else																						\n\
						gl_Position = (rotation * (vertices20[i]-fix))  + truePos1;								\n\
					gl_PrimitiveID = 2;																			\n\
					EmitVertex();																				\n\
				}																								\n\
				EndPrimitive();																					\n\
				vec4 vertices21[3] =	vec4[3](vec4( 2*mySize/3, mySize, mySize/3, 1.0),						\n\
													vec4( 2*mySize/3, 4*mySize/3, 0, 1.0),						\n\
													vec4( mySize/3, 5*mySize/3, 0, 1.0));						\n\
				for (int i = 0; i < 3; ++i) {																	\n\
					if(localRot)																				\n\
						gl_Position = rotation * (vertices21[i]  + truePos1);									\n\
					else																						\n\
						gl_Position = (rotation * (vertices21[i]-fix))  + truePos1;								\n\
					gl_PrimitiveID = 2;																			\n\
					EmitVertex();																				\n\
				}																								\n\
				EndPrimitive();																					\n\
				 vec4 vertices22[4] =	vec4[4](vec4( 0, 5*mySize/3, mySize/3, 1.0),							\n\
													vec4( -mySize/3, 5*mySize/3, 0, 1.0),						\n\
													vec4( -mySize/3, mySize, 2*mySize/3, 1.0),					\n\
													vec4( -2*mySize/3, mySize, mySize/3, 1.0));					\n\
				for (int i = 0; i < 4; ++i) {																	\n\
					if(localRot)																				\n\
						gl_Position = rotation * (vertices22[i]  + truePos1);									\n\
					else																						\n\
						gl_Position = (rotation * (vertices22[i]-fix))  + truePos1;								\n\
					gl_PrimitiveID = 1;																			\n\
					EmitVertex();																				\n\
				}																								\n\
				EndPrimitive();																					\n\
				 vec4 vertices23[3] =	vec4[3](vec4( -mySize/3, mySize, 2*mySize/3, 1.0),						\n\
													vec4( 0, 4*mySize/3, 2*mySize/3, 1.0),						\n\
													vec4( 0, 5*mySize/3, mySize/3, 1.0));						\n\
				for (int i = 0; i < 3; ++i) {																	\n\
					if(localRot)																				\n\
						gl_Position = rotation * (vertices23[i]  + truePos1);									\n\
					else																						\n\
						gl_Position = (rotation * (vertices23[i]-fix))  + truePos1;								\n\
					gl_PrimitiveID = 1;																			\n\
					EmitVertex();																				\n\
				}																								\n\
				EndPrimitive();																					\n\
				 vec4 vertices24[3] =	vec4[3](vec4( -2*mySize/3, 4*mySize/3, 0, 1.0),							\n\
													vec4( -2*mySize/3, mySize, mySize/3, 1.0),					\n\
													vec4( -mySize/3, 5*mySize/3, 0, 1.0));						\n\
				for (int i = 0; i < 3; ++i) {																	\n\
					if(localRot)																				\n\
						gl_Position = rotation * (vertices24[i]  + truePos1);									\n\
					else																						\n\
						gl_Position = (rotation * (vertices24[i]-fix))  + truePos1;								\n\
					gl_PrimitiveID = 1;																			\n\
					EmitVertex();																				\n\
				}																								\n\
				EndPrimitive();																					\n\
				 vec4 vertices25[4] =	vec4[4](vec4( 0, 5*mySize/3, -mySize/3, 1.0),							\n\
													vec4( -mySize/3, mySize, -2*mySize/3, 1.0),					\n\
													vec4( -mySize/3, 5*mySize/3, 0, 1.0),						\n\
													vec4( -2*mySize/3, mySize, -mySize/3, 1.0));				\n\
				for (int i = 0; i < 4; ++i) {																	\n\
					if(localRot)																				\n\
						gl_Position = rotation * (vertices25[i]  + truePos1);									\n\
					else																						\n\
						gl_Position = (rotation * (vertices25[i]-fix))  + truePos1;								\n\
					gl_PrimitiveID = 2;																			\n\
					EmitVertex();																				\n\
				}																								\n\
				EndPrimitive();																					\n\
				 vec4 vertices26[3] =	vec4[3](vec4( 0, 5*mySize/3, -mySize/3, 1.0),							\n\
													vec4( 0, 4*mySize/3, -2*mySize/3, 1.0),						\n\
													vec4( -mySize/3, mySize, -2*mySize/3, 1.0));				\n\
				for (int i = 0; i < 3; ++i) {																	\n\
					if(localRot)																				\n\
						gl_Position = rotation * (vertices26[i]  + truePos1);									\n\
					else																						\n\
						gl_Position = (rotation * (vertices26[i]-fix))  + truePos1;								\n\
					gl_PrimitiveID = 2;																			\n\
					EmitVertex();																				\n\
				}																								\n\
				EndPrimitive();																					\n\
				 vec4 vertices27[3] =	vec4[3](vec4( -mySize/3, 5*mySize/3, 0, 1.0),							\n\
													vec4( -2*mySize/3, mySize, -mySize/3, 1.0),					\n\
													vec4( -2*mySize/3, 4*mySize/3, 0, 1.0));					\n\
				for (int i = 0; i < 3; ++i) {																	\n\
					if(localRot)																				\n\
						gl_Position = rotation * (vertices27[i]  + truePos1);									\n\
					else																						\n\
						gl_Position = (rotation * (vertices27[i]-fix))  + truePos1;								\n\
					gl_PrimitiveID = 2;																			\n\
					EmitVertex();																				\n\
				}																								\n\
				EndPrimitive();																					\n\
				 vec4 vertices28[4] =	vec4[4](vec4( mySize/3, 5*mySize/3, 0, 1.0),							\n\
													vec4( 2*mySize/3, mySize, -mySize/3, 1.0),					\n\
													vec4( 0, 5*mySize/3, -mySize/3, 1.0),						\n\
													vec4( mySize/3, mySize, -2*mySize/3, 1.0));					\n\
				for (int i = 0; i < 4; ++i) {																	\n\
					if(localRot)																				\n\
						gl_Position = rotation * (vertices28[i]  + truePos1);									\n\
					else																						\n\
						gl_Position = (rotation * (vertices28[i]-fix))  + truePos1;								\n\
					gl_PrimitiveID = 1;																			\n\
					EmitVertex();																				\n\
				}																								\n\
				EndPrimitive();																					\n\
				 vec4 vertices29[3] =	vec4[3](vec4( 0, 5*mySize/3, -mySize/3, 1.0),							\n\
													vec4( mySize/3, mySize, -2*mySize/3, 1.0),					\n\
													vec4( 0, 4*mySize/3, -2*mySize/3, 1.0));					\n\
				for (int i = 0; i < 3; ++i) {																	\n\
					if(localRot)																				\n\
						gl_Position = rotation * (vertices29[i]  + truePos1);									\n\
					else																						\n\
						gl_Position = (rotation * (vertices29[i]-fix))  + truePos1;								\n\
					gl_PrimitiveID = 1;																			\n\
					EmitVertex();																				\n\
				}																								\n\
				EndPrimitive();																					\n\
				 vec4 vertices30[3] =	vec4[3](vec4( mySize/3, 5*mySize/3, 0, 1.0),							\n\
													vec4( 2*mySize/3, 4*mySize/3, 0, 1.0),						\n\
													vec4( 2*mySize/3, mySize, -mySize/3, 1.0));					\n\
				for (int i = 0; i < 3; ++i) {																	\n\
					if(localRot)																				\n\
						gl_Position = rotation * (vertices30[i]  + truePos1);									\n\
					else																						\n\
						gl_Position = (rotation * (vertices30[i]-fix))  + truePos1;								\n\
					gl_PrimitiveID = 1;																			\n\
					EmitVertex();																				\n\
				}																								\n\
				EndPrimitive();																					\n\
			}																									\n\}"
		};

		static const GLchar * ofragment_shader_source[] =
		{
			"#version 330							\n\
													\n\
			uniform bool Ejercicio5;				\n\
			uniform float time;						\n\
			uniform bool samePos;						\n\
			int halfciclecolor = 1;					\n\
			out vec4 color;							\n\
													\n\
			void main() {							\n\
				if(Ejercicio5){\n\
					if (time < halfciclecolor){		\n\
					vec4 colors[4] = vec4[4](vec4(1-(time/halfciclecolor),1.0,1-(time/halfciclecolor),0),\n\				//0\n\ //cuadrados\n\
													vec4(1-(time/halfciclecolor),0.8,1-(time/halfciclecolor),0),\n\			//1\n\
													vec4(1-(time/halfciclecolor),0.9,1-(time/halfciclecolor),0),\n\			//2\n\
													vec4(1-(time/halfciclecolor),0.7,1-(time/halfciclecolor),0));\n\		//3\n\
					color=colors[gl_PrimitiveID];\n\
						} \n\
					else if (time > halfciclecolor && time < halfciclecolor*2){		\n\
						vec4 colors[4] = vec4[4](vec4(0,(1-(time-halfciclecolor)/halfciclecolor),0,0),\n\	//0\n\ //cuadrados\n\
														vec4(0,(1-(time-halfciclecolor)/halfciclecolor)*0.9,0,0),\n\	//1\n\
														vec4(0,(1-(time-halfciclecolor)/halfciclecolor)*0.8,0,0),\n\	//2\n\
														vec4(0,(1-(time-halfciclecolor)/halfciclecolor)*0.7,0,0));\n\	//3\n\
						color=colors[gl_PrimitiveID];\n\
						} \n\
				}\n\
				else if(samePos){\n\
					vec4 colors[4] = vec4[4](vec4(1.0,1.0,1.0,0.5),\n\	//0\n\ //cuadrados\n\
													vec4(0.9,0.9,0.9,0.5),\n\	//1\n\
													vec4(0.8,0.8,0.8,0.5),\n\	//2\n\
													vec4(0.7,0.7,0.7,0.5));\n\	//3\n\
					color=colors[gl_PrimitiveID];\n\
				}\n\
				else{	\n\
					vec4 colors[4] = vec4[4](vec4(1.0,0.25,0.1,0.5),\n\	//0\n\ //cuadrados\n\
													vec4(0.1,0.1,0.1,0.5),\n\	//1\n\
													vec4(0.95,1.0,0.0,0.5),\n\	//2\n\
													vec4(1.0,1.0,0.6,0.5));\n\	//3\n\
					color=colors[gl_PrimitiveID];\n\
				}\n\
			}"
		};

		GLuint overtex_shader;
		GLuint ogeom_shader;
		GLuint ofragment_shader;
		GLuint oprogram;

		overtex_shader = glCreateShader(GL_VERTEX_SHADER);
		glShaderSource(overtex_shader, 1, overtex_shader_source, NULL);
		glCompileShader(overtex_shader);

		ogeom_shader = glCreateShader(GL_GEOMETRY_SHADER);
		glShaderSource(ogeom_shader, 1, ogeom_shader_source, NULL);
		glCompileShader(ogeom_shader);

		ofragment_shader = glCreateShader(GL_FRAGMENT_SHADER);
		glShaderSource(ofragment_shader, 1, ofragment_shader_source, NULL);
		glCompileShader(ofragment_shader);

		oprogram = glCreateProgram();
		glAttachShader(oprogram, overtex_shader);
		glAttachShader(oprogram, ogeom_shader);
		glAttachShader(oprogram, ofragment_shader);
		glLinkProgram(oprogram);

		glDeleteShader(overtex_shader);
		glDeleteShader(ogeom_shader);
		glDeleteShader(ofragment_shader);

		return oprogram;
	}

	GLuint geometricMetamorfosis(void) {
		static const GLchar * mvertex_shader_source[] =
		{
			"#version 330	\n\
	void main() {	\n\
	const vec4 vertices[3] = vec4[3](	vec4( 0.25,-0.25, 0.5, 1.0),	\n\
	vec4( 0.25, 0.25, 0.5, 1.0),	\n\
	vec4(-0.25,-0.25, 0.5, 1.0));	\n\
	gl_Position = vertices[gl_VertexID];	\n\
	}"
		};

		static GLchar * mgeom_shader_source[] =
		{ "#version 330	\n\
	uniform float mySize;	\n\
	uniform vec3 pos;	\n\
	uniform float progress;	\n\
	vec4 truePos = vec4(pos.x, pos.y, pos.z, 1);	\n\
	vec4 fix = vec4(0, mySize, 0, 0);	\n\
	uniform mat4 rotation;	\n\
	uniform bool localRot;	\n\
	layout(triangles) in;	\n\
	layout(triangle_strip, max_vertices = 200) out;	\n\
	void main(){	\n\
	vec4 vertices1_1[12] =	vec4[12](	vec4( mySize/2, mySize/2, mySize/2, 1.0),	/*caraD*/	\n\
	vec4( mySize/2, mySize/2, -mySize/2, 1.0),	\n\
	vec4( mySize/2, mySize/2, mySize/2, 1.0),	\n\
	vec4( mySize/2, mySize/2, -mySize/2, 1.0),	\n\
	vec4( mySize/2, mySize/2, mySize/2, 1.0),	/*caraC*/	\n\
	vec4( mySize/2, mySize/2, -mySize/2, 1.0),	\n\
	vec4( -mySize/2, mySize/2, mySize/2, 1.0),	\n\
	vec4( -mySize/2, mySize/2, -mySize/2, 1.0),	\n\
	vec4( -mySize/2, mySize/2, mySize/2, 1.0),	/*caraI*/	\n\
	vec4( -mySize/2, mySize/2, -mySize/2, 1.0),	\n\
	vec4( -mySize/2, mySize/2, mySize/2, 1.0),	\n\
	vec4( -mySize/2, mySize/2, -mySize/2, 1.0));	\n\
	vec4 vertices1_2[12] =	vec4[12](	vec4( mySize/2, mySize/2,	0, 1.0),	/*caraD*/	\n\
	vec4( mySize/2, mySize/2,	0, 1.0),	\n\
	vec4(	0,  mySize/2, mySize/2, 1.0),	\n\
	vec4(	0, mySize/2, -mySize/2, 1.0),	\n\
	vec4(	0, mySize/2, mySize/2, 1.0),	/*caraC*/	\n\
	vec4( 	0, mySize/2, -mySize/2, 1.0),	\n\
	vec4( 	0, mySize/2, mySize/2, 1.0),	\n\
	vec4( 	0, mySize/2, -mySize/2, 1.0),	\n\
	vec4(	0, mySize/2, mySize/2, 1.0),	/*caraI*/	\n\
	vec4(	0, mySize/2, -mySize/2, 1.0),	\n\
	vec4( -mySize/2, mySize/2,	0, 1.0),	\n\
	vec4( -mySize/2, mySize/2,	0, 1.0));	\n\
	vec4 vertices1_3[12] =	vec4[12](	vec4(	0, mySize/2,	0, 1.0),	/*caraD*/	\n\
	vec4(	0, mySize/2,	0, 1.0),	\n\
	vec4(	0,  mySize/2,	0, 1.0),	\n\
	vec4(	0, mySize/2,	0, 1.0),	\n\
	vec4(	0, mySize/2,	0, 1.0),	/*caraC*/	\n\
	vec4( 	0, mySize/2,	0, 1.0),	\n\
	vec4( 	0, mySize/2,	0, 1.0),	\n\
	vec4( 	0, mySize/2,	0, 1.0),	\n\
	vec4(	0, mySize/2,	0, 1.0),	/*caraI*/	\n\
	vec4(	0, mySize/2,	0, 1.0),	\n\
	vec4(	0, mySize/2,	0, 1.0),	\n\
	vec4(	0, mySize/2,	0, 1.0));	\n\
	for(int j=0; j<3; ++j){	\n\
	for (int i = 0; i < 4; ++i) {	\n\
	vec4 localVec;	\n\
	if(progress<0.5)	\n\
	localVec=((1-progress*2)*vertices1_1[i+j*4]+progress*2*vertices1_2[i+j*4]);	\n\
	else	\n\
	localVec=((2-progress*2)*vertices1_2[i+j*4]+(progress*2-1)*vertices1_3[i+j*4]);	\n\
	if(localRot)	\n\
	gl_Position = (rotation * (localVec  + truePos));	\n\
	else	\n\
	gl_Position = (rotation * (localVec))  + truePos;	\n\
	gl_PrimitiveID = 0;	\n\
	EmitVertex();	\n\
	}	\n\
	EndPrimitive();	\n\
	}	\n\
	\n\
	\n\
	vec4 vertices2_1[12] = vec4[12](vec4(mySize / 2, -mySize / 2, mySize / 2, 1.0),	/*caraD*/	\n\
	vec4(mySize / 2, -mySize / 2, mySize / 2, 1.0),	\n\
	vec4(mySize / 2, -mySize / 2, -mySize / 2, 1.0),	\n\
	vec4(mySize / 2, -mySize / 2, -mySize / 2, 1.0),	\n\
	vec4(mySize / 2, -mySize / 2, mySize / 2, 1.0),	/*caraC*/	\n\
	vec4(-mySize / 2, -mySize / 2, mySize / 2, 1.0),	\n\
	vec4(mySize / 2, -mySize / 2, -mySize / 2, 1.0),	\n\
	vec4(-mySize / 2, -mySize / 2, -mySize / 2, 1.0),	\n\
	vec4(-mySize / 2, -mySize / 2, mySize / 2, 1.0),	/*caraI*/	\n\
	vec4(-mySize / 2, -mySize / 2, mySize / 2, 1.0),	\n\
	vec4(-mySize / 2, -mySize / 2, -mySize / 2, 1.0),	\n\
	vec4(-mySize / 2, -mySize / 2, -mySize / 2, 1.0));	\n\
	vec4 vertices2_2[12] =	vec4[12](	vec4( mySize/2, -mySize/2,	0, 1.0),	/*caraD*/	\n\
	vec4(	0, -mySize/2,  mySize/2, 1.0),	\n\
	vec4( mySize/2, -mySize/2,	0, 1.0),	\n\
	vec4(	0, -mySize/2, -mySize/2, 1.0),	\n\
	vec4(	0, -mySize/2, mySize/2, 1.0),	/*caraC*/	\n\
	vec4( 	0, -mySize/2, mySize/2, 1.0),	\n\
	vec4( 	0, -mySize/2, -mySize/2, 1.0),	\n\
	vec4( 	0, -mySize/2, -mySize/2, 1.0),	\n\
	vec4(	0, -mySize/2, mySize/2, 1.0),	/*caraI*/	\n\
	vec4( -mySize/2, -mySize/2,	0, 1.0),	\n\
	vec4(	0, -mySize/2, -mySize/2, 1.0),	\n\
	vec4( -mySize/2, -mySize/2,	0, 1.0));	\n\
	vec4 vertices2_3[12] =	vec4[12](	vec4(	0, -mySize/2,	0, 1.0),	/*caraD*/	\n\
	vec4(	0, -mySize/2,	0, 1.0),	\n\
	vec4(	0,  -mySize/2,	0, 1.0),	\n\
	vec4(	0, -mySize/2,	0, 1.0),	\n\
	vec4(	0, -mySize/2,	0, 1.0),	/*caraC*/	\n\
	vec4( 	0, -mySize/2,	0, 1.0),	\n\
	vec4( 	0, -mySize/2,	0, 1.0),	\n\
	vec4( 	0, -mySize/2,	0, 1.0),	\n\
	vec4(	0, -mySize/2,	0, 1.0),	/*caraI*/	\n\
	vec4(	0, -mySize/2,	0, 1.0),	\n\
	vec4(	0, -mySize/2,	0, 1.0),	\n\
	vec4(	0, -mySize/2,	0, 1.0));	\n\
	for (int j = 0; j<3; ++j) {	\n\
	for (int i = 0; i < 4; ++i) {	\n\
	vec4 localVec;	\n\
	if(progress<0.5)	\n\
	localVec=((1-progress*2)*vertices2_1[i+j*4]+progress*2*vertices2_2[i+j*4]);	\n\
	else	\n\
	localVec=((2-progress*2)*vertices2_2[i+j*4]+(progress*2-1)*vertices2_3[i+j*4]);	\n\
	if (localRot)	\n\
	gl_Position = (rotation * (localVec + truePos));	\n\
	else	\n\
	gl_Position = (rotation * (localVec)) + truePos;	\n\
	gl_PrimitiveID = 0;	\n\
	EmitVertex();	\n\
	}	\n\
	EndPrimitive();	\n\
	}	\n\
	\n\
	\n\
	vec4 vertices3_1[12] = vec4[12](vec4(mySize / 2, -mySize / 2, mySize / 2, 1.0),	/*caraD*/	\n\
	vec4(mySize / 2, mySize / 2, mySize / 2, 1.0),	\n\
	vec4(mySize / 2, -mySize / 2, mySize / 2, 1.0),	\n\
	vec4(mySize / 2, mySize / 2, mySize / 2, 1.0),	\n\
	vec4(mySize / 2, -mySize / 2, mySize / 2, 1.0),	/*caraC*/	\n\
	vec4(mySize / 2, mySize / 2, mySize / 2, 1.0),	\n\
	vec4(-mySize / 2, -mySize / 2, mySize / 2, 1.0),	\n\
	vec4(-mySize / 2, mySize / 2, mySize / 2, 1.0),	\n\
	vec4(-mySize / 2, -mySize / 2, mySize / 2, 1.0),	/*caraI*/	\n\
	vec4(-mySize / 2, mySize / 2, mySize / 2, 1.0),	\n\
	vec4(-mySize / 2, -mySize / 2, mySize / 2, 1.0),	\n\
	vec4(-mySize / 2, mySize / 2, mySize / 2, 1.0));	\n\
	vec4 vertices3_2[12] =	vec4[12](	vec4( mySize/2,	0, mySize/2, 1.0),	/*caraD*/	\n\
	vec4( mySize/2,	0, mySize/2, 1.0),	\n\
	vec4(	0, -mySize/2, mySize/2, 1.0),	\n\
	vec4(	0, mySize/2, mySize/2, 1.0),	\n\
	vec4(	0, -mySize/2, mySize/2, 1.0),	/*caraC*/	\n\
	vec4( 	0, mySize/2, mySize/2, 1.0),	\n\
	vec4( 	0, -mySize/2, mySize/2, 1.0),	\n\
	vec4( 	0, mySize/2, mySize/2, 1.0),	\n\
	vec4(	0, -mySize/2, mySize/2, 1.0),	/*caraI*/	\n\
	vec4(	0, mySize/2, mySize/2, 1.0),	\n\
	vec4( -mySize/2,	0, mySize/2, 1.0),	\n\
	vec4( -mySize/2,	0,	 mySize/2, 1.0));	\n\
	vec4 vertices3_3[12] =	vec4[12](	vec4(	0,	0, mySize/2, 1.0),	/*caraD*/	\n\
	vec4(	0,	0, mySize/2, 1.0),	\n\
	vec4(	0,	0, mySize/2, 1.0),	\n\
	vec4(	0,	0, mySize/2, 1.0),	\n\
	vec4(	0,	0, mySize/2, 1.0),	/*caraC*/	\n\
	vec4( 	0,	0, mySize/2, 1.0),	\n\
	vec4( 	0,	0, mySize/2, 1.0),	\n\
	vec4( 	0,	0, mySize/2, 1.0),	\n\
	vec4(	0,	0, mySize/2, 1.0),	/*caraI*/	\n\
	vec4(	0,	0, mySize/2, 1.0),	\n\
	vec4(	0,	0, mySize/2, 1.0),	\n\
	vec4(	0,	0, mySize/2, 1.0));	\n\
	for (int j = 0; j<3; ++j) {	\n\
	for (int i = 0; i < 4; ++i) {	\n\
	vec4 localVec;	\n\
	if(progress<0.5)	\n\
	localVec=((1-progress*2)*vertices3_1[i+j*4]+progress*2*vertices3_2[i+j*4]);	\n\
	else	\n\
	localVec=((2-progress*2)*vertices3_2[i+j*4]+(progress*2-1)*vertices3_3[i+j*4]);	\n\
	if (localRot)	\n\
	gl_Position = (rotation * (localVec + truePos));	\n\
	else	\n\
	gl_Position = (rotation * (localVec)) + truePos;	\n\
	gl_PrimitiveID = 1;	\n\
	EmitVertex();	\n\
	}	\n\
	EndPrimitive();	\n\
	}	\n\
	\n\
	vec4 vertices4_1[12] = vec4[12](vec4(mySize / 2, -mySize / 2, -mySize / 2, 1.0),	/*caraD*/	\n\
	vec4(mySize / 2, -mySize / 2, -mySize / 2, 1.0),	\n\
	vec4(mySize / 2, mySize / 2, -mySize / 2, 1.0),	\n\
	vec4(mySize / 2, mySize / 2, -mySize / 2, 1.0),	\n\
	vec4(mySize / 2, -mySize / 2, -mySize / 2, 1.0),	/*caraC*/	\n\
	vec4(-mySize / 2, -mySize / 2, -mySize / 2, 1.0),	\n\
	vec4(mySize / 2, mySize / 2, -mySize / 2, 1.0),	\n\
	vec4(-mySize / 2, mySize / 2, -mySize / 2, 1.0),	\n\
	vec4(-mySize / 2, -mySize / 2, -mySize / 2, 1.0),	/*caraI*/	\n\
	vec4(-mySize / 2, -mySize / 2, -mySize / 2, 1.0),	\n\
	vec4(-mySize / 2, mySize / 2, -mySize / 2, 1.0),	\n\
	vec4(-mySize / 2, mySize / 2, -mySize / 2, 1.0));	\n\
	vec4 vertices4_2[12] =	vec4[12](	vec4( mySize/2,	0, -mySize/2, 1.0),	/*caraD*/	\n\
	vec4(	0,	-mySize/2, -mySize/2, 1.0),	\n\
	vec4( mySize/2,	0, -mySize/2, 1.0),	\n\
	vec4(	0, mySize/2, -mySize/2, 1.0),	\n\
	vec4(	0, -mySize/2, -mySize/2, 1.0),	/*caraC*/	\n\
	vec4( 	0, -mySize/2, -mySize/2, 1.0),	\n\
	vec4( 	0, mySize/2, -mySize/2, 1.0),	\n\
	vec4( 	0, mySize/2, -mySize/2, 1.0),	\n\
	vec4(	0, -mySize/2, -mySize/2, 1.0),	/*caraI*/	\n\
	vec4( -mySize/2,	0, -mySize/2, 1.0),	\n\
	vec4(	0,	mySize/2, -mySize/2, 1.0),	\n\
	vec4( -mySize/2,	0,	 -mySize/2, 1.0));	\n\
	vec4 vertices4_3[12] =	vec4[12](	vec4(	0,	0, -mySize/2, 1.0),	/*caraD*/	\n\
	vec4(	0,	0, -mySize/2, 1.0),	\n\
	vec4(	0,	0, -mySize/2, 1.0),	\n\
	vec4(	0,	0, -mySize/2, 1.0),	\n\
	vec4(	0,	0, -mySize/2, 1.0),	/*caraC*/	\n\
	vec4( 	0,	0, -mySize/2, 1.0),	\n\
	vec4( 	0,	0, -mySize/2, 1.0),	\n\
	vec4( 	0,	0, -mySize/2, 1.0),	\n\
	vec4(	0,	0, -mySize/2, 1.0),	/*caraI*/	\n\
	vec4(	0,	0, -mySize/2, 1.0),	\n\
	vec4(	0,	0, -mySize/2, 1.0),	\n\
	vec4(	0,	0, -mySize/2, 1.0));	\n\
	for (int j = 0; j<3; ++j) {	\n\
	for (int i = 0; i < 4; ++i) {	\n\
	vec4 localVec;	\n\
	if(progress<0.5)	\n\
	localVec=((1-progress*2)*vertices4_1[i+j*4]+progress*2*vertices4_2[i+j*4]);	\n\
	else	\n\
	localVec=((2-progress*2)*vertices4_2[i+j*4]+(progress*2-1)*vertices4_3[i+j*4]);	\n\
	if (localRot)	\n\
	gl_Position = (rotation * (localVec + truePos));	\n\
	else	\n\
	gl_Position = (rotation * (localVec)) + truePos;	\n\
	gl_PrimitiveID = 1;	\n\
	EmitVertex();	\n\
	}	\n\
	EndPrimitive();	\n\
	}"
			"vec4 vertices5_1[12] = vec4[12](vec4(-mySize / 2, -mySize / 2, mySize / 2, 1.0),	/*caraD*/	\n\
	vec4(-mySize / 2, mySize / 2, mySize / 2, 1.0),	\n\
	vec4(-mySize / 2, -mySize / 2, mySize / 2, 1.0),	\n\
	vec4(-mySize / 2, mySize / 2, mySize / 2, 1.0),	\n\
	vec4(-mySize / 2, -mySize / 2, mySize / 2, 1.0),	/*caraC*/	\n\
	vec4(-mySize / 2, mySize / 2, mySize / 2, 1.0),	\n\
	vec4(-mySize / 2, -mySize / 2, -mySize / 2, 1.0),	\n\
	vec4(-mySize / 2, mySize / 2, -mySize / 2, 1.0),	\n\
	vec4(-mySize / 2, -mySize / 2, -mySize / 2, 1.0),	/*caraI*/	\n\
	vec4(-mySize / 2, mySize / 2, -mySize / 2, 1.0),	\n\
	vec4(-mySize / 2, -mySize / 2, -mySize / 2, 1.0),	\n\
	vec4(-mySize / 2, mySize / 2, -mySize / 2, 1.0));	\n\
	vec4 vertices5_2[12] =	vec4[12](	vec4( -mySize / 2,	0, mySize/2, 1.0),	/*caraD*/	\n\
	vec4( -mySize / 2,	0, mySize/2, 1.0),	\n\
	vec4( -mySize / 2, -mySize/2,	0, 1.0),	\n\
	vec4( -mySize / 2, mySize/2,	0, 1.0),	\n\
	vec4( -mySize / 2, -mySize/2,	0, 1.0),	/*caraC*/	\n\
	vec4( -mySize / 2, mySize/2,	0, 1.0),	\n\
	vec4( -mySize / 2, -mySize/2,	0, 1.0),	\n\
	vec4( -mySize / 2, mySize/2,	0, 1.0),	\n\
	vec4( -mySize / 2, -mySize/2,	0, 1.0),	/*caraI*/	\n\
	vec4( -mySize / 2,	mySize/2,	0, 1.0),	\n\
	vec4( -mySize / 2,	0, -mySize/2, 1.0),	\n\
	vec4( -mySize / 2,	0, -mySize/2, 1.0));	\n\
	vec4 vertices5_3[12] =	vec4[12](	vec4( -mySize / 2,	0,  	0, 1.0),	/*caraD*/	\n\
	vec4( -mySize / 2,	0, 	0, 1.0),	\n\
	vec4( -mySize / 2,	0, 	0, 1.0),	\n\
	vec4( -mySize / 2,	0, 	0, 1.0),	\n\
	vec4( -mySize / 2,	0, 	0, 1.0),	/*caraC*/	\n\
	vec4( -mySize / 2,	0, 	0, 1.0),	\n\
	vec4( -mySize / 2,	0, 	0, 1.0),	\n\
	vec4( -mySize / 2,	0, 	0, 1.0),	\n\
	vec4( -mySize / 2,	0, 	0, 1.0),	/*caraI*/	\n\
	vec4( -mySize / 2,	0, 	0, 1.0),	\n\
	vec4( -mySize / 2,	0, 	0, 1.0),	\n\
	vec4( -mySize / 2,	0, 	0, 1.0));	\n\
	for (int j = 0; j<3; ++j) {	\n\
	for (int i = 0; i < 4; ++i) {	\n\
	vec4 localVec;	\n\
	if(progress<0.5)	\n\
	localVec=((1-progress*2)*vertices5_1[i+j*4]+progress*2*vertices5_2[i+j*4]);	\n\
	else	\n\
	localVec=((2-progress*2)*vertices5_2[i+j*4]+(progress*2-1)*vertices5_3[i+j*4]);	\n\
	if (localRot)	\n\
	gl_Position = (rotation * (localVec + truePos));	\n\
	else	\n\
	gl_Position = (rotation * (localVec)) + truePos;	\n\
	gl_PrimitiveID = 2;	\n\
	EmitVertex();	\n\
	}	\n\
	EndPrimitive();	\n\
	}	\n\
	\n\
	vec4 vertices6_1[12] = vec4[12](vec4(mySize / 2, -mySize / 2, -mySize / 2, 1.0),	/*caraD*/	\n\
	vec4(mySize / 2, mySize / 2, -mySize / 2, 1.0),	\n\
	vec4(mySize / 2, -mySize / 2, -mySize / 2, 1.0),	\n\
	vec4(mySize / 2, mySize / 2, -mySize / 2, 1.0),	\n\
	vec4(mySize / 2, -mySize / 2, -mySize / 2, 1.0),	/*caraC*/	\n\
	vec4(mySize / 2, mySize / 2, -mySize / 2, 1.0),	\n\
	vec4(mySize / 2, -mySize / 2, mySize / 2, 1.0),	\n\
	vec4(mySize / 2, mySize / 2, mySize / 2, 1.0),	\n\
	vec4(mySize / 2, -mySize / 2, mySize / 2, 1.0),	/*caraI*/	\n\
	vec4(mySize / 2, mySize / 2, mySize / 2, 1.0),	\n\
	vec4(mySize / 2, -mySize / 2, mySize / 2, 1.0),	\n\
	vec4(mySize / 2, mySize / 2, mySize / 2, 1.0));	\n\
	vec4 vertices6_2[12] =	vec4[12](	vec4( mySize / 2,	0, -mySize/2, 1.0),	/*caraD*/	\n\
	vec4( mySize / 2,	0, -mySize/2, 1.0),	\n\
	vec4( mySize / 2, -mySize/2,	0, 1.0),	\n\
	vec4( mySize / 2, mySize/2,	0, 1.0),	\n\
	vec4( mySize / 2, -mySize/2,	0, 1.0),	/*caraC*/	\n\
	vec4( mySize / 2, mySize/2,	0, 1.0),	\n\
	vec4( mySize / 2, -mySize/2,	0, 1.0),	\n\
	vec4( mySize / 2, mySize/2,	0, 1.0),	\n\
	vec4( mySize / 2, -mySize/2,	0, 1.0),	/*caraI*/	\n\
	vec4( mySize / 2,	mySize/2,	0, 1.0),	\n\
	vec4( mySize / 2,	0, mySize/2, 1.0),	\n\
	vec4( mySize / 2,	0, mySize/2, 1.0));	\n\
	vec4 vertices6_3[12] =	vec4[12](	vec4( mySize / 2,	0,  	0, 1.0),	/*caraD*/	\n\
	vec4( mySize / 2,	0, 	0, 1.0),	\n\
	vec4( mySize / 2,	0, 	0, 1.0),	\n\
	vec4( mySize / 2,	0, 	0, 1.0),	\n\
	vec4( mySize / 2,	0, 	0, 1.0),	/*caraC*/	\n\
	vec4( mySize / 2,	0, 	0, 1.0),	\n\
	vec4( mySize / 2,	0, 	0, 1.0),	\n\
	vec4( mySize / 2,	0, 	0, 1.0),	\n\
	vec4( mySize / 2,	0, 	0, 1.0),	/*caraI*/	\n\
	vec4( mySize / 2,	0, 	0, 1.0),	\n\
	vec4( mySize / 2,	0, 	0, 1.0),	\n\
	vec4( mySize / 2,	0, 	0, 1.0));	\n\
	for (int j = 0; j<3; ++j) {	\n\
	for (int i = 0; i < 4; ++i) {	\n\
	vec4 localVec;	\n\
	if(progress<0.5)	\n\
	localVec=((1-progress*2)*vertices6_1[i+j*4]+progress*2*vertices6_2[i+j*4]);	\n\
	else	\n\
	localVec=((2-progress*2)*vertices6_2[i+j*4]+(progress*2-1)*vertices6_3[i+j*4]);	\n\
	if (localRot)	\n\
	gl_Position = (rotation * (localVec + truePos));	\n\
	else	\n\
	gl_Position = (rotation * (localVec)) + truePos;	\n\
	gl_PrimitiveID = 2;	\n\
	EmitVertex();	\n\
	}	\n\
	EndPrimitive();	\n\
	}	\n\
	\n\
	vec4 vertices7_1[10] = vec4[10](vec4(mySize / 2, mySize / 2, mySize / 2, 1.0),	/*caraD*/	\n\
	vec4(mySize / 2, mySize / 2, mySize / 2, 1.0),	\n\
	vec4(mySize / 2, mySize / 2,mySize / 2, 1.0),	\n\
	vec4(mySize / 2, mySize / 2, mySize / 2, 1.0),	/*caraC*/	\n\
	vec4(mySize / 2, mySize / 2, mySize / 2, 1.0),	\n\
	vec4(mySize / 2, mySize / 2, mySize / 2, 1.0),	\n\
	vec4(mySize / 2, mySize / 2, mySize / 2, 1.0),	\n\
	vec4(mySize / 2, mySize / 2, mySize / 2, 1.0),	/*caraI*/	\n\
	vec4(mySize / 2, mySize / 2, mySize / 2, 1.0),	\n\
	vec4(mySize / 2, mySize / 2, mySize / 2, 1.0));	\n\
	vec4 vertices7_2[10] = vec4[10](vec4(mySize / 2,	0, mySize / 2, 1.0),	/*caraD*/	\n\
	vec4(mySize / 2, mySize / 2,	0, 1.0),	\n\
	vec4(mySize / 2, mySize / 2,	0, 1.0),	\n\
	vec4(mySize / 2,	0, mySize / 2, 1.0),	/*caraC*/	\n\
	vec4(mySize / 2, mySize / 2,	0, 1.0),	\n\
	vec4(mySize / 2,	0, mySize / 2, 1.0),	\n\
	vec4(	  0, mySize / 2, mySize / 2, 1.0),	\n\
	vec4(mySize / 2,	0, mySize / 2, 1.0),	/*caraI*/	\n\
	vec4(	0, mySize / 2, mySize/2, 1.0),	\n\
	vec4(	0, mySize / 2, mySize/2, 1.0));	\n\
	vec4 vertices7_3[10] = vec4[10](vec4(mySize / 2,	  0,	  0, 1.0),	/*caraD*/	\n\
	vec4(mySize / 2, 	  0,	  0, 1.0),	\n\
	vec4(	  0, mySize / 2,	  0, 1.0),	\n\
	vec4(mySize / 2,	  0,	  0, 1.0),	/*caraC*/	\n\
	vec4(	  0, mySize / 2,  	  0, 1.0),	\n\
	vec4(	  0,	  0,   mySize/2, 1.0),	\n\
	vec4(	  0, mySize / 2,  	  0, 1.0),	\n\
	vec4(	0,	  0, mySize/2, 1.0),	/*caraI*/	\n\
	vec4(	0, mySize/2,	  0, 1.0),	\n\
	vec4(	0,	  0, mySize/2, 1.0));	\n\
	for (int i = 0; i < 3; ++i) {	\n\
	vec4 localVec;	\n\
	if(progress<0.5)	\n\
	localVec=((1-progress*2)*vertices7_1[i]+progress*2*vertices7_2[i]);	\n\
	else	\n\
	localVec=((2-progress*2)*vertices7_2[i]+(progress*2-1)*vertices7_3[i]);	\n\
	if (localRot)	\n\
	gl_Position = (rotation * (localVec + truePos));	\n\
	else	\n\
	gl_Position = (rotation * (localVec)) + truePos;	\n\
	gl_PrimitiveID = 3;	\n\
	EmitVertex();	\n\
	}	\n\
	EndPrimitive();	\n\
	for (int i = 0; i < 4; ++i) {	\n\
	vec4 localVec;	\n\
	if(progress<0.5)	\n\
	localVec=((1-progress*2)*vertices7_1[i+3]+progress*2*vertices7_2[i+3]);	\n\
	else	\n\
	localVec=((2-progress*2)*vertices7_2[i+3]+(progress*2-1)*vertices7_3[i+3]);	\n\
	if (localRot)	\n\
	gl_Position = (rotation * (localVec + truePos));	\n\
	else	\n\
	gl_Position = (rotation * (localVec)) + truePos;	\n\
	gl_PrimitiveID = 3;	\n\
	EmitVertex();	\n\
	}	\n\
	EndPrimitive();	\n\
	for (int i = 0; i < 3; ++i) {	\n\
	vec4 localVec;	\n\
	if(progress<0.5)	\n\
	localVec=((1-progress*2)*vertices7_1[i+7]+progress*2*vertices7_2[i+7]);	\n\
	else	\n\
	localVec=((2-progress*2)*vertices7_2[i+7]+(progress*2-1)*vertices7_3[i+7]);	\n\
	if (localRot)	\n\
	gl_Position = (rotation * (localVec + truePos));	\n\
	else	\n\
	gl_Position = (rotation * (localVec)) + truePos;	\n\
	gl_PrimitiveID = 3;	\n\
	EmitVertex();	\n\
	}	\n\
	EndPrimitive();	\n\
	\n\
	\n\
	vec4 vertices8_1[10] = vec4[10](vec4(-mySize / 2, mySize / 2, mySize / 2, 1.0),	/*caraD*/	\n\
	vec4(-mySize / 2, mySize / 2, mySize / 2, 1.0),	\n\
	vec4(-mySize / 2, mySize / 2,mySize / 2, 1.0),	\n\
	vec4(-mySize / 2, mySize / 2, mySize / 2, 1.0),	/*caraC*/	\n\
	vec4(-mySize / 2, mySize / 2, mySize / 2, 1.0),	\n\
	vec4(-mySize / 2, mySize / 2, mySize / 2, 1.0),	\n\
	vec4(-mySize / 2, mySize / 2, mySize / 2, 1.0),	\n\
	vec4(-mySize / 2, mySize / 2, mySize / 2, 1.0),	/*caraI*/	\n\
	vec4(-mySize / 2, mySize / 2, mySize / 2, 1.0),	\n\
	vec4(-mySize / 2, mySize / 2, mySize / 2, 1.0));	\n\
	vec4 vertices8_2[10] = vec4[10](vec4(-mySize / 2,	0, mySize / 2, 1.0),	/*caraD*/	\n\
	vec4(-mySize / 2, mySize / 2,	0, 1.0),	\n\
	vec4(-mySize / 2, mySize / 2,	0, 1.0),	\n\
	vec4(-mySize / 2, mySize / 2,	0, 1.0),	/*caraC*/	\n\
	vec4(-mySize / 2,	0, mySize / 2, 1.0),	\n\
	vec4(	  0, mySize / 2, mySize / 2, 1.0),	\n\
	vec4(-mySize / 2,	0, mySize / 2, 1.0),	\n\
	vec4(-mySize / 2,	0, mySize / 2, 1.0),	/*caraI*/	\n\
	vec4(	0, mySize / 2, mySize/2, 1.0),	\n\
	vec4(	0, mySize / 2, mySize/2, 1.0));	\n\
	vec4 vertices8_3[10] = vec4[10](vec4(-mySize / 2,	  0,	  0, 1.0),	/*caraD*/	\n\
	vec4(	  0, mySize / 2,	  0, 1.0),	\n\
	vec4(-mySize / 2, 	  0,	  0, 1.0),	\n\
	vec4(	  0, mySize / 2,  	  0, 1.0),	/*caraC*/	\n\
	vec4(-mySize / 2,	  0,	  0, 1.0),	\n\
	vec4(	  0, mySize / 2,  	  0, 1.0),	\n\
	vec4(	  0,	  0,   mySize/2, 1.0),	\n\
	vec4(	0,	  0, mySize/2, 1.0),	/*caraI*/	\n\
	vec4(	0,	  0, mySize/2, 1.0),	\n\
	vec4(	0, mySize/2,	  0, 1.0));	\n\
	for (int i = 0; i < 3; ++i) {	\n\
	vec4 localVec;	\n\
	if(progress<0.5)	\n\
	localVec=((1-progress*2)*vertices8_1[i]+progress*2*vertices8_2[i]);	\n\
	else	\n\
	localVec=((2-progress*2)*vertices8_2[i]+(progress*2-1)*vertices8_3[i]);	\n\
	if (localRot)	\n\
	gl_Position = (rotation * (localVec + truePos));	\n\
	else	\n\
	gl_Position = (rotation * (localVec)) + truePos;	\n\
	gl_PrimitiveID = 4;	\n\
	EmitVertex();	\n\
	}	\n\
	EndPrimitive();	\n\
	for (int i = 0; i < 4; ++i) {	\n\
	vec4 localVec;	\n\
	if(progress<0.5)	\n\
	localVec=((1-progress*2)*vertices8_1[i+3]+progress*2*vertices8_2[i+3]);	\n\
	else	\n\
	localVec=((2-progress*2)*vertices8_2[i+3]+(progress*2-1)*vertices8_3[i+3]);	\n\
	if (localRot)	\n\
	gl_Position = (rotation * (localVec + truePos));	\n\
	else	\n\
	gl_Position = (rotation * (localVec)) + truePos;	\n\
	gl_PrimitiveID = 4;	\n\
	EmitVertex();	\n\
	}	\n\
	EndPrimitive();	\n\
	for (int i = 0; i < 3; ++i) {	\n\
	vec4 localVec;	\n\
	if(progress<0.5)	\n\
	localVec=((1-progress*2)*vertices8_1[i+7]+progress*2*vertices8_2[i+7]);	\n\
	else	\n\
	localVec=((2-progress*2)*vertices8_2[i+7]+(progress*2-1)*vertices8_3[i+7]);	\n\
	if (localRot)	\n\
	gl_Position = (rotation * (localVec + truePos));	\n\
	else	\n\
	gl_Position = (rotation * (localVec)) + truePos;	\n\
	gl_PrimitiveID = 4;	\n\
	EmitVertex();	\n\
	}	\n\
	EndPrimitive();	"
			"	\n\
	\n\
	vec4 vertices9_1[10] = vec4[10](vec4(mySize / 2, mySize / 2, -mySize / 2, 1.0),	/*caraD*/	\n\
	vec4(mySize / 2, mySize / 2, -mySize / 2, 1.0),	\n\
	vec4(mySize / 2, mySize / 2,-mySize / 2, 1.0),	\n\
	vec4(mySize / 2, mySize / 2, -mySize / 2, 1.0),	/*caraC*/	\n\
	vec4(mySize / 2, mySize / 2, -mySize / 2, 1.0),	\n\
	vec4(mySize / 2, mySize / 2, -mySize / 2, 1.0),	\n\
	vec4(mySize / 2, mySize / 2, -mySize / 2, 1.0),	\n\
	vec4(mySize / 2, mySize / 2, -mySize / 2, 1.0),	/*caraI*/	\n\
	vec4(mySize / 2, mySize / 2, -mySize / 2, 1.0),	\n\
	vec4(mySize / 2, mySize / 2, -mySize / 2, 1.0));	\n\
	vec4 vertices9_2[10] = vec4[10](vec4(mySize / 2,	0, -mySize / 2, 1.0),	/*caraD*/	\n\
	vec4(mySize / 2, mySize / 2,	0, 1.0),	\n\
	vec4(mySize / 2, mySize / 2,	0, 1.0),	\n\
	vec4(mySize / 2, mySize / 2,	0, 1.0),	/*caraC*/	\n\
	vec4(mySize / 2,	0, -mySize / 2, 1.0),	\n\
	vec4(	  0, mySize / 2, -mySize / 2, 1.0),	\n\
	vec4(mySize / 2,	0, -mySize / 2, 1.0),	\n\
	vec4(mySize / 2,	0, -mySize / 2, 1.0),	/*caraI*/	\n\
	vec4(	0, mySize / 2, -mySize/2, 1.0),	\n\
	vec4(	0, mySize / 2, -mySize/2, 1.0));	\n\
	vec4 vertices9_3[10] = vec4[10](vec4(mySize / 2,	  0,	  0, 1.0),	/*caraD*/	\n\
	vec4(	  0, mySize / 2,	  0, 1.0),	\n\
	vec4(mySize / 2,	  0,	  0, 1.0),	\n\
	vec4(	  0, mySize / 2,  	  0, 1.0),	/*caraC*/	\n\
	vec4(mySize / 2,	  0,	  0, 1.0),	\n\
	vec4(	  0, mySize / 2,  	  0, 1.0),	\n\
	vec4(	  0,	  0,   -mySize/2, 1.0),	\n\
	vec4(	0,	  0, -mySize/2, 1.0),	/*caraI*/	\n\
	vec4(	0,	  0, -mySize/2, 1.0),	\n\
	vec4(	0, mySize/2,	  0, 1.0));	\n\
	for (int i = 0; i < 3; ++i) {	\n\
	vec4 localVec;	\n\
	if(progress<0.5)	\n\
	localVec=((1-progress*2)*vertices9_1[i]+progress*2*vertices9_2[i]);	\n\
	else	\n\
	localVec=((2-progress*2)*vertices9_2[i]+(progress*2-1)*vertices9_3[i]);	\n\
	if (localRot)	\n\
	gl_Position = (rotation * (localVec + truePos));	\n\
	else	\n\
	gl_Position = (rotation * (localVec)) + truePos;	\n\
	gl_PrimitiveID = 4;	\n\
	EmitVertex();	\n\
	}	\n\
	EndPrimitive();	\n\
	for (int i = 0; i < 4; ++i) {	\n\
	vec4 localVec;	\n\
	if(progress<0.5)	\n\
	localVec=((1-progress*2)*vertices9_1[i+3]+progress*2*vertices9_2[i+3]);	\n\
	else	\n\
	localVec=((2-progress*2)*vertices9_2[i+3]+(progress*2-1)*vertices9_3[i+3]);	\n\
	if (localRot)	\n\
	gl_Position = (rotation * (localVec + truePos));	\n\
	else	\n\
	gl_Position = (rotation * (localVec)) + truePos;	\n\
	gl_PrimitiveID = 4;	\n\
	EmitVertex();	\n\
	}	\n\
	EndPrimitive();	\n\
	for (int i = 0; i < 3; ++i) {	\n\
	vec4 localVec;	\n\
	if(progress<0.5)	\n\
	localVec=((1-progress*2)*vertices9_1[i+7]+progress*2*vertices9_2[i+7]);	\n\
	else	\n\
	localVec=((2-progress*2)*vertices9_2[i+7]+(progress*2-1)*vertices9_3[i+7]);	\n\
	if (localRot)	\n\
	gl_Position = (rotation * (localVec + truePos));	\n\
	else	\n\
	gl_Position = (rotation * (localVec)) + truePos;	\n\
	gl_PrimitiveID = 4;	\n\
	EmitVertex();	\n\
	}	\n\
	EndPrimitive();	\n\
	\n\
	vec4 vertices10_1[10] = vec4[10](vec4(-mySize / 2, mySize / 2, -mySize / 2, 1.0),	/*caraD*/	\n\
	vec4(-mySize / 2, mySize / 2, -mySize / 2, 1.0),	\n\
	vec4(-mySize / 2, mySize / 2,-mySize / 2, 1.0),	\n\
	vec4(-mySize / 2, mySize / 2, -mySize / 2, 1.0),	/*caraC*/	\n\
	vec4(-mySize / 2, mySize / 2, -mySize / 2, 1.0),	\n\
	vec4(-mySize / 2, mySize / 2, -mySize / 2, 1.0),	\n\
	vec4(-mySize / 2, mySize / 2, -mySize / 2, 1.0),	\n\
	vec4(-mySize / 2, mySize / 2, -mySize / 2, 1.0),	/*caraI*/	\n\
	vec4(-mySize / 2, mySize / 2, -mySize / 2, 1.0),	\n\
	vec4(-mySize / 2, mySize / 2, -mySize / 2, 1.0));	\n\
	vec4 vertices10_2[10] = vec4[10](vec4(-mySize / 2,	0, -mySize / 2, 1.0),	/*caraD*/	\n\
	vec4(-mySize / 2, mySize / 2,	0, 1.0),	\n\
	vec4(-mySize / 2, mySize / 2,	0, 1.0),	\n\
	vec4(-mySize / 2,	0, -mySize / 2, 1.0),	/*caraC*/	\n\
	vec4(-mySize / 2, mySize / 2,	0, 1.0),	\n\
	vec4(-mySize / 2,	0, -mySize / 2, 1.0),	\n\
	vec4(	  0, mySize / 2, -mySize / 2, 1.0),	\n\
	vec4(-mySize / 2,	0, -mySize / 2, 1.0),	/*caraI*/	\n\
	vec4(	0, mySize / 2, -mySize/2, 1.0),	\n\
	vec4(	0, mySize / 2, -mySize/2, 1.0));	\n\
	vec4 vertices10_3[10] = vec4[10](vec4(-mySize / 2,	  0,	  0, 1.0),	/*caraD*/	\n\
	vec4(-mySize / 2, 	  0,	  0, 1.0),	\n\
	vec4(	  0, mySize / 2,	  0, 1.0),	\n\
	vec4(-mySize / 2,	  0,	  0, 1.0),	/*caraC*/	\n\
	vec4(	  0, mySize / 2,  	  0, 1.0),	\n\
	vec4(	  0,	  0,   -mySize/2, 1.0),	\n\
	vec4(	  0, mySize / 2,  	  0, 1.0),	\n\
	vec4(	0,	  0, -mySize/2, 1.0),	/*caraI*/	\n\
	vec4(	0, mySize/2,	  0, 1.0),	\n\
	vec4(	0,	  0, -mySize/2, 1.0));	\n\
	for (int i = 0; i < 3; ++i) {	\n\
	vec4 localVec;	\n\
	if(progress<0.5)	\n\
	localVec=((1-progress*2)*vertices10_1[i]+progress*2*vertices10_2[i]);	\n\
	else	\n\
	localVec=((2-progress*2)*vertices10_2[i]+(progress*2-1)*vertices10_3[i]);	\n\
	if (localRot)	\n\
	gl_Position = (rotation * (localVec + truePos));	\n\
	else	\n\
	gl_Position = (rotation * (localVec)) + truePos;	\n\
	gl_PrimitiveID = 3;	\n\
	EmitVertex();	\n\
	}	\n\
	EndPrimitive();	\n\
	for (int i = 0; i < 4; ++i) {	\n\
	vec4 localVec;	\n\
	if(progress<0.5)	\n\
	localVec=((1-progress*2)*vertices10_1[i+3]+progress*2*vertices10_2[i+3]);	\n\
	else	\n\
	localVec=((2-progress*2)*vertices10_2[i+3]+(progress*2-1)*vertices10_3[i+3]);	\n\
	if (localRot)	\n\
	gl_Position = (rotation * (localVec + truePos));	\n\
	else	\n\
	gl_Position = (rotation * (localVec)) + truePos;	\n\
	gl_PrimitiveID = 3;	\n\
	EmitVertex();	\n\
	}	\n\
	EndPrimitive();	\n\
	for (int i = 0; i < 3; ++i) {	\n\
	vec4 localVec;	\n\
	if(progress<0.5)	\n\
	localVec=((1-progress*2)*vertices10_1[i+7]+progress*2*vertices10_2[i+7]);	\n\
	else	\n\
	localVec=((2-progress*2)*vertices10_2[i+7]+(progress*2-1)*vertices10_3[i+7]);	\n\
	if (localRot)	\n\
	gl_Position = (rotation * (localVec + truePos));	\n\
	else	\n\
	gl_Position = (rotation * (localVec)) + truePos;	\n\
	gl_PrimitiveID = 3;	\n\
	EmitVertex();	\n\
	}	\n\
	EndPrimitive();	\n\
	\n\
	vec4 vertices11_1[10] = vec4[10](vec4(mySize / 2, -mySize / 2, mySize / 2, 1.0),	/*caraD*/	\n\
	vec4(mySize / 2, -mySize / 2, mySize / 2, 1.0),	\n\
	vec4(mySize / 2, -mySize / 2,mySize / 2, 1.0),	\n\
	vec4(mySize / 2, -mySize / 2, mySize / 2, 1.0),	/*caraC*/	\n\
	vec4(mySize / 2, -mySize / 2, mySize / 2, 1.0),	\n\
	vec4(mySize / 2, -mySize / 2, mySize / 2, 1.0),	\n\
	vec4(mySize / 2, -mySize / 2, mySize / 2, 1.0),	\n\
	vec4(mySize / 2, -mySize / 2, mySize / 2, 1.0),	/*caraI*/	\n\
	vec4(mySize / 2, -mySize / 2, mySize / 2, 1.0),	\n\
	vec4(mySize / 2, -mySize / 2, mySize / 2, 1.0));	\n\
	vec4 vertices11_2[10] = vec4[10](vec4(mySize / 2,	0, mySize / 2, 1.0),	/*caraD*/	\n\
	vec4(mySize / 2, -mySize / 2,	0, 1.0),	\n\
	vec4(mySize / 2, -mySize / 2,	0, 1.0),	\n\
	vec4(mySize / 2, -mySize / 2,	0, 1.0),	/*caraC*/	\n\
	vec4(mySize / 2,	0, mySize / 2, 1.0),	\n\
	vec4(	  0, -mySize / 2, mySize / 2, 1.0),	\n\
	vec4(mySize / 2,	0, mySize / 2, 1.0),	\n\
	vec4(mySize / 2,	0, mySize / 2, 1.0),	/*caraI*/	\n\
	vec4(	0, -mySize / 2, mySize/2, 1.0),	\n\
	vec4(	0, -mySize / 2, mySize/2, 1.0));	\n\
	vec4 vertices11_3[10] = vec4[10](vec4(mySize / 2,	  0,	  0, 1.0),	/*caraD*/	\n\
	vec4(	  0, -mySize / 2,	  0, 1.0),	\n\
	vec4(mySize / 2,	  0,	  0, 1.0),	\n\
	vec4(	  0, -mySize / 2,  	  0, 1.0),	/*caraC*/	\n\
	vec4(mySize / 2,	  0,	  0, 1.0),	\n\
	vec4(	  0, -mySize / 2,  	  0, 1.0),	\n\
	vec4(	  0,	  0,   mySize/2, 1.0),	\n\
	vec4(	0,	  0, mySize/2, 1.0),	/*caraI*/	\n\
	vec4(	0,	  0, mySize/2, 1.0),	\n\
	vec4(	0,-mySize/2,	0, 1.0));	\n\
	for (int i = 0; i < 3; ++i) {	\n\
	vec4 localVec;	\n\
	if(progress<0.5)	\n\
	localVec=((1-progress*2)*vertices11_1[i]+progress*2*vertices11_2[i]);	\n\
	else	\n\
	localVec=((2-progress*2)*vertices11_2[i]+(progress*2-1)*vertices11_3[i]);	\n\
	if (localRot)	\n\
	gl_Position = (rotation * (localVec + truePos));	\n\
	else	\n\
	gl_Position = (rotation * (localVec)) + truePos;	\n\
	gl_PrimitiveID = 4;	\n\
	EmitVertex();	\n\
	}	\n\
	EndPrimitive();	\n\
	for (int i = 0; i < 4; ++i) {	\n\
	vec4 localVec;	\n\
	if(progress<0.5)	\n\
	localVec=((1-progress*2)*vertices11_1[i+3]+progress*2*vertices11_2[i+3]);	\n\
	else	\n\
	localVec=((2-progress*2)*vertices11_2[i+3]+(progress*2-1)*vertices11_3[i+3]);	\n\
	if (localRot)	\n\
	gl_Position = (rotation * (localVec + truePos));	\n\
	else	\n\
	gl_Position = (rotation * (localVec)) + truePos;	\n\
	gl_PrimitiveID = 4;	\n\
	EmitVertex();	\n\
	}	\n\
	EndPrimitive();	\n\
	for (int i = 0; i < 3; ++i) {	\n\
	vec4 localVec;	\n\
	if(progress<0.5)	\n\
	localVec=((1-progress*2)*vertices11_1[i+7]+progress*2*vertices11_2[i+7]);	\n\
	else	\n\
	localVec=((2-progress*2)*vertices11_2[i+7]+(progress*2-1)*vertices11_3[i+7]);	\n\
	if (localRot)	\n\
	gl_Position = (rotation * (localVec + truePos));	\n\
	else	\n\
	gl_Position = (rotation * (localVec)) + truePos;	\n\
	gl_PrimitiveID = 4;	\n\
	EmitVertex();	\n\
	}	\n\
	EndPrimitive();	\n\
	\n\
	vec4 vertices12_1[10] = vec4[10](vec4(mySize / 2, -mySize / 2, -mySize / 2, 1.0),	/*caraD*/	\n\
	vec4(mySize / 2, -mySize / 2, -mySize / 2, 1.0),	\n\
	vec4(mySize / 2, -mySize / 2,-mySize / 2, 1.0),	\n\
	vec4(mySize / 2, -mySize / 2, -mySize / 2, 1.0),	/*caraC*/	\n\
	vec4(mySize / 2, -mySize / 2, -mySize / 2, 1.0),	\n\
	vec4(mySize / 2, -mySize / 2, -mySize / 2, 1.0),	\n\
	vec4(mySize / 2, -mySize / 2, -mySize / 2, 1.0),	\n\
	vec4(mySize / 2, -mySize / 2, -mySize / 2, 1.0),	/*caraI*/	\n\
	vec4(mySize / 2, -mySize / 2, -mySize / 2, 1.0),	\n\
	vec4(mySize / 2, -mySize / 2, -mySize / 2, 1.0));	\n\
	vec4 vertices12_2[10] = vec4[10](vec4(mySize / 2,	0, -mySize / 2, 1.0),	/*caraD*/	\n\
	vec4(mySize / 2, -mySize / 2,	0, 1.0),	\n\
	vec4(mySize / 2, -mySize / 2,	0, 1.0),	\n\
	vec4(mySize / 2,	0, -mySize / 2, 1.0),	/*caraC*/	\n\
	vec4(mySize / 2, -mySize / 2,	0, 1.0),	\n\
	vec4(mySize / 2,	0, -mySize / 2, 1.0),	\n\
	vec4(	  0, -mySize / 2, -mySize / 2, 1.0),	\n\
	vec4(mySize / 2,	0, -mySize / 2, 1.0),	/*caraI*/	\n\
	vec4(	0, -mySize / 2, -mySize/2, 1.0),	\n\
	vec4(	0, -mySize / 2, -mySize/2, 1.0));	\n\
	vec4 vertices12_3[10] = vec4[10](vec4(mySize / 2,	  0,	  0, 1.0),	/*caraD*/	\n\
	vec4(mySize / 2, 	  0,	  0, 1.0),	\n\
	vec4(	  0, -mySize / 2,	  0, 1.0),	\n\
	vec4(mySize / 2,	  0,	  0, 1.0),	/*caraC*/	\n\
	vec4(	  0, -mySize / 2,  	  0, 1.0),	\n\
	vec4(	  0,	  0,   -mySize/2, 1.0),	\n\
	vec4(	  0, -mySize / 2,  	  0, 1.0),	\n\
	vec4(	0,	  0, -mySize/2, 1.0),	/*caraI*/	\n\
	vec4(	0, -mySize/2,	  0, 1.0),	\n\
	vec4(	0,	  0, -mySize/2, 1.0));	\n\
	for (int i = 0; i < 3; ++i) {	\n\
	vec4 localVec;	\n\
	if(progress<0.5)	\n\
	localVec=((1-progress*2)*vertices12_1[i]+progress*2*vertices12_2[i]);	\n\
	else	\n\
	localVec=((2-progress*2)*vertices12_2[i]+(progress*2-1)*vertices12_3[i]);	\n\
	if (localRot)	\n\
	gl_Position = (rotation * (localVec + truePos));	\n\
	else	\n\
	gl_Position = (rotation * (localVec)) + truePos;	\n\
	gl_PrimitiveID = 3;	\n\
	EmitVertex();	\n\
	}	\n\
	EndPrimitive();	\n\
	for (int i = 0; i < 4; ++i) {	\n\
	vec4 localVec;	\n\
	if(progress<0.5)	\n\
	localVec=((1-progress*2)*vertices12_1[i+3]+progress*2*vertices12_2[i+3]);	\n\
	else	\n\
	localVec=((2-progress*2)*vertices12_2[i+3]+(progress*2-1)*vertices12_3[i+3]);	\n\
	if (localRot)	\n\
	gl_Position = (rotation * (localVec + truePos));	\n\
	else	\n\
	gl_Position = (rotation * (localVec)) + truePos;	\n\
	gl_PrimitiveID = 3;	\n\
	EmitVertex();	\n\
	}	\n\
	EndPrimitive();	\n\
	for (int i = 0; i < 3; ++i) {	\n\
	vec4 localVec;	\n\
	if(progress<0.5)	\n\
	localVec=((1-progress*2)*vertices12_1[i+7]+progress*2*vertices12_2[i+7]);	\n\
	else	\n\
	localVec=((2-progress*2)*vertices12_2[i+7]+(progress*2-1)*vertices12_3[i+7]);	\n\
	if (localRot)	\n\
	gl_Position = (rotation * (localVec + truePos));	\n\
	else	\n\
	gl_Position = (rotation * (localVec)) + truePos;	\n\
	gl_PrimitiveID = 3;	\n\
	EmitVertex();	\n\
	}	\n\
	EndPrimitive();"
			"vec4 vertices13_1[10] = vec4[10](vec4(-mySize / 2, -mySize / 2, mySize / 2, 1.0),	/*caraD*/	\n\
	vec4(-mySize / 2, -mySize / 2, mySize / 2, 1.0),	\n\
	vec4(-mySize / 2, -mySize / 2,mySize / 2, 1.0),	\n\
	vec4(-mySize / 2, -mySize / 2, mySize / 2, 1.0),	/*caraC*/	\n\
	vec4(-mySize / 2, -mySize / 2, mySize / 2, 1.0),	\n\
	vec4(-mySize / 2, -mySize / 2, mySize / 2, 1.0),	\n\
	vec4(-mySize / 2, -mySize / 2, mySize / 2, 1.0),	\n\
	vec4(-mySize / 2, -mySize / 2, mySize / 2, 1.0),	/*caraI*/	\n\
	vec4(-mySize / 2, -mySize / 2, mySize / 2, 1.0),	\n\
	vec4(-mySize / 2, -mySize / 2, mySize / 2, 1.0));	\n\
	vec4 vertices13_2[10] = vec4[10](vec4(-mySize / 2,	0, mySize / 2, 1.0),	/*caraD*/	\n\
	vec4(-mySize / 2, -mySize / 2,	0, 1.0),	\n\
	vec4(-mySize / 2, -mySize / 2,	0, 1.0),	\n\
	vec4(-mySize / 2,	0, mySize / 2, 1.0),	/*caraC*/	\n\
	vec4(-mySize / 2, -mySize / 2,	0, 1.0),	\n\
	vec4(-mySize / 2,	0, mySize / 2, 1.0),	\n\
	vec4(	  0, -mySize / 2, mySize / 2, 1.0),	\n\
	vec4(-mySize / 2,	0, mySize / 2, 1.0),	/*caraI*/	\n\
	vec4(	0, -mySize / 2, mySize/2, 1.0),	\n\
	vec4(	0, -mySize / 2, mySize/2, 1.0));	\n\
	vec4 vertices13_3[10] = vec4[10](vec4(-mySize / 2,	  0,	  0, 1.0),	/*caraD*/	\n\
	vec4(-mySize / 2, 	  0,	  0, 1.0),	\n\
	vec4(	  0, -mySize / 2,	  0, 1.0),	\n\
	vec4(-mySize / 2,	  0,	  0, 1.0),	/*caraC*/	\n\
	vec4(	  0, -mySize / 2,  	  0, 1.0),	\n\
	vec4(	  0,	  0,   mySize/2, 1.0),	\n\
	vec4(	  0, -mySize / 2,  	  0, 1.0),	\n\
	vec4(	0,	  0, mySize/2, 1.0),	/*caraI*/	\n\
	vec4(	0, -mySize/2,	  0, 1.0),	\n\
	vec4(	0,	  0, mySize/2, 1.0));	\n\
	for (int i = 0; i < 3; ++i) {	\n\
	vec4 localVec;	\n\
	if(progress<0.5)	\n\
	localVec=((1-progress*2)*vertices13_1[i]+progress*2*vertices13_2[i]);	\n\
	else	\n\
	localVec=((2-progress*2)*vertices13_2[i]+(progress*2-1)*vertices13_3[i]);	\n\
	if (localRot)	\n\
	gl_Position = (rotation * (localVec + truePos));	\n\
	else	\n\
	gl_Position = (rotation * (localVec)) + truePos;	\n\
	gl_PrimitiveID = 3;	\n\
	EmitVertex();	\n\
	}	\n\
	EndPrimitive();	\n\
	for (int i = 0; i < 4; ++i) {	\n\
	vec4 localVec;	\n\
	if(progress<0.5)	\n\
	localVec=((1-progress*2)*vertices13_1[i+3]+progress*2*vertices13_2[i+3]);	\n\
	else	\n\
	localVec=((2-progress*2)*vertices13_2[i+3]+(progress*2-1)*vertices13_3[i+3]);	\n\
	if (localRot)	\n\
	gl_Position = (rotation * (localVec + truePos));	\n\
	else	\n\
	gl_Position = (rotation * (localVec)) + truePos;	\n\
	gl_PrimitiveID = 3;	\n\
	EmitVertex();	\n\
	}	\n\
	EndPrimitive();	\n\
	for (int i = 0; i < 3; ++i) {	\n\
	vec4 localVec;	\n\
	if(progress<0.5)	\n\
	localVec=((1-progress*2)*vertices13_1[i+7]+progress*2*vertices13_2[i+7]);	\n\
	else	\n\
	localVec=((2-progress*2)*vertices13_2[i+7]+(progress*2-1)*vertices13_3[i+7]);	\n\
	if (localRot)	\n\
	gl_Position = (rotation * (localVec + truePos));	\n\
	else	\n\
	gl_Position = (rotation * (localVec)) + truePos;	\n\
	gl_PrimitiveID = 3;	\n\
	EmitVertex();	\n\
	}	\n\
	EndPrimitive();	\n\
	\n\
	\n\
	vec4 vertices14_1[10] = vec4[10](vec4(-mySize / 2, -mySize / 2, -mySize / 2, 1.0),	/*caraD*/	\n\
	vec4(-mySize / 2, -mySize / 2, -mySize / 2, 1.0),	\n\
	vec4(-mySize / 2, -mySize / 2,-mySize / 2, 1.0),	\n\
	vec4(-mySize / 2, -mySize / 2, -mySize / 2, 1.0),	/*caraC*/	\n\
	vec4(-mySize / 2, -mySize / 2, -mySize / 2, 1.0),	\n\
	vec4(-mySize / 2, -mySize / 2, -mySize / 2, 1.0),	\n\
	vec4(-mySize / 2, -mySize / 2, -mySize / 2, 1.0),	\n\
	vec4(-mySize / 2, -mySize / 2, -mySize / 2, 1.0),	/*caraI*/	\n\
	vec4(-mySize / 2, -mySize / 2, -mySize / 2, 1.0),	\n\
	vec4(-mySize / 2, -mySize / 2, -mySize / 2, 1.0));	\n\
	vec4 vertices14_2[10] = vec4[10](vec4(-mySize / 2,	0, -mySize / 2, 1.0),	/*caraD*/	\n\
	vec4(-mySize / 2, -mySize / 2,	0, 1.0),	\n\
	vec4(-mySize / 2, -mySize / 2,	0, 1.0),	\n\
	vec4(-mySize / 2, -mySize / 2,	0, 1.0),	/*caraC*/	\n\
	vec4(-mySize / 2,	0, -mySize / 2, 1.0),	\n\
	vec4(	  0, -mySize / 2, -mySize / 2, 1.0),	\n\
	vec4(-mySize / 2,	0, -mySize / 2, 1.0),	\n\
	vec4(-mySize / 2,	0, -mySize / 2, 1.0),	/*caraI*/	\n\
	vec4(	0, -mySize / 2, -mySize/2, 1.0),	\n\
	vec4(	0, -mySize / 2, -mySize/2, 1.0));	\n\
	vec4 vertices14_3[10] = vec4[10](vec4(-mySize / 2,	  0,	  0, 1.0),	/*caraD*/	\n\
	vec4(	  0, -mySize / 2,	  0, 1.0),	\n\
	vec4(-mySize / 2,	  0,	  0, 1.0),	\n\
	vec4(	  0, -mySize / 2,  	  0, 1.0),	/*caraC*/	\n\
	vec4(-mySize / 2,	  0,	  0, 1.0),	\n\
	vec4(	  0, -mySize / 2,  	  0, 1.0),	\n\
	vec4(	  0,	  0,   -mySize/2, 1.0),	\n\
	vec4(	0,	  0, -mySize/2, 1.0),	/*caraI*/	\n\
	vec4(	0,	  0, -mySize/2, 1.0),	\n\
	vec4(	0,-mySize/2,	0, 1.0));	\n\
	for (int i = 0; i < 3; ++i) {	\n\
	vec4 localVec;	\n\
	if(progress<0.5)	\n\
	localVec=((1-progress*2)*vertices14_1[i]+progress*2*vertices14_2[i]);	\n\
	else	\n\
	localVec=((2-progress*2)*vertices14_2[i]+(progress*2-1)*vertices14_3[i]);	\n\
	if (localRot)	\n\
	gl_Position = (rotation * (localVec + truePos));	\n\
	else	\n\
	gl_Position = (rotation * (localVec)) + truePos;	\n\
	gl_PrimitiveID = 4;	\n\
	EmitVertex();	\n\
	}	\n\
	EndPrimitive();	\n\
	for (int i = 0; i < 4; ++i) {	\n\
	vec4 localVec;	\n\
	if(progress<0.5)	\n\
	localVec=((1-progress*2)*vertices14_1[i+3]+progress*2*vertices14_2[i+3]);	\n\
	else	\n\
	localVec=((2-progress*2)*vertices14_2[i+3]+(progress*2-1)*vertices14_3[i+3]);	\n\
	if (localRot)	\n\
	gl_Position = (rotation * (localVec + truePos));	\n\
	else	\n\
	gl_Position = (rotation * (localVec)) + truePos;	\n\
	gl_PrimitiveID = 4;	\n\
	EmitVertex();	\n\
	}	\n\
	EndPrimitive();	\n\
	for (int i = 0; i < 3; ++i) {	\n\
	vec4 localVec;	\n\
	if(progress<0.5)	\n\
	localVec=((1-progress*2)*vertices14_1[i+7]+progress*2*vertices14_2[i+7]);	\n\
	else	\n\
	localVec=((2-progress*2)*vertices14_2[i+7]+(progress*2-1)*vertices14_3[i+7]);	\n\
	if (localRot)	\n\
	gl_Position = (rotation * (localVec + truePos));	\n\
	else	\n\
	gl_Position = (rotation * (localVec)) + truePos;	\n\
	gl_PrimitiveID = 4;	\n\
	EmitVertex();	\n\
	}	\n\
	EndPrimitive();	\n\
	}	\n\
	"
		};


		static const GLchar * mfragment_shader_source[] =
		{ "#version 330\n\
	\n\
	out vec4 color;\n\
	\n\
	void main() {\n\
	const vec4 colors[5] = vec4[5](	vec4(0.90,0.0,0.13,1.0),\n\
	vec4(0.80,0.9,0.13,1.0),\n\
	vec4(0.1,0.41,0.83,1.0),\n\
	vec4(0.14,0.8,0.19,1.0),\n\
	vec4(0.03,0.33,0.09,1.0));\n\
	color=colors[gl_PrimitiveID];\n\
	}"
		};

		GLuint mvertex_shader;
		GLuint mgeom_shader;
		GLuint mfragment_shader;
		GLuint mprogram;

		mvertex_shader = glCreateShader(GL_VERTEX_SHADER);
		glShaderSource(mvertex_shader, 1, mvertex_shader_source, NULL);
		glCompileShader(mvertex_shader);

		mgeom_shader = glCreateShader(GL_GEOMETRY_SHADER);
		glShaderSource(mgeom_shader, 1, mgeom_shader_source, NULL);
		glCompileShader(mgeom_shader);

		mfragment_shader = glCreateShader(GL_FRAGMENT_SHADER);
		glShaderSource(mfragment_shader, 1, mfragment_shader_source, NULL);
		glCompileShader(mfragment_shader);

		mprogram = glCreateProgram();
		glAttachShader(mprogram, mvertex_shader);
		glAttachShader(mprogram, mgeom_shader);
		glAttachShader(mprogram, mfragment_shader);
		glLinkProgram(mprogram);

		glDeleteShader(mvertex_shader);
		glDeleteShader(mgeom_shader);
		glDeleteShader(mfragment_shader);

		return mprogram;

	};

	GLuint octocahedronWire(void) {

		static const GLchar * wovertex_shader_source[] =
		{
			"#version 330														\n\
		void main() {															\n\
			const vec4 vertices[3] = vec4[3](	vec4( 0.25,-0.25, 0.5, 1.0),	\n\
												vec4( 0.25, 0.25, 0.5, 1.0),	\n\
												vec4(-0.25,-0.25, 0.5, 1.0));	\n\
			gl_Position = vertices[gl_VertexID];								\n\
		}"
		};

		static GLchar * wogeom_shader_source[] =
		{
			"#version 330																						\n\
			uniform float mySize;																				\n\
			uniform vec3 pos;																					\n\
			vec4 truePos=vec4(pos.x, pos.y, pos.z, 1);															\n\
			vec4 fix= vec4(0, mySize, 0, 0);																	\n\
			uniform mat4 rotation;																				\n\
			uniform mat4 scale;																					\n\
			uniform bool localRot;																				\n\
			layout(lines) in;																					\n\
			layout(line_strip, max_vertices = 104) out;															\n\
			void main() {																						\n\
				vec4 vertices[4] =	vec4[4](	vec4( 0, mySize/3, -mySize/3, 1.0),								\n\
												vec4( mySize/3, mySize/3, 0, 1.0),								\n\
												vec4( 0, mySize/3, mySize/3, 1.0),								\n\
												vec4( -mySize/3, mySize/3, 0, 1.0));							\n\
				for (int i = 0; i < 4; ++i) {																	\n\
					if(localRot)																				\n\
						gl_Position = (rotation * (vertices[i]  + truePos));									\n\
					else																						\n\
						gl_Position = (rotation * (vertices[i]-fix))  + truePos;								\n\
					gl_PrimitiveID = 1;																			\n\
					EmitVertex();																				\n\
				}																								\n\
				EndPrimitive();																					\n\
				vec4 vertices2[4] =	vec4[4](	vec4( 0, 5*mySize/3, -mySize/3, 1.0),							\n\
												vec4( -mySize/3, 5*mySize/3, 0, 1.0),							\n\
												vec4( 0, 5*mySize/3, mySize/3, 1.0),							\n\
												vec4( mySize/3, 5*mySize/3, 0, 1.0));							\n\
				for (int i = 0; i < 4; ++i) {																	\n\
					if(localRot)																				\n\
						gl_Position = rotation * (vertices2[i]  + truePos);										\n\
					else																						\n\
						gl_Position = (rotation * (vertices2[i]-fix))  + truePos;								\n\
					gl_PrimitiveID = 1;																			\n\
					EmitVertex();																				\n\
				}																								\n\
				EndPrimitive();																					\n\
				vec4 vertices3[4] =	vec4[4](	vec4( 0, 2*mySize/3, 2*mySize/3, 1.0),							\n\
												vec4( mySize/3, mySize, 2*mySize/3, 1.0),						\n\
												vec4( 0, 4*mySize/3, 2*mySize/3, 1.0),							\n\
												vec4( -mySize/3, mySize, 2*mySize/3, 1.0));						\n\
				for (int i = 0; i < 4; ++i) {																	\n\
					if(localRot)																				\n\
						gl_Position = rotation * (vertices3[i]  + truePos);										\n\
					else																						\n\
						gl_Position = (rotation * (vertices3[i]-fix))  + truePos;								\n\
					gl_PrimitiveID = 1;																			\n\
					EmitVertex();																				\n\
				}																								\n\
				EndPrimitive();																					\n\
				vec4 vertices4[4] =	vec4[4](	vec4( 0, 2*mySize/3, -2*mySize/3, 1.0),							\n\
												vec4( -mySize/3, mySize, -2*mySize/3, 1.0),						\n\
												vec4( 0, 4*mySize/3, -2*mySize/3, 1.0),							\n\
												vec4( mySize/3, mySize, -2*mySize/3, 1.0));						\n\
				for (int i = 0; i < 4; ++i) {																	\n\
					if(localRot)																				\n\
						gl_Position = rotation * (vertices4[i]  + truePos);										\n\
					else																						\n\
						gl_Position = (rotation * (vertices4[i]-fix))  + truePos;								\n\
					gl_PrimitiveID = 1;																			\n\
					EmitVertex();																				\n\
				}																								\n\
				EndPrimitive();																					\n\
				vec4 vertices5[4] =	vec4[4](	vec4(-2*mySize/3, 2*mySize/3, 0, 1.0),							\n\
												vec4(-2*mySize/3, mySize, mySize/3, 1.0),						\n\
												vec4(-2*mySize/3, 4*mySize/3, 0, 1.0),							\n\
												vec4(-2*mySize/3, mySize, -mySize/3, 1.0));						\n\
				for (int i = 0; i < 4; ++i) {																	\n\
					if(localRot)																				\n\
						gl_Position = rotation * (vertices5[i]  + truePos);										\n\
					else																						\n\
						gl_Position = (rotation * (vertices5[i]-fix))  + truePos;								\n\
					gl_PrimitiveID = 1;																			\n\
					EmitVertex();																				\n\
				}																								\n\
				EndPrimitive();																					\n\
				vec4 vertices6[4] =	vec4[4](	vec4(2*mySize/3, 2*mySize/3, 0, 1.0),							\n\
												vec4(2*mySize/3, mySize, -mySize/3, 1.0),						\n\
												vec4(2*mySize/3, 4*mySize/3, 0, 1.0),							\n\
												vec4(2*mySize/3, mySize, mySize/3, 1.0));						\n\
				for (int i = 0; i < 4; ++i) {																	\n\
					if(localRot)																				\n\
						gl_Position = rotation * (vertices6[i]  + truePos);										\n\
					else																						\n\
						gl_Position = (rotation * (vertices6[i]-fix))  + truePos;								\n\
					gl_PrimitiveID = 1;																			\n\
					EmitVertex();																				\n\
				}																								\n\
				EndPrimitive();																					\n\
				///////////////////////////////////////////HEX핯ONO 1///////////////////////////////////////////\n\
				vec4 vertices8[4] = vec4[4](	vec4( 0, mySize/3, mySize/3, 1.0),//abajo izquierda				\n\
												vec4( 0, 2*mySize/3, 2*mySize/3, 1.0),//centro izquierda		\n\
												vec4( mySize/3, mySize, 2*mySize/3, 1.0),//arriba izquierda		\n\
												vec4( 2*mySize/3, mySize, mySize/3, 1.0));//arriba derecha		\n\
				for (int i = 0; i < 4; ++i) {																	\n\
					if(localRot)																				\n\
						gl_Position = rotation * (vertices8[i]  + truePos);										\n\
					else																						\n\
						gl_Position = (rotation * (vertices8[i]-fix))  + truePos;								\n\
					gl_PrimitiveID = 0;																			\n\
					EmitVertex();																				\n\
				}																								\n\
				EndPrimitive();																					\n\
				vec4 vertices9[4] =	vec4[4](	vec4( 2*mySize/3, mySize, mySize/3, 1.0),//arriba derecha		\n\
												vec4( 2*mySize/3, 2*mySize/3, 0, 1.0),//centro derecha			\n\
												vec4( mySize/3, mySize/3, 0, 1.0),//abajo derecha				\n\
												vec4( 0, mySize/3, mySize/3, 1.0));//abajo izquierda			\n\
				for (int i = 0; i < 4; ++i) {																	\n\
					if(localRot)																				\n\
						gl_Position = rotation * (vertices9[i]  + truePos);										\n\
					else																						\n\
						gl_Position = (rotation * (vertices9[i]-fix))  + truePos;								\n\
					gl_PrimitiveID = 0;																			\n\
					EmitVertex();																				\n\
				}																								\n\
				EndPrimitive();"
			"///////////////////////////////////////////HEX핯ONO 2///////////////////////////////////////////\n\
				vec4 vertices11[4] = vec4[4](	vec4( 0, mySize/3, mySize/3, 1.0),//abajo derecha				\n\
												vec4( 0, 2*mySize/3, 2*mySize/3, 1.0),//centro derecha			\n\
												vec4( -mySize/3, mySize, 2*mySize/3, 1.0),//arriba derecha		\n\
												vec4( -2*mySize/3, mySize, mySize/3, 1.0));//arriba izquierda	\n\
				for (int i = 0; i < 4; ++i) {																	\n\
					if(localRot)																				\n\
						gl_Position = rotation * (vertices11[i]  + truePos);									\n\
					else																						\n\
						gl_Position = (rotation * (vertices11[i]-fix))  + truePos;								\n\
					gl_PrimitiveID = 0;																			\n\
					EmitVertex();																				\n\
				}																								\n\
				EndPrimitive();																					\n\
				vec4 vertices12[4] = vec4[4](	vec4( 0, mySize/3, mySize/3, 1.0),//abajo derecha				\n\
												vec4( -mySize/3, mySize/3, 0, 1.0),//abajo izquierda			\n\
												vec4( -2*mySize/3, 2*mySize/3, 0, 1.0),//centro izquierda		\n\
												vec4( -2*mySize/3, mySize, mySize/3, 1.0));//arriba izquierda	\n\
				for (int i = 0; i < 4; ++i) {																	\n\
					if(localRot)																				\n\
						gl_Position = rotation * (vertices12[i]  + truePos);									\n\
					else																						\n\
						gl_Position = (rotation * (vertices12[i]-fix))  + truePos;								\n\
					gl_PrimitiveID = 0;																			\n\
					EmitVertex();																				\n\
				}																								\n\
				EndPrimitive();																					\n\
				///////////////////////////////////////////HEX핯ONO 3///////////////////////////////////////////\n\
				vec4 vertices14[4] = vec4[4](	vec4( 0, 2*mySize/3, -2*mySize/3, 1.0),//centro izquierda		\n\
												vec4( 0, mySize/3, -mySize/3, 1.0),//abajo izquierda			\n\
												vec4( -mySize/3, mySize/3, 0, 1.0),//abajo derecha				\n\
												vec4( -2*mySize/3, 2*mySize/3, 0, 1.0));//centro derecha		\n\
				for (int i = 0; i < 4; ++i) {																	\n\
					if(localRot)																				\n\
						gl_Position = rotation * (vertices14[i]  + truePos);									\n\
					else																						\n\
						gl_Position = (rotation * (vertices14[i]-fix))  + truePos;								\n\
					gl_PrimitiveID = 0;																			\n\
					EmitVertex();																				\n\
				}																								\n\
				EndPrimitive();																					\n\
				vec4 vertices15[4] = vec4[4](	vec4( -2*mySize/3, 2*mySize/3, 0, 1.0),//centro derecha			\n\
												vec4( -2*mySize/3, mySize, -mySize/3, 1.0),//arriba derecha		\n\
												vec4( -mySize/3, mySize, -2*mySize/3, 1.0),//arriba izquierda	\n\
												vec4( 0, 2*mySize/3, -2*mySize/3, 1.0));//centro izquierda		\n\
				for (int i = 0; i < 4; ++i) {																	\n\
					if(localRot)																				\n\
						gl_Position = rotation * (vertices15[i]  + truePos);									\n\
					else																						\n\
						gl_Position = (rotation * (vertices15[i]-fix))  + truePos;								\n\
					gl_PrimitiveID = 0;																			\n\
					EmitVertex();																				\n\
				}																								\n\
				EndPrimitive();																					\n\
				///////////////////////////////////////////HEX핯ONO 3///////////////////////////////////////////\n\
				vec4 vertices17[4] = vec4[4](	vec4( 0, 2*mySize/3, -2*mySize/3, 1.0),//centro derecha			\n\
												vec4( mySize/3, mySize, -2*mySize/3, 1.0),//arriba derecha		\n\
												vec4( 2*mySize/3, mySize, -mySize/3, 1.0),	//arriba izquierda	\n\
												vec4( 2*mySize/3, 2*mySize/3, 0, 1.0));//centro izquierda		\n\
				for (int i = 0; i < 4; ++i) {																	\n\
					if(localRot)																				\n\
						gl_Position = rotation * (vertices17[i]  + truePos);									\n\
					else																						\n\
						gl_Position = (rotation * (vertices17[i]-fix))  + truePos;								\n\
					gl_PrimitiveID = 0;																			\n\
					EmitVertex();																				\n\
				}																								\n\
				EndPrimitive();																					\n\
				vec4 vertices18[4] = vec4[4](	vec4( 2*mySize/3, 2*mySize/3, 0, 1.0),//centro izquierda		\n\
												vec4( mySize/3, mySize/3, 0, 1.0),//abajo izquierda				\n\
												vec4( 0, mySize/3, -mySize/3, 1.0),//abajo izquierda			\n\
												vec4( 0, 2*mySize/3, -2*mySize/3, 1.0));//centro derecha		\n\
				for (int i = 0; i < 4; ++i) {																	\n\
					if(localRot)																				\n\
						gl_Position = rotation * (vertices18[i]  + truePos);									\n\
					else																						\n\
						gl_Position = (rotation * (vertices18[i]-fix))  + truePos;								\n\
					gl_PrimitiveID = 0;																			\n\
					EmitVertex();																				\n\
				}																								\n\
				EndPrimitive();																					\n\
				 vec4 vertices19[4] =	vec4[4](vec4( 0, 5*mySize/3, mySize/3, 1.0),//arriba izquierda			\n\
													vec4( mySize/3, 5*mySize/3, 0, 1.0),//arriba derecha		\n\
													vec4( 2*mySize/3, 4*mySize/3, 0, 1.0),//centro derecha		\n\
													vec4( 2*mySize/3, mySize, mySize/3, 1.0));//abajo derecha	\n\
				for (int i = 0; i < 4; ++i) {																	\n\
					if(localRot)																				\n\
						gl_Position = rotation * (vertices19[i]  + truePos);									\n\
					else																						\n\
						gl_Position = (rotation * (vertices19[i]-fix))  + truePos;								\n\
					gl_PrimitiveID = 3;																			\n\
					EmitVertex();																				\n\
				}																								\n\
				EndPrimitive();																					\n\
				 vec4 vertices20[4] = vec4[4](	vec4( 2*mySize/3, mySize, mySize/3, 1.0),//abajo derecha		\n\
												vec4( mySize/3, mySize, 2*mySize/3, 1.0),//abajo izquierda		\n\
												vec4( 0, 4*mySize/3, 2*mySize/3, 1.0),//centro izquierda		\n\
												vec4( 0, 5*mySize/3, mySize/3, 1.0));//arriba izquierda			\n\
				for (int i = 0; i < 4; ++i) {																	\n\
					if(localRot)																				\n\
						gl_Position = rotation * (vertices20[i]  + truePos);									\n\
					else																						\n\
						gl_Position = (rotation * (vertices20[i]-fix))  + truePos;								\n\
					gl_PrimitiveID = 3;																			\n\
					EmitVertex();																				\n\
				}																								\n\
				EndPrimitive();																					\n\
				 vec4 vertices22[4] = vec4[4](	vec4( -mySize/3, 5*mySize/3, 0, 1.0),//arriba izquierda			\n\
												vec4( 0, 5*mySize/3, mySize/3, 1.0),//arriba derecha			\n\
												vec4( 0, 4*mySize/3, 2*mySize/3, 1.0),//centro derecha			\n\
												vec4( -mySize/3, mySize, 2*mySize/3, 1.0));//abajo derecha		\n\
				for (int i = 0; i < 4; ++i) {																	\n\
					if(localRot)																				\n\
						gl_Position = rotation * (vertices22[i]  + truePos);									\n\
					else																						\n\
						gl_Position = (rotation * (vertices22[i]-fix))  + truePos;								\n\
					gl_PrimitiveID = 3;																			\n\
					EmitVertex();																				\n\
				}																								\n\
				EndPrimitive();																					\n\
				 vec4 vertices23[4] = vec4[4](	vec4( -mySize/3, mySize, 2*mySize/3, 1.0),//abajo derecha		\n\
												vec4( -2*mySize/3, mySize, mySize/3, 1.0),//abajo izquierda		\n\
												vec4( -2*mySize/3, 4*mySize/3, 0, 1.0),//centro izquierda		\n\
												vec4( -mySize/3, 5*mySize/3, 0, 1.0));//arriba izquierda		\n\
				for (int i = 0; i < 4; ++i) {																	\n\
					if(localRot)																				\n\
						gl_Position = rotation * (vertices23[i]  + truePos);									\n\
					else																						\n\
						gl_Position = (rotation * (vertices23[i]-fix))  + truePos;								\n\
					gl_PrimitiveID = 3;																			\n\
					EmitVertex();																				\n\
				}																								\n\
				EndPrimitive();																					\n\
				 vec4 vertices25[4] = vec4[4](	vec4( 0, 5*mySize/3, -mySize/3, 1.0),//arriba izquierda			\n\
												vec4( -mySize/3, 5*mySize/3, 0, 1.0),//arriba derecha			\n\
												vec4( -2*mySize/3, 4*mySize/3, 0, 1.0),//centro derecha			\n\
												vec4( -2*mySize/3, mySize, -mySize/3, 1.0));//abajo derecha		\n\
				for (int i = 0; i < 4; ++i) {																	\n\
					if(localRot)																				\n\
						gl_Position = rotation * (vertices25[i]  + truePos);									\n\
					else																						\n\
						gl_Position = (rotation * (vertices25[i]-fix))  + truePos;								\n\
					gl_PrimitiveID = 3;																			\n\
					EmitVertex();																				\n\
				}																								\n\
				EndPrimitive();																					\n\
				 vec4 vertices26[4] = vec4[4](	vec4( 0, 5*mySize/3, -mySize/3, 1.0),//arriba izquierda			\n\
												vec4( 0, 4*mySize/3, -2*mySize/3, 1.0),//centro izquierda		\n\
												vec4( -mySize/3, mySize, -2*mySize/3, 1.0),//abajo izquierda	\n\
												vec4( -2*mySize/3, mySize, -mySize/3, 1.0));//abajo derecha		\n\
				for (int i = 0; i < 4; ++i) {																	\n\
					if(localRot)																				\n\
						gl_Position = rotation * (vertices26[i]  + truePos);									\n\
					else																						\n\
						gl_Position = (rotation * (vertices26[i]-fix))  + truePos;								\n\
					gl_PrimitiveID = 3;																			\n\
					EmitVertex();																				\n\
				}																								\n\
				EndPrimitive();																					\n\
				 vec4 vertices28[4] = vec4[4](	vec4( mySize/3, 5*mySize/3, 0, 1.0),//arriba izquierda			\n\
												vec4( 0, 5*mySize/3, -mySize/3, 1.0),//arriba derecha			\n\
												vec4( 0, 4*mySize/3, -2*mySize/3, 1.0),//centro derecha			\n\
												vec4( mySize/3, mySize, -2*mySize/3, 1.0));//abajo derecha		\n\
				for (int i = 0; i < 4; ++i) {																	\n\
					if(localRot)																				\n\
						gl_Position = rotation * (vertices28[i]  + truePos);									\n\
					else																						\n\
						gl_Position = (rotation * (vertices28[i]-fix))  + truePos;								\n\
					gl_PrimitiveID = 3;																			\n\
					EmitVertex();																				\n\
				}																								\n\
				EndPrimitive();																					\n\
				 vec4 vertices29[4] = vec4[4](	vec4( mySize/3, mySize, -2*mySize/3, 1.0),//abajo derecha		\n\
												vec4( 2*mySize/3, mySize, -mySize/3, 1.0),//abajo izquierda		\n\
												vec4( 2*mySize/3, 4*mySize/3, 0, 1.0),//centro izquierda		\n\
												vec4( mySize/3, 5*mySize/3, 0, 1.0));//arriba izquierda			\n\
				for (int i = 0; i < 4; ++i) {																	\n\
					if(localRot)																				\n\
						gl_Position = rotation * (vertices29[i]  + truePos);									\n\
					else																						\n\
						gl_Position = (rotation * (vertices29[i]-fix))  + truePos;								\n\
					gl_PrimitiveID = 3;																			\n\
					EmitVertex();																				\n\
				}																								\n\
				EndPrimitive();																					\n\
			}"
		};

		static const GLchar * wofragment_shader_source[] =
		{
			"#version 330							\n\
													\n\
			uniform bool Ejercicio5;				\n\
			uniform float time;						\n\
			out vec4 color;							\n\
			float newtime = time;					\n\
													\n\
			void main() {							\n\
				if(Ejercicio5){\n\
					if (newtime < 5){		\n\
					vec4 colors[4] = vec4[4](vec4(1-(newtime/5),1.0,1-(newtime/5),0),\n\	//0\n\ //cuadrados\n\
													vec4(1-(newtime/5),0.8,1-(newtime/5),0),\n\	//1\n\
													vec4(1-(newtime/5),0.9,1-(newtime/5),0),\n\	//2\n\
													vec4(1-(newtime/5),0.7,1-(newtime/5),0));\n\	//3\n\
					color=colors[gl_PrimitiveID];\n\
						} \n\
					else if (newtime > 5){		\n\
						vec4 colors[4] = vec4[4](vec4(0,(1-(newtime-5)/5),0,0),\n\	//0\n\ //cuadrados\n\
														vec4(0,(1-(newtime-5)/5),0,0),\n\	//1\n\
														vec4(0,(1-(newtime-5)/5),0,0),\n\	//2\n\
														vec4(0,(1-(newtime-5)/5),0,0));\n\	//3\n\
						color=colors[gl_PrimitiveID];\n\
						} \n\
				}\n\
				else{	\n\
					vec4 colors[4] = vec4[4](vec4(1.0,1.0,1.0,1.0),\n\	//0\n\ //cuadrados\n\
													vec4(0.0,0.0,0.0,1.0),\n\	//1\n\
													vec4(0.0,1.0,0.0,1.0),\n\	//2\n\
													vec4(1.0,0.0,0.0,1.0));\n\	//3\n\
					color=colors[gl_PrimitiveID];\n\
				}\n\
			}"
		};

		GLuint wovertex_shader;
		GLuint wogeom_shader;
		GLuint wofragment_shader;
		GLuint woprogram;

		wovertex_shader = glCreateShader(GL_VERTEX_SHADER);
		glShaderSource(wovertex_shader, 1, wovertex_shader_source, NULL);
		glCompileShader(wovertex_shader);

		wogeom_shader = glCreateShader(GL_GEOMETRY_SHADER);
		glShaderSource(wogeom_shader, 1, wogeom_shader_source, NULL);
		glCompileShader(wogeom_shader);

		wofragment_shader = glCreateShader(GL_FRAGMENT_SHADER);
		glShaderSource(wofragment_shader, 1, wofragment_shader_source, NULL);
		glCompileShader(wofragment_shader);

		woprogram = glCreateProgram();
		glAttachShader(woprogram, wovertex_shader);
		glAttachShader(woprogram, wogeom_shader);
		glAttachShader(woprogram, wofragment_shader);
		glLinkProgram(woprogram);

		glDeleteShader(wovertex_shader);
		glDeleteShader(wogeom_shader);
		glDeleteShader(wofragment_shader);

		return woprogram;
	}

	float getRandomFloatBetween(float a, float b) {
		float random = (static_cast<float>(rand())) / static_cast<float>(RAND_MAX);
		float diff = b - a;
		float r = random * diff;
		return a + r;
	}

	void  myInitCode(void) {
		srand(time(NULL));

		myRenderProgram[0] = cubeShader();
		glCreateVertexArrays(1, &myVAO[0]);
		glBindVertexArray(myVAO[0]);

		myRenderProgram[1] = octocahedronShader();
		glCreateVertexArrays(1, &myVAO[1]);
		glBindVertexArray(myVAO[1]);

		myRenderProgram[2] = geometricMetamorfosis();
		glCreateVertexArrays(1, &myVAO[2]);
		glBindVertexArray(myVAO[2]);

		myRenderProgram[3] = octocahedronWire();
		glCreateVertexArrays(1, &myVAO[3]);
		glBindVertexArray(myVAO[3]);

		//myRenderProgram[2] = octocahedronMatrix();
		//glCreateVertexArrays(1, &myVAO[2]);
		//glBindVertexArray(myVAO[2]);

		ej1::pos1 = glm::vec3(getRandomFloatBetween(-5, 5), getRandomFloatBetween(0, 10), getRandomFloatBetween(-5, 0));
		ej1::pos2 = glm::vec3(getRandomFloatBetween(-5, 5), getRandomFloatBetween(0, 10), getRandomFloatBetween(-5, 0));

		ej3::seed1 = glm::vec3(1, 0, 0);
		ej3::seed2 = glm::vec3(-1, 1.4, 0);
		ej3::speed = 0.05;

		for (int i = 0; i < ej4::octoAmount; ++i) {
			ej4::seeds[i] = glm::vec3{ -2 + i * 4.1 / static_cast<float>(ej4::octoAmount), 2, 0 };
			ej4::seedR[i] = rand() % 2 + (rand() % 10) / 10.f;
			ej4::degRot[i] = glm::vec3(getRandomFloatBetween(0, 1), getRandomFloatBetween(0, 1), getRandomFloatBetween(0, 1));
		}
		ej4::speed = 0.03;

		for (int i = 0; i < ej5::octoAmount; ++i) {
			ej5::seeds[i] = glm::vec3{ -2 + i * 4.1 / static_cast<float>(ej5::octoAmount), 2, 0 };
			ej5::seedR[i] = rand() % 2 + (rand() % 10) / 10.f;
			ej5::degRot[i] = glm::vec3(getRandomFloatBetween(0, 1), getRandomFloatBetween(0, 1), getRandomFloatBetween(0, 1));
		}
		ej5::speed = 0.03;
	}

	void myRenderCode(double currentTime) {

		const Uint8* keyboardState = SDL_GetKeyboardState(NULL);
		float deltaTime = currentTime - ej4::lastTime;

		if (keyboardState[SDL_SCANCODE_1]) {

			RV::_projection = glm::perspective(RV::FOV, RV::width / RV::height, RV::zNear, RV::zFar);

			glUseProgram(myRenderProgram[0]);

			glm::mat4 rotation = { cos(currentTime),	0.f, -sin(currentTime), 0.f,
				0.f,				1.f, 0.f,				0.f,
				sin(currentTime),	0.f, cos(currentTime),	0.f,
				0.f,				0.f, 0.f,				1.f };
			float size = 1.f;

			glUniform3fv(glGetUniformLocation(myRenderProgram[0], "pos"), 1, (GLfloat*)&ej1::pos1);
			glUniform1f(glGetUniformLocation(myRenderProgram[0], "size"), (GLfloat)size);
			glUniformMatrix4fv(glGetUniformLocation(myRenderProgram[0], "rotation"), 1, GL_FALSE, glm::value_ptr(RV::_MVP));
			/*glUniform1f(glGetUniformLocation(myRenderProgram[0], "time"), (GLfloat)currentTime);*/
			glUniform1f(glGetUniformLocation(myRenderProgram[0], "time"), (GLfloat)currentTime);
			glDrawArrays(GL_TRIANGLES, 0, 3);

			glUniform3fv(glGetUniformLocation(myRenderProgram[0], "pos"), 1, (GLfloat*)&ej1::pos2);
			glUniform1f(glGetUniformLocation(myRenderProgram[0], "size"), (GLfloat)size);
			glUniformMatrix4fv(glGetUniformLocation(myRenderProgram[0], "rotation"), 1, GL_FALSE, glm::value_ptr(RV::_MVP));
			/*glUniform1f(glGetUniformLocation(myRenderProgram[0], "time"), (GLfloat)currentTime);*/
			glUniform1f(glGetUniformLocation(myRenderProgram[0], "time"), (GLfloat)currentTime);
			glDrawArrays(GL_TRIANGLES, 0, 3);
		}
		else if (keyboardState[SDL_SCANCODE_2]) {
			RV::_projection = glm::perspective(RV::FOV, RV::width / RV::height, RV::zNear, RV::zFar);
			glUseProgram(myRenderProgram[2]);

			float mySize = ej2::mySize;

			glm::vec3 pos{ 0, 5, 0 };
			bool localRotation = true;
			ej2::mySize = ((sin(currentTime) + 1) / 2)*1.334/2+1.334/2; 
			float progress = 0.75*glm::clamp(static_cast<float>((sin(currentTime) + 1) / 2), 0.f, 1.f);

			for (int i = 0; i < ej2::octoAmount; ++i) {
				glUniform1f(glGetUniformLocation(myRenderProgram[2], "mySize"), (GLfloat)mySize);
				glUniform1f(glGetUniformLocation(myRenderProgram[2], "progress"), (GLfloat)progress);
				glUniform3fv(glGetUniformLocation(myRenderProgram[2], "pos"), 1, (GLfloat*)&ej2::pos[i]);
				glUniform1f(glGetUniformLocation(myRenderProgram[2], "localRot"), (GLboolean)localRotation);
				glUniformMatrix4fv(glGetUniformLocation(myRenderProgram[2], "rotation"), 1, GL_FALSE, glm::value_ptr(RV::_MVP));
				glDrawArrays(GL_TRIANGLES, 0, 3);
			}
			//RV::_projection = glm::perspective(RV::FOV, RV::width / RV::height, RV::zNear, RV::zFar);

			//bool localRotation = true;
			//ej5::Ejercicio5 = false;
			//ej9::Ejercicio9 = false;
			//glUseProgram(myRenderProgram[1]);

			//glm::mat4 scale{ 5.f, 0.f, 0.f, 0.f,
			//	0.f, 5.f, 0.f, 0.f,
			//	0.f, 0.f, 5.f, 0.f,
			//	0.f, 0.f, 0.f, 1.f };

			//float mySize = 1;

			//for (int i = 0; i < ej2::octoAmount; ++i) {
			//	glUniform3fv(glGetUniformLocation(myRenderProgram[1], "pos"), 1, (GLfloat*)&ej2::pos[i]);
			//	glUniform1f(glGetUniformLocation(myRenderProgram[1], "mySize"), (GLfloat)mySize);
			//	glUniform1i(glGetUniformLocation(myRenderProgram[1], "Ejercicio5"), (GLboolean)ej5::Ejercicio5);
			//	glUniform1i(glGetUniformLocation(myRenderProgram[1], "Ejercicio9"), (GLboolean)ej9::Ejercicio9);
			//	glUniform1f(glGetUniformLocation(myRenderProgram[1], "time"), (GLfloat)currentTime);
			//	glUniformMatrix4fv(glGetUniformLocation(myRenderProgram[1], "rotation"), 1, GL_FALSE, glm::value_ptr(RV::_MVP));
			//	glUniformMatrix4fv(glGetUniformLocation(myRenderProgram[1], "scale"), 1, GL_FALSE, glm::value_ptr(scale));
			//	glUniform1f(glGetUniformLocation(myRenderProgram[1], "localRot"), (GLboolean)localRotation);
			//	glDrawArrays(GL_TRIANGLES, 0, 3);
			//}
		}
		else if (keyboardState[SDL_SCANCODE_3]) {
			RV::_projection = glm::ortho(-RV::width, RV::width, -RV::height, RV::height, RV::zNear, RV::zFar);

			glUseProgram(myRenderProgram[0]);

			float size = 0.05;
			for (int i = 0; i < ej4::octoAmount; ++i) {

				glm::mat4 rotationY = { cos(ej4::degRot[i].y*currentTime),	0.f, sin(ej4::degRot[i].y * currentTime), 0.f,
					0.f, 1.f, 0.f, 0.f,
					-sin(ej4::degRot[i].y * currentTime),	0.f, cos(ej4::degRot[i].y * currentTime),	0.f,
					0.f, 0.f, 0.f, 1.f };

				glm::mat4 rotationX = { 1,	0.f, 0.f, 0.f,
					0.f, cos(ej4::degRot[i].x * currentTime), -sin(ej4::degRot[i].x * currentTime),	0.f,
					0.f, sin(ej4::degRot[i].x * currentTime),	cos(ej4::degRot[i].x * currentTime),	0.f,
					0.f, 0.f, 0.f, 1.f };

				glm::mat4 rotationZ = { cos(ej4::degRot[i].z * currentTime), -sin(ej4::degRot[i].z * currentTime), 0.f, 0.f,
					sin(ej4::degRot[i].z * currentTime), cos(ej4::degRot[i].z * currentTime),  0.f, 0.f,
					0.f, 0.f, 1.f, 0.f,
					0.f, 0.f, 0.f, 1.f };

				glm::mat4 finalRot = rotationX * rotationY*rotationZ;

				glUniform3fv(glGetUniformLocation(myRenderProgram[0], "pos"), 1, (GLfloat*)&ej4::seeds[i]);
				glUniform1f(glGetUniformLocation(myRenderProgram[0], "size"), (GLfloat)size);
				glUniformMatrix4fv(glGetUniformLocation(myRenderProgram[0], "rotation"), 1, GL_FALSE, glm::value_ptr(finalRot));
				glDrawArrays(GL_TRIANGLES, 0, 3);
				ej4::seeds[i] -= glm::vec3(0, 0.005f + ej4::speed*ej4::seedR[i], 0);
			}
		}
		else if (keyboardState[SDL_SCANCODE_4]) {

			RV::_projection = glm::ortho(-RV::width, RV::width, -RV::height, RV::height, RV::zNear, RV::zFar);

			ej5::Ejercicio5 = false;
			ej9::Ejercicio9 = false;
			bool localRotation = false;
			float mySize = 0.1f;

			glUseProgram(myRenderProgram[1]);
			for (int i = 0; i < ej4::octoAmount; ++i) {

				float max = 0.3;
				glm::vec3 axis{ getRandomFloatBetween(0, max), getRandomFloatBetween(0, max), getRandomFloatBetween(0, max) };

				float degrees = 1;


				glm::mat4 rotationY = { cos(ej4::degRot[i].y * currentTime),	0.f, sin(ej4::degRot[i].y * currentTime), 0.f,
					0.f, 1.f, 0.f, 0.f,
					-sin(ej4::degRot[i].y * currentTime),	0.f, cos(ej4::degRot[i].y * currentTime),	0.f,
					0.f, 0.f, 0.f, 1.f };

				glm::mat4 rotationX = { 1,	0.f, 0.f, 0.f,
					0.f, cos(ej4::degRot[i].x * currentTime), -sin(ej4::degRot[i].x * currentTime),	0.f,
					0.f, sin(ej4::degRot[i].x * currentTime),	cos(ej4::degRot[i].x * currentTime),	0.f,
					0.f, 0.f, 0.f, 1.f };

				glm::mat4 rotationZ = { cos(ej4::degRot[i].z * currentTime), -sin(ej4::degRot[i].z * currentTime), 0.f, 0.f,
					sin(ej4::degRot[i].z * currentTime), cos(ej4::degRot[i].z * currentTime),  0.f, 0.f,
					0.f, 0.f, 1.f, 0.f,
					0.f, 0.f, 0.f, 1.f };

				glm::mat4 finalRot = rotationX * rotationY*rotationZ;


				glUniform3fv(glGetUniformLocation(myRenderProgram[1], "pos"), 1, (GLfloat*)&ej4::seeds[i]);
				glUniform1f(glGetUniformLocation(myRenderProgram[1], "mySize"), (GLfloat)mySize);
				glUniform1i(glGetUniformLocation(myRenderProgram[1], "Ejercicio5"), (GLboolean)ej5::Ejercicio5);
				glUniform1i(glGetUniformLocation(myRenderProgram[1], "Ejercicio9"), (GLboolean)ej9::Ejercicio9);
				glUniform1f(glGetUniformLocation(myRenderProgram[1], "time"), (GLfloat)currentTime);
				glUniformMatrix4fv(glGetUniformLocation(myRenderProgram[1], "rotation"), 1, GL_FALSE, glm::value_ptr(finalRot));
				glUniform1f(glGetUniformLocation(myRenderProgram[1], "localRot"), (GLboolean)localRotation);
				glDrawArrays(GL_TRIANGLES, 0, 3);
				ej4::seeds[i] -= glm::vec3(0, 0.005f + ej4::speed*ej4::seedR[i], 0);
			}
		}
		else if (keyboardState[SDL_SCANCODE_5]) {

			RV::_projection = glm::ortho(-RV::width, RV::width, -RV::height, RV::height, RV::zNear, RV::zFar);

			ej5::Ejercicio5 = true;
			ej9::Ejercicio9 = false;
			bool localRotation = false;
			float mySize = 0.1f;

			glUseProgram(myRenderProgram[1]);
			for (int i = 0; i < ej5::octoAmount; ++i) {

				float max = 0.3;
				glm::vec3 axis{ getRandomFloatBetween(0, max), getRandomFloatBetween(0, max), getRandomFloatBetween(0, max) };

				float degrees = 1;


				glm::mat4 rotationY = { cos(ej5::degRot[i].y * currentTime),	0.f, sin(ej5::degRot[i].y * currentTime), 0.f,
					0.f, 1.f, 0.f, 0.f,
					-sin(ej5::degRot[i].y * currentTime),	0.f, cos(ej5::degRot[i].y * currentTime),	0.f,
					0.f, 0.f, 0.f, 1.f };

				glm::mat4 rotationX = { 1,	0.f, 0.f, 0.f,
					0.f, cos(ej5::degRot[i].x * currentTime), -sin(ej5::degRot[i].x * currentTime),	0.f,
					0.f, sin(ej5::degRot[i].x * currentTime),	cos(ej5::degRot[i].x * currentTime),	0.f,
					0.f, 0.f, 0.f, 1.f };

				glm::mat4 rotationZ = { cos(ej5::degRot[i].z * currentTime), -sin(ej5::degRot[i].z * currentTime), 0.f, 0.f,
					sin(ej5::degRot[i].z * currentTime), cos(ej5::degRot[i].z * currentTime),  0.f, 0.f,
					0.f, 0.f, 1.f, 0.f,
					0.f, 0.f, 0.f, 1.f };

				//Aqui cambiariamos los colores

				glm::mat4 finalRot = rotationX * rotationY*rotationZ;

				glUniform4fv(glGetUniformLocation(myRenderProgram[1], "color"), 1, (GLfloat*)&ej5::colores[i]);
				glUniform3fv(glGetUniformLocation(myRenderProgram[1], "pos"), 1, (GLfloat*)&ej5::seeds[i]);
				glUniform1i(glGetUniformLocation(myRenderProgram[1], "Ejercicio5"), (GLboolean)ej5::Ejercicio5);
				glUniform1i(glGetUniformLocation(myRenderProgram[1], "Ejercicio9"), (GLboolean)ej9::Ejercicio9);
				glUniform1f(glGetUniformLocation(myRenderProgram[1], "mySize"), (GLfloat)mySize);
				glUniform1f(glGetUniformLocation(myRenderProgram[1], "time"), (GLfloat)fmod(currentTime, 2));

				glUniformMatrix4fv(glGetUniformLocation(myRenderProgram[1], "rotation"), 1, GL_FALSE, glm::value_ptr(finalRot));
				glUniform1f(glGetUniformLocation(myRenderProgram[1], "localRot"), (GLboolean)localRotation);
				glDrawArrays(GL_TRIANGLES, 0, 3);
				ej5::seeds[i] -= glm::vec3(0, 0.005f + ej5::speed*ej5::seedR[i], 0);
			}
		}
		else if (keyboardState[SDL_SCANCODE_6]) {
			RV::_projection = glm::perspective(RV::FOV, RV::width / RV::height, RV::zNear, RV::zFar);

			bool localRotation = true;
			ej5::Ejercicio5 = false;
			glUseProgram(myRenderProgram[3]);

			glm::mat4 scale{ 5.f, 0.f, 0.f, 0.f,
				0.f, 5.f, 0.f, 0.f,
				0.f, 0.f, 5.f, 0.f,
				0.f, 0.f, 0.f, 1.f };

			float mySize = 1;

			for (int i = 0; i < ej6a::octoAmount; ++i) {
				glUniform3fv(glGetUniformLocation(myRenderProgram[3], "pos"), 1, (GLfloat*)&ej6a::pos[i]);
				glUniform1f(glGetUniformLocation(myRenderProgram[3], "mySize"), (GLfloat)mySize);
				glUniform1i(glGetUniformLocation(myRenderProgram[3], "Ejercicio5"), (GLboolean)ej6a::Ejercicio5);
				glUniform1f(glGetUniformLocation(myRenderProgram[3], "time"), (GLfloat)currentTime);
				glUniformMatrix4fv(glGetUniformLocation(myRenderProgram[3], "rotation"), 1, GL_FALSE, glm::value_ptr(RV::_MVP));
				glUniformMatrix4fv(glGetUniformLocation(myRenderProgram[3], "scale"), 1, GL_FALSE, glm::value_ptr(scale));
				glUniform1f(glGetUniformLocation(myRenderProgram[3], "localRot"), (GLboolean)localRotation);
				glDrawArrays(GL_LINES, 0, 3);
			}
		}
		else if (keyboardState[SDL_SCANCODE_7]) {

			RV::_projection = glm::ortho(-RV::width, RV::width, -RV::height, RV::height, RV::zNear, RV::zFar);

			ej5::Ejercicio5 = false;
			ej9::Ejercicio9 = false;
			bool localRotation = false;
			float mySize = 0.1f;

			glUseProgram(myRenderProgram[1]);
			for (int i = 0; i < ej4::octoAmount; ++i) {

				float max = 0.3;
				glm::vec3 axis{ getRandomFloatBetween(0, max), getRandomFloatBetween(0, max), getRandomFloatBetween(0, max) };

				float degrees = 1;


				glm::mat4 rotationY = { cos(ej4::degRot[i].y * currentTime),	0.f, sin(ej4::degRot[i].y * currentTime), 0.f,
					0.f, 1.f, 0.f, 0.f,
					-sin(ej4::degRot[i].y * currentTime),	0.f, cos(ej4::degRot[i].y * currentTime),	0.f,
					0.f, 0.f, 0.f, 1.f };

				glm::mat4 rotationX = { 1,	0.f, 0.f, 0.f,
					0.f, cos(ej4::degRot[i].x * currentTime), -sin(ej4::degRot[i].x * currentTime),	0.f,
					0.f, sin(ej4::degRot[i].x * currentTime),	cos(ej4::degRot[i].x * currentTime),	0.f,
					0.f, 0.f, 0.f, 1.f };

				glm::mat4 rotationZ = { cos(ej4::degRot[i].z * currentTime), -sin(ej4::degRot[i].z * currentTime), 0.f, 0.f,
					sin(ej4::degRot[i].z * currentTime), cos(ej4::degRot[i].z * currentTime),  0.f, 0.f,
					0.f, 0.f, 1.f, 0.f,
					0.f, 0.f, 0.f, 1.f };

				glm::mat4 finalRot = rotationX * rotationY*rotationZ;



				glUniform3fv(glGetUniformLocation(myRenderProgram[1], "pos"), 1, (GLfloat*)&ej4::seeds[i]);
				glUniform1f(glGetUniformLocation(myRenderProgram[1], "mySize"), (GLfloat)mySize);
				glUniform1i(glGetUniformLocation(myRenderProgram[1], "Ejercicio5"), (GLboolean)ej5::Ejercicio5);
				glUniform1i(glGetUniformLocation(myRenderProgram[1], "Ejercicio9"), (GLboolean)ej9::Ejercicio9);
				glUniform1i(glGetUniformLocation(myRenderProgram[1], "samePos"), (GLboolean)ej6b::samePos[i]);
				glUniform1f(glGetUniformLocation(myRenderProgram[1], "time"), (GLfloat)currentTime);
				glUniformMatrix4fv(glGetUniformLocation(myRenderProgram[1], "rotation"), 1, GL_FALSE, glm::value_ptr(finalRot));
				glUniform1f(glGetUniformLocation(myRenderProgram[1], "localRot"), (GLboolean)localRotation);
				glDrawArrays(GL_TRIANGLES, 0, 3);
				ej4::seeds[i] -= glm::vec3(0, 0.005f + ej4::speed*ej4::seedR[i], 0);

				for (int j = 0; j < ej6b::HoneyComb;++j) {
					if ((ej4::seeds[i].y <= ej6b::pos[j].y + 0.2 && ej4::seeds[i].y >= ej6b::pos[j].y - 0.2) && (ej4::seeds[i].x <= ej6b::pos[j].x + 0.2 && ej4::seeds[i].x >= ej6b::pos[j].x - 0.2)) {
						ej6b::samePos[i] = true;
					}
				}
			}

			bool localRotation2 = true;
			glUseProgram(myRenderProgram[3]);
			float mySize2 = 75.f;
			

			for (int i = 0; i < ej6b::HoneyComb; ++i) {
				glUniform3fv(glGetUniformLocation(myRenderProgram[3], "pos"), 1, (GLfloat*)&ej6b::pos[i]);
				glUniform1f(glGetUniformLocation(myRenderProgram[3], "mySize"), (GLfloat)mySize2);
				glUniform1f(glGetUniformLocation(myRenderProgram[3], "time"), (GLfloat)currentTime);
				glUniformMatrix4fv(glGetUniformLocation(myRenderProgram[3], "rotation"), 1, GL_FALSE, glm::value_ptr(RV::_MVP));
				glUniform1f(glGetUniformLocation(myRenderProgram[3], "localRot"), (GLboolean)localRotation2);
				glDrawArrays(GL_LINES, 0, 3);
			}
		}
		else if (keyboardState[SDL_SCANCODE_9]) {
			RV::_projection = glm::perspective(RV::FOV, RV::width / RV::height, RV::zNear, RV::zFar);

			bool localRotation = true;
			ej5::Ejercicio5 = false;
			ej9::Ejercicio9 = true;
			glUseProgram(myRenderProgram[1]);

			glm::mat4 scale{ 5.f, 0.f, 0.f, 0.f,
				0.f, 5.f, 0.f, 0.f,
				0.f, 0.f, 5.f, 0.f,
				0.f, 0.f, 0.f, 1.f };

			float mySize = 1;

			for (int i = 0; i < ej9::octoAmount; ++i) {
				glUniform3fv(glGetUniformLocation(myRenderProgram[1], "pos"), 1, (GLfloat*)&ej9::pos[i]);
				glUniform1f(glGetUniformLocation(myRenderProgram[1], "mySize"), (GLfloat)mySize);
				glUniform1i(glGetUniformLocation(myRenderProgram[1], "Ejercicio5"), (GLboolean)ej5::Ejercicio5);
				glUniform1i(glGetUniformLocation(myRenderProgram[1], "Ejercicio9"), (GLboolean)ej9::Ejercicio9);
				glUniform1f(glGetUniformLocation(myRenderProgram[1], "time"), (GLfloat)fmod(currentTime, 1) / 1);
				glUniformMatrix4fv(glGetUniformLocation(myRenderProgram[1], "rotation"), 1, GL_FALSE, glm::value_ptr(RV::_MVP));
				glUniformMatrix4fv(glGetUniformLocation(myRenderProgram[1], "scale"), 1, GL_FALSE, glm::value_ptr(scale));
				glUniform1f(glGetUniformLocation(myRenderProgram[1], "localRot"), (GLboolean)localRotation);
				glDrawArrays(GL_TRIANGLES, 0, 3);
			}
		}
		else {
			ej1::pos1 = glm::vec3(getRandomFloatBetween(-5, 5), getRandomFloatBetween(0, 10), getRandomFloatBetween(-5, 0));
			ej1::pos2 = glm::vec3(getRandomFloatBetween(-5, 5), getRandomFloatBetween(0, 10), getRandomFloatBetween(-5, 0));

			ej3::seed1 = glm::vec3(1, 0, 0);
			ej3::seed2 = glm::vec3(-1, 1.4, 0);

			for (int i = 0; i < ej4::octoAmount; ++i) {
				ej4::seeds[i] = glm::vec3{ -2 + i * 4.1 / static_cast<float>(ej4::octoAmount), 2, 0 };
				ej4::seedR[i] = 0.95*(rand() % 2 + (rand() % 10) / 10.f);
				ej4::degRot[i] = glm::vec3(getRandomFloatBetween(1, 4), 0, getRandomFloatBetween(1, 4));
			}
			for (int i = 0; i < ej5::octoAmount; ++i) {
				ej5::seeds[i] = glm::vec3{ -2 + i * 4.1 / static_cast<float>(ej5::octoAmount), 2, 0 };
				ej5::seedR[i] = 0.95*(rand() % 2 + (rand() % 10) / 10.f);
				ej5::degRot[i] = glm::vec3(getRandomFloatBetween(1, 4), 0, getRandomFloatBetween(1, 4));
			}
			for (int i = 0; i < ej4::octoAmount; ++i) {
				ej6b::samePos[i] = false;
			}
		}

		ej4::lastTime = currentTime;
	}

}




////////////////////////////////////////////////// BOX
namespace Box {
	GLuint cubeVao;
	GLuint cubeVbo[2];
	GLuint cubeShaders[2];
	GLuint cubeProgram;

	float cubeVerts[] = {
		// -5,0,-5 -- 5, 10, 5
		-5.f,  0.f, -5.f,
		5.f,  0.f, -5.f,
		5.f,  0.f,  5.f,
		-5.f,  0.f,  5.f,
		-5.f, 10.f, -5.f,
		5.f, 10.f, -5.f,
		5.f, 10.f,  5.f,
		-5.f, 10.f,  5.f,
	};
	GLubyte cubeIdx[] = {
		1, 0, 2, 3, // Floor - TriangleStrip
		0, 1, 5, 4, // Wall - Lines
		1, 2, 6, 5, // Wall - Lines
		2, 3, 7, 6, // Wall - Lines
		3, 0, 4, 7  // Wall - Lines
	};

	const char* vertShader_xform =
		"#version 330\n\
in vec3 in_Position;\n\
uniform mat4 mvpMat;\n\
void main() {\n\
	gl_Position = mvpMat * vec4(in_Position, 1.0);\n\
}";
	const char* fragShader_flatColor =
		"#version 330\n\
out vec4 out_Color;\n\
uniform vec4 color;\n\
void main() {\n\
	out_Color = color;\n\
}";

	void setupCube() {
		glGenVertexArrays(1, &cubeVao);
		glBindVertexArray(cubeVao);
		glGenBuffers(2, cubeVbo);

		glBindBuffer(GL_ARRAY_BUFFER, cubeVbo[0]);
		glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 24, cubeVerts, GL_STATIC_DRAW);
		glVertexAttribPointer((GLuint)0, 3, GL_FLOAT, GL_FALSE, 0, 0);
		glEnableVertexAttribArray(0);

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, cubeVbo[1]);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLubyte) * 20, cubeIdx, GL_STATIC_DRAW);

		glBindVertexArray(0);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

		cubeShaders[0] = compileShader(vertShader_xform, GL_VERTEX_SHADER, "cubeVert");
		cubeShaders[1] = compileShader(fragShader_flatColor, GL_FRAGMENT_SHADER, "cubeFrag");

		cubeProgram = glCreateProgram();
		glAttachShader(cubeProgram, cubeShaders[0]);
		glAttachShader(cubeProgram, cubeShaders[1]);
		glBindAttribLocation(cubeProgram, 0, "in_Position");
		linkProgram(cubeProgram);
	}
	void cleanupCube() {
		glDeleteBuffers(2, cubeVbo);
		glDeleteVertexArrays(1, &cubeVao);

		glDeleteProgram(cubeProgram);
		glDeleteShader(cubeShaders[0]);
		glDeleteShader(cubeShaders[1]);
	}
	void drawCube() {
		glBindVertexArray(cubeVao);
		glUseProgram(cubeProgram);
		glUniformMatrix4fv(glGetUniformLocation(cubeProgram, "mvpMat"), 1, GL_FALSE, glm::value_ptr(RV::_MVP));
		// FLOOR
		glUniform4f(glGetUniformLocation(cubeProgram, "color"), 0.6f, 0.6f, 0.6f, 1.f);
		glDrawElements(GL_TRIANGLE_STRIP, 4, GL_UNSIGNED_BYTE, 0);
		// WALLS
		glUniform4f(glGetUniformLocation(cubeProgram, "color"), 0.f, 0.f, 0.f, 1.f);
		glDrawElements(GL_LINE_LOOP, 4, GL_UNSIGNED_BYTE, (void*)(sizeof(GLubyte) * 4));
		glDrawElements(GL_LINE_LOOP, 4, GL_UNSIGNED_BYTE, (void*)(sizeof(GLubyte) * 8));
		glDrawElements(GL_LINE_LOOP, 4, GL_UNSIGNED_BYTE, (void*)(sizeof(GLubyte) * 12));
		glDrawElements(GL_LINE_LOOP, 4, GL_UNSIGNED_BYTE, (void*)(sizeof(GLubyte) * 16));

		glUseProgram(0);
		glBindVertexArray(0);
	}
}

////////////////////////////////////////////////// AXIS
namespace Axis {
	GLuint AxisVao;
	GLuint AxisVbo[3];
	GLuint AxisShader[2];
	GLuint AxisProgram;

	float AxisVerts[] = {
		0.0, 0.0, 0.0,
		1.0, 0.0, 0.0,
		0.0, 0.0, 0.0,
		0.0, 1.0, 0.0,
		0.0, 0.0, 0.0,
		0.0, 0.0, 1.0
	};
	float AxisColors[] = {
		1.0, 0.0, 0.0, 1.0,
		1.0, 0.0, 0.0, 1.0,
		0.0, 1.0, 0.0, 1.0,
		0.0, 1.0, 0.0, 1.0,
		0.0, 0.0, 1.0, 1.0,
		0.0, 0.0, 1.0, 1.0
	};
	GLubyte AxisIdx[] = {
		0, 1,
		2, 3,
		4, 5
	};
	const char* Axis_vertShader =
		"#version 330\n\
in vec3 in_Position;\n\
in vec4 in_Color;\n\
out vec4 vert_color;\n\
uniform mat4 mvpMat;\n\
void main() {\n\
	vert_color = in_Color;\n\
	gl_Position = mvpMat * vec4(in_Position, 1.0);\n\
}";
	const char* Axis_fragShader =
		"#version 330\n\
in vec4 vert_color;\n\
out vec4 out_Color;\n\
void main() {\n\
	out_Color = vert_color;\n\
}";

	void setupAxis() {
		glGenVertexArrays(1, &AxisVao);
		glBindVertexArray(AxisVao);
		glGenBuffers(3, AxisVbo);

		glBindBuffer(GL_ARRAY_BUFFER, AxisVbo[0]);
		glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 24, AxisVerts, GL_STATIC_DRAW);
		glVertexAttribPointer((GLuint)0, 3, GL_FLOAT, GL_FALSE, 0, 0);
		glEnableVertexAttribArray(0);

		glBindBuffer(GL_ARRAY_BUFFER, AxisVbo[1]);
		glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 24, AxisColors, GL_STATIC_DRAW);
		glVertexAttribPointer((GLuint)1, 4, GL_FLOAT, false, 0, 0);
		glEnableVertexAttribArray(1);

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, AxisVbo[2]);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLubyte) * 6, AxisIdx, GL_STATIC_DRAW);

		glBindVertexArray(0);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

		AxisShader[0] = compileShader(Axis_vertShader, GL_VERTEX_SHADER, "AxisVert");
		AxisShader[1] = compileShader(Axis_fragShader, GL_FRAGMENT_SHADER, "AxisFrag");

		AxisProgram = glCreateProgram();
		glAttachShader(AxisProgram, AxisShader[0]);
		glAttachShader(AxisProgram, AxisShader[1]);
		glBindAttribLocation(AxisProgram, 0, "in_Position");
		glBindAttribLocation(AxisProgram, 1, "in_Color");
		linkProgram(AxisProgram);
	}
	void cleanupAxis() {
		glDeleteBuffers(3, AxisVbo);
		glDeleteVertexArrays(1, &AxisVao);

		glDeleteProgram(AxisProgram);
		glDeleteShader(AxisShader[0]);
		glDeleteShader(AxisShader[1]);
	}
	void drawAxis() {
		glBindVertexArray(AxisVao);
		glUseProgram(AxisProgram);
		glUniformMatrix4fv(glGetUniformLocation(AxisProgram, "mvpMat"), 1, GL_FALSE, glm::value_ptr(RV::_MVP));
		glDrawElements(GL_LINES, 6, GL_UNSIGNED_BYTE, 0);

		glUseProgram(0);
		glBindVertexArray(0);
	}
}

////////////////////////////////////////////////// SPHERE
namespace Sphere {
	GLuint sphereVao;
	GLuint sphereVbo;
	GLuint sphereShaders[3];
	GLuint sphereProgram;
	float radius;

	const char* sphere_vertShader =
		"#version 330\n\
in vec3 in_Position;\n\
uniform mat4 mv_Mat;\n\
void main() {\n\
	gl_Position = mv_Mat * vec4(in_Position, 1.0);\n\
}";
	const char* sphere_geomShader =
		"#version 330\n\
layout(points) in;\n\
layout(triangle_strip, max_vertices = 4) out;\n\
out vec4 eyePos;\n\
out vec4 centerEyePos;\n\
uniform mat4 projMat;\n\
uniform float radius;\n\
vec4 nu_verts[4];\n\
void main() {\n\
	vec3 n = normalize(-gl_in[0].gl_Position.xyz);\n\
	vec3 up = vec3(0.0, 1.0, 0.0);\n\
	vec3 u = normalize(cross(up, n));\n\
	vec3 v = normalize(cross(n, u));\n\
	nu_verts[0] = vec4(-radius*u - radius*v, 0.0); \n\
	nu_verts[1] = vec4( radius*u - radius*v, 0.0); \n\
	nu_verts[2] = vec4(-radius*u + radius*v, 0.0); \n\
	nu_verts[3] = vec4( radius*u + radius*v, 0.0); \n\
	centerEyePos = gl_in[0].gl_Position;\n\
	for (int i = 0; i < 4; ++i) {\n\
		eyePos = (gl_in[0].gl_Position + nu_verts[i]);\n\
		gl_Position = projMat * eyePos;\n\
		EmitVertex();\n\
	}\n\
	EndPrimitive();\n\
}";
	const char* sphere_fragShader_flatColor =
		"#version 330\n\
in vec4 eyePos;\n\
in vec4 centerEyePos;\n\
out vec4 out_Color;\n\
uniform mat4 projMat;\n\
uniform mat4 mv_Mat;\n\
uniform vec4 color;\n\
uniform float radius;\n\
void main() {\n\
	vec4 diff = eyePos - centerEyePos;\n\
	float distSq2C = dot(diff, diff);\n\
	if (distSq2C > (radius*radius)) discard;\n\
	float h = sqrt(radius*radius - distSq2C);\n\
	vec4 nuEyePos = vec4(eyePos.xy, eyePos.z + h, 1.0);\n\
	vec4 nuPos = projMat * nuEyePos;\n\
	gl_FragDepth = ((nuPos.z / nuPos.w) + 1) * 0.5;\n\
	vec3 normal = normalize(nuEyePos - centerEyePos).xyz;\n\
	out_Color = vec4(color.xyz * dot(normal, (mv_Mat*vec4(0.0, 1.0, 0.0, 0.0)).xyz) + color.xyz * 0.3, 1.0 );\n\
}";

	bool shadersCreated = false;
	void createSphereShaderAndProgram() {
		if (shadersCreated) return;

		sphereShaders[0] = compileShader(sphere_vertShader, GL_VERTEX_SHADER, "sphereVert");
		sphereShaders[1] = compileShader(sphere_geomShader, GL_GEOMETRY_SHADER, "sphereGeom");
		sphereShaders[2] = compileShader(sphere_fragShader_flatColor, GL_FRAGMENT_SHADER, "sphereFrag");

		sphereProgram = glCreateProgram();
		glAttachShader(sphereProgram, sphereShaders[0]);
		glAttachShader(sphereProgram, sphereShaders[1]);
		glAttachShader(sphereProgram, sphereShaders[2]);
		glBindAttribLocation(sphereProgram, 0, "in_Position");
		linkProgram(sphereProgram);

		shadersCreated = true;
	}
	void cleanupSphereShaderAndProgram() {
		if (!shadersCreated) return;
		glDeleteProgram(sphereProgram);
		glDeleteShader(sphereShaders[0]);
		glDeleteShader(sphereShaders[1]);
		glDeleteShader(sphereShaders[2]);
		shadersCreated = false;
	}

	void setupSphere(glm::vec3 pos, float radius) {
		Sphere::radius = radius;
		glGenVertexArrays(1, &sphereVao);
		glBindVertexArray(sphereVao);
		glGenBuffers(1, &sphereVbo);

		glBindBuffer(GL_ARRAY_BUFFER, sphereVbo);
		glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 3, &pos, GL_DYNAMIC_DRAW);
		glVertexAttribPointer((GLuint)0, 3, GL_FLOAT, GL_FALSE, 0, 0);
		glEnableVertexAttribArray(0);

		glBindVertexArray(0);
		glBindBuffer(GL_ARRAY_BUFFER, 0);

		createSphereShaderAndProgram();
	}
	void cleanupSphere() {
		glDeleteBuffers(1, &sphereVbo);
		glDeleteVertexArrays(1, &sphereVao);

		cleanupSphereShaderAndProgram();
	}
	void updateSphere(glm::vec3 pos, float radius) {
		glBindBuffer(GL_ARRAY_BUFFER, sphereVbo);
		float* buff = (float*)glMapBuffer(GL_ARRAY_BUFFER, GL_WRITE_ONLY);
		buff[0] = pos.x;
		buff[1] = pos.y;
		buff[2] = pos.z;
		glUnmapBuffer(GL_ARRAY_BUFFER);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
		Sphere::radius = radius;
	}
	void drawSphere() {
		glBindVertexArray(sphereVao);
		glUseProgram(sphereProgram);
		glUniformMatrix4fv(glGetUniformLocation(sphereProgram, "mvpMat"), 1, GL_FALSE, glm::value_ptr(RV::_MVP));
		glUniformMatrix4fv(glGetUniformLocation(sphereProgram, "mv_Mat"), 1, GL_FALSE, glm::value_ptr(RV::_modelView));
		glUniformMatrix4fv(glGetUniformLocation(sphereProgram, "projMat"), 1, GL_FALSE, glm::value_ptr(RV::_projection));
		glUniform4f(glGetUniformLocation(sphereProgram, "color"), 0.6f, 0.1f, 0.1f, 1.f);
		glUniform1f(glGetUniformLocation(sphereProgram, "radius"), Sphere::radius);
		glDrawArrays(GL_POINTS, 0, 1);

		glUseProgram(0);
		glBindVertexArray(0);
	}
}

////////////////////////////////////////////////// CAPSULE
namespace Capsule {
	GLuint capsuleVao;
	GLuint capsuleVbo[2];
	GLuint capsuleShader[3];
	GLuint capsuleProgram;
	float radius;

	const char* capsule_vertShader =
		"#version 330\n\
in vec3 in_Position;\n\
uniform mat4 mv_Mat;\n\
void main() {\n\
	gl_Position = mv_Mat * vec4(in_Position, 1.0);\n\
}";
	const char* capsule_geomShader =
		"#version 330\n\
layout(lines) in; \n\
layout(triangle_strip, max_vertices = 14) out;\n\
out vec3 eyePos;\n\
out vec3 capPoints[2];\n\
uniform mat4 projMat;\n\
uniform float radius;\n\
vec3 boxVerts[8];\n\
int boxIdx[14];\n\
void main(){\n\
	vec3 A = gl_in[0].gl_Position.xyz;\n\
	vec3 B = gl_in[1].gl_Position.xyz;\n\
	if(gl_in[1].gl_Position.x < gl_in[0].gl_Position.x) {\n\
		A = gl_in[1].gl_Position.xyz;\n\
		B = gl_in[0].gl_Position.xyz;\n\
	}\n\
	vec3 u = vec3(0.0, 1.0, 0.0);\n\
	if (abs(dot(u, normalize(gl_in[1].gl_Position.xyz - gl_in[0].gl_Position.xyz))) - 1.0 < 1e-6) {\n\
		if(gl_in[1].gl_Position.y > gl_in[0].gl_Position.y) {\n\
			A = gl_in[1].gl_Position.xyz;\n\
			B = gl_in[0].gl_Position.xyz;\n\
		}\n\
		u = vec3(1.0, 0.0, 0.0);\n\
	}\n\
	vec3 Am = normalize(A - B); \n\
	vec3 Bp = -Am;\n\
	vec3 v = normalize(cross(Am, u)) * radius;\n\
	u = normalize(cross(v, Am)) * radius;\n\
	Am *= radius;\n\
	Bp *= radius;\n\
	boxVerts[0] = A + Am - u - v;\n\
	boxVerts[1] = A + Am + u - v;\n\
	boxVerts[2] = A + Am + u + v;\n\
	boxVerts[3] = A + Am - u + v;\n\
	boxVerts[4] = B + Bp - u - v;\n\
	boxVerts[5] = B + Bp + u - v;\n\
	boxVerts[6] = B + Bp + u + v;\n\
	boxVerts[7] = B + Bp - u + v;\n\
	boxIdx = int[](0, 3, 4, 7, 6, 3, 2, 1, 6, 5, 4, 1, 0, 3);\n\
	capPoints[0] = A;\n\
	capPoints[1] = B;\n\
	for (int i = 0; i<14; ++i) {\n\
		eyePos = boxVerts[boxIdx[i]];\n\
		gl_Position = projMat * vec4(boxVerts[boxIdx[i]], 1.0);\n\
		EmitVertex();\n\
	}\n\
	EndPrimitive();\n\
}";
	const char* capsule_fragShader_flatColor =
		"#version 330\n\
in vec3 eyePos;\n\
in vec3 capPoints[2];\n\
out vec4 out_Color;\n\
uniform mat4 projMat;\n\
uniform mat4 mv_Mat;\n\
uniform vec4 color;\n\
uniform float radius;\n\
const int lin_steps = 30;\n\
const int bin_steps = 5;\n\
vec3 closestPointInSegment(vec3 p, vec3 a, vec3 b) {\n\
	vec3 pa = p - a, ba = b - a;\n\
	float h = clamp(dot(pa, ba) / dot(ba, ba), 0.0, 1.0);\n\
	return a + ba*h;\n\
}\n\
void main() {\n\
	vec3 viewDir = normalize(eyePos);\n\
	float step = radius / 5.0;\n\
	vec3 nuPB = eyePos;\n\
	int i = 0;\n\
	for(i = 0; i < lin_steps; ++i) {\n\
		nuPB = eyePos + viewDir*step*i;\n\
		vec3 C = closestPointInSegment(nuPB, capPoints[0], capPoints[1]);\n\
		float dist = length(C - nuPB) - radius;\n\
		if(dist < 0.0) break;\n\
	}\n\
	if(i==lin_steps) discard;\n\
	vec3 nuPA = nuPB - viewDir*step;\n\
	vec3 C;\n\
	for(i = 0; i < bin_steps; ++i) {\n\
		vec3 nuPC = nuPA + (nuPB - nuPA)*0.5; \n\
		C = closestPointInSegment(nuPC, capPoints[0], capPoints[1]); \n\
		float dist = length(C - nuPC) - radius; \n\
		if(dist > 0.0) nuPA = nuPC; \n\
		else nuPB = nuPC; \n\
	}\n\
	vec4 nuPos = projMat * vec4(nuPA, 1.0);\n\
	gl_FragDepth = ((nuPos.z / nuPos.w) + 1) * 0.5;\n\
	vec3 normal = normalize(nuPA - C);\n\
	out_Color = vec4(color.xyz * dot(normal, (mv_Mat*vec4(0.0, 1.0, 0.0, 0.0)).xyz) + color.xyz * 0.3, 1.0 );\n\
}";

	void setupCapsule(glm::vec3 posA, glm::vec3 posB, float radius) {
		Capsule::radius = radius;
		glGenVertexArrays(1, &capsuleVao);
		glBindVertexArray(capsuleVao);
		glGenBuffers(2, capsuleVbo);

		float capsuleVerts[] = {
			posA.x, posA.y, posA.z,
			posB.x, posB.y, posB.z
		};
		GLubyte capsuleIdx[] = {
			0, 1
		};

		glBindBuffer(GL_ARRAY_BUFFER, capsuleVbo[0]);
		glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 6, capsuleVerts, GL_DYNAMIC_DRAW);
		glVertexAttribPointer((GLuint)0, 3, GL_FLOAT, GL_FALSE, 0, 0);
		glEnableVertexAttribArray(0);

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, capsuleVbo[1]);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLubyte) * 2, capsuleIdx, GL_STATIC_DRAW);

		glBindVertexArray(0);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

		capsuleShader[0] = compileShader(capsule_vertShader, GL_VERTEX_SHADER, "capsuleVert");
		capsuleShader[1] = compileShader(capsule_geomShader, GL_GEOMETRY_SHADER, "capsuleGeom");
		capsuleShader[2] = compileShader(capsule_fragShader_flatColor, GL_FRAGMENT_SHADER, "capsuleFrag");

		capsuleProgram = glCreateProgram();
		glAttachShader(capsuleProgram, capsuleShader[0]);
		glAttachShader(capsuleProgram, capsuleShader[1]);
		glAttachShader(capsuleProgram, capsuleShader[2]);
		glBindAttribLocation(capsuleProgram, 0, "in_Position");
		linkProgram(capsuleProgram);
	}
	void cleanupCapsule() {
		glDeleteBuffers(2, capsuleVbo);
		glDeleteVertexArrays(1, &capsuleVao);

		glDeleteProgram(capsuleProgram);
		glDeleteShader(capsuleShader[0]);
		glDeleteShader(capsuleShader[1]);
		glDeleteShader(capsuleShader[2]);
	}
	void updateCapsule(glm::vec3 posA, glm::vec3 posB, float radius) {
		float vertPos[] = { posA.x, posA.y, posA.z, posB.z, posB.y, posB.z };
		glBindBuffer(GL_ARRAY_BUFFER, capsuleVbo[0]);
		float* buff = (float*)glMapBuffer(GL_ARRAY_BUFFER, GL_WRITE_ONLY);
		buff[0] = posA.x; buff[1] = posA.y; buff[2] = posA.z;
		buff[3] = posB.x; buff[4] = posB.y; buff[5] = posB.z;
		glUnmapBuffer(GL_ARRAY_BUFFER);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
		Capsule::radius = radius;
	}
	void drawCapsule() {
		glBindVertexArray(capsuleVao);
		glUseProgram(capsuleProgram);
		glUniformMatrix4fv(glGetUniformLocation(capsuleProgram, "mvpMat"), 1, GL_FALSE, glm::value_ptr(RV::_MVP));
		glUniformMatrix4fv(glGetUniformLocation(capsuleProgram, "mv_Mat"), 1, GL_FALSE, glm::value_ptr(RV::_modelView));
		glUniformMatrix4fv(glGetUniformLocation(capsuleProgram, "projMat"), 1, GL_FALSE, glm::value_ptr(RV::_projection));
		glUniform4fv(glGetUniformLocation(capsuleProgram, "camPoint"), 1, &RV::_cameraPoint[0]);
		glUniform4f(glGetUniformLocation(capsuleProgram, "color"), 0.1f, 0.6f, 0.1f, 1.f);
		glUniform1f(glGetUniformLocation(capsuleProgram, "radius"), Capsule::radius);
		glDrawElements(GL_LINES, 2, GL_UNSIGNED_BYTE, 0);

		glUseProgram(0);
		glBindVertexArray(0);
	}
}

////////////////////////////////////////////////// PARTICLES
// Same rendering as Sphere (reusing shaders)
namespace LilSpheres {
	GLuint particlesVao;
	GLuint particlesVbo;
	float radius;
	int numparticles;
	extern const int maxParticles = SHRT_MAX;

	void setupParticles(int numTotalParticles, float radius) {
		assert(numTotalParticles > 0);
		assert(numTotalParticles <= SHRT_MAX);
		numparticles = numTotalParticles;
		LilSpheres::radius = radius;

		glGenVertexArrays(1, &particlesVao);
		glBindVertexArray(particlesVao);
		glGenBuffers(1, &particlesVbo);

		glBindBuffer(GL_ARRAY_BUFFER, particlesVbo);
		glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 3 * numparticles, 0, GL_DYNAMIC_DRAW);
		glVertexAttribPointer((GLuint)0, 3, GL_FLOAT, GL_FALSE, 0, 0);
		glEnableVertexAttribArray(0);

		glBindVertexArray(0);
		glBindBuffer(GL_ARRAY_BUFFER, 0);

		Sphere::createSphereShaderAndProgram();
	}
	void cleanupParticles() {
		glDeleteVertexArrays(1, &particlesVao);
		glDeleteBuffers(1, &particlesVbo);

		Sphere::cleanupSphereShaderAndProgram();
	}
	void updateParticles(int startIdx, int count, float* array_data) {
		glBindBuffer(GL_ARRAY_BUFFER, particlesVbo);
		float* buff = (float*)glMapBuffer(GL_ARRAY_BUFFER, GL_WRITE_ONLY);
		buff = &buff[3 * startIdx];
		for (int i = 0; i < 3 * count; ++i) {
			buff[i] = array_data[i];
		}
		glUnmapBuffer(GL_ARRAY_BUFFER);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}
	void drawParticles(int startIdx, int count) {
		glBindVertexArray(particlesVao);
		glUseProgram(Sphere::sphereProgram);
		glUniformMatrix4fv(glGetUniformLocation(Sphere::sphereProgram, "mvpMat"), 1, GL_FALSE, glm::value_ptr(RV::_MVP));
		glUniformMatrix4fv(glGetUniformLocation(Sphere::sphereProgram, "mv_Mat"), 1, GL_FALSE, glm::value_ptr(RV::_modelView));
		glUniformMatrix4fv(glGetUniformLocation(Sphere::sphereProgram, "projMat"), 1, GL_FALSE, glm::value_ptr(RV::_projection));
		glUniform4f(glGetUniformLocation(Sphere::sphereProgram, "color"), 0.1f, 0.1f, 0.6f, 1.f);
		glUniform1f(glGetUniformLocation(Sphere::sphereProgram, "radius"), LilSpheres::radius);
		glDrawArrays(GL_POINTS, startIdx, count);

		glUseProgram(0);
		glBindVertexArray(0);
	}
}

////////////////////////////////////////////////// CLOTH
namespace ClothMesh {
	GLuint clothVao;
	GLuint clothVbo[2];
	GLuint clothShaders[2];
	GLuint clothProgram;
	extern const int numCols = 14;
	extern const int numRows = 18;
	extern const int numVerts = numRows * numCols;
	int numVirtualVerts;

	const char* cloth_vertShader =
		"#version 330\n\
in vec3 in_Position;\n\
uniform mat4 mvpMat;\n\
void main() {\n\
	gl_Position = mvpMat * vec4(in_Position, 1.0);\n\
}";
	const char* cloth_fragShader =
		"#version 330\n\
uniform vec4 color;\n\
out vec4 out_Color;\n\
void main() {\n\
	out_Color = color;\n\
}";

	void setupClothMesh() {
		glGenVertexArrays(1, &clothVao);
		glBindVertexArray(clothVao);
		glGenBuffers(2, clothVbo);

		glBindBuffer(GL_ARRAY_BUFFER, clothVbo[0]);
		glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 3 * numVerts, 0, GL_DYNAMIC_DRAW);
		glVertexAttribPointer((GLuint)0, 3, GL_FLOAT, GL_FALSE, 0, 0);
		glEnableVertexAttribArray(0);

		glPrimitiveRestartIndex(UCHAR_MAX);
		constexpr int facesVertsIdx = 5 * (numCols - 1) * (numRows - 1);
		GLubyte facesIdx[facesVertsIdx] = { 0 };
		for (int i = 0; i < (numRows - 1); ++i) {
			for (int j = 0; j < (numCols - 1); ++j) {
				facesIdx[5 * (i*(numCols - 1) + j) + 0] = i * numCols + j;
				facesIdx[5 * (i*(numCols - 1) + j) + 1] = (i + 1)*numCols + j;
				facesIdx[5 * (i*(numCols - 1) + j) + 2] = (i + 1)*numCols + (j + 1);
				facesIdx[5 * (i*(numCols - 1) + j) + 3] = i * numCols + (j + 1);
				facesIdx[5 * (i*(numCols - 1) + j) + 4] = UCHAR_MAX;
			}
		}
		numVirtualVerts = facesVertsIdx;

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, clothVbo[1]);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLubyte)*numVirtualVerts, facesIdx, GL_STATIC_DRAW);

		glBindVertexArray(0);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

		clothShaders[0] = compileShader(cloth_vertShader, GL_VERTEX_SHADER, "clothVert");
		clothShaders[1] = compileShader(cloth_fragShader, GL_FRAGMENT_SHADER, "clothFrag");

		clothProgram = glCreateProgram();
		glAttachShader(clothProgram, clothShaders[0]);
		glAttachShader(clothProgram, clothShaders[1]);
		glBindAttribLocation(clothProgram, 0, "in_Position");
		linkProgram(clothProgram);
	}
	void cleanupClothMesh() {
		glDeleteBuffers(2, clothVbo);
		glDeleteVertexArrays(1, &clothVao);

		glDeleteProgram(clothProgram);
		glDeleteShader(clothShaders[0]);
		glDeleteShader(clothShaders[1]);
	}
	void updateClothMesh(float *array_data) {
		glBindBuffer(GL_ARRAY_BUFFER, clothVbo[0]);
		float* buff = (float*)glMapBuffer(GL_ARRAY_BUFFER, GL_WRITE_ONLY);
		for (int i = 0; i < 3 * numVerts; ++i) {
			buff[i] = array_data[i];
		}
		glUnmapBuffer(GL_ARRAY_BUFFER);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}
	void drawClothMesh() {
		glEnable(GL_PRIMITIVE_RESTART);
		glBindVertexArray(clothVao);
		glUseProgram(clothProgram);
		glUniformMatrix4fv(glGetUniformLocation(clothProgram, "mvpMat"), 1, GL_FALSE, glm::value_ptr(RV::_MVP));
		glUniform4f(glGetUniformLocation(clothProgram, "color"), 0.1f, 1.f, 1.f, 0.f);
		glDrawElements(GL_LINE_LOOP, numVirtualVerts, GL_UNSIGNED_BYTE, 0);

		glUseProgram(0);
		glBindVertexArray(0);
		glDisable(GL_PRIMITIVE_RESTART);
	}
}

////////////////////////////////////////////////// CUBE
namespace Cube {
	GLuint cubeVao;
	GLuint cubeVbo[3];
	GLuint cubeShaders[2];
	GLuint cubeProgram;
	glm::mat4 objMat = glm::mat4(1.f);

	extern const float halfW = 0.5f;
	int numVerts = 24 + 6; // 4 vertex/face * 6 faces + 6 PRIMITIVE RESTART

						   //   4---------7
						   //  /|        /|
						   // / |       / |
						   //5---------6  |
						   //|  0------|--3
						   //| /       | /
						   //|/        |/
						   //1---------2
	glm::vec3 verts[] = {
		glm::vec3(-halfW, -halfW, -halfW),
		glm::vec3(-halfW, -halfW,  halfW),
		glm::vec3(halfW, -halfW,  halfW),
		glm::vec3(halfW, -halfW, -halfW),
		glm::vec3(-halfW,  halfW, -halfW),
		glm::vec3(-halfW,  halfW,  halfW),
		glm::vec3(halfW,  halfW,  halfW),
		glm::vec3(halfW,  halfW, -halfW)
	};
	glm::vec3 norms[] = {
		glm::vec3(0.f, -1.f,  0.f),
		glm::vec3(0.f,  1.f,  0.f),
		glm::vec3(-1.f,  0.f,  0.f),
		glm::vec3(1.f,  0.f,  0.f),
		glm::vec3(0.f,  0.f, -1.f),
		glm::vec3(0.f,  0.f,  1.f)
	};

	glm::vec3 cubeVerts[] = {
		verts[1], verts[0], verts[2], verts[3],
		verts[5], verts[6], verts[4], verts[7],
		verts[1], verts[5], verts[0], verts[4],
		verts[2], verts[3], verts[6], verts[7],
		verts[0], verts[4], verts[3], verts[7],
		verts[1], verts[2], verts[5], verts[6]
	};
	glm::vec3 cubeNorms[] = {
		norms[0], norms[0], norms[0], norms[0],
		norms[1], norms[1], norms[1], norms[1],
		norms[2], norms[2], norms[2], norms[2],
		norms[3], norms[3], norms[3], norms[3],
		norms[4], norms[4], norms[4], norms[4],
		norms[5], norms[5], norms[5], norms[5]
	};
	GLubyte cubeIdx[] = {
		0, 1, 2, 3, UCHAR_MAX,
		4, 5, 6, 7, UCHAR_MAX,
		8, 9, 10, 11, UCHAR_MAX,
		12, 13, 14, 15, UCHAR_MAX,
		16, 17, 18, 19, UCHAR_MAX,
		20, 21, 22, 23, UCHAR_MAX
	};




	const char* cube_vertShader =
		"#version 330\n\
	in vec3 in_Position;\n\
	in vec3 in_Normal;\n\
	out vec4 vert_Normal;\n\
	uniform mat4 objMat;\n\
	uniform mat4 mv_Mat;\n\
	uniform mat4 mvpMat;\n\
	void main() {\n\
		gl_Position = mvpMat * objMat * vec4(in_Position, 1.0);\n\
		vert_Normal = mv_Mat * objMat * vec4(in_Normal, 0.0);\n\
	}";


	const char* cube_fragShader =
		"#version 330\n\
in vec4 vert_Normal;\n\
out vec4 out_Color;\n\
uniform mat4 mv_Mat;\n\
uniform vec4 color;\n\
void main() {\n\
	out_Color = vec4(color.xyz * dot(vert_Normal, mv_Mat*vec4(0.0, 1.0, 0.0, 0.0)) + color.xyz * 0.3, 1.0 );\n\
}";
	void setupCube() {
		glGenVertexArrays(1, &cubeVao);
		glBindVertexArray(cubeVao);
		glGenBuffers(3, cubeVbo);

		glBindBuffer(GL_ARRAY_BUFFER, cubeVbo[0]);
		glBufferData(GL_ARRAY_BUFFER, sizeof(cubeVerts), cubeVerts, GL_STATIC_DRAW);
		glVertexAttribPointer((GLuint)0, 3, GL_FLOAT, GL_FALSE, 0, 0);
		glEnableVertexAttribArray(0);

		glBindBuffer(GL_ARRAY_BUFFER, cubeVbo[1]);
		glBufferData(GL_ARRAY_BUFFER, sizeof(cubeNorms), cubeNorms, GL_STATIC_DRAW);
		glVertexAttribPointer((GLuint)1, 3, GL_FLOAT, GL_FALSE, 0, 0);
		glEnableVertexAttribArray(1);

		glPrimitiveRestartIndex(UCHAR_MAX);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, cubeVbo[2]);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(cubeIdx), cubeIdx, GL_STATIC_DRAW);

		glBindVertexArray(0);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

		cubeShaders[0] = compileShader(cube_vertShader, GL_VERTEX_SHADER, "cubeVert");
		cubeShaders[1] = compileShader(cube_fragShader, GL_FRAGMENT_SHADER, "cubeFrag");

		cubeProgram = glCreateProgram();
		glAttachShader(cubeProgram, cubeShaders[0]);
		glAttachShader(cubeProgram, cubeShaders[1]);
		glBindAttribLocation(cubeProgram, 0, "in_Position");
		glBindAttribLocation(cubeProgram, 1, "in_Normal");
		linkProgram(cubeProgram);
	}
	void cleanupCube() {
		glDeleteBuffers(3, cubeVbo);
		glDeleteVertexArrays(1, &cubeVao);

		glDeleteProgram(cubeProgram);
		glDeleteShader(cubeShaders[0]);
		glDeleteShader(cubeShaders[1]);
	}
	void updateCube(const glm::mat4& transform) {
		objMat = transform;
	}
	void drawCube() {
		glEnable(GL_PRIMITIVE_RESTART);
		glBindVertexArray(cubeVao);
		glUseProgram(cubeProgram);
		glUniformMatrix4fv(glGetUniformLocation(cubeProgram, "objMat"), 1, GL_FALSE, glm::value_ptr(objMat));
		glUniformMatrix4fv(glGetUniformLocation(cubeProgram, "mv_Mat"), 1, GL_FALSE, glm::value_ptr(RenderVars::_modelView));
		glUniformMatrix4fv(glGetUniformLocation(cubeProgram, "mvpMat"), 1, GL_FALSE, glm::value_ptr(RenderVars::_MVP));
		glUniform4f(glGetUniformLocation(cubeProgram, "color"), 0.1f, 1.f, 1.f, 0.f);
		glDrawElements(GL_TRIANGLE_STRIP, numVerts, GL_UNSIGNED_BYTE, 0);

		glUseProgram(0);
		glBindVertexArray(0);
		glDisable(GL_PRIMITIVE_RESTART);
	}


}
