#ifndef SLIDER_H_INCLUDED
#define SLIDER_H_INCLUDED

namespace sf
{
    namespace gui
    {
        class Slider : public Drawable
        {
        private:
            int Pos;
            int Steps;
            float scale;

            bool selected = false;

            sf::Sprite bar;
            sf::Sprite pointer;

            sf::Texture *standardT;
            sf::Texture *selectedT;

            virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
        public:
            Slider(textureManager & tm, sf::Vector2f position, float newSize, sf::Uint8 currentStep = 0);

            void update(Event event);
            int getCurrentStep();
        };
        Slider::Slider(textureManager & tm, sf::Vector2f position, float newSize, sf::Uint8 currentStep)
        {
            tm.add("assets/graphics/UI/mainMenu/slider/sliderBar.png");
            bar.setTexture(*tm.get("assets/graphics/UI/mainMenu/slider/sliderBar.png"));
            bar.setScale(sf::Vector2f(newSize, newSize));
            bar.setPosition(position);

            tm.add("assets/graphics/UI/mainMenu/slider/sliderPointer.png");
            tm.add("assets/graphics/UI/mainMenu/slider/sliderPointer_selected.png");
            pointer.setTexture(*tm.get("assets/graphics/UI/mainMenu/slider/sliderPointer.png"));
            pointer.setScale(sf::Vector2f(newSize, newSize));
            pointer.setOrigin(2, 0);
            pointer.setPosition(sf::Vector2f(bar.getPosition().x + 2 * bar.getScale().x, position.y + newSize * -1));
            pointer.move(((bar.getLocalBounds().width - 2) * bar.getScale().x) * currentStep / 100.f, 0);

            if(pointer.getPosition().x > bar.getPosition().x + (bar.getLocalBounds().width - 1) * bar.getScale().x)
                pointer.setPosition(bar.getPosition().x + (bar.getLocalBounds().width - 1) * bar.getScale().x, pointer.getPosition().y);
            else if(pointer.getPosition().x < bar.getPosition().x + 2 * bar.getScale().x)
                pointer.setPosition(bar.getPosition().x + 2 * bar.getScale().x, pointer.getPosition().y);

            selectedT = tm.get("assets/graphics/UI/mainMenu/slider/sliderPointer_selected.png");
            standardT = tm.get("assets/graphics/UI/mainMenu/slider/sliderPointer.png");

            scale = newSize;
        }

        void Slider::draw(sf::RenderTarget& target, sf::RenderStates states) const
        {
            target.draw(bar, states);
            target.draw(pointer, states);
        }

        int Slider::getCurrentStep()
        {
            return (pointer.getPosition().x - bar.getPosition().x - scale) / (bar.getLocalBounds().width - 2) * 100 / scale;
        }

        void Slider::update(Event event)
        {
            sf::Vector2f mouseCoords = sf::Vector2f(sf::Mouse::getPosition().x * viewScale + screenCornerX, sf::Mouse::getPosition().y * viewScale + screenCornerY);

            if(event.type == Event::MouseButtonPressed and bar.getGlobalBounds().contains(mouseCoords))
            {
                selected = !selected;

                if(selected)
                    pointer.setPosition(limit(mouseCoords.x, bar.getPosition().x + 2 * bar.getScale().x, bar.getPosition().x + (bar.getLocalBounds().width - 1) * bar.getScale().x), pointer.getPosition().y);
            }
            else if(event.type == Event::MouseButtonPressed and !bar.getGlobalBounds().contains(mouseCoords))
                selected = false;

            if(selected)
            {
                pointer.setTexture(*selectedT);
            }
            else
                pointer.setTexture(*standardT);

            if(event.type == Event::MouseMoved)
            {
                if(selected)
                    pointer.setPosition(limit(mouseCoords.x, bar.getPosition().x + 2 * bar.getScale().x, bar.getPosition().x + (bar.getLocalBounds().width - 1) * bar.getScale().x), pointer.getPosition().y);
            }
        }
    };
};

#endif // SLIDER_H_INCLUDED
