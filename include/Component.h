#include "Model.h"
#include "HitBox.h"

struct PhysicalAttributes{
    glm::vec3 position;
    glm::vec3 velocity;
    glm::vec3 momentum;
    float mass;
};

class Component{
public:
    Component(const std::string&);
    std::string name;
    PhysicalAttributes physicsAttrib;
    void render(Camera&);
    void applyPhysics();
    void applyCollision(PhysicalAttributes);
    void setShader(Shader&);
    void rotate(float, axis);
    void translate(float, axis);
    void setScale(float);
    ~Component();
private:
    std::vector<HitBox> hitboxes;
    Model model;
    Shader* shader;
};