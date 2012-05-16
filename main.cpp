#include <SFML/Graphics.hpp>
#include "world.h"
int main()
{
    // Create the main window
    sf::RenderWindow App(sf::VideoMode(800, 600), "Crystal");

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

	// Start the game loop
    while (App.IsOpened())
    {
        // Process events
        sf::Event Event;
        while (App.GetEvent(Event))
        {
            // Close window : exit
            if (Event.Type == sf::Event::Closed)
                App.Close();
        }

        // Clear screen
        App.Clear();

        // Draw the sprite
        App.Draw(Sprite);

        // Update the window
        App.Display();
    }

    return EXIT_SUCCESS;
}
