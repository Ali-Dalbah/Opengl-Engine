#include "../include/Component.h"

Component::Component(const std::string& name): model(name) {
    this->name = name;
}

void Component::render(Camera& camera) {
    model.render(*shader, camera);
}

void Component::setShader(Shader& shader) {
    this->shader = &shader;
}

void Component::rotate(float theta, axis a) {
	model.rotate(theta, a);
}

void  Component::translate(float displacement, axis a) {
	model.translate(displacement, a);

}

void Component::setScale(float scale) {
	model.setScale(scale);
}

void Component::applyCollision(PhysicalAttributes) {}

void Component::applyPhysics() {}

Component::~Component() {}