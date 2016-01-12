#ifndef SPACESHIP_H_INCLUDED
#define SPACESHIP_H_INCLUDED

class spaceship
{
public:
    sf::Uint16_s movingSpeed;
    sf::Uint16_s baseMovingSpeed;
    sf::Uint16_s MovingSpeed;

    sf::Uint16_s XP;

    sf::Uint16_s HP;
    sf::Uint16_s maxHP;
    sf::Uint16_s ammo;
    sf::Uint16_s ammoMax;
    sf::Int16_s shield;
    sf::Uint16_s shieldMax;

    sf::Uint16_s shieldRegerationTimeInFrames;
    sf::Uint16_s bulletsPerRegeneration;
    sf::Uint16_s FramesForRegeneration;

    sf::Float_s shieldRegenerationCounter = 0.f;
    sf::Float_s shieldRegainingCounter = 0.f;
    sf::Float_s ammoRegenerationCtrlNumber = 0.f;
    sf::Float_s ammoRegainingCounter = 0.f;

    bool destroyed = false;
    bool destroyed_end = false;
    bool regenerateAmmo = true;
    bool startExplosion = false;
    bool shouldSlow = false;

    weapon Weapon;
    weapons Weapons;
    laser Laser;

    bool enemySelected = false;
    sf::Vector2f target;
    int targetID = -1;
    float releaseTargets = 0.f;
    vector <drone> drones;

    sf::Sprite sprite;
    animation wybuch;
    animation eksplozja;

    sf::Texture shieldTexture;
    sf::Sprite shieldSprite;

    void load_texture(string dir);
    void move();
    void getDamage(int damage);
    void regenerate(bool Ammo);
    void addDrone(string dir, float r, float a, int weaponID);
    void updateDronesTextures();
private:
    sf::Texture texture;
};

void spaceship::updateDronesTextures()
{
    for(int dronesTabPos = drones.size() - 1; dronesTabPos >= 0; dronesTabPos--)
        drones[dronesTabPos].loadTextures("assets/graphics/bullets/" + Weapons.top().codeName + "/drone.png");
}

void spaceship::addDrone(string dir, float r, float a, int weaponID)
{
    weapons dw;
    dw.loadFromFile("assets/xml/weapons3.xml");
    dw.select(weaponID);

    drone * d  = new drone;
    d -> create(dir, baseMovingSpeed, r, a, dw.top());
    d -> Drone.setPosition(screenCenter);
    drones.push_back(*d);

    delete d;
}

void spaceship::regenerate(bool Ammo)
{
    if(shield == 0 and shieldRegainingCounter < shieldRegerationTimeInFrames)
        shieldRegainingCounter += timeModifier;

    if(shield == 0 and shieldRegainingCounter >= shieldRegerationTimeInFrames)
    {
        shield = 10;
        shieldRegainingCounter = 0;
    }

    if(shield > 0 and shield < shieldMax and shieldRegenerationCounter < shieldRegerationTimeInFrames / 6)
        shieldRegenerationCounter += timeModifier;

    if(shield > 0 and shield < shieldMax and shieldRegenerationCounter >= shieldRegerationTimeInFrames / 6)
    {
        shield++;
        shieldRegenerationCounter = 0;
    }

    if(Ammo)
    {
        if(ammo == 0 and ammoRegainingCounter < 180)
        {
            ammoRegainingCounter += timeModifier;
            regenerateAmmo = false;
        }

        if(ammo == 0 and ammoRegainingCounter >= 180)
        {
            regenerateAmmo = true;
            ammoRegainingCounter = 0;
        }

        if(ammoRegenerationCtrlNumber < FramesForRegeneration and Ready_to_shot)
            ammoRegenerationCtrlNumber += timeModifier;

        else if(ammo < ammoMax and regenerateAmmo and Ready_to_shot)
        {
            if(ammoMax - ammo > bulletsPerRegeneration)
                ammo += bulletsPerRegeneration;
            else
                ammo = ammoMax;

            ammoRegenerationCtrlNumber = 0;
        }
    }
}

void spaceship::load_texture(string dir)
{
    textureManager.add(dir, true);
    sprite.setTexture(*textureManager.get(dir));
}

void spaceship::move()
{
    movingSpeed = MovingSpeed * timeModifier;

    double i = 4;

    direction = kursor.sprite.getPosition();

    //Góra
    if(characterControler.checkAction(characterControler.playerUp) and !(characterControler.checkAction(characterControler.playerLeft) or characterControler.checkAction(characterControler.playerRight)))
    {
        view.move(0, -movingSpeed);
        kursor.sprite.move(0, -movingSpeed);
        app.setView(view);
        screenCornerY -= movingSpeed;
        mapCornerY -= movingSpeed / 4;
        map2CornerY -= movingSpeed / 3;
        map3CornerY -= movingSpeed / 2;
    }
    //-------------

    //Góra + prawo
    else if(characterControler.checkAction(characterControler.playerUp) and characterControler.checkAction(characterControler.playerRight) and !characterControler.checkAction(characterControler.playerLeft))
    {
        movingSpeed -= movingSpeed / i;

        view.move(0, -movingSpeed);
        kursor.sprite.move(0, -movingSpeed);
        app.setView(view);
        screenCornerY -= movingSpeed;
        mapCornerY -= movingSpeed / 4;
        map2CornerY -= movingSpeed / 3;
        map3CornerY -= movingSpeed / 2;

        view.move(movingSpeed, 0);
        kursor.sprite.move(movingSpeed, 0);
        app.setView(view);
        screenCornerX += movingSpeed;
        mapCornerX += movingSpeed / 4;
        map2CornerX += movingSpeed / 3;
        map3CornerX += movingSpeed / 2;
    }
    //-------------

    //Góra + lewo
    else if(characterControler.checkAction(characterControler.playerUp) and !characterControler.checkAction(characterControler.playerRight) and characterControler.checkAction(characterControler.playerLeft))
    {
        movingSpeed -= movingSpeed / i;

        view.move(0, -movingSpeed);
        kursor.sprite.move(0, -movingSpeed);
        app.setView(view);
        screenCornerY -= movingSpeed;
        mapCornerY -= movingSpeed / 4;
        map2CornerY -= movingSpeed / 3;
        map3CornerY -= movingSpeed / 2;

        view.move(-movingSpeed, 0);
        kursor.sprite.move(-movingSpeed, 0);
        app.setView(view);
        screenCornerX -= movingSpeed;
        mapCornerX -= movingSpeed / 4;
        map2CornerX -= movingSpeed / 3;
        map3CornerX -= movingSpeed / 2;
    }
    //-------------

    //Dół
    else if(characterControler.checkAction(characterControler.playerDown) and !(characterControler.checkAction(characterControler.playerLeft) or characterControler.checkAction(characterControler.playerRight)))
    {
        view.move(0, movingSpeed);
        kursor.sprite.move(0, movingSpeed);
        app.setView(view);
        screenCornerY += movingSpeed;
        mapCornerY += movingSpeed / 4;
        map2CornerY += movingSpeed / 3;
        map3CornerY += movingSpeed / 2;
    }
    //-------------

    //Dół + prawo
    else if(characterControler.checkAction(characterControler.playerDown) and characterControler.checkAction(characterControler.playerRight) and !characterControler.checkAction(characterControler.playerLeft))
    {
        movingSpeed -= movingSpeed / i;

        view.move(0, movingSpeed);
        kursor.sprite.move(0, movingSpeed);
        app.setView(view);
        screenCornerY += movingSpeed;
        mapCornerY += movingSpeed / 4;
        map2CornerY += movingSpeed / 3;
        map3CornerY += movingSpeed / 2;

        view.move(movingSpeed, 0);
        kursor.sprite.move(movingSpeed, 0);
        app.setView(view);
        screenCornerX += movingSpeed;
        mapCornerX += movingSpeed / 4;
        map2CornerX += movingSpeed / 3;
        map3CornerX += movingSpeed / 2;
    }
    //Dół + lewo
    else if(characterControler.checkAction(characterControler.playerDown) and !characterControler.checkAction(characterControler.playerRight) and characterControler.checkAction(characterControler.playerLeft))
    {
        movingSpeed -= movingSpeed / i;

        view.move(0, movingSpeed);
        kursor.sprite.move(0, movingSpeed);
        app.setView(view);
        screenCornerY += movingSpeed;
        mapCornerY += movingSpeed / 4;
        map2CornerY += movingSpeed / 3;
        map3CornerY += movingSpeed / 2;

        view.move(-movingSpeed, 0);
        kursor.sprite.move(-movingSpeed, 0);
        app.setView(view);
        screenCornerX -= movingSpeed;
        mapCornerX -= movingSpeed / 4;
        map2CornerX -= movingSpeed / 3;
        map3CornerX -= movingSpeed / 2;
    }
    //-------------

    //Prawo
    else if(characterControler.checkAction(characterControler.playerRight))
    {
        view.move(movingSpeed, 0);
        kursor.sprite.move(movingSpeed, 0);
        app.setView(view);
        screenCornerX += movingSpeed;
        mapCornerX += movingSpeed / 4;
        map2CornerX += movingSpeed / 3;
        map3CornerX += movingSpeed / 2;
    }
    //-------------

    //Lewo
    else if(characterControler.checkAction(characterControler.playerLeft))
    {
        view.move(-movingSpeed, 0);
        kursor.sprite.move(-movingSpeed, 0);
        app.setView(view);
        screenCornerX -= movingSpeed;
        mapCornerX -= movingSpeed / 4;
        map2CornerX -= movingSpeed / 3;
        map3CornerX -= movingSpeed / 2;
    }
    //-------------

    //Bezruch
    else
        newTiles = false;
    //-------

    direction -= kursor.sprite.getPosition();

    //ustawianie pozycji statku
    sprite.setPosition(screenX/2 + screenCornerX, screenY/2 + screenCornerY);
    //-------------------------
}

void spaceship::getDamage(int damage)
{
    if(damage < shield or (shield > 0 and damage > shield))shieldSprite.setColor(sf::Color(255, 255, 255, 255));

    if(damage < shield)
        shield -= damage;
    else if(shield > 0 and damage > shield)
        shield = 0;
    else if(shield == 0)
    {
        if(damage < HP)
            HP -= damage;
        else if(damage > HP)
            HP = 0;
    }
}
spaceship statek;

#endif // SPACESHIP_H_INCLUDED
