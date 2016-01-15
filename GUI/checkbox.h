#ifndef CHECKBOX_H_INCLUDED
#define CHECKBOX_H_INCLUDED

namespace sf
{
    namespace gui
    {
        class Checkbox : public sf::Drawable
        {
        private:
            bool state;
            bool focus;

            sf::Sprite box;
            sf::Sprite check;

            virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
        public:
            Checkbox(textureManager & tm, sf::Vector2f position, float _size, string dir, bool _state);

            bool getCurrentState();
            void setCurrentState(bool _state);

            void update(Event event);
        };

        void Checkbox::draw(sf::RenderTarget& target, sf::RenderStates states) const
        {
            target.draw(box, states);
            target.draw(check, states);
        }

        Checkbox::Checkbox(textureManager & tm, sf::Vector2f position, float _size, string dir, bool _state)
        {
            tm.add(dir + "box.png");
            box.setTexture(*tm.get(dir + "box.png"));
            box.setScale(_size, _size);
            box.setPosition(position);

            tm.add(dir + "check.png");
            check.setTexture(*tm.get(dir + "check.png"));
            check.setScale(_size, _size);
            check.setPosition(position);

            state = _state;
            focus = false;
        }

        bool Checkbox::getCurrentState()
        {
            return state;
        }
        void Checkbox::setCurrentState(bool _state)
        {
            state = _state;
        }

        void Checkbox::update(Event event)
        {
            if(!event.type == sf::Event::MouseButtonPressed and !event.type == sf::Event::MouseMoved)
                return;

            sf::Vector2f mouseCoords = sf::Vector2f(sf::Mouse::getPosition().x * viewScale + screenCornerX, sf::Mouse::getPosition().y * viewScale + screenCornerY);

            if(event.type == sf::Event::MouseMoved)
                focus = box.getGlobalBounds().contains(mouseCoords);

            if(event.type == sf::Event::MouseButtonPressed and focus)
                state = !state;

            if(state)
                check.setColor(sf::Color(255, 255, 255, 255));
            else if(focus)
                check.setColor(sf::Color(255, 255, 255, 127));
            else
                check.setColor(sf::Color(255, 255, 255, 0));
        }
    }
}

#endif // CHECKBOX_H_INCLUDED
