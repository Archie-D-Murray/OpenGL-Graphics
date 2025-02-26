#include <glm/ext/matrix_float2x2.hpp>
#include <glm/gtc/constants.hpp>
#include <glm/matrix.hpp>
#include <iostream>

// Include the glm library
#include <glm/glm.hpp>
#include <glm/gtx/io.hpp>

glm::mat2 rotation(float angle) {
    glm::mat2 rot(0);
    rot[0][0] = +cosf(angle); rot[0][1] = -sinf(angle);
    rot[1][0] = +sinf(angle); rot[1][1] = +cosf(angle);
    return rot;
}

void vectors() {
    std::cout << glm::vec3 { 2, 0, 3 } << "\n";
}

void matrices() {
    float angle = -glm::two_pi<float>() * 0.25f; //180 deg
    glm::vec2 point = { 1, 0 };
    glm::mat2 rot = rotation(angle);
    std::cout << point << " rotated by mat2 " << rot << " is " << point * rot << "\n";
}

void matrix_operations() {
    glm::mat2 a; //glm::mat2(-1, +3, +2, -5);
    a[0][0] = -1; a[1][0] = 3;
    a[0][1] = +2; a[1][1] = -5;

    glm::mat2 b; // glm::mat2(+0, +2, +7, +1);
    b[0][0] = +0; b[1][0] = +2;
    b[0][1] = +7; b[1][1] = +1;

    glm::mat2 c = glm::mat2(+3, +2, -3, -4);
    c[0][0] = +3; c[1][0] = +2;
    c[0][1] = -3; c[1][1] = -4;

    std::cout << "a: " << a << "\nb: " << b << "\nc: " << c << "\n";
    std::cout << "a * b = " << a * b << "\n"; // glm is column major so all multiplications are backwards - I have flipped coordinates in matrix init to not do this, alternative is always printing transpose
    std::cout << "a * b * c = " << a * b * c << "\n";
    std::cout << "c * b * a = " << c * b * a << "\n";
    std::cout << "aT * b = " << glm::transpose(a) * b << "\n";
    std::cout << "a^-1 = " << glm::inverse(a) << "\n";
}

void matrix_operations_flipped_outputs() {
    glm::mat2 a; //glm::mat2(-1, +3, +2, -5);
    a[0][0] = -1; a[0][1] = 3;
    a[1][0] = +2; a[1][1] = -5;

    glm::mat2 b; // glm::mat2(+0, +2, +7, +1);
    b[0][0] = +0; b[0][1] = +2;
    b[1][0] = +7; b[1][1] = +1;

    glm::mat2 c = glm::mat2(+3, +2, -3, -4);
    c[0][0] = +3; c[0][1] = +2;
    c[1][0] = -3; c[1][1] = -4;

    std::cout << "a: " << glm::transpose(a) << "\nb: " << glm::transpose(b) << "\nc: " << glm::transpose(c) << "\n";
    std::cout << "a * b = " << glm::transpose(a) * glm::transpose(b) << "\n"; // glm is column major so all multiplications are backwards - I have flipped coordinates in matrix init to not do this, alternative is always printing transpose
    std::cout << "a * b * c = " << glm::transpose(a) * glm::transpose(b) * glm::transpose(c) << "\n";
    std::cout << "c * b * a = " << glm::transpose(c) * glm::transpose(b) * glm::transpose(a) << "\n";
    std::cout << "aT * b = " << glm::transpose(glm::transpose(a)) * glm::transpose(b) << "\n";
    std::cout << "a^-1 = " << glm::transpose(glm::inverse(a)) << "\n";
}

int main() {
    std::cout << "Vectors and matrices\n";
    matrix_operations_flipped_outputs();
    return 0;
}
