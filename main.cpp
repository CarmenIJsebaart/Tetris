#include <cassert>
#include <iostream>
#include <SFML/Graphics.hpp>
#include <vector>

enum class direction {down, left, right, up};

void draw_grid(sf::RenderWindow &window, const std::vector<std::vector<sf::Color>> &grid, const int pixel_size);
void draw_shape(sf::RenderWindow &window, std::vector<sf::Vector2i> &shape, const int pixel_size);

int main()
{
  const int window_height = 560; //28 squares high
  const int window_width = 360;  //18 squares wide
  const int pixel_size = 20;
  assert(window_height % pixel_size == 0);
  assert(window_width % pixel_size == 0);
  sf::RenderWindow window(sf::VideoMode(window_width, window_height), "Tetris", sf::Style::Titlebar | sf::Style::Close);

  int x = 9;
  int y = -1;

  std::vector <std::vector<sf::Color>> grid(18, std::vector<sf::Color>(28, sf::Color(100, 100, 100)));
  sf::Clock clock;

  while(window.isOpen())
  {
    sf::Event event;

    std::vector <sf::Vector2i> i_shape =
    {                              //                 _
      sf::Vector2i(x, y - 3),      // 1              |1|
      sf::Vector2i(x, y - 2),      // 2              |2|
      sf::Vector2i(x, y - 1),      // 3              |3|
      sf::Vector2i(x, y)           // 4              |4|
    };                             //

    std::vector <sf::Vector2i> j_shape =
    {                              //
      sf::Vector2i(x + 1, y - 2),  // 1               _
      sf::Vector2i(x + 1, y - 1),  // 2              |1|
      sf::Vector2i(x + 1, y),      // 3             _|2|
      sf::Vector2i(x, y)           // 4            |4|3|
    };                             //

    std::vector <sf::Vector2i> l_shape =
    {                             //
      sf::Vector2i(x - 1, y - 2), // 1              _
      sf::Vector2i(x - 1, y - 1), // 2             |1|
      sf::Vector2i(x - 1, y),     // 3             |2|_
      sf::Vector2i(x, y)          // 4             |3|4|
    };                            //

    std::vector <sf::Vector2i> o_shape =
    {                             //
      sf::Vector2i(x - 1, y - 1), // 1              _ _
      sf::Vector2i(x - 1, y),     // 2             |1|2|
      sf::Vector2i(x, y - 1),     // 3             |3|4|
      sf::Vector2i(x, y)          // 4
    };                            //

    std::vector <sf::Vector2i> z_shape =
    {                             //
      sf::Vector2i(x - 2, y - 1), // 1              _ _
      sf::Vector2i(x - 1, y - 1), // 2             |1|2|_
      sf::Vector2i(x - 1, y),     // 3               |3|4|
      sf::Vector2i(x, y)          // 4
    };                            //

    std::vector <sf::Vector2i> t_shape =
    {                             //
      sf::Vector2i(x - 1, y - 1), // 1                _
      sf::Vector2i(x - 2, y),     // 2              _|1|_
      sf::Vector2i(x - 1, y),     // 3             |2|3|4|
      sf::Vector2i(x, y)          // 4
    };                            //

    std::vector <sf::Vector2i> s_shape =
    {                             //
      sf::Vector2i(x, y - 1),     // 1                _ _
      sf::Vector2i(x + 1, y - 1), // 2              _|1|2|
      sf::Vector2i(x - 1, y),     // 3             |3|4|
      sf::Vector2i(x, y)          // 4
    };                            //

    while(window.pollEvent(event))
    {
      switch(event.type)
      {
        case sf::Event::Closed:
          window.close();
          break;
        default:
          break;
      }
    }

    const double update_time = 125; //milliseconds

    if(clock.getElapsedTime().asMilliseconds() >= update_time)
    {
      y += 1;
      clock.restart();
      if(grid[x - 1][y] == sf::Color::Green || grid[x][y] == sf::Color::Green || grid[x + 1][y - 1] == sf::Color::Green)
      {
        //for s_shape
        grid[x][y - 1] = sf::Color::Green;
        grid[x + 1][y - 2] = sf::Color::Green;
        grid[x - 1][y - 1] = sf::Color::Green;
        grid[x][y - 2] = sf::Color::Green;

        std::cout << x << std::endl;
        std::cout << y << std::endl;
        y = -1;
        x += 2;
      }
      else if(y == 28)
      {
        //for s_shape
        grid[x][y - 1] = sf::Color::Green;
        grid[x + 1][y - 2] = sf::Color::Green;
        grid[x - 1][y - 1] = sf::Color::Green;
        grid[x][y - 2] = sf::Color::Green;

        std::cout << x << std::endl;
        std::cout << y << std::endl;
        y = -1;
      }
    }
    window.clear();
    draw_grid(window, grid, pixel_size);
    draw_shape(window, s_shape, pixel_size);
    window.display();
  }
}

void draw_shape(sf::RenderWindow &window, std::vector<sf::Vector2i> &shape, const int pixel_size)
{
  for(int i = 0; i != static_cast<int>(shape.size()); ++i)
  {
    const auto coordinat = shape[i];

    sf::RectangleShape s;
    s.setFillColor(sf::Color::Cyan);
    s.setPosition(coordinat.x * pixel_size, coordinat.y * pixel_size);
    s.setSize(sf::Vector2f(pixel_size, pixel_size));
    s.setOutlineThickness(-1);
    s.setOutlineColor(sf::Color::Black);
    window.draw(s);
  }
}

void draw_grid(sf::RenderWindow &window, const std::vector<std::vector<sf::Color>> &grid, const int pixel_size)
{
  const int n_cols{static_cast<int>(grid.size())};
  const int n_rows{static_cast<int>(grid[0].size())};
  for (int x = 0; x != n_cols; ++x)
  {
    for (int y = 0; y != n_rows; ++y)
    {
      const sf::Color c = grid[x][y];
      sf::RectangleShape s;
      s.setFillColor(c);
      s.setPosition(x * pixel_size, y * pixel_size);
      s.setSize(sf::Vector2f(pixel_size, pixel_size));
      s.setOutlineThickness(-1);
      s.setOutlineColor(sf::Color::Black);
      window.draw(s);
    }
  }
}

