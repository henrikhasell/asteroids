#include "spaceship.hpp"
#include <iostream>

SpaceShip::SpaceShip(const Model &model, const glm::vec2  &position, float rotation, float scale) :
    model(model),
    position(position),
    rotation(rotation),
    scale(scale),
    cooldown(bulletCooldown)
{
    /* Do nothing! */
}

void SpaceShip::fireBullet(std::vector<Bullet> &bulletArray)
{
    if(cooldown <= 0)
    {
        bulletArray.push_back(Bullet(position, glm::vec2()));
        cooldown = bulletCooldown;
    }
}

void SpaceShip::update(const Uint8 keyboardState[])
{
    if(keyboardState[SDL_SCANCODE_LEFT] ^ keyboardState[SDL_SCANCODE_RIGHT])
    {
        if(keyboardState[SDL_SCANCODE_LEFT])
        {
            rotation -= rotationSpeed;
        }
        else
        {
            rotation += rotationSpeed;
        }
    }

    if(keyboardState[SDL_SCANCODE_UP] ^ keyboardState[SDL_SCANCODE_DOWN])
    {
        glm::vec2 velocity = {
            +sin(rotation) * movementSpeed,
            -cos(rotation) * movementSpeed
        };

        if(keyboardState[SDL_SCANCODE_UP])
        {
            position += velocity;
        }
        else
        {
            position -= velocity;
        }
    }

    cooldown--;
}

void SpaceShip::draw(Graphics &graphics)
{
    graphics.draw(model, position, scale, rotation);
}
