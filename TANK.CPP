#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include<iostream>
#include<windows.h>
#include<vector>
#include <cmath>
#include<string>
#include <sstream>
#include <cmath>
using namespace std;
int screenx=1000;
int screeny=1000;
int gametime=0;
struct player
{
  double x;
  double y;
  double angle;
  int hp;
};
struct enemy
{
    double x;
    double y;
    int hp;
    double r;
};
player push(player b)
{
    b.x+=10*sin(b.angle/180*M_PI);
    b.y-=10*cos(b.angle/180*M_PI);
    return b;
}
player correctposition(player pl)
{
    if(pl.x>screenx)
        pl.x=screenx;
    if(pl.x<0)
        pl.x=0;
    if(pl.y>screeny)
        pl.y=screeny;
    if(pl.y<0)
        pl.y=0;
    return pl;
}
bool out(player pl)
{
    if(pl.x>screenx || pl.x<0 || pl.y>screeny || pl.y<0)
    return true;
    else return false;
}
void setenemy(enemy &e)
{
    e.x=500;
    e.y=500;
    e.r=25;
    e.hp=100;
}
void setplayer(player &p)
{
    p.x=50;
    p.y=50;
    p.angle=0;
    p.hp=100;
}
void moveenemy(enemy &e, player pl)
{
    if(e.x>pl.x)
        e.x-=1;
    else
        e.x+=1;
    if(e.y>pl.y)
        e.y-=1;
    else
        e.y+=1;
}

int main()
{

    sf::RenderWindow window( sf::VideoMode( screenx, screeny, 32 ), "Tank game" );
    sf::Texture gracz;
    sf::Texture bullet;
    sf::Texture background;
    sf::Texture robak;
    sf::Texture wygrana;
    sf::Texture porazka;
    sf::Text enemyhp;
    sf::Font font;
    enemyhp.setFont(font);
    enemyhp.setCharacterSize(48);
    enemyhp.setColor(sf::Color::White);
    font.loadFromFile("chintzys.ttf");
    gracz.loadFromFile( "mee.jpg" );
    bullet.loadFromFile( "bullet.png");
    background.loadFromFile( "background.jpg");
    robak.loadFromFile("bug.png");
    wygrana.loadFromFile("victory.png");
    porazka.loadFromFile("defeat.png");

    sf::Sprite p1;
    sf::Sprite bu;
    sf::Sprite bg;
    sf::Sprite en;
    sf::Sprite vi;
    sf::Sprite de;
    p1.setOrigin(25,25);
    player me;
    setplayer(me);

    enemy wrog;
    setenemy(wrog);

    vi.setTexture(wygrana);
    de.setTexture(porazka);
    bu.setTexture(bullet);
    p1.setTexture( gracz );
    bg.setTexture(background);
    en.setTexture(robak);
    en.setOrigin(25,25);
    vector<player> shot;
    player test;
    while( window.isOpen() )
    {
        gametime++;
        Sleep(10);
        sf::Event zdarzenie;
        while( window.pollEvent( zdarzenie ) )
        {
            if( zdarzenie.type == sf::Event::Closed )
                 window.close();
            if( sf::Keyboard::isKeyPressed( sf::Keyboard::D ))
                    me.x+=10;
            if( sf::Keyboard::isKeyPressed( sf::Keyboard::A))
                    me.x-=10;
            if( sf::Keyboard::isKeyPressed( sf::Keyboard::W))
                    me.y-=10;
            if( sf::Keyboard::isKeyPressed( sf::Keyboard::S))
                    me.y+=10;
            if( sf::Keyboard::isKeyPressed( sf::Keyboard::Q))
                    me.angle+=10;
            if( sf::Keyboard::isKeyPressed( sf::Keyboard::E))
                    me.angle-=10;
            if( sf::Keyboard::isKeyPressed( sf::Keyboard::P))
                    {
                        test.x=me.x;
                        test.y=me.y;
                        test.angle=me.angle-90;
                        shot.push_back(test);
                    }
        }
        p1.setRotation(me.angle);
        p1.setPosition(me.x, me.y);
        en.setPosition(wrog.x, wrog.y);
        moveenemy(wrog, me);
        stringstream ss;
        ss << wrog.hp;
        string str = ss.str();
        enemyhp.setString(str);
        enemyhp.setPosition(wrog.x,wrog.y+20);
        if(wrog.hp<=0)
        {
            window.clear();
            window.draw( vi );
            window.display();
            Sleep(5000);
            return 0;
        }
        if(sqrt((me.x-wrog.x)*(me.x-wrog.x)+(me.y-wrog.y)*(me.y-wrog.y))<30)
        {
            window.clear();
            window.draw( de );
            window.display();
            Sleep(5000);
        }
        me=correctposition(me);
        window.draw( bg );
        window.draw( en );
        window.draw( p1 );

        for(int i=0; i<shot.size(); i+=2)
        {
            shot[i]=push(shot[i]);
            if(((wrog.x-shot[i].x)*(wrog.x-shot[i].x)+(wrog.y-shot[i].y)*(wrog.y-shot[i].y))<wrog.r*wrog.r)
                wrog.hp--;
            bu.setPosition( shot[i].x, shot[i].y);
            bu.setRotation( shot[i].angle);
            window.draw( bu );
        }
        window.draw(enemyhp);
        window.display();
        if(shot.size()>100)
            shot.erase(shot.begin(), shot.begin()+80);
    }

    return 0;
}
