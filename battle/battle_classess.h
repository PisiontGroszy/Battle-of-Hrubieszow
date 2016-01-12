#ifndef CLASSESS_H_INCLUDED
#define CLASSESS_H_INCLUDED
#define CLASSESS_H_INCLUDED

#include "classes/weapons.h"

void Shot(weapon W, bool Mine, sf::Vector2f cel, sf::Vector2f start, bool * readyToShot);
void ShotRocket(weapon W, bool Mine, int ID, sf::Vector2f start, bool * readyToShot);

#include "classes/drone.h"
#include "classes/spaceship.h"
#include "classes/bullets.h"
#include "classes/souls.h"
#include "classes/enemies.h"

#endif // CLASSESS_H_INCLUDED
