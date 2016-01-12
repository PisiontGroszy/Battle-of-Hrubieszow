#ifndef PAUSE_H_INCLUDED
#define PAUSE_H_INCLUDED

int lastTimePaused = 0;

bool confirm(string dir)
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

    sf::Texture yes[2];
    yes[0].loadFromFile(dir + "/yes1.png");
    yes[1].loadFromFile(dir + "/yes2.png");

    sf::Texture no[2];
    no[0].loadFromFile(dir + "/no1.png");
    no[1].loadFromFile(dir + "/no2.png");

    sf::gui::Button Yes(sf::Vector2f(0, 0), yes[0], yes[1]);
    sf::gui::Button No(sf::Vector2f(0, 0), no[0], no[1]);

    Yes.sprite.setScale(7, 7);
    No.sprite.setScale(7, 7);

    Yes.setPosition(screenCornerX + (screenX / 2) + 72, screenCornerY + (screenY / 2));
    No.setPosition(screenCornerX + (screenX / 2) - 240, screenCornerY + (screenY / 2));


    for(;;)
    {
        app.clear();
        app << screenshot;
        tmpCursor.setPosition(sf::Mouse::getPosition().x * viewScale + screenCornerX, sf::Mouse::getPosition().y * viewScale + screenCornerY);

        app << Yes;
        app << No;

        app << tmpCursor;
        app.display();

        while(app >> event)
        {
            if(event.type == sf::Event::KeyPressed and event.key.code == sf::Keyboard::Escape)
                return false;

            Yes.update(event);
            No.update(event);

            if(Yes.funcDone)
                return true;

            if(No.funcDone)
                return false;
        }
    }
}

void Pause()
{
    sf::Vector2i mousePos = sf::Mouse::getPosition(app);
    sf::Mouse::setPosition(sf::Vector2i(screenX / 2, screenY / 2));

    sf::Texture tmpCursorTexture;
    tmpCursorTexture.loadFromFile("assets/graphics/UI/game/pauseCursor.png");
    sf::Sprite tmpCursor;
    tmpCursor.setTexture(tmpCursorTexture);

    sf::Texture screnshotTexture;
    screnshotTexture.loadFromImage(app.capture());
    sf::Sprite screenshot;

    screenshot.setTexture(screnshotTexture);
    screenshot.setPosition(screenCornerX, screenCornerY);
    screenshot.setScale(viewScale, viewScale);
    screenshot.setColor(sf::Color(90, 90, 90));

    //GUI
    sf::gui::Button ContinueButton(sf::Vector2f(0, 0), *textureManager.get("assets/graphics/UI/game/continue1.png"), *textureManager.get("assets/graphics/UI/game/continue2.png"));
    ContinueButton.sprite.scale(7, 7);
    ContinueButton.setPosition(screenCornerX + (screenX / 2) - 217, screenCornerY + (screenY / 2) - 300);

    sf::gui::Button BackButton(sf::Vector2f(0, 0), *textureManager.get("assets/graphics/UI/game/back1.png"), *textureManager.get("assets/graphics/UI/game/back2.png"));
    BackButton.sprite.scale(7, 7);
    BackButton.setPosition(screenCornerX + (screenX / 2) - 315, screenCornerY + (screenY / 2) - 120);

    sf::gui::Button QuitButton(sf::Vector2f(0, 0), *textureManager.get("assets/graphics/UI/game/quit1.png"), *textureManager.get("assets/graphics/UI/game/quit2.png"));
    QuitButton.sprite.scale(7, 7);
    QuitButton.setPosition(screenCornerX + (screenX / 2) - 112, screenCornerY + (screenY / 2) + 280);

    sf::gui::Button SettingsButton(sf::Vector2f(0, 0), *textureManager.get("assets/graphics/UI/game/settings1.png"), *textureManager.get("assets/graphics/UI/game/settings2.png"));
    SettingsButton.sprite.scale(7, 7);
    SettingsButton.setPosition(screenCornerX + (screenX / 2) - (65 * 3.5), screenCornerY + (screenY / 2) + 170);
    //---

    gamePause = true;
    app.soundsManager.getMusic() -> pause();
    sf::Clock tmpClock;

    for(;gamePause;)
    {
        app.clear();
        app << screenshot;
        tmpCursor.setPosition(sf::Mouse::getPosition().x * viewScale + screenCornerX, sf::Mouse::getPosition().y * viewScale + screenCornerY);

        app << QuitButton;
        app << BackButton;
        app << ContinueButton;
        app << SettingsButton;

        if(!QuitButton.funcDone and !BackButton.funcDone and !SettingsButton.funcDone)
            app << tmpCursor;

        app.display();

        if(QuitButton.funcDone)
        {
            if(confirm("assets/graphics/UI/game"))
                gameOver();

            else
            {
                QuitButton.update();
                QuitButton.funcDone = false;
            }
        }
        else if(BackButton.funcDone)
        {
            if(confirm("assets/graphics/UI/game"))
            {
                quit = true;
                break;
            }

            else
            {
                BackButton.update();
                BackButton.funcDone = false;
            }
        }
        else if(ContinueButton.funcDone)
        {
            ContinueButton.funcDone = false;
            gamePause = false;
        }
        else if(SettingsButton.funcDone)
        {
            settingsScreen();
            SettingsButton.funcDone = false;
        }


        while(app >> event)
        {
            if(characterControler.checkAction(characterControler.pause) and tmpClock.getElapsedTime().asMilliseconds() > 100)
            {
                lastTimePaused = Time;
                gamePause = false;
            }

            ContinueButton.update(event);
            BackButton.update(event);
            QuitButton.update(event);
            SettingsButton.update(event);
        }
    }
    app.soundsManager.getMusic() -> play();
    sf::Mouse::setPosition(mousePos);
}

#endif // PAUSE_H_INCLUDED
