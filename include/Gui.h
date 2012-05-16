#ifndef GUI_H
#define GUI_H
#include <SFML/Graphics.hpp>

class Gui
{
    public:
        Gui();
        virtual ~Gui();

        void Draw(const sf::RenderTarget& RenderTarget) const ;
    protected:
    private:
};

#endif // GUI_H
