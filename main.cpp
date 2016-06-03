#include <cassert>
#include <iostream>
#include <SFML/Graphics.hpp>
#include <vector>

enum class shapes {i_shape, j_shape, l_shape, o_shape, t_shape, s_shape, z_shape};

//                     _
//                    |_|       _      _
//                    |_|      |_|    |_|       _ _       _        _ _    _ _
//                    |_|     _|_|    |_|_     |_|_|    _|_|_    _|_|_|  |_|_|_
//                    |_|    |_|_|    |_|_|    |_|_|   |_|_|_|  |_|_|      |_|_|
//

void check_shape_collision(std::vector <std::vector<sf::Color>> &grid, shapes new_shape, int &x, int &y);
std::vector <sf::Vector2i> choose_new_shape(shapes new_shape, const int x, const int y);
void choose_random_shape(shapes &new_shape, const int y);
void do_left(std::vector <std::vector<sf::Color>> &grid, shapes &new_shape, int &x, const int y);
void do_right(std::vector <std::vector<sf::Color>> &grid, shapes &new_shape, int &x, const int y);
void do_up(std::vector <std::vector<sf::Color>> &grid, shapes &new_shape, const int x, int &y);
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
  shapes new_shape;

  while(window.isOpen())
  {
    sf::Event event;

    choose_random_shape(new_shape, y);
    std::vector <sf::Vector2i> new_shape_vector = choose_new_shape(new_shape, x, y);

    while(window.pollEvent(event))
    {
      switch(event.type)
      {
        case sf::Event::Closed:
          window.close();
          break;
        case sf::Event::KeyPressed:
          if(sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) //TODO
          {

          }
          if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
          {
            do_up(grid, new_shape, x, y);
          }
          if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
          {
            do_left(grid, new_shape, x, y);
          }
          if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
          {
            do_right(grid, new_shape, x, y);
          }
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
        check_shape_collision(grid, new_shape, x, y);
      }
    window.clear();
    draw_grid(window, grid, pixel_size);
    draw_shape(window, new_shape_vector, pixel_size);
    window.display();
  }
}

void check_shape_collision(std::vector <std::vector<sf::Color>> &grid, shapes new_shape, int &x, int &y)
{
  if(new_shape == shapes::i_shape)
  {
    if(y == 28 || grid[x][y] == sf::Color::Green)
    {
      grid[x][y - 4] = sf::Color::Green;
      grid[x][y - 3] = sf::Color::Green;
      grid[x][y - 2] = sf::Color::Green;
      grid[x][y - 1] = sf::Color::Green;

      std::cout << x << std::endl;
      std::cout << y << std::endl;
      y = -1;
      x = 9;
    }
  }
  if(new_shape == shapes::j_shape)
  {
    if(y == 28 || grid[x][y] == sf::Color::Green || grid[x + 1][y] == sf::Color::Green)
    {
      grid[x + 1][y - 3] = sf::Color::Green;
      grid[x + 1][y - 2] = sf::Color::Green;
      grid[x + 1][y - 1] = sf::Color::Green;
      grid[x][y - 1] = sf::Color::Green;

      std::cout << x << std::endl;
      std::cout << y << std::endl;
      y = -1;
      x = 9;
    }
  }
  if(new_shape == shapes::l_shape)
  {
    if(y == 28 || grid[x][y] == sf::Color::Green || grid[x - 1][y] == sf::Color::Green)
    {
      grid[x - 1][y - 3] = sf::Color::Green;
      grid[x - 1][y - 2] = sf::Color::Green;
      grid[x - 1][y - 1] = sf::Color::Green;
      grid[x][y - 1] = sf::Color::Green;

      std::cout << x << std::endl;
      std::cout << y << std::endl;
      y = -1;
      x = 9;
    }
  }
  if(new_shape == shapes::o_shape)
  {
    if(y == 28 || grid[x][y] == sf::Color::Green || grid[x][y - 1] == sf::Color::Green)
    {
      grid[x - 1][y - 2] = sf::Color::Green;
      grid[x - 1][y - 1] = sf::Color::Green;
      grid[x][y - 2] = sf::Color::Green;
      grid[x][y - 1] = sf::Color::Green;

      std::cout << x << std::endl;
      std::cout << y << std::endl;
      y = -1;
      x = 9;
    }
  }
  if(new_shape == shapes::t_shape)
  {
    if(y == 28 || grid[x][y] == sf::Color::Green || grid[x - 1][y] == sf::Color::Green || grid[x - 2][y] == sf::Color::Green)
    {
      grid[x - 1][y - 2] = sf::Color::Green;
      grid[x - 2][y - 1] = sf::Color::Green;
      grid[x - 1][y - 1] = sf::Color::Green;
      grid[x][y - 1] = sf::Color::Green;

      std::cout << x << std::endl;
      std::cout << y << std::endl;
      y = -1;
      x = 9;
    }
  }
  if(new_shape == shapes::s_shape)
  {
    if(y == 28 || grid[x - 1][y] == sf::Color::Green || grid[x][y] == sf::Color::Green || grid[x + 1][y - 1] == sf::Color::Green)
    {
      grid[x][y - 1] = sf::Color::Green;
      grid[x + 1][y - 2] = sf::Color::Green;
      grid[x - 1][y - 1] = sf::Color::Green;
      grid[x][y - 2] = sf::Color::Green;

      std::cout << x << std::endl;
      std::cout << y << std::endl;
      y = -1;
      x = 9;
    }
  }
  if(new_shape == shapes::z_shape)
  {
    std::vector <sf::Vector2i> z_shape =
    {                             //
      sf::Vector2i(x - 2, y - 1), // 1              _ _
      sf::Vector2i(x - 1, y - 1), // 2             |1|2|_
      sf::Vector2i(x - 1, y),     // 3               |3|4|
      sf::Vector2i(x, y)          // 4
    };                            //
    if(y == 28 || grid[x - 2][y - 1] == sf::Color::Green || grid[x - 1][y] == sf::Color::Green || grid[x][y] == sf::Color::Green)
    {
      grid[x][y - 1] = sf::Color::Green;
      grid[x + 1][y - 2] = sf::Color::Green;
      grid[x - 1][y - 1] = sf::Color::Green;
      grid[x][y - 2] = sf::Color::Green;

      std::cout << x << std::endl;
      std::cout << y << std::endl;
      y = -1;
      x = 9;
    }
  }
}

void do_right(std::vector <std::vector<sf::Color>> &grid, shapes &new_shape, int &x, const int y)
{
  if(new_shape == shapes::i_shape)
  {}
  if(new_shape == shapes::j_shape)
  {}
  if(new_shape == shapes::l_shape)
  {}
  if(new_shape == shapes::o_shape)
  {}
  if(new_shape == shapes::t_shape)
  {}
  if(new_shape == shapes::s_shape)
  {
    if(grid[x + 2][y - 1] != sf::Color::Green && grid[x + 1][y] != sf::Color::Green)
    {
      x += 1;
      std::cout << x << std::endl;
      assert(x <= 16);
    }
  }
  if(new_shape == shapes::z_shape)
  {}
}

void do_left(std::vector <std::vector<sf::Color>> &grid, shapes &new_shape, int &x, const int y)
{
  if(new_shape == shapes::i_shape)
  {}
  if(new_shape == shapes::j_shape)
  {}
  if(new_shape == shapes::l_shape)
  {}
  if(new_shape == shapes::o_shape)
  {}
  if(new_shape == shapes::t_shape)
  {}
  if(new_shape == shapes::s_shape)
  {
    if(grid[x - 2][y] != sf::Color::Green && grid[x - 1][y - 1] != sf::Color::Green)
    {
      x -= 1;
      std::cout << x << std::endl;
      assert(x >= 1);
    }
  }
  if(new_shape == shapes::z_shape)
  {}
}

void do_up(std::vector <std::vector<sf::Color>> &grid, shapes &new_shape, const int x, int &y)
{
  if(new_shape == shapes::i_shape)
  {}
  if(new_shape == shapes::j_shape)
  {}
  if(new_shape == shapes::l_shape)
  {}
  if(new_shape == shapes::o_shape)
  {}
  if(new_shape == shapes::t_shape)
  {}
  if(new_shape == shapes::s_shape)
  {
    do
    {
      y += 1;
      assert(y <= 28);
    }
    while(grid[x - 1][y] != sf::Color::Green && grid[x][y] != sf::Color::Green && grid[x + 1][y - 1] != sf::Color::Green && y != 27);
    std::cout << y << std::endl;
    if(y == 27 && grid[x + 1][y - 1] == sf::Color::Green)
    {
      y -= 1;
      assert(y <= 28);
    }
    else if(y == 28)
    {
      y += 1; //only if the block is going to end up on the floor
      assert(y <= 28);
    }
    else if(y < 27)
    {
      y -= 1; //only if the block is not going to end up on the floor
      assert(y <= 28);
    }
  }
  if(new_shape == shapes::z_shape)
  {}
}

void choose_random_shape(shapes &new_shape, const int y)
{
  if(y == -1)
  {
    new_shape = static_cast<shapes>(rand() % 6);
  }
}

std::vector <sf::Vector2i> choose_new_shape(shapes new_shape, const int x, const int y)
{
  if(new_shape == shapes::i_shape)
  {
    std::vector <sf::Vector2i> i_shape =
    {                              //                 _
      sf::Vector2i(x, y - 3),      // 1              |1|
      sf::Vector2i(x, y - 2),      // 2              |2|
      sf::Vector2i(x, y - 1),      // 3              |3|
      sf::Vector2i(x, y)           // 4              |4|
    };                             //
    return i_shape;
  }

/*  std::vector <sf::Vector2i> i_shape_turned =
  {                              //
    sf::Vector2i(x, y),          // 1
    sf::Vector2i(x + 1, y),      // 2            _ _ _ _
    sf::Vector2i(x + 2, y),      // 3           |1|2|3|4|
    sf::Vector2i(x + 3, y)       // 4
  };                             //
*/
  if(new_shape == shapes::j_shape)
  {
    std::vector <sf::Vector2i> j_shape =
    {                              //
      sf::Vector2i(x + 1, y - 2),  // 1               _
      sf::Vector2i(x + 1, y - 1),  // 2              |1|
      sf::Vector2i(x + 1, y),      // 3             _|2|
      sf::Vector2i(x, y)           // 4            |4|3|
    };                             //
    return j_shape;
  }

/*    std::vector <sf::Vector2i> j_shape_turned_once =
  {                              //
    sf::Vector2i(x + 1, y - 2),  // 1
    sf::Vector2i(x + 1, y - 1),  // 2
    sf::Vector2i(x + 1, y),      // 3
    sf::Vector2i(x, y)           // 4
  };                             //

  std::vector <sf::Vector2i> j_shape_turned_twice =
  {                              //
    sf::Vector2i(x + 1, y - 2),  // 1
    sf::Vector2i(x + 1, y - 1),  // 2
    sf::Vector2i(x + 1, y),      // 3
    sf::Vector2i(x, y)           // 4
  };                             //

  std::vector <sf::Vector2i> j_shape_turned_thrice =
  {                              //
    sf::Vector2i(x + 1, y - 2),  // 1
    sf::Vector2i(x + 1, y - 1),  // 2
    sf::Vector2i(x + 1, y),      // 3
    sf::Vector2i(x, y)           // 4
  };                             //
*/
  if(new_shape == shapes::l_shape)
  {
    std::vector <sf::Vector2i> l_shape =
    {                             //
      sf::Vector2i(x - 1, y - 2), // 1              _
      sf::Vector2i(x - 1, y - 1), // 2             |1|
      sf::Vector2i(x - 1, y),     // 3             |2|_
      sf::Vector2i(x, y)          // 4             |3|4|
    };                            //
    return l_shape;
  }

/*    std::vector <sf::Vector2i> l_shape_turned_once =
  {                             //
    sf::Vector2i(x - 1, y - 2), // 1
    sf::Vector2i(x - 1, y - 1), // 2
    sf::Vector2i(x - 1, y),     // 3
    sf::Vector2i(x, y)          // 4
  };                            //

  std::vector <sf::Vector2i> l_shape_turned_twice =
  {                             //
    sf::Vector2i(x - 1, y - 2), // 1
    sf::Vector2i(x - 1, y - 1), // 2
    sf::Vector2i(x - 1, y),     // 3
    sf::Vector2i(x, y)          // 4
  };                            //

  std::vector <sf::Vector2i> l_shape_turned_thrice =
  {                             //
    sf::Vector2i(x - 1, y - 2), // 1
    sf::Vector2i(x - 1, y - 1), // 2
    sf::Vector2i(x - 1, y),     // 3
    sf::Vector2i(x, y)          // 4
  };                            //
*/
  if(new_shape == shapes::o_shape)
  {
    std::vector <sf::Vector2i> o_shape =
    {                             //
      sf::Vector2i(x - 1, y - 1), // 1              _ _
      sf::Vector2i(x - 1, y),     // 2             |1|2|
      sf::Vector2i(x, y - 1),     // 3             |3|4|
      sf::Vector2i(x, y)          // 4
    };                            //
    return o_shape;
  }

  if(new_shape == shapes::t_shape)
  {
    std::vector <sf::Vector2i> t_shape =
    {                             //
      sf::Vector2i(x - 1, y - 1), // 1                _
      sf::Vector2i(x - 2, y),     // 2              _|1|_
      sf::Vector2i(x - 1, y),     // 3             |2|3|4|
      sf::Vector2i(x, y)          // 4
    };                            //
    return t_shape;
  }

/*  std::vector <sf::Vector2i> t_shape_turned_once =
  {                             //
    sf::Vector2i(x, y - 2),     // 1                _
    sf::Vector2i(x, y - 1),     // 2               |1|_
    sf::Vector2i(x + 1, y - 1), // 3               |2|3|
    sf::Vector2i(x, y)          // 4               |4|
  };                            //

  std::vector <sf::Vector2i> t_shape_turned_twice =
  {                             //
    sf::Vector2i(x - 1, y - 1), // 1              _ _ _
    sf::Vector2i(x, y - 1),     // 2             |1|2|3|
    sf::Vector2i(x + 1, y - 1), // 3               |4|
    sf::Vector2i(x, y)          // 4
  };                            //

  std::vector <sf::Vector2i> t_shape_turned_thrice =
  {                             //
    sf::Vector2i(x, y - 2),     // 1                _
    sf::Vector2i(x - 1, y - 1), // 2              _|1|
    sf::Vector2i(x, y - 1),     // 3             |2|3|
    sf::Vector2i(x, y)          // 4               |4|
  };                            //
*/
  if(new_shape == shapes::s_shape)
  {
    std::vector <sf::Vector2i> s_shape =
    {                             //
      sf::Vector2i(x, y - 1),     // 1                _ _
      sf::Vector2i(x + 1, y - 1), // 2              _|1|2|
      sf::Vector2i(x - 1, y),     // 3             |3|4|
      sf::Vector2i(x, y)          // 4
    };                            //
    return s_shape;
  }

/*  std::vector <sf::Vector2i> s_shape_turned =
  {                             //
    sf::Vector2i(x - 1, y - 2), // 1               _
    sf::Vector2i(x - 1, y - 1), // 2              |1|_
    sf::Vector2i(x, y - 1),     // 3              |2|3|
    sf::Vector2i(x, y)          // 4                |4|
  };                            //
*/
  if(new_shape == shapes::z_shape)
  {
    std::vector <sf::Vector2i> z_shape =
    {                             //
      sf::Vector2i(x - 2, y - 1), // 1              _ _
      sf::Vector2i(x - 1, y - 1), // 2             |1|2|_
      sf::Vector2i(x - 1, y),     // 3               |3|4|
      sf::Vector2i(x, y)          // 4
    };                            //
    return z_shape;
  }

/*    std::vector <sf::Vector2i> z_shape_turned =
  {                             //
    sf::Vector2i(x - 2, y - 1), // 1                 _
    sf::Vector2i(x - 1, y - 1), // 2               _|_|
    sf::Vector2i(x - 1, y),     // 3              |_|_|
    sf::Vector2i(x, y)          // 4              |_|
  };                            //
*/
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

