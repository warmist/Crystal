#include <SFML/Graphics.hpp>
#include "world.h"
#include "Gui.h"
int main()
{
    // Create the main window
    sf::RenderWindow App(sf::VideoMode(800, 600), "Crystal");
    sf::RenderWindow App2(sf::VideoMode(200,200),"Map");
    // Load a sprite to display
    sf::Image Image;
    if (!Image.Create(100,100,sf::Color(255,0,0,255)))
        return EXIT_FAILURE;
    for(size_t i=0;i<100;i++)
    for(size_t j=0;j<100;j++)
        Image.SetPixel(i,j,sf::Color(rand()%256,rand()%256,rand()%256));
    Image.SetSmooth(false);
    sf::Sprite Sprite(Image);

    Sprite.SetScale(8,8);
    Gui gui(sf::FloatRect(600,0,800,600));
	// Start the game loop
    while (App.IsOpened()&& App2.IsOpened())
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
            }
            /* does not work for some reason...
            if (Event.Type == sf::Event::Resized)
            {
                App.SetSize(800,Event.Size.Width-200);
            }
            //*/
        }
        while (App2.GetEvent(Event))
        {
            if (Event.Type == sf::Event::Closed)
                App2.Close();
        }
        // Clear screen
        App.Clear();

        // Draw the sprite
        App.Draw(Sprite);
        gui.Draw(App);
        // Update the window
        App.Display();
        App2.Clear();
        App2.Display();
    }

    return EXIT_SUCCESS;
}
