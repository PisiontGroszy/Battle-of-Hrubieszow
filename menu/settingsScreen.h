#ifndef SETTINGS_SCREEN_H_INCLUDED
#define SETTINGS_SCREEN_H_INCLUDED

void settingsScreen()
{
    sf::Texture screnshotTexture;
    screnshotTexture.loadFromImage(app.capture());
    sf::Sprite screenshot;

    screenshot.setTexture(screnshotTexture);
    screenshot.setPosition(screenCornerX, screenCornerY);
    screenshot.setScale(viewScale, viewScale);
    screenshot.setColor(sf::Color(80, 80, 80));

    sf::Texture tmpCursorTexture;
    tmpCursorTexture.loadFromFile("assets/graphics/UI/game/pauseCursor.png");
    sf::Sprite tmpCursor;
    tmpCursor.setTexture(tmpCursorTexture);

    sf::gui::Button QuitButton(sf::Vector2f(0, 0), *textureManager.get("assets/graphics/UI/mainMenu/quit1.png"), *textureManager.get("assets/graphics/UI/mainMenu/quit2.png"));
    QuitButton.sprite.scale(3, 3);
    QuitButton.setPosition(sf::Vector2f(screenCornerX + screenX / 2 - 96, screenCornerY + screenY - 100));

    textureManager.add("assets/graphics/UI/mainMenu/save1.png");
    textureManager.add("assets/graphics/UI/mainMenu/save2.png");

    sf::gui::Button SaveButton(sf::Vector2f(0, 0), *textureManager.get("assets/graphics/UI/mainMenu/save1.png"), *textureManager.get("assets/graphics/UI/mainMenu/save2.png"));
    SaveButton.sprite.setScale(3, 3);
    SaveButton.setPosition(screenCornerX + screenX - 230, screenCornerY + 20);

    sf::Event event;

    sf::Text musicSoundText;
    musicSoundText.setFont(bitFont);
    musicSoundText.setCharacterSize(40);
    musicSoundText.setPosition(screenCornerX + 430, screenCornerY);

    sf::Text inGameSoundText;
    inGameSoundText.setFont(bitFont);
    inGameSoundText.setCharacterSize(40);
    inGameSoundText.setPosition(screenCornerX + 430, screenCornerY + 40);

    sf::Text enableVsyncText;
    enableVsyncText.setFont(bitFont);
    enableVsyncText.setCharacterSize(40);
    enableVsyncText.setString("(En/Dis)ables v-sync (reguires restart)");
    enableVsyncText.setPosition(screenCornerX + 70, screenCornerY + 105);

    sf::gui::Slider musicSlider(textureManager, sf::Vector2f(screenCornerX + 10, screenCornerY + 30), 4, settings.getMusicVolume());
    sf::gui::Slider inGameSlider(textureManager, sf::Vector2f(screenCornerX + 10, screenCornerY + 70), 4, settings.getInGameVolume());

    sf::gui::Checkbox enableVsync(textureManager, sf::Vector2f(screenCornerX + 10, screenCornerY + 110), 4, "assets/graphics/UI/checkbox/", settings.FPScontroller == "v-sync");

    for(bool exit = false; !exit;)
    {
        tmpCursor.setPosition(sf::Mouse::getPosition().x * viewScale + screenCornerX, sf::Mouse::getPosition().y * viewScale + screenCornerY);

        ostringstream musicSS;
        musicSS << "Music volume: ";
        musicSS << musicSlider.getCurrentStep();
        musicSoundText.setString(musicSS.str());

        ostringstream inGameSS;
        inGameSS << "In-Game volume: ";
        inGameSS << inGameSlider.getCurrentStep();
        inGameSoundText.setString(inGameSS.str());

        //Rysowanie
        app << screenshot;

        app << QuitButton;
        app << SaveButton;

        app << musicSoundText;
        app << musicSlider;

        app << inGameSoundText;
        app << inGameSlider;

        app << enableVsyncText;
        app << enableVsync;

        app << tmpCursor;
        //---------

        while(app >> event)
        {
            QuitButton.update(event);
            SaveButton.update(event);

            musicSlider.update(event);
            inGameSlider.update(event);

            enableVsync.update(event);

            if(QuitButton.funcDone)
                exit = true;
            else if(SaveButton.funcDone)
            {
                settings.setMusicVolume(musicSlider.getCurrentStep());
                app.soundsManager.getMusic() -> setVolume(settings.getMusicVolume());

                settings.setInGameVolume(inGameSlider.getCurrentStep());
                app.soundsManager.setInGameVolume(settings.getInGameVolume());

                settings.enableVsync(enableVsync.getCurrentState());

                settings.save();

                SaveButton.funcDone = false;
            }
        }

        app.display();
    }
}

#endif // SETTINGS_H_INCLUDED
