#include "spaceship.hpp"
#include <iostream>

SpaceShip::SpaceShip(Model &model, const glm::vec2  &position, float rotation, float scale) :
    model(model),
    position(position),
    rotation(rotation),
    scale(scale)
{
    /* Do nothing! */
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
}

void SpaceShip::draw(Graphics &graphics)
{
    graphics.draw(model, position, scale, rotation);
}
