#ifndef ANIMATION_H_INCLUDED
#define ANIMATION_H_INCLUDED

void loadAnimationTextures(string file)
{
    int useless;
    int frames;
    string dir;
    bool smooth;
    ifstream animationFile(file.c_str());
    animationFile >> frames >> useless >> useless >> smooth >> dir;

    for(int i = 0; i < frames; i++)
    {
        string tmp;
        animationFile >> tmp;
        textureManager.add(dir + tmp, smooth);
    }
}

class animation
{
private:
    int lastFrame;
    int iterationsPerFrame;
    bool alphaLast;
    float controlNumber;

    sf::advencedTexture ** T;
    string * textures;
    string dir;
public:
    int frames;
    int currentAlpha;
    int currentFrame;
    bool finished = false;

    sf::Sprite currentFrameSprite;

    int play(sf::Vector2f Pos, float rotation);
    void loadAnimation(string file);
};

void animation::loadAnimation(string file)
{
    lastFrame = -1;
    currentAlpha = 255;
    currentFrame = 0;
    bool smooth;

    ifstream animationFile(file.c_str());
    animationFile >> frames >> iterationsPerFrame >> alphaLast >> smooth >> dir;

    textures = new string[frames];
    T = new sf::advencedTexture*[frames];
    for(int i = 0; i < frames; i++)
    {
        animationFile >> textures[i];
        T[i] = textureManager.get(dir + textures[i]);
    }

    currentFrameSprite.setTexture(*T[0]);
    currentFrameSprite.setOrigin(Collision::GetSpriteSize(currentFrameSprite).x / 2, Collision::GetSpriteSize(currentFrameSprite).y / 2);
}

int animation::play(sf::Vector2f Pos, float rotation)
{
    if(currentFrame < frames)
    {
        if(lastFrame != currentFrame)
        {
            currentFrameSprite.setTexture(*T[currentFrame]);

            lastFrame = currentFrame;
        }

        currentFrameSprite.setPosition(Pos);
        currentFrameSprite.setRotation(rotation);

        app << currentFrameSprite;

        controlNumber += timeModifier;
        int cI = (255 / (iterationsPerFrame * 10)) * timeModifier;

        if(alphaLast and currentFrame == frames - 1)
        {
            if(currentAlpha - cI > 0)
                currentAlpha -= cI;
            else
                currentAlpha = 0;

            currentFrameSprite.setColor(sf::Color(255, 255, 255, currentAlpha));
            if(currentAlpha == 0)
                finished = true;
        }

        if((alphaLast and controlNumber >= iterationsPerFrame and currentFrame < frames - 1) or (!alphaLast and controlNumber >= iterationsPerFrame and currentFrame < frames))
        {
            currentFrame++;
            controlNumber -= iterationsPerFrame;
        }
    }

    else if(currentFrame >= frames - 1)
        finished = true;

    return 0;
}
#endif // ANIMATION_H_INCLUDED
