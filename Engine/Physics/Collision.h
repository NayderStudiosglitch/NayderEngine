#pragma once

struct BoxCollider {
    float x;
    float y;
    float z;
    float width;
    float height;
    float depth;
};

class CollisionSystem {
public:
    bool CheckCollision(const BoxCollider& a, const BoxCollider& b);
};
