#ifndef CONTROLS_H_INCLUDED
#define CONTROLS_H_INCLUDED

namespace controller
{
    class Controls
    {
    private:
        vector <sf::Event> events;
    public:
        //K_* - a-z, spacja
        //S_* - Alt i Shift
        //MB_* - przyciski myszy (l, r, m)
        //ARR_* - Strzałki (l, r, u, d)
        //MS_* - Scroll (u, d)


        //Wartości domyślne
      //Tylko klawiatura
        string playerUp = "K_w";
        string playerDown = "K_s";
        string playerLeft = "K_a";
        string playerRight = "K_d";

        string pause = "K_esc";
        string confirm = "K_enter";
        string dronesControl = "K_f";
      //----------------

      //Wymienne
        string playerShot = "K_enter";
        string droneShot = "MB_r";

        string nextWeapon = "MS_u";
        string previousWeapon = "MS_d";
      //--------
        //-----------------

        void load(Settings config);
        bool checkAction(string action);
    };

    bool Controls::checkAction(string action)
    {
        if(action[0] == 'M' and action[1] == 'B' and action[2] == '_')
        {
            if(action[3] == 'l')
                return sf::Mouse::isButtonPressed(sf::Mouse::Left);
            else if(action[3] == 'm')
                return sf::Mouse::isButtonPressed(sf::Mouse::Middle);
            else if(action[3] == 'r')
                return sf::Mouse::isButtonPressed(sf::Mouse::Right);
        }
        else if(action[0] == 'S' and action[1] == '_')
        {
            if(action[2] == 's' and action[3] == 'h' and action[4] == 'i' and action[5] == 'f' and action[6] == 't' and sf::Keyboard::isKeyPressed(sf::Keyboard::LShift))
                return true;

            else if(action[2] == 'a' and action[3] == 'l' and action[4] == 't' and sf::Keyboard::isKeyPressed(sf::Keyboard::LAlt))
                return true;
        }
        else if(action[0] == 'K' and action[1] == '_')
        {
            if(action[2] == 'e' and action[3] == 'n' and action[4] == 't' and action[5] == 'e' and action[6] == 'r' and sf::Keyboard::isKeyPressed(sf::Keyboard::Return))
                return true;

            else if(action[2] == 'e' and action[3] == 's' and action[4] == 'c' and sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
                return true;

            else if(action[2] == ' ' and sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
                return true;

            else
            {
                for(int i = sf::Keyboard::A; i <= sf::Keyboard::Z; i++)
                {
                    if(sf::Keyboard::isKeyPressed(static_cast <sf::Keyboard::Key> (i)))
                    {
                        if((char) (i + 97) == action[2])
                            return true;
                    }
                }

                for(int i = sf::Keyboard::Num0; i <= sf::Keyboard::Num9; i++)
                {
                    if(sf::Keyboard::isKeyPressed(static_cast <sf::Keyboard::Key> (i)))
                    {
                        if((char) (i - 26) == action[2] - 48)
                            return true;
                    }
                }
            }
        }
        else if(action[0] == 'A' and action[1] == 'R' and action[2] == 'R' and action[3] == '_')
        {
            for(int i = sf::Keyboard::Left; i <= sf::Keyboard::Down; i++)
            {
                if(sf::Keyboard::isKeyPressed(static_cast <sf::Keyboard::Key> (i)))
                {
                    int tmp;

                    if(action[4] == 'l')
                        tmp = 71;
                    else if(action[4] == 'r')
                        tmp = 72;
                    else if(action[4] == 'u')
                        tmp = 73;
                    else if(action[4] == 'd')
                        tmp = 74;

                    if(i == tmp)
                      return true;
                }
            }
        }
        else if(action[0] == 'M' and action[1] == 'S' and action[2] == '_')
        {
            if(action[3] == 'u' and mouseWheelDelta >= 1)
            {
                mouseWheelDelta = 0;
                return true;
            }
            if(action[3] == 'd' and mouseWheelDelta <= -1)
            {
                mouseWheelDelta = 0;
                return true;
            }
        }

        return false;
    }

    void Controls::load(Settings config)
    {
        xml_node<> *Root = config.settingsFile -> getRootNode();
        xml_node<> *currentNode = Root -> first_node("config");

        if(currentNode != NULL)
        {
            playerRight = config.settingsFile -> getNodeAttribute(currentNode, "playerRight");
            playerLeft = config.settingsFile -> getNodeAttribute(currentNode, "playerLeft");
            playerDown = config.settingsFile -> getNodeAttribute(currentNode, "playerDown");
            playerUp = config.settingsFile -> getNodeAttribute(currentNode, "playerUp");
            playerShot = config.settingsFile -> getNodeAttribute(currentNode, "playerShot");
            droneShot = config.settingsFile -> getNodeAttribute(currentNode, "droneShot");
            dronesControl = config.settingsFile -> getNodeAttribute(currentNode, "dronesControl");

            confirm = config.settingsFile -> getNodeAttribute(currentNode, "confirm");
            pause = config.settingsFile -> getNodeAttribute(currentNode, "pause");

            nextWeapon = config.settingsFile -> getNodeAttribute(currentNode, "nextWeapon");
            previousWeapon = config.settingsFile -> getNodeAttribute(currentNode, "previousWeapon");
        }
    }
};

controller::Controls characterControler;

#endif // CONTROLS_H_INCLUDED
