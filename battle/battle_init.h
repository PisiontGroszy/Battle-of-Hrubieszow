#ifndef INIT_H_INCLUDED
#define INIT_H_INCLUDED

void init_textures()
{
    statek.wybuch.loadAnimation("assets/graphics/spaceship/destroy.animation");
    statek.eksplozja.loadAnimation("assets/graphics/spaceship/blood.animation");
}

void init_positions()
{
    statek.sprite.setPosition(screenX/2 - Collision::GetSpriteSize(statek.sprite).x / 2, screenY/2 - Collision::GetSpriteSize(statek.sprite).x / 2);
}

#endif // INIT_H_INCLUDED
