#include <SFML/Graphics.hpp>
#include "world.h"
#include "Gui.h"
int main()
{
    // Create the main window
    sf::RenderWindow App(sf::VideoMode(800, 600), "Crystal");
    sf::RenderWindow MapWin(sf::VideoMode(200,200),"Map");

    // Load a sprite to display
    sf::Image Image;
    if (!Image.Create(100,100,sf::Color(255,0,0,255)))
        return EXIT_FAILURE;
    for(size_t i=0;i<100;i++)
    for(size_t j=0;j<100;j++)
        Image.SetPixel(i,j,sf::Color(rand()%256,rand()%256,rand()%256));
    Image.SetSmooth(false);
    sf::Sprite Sprite(Image);
    App.ShowMouseCursor(false);
    Sprite.SetScale(8,8);
    Gui gui(sf::FloatRect(600,0,800,600));
    World world(sf::FloatRect(0,0,800,600));
	// Start the game loop
	sf::String str1;

    while (App.IsOpened()&& MapWin.IsOpened())
    {
        // Process events
        sf::Event Event;
        while (App.GetEvent(Event))
        {
            // Close window : exit
            if (Event.Type == sf::Event::Closed)
                App.Close();
            if (Event.Type == sf::Event::MouseButtonReleased)
            {
                if(gui.Inside(Event.MouseButton.X,Event.MouseButton.Y))
                    gui.OnEvent(Event);
                else
                {

                    //world.OnEvent(Event);
                    sf::Vector2f pos=App.ConvertCoords(Event.MouseButton.X,Event.MouseButton.Y,&world.camera);
                    world.Click(pos.x,pos.y);
                }
            }
            if (Event.Type == sf::Event::MouseMoved)
            {
                if(gui.Inside(Event.MouseMove.X,Event.MouseMove.Y))
                {
                    App.ShowMouseCursor(true);
                }
                else
                {
                     App.ShowMouseCursor(false);
                    //world.OnEvent(Event);
                    sf::Vector2f pos=App.ConvertCoords(Event.MouseMove.X,Event.MouseMove.Y,&world.camera);
                    world.MouseMove(pos.x,pos.y);
                }
            }
            /* does not work for some reason...
            if (Event.Type == sf::Event::Resized)
            {
                App.SetSize(800,Event.Size.Width-200);
            }
            //*/
        }
        while (MapWin.GetEvent(Event))
        {
            if (Event.Type == sf::Event::Closed)
                MapWin.Close();
        }
        float Offset = 200.f * App.GetFrameTime();
        if (App.GetInput().IsKeyDown(sf::Key::Up))    world.camera.Move( 0,      -Offset);
        if (App.GetInput().IsKeyDown(sf::Key::Down))  world.camera.Move( 0,       Offset);
        if (App.GetInput().IsKeyDown(sf::Key::Left))  world.camera.Move(-Offset,  0);
        if (App.GetInput().IsKeyDown(sf::Key::Right)) world.camera.Move( Offset,  0);
        // Clear screen
        App.Clear();

        // World, and then Gui
        world.Draw(App);
        gui.Draw(App);
        //App.Draw(Sprite);
        // Update the window
        App.Display();
        MapWin.Clear();
        //Map window drawing goes here
        MapWin.Display();
    }

    return EXIT_SUCCESS;
}
