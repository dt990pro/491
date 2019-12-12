#include <stdio.h>
#include <string>
#define _USE_MATH_DEFINES
#include <cmath>

#define GLM_FORCE_RADIANS
#include "glm/vec2.hpp"
#include "glm/vec3.hpp"
#include "glm/mat4x4.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/matrix_inverse.hpp"


glm::mat4
Multiply(glm::mat4 a, glm::mat4 b)
{
	return a * b;
}



glm::vec3
Multiply(glm::mat4 a, glm::vec3 b)
{
	glm::vec4 promote = glm::vec4(b.x, b.y, b.z, 1.f);
	glm::vec4 temp = a * promote;
	return glm::vec3(temp.x, temp.y, temp.z);
}



glm::vec3
ScalePointAroundAnotherPoint(glm::vec3 inputPoint, glm::vec3 centerPoint, glm::vec3 scale)
{
	// identity mat
	glm::mat4 i = glm::mat4(1.f);

	// subtract center
	glm::mat4 sub_tran = glm::translate(i, 0.f - centerPoint);

	// scale
	glm::mat4 scale_tran = glm::scale(i, scale);

	// add center back
	glm::mat4 add_tran = glm::translate(i, centerPoint);

	// associative
	glm::mat4 transformation = add_tran * scale_tran * sub_tran;
	return Multiply(transformation, inputPoint);
}



glm::vec3
RotatePointAroundAnotherPoint(glm::vec3 inputPoint, glm::vec3 centerPoint, glm::mat4 first, glm::mat4 second, glm::mat4 third)
{
	// identity mat
	glm::mat4 i = glm::mat4(1.f);

	// subtract center
	glm::mat4 sub_tran = glm::translate(i, 0.f - centerPoint);

	// add center back
	glm::mat4 add_tran = glm::inverse(sub_tran);

	// associative
	glm::mat4 transformation = add_tran * third * second * first * sub_tran;
	return Multiply(transformation, inputPoint);
}


void
WhoAmI(std::string& yourName, std::string& yourEmailAddress)
{
	yourName = "Jiawei Mo";
	yourEmailAddress = "moji@oregonstate.edu";
}


void
PrintMatrix(glm::mat4 mat)
{
	for (int row = 0; row < 4; row++)
	{
		fprintf(stderr, "  %7.2f %7.2f %7.2f %7.2f\n", mat[row][0], mat[row][1], mat[row][2], mat[row][3]);
	}
	printf("\n");
}


int main() {
	glm::mat4 a = glm::mat4(1, 1, 1, 1, 2, 2, 2, 2, 3, 3, 3, 3, 4, 4, 4, 4);
	glm::mat4 b = glm::mat4(1, 1, 1, 4, 2, 2, 2, 3, 3, 3, 3, 2, 4, 4, 4, 1);
	glm::vec3 c = glm::vec3(4, 2, 7);

	glm::mat4 z = Multiply(a, b);

	glm::vec3 y = Multiply(a, c);


	y = ScalePointAroundAnotherPoint(glm::vec3(3, 0, 0), glm::vec3(1, 0, 0), glm::vec3(1, 2, 3));
	printf("%f, %f, %f\n", y.x, y.y, y.z);

	return 0;
}