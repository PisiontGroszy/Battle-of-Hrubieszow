#ifndef MENU_H_INCLUDED
#define MENU_H_INCLUDED

void menu()
{
    view.reset(sf::FloatRect(screenCornerX, screenCornerY, screenX, screenY));
    app.setView(view);

    loadingScreen();

    characterControler.load(settings);

    bool Quit = true;

    space::meteor meteor;
    int i = random() % 1000;
    meteor.startCreating(random() % 700 + 300, sf::Vector2f(random() % (int) (screenX * 1.5), 0) + sf::Vector2f(-5000 - i, 5000 + i), 6);

    for(;Quit;)
    {
        sf::Mouse::setPosition(sf::Vector2i(screenX / 2, screenY / 2));

        sf::gui::Button PlayButton(sf::Vector2f(0, 0), *textureManager.get("assets/graphics/UI/mainMenu/play1.png"), *textureManager.get("assets/graphics/UI/mainMenu/play2.png"));
        PlayButton.sprite.scale(7, 7);

        sf::gui::Button QuitButton(sf::Vector2f(0, 0), *textureManager.get("assets/graphics/UI/mainMenu/quit1.png"), *textureManager.get("assets/graphics/UI/mainMenu/quit2.png"));
        QuitButton.sprite.scale(5, 5);

        sf::gui::Button SettingsButton(sf::Vector2f(0, 0), *textureManager.get("assets/graphics/UI/mainMenu/settings1.png"), *textureManager.get("assets/graphics/UI/mainMenu/settings2.png"));
        SettingsButton.sprite.scale(3, 3);

        sf::Sprite tmpCursor;
        tmpCursor.setTexture(*textureManager.get("assets/graphics/UI/game/pauseCursor.png"));

        bool Break = false;
        float baseStarsSpeed = 0.f;

        app.soundsManager.getMusic() -> stop();

        PlayButton.setPosition(screenCornerX + screenX / 2 - 245, screenCornerY + screenY / 2 - 380);
        QuitButton.setPosition(screenCornerX + screenX - 50 - (63 * 5), screenCornerY + screenY - 130);
        SettingsButton.setPosition(screenCornerX + 20, screenCornerY + screenY - 70);

        for(float starsSpeed; !Break;)
        {
            //Mierzenie czasu
            sf::Time iterationTime = controlClock.getElapsedTime();

            currentFrameTime = iterationTime.asSeconds();
            timeModifier = currentFrameTime / perfectFrameTime;

            controlClock.restart();
            //---------------

            meteor.create();
            if(meteor.getPosition().y < -500)
            {
                meteor.destroy();
                int i = random() % 1000;
                meteor.startCreating(random() % 700 + 300, sf::Vector2f(random() % (int) (screenX * 1.5), 0) + sf::Vector2f(-5000 - i, 5000 + i), 6);
            }

            //rysowanie mapy
            if(baseStarsSpeed < 1.f)
                baseStarsSpeed += 0.001f;

            starsSpeed = baseStarsSpeed * timeModifier;

            meteor.move(4 * starsSpeed, -4 * starsSpeed);

            mapCornerX += 3 * starsSpeed;
            mapCornerY -= 3 * starsSpeed;

            map2CornerX += 2 * starsSpeed;
            map2CornerY -= 2 * starsSpeed;

            map3CornerX += 1 * starsSpeed;
            map3CornerY -= 1 * starsSpeed;

            mapTile.setPosition(map3CornerX, map3CornerY);
            app << mapTile;
            mapTile.move(-1500, 0);
            app << mapTile;
            mapTile.move(3000, 0);
            app << mapTile;
            mapTile.move(-1500, 1500);
            app << mapTile;
            mapTile.move(-1500, 0);
            app << mapTile;
            mapTile.move(3000, 0);
            app << mapTile;
            mapTile.move(-1500, -3000);
            app << mapTile;
            mapTile.move(-1500, 0);
            app << mapTile;
            mapTile.move(3000, 0);
            app << mapTile;

            map2Tile.setPosition(map2CornerX, map2CornerY);
            app << map2Tile;
            map2Tile.move(-1500, 0);
            app << map2Tile;
            map2Tile.move(3000, 0);
            app << map2Tile;
            map2Tile.move(-1500, 1500);
            app << map2Tile;
            map2Tile.move(-1500, 0);
            app << map2Tile;
            map2Tile.move(3000, 0);
            app << map2Tile;
            map2Tile.move(-1500, -3000);
            app << map2Tile;
            map2Tile.move(-1500, 0);
            app << map2Tile;
            map2Tile.move(3000, 0);
            app << map2Tile;

            map3Tile.setPosition(mapCornerX, mapCornerY);
            app << map3Tile;
            map3Tile.move(-1500, 0);
            app << map3Tile;
            map3Tile.move(3000, 0);
            app << map3Tile;
            map3Tile.move(-1500, 1500);
            app << map3Tile;
            map3Tile.move(-1500, 0);
            app << map3Tile;
            map3Tile.move(3000, 0);
            app << map3Tile;
            map3Tile.move(-1500, -3000);
            app << map3Tile;
            map3Tile.move(-1500, 0);
            app << map3Tile;
            map3Tile.move(3000, 0);
            app << map3Tile;
            //------------

            //przesuwanie mapy
            if(statek.sprite.getPosition().x > mapCornerX + 1500)
                mapCornerX += 1500;
            if(statek.sprite.getPosition().x < mapCornerX)
                mapCornerX -= 1500;

            if(statek.sprite.getPosition().y > mapCornerY + 1500)
                mapCornerY += 1500;
            if(statek.sprite.getPosition().y < mapCornerY)
                mapCornerY -= 1500;


            if(statek.sprite.getPosition().x > map2CornerX + 1500)
                map2CornerX += 1500;
            if(statek.sprite.getPosition().x < map2CornerX)
                map2CornerX -= 1500;

            if(statek.sprite.getPosition().y > map2CornerY + 1500)
                map2CornerY += 1500;
            if(statek.sprite.getPosition().y < map2CornerY)
                map2CornerY -= 1500;

            if(statek.sprite.getPosition().x > map3CornerX + 1500)
                map3CornerX += 1500;
            if(statek.sprite.getPosition().x < map3CornerX)
                map3CornerX -= 1500;

            if(statek.sprite.getPosition().y > map3CornerY + 1500)
                map3CornerY += 1500;
            if(statek.sprite.getPosition().y < map3CornerY)
                map3CornerY -= 1500;
            //------------

            app << meteor;

            app << PlayButton;
            app << QuitButton;
            app << SettingsButton;

            while(app >> event)
            {
                tmpCursor.setPosition(screenCornerX + sf::Mouse::getPosition().x * viewScale, screenCornerY +  sf::Mouse::getPosition().y * viewScale);

                PlayButton.update(event);
                QuitButton.update(event);
                SettingsButton.update(event);

                if(PlayButton.funcDone)
                {
                    app.soundsManager.getMusic() -> setLoop(true);
                    app.soundsManager.getMusic() -> play();
                    quit = false;

                    view.reset(sf::FloatRect(screenCornerX, screenCornerY, screenX, screenY));
                    app.setView(view);

                    battle();

                    starsSpeed = 0.f;

                    Break = true;
                    PlayButton.funcDone = false;
                }
                else if(QuitButton.funcDone)
                {
                    if(confirm("assets/graphics/UI/mainMenu"))
                    {
                        Break = true;
                        Quit = false;
                    }
                    else
                    {
                        QuitButton.funcDone = false;
                        QuitButton.update();
                    }
                }
                else if(SettingsButton.funcDone)
                {
                    settingsScreen();
                    SettingsButton.update();
                    SettingsButton.funcDone = false;
                }
            }

            app << tmpCursor;
            app.display();
        }
    }
}

#endif // MENU_H_INCLUDED
