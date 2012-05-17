#ifndef GUI_H
#define GUI_H
#include <SFML/Graphics.hpp>
#include "Button.h"
class Gui
{
    sf::FloatRect pos;
    sf::Shape box;
    std::vector<Button> buttons;
    public:
        Gui(const sf::FloatRect& pos);
        virtual ~Gui();

        void Draw(sf::RenderTarget& RenderTarget) const ;
        void OnEvent(const sf::Event& ev);
        inline bool Inside(float x,float y)
        {
            return pos.Contains(x,y);
        }
    protected:
    private:
};

#endif // GUI_H
