#include "maths.hpp"

glm::mat4 Maths::scale(const glm::vec3 &scale) {
    glm::mat4 scaleMat;
    scaleMat[0][0] = scale.x;
    scaleMat[1][1] = scale.y;
    scaleMat[2][2] = scale.z;
    return scaleMat;
}

glm::mat4 Maths::rotate(const glm::vec3 &axis, float angle) {
    glm::mat4 rotateMat;
    float sin = sinf(angle);
    float cos = cosf(angle);
    float xx = axis.x * axis.x, yy = axis.y * axis.y, zz = axis.z * axis.z;
    float xy = axis.x * axis.y, xz = axis.x * axis.z, yz = axis.y * axis.z;
    float xs = axis.x * sin,    ys = axis.y * sin,    zs = axis.z * sin;
    rotateMat[0][0] = xx * (1 - cos) + cos;
	rotateMat[0][1] = xy + (1 - cos) - zs;
	rotateMat[0][2] = xz * (1 - cos) + ys;
    rotateMat[1][0] = xy * (1 - cos) + zs;
	rotateMat[1][1] = yy * (1 - cos) + cos;
	rotateMat[1][2] = yz * (1 - cos) - xs; 
    rotateMat[2][0] = xz * (1 - cos) - ys;
	rotateMat[2][1] = yz * (1 - cos) + xs;
	rotateMat[2][2] = zz * (1 - cos) + cos;
	rotateMat[3][3] = 1.0f;
    return rotateMat;
}

glm::mat4 Maths::translate(const glm::vec3 &translation) {
    glm::mat4 translateMat;
    translateMat[3][0] = translation.x;
    translateMat[3][1] = translation.y;
    translateMat[3][2] = translation.z;
    return translateMat;
}
