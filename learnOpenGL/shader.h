#pragma once
#ifndef  SHADER_H
#define SHADER_H

#include <glad/glad.h>

#include <glm/glm/glm.hpp>
#include <glm/glm/gtc/matrix_transform.hpp>
#include <glm/glm/gtc/type_ptr.hpp>
using namespace glm;
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

using namespace std;

class Shader {
public:
	unsigned int ID;	//程序ID

	//Shader(const char* vertexPath, const char* fragmentPath) {
	Shader(const char* vertexPath, const char* fragmentPath){//, const char* geometryPath) {
		// 1. 从文件路径获取shader
		string vertexCode;
		string fragmentCode;
		//string geometryCode;
		ifstream vShaderFile;
		ifstream fShaderFile;
		//ifstream gShaderFile;
		vShaderFile.exceptions(ifstream::failbit | ifstream::badbit);
		fShaderFile.exceptions(ifstream::failbit | ifstream::badbit);
		//gShaderFile.exceptions(ifstream::failbit | ifstream::badbit);
		try {
			// 打开文件
			vShaderFile.open(vertexPath);
			fShaderFile.open(fragmentPath);
			//gShaderFile.open(geometryPath);
			stringstream vShaderStream, fShaderStream, gShaderStream;
			// 读取文件的缓冲内容到数据流
			vShaderStream << vShaderFile.rdbuf();
			fShaderStream << fShaderFile.rdbuf();
			//gShaderStream << gShaderFile.rdbuf();
			vShaderFile.close();
			fShaderFile.close();
			//gShaderFile.close();
			vertexCode = vShaderStream.str();
			fragmentCode = fShaderStream.str();
			//geometryCode = gShaderStream.str();
		}
		catch (ifstream::failure e) {
			cout << "ERROR::SHADER::FILE_NOT_SUCCESFULLY_READ" << endl;
		}
		const char* vShaderCode = vertexCode.c_str();
		const char* fShaderCode = fragmentCode.c_str();
		//const char* gShaderCode = geometryCode.c_str();

		// 2. 编译着色器
		unsigned int vertex, fragment, geometry;
		int success;
		char infoLog[512];

		// 顶点着色器
		vertex = glCreateShader(GL_VERTEX_SHADER);
		glShaderSource(vertex, 1, &vShaderCode, NULL);
		glCompileShader(vertex);

		glGetShaderiv(vertex, GL_COMPILE_STATUS, &success);
		if (!success) {
			glGetShaderInfoLog(vertex, 512, NULL, infoLog);
			cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << endl;
		}

		// 几何着色器
		/*geometry = glCreateShader(GL_GEOMETRY_SHADER);
		glShaderSource(geometry, 1, &gShaderCode, NULL);
		glCompileShader(geometry);

		glGetShaderiv(geometry, GL_COMPILE_STATUS, &success);
		if (!success) {
			glGetShaderInfoLog(geometry, 512, NULL, infoLog);
			cout << "ERROR::SHADER::GEOMETRY::COMPILATION_FAILED\n" << infoLog << endl;
		}*/
		
		// 片段着色器
		fragment = glCreateShader(GL_FRAGMENT_SHADER);
		glShaderSource(fragment, 1, &fShaderCode, NULL);
		glCompileShader(fragment);

		glGetShaderiv(fragment, GL_COMPILE_STATUS, &success);
		if (!success) {
			glGetShaderInfoLog(fragment, 512, NULL, infoLog);
			cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << endl;
		}

		// 着色器程序
		ID = glCreateProgram();
		glAttachShader(ID, vertex);
		//glAttachShader(ID, geometry);
		glAttachShader(ID, fragment);
		glLinkProgram(ID);

		glGetProgramiv(ID, GL_LINK_STATUS, &success);
		if (!success) {
			glGetProgramInfoLog(ID, 512, NULL, infoLog);
			cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << endl;
		}

		// 删除shader
		glDeleteShader(vertex);
		glDeleteShader(fragment);
		//glDeleteShader(geometry);
	}

	void use() {
		glUseProgram(ID);
	}

	void setBool(const string& name, bool value) const {
		glUniform1i(glGetUniformLocation(ID, name.c_str()), (int)value);
	}

	void setInt(const string& name, int value) const {
		glUniform1i(glGetUniformLocation(ID, name.c_str()), value);
	}

	void setFloat(const string& name, float value) const {
		glUniform1f(glGetUniformLocation(ID, name.c_str()), value);
	}

	void setVec3(const string& name, vec3& vec) const
	{
		glUniform3fv(glGetUniformLocation(ID, name.c_str()), 1, &vec[0]);
	}

	void setVec3(const std::string& name, float x, float y, float z) const
	{
		glUniform3f(glGetUniformLocation(ID, name.c_str()), x, y, z);
	}

	void setVec2(const std::string& name, const vec2& value) const
	{
		glUniform2fv(glGetUniformLocation(ID, name.c_str()), 1, &value[0]);
	}
	void setVec2(const std::string& name, float x, float y) const
	{
		glUniform2f(glGetUniformLocation(ID, name.c_str()), x, y);
	}

	void setMat4(const std::string& name, const glm::mat4& mat) const
	{
		glUniformMatrix4fv(glGetUniformLocation(ID, name.c_str()), 1, GL_FALSE, &mat[0][0]);
	}
};

#endif // ! SHADER_H
