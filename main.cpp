#define PI 3.14
#define HALF_PI 1.57

#include <algorithm>
#include <string>
#include <iostream>
#include <sstream>
#include <iomanip>
#include <string>
#include <fstream>
#include <math.h>
#include <random>
#include <atomic>
#include <cstring>

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

#include "RapidXML/rapidxml.hpp"
#include "RapidXML/rapidxml_utils.hpp"
#include "RapidXML/rapidxml_print.hpp"

#include "lua/LVM.h"
#include "lua/api.h"

using namespace std;
using namespace rapidxml;

#include "collision/collision.h"

#include "base/safeNumbers.h"
#include "base/math.h"
#include "base/xmlReader.h"
#include "base/settings.h"
#include "base/SFMLstream.h"
#include "base/languages.h"
#include "base/textureManager.h"
#include "base/preinit.h"
#include "base/cursor.h"
#include "base/animation.h"
#include "base/controls.h"
#include "base/tile.h"
#include "base/console.h"

#include "base/numbers.h"
#include "base/spaceObjects.h"

#include "GUI/button.h"
#include "GUI/slider.h"
#include "GUI/checkbox.h"

void menu();

#include "menu/settingsScreen.h"

#include "battle/pause.h"
#include "battle/battle_classess.h"
#include "battle/battle_init.h"
#include "battle/battle_drawer.h"
#include "battle/battle.h"

#include "menu/loadingScreen.h"
#include "menu/menu.h"

#include "lua/advencedAPI.h"

int main()
{
    //inicjalizacja tekstur, dźwięków itd.
    app.create(sf::VideoMode(sf::VideoMode::getDesktopMode().width, sf::VideoMode::getDesktopMode().height, 32), "Galactical Killer", sf::Style::Fullscreen);

    view = app.getDefaultView();

    viewScale = 1080.f / screenY;
    screenX *= viewScale;
    screenY *= viewScale;

    app.setView(view);
    kursor.init("assets/graphics/cursor/cursorGrey.png");
    init_textures();
    init_positions();

    //Tła
    mapTile.load("1", 255);
    map2Tile.load("2", 230);
    map3Tile.load("3", 230);
    //---

    textureManager.add("assets/graphics/UI/game/arrow.png", true);
    enemyArrow.setTexture(*textureManager.get("assets/graphics/UI/game/arrow.png"));
    enemyArrow.setOrigin(20, 20);

    textureManager.add("assets/graphics/UI/game/info.png");
    infoBackground.setTexture(*textureManager.get("assets/graphics/UI/game/info.png"));
    infoBackground.setColor(sf::Color(255, 255, 255, 64));

    textureManager.add("assets/graphics/UI/game/HPbar.png");
    HPbar.setTexture(*textureManager.get("assets/graphics/UI/game/HPbar.png"));

    textureManager.add("assets/graphics/UI/game/shieldBar.png");
    shieldBar.setTexture(*textureManager.get("assets/graphics/UI/game/shieldBar.png"));

    textureManager.add("assets/graphics/UI/game/RegainingShieldBar.png");
    regainingShieldBar.setTexture(*textureManager.get("assets/graphics/UI/game/RegainingShieldBar.png"));

    textureManager.add("assets/graphics/UI/game/ammoBar.png");
    ammoBar.setTexture(*textureManager.get("assets/graphics/UI/game/ammoBar.png"));

    textureManager.add("assets/graphics/UI/game/noAmmoBar.png");
    noAmmoBar.setTexture(*textureManager.get("assets/graphics/UI/game/noAmmoBar.png"));
    //------------

    //Inicjalizacja czcionek, tekstów itd.
    roboto.loadFromFile("assets/fonts/Roboto.ttf");
    bitFont.loadFromFile("assets/fonts/BitFont.ttf");

    FPStext.setFont(bitFont);
    FPStext.setCharacterSize(40);
    FPStext.setColor(sf::Color::Green);

    XPtext.setFont(bitFont);
    XPtext.setCharacterSize(50);
    XPtext.setColor(sf::Color::White);

    HPtext.setFont(bitFont);
    HPtext.setCharacterSize(20);
    HPtext.setColor(sf::Color::White);

    shieldText.setFont(bitFont);
    shieldText.setCharacterSize(20);
    shieldText.setColor(sf::Color::White);

    ammoText.setFont(bitFont);
    ammoText.setCharacterSize(20);
    ammoText.setColor(sf::Color::White);

    releaseButton.setFont(bitFont);
    releaseButton.setCharacterSize(20);
    releaseButton.setColor(sf::Color::Red);
    //------------

    //Gra
    menu();

    ostringstream gameOver;
    gameOver << "\nXP: " << statek.XP << "\nHP: " << statek.HP << "\nShield: " << statek.shield << endl;
    cout << gameOver.str();
    //------------

    //Zamykanie gry
    app.soundsManager.getMusic() -> stop();
    app.close();
    //-------------

    return EXIT_SUCCESS;
}
