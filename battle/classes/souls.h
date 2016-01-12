#ifndef SOULS_H_INCLUDED
#define SOULS_H_INCLUDED

class soul
{
public:
    sf::Texture texture;
    sf::Sprite sprite;

    int XP = 1;

    soul(sf::Vector2f Coords);

    void move(sf::Sprite & Cel);
};

void soul::move(sf::Sprite & cel)
{
    sf::Vector2f currentPos = sprite.getPosition();
    sf::Vector2f kierunek = cel.getPosition() - currentPos;
    float magnitude = sqrt((kierunek.x * kierunek.x) + (kierunek.y * kierunek.y));
    sf::Vector2f unitVector = sf::Vector2f(kierunek.x / magnitude, kierunek.y / magnitude);
    unitVector *= static_cast <float> (statek.baseMovingSpeed) * 1.2f;
    unitVector *= timeModifier;

    for(int meteorTabPos = meteors.size() - 1; meteorTabPos >= 0; meteorTabPos--)
    {
        if(meteors[meteorTabPos].contains(currentPos + unitVector, 20))
            return;
    }

    sprite.move(unitVector);
}

soul::soul(sf::Vector2f Coords)
{
    sprite.setPosition(Coords);
}
vector <soul> souls;

struct fakeSoul
{
    sf::Sprite sprite;
    sf::Texture texture;
};

class soulsAddons
{
public:
    sf::Vector2f pos;
    float alpha = 0.f;
    fakeSoul soulCopy;
};
vector <soulsAddons> soulAddons;

#endif // SOULS_H_INCLUDED
