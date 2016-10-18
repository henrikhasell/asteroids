#ifndef ASTEROID_HPP
#define ASTEROID_HPP

// TODO: Move to a central location.
#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 600

#include "graphics.hpp"
#include "model.hpp"

class Asteroid
{
public:
    static constexpr float rotationSpeed = 0.01f;
    static constexpr float movementSpeed = 2.0f;

    Asteroid(
        const Model &model,
        const glm::vec2 &position,
        const glm::vec2 &velocity,
        float rotation,
        float scale
    );
    void draw(Graphics &graphics);
    void move();
private:
    const Model &model;
    glm::vec2 position;
    glm::vec2 velocity;
    float rotation;
    float scale;
};

#endif /* ASTEROID_HPP */
