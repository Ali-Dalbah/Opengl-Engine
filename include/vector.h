#ifndef VECTOR_H
#define VECTOR_H

class Vector2f{
    public:
        float x;
        float y;
        Vector2f();
        Vector2f(float, float);
        ~Vector2f();

        Vector2f operator+ (Vector2f const &);
        Vector2f operator- (Vector2f const &);
        Vector2f operator/ (Vector2f const &);
        Vector2f operator* (Vector2f const &);

        Vector2f operator/ (float);
        Vector2f operator* (float);

        void operator+= (Vector2f const &);
        void operator-= (Vector2f const &);
        void operator/= (Vector2f const &);
        void operator*= (Vector2f const &);

        void operator/= (float);
        void operator*= (float);
};

class Vector3f{
    public:
        float x;
        float y;
        float z;
        Vector3f();
        Vector3f(float, float, float);

        Vector3f operator+ (Vector3f const &);
        Vector3f operator- (Vector3f const &);
        Vector3f operator/ (Vector3f const &);
        Vector3f operator* (Vector3f const &);

        Vector3f operator/ (float);
        Vector3f operator* (float);

        void operator+= (Vector3f const &);
        void operator-= (Vector3f const &);
        void operator/= (Vector3f const &);
        void operator*= (Vector3f const &);

        void operator/= (float);
        void operator*= (float);
};

#endif 