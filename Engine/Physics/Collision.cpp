#include "Collision.h"

bool CollisionSystem::CheckCollision(const BoxCollider& a, const BoxCollider& b) {
    return (a.x < b.x + b.width)   && (a.x + a.width > b.x) &&
           (a.y < b.y + b.height)  && (a.y + a.height > b.y) &&
           (a.z < b.z + b.depth)   && (a.z + a.depth > b.z);
}
