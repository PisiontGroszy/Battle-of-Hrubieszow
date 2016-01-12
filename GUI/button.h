#ifndef BUTTON_H_INCLUDED
#define BUTTON_H_INCLUDED

namespace sf
{
    namespace gui
    {
        class Button : public sf::Drawable
        {
        public:
            Button(sf::Vector2f Coords, sf::Texture texture1, sf::Texture texture2);

            void destroy();
            void update(Event event);
            void update();
            void setPosition(sf::Vector2f Coords);
            void setPosition(double x, double y);
            sf::Vector2f coords;
            sf::Sprite sprite;
            bool funcDone = false;

        private:
            virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

            sf::Vector2f mouseCoords;
            sf::Texture texture;
            sf::Texture Texture1;
            sf::Texture Texture2;
            bool toDelete = false;
            int state;
        };

        Button::Button(sf::Vector2f Coords, sf::Texture texture1, sf::Texture texture2)
        {
            coords = Coords;
            state = 0;

            Texture1 = texture1;
            Texture2 = texture2;
        }

        void Button::update(Event event)
        {
            if(event.type == sf::Event::MouseMoved)
            {
                mouseCoords = sf::Vector2f(event.mouseMove.x * viewScale + screenCornerX, event.mouseMove.y * viewScale + screenCornerY);

                if(sprite.getGlobalBounds().contains(mouseCoords))
                    state = 1;
                else
                    state = 0;
            }
            if(event.type == sf::Event::MouseButtonPressed and state == 1)
                funcDone = true;

            if(state == 0)
                sprite.setTexture(Texture1);
            else if(state == 1)
                sprite.setTexture(Texture2);

            sprite.setPosition(coords);
        }

        void Button::update()
        {
            mouseCoords = sf::Vector2f(sf::Mouse::getPosition(app).x + screenCornerX, sf::Mouse::getPosition(app).x + screenCornerY);

            if(sprite.getGlobalBounds().contains(mouseCoords))
                state = 1;
            else
                state = 0;

            if(state == 0)
                sprite.setTexture(Texture1);

            else if(state == 1)
                sprite.setTexture(Texture2);

            sprite.setPosition(coords);
        }

        void Button::destroy()
        {
            toDelete = true;
        }

        void Button::setPosition(sf::Vector2f Coords)
        {
            coords = Coords;
        }

        void Button::setPosition(double x, double y)
        {
            coords = sf::Vector2f(x, y);
        }

        void Button::draw(sf::RenderTarget& target, sf::RenderStates states) const
        {
            target.draw(sprite, states);
        }
    };
};

#endif // BUTTON_H_INCLUDED
