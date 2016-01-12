#ifndef LOADINGSCREEN_H_INCLUDED
#define LOADINGSCREEN_H_INCLUDED

void loadingScreen()
{
    sf::Clock timer;
    sf::Sprite SFMLlogo;
    sf::Texture SFMLlogoT;

    SFMLlogoT.loadFromFile("assets/graphics/UI/mainMenu/sfLogo.png");

    SFMLlogo.setTexture(SFMLlogoT);
    SFMLlogo.setPosition(screenCornerX + 10, screenCornerY + screenY - 100);

    while(timer.getElapsedTime().asSeconds() < 1.f)
    {
        app << sf::Color(0, 0, 0);

        if(timer.getElapsedTime().asSeconds() < 1.f)
            SFMLlogo.setColor(sf::Color(255, 255, 255, (timer.getElapsedTime().asSeconds() / 1.f) * 255));

        app << SFMLlogo;
        app.display();
    }

    cout << "-----Loading screen (" << date() << ")-----" << endl;

    cout << "Loading settings... ";
    settings.load();
    cout << "[OK]" << endl;

    cout << "Setting framerate controller... ";
    app.setVerticalSyncEnabled(false);

    string FPScontroller = settings.FPScontroller;
    if(FPScontroller == "v-sync")
    {
        app.setVerticalSyncEnabled(true);
        cout << "(v-sync) [OK]" << endl;
    }
    else if(FPScontroller == "custom")
    {
        app.setFramerateLimit(settings.FPSlimit);
        cout << "(custom: " << settings.FPSlimit << ") [OK]" << endl;
    }
    else if(FPScontroller == "none")
    {
        cout << "(none) it can cause screen tearing etc. [WARNING]" << endl;
    }
    else
    {
        cout << "ERROR: unknown controller, using \"v-sync\" [fail]" << endl;
        app.setVerticalSyncEnabled(true);
    }

    cout << "Loading sounds... ";
    app.soundsManager.init(settings);
    app.soundsManager.loadFromFile("assets/sounds/weapons/crossbow.flac", "crossbow", 30);
    app.soundsManager.loadFromFile("assets/sounds/music.wav", "russianMusic", 50);
    app.soundsManager.createMusic(app.soundsManager.getIdByName("russianMusic"));
    cout << "[OK]" << endl;

    cout << "Loading animations... ";
    xml::xmlDocument doc("assets/xml/animations.xml");
    xml_node<> *node = doc.getRootNode();
    node = node -> first_node();

    while(node != NULL)
    {
        loadAnimationTextures(xml::getNodeAttribute(node, "file"));
        node = node -> next_sibling();
    }
    cout << "[OK]" << endl;

    cout << "Loading languages... ";
    languageManager.load("assets/xml/texts.xml");
    cout << "[OK]" << endl;

    cout << "Loading language (" << languageManager.lang << ")... ";
    if(!languageManager.setLang())
        cout << "[fail]\nCould not load selected language, using default one." << endl;
    else
        cout << "[OK]" << endl;

    cout << "Loading graphics... ";
    textureManagerInit();
    cout << "[OK]" << endl;

    while(timer.getElapsedTime().asSeconds() < 2.f){}
}

#endif // LOADINGSCREEN_H_INCLUDED
