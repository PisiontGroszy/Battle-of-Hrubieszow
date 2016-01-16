#ifndef CONSOLE_H_INCLUDED
#define CONSOLE_H_INCLUDED

namespace sf
{
    namespace gui
    {
        class Console : public sf::Drawable
        {
        private:
            sf::Vector2i consoleSize;
            sf::RectangleShape consoleShape;
            sf::RectangleShape cursorShape;

            string currentCommand;
            sf::Text currentCommandText;

            vector <string> commands;
            vector <sf::Text> consoleText;

            bool _visible = false;
            virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

            luaVirtualMachine * LVM;
            int cursorPos = 1;
        public:
            Console() {};
            Console(int sizeX, int sizeY, sf::Color color);

            void create(int sizeX, int sizeY, sf::Color color);

            void setPosition(sf::Vector2f vect);
            sf::Vector2f getPosition();
            void move(sf::Vector2f vect);

            void visible(bool show);
            bool isVisible();

            sf::Vector2i getSize();

            void moveCursor(int diff);
            void insertCharacter(char c);
            void printData(string data, sf::Color color);

            void update();
        };

        void Console::create(int sizeX, int sizeY, sf::Color color)
        {
            consoleSize.x = sizeX;
            consoleSize.y = sizeY;

            consoleShape.setSize(static_cast<sf::Vector2f>(consoleSize));
            consoleShape.setFillColor(color);
            consoleShape.setOutlineColor(sf::Color(255, 255, 255));
            consoleShape.setOutlineThickness(3);

            cursorShape.setSize(sf::Vector2f(2.f, 15.f));
            cursorShape.setFillColor(sf::Color(20, 255, 20));

            currentCommandText.setCharacterSize(15);
            currentCommandText.setColor(sf::Color(20, 255, 20));
            currentCommandText.setFont(roboto);

            currentCommand = "$ ";

            LVM = new luaVirtualMachine("assets/lua/console.lua");
            LVM -> registerFunc("read", (void*) api::api_read);
            LVM -> registerFunc("flush", (void*) api::api_flush);
            LVM -> registerFunc("write", (void*) api::api_write);
            LVM -> registerFunc("sleep", (void*) api::api_sleep);
            LVM -> registerFunc("writeln", (void*) api::api_writeln);

            LVM -> registerFunc("SHset", (void*) gameApi::api_SHset);
            LVM -> registerFunc("HPset", (void*) gameApi::api_HPset);

            LVM -> registerFunc("SHgetMax", (void*) gameApi::api_SHgetMax);
            LVM -> registerFunc("HPgetMax", (void*) gameApi::api_HPgetMax);

            LVM -> launch();
        }
        Console::Console(int sizeX, int sizeY, sf::Color color)
        {
            create(sizeX, sizeY, color);
        }

        void Console::setPosition(sf::Vector2f vect)
        {
            consoleShape.setPosition(vect);
            cursorShape.setPosition(currentCommandText.findCharacterPos(cursorPos));
            currentCommandText.setPosition(vect + sf::Vector2f(5, consoleSize.y - 20));

            for(int i = consoleText.size() - 1, j = 1; i >= 0; i--, j++)
                consoleText[i].setPosition(currentCommandText.getPosition() + sf::Vector2f(0, -15 * j));
        }
        sf::Vector2f Console::getPosition()
        {
            return consoleShape.getPosition();
        }
        void Console::move(sf::Vector2f vect)
        {
            this -> setPosition(this -> getPosition() + vect);
        }

        void Console::draw(sf::RenderTarget& target, sf::RenderStates states) const
        {
            if(_visible)
            {
                target.draw(consoleShape, states);
                target.draw(currentCommandText, states);
                target.draw(cursorShape, states);

                for(int i = consoleText.size() - 1; i >= 0; i--)
                    target.draw(consoleText[i], states);
            }
        }

        void Console::visible(bool show)
        {
            _visible = show;
        }
        bool Console::isVisible()
        {
            return _visible;
        }

        sf::Vector2i Console::getSize()
        {
            return consoleSize;
        }

        void Console::moveCursor(int diff)
        {
            cursorPos = limit(cursorPos + diff, 1, currentCommand.size() - 1);
        }
        void Console::insertCharacter(char c)
        {
            if(LVM -> sentData())
                return;

            if(c != 8 and c != 9 and c != 13 and c != 127)
            {
                currentCommand.insert(currentCommand.begin() + cursorPos, c);
                cursorPos++;
            }
            else if(c == 8 and cursorPos > 1)
            {
                currentCommand.erase(currentCommand.begin() + cursorPos - 1);
                cursorPos--;
            }
            else if(c == 127 and cursorPos + 1 < currentCommand.size())
            {
                currentCommand.erase(currentCommand.begin() + cursorPos);
            }
            else if(c == 13 and currentCommand.size() > 0 and LVM -> reguiresData())
            {
                currentCommand.erase(currentCommand.begin());
                currentCommand.erase(currentCommand.end() - 1);
                commands.push_back(currentCommand);
                currentCommand.clear();
                currentCommand = "$ ";
                printData(string("$") + commands[commands.size() - 1], sf::Color(20, 255, 20));
                LVM -> putstring(commands[commands.size() - 1]);
                cursorPos = 1;
            }
            currentCommandText.setString(currentCommand);
        }
        void Console::printData(string data, sf::Color color)
        {
            if(data.size() == 0)
                return;

            sf::Text tmp;
            tmp.setCharacterSize(15);
            tmp.setColor(color);
            tmp.setFont(roboto);
            tmp.setString(data);
            consoleText.push_back(tmp);

            for(int i = consoleText.size() - 1, j = 1; i >= 0; i--, j++)
            {
                if(currentCommandText.getPosition().y - (15 * j) > consoleShape.getPosition().y)
                    consoleText[i].setPosition(currentCommandText.getPosition() + sf::Vector2f(0, -15 * j));
                else
                    consoleText.erase(consoleText.begin() + i);
            }
        }

        void Console::update()
        {
            cursorShape.setPosition(currentCommandText.findCharacterPos(cursorPos));
            while(LVM -> sentData())
            {
                ColorAndText tmp = LVM -> getstring();

                string s;
                for(int i = 0; i < tmp.text.size(); i++)
                {
                    if(tmp.text[i] != '\n')
                        s += tmp.text[i];
                    else
                    {
                        printData(s, tmp.color);
                        s.clear();
                    }
                }
            }
        }
    }
}
sf::gui::Console terminal;

#endif // CONSOLE_H_INCLUDED
