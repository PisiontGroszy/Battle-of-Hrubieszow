#ifndef TEXTUREMANAGER_H_INCLUDED
#define TEXTUREMANAGER_H_INCLUDED

#define TEXTURES_LIMIT 256
namespace sf
{
    class advencedTexture : public Texture
    {
    public:
        string pass;
        bool load(string textureFile);
    };

    bool advencedTexture::load(string textureFile)
    {
        pass = textureFile;
        return loadFromFile(textureFile.c_str());
    }

    class textureManager
    {
    private:
        advencedTexture textures[TEXTURES_LIMIT];
        advencedTexture blank;
        int current = 0;
    public:
        textureManager();
        int getCurrent();
        bool add(string pass, bool smooth);
        advencedTexture * get(int pass);
        advencedTexture * get(string pass);
    };

    textureManager::textureManager()
    {
        blank.create(1, 1);
        blank.pass = "Texture not found!";
    }

    int textureManager::getCurrent()
    {
        return current;
    }

    bool textureManager::add(string pass, bool smooth = false)
    {
        for(int i = 0; i <= current; i++)
            if(textures[i].pass == pass or current + 1 == TEXTURES_LIMIT)
                return false;

        textures[current].load(pass);
        textures[current].setSmooth(smooth);
        current++;
        return true;
    }

    advencedTexture * textureManager::get(string pass)
    {
        for(int i = 0; i <= current; i++)
        {
            if(textures[i].pass == pass)
                return &textures[i];
        }
        return &blank;
    }

    advencedTexture * textureManager::get(int pass)
    {
        if(pass <= current)
            return &textures[pass];

        return &blank;
    }
};

#endif // TEXTUREMANAGER_H_INCLUDED
