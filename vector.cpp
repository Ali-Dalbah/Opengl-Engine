#include "../include/vector.h"

Vector2f::Vector2f() {
    x = 0.f;
    y = 0.f;
}

Vector2f::Vector2f(float x, float y): x(x), y(y) {}

Vector2f::~Vector2f() {
}

Vector2f Vector2f::operator+ (Vector2f const & vec) {
    return Vector2f(x + vec.x, y + vec.y);
}

Vector2f Vector2f::operator- (Vector2f const & vec) {
    return Vector2f(x - vec.x, y - vec.y);
}

Vector2f Vector2f::operator/ (Vector2f const & vec) {
    return Vector2f(x / vec.x, y / vec.y);
}

Vector2f Vector2f::operator* (Vector2f const & vec) {
    return Vector2f(x * vec.x, y * vec.y);
}

void Vector2f::operator+= (Vector2f const & vec) {
    x += vec.x;
    y += vec.y;
}

void Vector2f::operator-= (Vector2f const & vec) {
    x -= vec.x;
    y -= vec.y;
}

void Vector2f::operator/= (Vector2f const & vec) {
    x /= vec.x; 
    y /= vec.y;
}

void Vector2f::operator*= (Vector2f const & vec) {
    x *= vec.x;
    y *= vec.y;
}

Vector2f::Vector2f() {
    x = 0.f;
    y = 0.f;
}

Vector3f::Vector3f(float x, float y, float z): x(x), y(y), z(z) {}

Vector3f::~Vector3f() {
}

Vector3f Vector3f::operator+ (Vector3f const & vec) {
    return Vector3f(x + vec.x, y + vec.y, z + vec.z);
}

Vector3f Vector3f::operator- (Vector3f const & vec) {
    return Vector3f(x - vec.x, y - vec.y, z - vec.z);
}

Vector3f Vector3f::operator/ (Vector3f const & vec) {
    return Vector3f(x / vec.x, y / vec.y, z / vec.z);
}

Vector3f Vector3f::operator* (Vector3f const & vec) {
    return Vector3f(x * vec.x, y * vec.y, z * vec.z);
}

void Vector3f::operator+= (Vector3f const & vec) {
    x += vec.x;
    y += vec.y;
    z += vec.z;
}

void Vector3f::operator-= (Vector3f const & vec) {
    x -= vec.x;
    y -= vec.y;
    z -= vec.z;
}

void Vector3f::operator/= (Vector3f const & vec) {
    x /= vec.x; 
    y /= vec.y;
    z /= vec.z;
}

void Vector3f::operator*= (Vector3f const & vec) {
    x *= vec.x;
    y *= vec.y;
    z *= vec.z;
}

Vector2f Vector2f::operator* (float num) {
    return Vector2f(x * num, y * num);
}

void Vector2f::operator*= (float num) {
    x *= num;
    y *= num;
}

Vector2f Vector2f::operator/ (float num) {
    return Vector2f(x / num, y / num);
}

void Vector2f::operator/= (float num) {
    x /= num;
    y /= num;
}

Vector3f Vector3f::operator* (float num) {
    return Vector3f(x * num, y * num, z * num);
}

void Vector3f::operator*= (float num) {
    x *= num;
    y *= num;
    z *= num;
}

Vector3f Vector3f::operator/ (float num) {
    return Vector3f(x / num, y / num, z / num);
}

void Vector3f::operator/= (float num) {
    x /= num;
    y /= num;
    z /= num;
}