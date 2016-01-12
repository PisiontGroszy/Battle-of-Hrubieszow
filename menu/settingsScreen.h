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
    musicSoundText.setFont(roboto);
    musicSoundText.setCharacterSize(30);
    musicSoundText.setPosition(screenCornerX + 430, screenCornerY + 10);

    sf::Text inGameSoundText;
    inGameSoundText.setFont(roboto);
    inGameSoundText.setCharacterSize(30);
    inGameSoundText.setPosition(screenCornerX + 430, screenCornerY + 50);

    sf::gui::Slider musicSlider(textureManager, sf::Vector2f(screenCornerX + 10, screenCornerY + 30), 4, settings.getMusicVolume());
    sf::gui::Slider inGameSlider(textureManager, sf::Vector2f(screenCornerX + 10, screenCornerY + 70), 4, settings.getInGameVolume());

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

        app << tmpCursor;
        //---------

        while(app >> event)
        {
            QuitButton.update(event);
            SaveButton.update(event);

            musicSlider.update(event);
            inGameSlider.update(event);

            if(QuitButton.funcDone)
                exit = true;
            else if(SaveButton.funcDone)
            {
                settings.setMusicVolume(musicSlider.getCurrentStep());
                app.soundsManager.getMusic() -> setVolume(settings.getMusicVolume());

                settings.setInGameVolume(inGameSlider.getCurrentStep());
                app.soundsManager.setInGameVolume(settings.getInGameVolume());

                settings.save();

                SaveButton.funcDone = false;
            }
        }

        app.display();
    }
}

#endif // SETTINGS_H_INCLUDED
