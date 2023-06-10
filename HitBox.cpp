#include "../include/HitBox.h"

float abs(float x) {
    return x > 0? x: -x;
}

HitBox::HitBox(glm::vec3 position, glm::vec3 sizes): position(position), sizes(sizes) {}

bool HitBox::isHit(HitBox& hitbox) {
    if (abs(position.x + sizes.x/2 - hitbox.position.x - hitbox.sizes.x) < 0.1 &&
        abs(position.y + sizes.y/2 - hitbox.position.y - hitbox.sizes.y) < 0.1 &&
        abs(position.z + sizes.z/2 - hitbox.position.z - hitbox.sizes.z) < 0.1) 
        return true;
    return false;
}