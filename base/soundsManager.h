#ifndef SOUNDSMANAGER_H_INCLUDED
#define SOUNDSMANAGER_H_INCLUDED

namespace sfSounds
{
    class advencedBuffer : public sf::SoundBuffer
    {
    public:
        sf::Uint8 defaultVolume;
        string pass;
        string name;
    };

    class SoundsManager : sf::NonCopyable
    {
    private:
        sf::Uint8 globalVolume;
        sf::Uint8 inGameVolume;
        sf::Uint8 musicVolume;

        sf::Uint8 current;
        vector <sf::Sound*> sounds;
        sf::Sound music;
        advencedBuffer buffers[256];
    public:
        SoundsManager();
        ~SoundsManager();
        sf::Uint8 loadFromFile(string pass, string name, sf::Uint8 defaultVolume);
        sf::Uint8 getIdByName(string name);
        sf::Sound * createSound(sf::Uint8 ID);
        sf::Sound * createMusic(sf::Uint8 ID);
        sf::Sound * getMusic();

        void setGlobalVolume(int vol);
        void setInGameVolume(int vol);
        void setMusicVolume(int vol);

        sf::Uint8 getGlobalVolume();
        sf::Uint8 getInGameVolume();
        sf::Uint8 getMusicVolume();

        void unpauseAll();
        void pauseAll();
        void cleaner();

        void init(Settings config);
    };

    SoundsManager::SoundsManager()
    {
        globalVolume = 50;
        current = 0;
    }
    SoundsManager::~SoundsManager()
    {
        for(int i = sounds.size() - 1; i >=0; i--)
            delete sounds[i];

        sounds.clear();
    }

    sf::Uint8 SoundsManager::loadFromFile(string pass, string name, sf::Uint8 defaultVolume = 50)
    {
        sf::Uint8 retID = 0;
        bool loaded = false;

        for(int i = 0; i < current; i++)
        {
            if(buffers[i].pass == pass)
            {
                loaded = true;
                retID = i;
            }
        }

        if(!loaded)
        {
            retID = current;
            buffers[current].loadFromFile(pass);
            buffers[current].pass = pass;
            buffers[current].name = name;
            buffers[current].defaultVolume = defaultVolume;
            current++;
        }

        return retID;
    }

    sf::Uint8 SoundsManager::getIdByName(string name)
    {
        for(int i = 0; i < current; i++)
            if(buffers[i].name == name)
                return i;

        return 0;
    }

    sf::Sound * SoundsManager::createSound(sf::Uint8 ID)
    {
        sf::Sound * tmp = new sf::Sound;
        tmp -> setBuffer(buffers[ID]);
        tmp -> setVolume(buffers[ID].defaultVolume * static_cast<float>(inGameVolume) / 100.f);

        sounds.push_back(tmp);

        return tmp;
    }
    sf::Sound * SoundsManager::createMusic(sf::Uint8 ID)
    {
        music.setBuffer(buffers[ID]);
        music.setVolume(buffers[ID].defaultVolume * static_cast<float>(musicVolume) / 100.f);

        return &music;
    }
    sf::Sound * SoundsManager::getMusic()
    {
        return & music;
    }

    void SoundsManager::setGlobalVolume(int vol)
    {
        if(vol > 100)
            vol = 100;

        sf::Listener::setGlobalVolume(vol);
    }
    void SoundsManager::setInGameVolume(int vol)
    {
        if(vol > 100)
            vol = 100;

        inGameVolume = vol;
    }
    void SoundsManager::setMusicVolume(int vol)
    {
        if(vol > 100)
            vol = 100;

        musicVolume = vol;
    }

    sf::Uint8 SoundsManager::getGlobalVolume()
    {
        return sf::Listener::getGlobalVolume();
    }
    sf::Uint8 SoundsManager::getInGameVolume()
    {
        return inGameVolume;
    }
    sf::Uint8 SoundsManager::getMusicVolume()
    {
        return musicVolume;
    }

    void SoundsManager::pauseAll()
    {
        for(sf::Uint32 i = 0; i < sounds.size(); i++)
            sounds[i] -> pause();
    }
    void SoundsManager::unpauseAll()
    {
        for(sf::Uint32 i = 0; i < sounds.size(); i++)
            sounds[i] -> play();
    }

    void SoundsManager::cleaner()
    {
        for(sf::Uint32 i = 0; i < sounds.size(); i++)
        {
            if(sounds[i] -> getStatus() == sf::Sound::Stopped)
            {
                delete sounds[i];
                sounds.erase(sounds.begin() + i);
            }
        }
    }

    void SoundsManager::init(Settings config)
    {
        setGlobalVolume(config.getGlobalVolume());
        setInGameVolume(config.getInGameVolume());
        setMusicVolume(config.getMusicVolume());
    }
}

#endif // SOUNDSMANAGER_H_INCLUDED
