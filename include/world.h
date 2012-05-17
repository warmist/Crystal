#ifndef WORLD_H
#define WORLD_H
#include <SFML/Graphics.hpp>
#include <bitset>
#include <stdexcept>
const int BLOCK_SIZE=16;
const float ZOOM=16;
namespace Types
{
    enum TypeNames
    {
        Empty,LowDensity,MediumDensity,Crystal_LQ,LAST_TYPE
    };
    const sf::Color colors[]={
        sf::Color{0x32,0x26,0},
        sf::Color{0x6d,0x52,0},
        sf::Color{0x5c,0x5c,0x5c},
        sf::Color{0x1E,0xDA,2}
    };
}
struct World_Tile
{
    enum Flags
    {
        FLAG_PROCESSED,FLAG_DISCOVERED,FLAG_LAST
    };
    char type;
    std::bitset<FLAG_LAST> flags;
    int order;
};
class World_Block
{
    int mx,my;
    sf::Image img;
    sf::Sprite sprite;
    public:
    World_Tile data[BLOCK_SIZE*BLOCK_SIZE];
    World_Block(int mx=0,int my=0)
    {
        SetPos(mx,my);
        img.Create(BLOCK_SIZE,BLOCK_SIZE,Types::colors[Types::Empty]);
        img.SetSmooth(false);
        for(int i=0;i<BLOCK_SIZE*BLOCK_SIZE;i++)
        {
            data[i].type=Types::Empty;
            data[i].flags.reset();
            data[i].order=0;
        }
        sprite.SetImage(img);
        sprite.SetScale(ZOOM,ZOOM);

    };
    void SetPos(int x,int y)
    {
        mx=x;
        my=y;
        sprite.SetPosition(mx*BLOCK_SIZE*ZOOM,my*BLOCK_SIZE*ZOOM);
    }
    inline World_Tile& get(int tx,int ty) //faster way to get tile, no error checks
    {
        return data[tx+ty*BLOCK_SIZE];
    }
    World_Tile& operator()(int tx,int ty)
    {
        int x,y;
        x=tx-mx*BLOCK_SIZE;
        y=ty-my*BLOCK_SIZE;
        if(x<0 || x>BLOCK_SIZE || y<0 || y>BLOCK_SIZE)
            throw std::runtime_error("Invalid coordinates");
        return data[x+y*BLOCK_SIZE];
    }
    void UpdateImage()
    {
        for(int i=0;i<BLOCK_SIZE;i++)
        for(int j=0;j<BLOCK_SIZE;j++)
        {
            int type=get(i,j).type;
            img.SetPixel(i,j,Types::colors[type]);
        }
    }
    const sf::Sprite& GetSprite() const
    {
        return sprite;
    }
};
class World
{
    typedef std::pair<int,int> world_coord;
    typedef std::map<world_coord,World_Block> world_blocks;
    world_blocks data;
    sf::FloatRect pos;
    sf::Vector2f camerastart;
    public:
        World(const sf::FloatRect& pos);
        virtual ~World();

        void Draw(sf::RenderTarget& RenderTarget) const ;
    protected:
        World_Block& InitBlock(int x,int y);
    private:
};

#endif // WORLD_H
