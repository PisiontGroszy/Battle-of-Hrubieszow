#ifndef BATTLE_H_INCLUDED
#define BATTLE_H_INCLUDED

void battle()
{
    if(saws.size() > 0)
        saws.clear();
    if(souls.size() > 0)
        souls.clear();
    if(pociski.size() > 0)
        pociski.clear();
    if(meteors.size() > 0)
        meteors.clear();
    if(enemies.size() > 0)
        enemies.clear();
    if(damageInfo.size() > 0)
        damageInfo.clear();
    if(soulAddons.size() > 0)
        soulAddons.clear();

    generated_enemies = 0;

    cout << "\n-----Battle (" << date() << ")-----" << endl;

    //Ustawianie parametrów statku i broni
    cout << "Loading enemyies weapons... ";
    enemyWeapons.loadFromFile("assets/xml/weapons2.xml");
    cout << "[OK]" << endl;

    spaceship buf;
    statek = buf;
    init_textures();

    cout << "Loading spaceship weapons... ";
    statek.Weapons.loadFromFile("assets/xml/weapons1.xml");
    statek.Weapons.select(3);
    statek.Weapon = statek.Weapons.top();
    cout << "[OK]" << endl;

    statek.HP = 500;
    statek.shield = 500;
    statek.XP = 0;
    statek.baseMovingSpeed = 20;
    statek.MovingSpeed = statek.baseMovingSpeed;
    statek.bulletsPerRegeneration = 10;
    statek.FramesForRegeneration = 1;
    statek.shieldMax = statek.shield;
    statek.maxHP = statek.HP;
    statek.shieldRegerationTimeInFrames = 120;

    statek.shieldTexture.loadFromFile("assets/graphics/spaceship/shields/active/3.png");
    statek.shieldTexture.setSmooth(true);
    statek.shieldSprite.setTexture(statek.shieldTexture);
    statek.shieldSprite.setOrigin(Collision::GetSpriteSize(statek.shieldSprite).x / 2, Collision::GetSpriteSize(statek.shieldSprite).y / 2);
    statek.shieldSprite.setColor(sf::Color(255, 255, 255, 0));

    statek.ammo = 2000;
    statek.ammoMax = 2000;
    //------------

    //Mało / dużo amunicji etc.
    kursor.lowAmmoTexture.loadFromFile("assets/graphics/cursor/lowAmmo.png");
    kursor.lowAmmoTexture.setSmooth(true);
    kursor.lowAmmoSprite.setTexture(kursor.lowAmmoTexture);
    kursor.lowAmmoSprite.setScale(settings.getCursorScale());
    kursor.lowAmmoSprite.setOrigin((Collision::GetSpriteSize(kursor.lowAmmoSprite).x / kursor.lowAmmoSprite.getScale().x / 2), (Collision::GetSpriteSize(kursor.lowAmmoSprite).y / kursor.lowAmmoSprite.getScale().y / 2));

    kursor.highAmmoTexture.loadFromFile("assets/graphics/cursor/highAmmo.png");
    kursor.highAmmoTexture.setSmooth(true);
    kursor.highAmmoSprite.setTexture(kursor.highAmmoTexture);
    kursor.highAmmoSprite.setScale(settings.getCursorScale());
    kursor.highAmmoSprite.setOrigin((Collision::GetSpriteSize(kursor.highAmmoSprite).x / kursor.highAmmoSprite.getScale().x / 2), (Collision::GetSpriteSize(kursor.highAmmoSprite).y / kursor.highAmmoSprite.getScale().y / 2));

    kursor.hitTexture.loadFromFile("assets/graphics/cursor/hit.png");
    kursor.hitTexture.setSmooth(true);
    kursor.hitSprite.setTexture(kursor.hitTexture);
    kursor.hitSprite.setScale(settings.getCursorScale());
    kursor.hitSprite.setOrigin((Collision::GetSpriteSize(kursor.hitSprite).x / kursor.hitSprite.getScale().x / 2), (Collision::GetSpriteSize(kursor.hitSprite).y / kursor.hitSprite.getScale().y / 2));
    kursor.hitSprite.setColor(sf::Color(255, 255, 255, 0));
    //-------------

    statek.load_texture("assets/graphics/bullets/" + statek.Weapons.top().codeName + "/texture.png");

    FPStext.setPosition(screenCornerX + screenX - 90, screenCornerY + 8);

    releaseButton.setString("Release SHOT button!");

    //Ustawianie pozycji elementów UI
    terminal.create(screenX / 2.5, screenY / 3, sf::Color(10, 10, 10, 230));
    terminal.setPosition(sf::Vector2f(screenCornerX, screenY + screenCornerY - terminal.getSize().y));

    regainingShieldBar.setPosition(screenX + screenCornerX - 240, screenY + screenCornerY - 59);

    releaseButton.setPosition(screenX + screenCornerX - 158, screenY + screenCornerY - 100);

    shieldText.setPosition(screenX + screenCornerX - 335, screenY + screenCornerY - 67);
    shieldBar.setPosition(screenX + screenCornerX - 240, screenY + screenCornerY - 59);

    ammoText.setPosition(screenX + screenCornerX - 335, screenY + screenCornerY - 82);
    ammoBar.setPosition(screenX + screenCornerX - 240, screenY + screenCornerY - 74);
    noAmmoBar.setPosition(screenX + screenCornerX - 240, screenY + screenCornerY - 74);

    HPtext.setPosition(screenX + screenCornerX - 335, screenY + screenCornerY - 52);
    HPbar.setPosition(screenX + screenCornerX - 240, screenY + screenCornerY - 44);

    FPStext.setPosition(screenCornerX + screenX - 110, screenCornerY);

    XPtext.setPosition(screenCornerX + 10, screenCornerY - 10);
    //-------------------------------

    //Przygotowywanie kursora
    kursor.init("assets/graphics/cursor/cursorGrey.png");
    kursor.init("assets/graphics/cursor/cursorRed.png");
    //-----------------------

    screenRect.height = screenY + 100;
    screenRect.width = screenX + 100;

    screenCenter = sf::Vector2f(screenCornerX + (screenX / 2), screenCornerY + (screenY / 2));

    cout << "Loading drones... ";
    statek.addDrone("assets/graphics/bullets/" + statek.Weapons.top().codeName + "/drone.png", 130, -120, 0);
    statek.addDrone("assets/graphics/bullets/" + statek.Weapons.top().codeName + "/drone.png", 130, 120, 0);

    statek.addDrone("assets/graphics/bullets/" + statek.Weapons.top().codeName + "/drone.png", 190, -75, 1);
    statek.addDrone("assets/graphics/bullets/" + statek.Weapons.top().codeName + "/drone.png", 190, 75, 1);
    cout << "[OK]" << endl;

    while (app.isOpen() and !quit and !statek.destroyed_end)
    {
        Time++;

        if(counter >= 101 - statek.Weapon.agility)
        {
            Ready_to_shot = true;
            counter = 0;
        }
        if(!Ready_to_shot)
            counter += timeModifier;

        if(Ready_to_shot)
            Ready_to_shot = (saws.size() <= 200);

        while (app >> event)
        {
            if(event.type == sf::Event::Closed)
                app.close();

            //Zmiana broni
            if (event.type == sf::Event::MouseWheelMoved and Ready_to_shot)
                mouseWheelDelta += event.mouseWheel.delta;

            if(event.type == sf::Event::Resized)
            {
                screenX = event.size.width;
                screenY = event.size.height;
            }

            if(event.type == sf::Event::KeyPressed and event.key.code == sf::Keyboard::Tab)
                terminal.visible(!terminal.isVisible());

            if(terminal.isVisible())
            {
                if(event.type == sf::Event::KeyPressed and (event.key.code == sf::Keyboard::Left or event.key.code == sf::Keyboard::Right))
                    terminal.moveCursor(event.key.code == sf::Keyboard::Left ? -1 : 1);

                if(event.type == sf::Event::TextEntered and event.text.unicode < 128)
                    terminal.insertCharacter(static_cast<char>(event.text.unicode));

                terminal.update();
            }
            else
            {
                if (characterControler.checkAction(characterControler.nextWeapon))
                {
                    statek.Weapons.next();
                    statek.Weapon = statek.Weapons.top();
                    statek.load_texture("assets/graphics/bullets/" + statek.Weapons.top().codeName + "/texture.png");
                    statek.updateDronesTextures();
                    mouseWheelDelta = 0;
                }
                else if (characterControler.checkAction(characterControler.previousWeapon))
                {
                    statek.Weapons.previous();
                    statek.Weapon = statek.Weapons.top();
                    statek.load_texture("assets/graphics/bullets/" + statek.Weapons.top().codeName + "/texture.png");
                    statek.updateDronesTextures();
                    mouseWheelDelta = 0;
                }
                //----------

                //PAUZA
                if(characterControler.checkAction(characterControler.pause) and Time - lastTimePaused > 10)
                {
                    app.soundsManager.pauseAll();
                    Pause();
                    controlClock.restart();
                }
                //-----

                //Kontrolowanie dronów
                if(characterControler.checkAction(characterControler.droneShot))
                {
                    sf::Sprite px;
                    sf::Texture pxT;
                    pxT.create(5, 5);
                    px.setPosition(kursor.sprite.getPosition());
                    px.setTexture(pxT);

                    for(int i = enemies.size() - 1; i >= 0; i--)
                    {
                        if(Collision::PixelPerfectTest(enemies[i].sprite, px))
                        {
                            cout << "Enemy selected!" << endl;
                            statek.targetID = enemies[i].ID;
                        }
                    }
                }
                if(characterControler.checkAction(characterControler.dronesControl))
                {
                    statek.releaseTargets += timeModifier;
                    if(statek.releaseTargets >= 10.f)
                    {
                        statek.enemySelected = false;
                        statek.targetID = -1;
                    }
                }
                else
                    statek.releaseTargets = 0;
                //--------------------
            }
        }

        //strzał nie-laserem
        if(characterControler.checkAction(characterControler.playerShot) and Ready_to_shot and statek.Weapon.codeName != "laser" and !statek.destroyed and Time > 100)
        {
            sf::Vector2f target = statek.sprite.getPosition();
            target += sf::Vector2f(cos(statek.sprite.getRotation() * 0.0174532925f), sin(statek.sprite.getRotation() * 0.0174532925f)) * 1000.f;

            Shot(statek.Weapon, true, target, statek.sprite.getPosition(), &Ready_to_shot);

            if(statek.Weapon.baseAccuracyBonus > 0)
                statek.Weapon.baseAccuracyBonus--;
        }
        //------------------

        //Spoczynek
        if(!characterControler.checkAction(characterControler.playerShot))
        {
            statek.regenerate(true);

            if(statek.Weapon.baseAccuracyBonus < 4)
                statek.Weapon.baseAccuracyBonus++;
        }
        else
            statek.regenerate(false);
        //---------

        //Informacje dodatkowe przy kursorze
        if(static_cast <float> (statek.ammo) / statek.ammoMax <= 0.3)
            kursor.lowAmmo = true;
        else
            kursor.lowAmmo = false;

        if(static_cast <float> (statek.ammo) / statek.ammoMax >= 0.7)
            kursor.highAmmo = true;
        else
            kursor.highAmmo = false;
        //----------------------------------

        //Mierzenie czasu
        sf::Time iterationTime = controlClock.getElapsedTime();
        timeModifier = iterationTime.asSeconds() / perfectFrameTime;
        frameTimes.push_back(iterationTime.asSeconds());

        if(frameTimes.size() > 60)
            frameTimes.erase(frameTimes.begin());
        controlClock.restart();
        //---------------

        //Wrogowie, poruszanie się, rysowanie, itp.
        screenCenter = sf::Vector2f(screenCornerX + (screenX / 2), screenCornerY + (screenY / 2));

        enemyGenerator();
        if(!statek.destroyed and !terminal.isVisible())
            statek.move();

        screenRect.left = screenCornerX - 100;
        screenRect.top = screenCornerY - 100;

        drawer(counter);
        app.display();
        app.soundsManager.cleaner();
        //-----------------------------------------
    }
    if(terminal.isVisible())
        terminal.visible(false);
}
#endif // BATTLE_H_INCLUDED
