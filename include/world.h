#ifndef WORLD_H
#define WORLD_H
#include <SFML/Graphics.hpp>

const int BLOCK_SIZE=256;

class World
{
    public:
        World();
        virtual ~World();

        void Draw(const sf::RenderTarget& RenderTarget) const ;
    protected:
    private:
};

#endif // WORLD_H
