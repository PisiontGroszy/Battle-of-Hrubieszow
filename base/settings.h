#ifndef SETTINGS_H_INCLUDED
#define SETTINGS_H_INCLUDED

class Settings
{
private:
    sf::Vector2f cursorScale = sf::Vector2f(0.6f, 0.6f);
    char cursorAlpha = (char) 255;

    int musicVolume;
    int inGameVolume;
    int globalVolume;
public:
    string FPScontroller;
    int FPSlimit;

    xml::xmlDocument * settingsFile;
    void load();
    void save();

    sf::Vector2f getCursorScale();
    void setCursorScale(sf::Vector2f scale);

    sf::Uint8 getCursorAplha();
    void setCursorAlpha(sf::Uint8 alpha);

    sf::Uint8 getMusicVolume();
    void setMusicVolume(sf::Uint8 volume);

    sf::Uint8 getInGameVolume();
    void setInGameVolume(sf::Uint8 volume);

    sf::Uint8 getGlobalVolume();
    void setGlobalVolume(sf::Uint8 volume);
};

void Settings::load()
{
    settingsFile = new xml::xmlDocument("assets/xml/settings.xml");
    xml_node<> *soundsNode = settingsFile -> getFirstNode("sound", settingsFile -> getRootNode());

    setMusicVolume(atoi(settingsFile -> getNodeAttribute(soundsNode, "musicVolume").c_str()));
    setInGameVolume(atoi(settingsFile -> getNodeAttribute(soundsNode, "inGameVolume").c_str()));
    setGlobalVolume(atoi(settingsFile -> getNodeAttribute(soundsNode, "globalVolume").c_str()));

    xml_node<> *personalizeNode = settingsFile -> getFirstNode("personalization", settingsFile -> getRootNode());

    setCursorScale(sf::Vector2f(atof(settingsFile -> getNodeAttribute(personalizeNode, "cursorScale").c_str()), atof(settingsFile -> getNodeAttribute(personalizeNode, "cursorScale").c_str())));
    setCursorAlpha(atoi(settingsFile -> getNodeAttribute(personalizeNode, "cursorAlpha").c_str()));

    xml_node<> *FPSnode = settingsFile -> getFirstNode("framerate", settingsFile -> getRootNode());
    FPScontroller = settingsFile -> getNodeAttribute(FPSnode, "controller");
    FPSlimit = atoi(settingsFile -> getNodeAttribute(FPSnode, "fps").c_str());
}

void Settings::save()
{
    xml_node<> *soundsNode = settingsFile -> getFirstNode("sound", settingsFile -> getRootNode());

    ostringstream inGameVolumeSS, musicVolumeSS;

    inGameVolumeSS << (int) getInGameVolume();
    musicVolumeSS << (int) getMusicVolume();

    const string inGameVolumeSSs(inGameVolumeSS.str());
    const string musicVolumeSSs(musicVolumeSS.str());

    //settingsFile -> setNodeAttribute(soundsNode, "globalVolume", itoa(getGlobalVolume()));
    settingsFile -> setNodeAttribute(soundsNode, "inGameVolume", inGameVolumeSSs.c_str());
    settingsFile -> setNodeAttribute(soundsNode, "musicVolume", musicVolumeSSs.c_str());
}

sf::Vector2f Settings::getCursorScale()
{
    return cursorScale;
}

void Settings::setCursorScale(sf::Vector2f scale)
{
    cursorScale = scale;
}

sf::Uint8 Settings::getCursorAplha()
{
    return (int) cursorAlpha;
}

void Settings::setCursorAlpha(sf::Uint8 alpha)
{
    cursorAlpha = (char) alpha;
}

sf::Uint8 Settings::getMusicVolume()
{
    return musicVolume;
}
void Settings::setMusicVolume(sf::Uint8 volume)
{
    musicVolume = volume;
}

sf::Uint8 Settings::getInGameVolume()
{
    return inGameVolume;
}
void Settings::setInGameVolume(sf::Uint8 volume)
{
    inGameVolume = volume;
}

sf::Uint8 Settings::getGlobalVolume()
{
    return globalVolume;
}
void Settings::setGlobalVolume(sf::Uint8 volume)
{
    globalVolume = volume;
}

Settings settings;

#endif // SETTINGS_H_INCLUDED
