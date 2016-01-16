#ifndef SPACEOBJECTS_H_INCLUDED
#define SPACEOBJECTS_H_INCLUDED

namespace space
{
    class meteorPart
    {
    public:

        sf::Color color;
        sf::CircleShape hexagon;

        bool right = true;
        bool left = true;
        bool upDown = true;
        bool Rotated;

        int HP;

        void create(sf::Color mask, sf::Vector2f pos, bool rotated, int polygons, int hp);
    };

    void meteorPart::create(sf::Color mask, sf::Vector2f pos, bool rotated, int polygons, int hp)
    {
        hexagon = sf::CircleShape(29, polygons);
        hexagon.setFillColor(mask);
        hexagon.setOrigin(20, 29);
        hexagon.setPosition(pos);
        Rotated = rotated;
        HP = hp;

        hexagon.setRotation((int) rotated * 60);
    }

    class meteor : public sf::Drawable
    {
    public:
        vector <meteorPart> meteorParts;

        void startCreating(int m, sf::Vector2f Pos, int Polygons);
        void create();
        void update();
        void destroy();

        void setColor(sf::Color color);
        void move(sf::Vector2f vect);
        void move(float x, float y);
        void move();

        void push(sf::Vector2f vect, int mass);

        bool contains(sf::Vector2f point, int damage);

        sf::Color getColor();
        sf::Vector2f getPosition();

        bool created = false;
        bool creating = false;
        bool destroyed = false;
        bool moving;

        sf::Vector2f pos;

        float momentumX;
        float momentumY;
    private:
        sf::Text HP;
        sf::Text Size;
        sf::Uint32 fullHP;

        sf::Sprite sprite;
        sf::FloatRect rect;
        sf::Uint8 parts = 16;

        virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

        unsigned int targetParts = 0;
        unsigned int currentParts = 0;
        unsigned int polygons;

        unsigned int HPPerPart = 40;

        int poz1P[2] = {29, -22};
        int poz1L[2] = {-20, -22};
        int poz1B[2] = {4, 21};

        int poz2P[2] = {20, 22};
        int poz2L[2] = {-29, 22};
        int poz2U[2] = {-4, -21};
    };

    void meteor::startCreating(int m, sf::Vector2f Pos, int Polygons)
    {
        targetParts = m;
        pos = Pos;
        polygons = Polygons;
        created = false;
        creating = true;

        moving = false;
        momentumX = 0.f;
        momentumY = 0.f;

        HP.setFont(bitFont);
        Size.setFont(bitFont);

        HP.setCharacterSize(70);
        Size.setCharacterSize(90);
    }

    void meteor::create()
    {
        if(currentParts == targetParts)
        {
            created = true;
            creating = false;
            return;
        }

        for(unsigned int i = 0; i < parts and currentParts < targetParts; i++)
        {
            if(currentParts == 0)
            {
                int i = 85;
                meteorPart tmp;
                meteorParts.push_back(tmp);
                meteorParts[meteorParts.size() - 1].create(sf::Color(i, i, i, 50), pos, true, polygons, HPPerPart);
                currentParts++;
            }
            else
            {
                for(bool done = false; !done;)
                {
                    int addTo = random() % currentParts;

                    if(meteorParts[addTo].right or meteorParts[addTo].left or meteorParts[addTo].upDown)
                    {
                        bool rotated = !meteorParts[addTo].Rotated;
                        sf::Vector2f pos = meteorParts[addTo].hexagon.getPosition();

                        int strona = addTo % 3;

                        for(bool Done = false; !Done;)
                        {
                            if(strona == 0)
                            {
                                if(!meteorParts[addTo].right)
                                    strona++;

                                else
                                {
                                    if(meteorParts[addTo].Rotated)
                                    {
                                        pos.x += poz2P[0];
                                        pos.y += poz2P[1];
                                    }
                                    else
                                    {
                                        pos.x += poz1P[0];
                                        pos.y += poz1P[1];
                                    }
                                    meteorParts[addTo].right = false;
                                    Done = true;
                                }
                            }
                            else if(strona == 1)
                            {
                                if(!meteorParts[addTo].left)
                                    strona++;

                                else
                                {
                                    if(meteorParts[addTo].Rotated)
                                    {
                                        pos.x += poz2L[0];
                                        pos.y += poz2L[1];
                                    }
                                    else
                                    {
                                        pos.x += poz1L[0];
                                        pos.y += poz1L[1];
                                    }
                                    meteorParts[addTo].left = false;
                                    Done = true;
                                }
                            }
                            else if(strona == 2)
                            {
                                if(!meteorParts[addTo].upDown)
                                    strona = 0;

                                else
                                {
                                    if(meteorParts[addTo].Rotated)
                                    {
                                        pos.x += poz2U[0];
                                        pos.y += poz2U[1];
                                    }
                                    else
                                    {
                                        pos.x += poz1B[0];
                                        pos.y += poz1B[1];
                                    }
                                    meteorParts[addTo].upDown = false;
                                    Done = true;
                                }
                            }
                        }

                        int i = 85;
                        meteorPart tmp;
                        meteorParts.push_back(tmp);
                        meteorParts[currentParts].create(sf::Color(i, i, i, 50), pos, rotated, polygons, HPPerPart);

                        if(strona == 0)
                            meteorParts[currentParts].left = false;
                        else if(strona == 1)
                            meteorParts[currentParts].right = false;
                        else if(strona == 2)
                            meteorParts[currentParts].upDown = false;

                        currentParts++;
                        done = true;
                    }
                }
            }
        }
        if(currentParts == targetParts)
            update();
    }

    void meteor::draw(sf::RenderTarget& target, sf::RenderStates states) const
    {
        for(unsigned int i = 0; i < currentParts; i++)
            target.draw(meteorParts[i].hexagon, states);

        target.draw(HP, states);
        target.draw(Size, states);
    }

    void meteor::destroy()
    {
        meteorParts.clear();
        currentParts = 0;
        destroyed = true;
    }

    void meteor::move(sf::Vector2f vect)
    {
        for(unsigned int i = 0; i < currentParts; i++)
            meteorParts[i].hexagon.setPosition(meteorParts[i].hexagon.getPosition() + vect);

        update();
        pos += vect;
    }

    void meteor::move(float x, float y)
    {
        move(sf::Vector2f(x, y));
    }

    void meteor::move()
    {
        move(momentumX, momentumY);
    }

    void meteor::push(sf::Vector2f vect, int mass)
    {
        momentumX += (vect.x * mass) / ((currentParts + 50) * 15);
        momentumY += (vect.y * mass) / ((currentParts + 50) * 15);

        moving = true;
    }

    void meteor::setColor(sf::Color color)
    {
        for(unsigned int i = 0; i < currentParts; i++)
            meteorParts[i].hexagon.setFillColor(color);
    }

    sf::Color meteor::getColor()
    {
        return meteorParts[0].hexagon.getFillColor();
    }

    sf::Vector2f meteor::getPosition()
    {
        return pos;
    }

    bool meteor::contains(const sf::Vector2f point, int damage)
    {
        if(rect.contains(point))
        {
            bool any = false;

            for(int i = meteorParts.size() - 1; i >= 0; i--)
            {
                if(meteorParts[i].hexagon.getGlobalBounds().contains(point))
                {
                    meteorParts[i].HP -= damage;

                    if(meteorParts[i].HP <= 0)
                    {
                        meteorParts.erase(meteorParts.begin() + i);
                        currentParts--;
                    }

                    any = true;
                    break;
                }
            }

            if(meteorParts.size() == 0)
                destroy();

            return any;
        }
        else
            return false;
    }

    void meteor::update()
    {
        int top = pos.y;
        int bottom = pos.y;
        int right = pos.x;
        int left = pos.x;

        for(unsigned int i = 0; i < currentParts; i++)
        {
            sf::Vector2f tmp = meteorParts[i].hexagon.getPosition();
            if(tmp.y < top)
                top = tmp.y;
            if(tmp.y > bottom)
                bottom = tmp.y;

            if(tmp.x < left)
                left = tmp.x;
            if(tmp.x > right)
                right = tmp.x;
        }

        rect.top = top - 30;
        rect.height = (bottom - top) + 30;

        rect.left = left - 30;
        rect.width = (right - left) + 30;

        ostringstream HPss, SizeSS;
        sf::Uint32 tmp = 0;
        for(unsigned int i = 0; i < currentParts; i++)
            tmp += meteorParts[i].HP;
        HPss << tmp / 1000 << "kHP";
        SizeSS << currentParts;

        HP.setString(HPss.str());
        Size.setString(SizeSS.str());

        HP.setOrigin(HP.getGlobalBounds().width / 2, HP.getGlobalBounds().height / 2);
        Size.setOrigin(Size.getGlobalBounds().width / 2, Size.getGlobalBounds().height / 2);

        Size.setPosition(rect.left + (rect.width / 2), rect.top + (rect.height / 2) - 35);
        HP.setPosition(rect.left + (rect.width / 2), rect.top + (rect.height / 2) + 35);
    }
    bool anyCreating = false;

    class blackHole : public sf::Drawable
    {
    private:
        sf::Sprite sprite;
        virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
    public:
        const float mass = 16.f;
        blackHole(sf::Vector2f pos, sf::Texture * tex);
        sf::Vector2f getPosition();
    };

    blackHole::blackHole(sf::Vector2f pos, sf::Texture * tex)
    {
        sprite.setTexture(*tex);
        sprite.setOrigin(Collision::GetSpriteSize(sprite).x / 2, Collision::GetSpriteSize(sprite).y / 2);
        sprite.setPosition(pos);
    }

    void blackHole::draw(sf::RenderTarget& target, sf::RenderStates states) const
    {
        target.draw(sprite, states);
    }
    sf::Vector2f blackHole::getPosition(){return sprite.getPosition();}

    bool createBlackHole = false;
}
vector <space::meteor> meteors;
vector <space::blackHole> blackHoles;

#endif // SPACEOBJECTS_H_INCLUDED
