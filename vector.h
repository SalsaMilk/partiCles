// Basic vector implementation for C and C++

#ifndef VECTOR_H
#define VECTOR_H

#include <math.h>

typedef struct {
    float x, y;
} Vector;

float distance(Vector p1, Vector p2) {
    return sqrtf((p2.x - p1.x)*(p2.x - p1.x) + (p2.y - p1.y)*(p2.y - p1.y));
}

float vec_length(Vector vec) {
    return sqrtf(vec.x*vec.x + vec.y*vec.y);
}

Vector vec_normalize(Vector vec) {
    float  len = vec_length(vec);
    Vector v = {vec.x / len, vec.y / len};
    return v;
}

#ifdef __cplusplus
Vector operator+ (const Vector &p1, const Vector &p2) {
    return Vector {p1.x + p2.x, p1.y + p2.y};
}

Vector operator- (const Vector &p1, const Vector &p2) {
    return Vector {p1.x - p2.x, p1.y - p2.y};
}

Vector operator* (const Vector &p1, const Vector &p2) {
    return Vector {p1.x * p2.x, p1.y * p2.y};
}

Vector operator* (const Vector &p1, const float &i) {
    return Vector {p1.x * i, p1.y * i};
}

Vector operator/ (const Vector &p1, const Vector &p2) {
    return Vector {p1.x / p2.x, p1.y / p2.y};
}

Vector operator/ (const Vector &p1, const float &i) {
    return Vector {p1.x / i, p1.y / i};
}
#endif // __cplusplus

#endif // VECTOR_H