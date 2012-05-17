#include "world.h"

World::World(const sf::FloatRect& pos):pos(pos),camerastart(0,0)
{
    World_Block &wb=InitBlock(0,0);
    InitBlock(2,0);
    for(int i=0;i<BLOCK_SIZE;i++)
    for(int j=0;j<BLOCK_SIZE;j++)
    wb.get(i,j).type=rand()%Types::LAST_TYPE;
    wb.get(10,10).type=Types::MediumDensity;
    wb.UpdateImage();
    //ctor
}

World::~World()
{
    //dtor
}

void World::Draw(sf::RenderTarget& RenderTarget) const
{
    sf::FloatRect screen(camerastart.x,camerastart.y,camerastart.x+pos.GetWidth(),camerastart.y+pos.GetHeight());
    const float zoom=ZOOM;
    for(const std::pair<world_coord,World_Block>&it: data)
    {
        world_coord ps=it.first;
        sf::FloatRect blockrect(ps.first*BLOCK_SIZE*zoom,ps.second*BLOCK_SIZE*zoom,
                                (ps.first+1)*BLOCK_SIZE*zoom,(ps.second+1)*BLOCK_SIZE*zoom);
        if(screen.Intersects(blockrect))
            {
                RenderTarget.Draw(it.second.GetSprite());
            }
    }
}
World_Block& World::InitBlock(int x,int y)
{
    world_coord coord(x,y);
    data[coord].SetPos(x,y);
    return data[coord];
}
