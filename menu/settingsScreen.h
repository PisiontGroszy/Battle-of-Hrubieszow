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

    sf::Text soundSettingsText;
    soundSettingsText.setFont(bitFont);
    soundSettingsText.setCharacterSize(70);
    soundSettingsText.setString("Sounds:");
    soundSettingsText.setPosition(screenCornerX + 10, screenCornerY - 10);

    sf::Text graphicsSettingsText;
    graphicsSettingsText.setFont(bitFont);
    graphicsSettingsText.setCharacterSize(70);
    graphicsSettingsText.setString("Graphics (reguire restart):");
    graphicsSettingsText.setPosition(screenCornerX + 10, screenCornerY + 185);

    sf::Text musicSoundText;
    musicSoundText.setFont(bitFont);
    musicSoundText.setCharacterSize(40);
    musicSoundText.setPosition(screenCornerX + 430, screenCornerY + 50);

    sf::Text inGameSoundText;
    inGameSoundText.setFont(bitFont);
    inGameSoundText.setCharacterSize(40);
    inGameSoundText.setPosition(screenCornerX + 430, screenCornerY + 90);

    sf::Text globalSoundText;
    globalSoundText.setFont(bitFont);
    globalSoundText.setCharacterSize(40);
    globalSoundText.setPosition(screenCornerX + 430, screenCornerY + 130);

    sf::Text cursorScaleText;
    cursorScaleText.setFont(bitFont);
    cursorScaleText.setCharacterSize(40);
    cursorScaleText.setPosition(screenCornerX + 430, screenCornerY + 300);

    sf::Text cursorAlphaText;
    cursorAlphaText.setFont(bitFont);
    cursorAlphaText.setCharacterSize(40);
    cursorAlphaText.setPosition(screenCornerX + 430, screenCornerY + 340);

    sf::Text enableVsyncText;
    enableVsyncText.setFont(bitFont);
    enableVsyncText.setCharacterSize(40);
    enableVsyncText.setString("(En/Dis)ables v-sync");
    enableVsyncText.setPosition(screenCornerX + 70, screenCornerY + 260);

    //Kontrolki od dźwięku
    sf::gui::Slider musicSlider(textureManager, sf::Vector2f(screenCornerX + 10, screenCornerY + 80), 4, settings.getMusicVolume());
    sf::gui::Slider inGameSlider(textureManager, sf::Vector2f(screenCornerX + 10, screenCornerY + 120), 4, settings.getInGameVolume());
    sf::gui::Slider globalSlider(textureManager, sf::Vector2f(screenCornerX + 10, screenCornerY + 160), 4, settings.getGlobalVolume());
    //--------------------

    //Kontrolki od grafiki
    sf::gui::Checkbox enableVsync(textureManager, sf::Vector2f(screenCornerX + 10, screenCornerY + 265), 2, "assets/graphics/UI/checkbox/", settings.FPScontroller == "v-sync");

    sf::gui::Slider cursorScaleSlider(textureManager, sf::Vector2f(screenCornerX + 10, screenCornerY + 330), 4, Map(settings.getCursorScale().x, 0.1f, 2.f, 0, 100));
    sf::gui::Slider cursorAlphaSlider(textureManager, sf::Vector2f(screenCornerX + 10, screenCornerY + 370), 4, Map(settings.getCursorAplha(), 0, 255, 0, 100));
    //--------------------

    for(bool exit = false; !exit;)
    {
        tmpCursor.setPosition(sf::Mouse::getPosition().x * viewScale + screenCornerX, sf::Mouse::getPosition().y * viewScale + screenCornerY);

        ostringstream musicSS;
        musicSS << "Music volume: ";
        musicSS << musicSlider.getCurrentStep();
        musicSS << "%";
        musicSoundText.setString(musicSS.str());

        ostringstream inGameSS;
        inGameSS << "In-Game volume: ";
        inGameSS << inGameSlider.getCurrentStep();
        inGameSS << "%";
        inGameSoundText.setString(inGameSS.str());

        ostringstream globalSS;
        globalSS << "Global volume: ";
        globalSS << globalSlider.getCurrentStep();
        globalSS << "%";
        globalSoundText.setString(globalSS.str());

        ostringstream cursorScaleSS;
        cursorScaleSS << "Cursor Scale: ";
        cursorScaleSS << ((Map(cursorScaleSlider.getCurrentStep(), 0, 100, 0.1f, 2.f) < 1) ? setprecision(1) : setprecision(2)) << Map(cursorScaleSlider.getCurrentStep(), 0, 100, 0.1f, 2.f);
        cursorScaleSS << "x";
        cursorScaleText.setString(cursorScaleSS.str());

        ostringstream cursorAlphaSS;
        cursorAlphaSS << "Cursor alpha: ";
        cursorAlphaSS << cursorAlphaSlider.getCurrentStep();
        cursorAlphaSS << "%";
        cursorAlphaText.setString(cursorAlphaSS.str());

        //Rysowanie
        app << screenshot;

        app << soundSettingsText;
        app << graphicsSettingsText;

        app << QuitButton;
        app << SaveButton;

        app << musicSoundText;
        app << musicSlider;

        app << inGameSoundText;
        app << inGameSlider;

        app << globalSoundText;
        app << globalSlider;

        app << enableVsyncText;
        app << enableVsync;

        app << cursorScaleText;
        app << cursorScaleSlider;

        app << cursorAlphaText;
        app << cursorAlphaSlider;

        app << tmpCursor;
        //---------

        while(app >> event)
        {
            QuitButton.update(event);
            SaveButton.update(event);

            musicSlider.update(event);
            inGameSlider.update(event);
            globalSlider.update(event);

            enableVsync.update(event);

            cursorScaleSlider.update(event);
            cursorAlphaSlider.update(event);

            if(QuitButton.funcDone)
                exit = true;

            else if(SaveButton.funcDone)
            {
                cout << endl << "-----Saving settings (" << date() << ")-----" << endl;

                settings.setMusicVolume(musicSlider.getCurrentStep());
                app.soundsManager.getMusic() -> setVolume(settings.getMusicVolume());
                cout << "Music volume set to: " << (int) settings.getMusicVolume() << endl;

                settings.setInGameVolume(inGameSlider.getCurrentStep());
                app.soundsManager.setInGameVolume(settings.getInGameVolume());
                cout << "In-game volume set to: " << (int) settings.getInGameVolume() << endl;

                settings.setGlobalVolume(globalSlider.getCurrentStep());
                app.soundsManager.setGlobalVolume(settings.getGlobalVolume());
                cout << "Global volume set to: " << (int) settings.getGlobalVolume() << endl;

                settings.enableVsync(enableVsync.getCurrentState());
                cout << "V-Sync " << (enableVsync.getCurrentState() ? "En" : "Dis") << "abled" << endl;

                float s = Map(cursorScaleSlider.getCurrentStep(), 0, 100, 0.1f, 2.f);
                settings.setCursorScale(sf::Vector2f(s, s));
                cout << "Cursor scale set to: " << s << endl;

                settings.setCursorAlpha(Map(cursorAlphaSlider.getCurrentStep(), 0, 100, 0, 255));
                cout << "Cursor alpha set to: " << settings.getCursorAplha() << endl;

                settings.save();
                SaveButton.funcDone = false;
            }
        }

        app.display();
    }
}

#endif // SETTINGS_H_INCLUDED
