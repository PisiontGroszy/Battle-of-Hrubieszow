#ifndef NUMBERS_H_INCLUDED
#define NUMBERS_H_INCLUDED

class digit : public sf::Sprite
{
public:
    void load(string prefix, int number);

private:
    int value;
};

void digit::load(string prefix, int number)
{
    string tmp = prefix;

    tmp += (char) (number + 48);

    tmp += ".png";

    textureManager.add(tmp);

    setTexture(*textureManager.get(tmp));

    value = number;
}

class number : public sf::Drawable
{
public:
    void create(string Number, string digitsDir, float scale, sf::Vector2f position);
    void setNumber(string Number);
    void setPosition(sf::Vector2f position);
    void setAlpha(int alpha);
    void move(sf::Vector2f vect);

    sf::Vector2f getPosition();
    int getAlpha();

private:
    vector <digit> digits;
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

    sf::Vector2f currentPos;
    float Scale;
    string DigitsDir;
    int Alpha;
};

void number::create(string Number, string digitsDir, float scale, sf::Vector2f position)
{
    currentPos = position;
    Scale = scale;
    DigitsDir = digitsDir;

    for(unsigned int i = 0; i < Number.size(); i++)
    {
        digit tmp;

        digits.push_back(tmp);
        digits[digits.size() - 1].load(DigitsDir, Number[i] - 48);
        digits[digits.size() - 1].setScale(Scale, Scale);
        digits[digits.size() - 1].setPosition(currentPos);

        currentPos.x += digits[digits.size() - 1].getGlobalBounds().width;
    }

    Alpha = 255;
    currentPos = position;
}

void number::setNumber(string Number)
{
    sf::Vector2f tmpPos = currentPos;

    digits.clear();

    for(unsigned int i = 0; i < Number.size(); i++)
    {
        digit tmp;

        digits.push_back(tmp);
        digits[digits.size() - 1].load(DigitsDir, Number[i] - 48);
        digits[digits.size() - 1].setScale(Scale, Scale);
        digits[digits.size() - 1].setPosition(tmpPos);

        tmpPos.x += digits[digits.size() - 1].getGlobalBounds().width;
    }
}

void number::setPosition(sf::Vector2f position)
{
    currentPos = position;
    sf::Vector2f tmpPos = currentPos;

    for(unsigned int i = 0; i <= digits.size() - 1; i++)
    {
        digits[i].setPosition(tmpPos);

        tmpPos.x += digits[i].getGlobalBounds().width;
    }
}

void number::setAlpha(int alpha)
{
    if(alpha > 255)
        alpha = 255;
    else if(alpha < 0)
        alpha = 0;

    for(unsigned int i = 0; i <= digits.size() - 1; i++)
    {
        digits[i].setColor(sf::Color(255, 255, 255, alpha));
    }
    Alpha = alpha;
}

void number::move(sf::Vector2f vect)
{
    setPosition(currentPos + vect);
}

sf::Vector2f number::getPosition()
{
    return digits[0].getPosition();
}

int number::getAlpha()
{
    return Alpha;
}

void number::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    for(int i = digits.size() - 1; i >= 0; i--)
        target.draw(digits[i], states);
}

vector <number> damageInfo;

#endif // NUMBERS_H_INCLUDED
