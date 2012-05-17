#ifndef BUTTON_H
#define BUTTON_H

#include <string>
#include <functional>

#include <SFML/Graphics.hpp>

//TODO move implementation to cpp file
class Button_Base:public sf::Shape
{
protected:
    sf::FloatRect pos;
    std::function<void(Button_Base&)> func;
public:
    Button_Base(const sf::FloatRect& pos,std::function<void(Button_Base&)>  func=std::function<void(Button_Base&)>()):
        pos(pos),
        Shape(sf::Shape::Rectangle(pos.Left,pos.Top,pos.Right,pos.Bottom,sf::Color(0,0,0,255),3,sf::Color(200,0,0,255)) ),
        func(func)
    {
    }

    virtual ~Button_Base(){};

    void Click()
    {
        if(func)
            func(*this);
    }
    inline bool Inside(float x,float y) const
    {
        return pos.Contains(x,y);
    }
protected:
    virtual void Render(sf::RenderTarget& Target) const
    {
        Shape::Render(Target);
    }
};
class Button:public Button_Base
{
    sf::String str;
public:
    Button(const sf::FloatRect& pos,const std::string& caption,std::function<void(Button_Base&)>  func=std::function<void(Button_Base&)>()):
        str(caption),Button_Base(pos,func)
    {
        //str.SetPosition(pos);
        float w=str.GetRect().GetWidth();
        float allw=pos.GetWidth();

        str.SetPosition(pos.Left+(allw-w)/2,pos.Top); //set centered
        str.SetColor(sf::Color(255,255,255,255));
    }
    virtual void Render(sf::RenderTarget& Target) const
    {
        Button_Base::Render(Target);
        Target.Draw(str);
    }
};
class ImageButtonButton:public Button_Base
{
    sf::Sprite sprite;
public:
    ImageButtonButton(const sf::FloatRect& pos,const sf::Sprite& img,std::function<void(Button_Base&)>  func=std::function<void(Button_Base&)>()):
        Button_Base(pos,func),sprite(img)
    {
        float w=sprite.GetSize().x;
        float allw=pos.GetWidth();
        float h=sprite.GetSize().y;
        float allh=pos.GetHeight();
        sprite.SetPosition(pos.Left+(allw-w)/2,pos.Top+(allh-h)/2);

    }
    virtual void Render(sf::RenderTarget& Target) const
    {
        Button_Base::Render(Target);
        Target.Draw(sprite);
    }
};
#endif // BUTTON_H
