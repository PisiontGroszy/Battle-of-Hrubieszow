#ifndef DRAWER_H_INCLUDED
#define DRAWER_H_INCLUDED

void rotator()
{
    int cursorX = kursor.sprite.getPosition().x;
    int cursorY = kursor.sprite.getPosition().y;

    kursor.sprite.setRotation(rotate_to_fi(statek.sprite.getPosition(), sf::Vector2i(cursorX, cursorY)));

    if(!statek.destroyed)
    {
        //Limit prędkości obrotu
        float rotationSpeedLimit = 10 * timeModifier;
        //----------------------

        statek.sprite.setOrigin(Collision::GetSpriteSize(statek.sprite).x / 2, Collision::GetSpriteSize(statek.sprite).y / 2);

        float rotation = rotate_to_fi(statek.sprite.getPosition(), sf::Vector2i(cursorX, cursorY)) - statek.sprite.getRotation();

        if(rotation < 180)
            rotation += 360;
        if(rotation > 180)
            rotation -= 360;

        //Egzekwowanie limitu prędkości obrotu
        if(rotation > rotationSpeedLimit)
            rotation = rotationSpeedLimit;
        if(rotation < -rotationSpeedLimit)
            rotation = -rotationSpeedLimit;
        //----------------------

        statek.sprite.rotate(rotation);
    }
}

void drawer(int counter)
{
    //rysowanie mapy
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
    sf::Vector2f controlVect(mapControlCornerX, mapControlCornerY);
    if(statek.sprite.getPosition().x > mapControlCornerX + 1500)
        mapControlCornerX += 1500;
    if(statek.sprite.getPosition().x < mapControlCornerX)
        mapControlCornerX -= 1500;

    if(statek.sprite.getPosition().y > mapControlCornerY + 1500)
        mapControlCornerY += 1500;
    if(statek.sprite.getPosition().y < mapControlCornerY)
        mapControlCornerY -= 1500;

    if(controlVect != sf::Vector2f(mapControlCornerX, mapControlCornerY))
    {
        if(controlVect.x != mapControlCornerX)
        {
            if(mapControlCornerX > generatedMaxX)
            {
                generatedMaxX = mapControlCornerX + 1500;
                generatedTiles += 3;
                newTiles = true;
            }
            if(mapControlCornerX < generatedMinX)
            {
                generatedMinX = mapControlCornerX;
                generatedTiles += 3;
                newTiles = true;
            }
        }

        if(controlVect.y != mapControlCornerY)
        {
            if(mapControlCornerY > generatedMaxY)
            {
                generatedMaxY = mapControlCornerY + 1500;
                generatedTiles += 3;
                newTiles = true;
            }
            if(mapControlCornerY < generatedMinY)
            {
                generatedMinY = mapControlCornerY;
                generatedTiles += 3;
                newTiles = true;
            }
        }
    }
    //-------------------

    //Rysowanie meteorytów
    int creatingFreq = 5 * 60;

    if(Time % creatingFreq == 0 and newTiles and meteors.size() < 10)
    {
        space::meteor tmp;
        meteors.push_back(tmp);

        meteors[meteors.size() - 1].startCreating((random() % 300) + 700, statek.sprite.getPosition() - (direction / static_cast <float> (statek.baseMovingSpeed)) * 5000.f + sf::Vector2f(random() % 751 - 375, random() % 751 - 375) * 2.f, 6);
        newTiles = false;
    }

    for(int meteorTabPos = meteors.size() - 1; meteorTabPos >= 0; meteorTabPos--)
    {
        sf::Vector2f kierunek = meteors[meteorTabPos].pos - statek.sprite.getPosition();
        float magnitude = sqrt((kierunek.x * kierunek.x) + (kierunek.y * kierunek.y));

        meteors[meteorTabPos].move();
        if(meteors[meteorTabPos].contains(statek.sprite.getPosition(), 0))
        {
            meteors[meteorTabPos].move(meteors[meteorTabPos].momentumX * -1.f, meteors[meteorTabPos].momentumY * -1.f);

            meteors[meteorTabPos].momentumX = meteors[meteorTabPos].momentumX * -0.2f;
            meteors[meteorTabPos].momentumY = meteors[meteorTabPos].momentumY * -0.2f;
        }

        if(!meteors[meteorTabPos].destroyed and !meteors[meteorTabPos].created)
            meteors[meteorTabPos].create();

        if(magnitude < screenX and meteors[meteorTabPos].created)
            app << meteors[meteorTabPos];

        if(magnitude > screenX * 6 or meteors[meteorTabPos].destroyed)
        {
            meteors[meteorTabPos].destroy();
            meteors.erase(meteors.begin() + meteorTabPos);
        }
    }
    //--------------------

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

    if(sf::Mouse::isButtonPressed(sf::Mouse::Left) and statek.Weapon.codeName == "laser" and statek.ammo > statek.Weapon.ammoUsage and !statek.destroyed)
    {
        statek.Laser.load(statek.sprite.getPosition(), statek.Weapon);

        sf::Vector2f target = statek.sprite.getPosition();
        target += sf::Vector2f(cos(statek.sprite.getRotation() * 0.0174532925f), sin(statek.sprite.getRotation() * 0.0174532925f));
        kursor.sprite.setPosition(target);

        statek.Laser.setTarget(target);
        statek.ammo -= statek.Weapon.ammoUsage;

        vector <sf::Sprite> sprites;
        vector <string> textures;
        vector <int> IDs;

        for(int enemiesTabPos = enemies.size() - 1; enemiesTabPos >= 0; enemiesTabPos--)
        {
            if(!enemies[enemiesTabPos].killed)
            {
                sprites.push_back(enemies[enemiesTabPos].sprite);
                textures.push_back(enemies[enemiesTabPos].tekstura);
                IDs.push_back(enemies[enemiesTabPos].ID);
            }
        }

        int i = statek.Laser.collision(sprites, textures, IDs);

        if(i >= 0)
        {
            statek.Laser.calculateTransform();
            sf::Vector2f hitPoint = statek.Laser.collisionPoint;
            bool p = true;
            bool * prawda = &p;

            for(int enemiesTabPos = enemies.size() - 1; enemiesTabPos >= 0; enemiesTabPos--)
            {
                if(enemies[enemiesTabPos].ID == i)
                {
                    Shot(statek.Weapon, true, hitPoint, hitPoint, prawda);
                    pociski[pociski.size() - 1].hit = true;

                    enemies[enemiesTabPos].takeDamage(statek.Weapon.damage);
                    kursor.hitInFrame();

                    if(enemies[enemiesTabPos].killed)
                    {
                        soul tmpSoul(enemies[enemiesTabPos].sprite.getPosition() + sf::Vector2f(0, 0));
                        tmpSoul.XP = enemies[enemiesTabPos].XP;
                        souls.push_back(tmpSoul);
                    }
                }
            }
        }
        Ready_to_shot = false;
    }
    else if(characterControler.checkAction(characterControler.playerShot) and Ready_to_shot and statek.Weapon.codeName == "laser" and statek.ammo <= statek.Weapon.ammoUsage)
        statek.ammo = 0;


    //ustawianie pozycji kursora
    kursor.sprite.setPosition(sf::Mouse::getPosition(app).x * viewScale + screenCornerX, sf::Mouse::getPosition(app).y * viewScale + screenCornerY);
    //---------------

    //rysowanie dronów
    for(int i = statek.drones.size() - 1; !statek.destroyed and i >= 0; i--)
    {
        statek.drones[i].Drone.setRotation(statek.sprite.getRotation());

        float radiaus = statek.drones[i].radiaus;

        sf::Vector2f dronTargetPos;
        dronTargetPos.x = cos(aToRadian(statek.sprite.getRotation() + statek.drones[i].angleMod)) * radiaus + statek.sprite.getPosition().x;
        dronTargetPos.y = sin(aToRadian(statek.sprite.getRotation() + statek.drones[i].angleMod)) * radiaus + statek.sprite.getPosition().y;

        statek.drones[i].moveTo(dronTargetPos, statek.enemySelected);

        if(statek.enemySelected)
        {
            statek.drones[i].fightManager(statek.target, statek.targetID);
        }

        app << statek.drones[i];
    }
    //----------------

    //rysowanie pocisków
    for(bool allMoved = false, first = true; !allMoved; first = false)
    {
        bool buf = true;
        for(int bulletTabPos = pociski.size() - 1; bulletTabPos >= 0; bulletTabPos--)
        {
            if(!pociski[bulletTabPos].destroyed and !pociski[bulletTabPos].hit)
            {
                if(first)
                    pociski[bulletTabPos].prepareToMove();

                if(!pociski[bulletTabPos].move())
                    buf = false;
            }

            if(!pociski[bulletTabPos].hit and counter % 2 == 0)
            {
                if(pociski[bulletTabPos].mine and pociski[bulletTabPos].bulletType == "minigun")
                {
                    for(int bulletTabPos2 = pociski.size() - 1; bulletTabPos2 >= 0; bulletTabPos2--)
                    {
                        if(pociski[bulletTabPos2].mine == false and pociski[bulletTabPos2].sprite.getGlobalBounds().contains(pociski[bulletTabPos].sprite.getPosition()))
                        {
                            pociski[bulletTabPos].hit = true;
                            pociski[bulletTabPos2].hit = true;
                            break;
                        }
                    }
                }

                for(int meteorTabPos = meteors.size() - 1; meteorTabPos >= 0; meteorTabPos--)
                {
                    if(meteors[meteorTabPos].contains(pociski[bulletTabPos].sprite.getPosition(), pociski[bulletTabPos].damage))
                    {
                        meteors[meteorTabPos].push(pociski[bulletTabPos].unitVector, pociski[bulletTabPos].mass);
                        pociski[bulletTabPos].hit = true;
                    }
                }

                if(!pociski[bulletTabPos].mine and ((!statek.destroyed and statek.sprite.getGlobalBounds().contains(pociski[bulletTabPos].sprite.getPosition()) and Collision::PixelPerfectTest(pociski[bulletTabPos].sprite, statek.sprite)) or (statek.destroyed and statek.wybuch.currentFrameSprite.getGlobalBounds().contains(pociski[bulletTabPos].sprite.getPosition()) and Collision::PixelPerfectTest(pociski[bulletTabPos].sprite, statek.wybuch.currentFrameSprite))))
                {
                        int dmg = pociski[bulletTabPos].damage + ((random() % (pociski[bulletTabPos].modifier * 2 + 1)) - pociski[bulletTabPos].modifier);
                        pociski[bulletTabPos].hit = true;
                        statek.shieldRegainingCounter = 0;
                        statek.getDamage(dmg);

                        if(statek.HP <= 0)
                            statek.destroyed = true;
                }

                for(int enemiesTabPos = enemies.size() - 1; enemiesTabPos >= 0; enemiesTabPos--)
                {
                    if(pociski[bulletTabPos].mine and !enemies[enemiesTabPos].killed)
                    {
                        if(enemies[enemiesTabPos].sprite.getGlobalBounds().contains(pociski[bulletTabPos].sprite.getPosition()) and Collision::PixelPerfectTest(enemies[enemiesTabPos].sprite, pociski[bulletTabPos].sprite))
                        {
                            int dmg = pociski[bulletTabPos].damage + ((random() % (pociski[bulletTabPos].modifier * 2 + 1)) - pociski[bulletTabPos].modifier);
                            pociski[bulletTabPos].hit = true;
                            kursor.hitInFrame();

                            enemies[enemiesTabPos].takeDamage(dmg);
                        }
                    }
                }
            }
        }

        for(int sawTabPos = saws.size() - 1; sawTabPos >= 0; sawTabPos--)
        {
            if(!saws[sawTabPos].destroyed and !saws[sawTabPos].hit)
            {
                if(first)
                    saws[sawTabPos].prepareToMove();

                if(!saws[sawTabPos].move())
                    buf = false;
            }

            for(int meteorTabPos = meteors.size() - 1; meteorTabPos >= 0; meteorTabPos--)
            {
                if(!saws[sawTabPos].isTargetReached() and meteors[meteorTabPos].contains(saws[sawTabPos].sprite.getPosition(), saws[sawTabPos].damage))
                {
                    meteors[meteorTabPos].push(-saws[sawTabPos].unitVector, saws[sawTabPos].mass);
                    saws[sawTabPos].hitTarget();
                }
            }

            if(!saws[sawTabPos].hit and counter % 2 == 0)
            {
                if(!saws[sawTabPos].mine and ((!statek.destroyed and statek.sprite.getGlobalBounds().contains(saws[sawTabPos].sprite.getPosition()) and Collision::PixelPerfectTest(saws[sawTabPos].sprite, statek.sprite)) or (statek.destroyed and statek.wybuch.currentFrameSprite.getGlobalBounds().contains(saws[sawTabPos].sprite.getPosition()) and Collision::PixelPerfectTest(saws[sawTabPos].sprite, statek.wybuch.currentFrameSprite))))
                {
                        int dmg = saws[sawTabPos].damage + ((random() % (saws[sawTabPos].modifier * 2 + 1)) - saws[sawTabPos].modifier);
                        saws[sawTabPos].hitTarget();
                        statek.shieldRegainingCounter = 0;
                        statek.getDamage(dmg);

                        if(statek.HP <= 0)
                            statek.destroyed = true;
                }

                for(int enemiesTabPos = enemies.size() - 1; enemiesTabPos >= 0; enemiesTabPos--)
                {
                    if(saws[sawTabPos].mine and !enemies[enemiesTabPos].killed)
                    {
                        if(enemies[enemiesTabPos].sprite.getGlobalBounds().contains(saws[sawTabPos].sprite.getPosition()) and Collision::PixelPerfectTest(enemies[enemiesTabPos].sprite, saws[sawTabPos].sprite))
                        {
                            int dmg = saws[sawTabPos].damage + ((random() % (saws[sawTabPos].modifier * 2 + 1)) - saws[sawTabPos].modifier);
                            saws[sawTabPos].hitTarget();
                            kursor.hitInFrame();

                            enemies[enemiesTabPos].takeDamage(dmg);
                        }
                    }
                }
            }
        }

        allMoved = buf;
    }
    for(int bulletTabPos = pociski.size() - 1; bulletTabPos >= 0; bulletTabPos--)
        if(!pociski[bulletTabPos].hit and shouldRender(pociski[bulletTabPos].sprite.getPosition()))
                app << pociski[bulletTabPos].sprite;

    for(int sawTabPos = saws.size() - 1; sawTabPos >= 0; sawTabPos--)
        if(!saws[sawTabPos].hit and shouldRender(saws[sawTabPos].sprite.getPosition()))
                app << saws[sawTabPos].sprite;

    {
        sort(pociski.begin(), pociski.end());
        bool anyToDelete = false;
        vector<bullet>::iterator _from = pociski.end();
        for(int bulletTabPos = pociski.size() - 1; bulletTabPos >= 0; bulletTabPos--)
        {
            if(!pociski[bulletTabPos].destroyed)
                break;
            else
                anyToDelete = true;

            _from--;
        }
        if(anyToDelete)
            pociski.erase(_from, pociski.end());
    }

    {
        sort(saws.begin(), saws.end());
        bool anyToDelete = false;
        vector<saw>::iterator _from = saws.end();
        for(int sawTabPos = saws.size() - 1; sawTabPos >= 0; sawTabPos--)
        {
            if(!saws[sawTabPos].destroyed)
                break;
            else
                anyToDelete = true;

            _from--;
        }
        if(anyToDelete)
            saws.erase(_from, saws.end());
    }
    //---------------

    //Rysowanie przeciwników
    for(int enemiesTabPos = enemies.size() - 1; enemiesTabPos >= 0; enemiesTabPos--)
    {
        if(!enemies[enemiesTabPos].killed)
            app << enemies[enemiesTabPos].sprite;

        if(enemies[enemiesTabPos].ID == statek.targetID)
        {
            if(!enemies[enemiesTabPos].killed)
            {
                statek.target = enemies[enemiesTabPos].sprite.getPosition();
                statek.enemySelected = true;
            }
            else
                statek.enemySelected = false;
        }

        enemies[enemiesTabPos].sprite.setOrigin(Collision::GetSpriteSize(enemies[enemiesTabPos].sprite).x / 2, Collision::GetSpriteSize(enemies[enemiesTabPos].sprite).y / 2);
        enemies[enemiesTabPos].fight_manager();

        if(enemies.size() < 2)
            enemies[enemiesTabPos].shouldAvoid1 = false;

        else
        {
            sf::Vector2f delta = enemies[enemies.size() - 1].sprite.getPosition() - enemies[enemiesTabPos].sprite.getPosition();
            float minimum = sqrt((delta.x * delta.x) + (delta.y * delta.y));
            sf::Vector2f minimumPos = enemies[enemies.size() - 1].sprite.getPosition();

            for(int i = enemies.size() - 1; i >= 0; i--)
            {
                if(i == enemiesTabPos)
                    continue;

                delta = enemies[i].sprite.getPosition() - enemies[enemiesTabPos].sprite.getPosition();
                if(sqrt((delta.x * delta.x) + (delta.y * delta.y)) < minimum)
                {
                    minimum = sqrt((delta.x * delta.x) + (delta.y * delta.y));
                    minimumPos = enemies[i].sprite.getPosition();
                }
            }

            enemies[enemiesTabPos].shouldAvoid1 = true;
            enemies[enemiesTabPos].avoid1 = minimumPos;
        }

        enemies[enemiesTabPos].move();
        enemies[enemiesTabPos].rotate();

        //Ustawianie tekstur
        if(enemies[enemiesTabPos].oldHP != enemies[enemiesTabPos].HP)
        {
            int percentHP = enemies[enemiesTabPos].HP;

            if(percentHP >= enemies[enemiesTabPos].fullHP - enemies[enemiesTabPos].fullHP / 5)
                enemies[enemiesTabPos].tekstura = enemies[enemiesTabPos].baseTexture + "a.png";

            else if(percentHP < enemies[enemiesTabPos].fullHP - enemies[enemiesTabPos].fullHP / 5 and percentHP >= enemies[enemiesTabPos].fullHP - (enemies[enemiesTabPos].fullHP / 5) * 2)
                enemies[enemiesTabPos].tekstura = enemies[enemiesTabPos].baseTexture + "b.png";

            else if(enemies[enemiesTabPos].fullHP - (enemies[enemiesTabPos].fullHP / 5) * 2 and percentHP >= enemies[enemiesTabPos].fullHP - (enemies[enemiesTabPos].fullHP / 5) * 3)
                enemies[enemiesTabPos].tekstura = enemies[enemiesTabPos].baseTexture + "c.png";

            else if(percentHP < enemies[enemiesTabPos].fullHP - (enemies[enemiesTabPos].fullHP / 5) * 3 and percentHP >= enemies[enemiesTabPos].fullHP / 5)
                enemies[enemiesTabPos].tekstura = enemies[enemiesTabPos].baseTexture + "d.png";

            else if(percentHP < enemies[enemiesTabPos].fullHP / 5)
                enemies[enemiesTabPos].tekstura = enemies[enemiesTabPos].baseTexture + "e.png";

            enemies[enemiesTabPos].oldHP = enemies[enemiesTabPos].HP;
            enemies[enemiesTabPos].load_textures(enemies[enemiesTabPos].tekstura);
        }
        //------------------

        if(!enemies[enemiesTabPos].killed)
        {
            sf::FloatRect rect;
            rect.height = screenY - 80;
            rect.width = screenX - 80;
            rect.top = screenCornerY + 40;
            rect.left = screenCornerX + 40;

            if(!rect.contains(enemies[enemiesTabPos].sprite.getPosition()))
            {
                sf::Vector2f A = statek.sprite.getPosition();
                sf::Vector2f B = enemies[enemiesTabPos].sprite.getPosition();

                float slope = (A.y - B.y) / (A.x - B.x);

                if(-rect.height / 2 <= slope * rect.width / 2 and slope * rect.width / 2 <=  rect.height /2)
                {
                    if(A.x < B.x)
                    {
                        sf::Vector2f C = sf::Vector2f(rect.left + rect.width, rect.top);
                        sf::Vector2f D = sf::Vector2f(rect.left + rect.width, rect.top + rect.height);

                        float x = ((B.x - A.x) * (D.x * C.y - D.y * C.x) - (D.x - C.x) * (B.x * A.y - B.y * A.x)) / ((B.y - A.y) * (D.x - C.x) - (D.y - C.y) * (B.x - A.x));
                        float y = ((D.y - C.y) * (B.x * A.y - B.y * A.x) - (B.y - A.y) * (D.x * C.y - D.y * C.x)) / ((D.y - C.y) * (B.x - A.x) - (B.y - A.y) * (D.x - C.x));

                        enemyArrow.setPosition(x, y);
                    }
                    else
                    {
                        sf::Vector2f C = sf::Vector2f(rect.left, rect.top);
                        sf::Vector2f D = sf::Vector2f(rect.left, rect.top + rect.height);

                        float x = ((B.x - A.x) * (D.x * C.y - D.y * C.x) - (D.x - C.x) * (B.x * A.y - B.y * A.x)) / ((B.y - A.y) * (D.x - C.x) - (D.y - C.y) * (B.x - A.x));
                        float y = ((D.y - C.y) * (B.x * A.y - B.y * A.x) - (B.y - A.y) * (D.x * C.y - D.y * C.x)) / ((D.y - C.y) * (B.x - A.x) - (B.y - A.y) * (D.x - C.x));

                        enemyArrow.setPosition(x, y);
                    }
                }
                else
                {
                    if(A.y > B.y)
                    {
                        sf::Vector2f C = sf::Vector2f(rect.left, rect.top);
                        sf::Vector2f D = sf::Vector2f(rect.left + rect.width, rect.top);

                        float x = ((B.x - A.x) * (D.x * C.y - D.y * C.x) - (D.x - C.x) * (B.x * A.y - B.y * A.x)) / ((B.y - A.y) * (D.x - C.x) - (D.y - C.y) * (B.x - A.x));
                        float y = ((D.y - C.y) * (B.x * A.y - B.y * A.x) - (B.y - A.y) * (D.x * C.y - D.y * C.x)) / ((D.y - C.y) * (B.x - A.x) - (B.y - A.y) * (D.x - C.x));

                        enemyArrow.setPosition(x, y);
                    }
                    else
                    {
                        sf::Vector2f C = sf::Vector2f(rect.left, rect.top + rect.height);
                        sf::Vector2f D = sf::Vector2f(rect.left + rect.width, rect.top + rect.height);

                        float x = ((B.x - A.x) * (D.x * C.y - D.y * C.x) - (D.x - C.x) * (B.x * A.y - B.y * A.x)) / ((B.y - A.y) * (D.x - C.x) - (D.y - C.y) * (B.x - A.x));
                        float y = ((D.y - C.y) * (B.x * A.y - B.y * A.x) - (B.y - A.y) * (D.x * C.y - D.y * C.x)) / ((D.y - C.y) * (B.x - A.x) - (B.y - A.y) * (D.x - C.x));

                        enemyArrow.setPosition(x, y);
                    }
                }

                enemyArrow.setRotation(rotate_to_ff(enemyArrow.getPosition(), enemies[enemiesTabPos].sprite.getPosition()) + 90);
                app << enemyArrow;
            }
        }
        else
        {
            enemies[enemiesTabPos].eksplozja.play(enemies[enemiesTabPos].sprite.getPosition(), enemies[enemiesTabPos].sprite.getRotation());
            enemies[enemiesTabPos].wybuch.play(enemies[enemiesTabPos].sprite.getPosition(), enemies[enemiesTabPos].sprite.getRotation());

            if(enemies[enemiesTabPos].wybuch.finished and enemies[enemiesTabPos].eksplozja.finished)
                enemies.erase(enemies.begin() + enemiesTabPos);
        }

        for(unsigned int i = 0; i < rockets.size(); i++)
        {
            if(enemies[enemiesTabPos].ID == rockets[i].targetID)
            {
                enemies[enemiesTabPos].selected = true;

                if(!rockets[i].hit and Collision::PixelPerfectTest(rockets[i].sprite, enemies[enemiesTabPos].sprite))
                {
                    enemies[enemiesTabPos].takeDamage(rockets[i].damage);
                    rockets[i].hit = true;
                }
                else if(enemies[enemiesTabPos].killed)
                    rockets[i].hit = true;

                if(!rockets[i].hit)
                {
                    rockets[i].move(enemies[enemiesTabPos].sprite.getPosition());
                    app << rockets[i].sprite;
                }
                else
                {
                    rockets[i].explosion.play(rockets[i].sprite.getPosition(), rockets[i].sprite.getRotation());

                    if(rockets[i].explosion.finished)
                        rockets.erase(rockets.begin() + i);
                }
            }
            else
                enemies[enemiesTabPos].selected = false;
        }
    }
    //--------

    //rysowanie statku
    statek.shieldSprite.setPosition(statek.sprite.getPosition());
    statek.shieldSprite.setRotation(statek.sprite.getRotation());

    if(statek.shieldSprite.getColor().a - 4 > 0)
        statek.shieldSprite.setColor(sf::Color(255, 255, 255, statek.shieldSprite.getColor().a - 5));
    else if(statek.shieldSprite.getColor().a > 0)
        statek.shieldSprite.setColor(sf::Color(255, 255, 255, 0));

    app << statek.shieldSprite;

    if(!statek.destroyed)
        app << statek.sprite;

    if(statek.destroyed and !statek.destroyed_end)
    {
        statek.shieldSprite.setColor(sf::Color(0, 0, 0, 0));

        statek.wybuch.play(statek.sprite.getPosition(), statek.sprite.getRotation());
        statek.eksplozja.play(statek.sprite.getPosition(), statek.sprite.getRotation());
        if(statek.wybuch.finished)
            statek.destroyed_end = true;
    }
    //-----------------

    //rysowanie eksplozji
    for(int bulletTabPos = pociski.size() - 1; bulletTabPos >= 0; bulletTabPos--)
    {
        if(pociski[bulletTabPos].hit)
        {
            pociski[bulletTabPos].wybuch.play(pociski[bulletTabPos].sprite.getPosition(), pociski[bulletTabPos].sprite.getRotation());
            pociski[bulletTabPos].freeze = true;

            if(pociski[bulletTabPos].wybuch.finished)
                pociski[bulletTabPos].destroyed = true;
        }
    }
    //-----------------

    //Dusze
    for(int soulTabPos = souls.size() - 1; soulTabPos >= 0; soulTabPos--)
    {
        souls[soulTabPos].sprite.setTexture(*textureManager.get("assets/graphics/UI/game/soul.png"));

        sf::Vector2f moved = souls[soulTabPos].sprite.getPosition();
        souls[soulTabPos].move(statek.sprite);
        moved -= souls[soulTabPos].sprite.getPosition();
        moved = sf::Vector2f(moved.x / 2, moved.y / 2);

        if(shouldRender(souls[soulTabPos].sprite.getPosition()))
        {
            soulsAddons tmp;
            tmp.soulCopy.sprite = souls[soulTabPos].sprite;
            tmp.pos = souls[soulTabPos].sprite.getPosition();
            tmp.alpha = 255;
            soulAddons.push_back(tmp);
            tmp.pos += moved;
            soulAddons.push_back(tmp);
            tmp.pos -= moved;

            app << souls[soulTabPos].sprite;

            if(statek.sprite.getGlobalBounds().contains(souls[soulTabPos].sprite.getPosition()) and Collision::PixelPerfectTest(souls[soulTabPos].sprite, statek.sprite))
            {
                int soulI = souls[soulTabPos].XP;
                statek.XP += soulI;

                //Przeskakiwanie szarych pasków etc.
                statek.shieldRegainingCounter = statek.shieldRegerationTimeInFrames;

                if(statek.ammoRegainingCounter > 0 and statek.ammoRegainingCounter < 180)
                    statek.ammoRegainingCounter = 180;
                else
                {
                    if(statek.ammo + soulI * 200 > statek.ammoMax)
                        statek.ammo = statek.ammoMax;
                    else
                        statek.ammo += soulI * 200;
                }

                if(statek.HP < statek.maxHP)
                    statek.HP++;

                if(statek.shield > 0 and statek.shield + soulI * 50 > statek.shieldMax)
                    statek.shield = statek.shieldMax;
                else if(statek.shield > 0)
                    statek.shield += soulI * 50;
                //-----------------------------

                souls.erase(souls.begin() + soulTabPos);
            }
        }
    }

    for(int soulTabPos = soulAddons.size() - 1; soulTabPos >= 0; soulTabPos--)
    {
        int i = 20 * timeModifier;

        if(soulAddons[soulTabPos].alpha - i > 0)
            soulAddons[soulTabPos].alpha -= i;
        else
            soulAddons[soulTabPos].alpha = 0;

        soulAddons[soulTabPos].soulCopy.sprite.setPosition(soulAddons[soulTabPos].pos);
        soulAddons[soulTabPos].soulCopy.sprite.setColor(sf::Color(255, 255, 255, (int) soulAddons[soulTabPos].alpha));
        app << soulAddons[soulTabPos].soulCopy.sprite;

        if(soulAddons[soulTabPos].alpha == 0)
            soulAddons.erase(soulAddons.begin() + soulTabPos);
    }
    //-----

    //Komunikaty o zadanych obrażeniach
    for(unsigned int i = 0; i < damageInfo.size(); i++)
    {
        damageInfo[i].move(sf::Vector2f(0, -4) * timeModifier);
        damageInfo[i].setAlpha(damageInfo[i].getAlpha() - 8 * timeModifier);

        if(damageInfo[i].getAlpha() == 0)
            damageInfo.erase(damageInfo.begin() + i);
        else
            app << damageInfo[i];
    }
    //---------------------------------

    //Czarne dziury
    if(sf::Mouse::isButtonPressed(sf::Mouse::Middle) and !space::createBlackHole)
    {
        space::createBlackHole = true;
        textureManager.add("assets/graphics/background/blackhole.png");
        space::blackHole tmp(static_cast<sf::Vector2f>(sf::Mouse::getPosition()) + sf::Vector2f(screenCornerX, screenCornerY), textureManager.get("assets/graphics/background/blackhole.png"));
        blackHoles.push_back(tmp);
    }
    else if(!sf::Mouse::isButtonPressed(sf::Mouse::Middle) and space::createBlackHole)
        space::createBlackHole = false;

    for(int blackHolesTabPos = blackHoles.size() - 1; blackHolesTabPos >= 0; blackHolesTabPos--)
    {
        for(int bulletTabPos = pociski.size() - 1; bulletTabPos >= 0; bulletTabPos--)
        {
            sf::Vector2f kierunek = blackHoles[blackHolesTabPos].getPosition() - pociski[bulletTabPos].sprite.getPosition();
            float distance = sqrt((kierunek.x * kierunek.x) + (kierunek.y * kierunek.y));

            if(distance < 250)
            {
                float angleModifier = pociski[bulletTabPos].sprite.getRotation() - rotate_to_ff(pociski[bulletTabPos].sprite.getPosition(), blackHoles[blackHolesTabPos].getPosition());
                if(angleModifier > 180)
                    angleModifier -= 360;

                angleModifier = Map(angleModifier, -90.f, 90.f, -1.f, 1.f);

                pociski[bulletTabPos].speed *= Map(distance, 0.f, 250.f, 1.05f, 1.015f);

                pociski[bulletTabPos].rotate(Map(distance, 50.f, 250.f, blackHoles[blackHolesTabPos].mass, 0.f) * angleModifier);
                pociski[bulletTabPos].CalculateDirection();
            }
            if(distance < 58)
                pociski[bulletTabPos].destroyed = true;
        }

        for(int sawTabPos = saws.size() - 1; sawTabPos >= 0; sawTabPos--)
        {
            if(saws[sawTabPos].isTargetReached())
                continue;

            sf::Vector2f kierunek = blackHoles[blackHolesTabPos].getPosition() - saws[sawTabPos].sprite.getPosition();
            float distance = sqrt((kierunek.x * kierunek.x) + (kierunek.y * kierunek.y));

            if(distance < 250)
            {
                float angleModifier = saws[sawTabPos].getPseudoRotation() - rotate_to_ff(saws[sawTabPos].sprite.getPosition(), blackHoles[blackHolesTabPos].getPosition());
                if(angleModifier > 180)
                    angleModifier -= 360;

                angleModifier = Map(angleModifier, -90.f, 90.f, -1.f, 1.f);

                saws[sawTabPos].rotate(Map(distance, 50.f, 250.f, blackHoles[blackHolesTabPos].mass, 0.f) * angleModifier);
            }
        }

        app << blackHoles[blackHolesTabPos];
    }
    //-------------

    //UI
    infoBackground.setPosition(screenCornerX + screenX - Collision::GetSpriteSize(infoBackground).x - 6, screenCornerY + screenY - Collision::GetSpriteSize(infoBackground).y - 30);
    app << infoBackground;

    ostringstream HPss;
    ostringstream XPss;
    ostringstream shieldSs;
    ostringstream ammoSs;
    ostringstream FPSss;

    //Ustawianie pozycji elementów UI
    if(direction.x != 0 or direction.y != 0)
    {
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
    }
    //-------------------------------

    app << terminal;

    float sum = frameTimes[0];
    for(int i = frameTimes.size() - 1; i >= 1; i--)
        sum += frameTimes[i];

    float fps = 1 / (sum / frameTimes.size());
    fps = round(fps);
    FPSss << "FPS: " << fps;
    FPStext.setString(FPSss.str());
    app << FPStext;

    XPss << statek.XP;
    XPtext.setString(languageManager.current().souls + XPss.str());
    app << XPtext;

    HPss << statek.HP;
    HPtext.setString(languageManager.current().healthPoints + HPss.str());
    app << HPtext;

    shieldSs << statek.shield;
    shieldText.setString(languageManager.current().shield + shieldSs.str());
    app << shieldText;

    ammoSs << statek.ammo;
    ammoText.setString(languageManager.current().hatred + ammoSs.str());
    app << ammoText;

    HPbar.setScale(static_cast <float> (statek.HP) / statek.maxHP, 1);
    app << HPbar;

    shieldBar.setScale(static_cast <float> (statek.shield) / statek.shieldMax, 1);
    app << shieldBar;

    regainingShieldBar.setScale(static_cast <float> (statek.shieldRegerationTimeInFrames - statek.shieldRegainingCounter) / statek.shieldRegerationTimeInFrames, 1);
    if(statek.shield == 0)
        app << regainingShieldBar;

    if(!Ready_to_shot)
        ammoBar.setColor(sf::Color(153, 0, 0));
    else
        ammoBar.setColor(sf::Color(255, 255, 0));

    ammoBar.setScale(static_cast <float> (statek.ammo) / statek.ammoMax, 1);
    app << ammoBar;

    noAmmoBar.setScale(static_cast <float> (180 - statek.ammoRegainingCounter) / 180, 1);
    if(statek.ammo == 0)
        app << noAmmoBar;

    if(statek.ammo == 0 and sf::Mouse::isButtonPressed(sf::Mouse::Left))
        app << releaseButton;
    //-----------------

    //rysowanie kursora
    if(Ready_to_shot)
        kursor.setTexture("assets/graphics/cursor/cursorGrey.png");
    else
        kursor.setTexture("assets/graphics/cursor/cursorRed.png");

    kursor.manageHit();

    app << kursor;

    if(kursor.lowAmmo)
    {
        kursor.LowAmmo(statek.ammo, statek.ammoMax);
        app << kursor.lowAmmoSprite;
    }

    if(kursor.highAmmo)
    {
        kursor.HighAmmo(statek.ammo, statek.ammoMax);
        app << kursor.highAmmoSprite;
    }
    //-----------------

    //obracanie obiektów
    rotator();
    //------------
}

#endif // DRAWER_H_INCLUDED
