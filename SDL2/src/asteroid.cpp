#include "asteroid.hpp"

Asteroid::Asteroid(const Model &model, const glm::vec2 &position, const glm::vec2 &velocity, float rotation, float scale) :
    model(model),
    position(position),
    velocity(velocity),
    rotation(rotation),
    scale(scale)
{
    /* Do nothing! */
}

void Asteroid::draw(Graphics &graphics)
{
    graphics.draw(model, position, scale, rotation);
}

void Asteroid::move()
{
    position += velocity;
    // How far is the object allowed to go offscreen:
    constexpr float padding = 100.0f;
    // Minimum and maximum legal X position of the object:
    constexpr float max_x = SCREEN_WIDTH + padding;
    constexpr float min_x = -padding;
    // Minimum and maximum legal Y position of the object:
    constexpr float max_y = SCREEN_HEIGHT + padding;
    constexpr float min_y = -padding;

    if(position.x > max_x) position.x -= max_x + padding;
    if(position.x < min_x) position.x += max_x + padding;
    if(position.y > max_y) position.y -= max_y + padding;
    if(position.y < min_y) position.y += max_y + padding;

    rotation += rotationSpeed;
}
