#ifndef ENEMIES_H_INCLUDED
#define ENEMIES_H_INCLUDED

class enemy
{
public:
    weapon Weapon;

    int XP;
    int HP;
    int oldHP;
    int fullHP;
    float fightCounter;
    int fireRating;

    int ID;

    float momentum;
    float speed;
    float defaultSpeed;
    void move();
    void rotate();
    void load_textures(string dir);
    sf::Texture texture;
    sf::Sprite sprite;

    bool destroyed;
    bool killed;
    bool error = false;

    string tekstura;
    string baseTexture;
    void fight_manager();

    sf::Vector2f lastOkPos;
    sf::Vector2f target;
    sf::Vector2f avoid1;
    bool shouldAvoid1 = false;

    animation wybuch;
    animation eksplozja;

    bool onScreen;
    bool startExplosion = false;

    //Oznaczenie
    sf::CircleShape circle;
    sf::Sprite arr[3];

    float arrowAngle = 0.f;
    float arrowDistance = 0.f;

    float radiaus;

    bool getBigger = true;
    bool selected = false;
    //----------

    void takeDamage(int damage);

private:
    sf::Vector2f finalMomentum;
    bool Good;
    int Error_code;
    bool ready_to_shot = false;
};

void enemy::load_textures(string dir)
{
    finalMomentum = sf::Vector2f(0, 0);

    textureManager.add(dir, true);
    sprite.setTexture(*textureManager.get(dir));
    tekstura = dir;

    textureManager.add("assets/graphics/drone/selected.png", true);

    for(int i = 0; i < 3; i++)
    {
        arr[i].setTexture(*textureManager.get("assets/graphics/drone/selected.png"));
        arr[i].setOrigin(Collision::GetSpriteSize(arr[i]) / 2.f);
        arr[i].setScale(0.6f, 0.6f);
    }

    circle.setPointCount(64);
    circle.setFillColor(sf::Color(255, 255, 255, 0));
    circle.setOutlineColor(sf::Color(255, 0, 0));
    circle.setOutlineThickness(3);

    radiaus = max(Collision::GetSpriteSize(sprite).x, Collision::GetSpriteSize(sprite).y) * 0.6;
}

void enemy::move()
{
    onScreen = (sprite.getPosition().x > screenCornerX and sprite.getPosition().y > screenCornerY and sprite.getPosition().x < screenX + screenCornerX and sprite.getPosition().y < screenY + screenCornerY);

    if(killed)
        return;

    sf::Vector2f kierunek = statek.sprite.getPosition() - sprite.getPosition();
    float distance = sqrt((kierunek.x * kierunek.x) + (kierunek.y * kierunek.y));

    sprite.setOrigin(Collision::GetSpriteSize(sprite).x / 2, Collision::GetSpriteSize(sprite).y / 2);

    if(!statek.destroyed)
    {
        if(distance > screenX/5)
        {
            if(momentum < 1)
                momentum += 0.05f;

            sf::Vector2f kierunek = target - sprite.getPosition();
            float magnitude = sqrt((kierunek.x * kierunek.x) + (kierunek.y * kierunek.y));
            sf::Vector2f unitVector(kierunek.x / magnitude, kierunek.y / magnitude);

            finalMomentum += (unitVector * speed * momentum * timeModifier);
        }

        if(distance < screenX/5 and distance > screenX/6)
        {
            if(momentum > 0.005f)
                momentum -= 0.005f;

            sf::Vector2f kierunek = target - sprite.getPosition();
            float dystans = sqrt((kierunek.x * kierunek.x) + (kierunek.y * kierunek.y));
            sf::Vector2f unitVector(kierunek.x / dystans, kierunek.y / dystans);

            float speedModifier = (screenX/5 - screenX/10) / dystans;

            unitVector *= speedModifier;

            finalMomentum += (unitVector * speed * momentum * timeModifier);
        }

        if(distance < screenX/7)
        {
            sf::Vector2f kierunek = target - sprite.getPosition();
            float dystans = sqrt((kierunek.x * kierunek.x) + (kierunek.y * kierunek.y));
            sf::Vector2f unitVector(-(kierunek.x / dystans), -(kierunek.y / dystans));
            finalMomentum += (unitVector * speed * timeModifier);
        }


        if(shouldAvoid1)
        {
            sf::Vector2f kierunek = avoid1 - sprite.getPosition();
            float magnitude = sqrt((kierunek.x * kierunek.x) + (kierunek.y * kierunek.y));
            sf::Vector2f unitVector(kierunek.x / magnitude, kierunek.y / magnitude);

            unitVector = sf::Vector2f(-unitVector.x, -unitVector.y);

            if(unitVector.x == unitVector.x)
                finalMomentum += (unitVector * speed * 0.5f * timeModifier);
        }

        sprite.move(finalMomentum);
        finalMomentum = sf::Vector2f(0, 0);
    }

    if(sprite.getPosition().x != sprite.getPosition().x)
        error = true;
    else
        lastOkPos = sprite.getPosition();

    //Oznaczenia
    if(selected)
    {
        if(arrowDistance < 20.f and getBigger)
            arrowDistance += 0.5f;
        else if(arrowDistance >= 20.f and getBigger)
            getBigger = false;
        else if(arrowDistance > 0.f and !getBigger)
            arrowDistance -= 0.5f;
        else if(arrowDistance <= 0.f and !getBigger)
            getBigger = true;

        circle.setRadius(radiaus + arrowDistance);
        circle.setOrigin(radiaus + arrowDistance, radiaus + arrowDistance);
        circle.setPosition(sprite.getPosition());

        app << circle;

        for(int i = 0; i < 3; i++)
        {
            arr[i].setPosition(onCircle(sprite.getPosition(), radiaus + arrowDistance - 9.f, arrowAngle + 120.f * i));
            arr[i].setRotation(rotate_to_ff(arr[i].getPosition(), sprite.getPosition()) + 90);

            app << arr[i];
        }

        arrowAngle += timeModifier;
    }
    //----------
}

void enemy::rotate()
{
    if(killed)
        return;

    sf::Vector2f kierunek = sprite.getPosition() - statek.sprite.getPosition();
    float distance = sqrt((kierunek.x * kierunek.x) + (kierunek.y * kierunek.y));

    target = statek.sprite.getPosition();
    target -= direction * static_cast <float> (distance / (timeModifier * 30));

    float rotation = rotate_to_ff(sprite.getPosition(), target) - sprite.getRotation();

    if(rotation < 180)
        rotation += 360;
    if(rotation > 180)
        rotation -= 360;

    float rotationSpeedLimit = 5.f * timeModifier;

    if(rotation > rotationSpeedLimit)
        rotation = rotationSpeedLimit;
    else if(rotation < -rotationSpeedLimit)
        rotation = -rotationSpeedLimit;


    sprite.rotate(rotation);
}

void enemy::fight_manager()
{
    if(killed)
        return;

    fightCounter += timeModifier;
    if(fightCounter >= fireRating)
    {
        ready_to_shot = true;
        fightCounter = 0.f;
    }

    if(ready_to_shot and sprite.getPosition().x < screenX * 1.5 + screenCornerX - 50 and sprite.getPosition().x > screenCornerX + 50 - screenX / 2 and sprite.getPosition().y > screenCornerY + 50 - screenY / 2 and sprite.getPosition().y < screenY * 1.5 + screenCornerY - 100 and !statek.destroyed)
        Shot(Weapon, false, target, sprite.getPosition(), &ready_to_shot);
}

void enemy::takeDamage(int damage)
{
    if(HP - damage < 0)
        damage = HP + 1;

    stringstream damageSS;
    damageSS << -damage;

    number tmpNum;
    damageInfo.push_back(tmpNum);
    damageInfo[damageInfo.size() - 1].create(damageSS.str(), "assets/graphics/digits/", 1.6f, sprite.getPosition());

    HP -= damage;
    if(HP < 0 and !killed)
    {
        killed = true;

        for(int i = 0; i < XP; i++)
        {
            soul tmpSoul(sprite.getPosition() + sf::Vector2f(i * 50, 0));
            souls.push_back(tmpSoul);
        }
    }
}

vector <enemy> enemies;

int Counter = 0;
int i = 0;
bool nextEnemy;
int CtrlNumber = 0;
int generated_enemies = 0;
int baseEnemiesLimit = 1;

weapons enemyWeapons;

int moreEnemies(int Generated_enemies)
{
    if(Generated_enemies < 3)
        return 0;
    else if(Generated_enemies >= 3 and Generated_enemies < 10)
        return 1;
    else if(Generated_enemies >= 10 and Generated_enemies < 25)
        return 2;
    else if(Generated_enemies >= 25 and Generated_enemies < 50)
        return 3;
    else if(Generated_enemies >= 50 and Generated_enemies < 90)
        return 4;
    else
        return 4 + (Generated_enemies - 90) / 50;
}

void enemyGenerator()
{
    unsigned int enemies_limit = baseEnemiesLimit + moreEnemies(generated_enemies);

    if(enemies_limit > enemies.size() or baseEnemiesLimit == -1)
    {
        if(!nextEnemy and CtrlNumber < 200)
            CtrlNumber++;
        else
        {
            nextEnemy = true;
            CtrlNumber = 0;
        }

        if(nextEnemy)
        {
            enemy Enemy;
            enemyWeapons.select(0);
            Enemy.Weapon = enemyWeapons.top();

            Enemy.ID = generated_enemies;
            Enemy.baseTexture = "assets/graphics/enemies/standard/";
            Enemy.speed = 2.f + (0.1f * generated_enemies);
            Enemy.defaultSpeed = Enemy.speed;

            int baseHP = 200 + generated_enemies * 10;

            Enemy.HP = baseHP;
            Enemy.XP = 1;
            Enemy.fightCounter = 0;

            //Do usunięcia
            Enemy.fireRating = 101 - Enemy.Weapon.agility;
            //------------

            Enemy.oldHP = 0;
            Enemy.fullHP = baseHP;
            Enemy.destroyed = false;
            Enemy.killed = false;
            Enemy.wybuch.loadAnimation("assets/graphics/spaceship/destroy.animation");
            Enemy.eksplozja.loadAnimation("assets/graphics/spaceship/blood.animation");

            int strona = random() % 4;
            switch(strona)
            {
                case 0:
                    Enemy.sprite.setPosition(screenX+300 + screenCornerX, random() % screenY + screenCornerY + 1);
                    break;

                case 1:
                    Enemy.sprite.setPosition(-300 + screenCornerX, random() % screenY + screenCornerY + 1);
                    break;

                case 2:
                    Enemy.sprite.setPosition(random() % screenX + screenCornerX + 1, -300  + screenCornerY);
                    break;

                case 3:
                    Enemy.sprite.setPosition(random() % screenX + screenCornerX + 1, screenY + 300 + screenCornerY);
                    break;
            };

            Enemy.load_textures(Enemy.baseTexture + "a.png");

            enemies.push_back(Enemy);
            generated_enemies++;
        }
    }
}

#endif // ENEMIES_H_INCLUDED
