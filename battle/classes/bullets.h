#ifndef BULLETS_H_INCLUDED
#define BULLETS_H_INCLUDED

class bullet
{
public:
    virtual void load_texture(string dir);

    virtual void rotator();
    virtual void rotate(float angle);
    virtual void CalculateDirection();
    virtual void prepareToMove();
    virtual bool move();

    sf::Vector2f shouldMove;
    sf::Vector2f unitVector;
    sf::Vector2f target;
    sf::Sprite sprite;

    float speed;

    int mass;
    int oldX;
    int oldY;
    int cel_x;
    int cel_y;
    int frame = 0;
    int damage;
    int start_x;
    int start_y;
    int accuracy;
    int modifier;
    int ammoUsage;
    int accuracyBonus;

    bool hit = false;
    bool destroyed = false;
    bool Kierunek;
    bool mine;
    bool freeze = false;
    string bulletType;
    animation wybuch;

    bool operator<(bullet b) const {return (!destroyed and b.destroyed);}
private:
    sf::Texture texture;
    bool Good;
    int Error_code;
    int moves;
    int doneMoves;

    friend class saw;
};

void bullet::load_texture(string dir)
{
    textureManager.add(dir , true);
    sprite.setTexture(*textureManager.get(dir));
}

void bullet::CalculateDirection()
{
    if(accuracyBonus > 0)
        accuracy += 100;

    unitVector = sf::Vector2f(cos(3.14159265 * (sprite.getRotation() + 180) / 180.f), sin(3.14159265 * (sprite.getRotation() + 180) / 180.f));

    unitVector *= 5.f;
    unitVector *= speed;
    unitVector.y += ((random() % 100) - 50) / (5.0 / speed * accuracy);
    unitVector.x += ((random() % 100) - 50) / (5.0 / speed * accuracy);
}

void bullet::prepareToMove()
{
    shouldMove = sf::Vector2f(unitVector.x, unitVector.y) * timeModifier;
    moves = sqrt(pow(shouldMove.x, 2) + pow(shouldMove.y, 2)) / 5.f;
    doneMoves = 0;
}

bool bullet::move()
{
    if(freeze)
        return true;

    if(doneMoves != moves)
    {
        sprite.move(shouldMove / (float) moves);
        doneMoves++;
        return false;
    }
    else
    {
        if(sprite.getPosition().x > (screenX * 1.5) + screenCornerX or sprite.getPosition().x < (screenX * -1.5) + screenCornerX or sprite.getPosition().y > (screenY * 1.5) + screenCornerY or sprite.getPosition().y < (screenY * -1.5) + screenCornerY)
            destroyed = true;

        return true;
    }
}

void bullet::rotator() {sprite.setRotation(rotate_to_ff(sprite.getPosition(), sf::Vector2f(cel_x, cel_y)) + 180);}
void bullet::rotate(float angle){sprite.rotate(angle);}

class saw : public bullet
{
private:
    float pseudoRotation;
    bool reachedTarget = false;
    sf::Texture texture2;
    sf::Vector2f sourceUnitVector;

public:
    float time = 2.f;
    float speedBonus = 0.f;
    virtual void rotator() override;
    virtual void rotate(float angle) override;
    virtual void CalculateDirection() override;
    virtual void prepareToMove() override;
    virtual bool move() override;
    virtual void load_texture(string dir);

    void hitTarget();
    void preCalculating();
    bool isTargetReached();
    float getPseudoRotation();

    bool playHitAnimation = false;
    sf::Clock speedClock;
};

float saw::getPseudoRotation()
{
    return pseudoRotation;
}

bool saw::isTargetReached()
{
    return reachedTarget;
}

void saw::rotator() {pseudoRotation = rotate_to_ff(sprite.getPosition(), sf::Vector2f(cel_x, cel_y)) + 180;}
void saw::rotate(float angle)
{
    pseudoRotation += angle;
    preCalculating();
}

void saw::hitTarget()
{
    reachedTarget = true;
    playHitAnimation = true;
    speedBonus = speed;
}

void saw::preCalculating()
{
    sourceUnitVector = sf::Vector2f(cos(3.14159265 * (pseudoRotation + 180) / 180.f), sin(3.14159265 * (pseudoRotation + 180) / 180.f));
}

void saw::CalculateDirection()
{
    if(!reachedTarget)
    {
        unitVector = sourceUnitVector * speed * Map(speedClock.getElapsedTime().asSeconds(), 0.f, time, 1.f, 0.f) * 5.f;

        if(speedClock.getElapsedTime().asSeconds() > time)
        {
            speedClock.restart();
            reachedTarget = true;
        }
    }
    else
    {
        sprite.setTexture(texture2);

        sf::Vector2f kierunek = statek.sprite.getPosition() - sprite.getPosition();
        float magnitude = sqrt((kierunek.x * kierunek.x) + (kierunek.y * kierunek.y));
        unitVector = sf::Vector2f(kierunek.x / magnitude, kierunek.y / magnitude);

        if(magnitude < 50)
            destroyed = true;

        unitVector *= (speed * Map(speedClock.getElapsedTime().asSeconds(), 0.f, time, 0.f, 1.0f) * 5.f) + (speedBonus * speed * Map(speedClock.getElapsedTime().asSeconds(), 0.f, time, 0.f, 1.0f) * 5.f);
    }
}

void saw::prepareToMove()
{
    shouldMove = sf::Vector2f(unitVector.x, unitVector.y) * timeModifier;
    moves = sqrt(pow(shouldMove.x, 2) + pow(shouldMove.y, 2)) / 5.f;
    doneMoves = 0;
}

bool saw::move()
{
    CalculateDirection();

    sprite.rotate(4);

    if(freeze)
        return true;

    if(doneMoves != moves)
    {
        sprite.move(shouldMove / (float) moves);
        doneMoves++;
        return false;
    }

    else
        return true;
}

void saw::load_texture(string dir)
{
    textureManager.add(dir + "texture.png", true);
    sprite.setTexture(*textureManager.get(dir + "texture.png"));

    textureManager.add(dir + "texture2.png", true);
    texture2 = *textureManager.get(dir + "texture2.png");
}

vector <saw> saws;
vector <bullet> pociski;

class rocket
{
private:
    float speed;
    float currentSpeed;
public:
    sf::Sprite sprite;
    animation explosion;

    bool hit = false;

    bool mine;
    int targetID;
    int damage;
    int mass;

    void create(sf::Vector2f start, int ID, float newSpeed, string dir);
    void move(sf::Vector2f target);
};

void rocket::create(sf::Vector2f start, int ID, float newSpeed, string dir)
{
    targetID = ID;
    speed = newSpeed;
    currentSpeed = speed / 3;

    textureManager.add(dir + "texture.png");
    sprite.setTexture(*textureManager.get(dir + "texture.png"));
    sprite.setOrigin(Collision::GetSpriteSize(sprite) / 2.f);
    sprite.setPosition(start);
}

void rocket::move(sf::Vector2f target)
{
    sf::Vector2f kierunek = target - sprite.getPosition();
    float magnitude = sqrt((kierunek.x * kierunek.x) + (kierunek.y * kierunek.y));
    sf::Vector2f unitVector = sf::Vector2f(kierunek.x / magnitude, kierunek.y / magnitude);

    unitVector *= currentSpeed;
    unitVector *= timeModifier;

    sprite.move(unitVector);

    sprite.setRotation(rotate_to_ff(sprite.getPosition(), target) + 180);

    if(currentSpeed < speed)
        currentSpeed += timeModifier / 10;
    else if(currentSpeed < speed * 2)
        currentSpeed += timeModifier / 20;
}
vector <rocket> rockets;

void ShotRocket(weapon W, bool Mine, int ID, sf::Vector2f start, bool * readyToShot)
{
    *readyToShot = false;

    rocket r;
    r.create(start, ID, W.speed, "assets/graphics/bullets/autoRockets/fly/");
    r.explosion.loadAnimation("assets/graphics/bullets/autoRockets/explosion.animation");
    r.damage = W.damage + ((random() % W.modifier) - W.modifier / 2);
    r.mass = W.mass;
    r.mine = Mine;

    rockets.push_back(r);
}

void ShotSaw(weapon W, bool Mine, sf::Vector2f cel, sf::Vector2f start, bool * readyToShot)
{
    int bullets = W.bulletsPerShot;
    int toShot = bullets;

    sf::Sound * boom = app.soundsManager.createSound(app.soundsManager.getIdByName("crossbow"));
    boom -> setPitch(static_cast<float>((rand() % 10) / 10) + 0.5f);
    boom -> play();

    for(int i = 0; i < toShot; i++)
    {
        if(Mine)
        {
            if(statek.ammo - W.ammoUsage <= 0)
            {
                statek.ammo = 0;
                break;
            }

            statek.ammo -= W.ammoUsage;
        }

        //bullet pocisk;
        saw pocisk;

        pocisk.mine = Mine;
        pocisk.damage = W.damage;
        pocisk.accuracy = W.accuracy;
        pocisk.modifier = W.modifier;
        pocisk.ammoUsage = W.ammoUsage;
        pocisk.mass = W.mass;
        pocisk.accuracyBonus = W.baseAccuracyBonus - i;
        pocisk.speed = W.speed;
        pocisk.bulletType = W.codeName;

        pocisk.start_x = start.x;
        pocisk.start_y = start.y;

        pocisk.cel_x = cel.x;
        pocisk.cel_y = cel.y;

        if(start.x <= cel.x)
            pocisk.Kierunek = true;

        if(start.x > cel.x)
            pocisk.Kierunek = false;

        pocisk.wybuch.loadAnimation("assets/graphics/bullets/"  + pocisk.bulletType +  "/explosion.animation");
        pocisk.load_texture("assets/graphics/bullets/" + pocisk.bulletType + "/fly/");


        pocisk.sprite.setOrigin(Collision::GetSpriteSize(pocisk.sprite).x / 2, Collision::GetSpriteSize(pocisk.sprite).y / 2);
        pocisk.sprite.setPosition(start);
        pocisk.rotator();
        pocisk.CalculateDirection();
        pocisk.preCalculating();

        saws.push_back(pocisk);
        saws[saws.size() - 1].speedClock.restart();
    }

    if(Mine and statek.ammo < 0)
        statek.ammo = 0;

    *readyToShot = false;
}

void Shot(weapon W, bool Mine, sf::Vector2f cel, sf::Vector2f start, bool * readyToShot)
{
    if(W.codeName == "saw")
    {
        ShotSaw(W, Mine, cel, start, readyToShot);
        return;
    }

    int bullets = W.bulletsPerShot;
    int toShot = bullets;

    sf::Sound * boom = app.soundsManager.createSound(app.soundsManager.getIdByName("crossbow"));
    boom -> setPitch(static_cast<float>((rand() % 10) / 10) + 0.5f);
    boom -> play();

    for(int i = 0; i < toShot; i++)
    {
        if(Mine)
        {
            if(statek.ammo - W.ammoUsage <= 0)
            {
                statek.ammo = 0;
                break;
            }

            statek.ammo -= W.ammoUsage;
        }

        //bullet pocisk;
        bullet pocisk;

        pocisk.mine = Mine;
        pocisk.damage = W.damage;
        pocisk.accuracy = W.accuracy;
        pocisk.modifier = W.modifier;
        pocisk.ammoUsage = W.ammoUsage;
        pocisk.mass = W.mass;
        pocisk.accuracyBonus = W.baseAccuracyBonus - i;
        pocisk.speed = W.speed;
        pocisk.bulletType = W.codeName;

        pocisk.start_x = start.x;
        pocisk.start_y = start.y;

        pocisk.cel_x = cel.x;
        pocisk.cel_y = cel.y;

        if(start.x <= cel.x)
            pocisk.Kierunek = true;

        if(start.x > cel.x)
            pocisk.Kierunek = false;

        pocisk.wybuch.loadAnimation("assets/graphics/bullets/"  + pocisk.bulletType +  "/explosion.animation");
        pocisk.load_texture("assets/graphics/bullets/" + pocisk.bulletType + "/fly/texture.png");


        pocisk.sprite.setOrigin(Collision::GetSpriteSize(pocisk.sprite).x / 2, Collision::GetSpriteSize(pocisk.sprite).y / 2);
        pocisk.sprite.setPosition(start);
        pocisk.rotator();
        pocisk.CalculateDirection();

        pociski.push_back(pocisk);
    }

    if(Mine and statek.ammo < 0)
        statek.ammo = 0;

    *readyToShot = false;
}

#endif // BULLETS_H_INCLUDED
