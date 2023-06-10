#include <glm/glm.hpp>

float abs(float x);

class HitBox{
    public:
        HitBox(glm::vec3, glm::vec3);
        bool isHit(HitBox&);
    private:
        glm::vec3 position;
        glm::vec3 sizes;
        glm::vec3 normals;
};