#ifndef SPACESHIP_HPP
#define SPACESHIP_HPP

#include <vector>

#include <SDL2/SDL.h>
#include <glm/vec2.hpp>
#include "graphics.hpp"
#include "model.hpp"

struct Bullet
{
    Bullet(const glm::vec2 &position, const glm::vec2 &velocity) :
        position(position),
        velocity(velocity),
        timeToLive(20)
    {
        /* Absolutely nothing! */
    }

    void move()
    {
        position += velocity;
        timeToLive--;
    }

    glm::vec2 position;
    glm::vec2 velocity;
    int timeToLive;
};

class SpaceShip
{
public:
    static constexpr float rotationSpeed = 0.1f;
    static constexpr float movementSpeed = 5.0f;
    static constexpr int bulletCooldown = 10;

    SpaceShip(
        const Model &model,
        const glm::vec2 &position,
        float rotation,
        float scale
    );

    void fireBullet(std::vector<Bullet> &bulletArray);

    void update(const Uint8 keyboardState[]);
    void draw(Graphics &graphics);
private:
    const Model &model;
    glm::vec2 position;
    float rotation;
    float scale;
    int cooldown;
};

#endif /* SPACESHIP_HPP */
