#ifndef DRON_H_INCLUDED
#define DRON_H_INCLUDED

class drone : public sf::Drawable
{
private:
    float speed;
    weapon Weapon;
    float fightCounter = 0;
    bool readyToShot = false;

    sf::Sprite turret;
public:
    virtual void draw(sf::RenderTarget & target, sf::RenderStates states) const;

    float radiaus;
    float angleMod;

    sf::Sprite Drone;

    void create(string dir, float newSpeed, float newRadiaus, float newAngleMod, weapon newWeapon);
    void rotateTo(sf::Vector2f t);
    void moveTo(sf::Vector2f vect, bool fight);
    void fightManager(sf::Vector2f target, int targetID);
    void loadTextures(string dir);
};

void drone::loadTextures(string dir)
{
    textureManager.add(dir, true);
    Drone.setTexture(*textureManager.get(dir));
}

void drone::create(string dir, float newSpeed, float newRadiaus, float newAngleMod, weapon newWeapon)
{
    textureManager.add("assets/graphics/bullets/" + newWeapon.codeName + "/texture.png");
    turret.setTexture(*textureManager.get("assets/graphics/bullets/" + newWeapon.codeName + "/texture.png"));
    turret.setOrigin(Collision::GetSpriteSize(turret) / 2.f);

    textureManager.add(dir, true);
    Drone.setTexture(*textureManager.get(dir));
    Drone.setOrigin(Collision::GetSpriteSize(Drone) / 2.f);

    speed = newSpeed;
    radiaus = newRadiaus;
    angleMod = newAngleMod;
    Weapon = newWeapon;
}

void drone::moveTo(sf::Vector2f vect, bool fight)
{
    if(fightCounter < 105)
        fightCounter += timeModifier;

    sf::Vector2f kierunek = vect - Drone.getPosition();
    float magnitude = sqrt((kierunek.x * kierunek.x) + (kierunek.y * kierunek.y));
    sf::Vector2f unitVector = sf::Vector2f(kierunek.x / magnitude, kierunek.y / magnitude);

    unitVector *= timeModifier;

    float tmpSpeed = speed;
    if(magnitude <= radiaus * 0.6)
        tmpSpeed *= Map(magnitude, 5.f, radiaus * 0.6, 0.f, 1.1f);
    else
        tmpSpeed *= 1.1f;

    Drone.move(unitVector * tmpSpeed);

    turret.setPosition(Drone.getPosition());
    if(!fight)
        rotateTo(sf::Vector2f(screenCornerX + sf::Mouse::getPosition(app).x * viewScale, screenCornerY + sf::Mouse::getPosition(app).y * viewScale));
}

void drone::fightManager(sf::Vector2f target, int targetID)
{
    if(!shouldRender(target))
    {
        sf::Vector2f kierunek = target - Drone.getPosition();

        if(sqrt((kierunek.x * kierunek.x) + (kierunek.y * kierunek.y)) > 3000)
            return;
    }

    rotateTo(target);

    if(fightCounter >= 101 - Weapon.agility)
    {
        readyToShot = true;
        fightCounter = 0.f;
    }

    if(readyToShot)
    {
        if(Weapon.codeName != "autoRockets")
            Shot(Weapon, true, target, Drone.getPosition(), &readyToShot);
        else
            ShotRocket(Weapon, true, targetID, Drone.getPosition(), &readyToShot);
    }
}

void drone::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
    target.draw(Drone, states);
    target.draw(turret, states);
}

void drone::rotateTo(sf::Vector2f t)
{
    float rotation = rotate_to_ff(turret.getPosition(), t) - turret.getRotation();

    //Limit prędkości obrotu
    float rotationSpeedLimit = 8 * timeModifier;
    //----------------------

    if(rotation < 180)
        rotation += 360;
    if(rotation > 180)
        rotation -= 360;

    //Egzekwowanie limitu prędkości obrotu
    if(rotation > rotationSpeedLimit)
        rotation = rotationSpeedLimit;
    if(rotation < -rotationSpeedLimit)
        rotation = -rotationSpeedLimit;
    //----------------------

    turret.rotate(rotation);
}
#endif // DRON_H_INCLUDED
