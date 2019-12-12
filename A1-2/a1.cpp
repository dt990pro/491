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

glm::vec3 WhatPartOfALivesInBDir(glm::vec3 a, glm::vec3 b);
glm::vec3 WhatPartOfALivesPerpToB(glm::vec3 a, glm::vec3 b);
glm::vec3 UnitSurfaceNormal(glm::vec3 q, glm::vec3 r, glm::vec3 s);
float Area(glm::vec3 q, glm::vec3 r, glm::vec3 s);
bool IsPointInTriangle(glm::vec3 q, glm::vec3 r, glm::vec3 s, glm::vec3 p);
float DistanceFromPointToPlane(glm::vec3 q, glm::vec3 r, glm::vec3 s, glm::vec3 p);
void WhoAmI(std::string& yourName, std::string& yourEmailAddress);

int main() {
	glm::vec3 test = UnitSurfaceNormal(glm::vec3(0., 0., 0.), glm::vec3(4., 0., 0.), glm::vec3(0., 4., 0.));
	printf("%f, %f, %f\n", test.x, test.y, test.z);
	printf("%f\n", Area(glm::vec3(0., 0., 0.), glm::vec3(5., 0., 0.), glm::vec3(0., 4., 0.)));

	if (IsPointInTriangle(glm::vec3(0., 0., 0.), glm::vec3(5., 0., 0.), glm::vec3(0., 4., 0.), glm::vec3(1., 1., 0.))) printf("yes\n");
	else printf("no\n");

	printf("%f\n", DistanceFromPointToPlane(glm::vec3(0., 0., 0.), glm::vec3(5., 0., 0.), glm::vec3(0., 4., 0.), glm::vec3(1., 9., 4.)));

	return 0;
}

glm::vec3
WhatPartOfALivesInBDir(glm::vec3 a, glm::vec3 b)
{
	float val = glm::dot(a, b) / (glm::length(b) * glm::length(b));
	return val * b;
}


glm::vec3
WhatPartOfALivesPerpToB(glm::vec3 a, glm::vec3 b)
{
	return a - WhatPartOfALivesInBDir(a, b);
}


glm::vec3
UnitSurfaceNormal(glm::vec3 q, glm::vec3 r, glm::vec3 s)
{
	glm::vec3 n = glm::cross(r - q, s - q);
	return glm::normalize(n);
}


float
Area(glm::vec3 q, glm::vec3 r, glm::vec3 s)
{
	return glm::length(glm::cross(r - q, s - q)) / 2.;
}


bool
IsPointInTriangle(glm::vec3 q, glm::vec3 r, glm::vec3 s, glm::vec3 p)
{
	glm::vec3 normal = UnitSurfaceNormal(q, r, s);

	// if in the plane
	if (glm::dot(p - q, normal) != 0.) return false;

	// if in the triangle area
	glm::vec3 nq = glm::cross(r - q, p - q);
	glm::vec3 nr = glm::cross(s - r, p - r);
	glm::vec3 ns = glm::cross(q - s, p - s);
	if (glm::dot(normal, nq) > 0. && glm::dot(normal, nr) > 0. && glm::dot(normal, ns) > 0.) return true;
	else return false;
}


float
DistanceFromPointToPlane(glm::vec3 q, glm::vec3 r, glm::vec3 s, glm::vec3 p)
{
	glm::vec3 normal = UnitSurfaceNormal(q, r, s);
	glm::vec3 pq = p - q;

	return glm::length(WhatPartOfALivesInBDir(pq, normal));
}


void
WhoAmI(std::string& yourName, std::string& yourEmailAddress)
{
	yourName = "Jiawei Mo";
	yourEmailAddress = "moji@oregonstate.edu";
}