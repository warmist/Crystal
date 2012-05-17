#include "world.h"

World::World(const sf::FloatRect& pos):pos(pos),cameracenter(0,0)
{
    World_Block &wb=InitBlock(0,0);
    InitBlock(2,0);
    for(int i=0;i<BLOCK_SIZE;i++)
    for(int j=0;j<BLOCK_SIZE;j++)
        wb.get(i,j).type=rand()%Types::LAST_TYPE;
    wb.get(10,10).type=Types::MediumDensity;
    wb.UpdateImage();
    camera.SetHalfSize(pos.GetWidth()/2,pos.GetHeight()/2);
    cursor=sf::Shape::Rectangle(0,0,ZOOM-6,ZOOM-6,sf::Color(0,0,0,0),3,sf::Color(200,0,0));
    //camera.Zoom(ZOOM);

    //ctor
}

World::~World()
{
    for(std::pair<world_coord,World_Block*> it: data)
    {
        delete it.second;
    }
    //dtor
}

void World::Draw(sf::RenderTarget& RenderTarget) const
{
    sf::FloatRect screen=GetScreen();
    //const float zoom=ZOOM;
    /*World_Block twb(0,0);
    for(int i=0;i<BLOCK_SIZE;i++)
    for(int j=0;j<BLOCK_SIZE;j++)
        twb.get(i,j).type=rand()%Types::LAST_TYPE;
    twb.UpdateImage();
    RenderTarget.Draw(twb.GetSprite());*/


    RenderTarget.SetView(camera);

    for(const std::pair<world_coord,World_Block*>&it: data)
    {
        world_coord ps=it.first;

        sf::FloatRect blockrect(ps.first*BLOCK_SIZE*ZOOM,ps.second*BLOCK_SIZE*ZOOM,
                        (ps.first+1)*BLOCK_SIZE*ZOOM,(ps.second+1)*BLOCK_SIZE*ZOOM);
        //if(screen.Intersects(blockrect))
        if(camera.GetRect().Intersects(blockrect))
            {
                const World_Block &block=*it.second;
                RenderTarget.Draw(block.GetSprite());
            }
    }
    RenderTarget.Draw(cursor);
    RenderTarget.SetView(RenderTarget.GetDefaultView());
}
World_Block& World::InitBlock(int x,int y)
{

    world_coord coord(x,y);
    auto ret=data.insert(std::make_pair(coord,new World_Block(x,y)));
    //data[coord].SetPos(x,y);
    if(ret.second)
        return *ret.first->second;
    else
        throw std::runtime_error("Failed to allocate new map block");
}
void World::OnEvent(const sf::Event& ev)
{

}
sf::FloatRect World::GetScreen() const
{
     return sf::FloatRect(cameracenter.x-pos.GetWidth()/2,cameracenter.y-pos.GetHeight()/2,cameracenter.x+pos.GetWidth()/2,cameracenter.y+pos.GetHeight()/2);
}
void World::Click(float tx,float ty)
{
    sf::FloatRect frect=camera.GetRect();
    //cameracenter.x+=ev.MouseButton.X/ZOOM;
    int x=(tx-pos.Left)/ZOOM;
    int y=(ty-pos.Top)/ZOOM;
    world_coord coord(std::floor(x/(float)BLOCK_SIZE),std::floor(y/(float)BLOCK_SIZE));
    World_Block *wb;
    if(data.count(coord)==0)
        wb=&InitBlock(coord.first,coord.second);
    else
        wb=data[coord];
    World_Tile &t=(*wb)(x,y);
    //t.type=Types::LowDensity;
    t.flags.set(World_Tile::FLAG_DISCOVERED);
    wb->UpdateImage();
}
void World::MouseMove(float tx,float ty)
{
    cursor.SetPosition(std::floor(tx/ZOOM)*ZOOM+ZOOM/2+1,std::floor(ty/ZOOM)*ZOOM+ZOOM/2+1);
}
