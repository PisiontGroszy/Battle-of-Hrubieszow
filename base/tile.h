#ifndef TILE_H_INCLUDED
#define TILE_H_INCLUDED

class tile : public sf::Drawable
{
private:
    sf::Sprite a, b, c, d;
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

public:
    void load(string pass, int alpha);
    void setPosition(sf::Vector2f vect);
    void setPosition(float _x, float _y);

    void move(float _x, float _y);
};

void tile::load(string pass, int alpha)
{
    textureManager.add("assets/graphics/background/" + pass + "/a.png");
    a.setTexture(*textureManager.get("assets/graphics/background/" + pass + "/a.png"));
    a.setColor(sf::Color(255, 255, 255, alpha));

    textureManager.add("assets/graphics/background/" + pass + "/b.png");
    b.setTexture(*textureManager.get("assets/graphics/background/" + pass + "/b.png"));
    b.setColor(sf::Color(255, 255, 255, alpha));

    textureManager.add("assets/graphics/background/" + pass + "/c.png");
    c.setTexture(*textureManager.get("assets/graphics/background/" + pass + "/c.png"));
    c.setColor(sf::Color(255, 255, 255, alpha));

    textureManager.add("assets/graphics/background/" + pass + "/d.png");
    d.setTexture(*textureManager.get("assets/graphics/background/" + pass + "/d.png"));
    d.setColor(sf::Color(255, 255, 255, alpha));
}

void tile::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    target.draw(a, states);
    target.draw(b, states);
    target.draw(c, states);
    target.draw(d, states);
}

void tile::setPosition(sf::Vector2f vect)
{
    a.setPosition(vect + sf::Vector2f(0, -750));
    b.setPosition(vect + sf::Vector2f(750, -750));
    c.setPosition(vect);
    d.setPosition(vect + sf::Vector2f(750, 0));
}
void tile::setPosition(float _x, float _y)
{
    sf::Vector2f vect(_x, _y);
    setPosition(vect);
}

void tile::move(float _x, float _y)
{
    sf::Vector2f vect(_x, _y);

    a.move(vect);
    b.move(vect);
    c.move(vect);
    d.move(vect);
}

tile mapTile;
tile map2Tile;
tile map3Tile;
#endif // TILE_H_INCLUDED
