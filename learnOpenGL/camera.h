#ifndef Camera_H
#define Camera_H

#include <glad/glad.h>
#include <glm/glm/glm.hpp>
#include <glm/glm/gtc/matrix_transform.hpp>
#include <iostream>
#include<vector>
using namespace std;
using namespace glm;

enum Camera_Movement {
	FORWARD,
	BACKWARD,
	LEFT,
	RIGHT,
	UP,
	BOTTOM
};

const float YAW = -90;
const float PITCH = 0.0f;
const float SPEED = 2.5f;
const float SENSITIVITY = 0.1f;
const float ZOOM = 45.0f;

class Camera {
public:
	// 摄像机属性
	vec3 Position;
	vec3 Front;
	vec3 Up;
	vec3 Right;
	vec3 WorldUp;

	// 角度
	float Yaw;
	float Pitch;

	// 摄像机参数
	float MovementSpeed;
	float MouseSensitivity;
	float Zoom;

	// 构造函数
	Camera(vec3 position = vec3(0.0f, 0.0f, 0.0f), vec3 up = vec3(0.0f, 1.0f, 0.0f), float yaw = YAW, float pitch = PITCH) : Front(vec3(0.0f, 0.0f, -1.0f)), MovementSpeed(SPEED), MouseSensitivity(SENSITIVITY), Zoom(ZOOM) {
		Position = position;
		WorldUp = up;
		Yaw = yaw;
		Pitch = pitch;
		updateCameraVectors();
	}

	Camera(float posX, float posY, float posZ, float upX, float upY, float upZ, float yaw, float pitch) : Front(vec3(0.0f, 0.0f, -1.0f)), MovementSpeed(SPEED), MouseSensitivity(SENSITIVITY), Zoom(ZOOM) {
		Position = vec3(posX, posY, posZ);
		WorldUp = vec3(upX, upY, upZ);
		Yaw = yaw;
		Pitch = pitch;
		updateCameraVectors();
	}

	mat4 GetViewMatrix() {
		//return lookAt(Position, Position + Front, Up);
		return calculate_lookAt_matrix(Position, Position + Front, WorldUp);
	}

	mat4 calculate_lookAt_matrix(vec3 position, vec3 target, vec3 worldUp) {
		vec3 zaxis = normalize(position - target); // cameradirection
		vec3 xaxis = normalize(cross(normalize(worldUp), zaxis)); // cameraright
		vec3 yaxis = cross(zaxis , xaxis); // cameraup

		mat4 translation;
		translation[3][0] = -position.x;
		translation[3][1] = -position.y;
		translation[3][2] = -position.z;

		mat4 rotation;
		rotation[0][0] = xaxis.x;
		rotation[1][0] = xaxis.y;
		rotation[2][0] = xaxis.z;
		rotation[0][1] = yaxis.x;
		rotation[1][1] = yaxis.y;
		rotation[2][1] = yaxis.z;
		rotation[0][2] = zaxis.x;
		rotation[1][2] = zaxis.y;
		rotation[2][2] = zaxis.z;

		return rotation * translation;
	}

	void ProcessKeyboard(Camera_Movement direction, float deltaTime) {
		float velocity = MovementSpeed * deltaTime;
		if (direction == FORWARD) {
			Position += Front * velocity;
		}
		if (direction == BACKWARD) {
			Position -= Front * velocity;
		}
		if (direction == LEFT) {
			Position -= Right * velocity;
		}
		if (direction == RIGHT) {
			Position += Right * velocity;
		}
		if (direction == UP) {
			Position += Up * velocity;
		}
		if (direction == BOTTOM) {
			Position -= Up * velocity;
		}
	}

	void ProcessMouseMovement(float xoffset, float yoffset, GLboolean constrainPitch = true) {
		xoffset *= MouseSensitivity;
		yoffset *= MouseSensitivity;

		Yaw += xoffset;
		Pitch += yoffset;

		if (constrainPitch) {
			if (Pitch > 89.0f)
				Pitch = 89.0f;
			if (Pitch < -89.0f)
				Pitch = -89.0f;
		}

		updateCameraVectors();
	}

	void ProcessMouseScroll(float yoffset) {
		if (Zoom >= 1.0f && Zoom <= 45.0f)
			Zoom -= yoffset;
		if (Zoom <= 1.0f)
			Zoom = 1.0f;
		if (Zoom >= 45.0f)
			Zoom = 45.0f;
	}

private:
	void updateCameraVectors() {
		vec3 front;
		front.x = cos(radians(Yaw) * cos(radians(Pitch)));
		front.y = sin(radians(Pitch));
		front.z = sin(radians(Yaw) * cos(radians(Pitch)));
		Front = normalize(front);
		Right = normalize(cross(Front, WorldUp));
		Up = normalize(cross(Right, Front));
	}
};

#endif 