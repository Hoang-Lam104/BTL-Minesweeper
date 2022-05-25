#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Color.hpp>
#include <algorithm>
#include <cmath>
#include <iostream>
#include <string>

const int map_size_x = 30;
const int map_size_y = 16;
const int window_size_x = 890;
const int window_size_y = 430;
const int mines = 99;

const int square_size = (int)(std::min(window_size_x / map_size_x, window_size_y / map_size_y));

int map[map_size_y][map_size_x];
int map_view[map_size_y][map_size_x];
sf::RenderWindow app(sf::VideoMode(map_size_x *square_size, map_size_y *square_size), "Minesweeper!", sf::Style::Close);

sf::Texture mine;
sf::Texture flag;
sf::Font font;

int ways[][2] = {{-1, -1},
                 {-1, 0},
                 {-1, 1},
                 {0, -1},
                 {0, 1},
                 {1, -1},
                 {1, 0},
                 {1, 1}};

void game_over(std::string t)
{
    sf::Text text;
    text.setFont(font);
    text.setString(t);
    text.setFillColor(sf::Color::Red);
    text.setCharacterSize(std::min(map_size_x * square_size, map_size_y * square_size) / 4);
    // text.setPosition(sf::Vector2f(map_size_x*square_size, map_size_y*square_size));
    app.draw(text);
    app.display();
    sf::Event e;
    while (1)
    {
        while (app.pollEvent(e))
        {
            if (e.type == sf::Event::Closed)
            {
                return;
            }
        }
    }
}

void check_win()
{
    for (int y = 0; y < map_size_y; y++)
    {
        for (int x = 0; x < map_size_x; x++)
        {
            if (!(map[y][x] == map_view[y][x] || (map[y][x] == -1 && map_view[y][x] == 9) || (map[y][x] == 0 && map_view[y][x] == 10)))
            {
                return;
            }
        }
    }
    std::string t = "You won!";
    game_over(t);
    return;
}

void open_all_zero_around(int x, int y)
{
    for (auto i : ways)
    {

        if (x - i[0] >= 0 && x - i[0] < map_size_x && y - i[1] >= 0 && y - i[1] < map_size_y && (map_view[y - i[1]][x - i[0]] == 10))
        {
            map_view[y - i[1]][x - i[0]] = map[y - i[1]][x - i[0]];
            if (map[y - i[1]][x - i[0]] == 0)
            {
                open_all_zero_around(x - i[0], y - i[1]);
            }
        }
    }
}

void set_numbers()
{
    for (int y = 0; y < map_size_y; y++)
    {
        for (int x = 0; x < map_size_x; x++)
        {
            if (map[y][x] != -1)
            {
                int n = 0;
                for (auto i : ways)
                {
                    if (x - i[0] >= 0 && x - i[0] < map_size_x && y - i[1] >= 0 && y - i[1] < map_size_y && map[y - i[1]][x - i[0]] == -1)
                    {
                        n++;
                    }
                }
                map[y][x] = n;
            }
        }
    }
}

void generate_map()
{
    for (int y = 0; y < map_size_y; y++)
    {
        for (int x = 0; x < map_size_x; x++)
        {
            map_view[y][x] = 10;
            if (rand() % 5 == 0 && mines > 0)
            {
                map[y][x] = -1; // mine
            }
            else
            {
                map[y][x] = 0;
            }
        }
    }
    set_numbers();
}

void loop()
{
    sf::Event e;
    while (app.isOpen())
    {
        while (app.pollEvent(e))
        {
            if (e.type == sf::Event::Closed)
            {
                app.close();
            }

            if (e.type == sf::Event::MouseButtonPressed)
            {

                int x = (int)(e.mouseButton.x / square_size);
                int y = (int)(e.mouseButton.y / square_size);

                if (x < map_size_x && x >= 0 && y < map_size_y && y >= 0)
                {
                    if (e.mouseButton.button == sf::Mouse::Right)
                    {
                        if (map_view[y][x] != 9 && map_view[y][x] == 10) // 9 - flag
                        {
                            map_view[y][x] = 9;
                        }
                        else if (map_view[y][x] == 9)
                        {
                            map_view[y][x] = 10;
                        }
                    }

                    if (e.mouseButton.button == sf::Mouse::Left)
                    {
                        map_view[y][x] = map[y][x];
                        if (map[y][x] == 0)
                        {
                            open_all_zero_around(x, y);
                        }
                        if (map[y][x] == -1)
                        {
                            std::string t = "Game over!";
                            game_over(t);
                            // return;
                        }
                        check_win();
                    }
                }
            }
        }

        //map
        app.clear(sf::Color::Black);
        for (int y = 0; y < map_size_y; y++)
        {
            for (int x = 0; x < map_size_x; x++)
            {
                sf::RectangleShape rectangle(sf::Vector2f(x * square_size, y * square_size));
                rectangle.setSize(sf::Vector2f(square_size, square_size));
                rectangle.setPosition(sf::Vector2f(x * square_size, y * square_size));
                rectangle.setFillColor(sf::Color::White);
                rectangle.setOutlineColor(sf::Color::Black);
                rectangle.setOutlineThickness(1);
                app.draw(rectangle);

                if (map_view[y][x] == -1)
                { // mines
                    sf::Sprite sprite;
                    sprite.setTexture(mine);
                    sprite.scale(sf::Vector2f((float)square_size / (float)mine.getSize().x, (float)square_size / (float)mine.getSize().y));
                    sprite.setPosition(sf::Vector2f(x * square_size, y * square_size));
                    app.draw(sprite);
                }
                else if (map_view[y][x] == 9)
                {//flags
                    sf::Sprite sprite;
                    sprite.setTexture(flag);
                    sprite.scale(sf::Vector2f((float)square_size / (float)flag.getSize().x, (float)square_size / (float)flag.getSize().y));
                    sprite.setPosition(sf::Vector2f(x * square_size, y * square_size));
                    app.draw(sprite);
                }

                else if (map_view[y][x] != 10)
                {//number
                    sf::Color colors[] = {
                        sf::Color::Blue,
                        sf::Color::Green,
                        sf::Color::Red,
                        sf::Color::Magenta,
                        sf::Color::Cyan,
                        sf::Color::Blue,
                        sf::Color::Green,
                        sf::Color::Red,
                    };

                    sf::Text text;
                    text.setFont(font);
                    text.setString(std::to_string(map[y][x]));
                    text.setCharacterSize(square_size);
                    text.setFillColor(colors[map[y][x] - 1]);
                    text.setPosition(sf::Vector2f(x * square_size + square_size / 4, y * square_size - square_size / 6));
                    app.draw(text);
                }
            }
        }
        app.display();
    }
}

int main()
{
    //nhận asset

    flag.loadFromFile("asset/flag.png");
    mine.loadFromFile("asset/mine.png");
    font.loadFromFile("asset/arial.ttf");

    generate_map();
    loop();
}