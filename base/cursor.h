#ifndef CURSOR_H_INCLUDED
#define CURSOR_H_INCLUDED

class cursor : public sf::Drawable
{
public:
    void hitInFrame();
    void manageHit();

    void init(char * cursorFile);
    void setTexture(char * cursorFile);

    void LowAmmo(int current, int maximum);
    void HighAmmo(int current, int maximum);

    sf::Sprite sprite;

    bool lowAmmo = false;
    bool highAmmo = true;

    sf::Texture lowAmmoTexture;
    sf::Sprite lowAmmoSprite;

    sf::Texture highAmmoTexture;
    sf::Sprite highAmmoSprite;

    sf::Texture hitTexture;
    sf::Sprite hitSprite;

private:
    bool hit = false;
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
    sf::Texture texture;
    float a = 0.f;
};

void cursor::hitInFrame()
{
    hit = true;
}

void cursor::manageHit()
{
    if(hit)
    {
        hitSprite.setColor(sf::Color(255, 255, 255, 255));
        hit = false;
    }
    else if(hitSprite.getColor().a > 0)
    {
        int currentAlpha = hitSprite.getColor().a;
        a += timeModifier;
        while(a > 1)
        {
            currentAlpha -= 15;
            a -= 15;
        }
        if(a < 0)
            a = 0;

        if(currentAlpha < 0)
            currentAlpha = 0;

        hitSprite.setColor(sf::Color(255, 255, 255, currentAlpha));
    }
    hitSprite.setPosition(sprite.getPosition());
    hitSprite.setRotation(sprite.getRotation());
}

void cursor::LowAmmo(int current, int maximum)
{
    lowAmmoSprite.setPosition(sprite.getPosition());
    lowAmmoSprite.setRotation(sprite.getRotation());

    double ammoLimit = 0.3 * maximum;
    double ammoPseudoPercentage = static_cast <float> (current) / ammoLimit;
    ammoPseudoPercentage *= 255;

    lowAmmoSprite.setColor(sf::Color(255, 255, 255, 255 - ammoPseudoPercentage));
}

void cursor::HighAmmo(int current, int maximum)
{
    highAmmoSprite.setPosition(sprite.getPosition());
    highAmmoSprite.setRotation(sprite.getRotation());

    double pseudoAmmo = current - (0.7 * maximum);
    double pseudoAmmoMax = maximum - (0.7 * maximum);

    double ammoPseudoPercentage = static_cast <float> (pseudoAmmo) / pseudoAmmoMax;
    ammoPseudoPercentage *= 255;

    highAmmoSprite.setColor(sf::Color(255, 255, 255, ammoPseudoPercentage));
}

void cursor::init(char * cursorFile)
{
    app.setMouseCursorVisible(false);
    textureManager.add(cursorFile, true);
    sprite.setScale(settings.getCursorScale());
}

void cursor::setTexture(char * cursorFile)
{
    sprite.setTexture(*textureManager.get(cursorFile));
    sprite.setOrigin((Collision::GetSpriteSize(sprite).x / sprite.getScale().x / 2), (Collision::GetSpriteSize(sprite).y / sprite.getScale().y / 2));
    sprite.rotate(-90);
    sprite.setColor(sf::Color(255, 255, 255, settings.getCursorAplha()));
}

void cursor::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    target.draw(sprite, states);
    target.draw(hitSprite, states);
}
cursor kursor;

#endif // CURSOR_H_INCLUDED
