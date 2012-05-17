#include "Gui.h"

Gui::Gui(const sf::FloatRect& pos):pos(pos)
{
    box=sf::Shape::Rectangle(pos.Left,pos.Top,pos.Right,pos.Bottom,sf::Color(0,0,0,255),3,sf::Color(200,0,0,255));
    buttons.emplace_back(sf::FloatRect(pos.Left+10,pos.Top+10,pos.Right-10,pos.Top+50),"Step");
    //box.EnableFill(true);
    //box.SetColor(sf::Color(0,0,0,255));
}

Gui::~Gui()
{
    //dtor
}


void Gui::Draw(sf::RenderTarget& RenderTarget) const
{
    RenderTarget.Draw(box);
    for(const Button& b : buttons)
    {
        RenderTarget.Draw(b);
    }
}

void Gui::OnEvent(const sf::Event& ev)
{

}
