#ifndef SPACESHIP_HPP
#define SPACESHIP_HPP

#include <SDL2/SDL.h>
#include <glm/vec2.hpp>
#include "graphics.hpp"
#include "model.hpp"

class SpaceShip
{
public:
    static constexpr float rotationSpeed = 0.1f;
    static constexpr float movementSpeed = 5.0f;

    SpaceShip(
        Model &model,
        const glm::vec2  &position,
        float rotation,
        float scale
    );
    void update(const Uint8 keyboardState[]);
    void draw(Graphics &graphics);
private:
    Model &model;
    glm::vec2 position;
    float rotation;
    float scale;
};

#endif /* SPACESHIP_HPP */
