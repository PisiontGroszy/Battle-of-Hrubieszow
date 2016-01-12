#ifndef WEAPONS_H_INCLUDED
#define WEAPONS_H_INCLUDED

class weapon
{
public:
    string codeName;

    int accuracy;
    int damage;
    int agility;
    int baseAccuracyBonus;
    int speed;
    int ammoUsage;
    int modifier;
    int bulletsPerShot;
    int mass;
};

class weapons
{
private:
    xml::xmlDocument * document;
    unsigned int currentWeapon = 0;
public:
    vector <weapon> Weapons;

    void loadFromFile(string file);
    weapon top();
    bool previous();
    bool next();
    void select(int n);
};

void weapons::select(int n)
{
    currentWeapon = n;
}

bool weapons::previous()
{
    if(currentWeapon > 0)
    {
        currentWeapon--;
        return true;
    }
    else
    {
        currentWeapon = Weapons.size() - 1;
        return false;
    }
}
bool weapons::next()
{
    if(currentWeapon < Weapons.size() - 1)
    {
        currentWeapon++;
        return true;
    }
    else
    {
        currentWeapon = 0;
        return false;
    }
}

void weapons::loadFromFile(string file)
{
    document = new xml::xmlDocument(file);

    xml_node<> *Root = document -> getRootNode();
    xml_node<> *weaponNode = Root -> first_node("weapon");

    while(weaponNode != NULL)
    {
        weapon tmpWeapon;
        tmpWeapon.baseAccuracyBonus = atoi(xml::getNodeAttribute(weaponNode, "accuracyBonus").c_str());
        tmpWeapon.bulletsPerShot = atoi(xml::getNodeAttribute(weaponNode, "bulletsPerShot").c_str());
        tmpWeapon.ammoUsage = atoi(xml::getNodeAttribute(weaponNode, "ammoUsage").c_str());
        tmpWeapon.accuracy = atoi(xml::getNodeAttribute(weaponNode, "accuracy").c_str());
        tmpWeapon.modifier = atoi(xml::getNodeAttribute(weaponNode, "modifier").c_str());
        tmpWeapon.agility = atoi(xml::getNodeAttribute(weaponNode, "fireRate").c_str());
        tmpWeapon.damage = atoi(xml::getNodeAttribute(weaponNode, "damage").c_str());
        tmpWeapon.speed = atoi(xml::getNodeAttribute(weaponNode, "speed").c_str());
        tmpWeapon.mass = atoi(xml::getNodeAttribute(weaponNode, "mass").c_str());

        tmpWeapon.codeName = xml::getNodeAttribute(weaponNode, "codeName");

        weaponNode = weaponNode -> next_sibling();
        Weapons.push_back(tmpWeapon);
    }
    currentWeapon = 0;
}

weapon weapons::top()
{
    return Weapons[currentWeapon];
}
bool Ready_to_shot = false;

class laser
{
public:
    sf::Sprite sprite;
    sf::Vector2f cel;
    sf::Vector2f collisionPoint;
    sf::Vector2f start;
    sf::Vector2f unitVector;
    weapon info;

    int collision(vector <sf::Sprite> & Wrogowie, vector <string> & WrogowieT, vector <int> & IDs);

    void load(sf::Vector2f Start, weapon Info);
    void setTarget(sf::Vector2f coords);
    void calculateTransform();
};

int laser::collision(vector <sf::Sprite> & Wrogowie, vector <string> & WrogowieT, vector <int> & IDs)
{
    int i = -1;

    sf::Sprite testRay = sprite;
    testRay.setPosition(start);
    testRay.setScale(2000, 1);
    testRay.setOrigin(0, 4);
    testRay.setRotation(rotate_to_ff(testRay.getPosition(), kursor.sprite.getPosition()));

    bool collision = false;
    sf::Sprite object;

    while(Wrogowie.size() > 0)
    {
        Wrogowie[Wrogowie.size() - 1].setTexture(*textureManager.get(WrogowieT[WrogowieT.size() - 1]));

        if(Collision::PixelPerfectTest(Wrogowie[Wrogowie.size() - 1], testRay))
        {
            collision = true;
            i = IDs[IDs.size() - 1];
            object = Wrogowie[Wrogowie.size() - 1];
        }

        IDs.pop_back();
        WrogowieT.pop_back();
        Wrogowie.pop_back();
    }

    if(collision)
    {
        testRay = sprite;
        testRay.setScale(20, 1);
        testRay.setPosition(start);
        testRay.setOrigin(0, 4);
        testRay.setRotation(rotate_to_ff(testRay.getPosition(), kursor.sprite.getPosition()));

        sf::Vector2f kierunek = sprite.getPosition() - cel;
        float magnitude = sqrt((kierunek.x * kierunek.x) + (kierunek.y * kierunek.y));
        unitVector = sf::Vector2f(kierunek.x / magnitude, kierunek.y / magnitude);

        for(int movedXTimes = 0; !Collision::PixelPerfectTest(testRay, object) and movedXTimes < 120; movedXTimes++)
        {
            testRay.move(unitVector * 10.f);
            app << testRay;
        }

        collisionPoint = testRay.getPosition();
    }
    else
        app << testRay;

    testRay.setOrigin(5999, 4);
    collisionPoint = testRay.getPosition();
    return i;
}

void laser::load(sf::Vector2f Start, weapon Info)
{
    info = Info;
    textureManager.add("assets/graphics/bullets/laser/fly/texture.png", true);
    sprite.setTexture(*textureManager.get("assets/graphics/bullets/laser/fly/texture.png"));
    start = Start;
}

void laser::setTarget(sf::Vector2f coords)
{
    sf::Sprite tmp;
    tmp.setPosition(start);

    sf::Vector2f kierunek = start - coords;
    float magnitude = sqrt((kierunek.x * kierunek.x) + (kierunek.y * kierunek.y));
    sf::Vector2f unitVector = sf::Vector2f(kierunek.x / magnitude, kierunek.y / magnitude);
    unitVector *= 25.f;

    for(int i = 0; i < 500; i++)
        tmp.move(unitVector);

    cel = tmp.getPosition();
}

void laser::calculateTransform()
{
    sf::Vector2f kierunek = cel - collisionPoint;
    int magnitude = sqrt((kierunek.x * kierunek.x) + (kierunek.y * kierunek.y));
    sprite.setScale(magnitude, 1);
    sprite.setOrigin(0, 4);
    sprite.setPosition(start);
    sprite.setRotation(rotate_to_ff(sprite.getPosition(), kursor.sprite.getPosition()));
}

#endif // WEAPONS_H_INCLUDED
