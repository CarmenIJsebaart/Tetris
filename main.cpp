#include <cassert>
#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <vector>

enum class shapes {i_shape, j_shape, l_shape, o_shape, t_shape, s_shape, z_shape,
/////////////////////////////////////////////////////////////////////////////////////////////////////
//                     _                                                                           //
//                    |_|       _      _                                                           //
//                    |_|      |_|    |_|       _ _       _        _ _    _ _                      //
//                    |_|     _|_|    |_|_     |_|_|    _|_|_    _|_|_|  |_|_|_                    //
//                    |_|    |_|_|    |_|_|    |_|_|   |_|_|_|  |_|_|      |_|_|                   //
//                                                                                                 //
/////////////////////////////////////////////////////////////////////////////////////////////////////
                    i_shape_turned, j_shape_turned_once, j_shape_turned_twice, j_shape_turned_thrice,
                    l_shape_turned_once, l_shape_turned_twice, l_shape_turned_thrice, t_shape_turned_once,
                    t_shape_turned_twice, t_shape_turned_thrice, s_shape_turned, z_shape_turned};

void check_shape_collision(std::vector <std::vector<sf::Color>> &grid, shapes new_shape, int &x, int &y, const int vertical_squares);
std::vector <sf::Vector2i> choose_new_shape(shapes new_shape, const int x, const int y);
void choose_random_shape(shapes &new_shape, const int y);
void do_down(shapes &new_shape, const int x, const int horizontal_squares);
void do_left(std::vector <std::vector<sf::Color>> &grid, shapes &new_shape, int &x, const int y);
void do_right(std::vector <std::vector<sf::Color>> &grid, shapes &new_shape, int &x, const int y, const int horizontal_squares);
void do_up(std::vector <std::vector<sf::Color>> &grid, shapes &new_shape, const int x, int &y, const int vertical_squares);
void draw_grid(sf::RenderWindow &window, const std::vector<std::vector<sf::Color>> &grid, const int pixel_size);
void draw_shape(sf::RenderWindow &window, std::vector<sf::Vector2i> &shape, const int pixel_size);


int main()
{
  const int horiontal_squares = 10;
  const int vertical_squares = 20;
  const int pixel_size = 30;
  const int window_height = vertical_squares * pixel_size;
  const int window_width = horiontal_squares * pixel_size;
  sf::RenderWindow window(sf::VideoMode(window_width, window_height), "Tetris", sf::Style::Titlebar | sf::Style::Close);

  int x = horiontal_squares / 2;
  int y = -1;

  std::vector <std::vector<sf::Color>> grid(horiontal_squares, std::vector<sf::Color>(vertical_squares, sf::Color(100, 100, 100)));
  sf::Clock clock;
  shapes new_shape;

  //background music
  sf::Music background_music;
  if(!background_music.openFromFile("Background.wav"))
  {
    std::cout << "Error loading sound (Background)" << std::endl;
  }
  background_music.setLoop(true);
  background_music.play();

  //shape falls to ground sound
  sf::SoundBuffer shape_soundbuffer;
  if(!shape_soundbuffer.loadFromFile("ShapeFalls.wav")) {std::cout << "Error loading sound (ShapeFalls)" << std::endl; }

  sf::Sound shape_sound;
  shape_sound.setBuffer(shape_soundbuffer);
  shape_sound.setVolume(50);

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
          if(sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
          {
            do_down(new_shape, x, horiontal_squares);
          }
          if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
          {
            do_up(grid, new_shape, x, y, vertical_squares);
            shape_sound.play();
          }
          if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
          {
            do_left(grid, new_shape, x, y);
          }
          if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
          {
            do_right(grid, new_shape, x, y, horiontal_squares);
          }
          break;
        default:
          break;
      }
    }

    const double update_time = 150; //milliseconds

    if(clock.getElapsedTime().asMilliseconds() >= update_time)
    {
      y += 1;
      clock.restart();
      check_shape_collision(grid, new_shape, x, y, vertical_squares);
    }

    window.clear();
    draw_grid(window, grid, pixel_size);
    draw_shape(window, new_shape_vector, pixel_size);
    window.display();
  }
}
void check_shape_collision(std::vector <std::vector<sf::Color>> &grid, shapes new_shape, int &x, int &y, const int vertical_squares)
{
  if(new_shape == shapes::i_shape)
  {
    if(y == vertical_squares - 1 || grid[x][y + 1] == sf::Color::Green)
    {
      grid[x][y - 3] = sf::Color::Green;
      grid[x][y - 2] = sf::Color::Green;
      grid[x][y - 1] = sf::Color::Green;
      grid[x][y] = sf::Color::Green;

      y = -1;
      x = 5;
    }
  }
  if(new_shape == shapes::i_shape_turned)
  {
    if(y == vertical_squares || grid[x - 2][y] == sf::Color::Green || grid[x - 1][y] == sf::Color::Green ||
       grid[x][y] == sf::Color::Green || grid[x + 1][y] == sf::Color::Green)
    {
      grid[x - 2][y - 1] = sf::Color::Green;
      grid[x - 1][y - 1] = sf::Color::Green;
      grid[x][y - 1] = sf::Color::Green;
      grid[x + 1][y - 1] = sf::Color::Green;

      y = -1;
      x = 5;
    }
  }
  if(new_shape == shapes::j_shape)
  {
    if(y == vertical_squares || grid[x][y] == sf::Color::Green || grid[x - 1][y] == sf::Color::Green)
    {
      grid[x][y - 3] = sf::Color::Green;
      grid[x][y - 2] = sf::Color::Green;
      grid[x][y - 1] = sf::Color::Green;
      grid[x - 1][y - 1] = sf::Color::Green;

      y = -1;
      x = 5;
    }
  }
  if(new_shape == shapes::j_shape_turned_once)
  {
    if(y == vertical_squares || grid [x][y] == sf::Color::Green || grid[x + 1][y] == sf::Color::Green || grid[x + 2][y] == sf::Color::Green)
    {
      grid[x][y - 2] = sf::Color::Green;
      grid[x][y - 1] = sf::Color::Green;
      grid[x + 1][y - 1] = sf::Color::Green;
      grid[x + 2][y - 1] = sf::Color::Green;

      y = -1;
      x = 5;
    }
  }
  if(new_shape == shapes::j_shape_turned_twice)
  {
    if(y == vertical_squares - 2 || grid[x + 1][y] == sf::Color::Green || grid[x][y + 2] == sf::Color::Green)
    {
      grid[x][y - 1] = sf::Color::Green;
      grid[x + 1][y - 1] = sf::Color::Green;
      grid[x][y] = sf::Color::Green;
      grid[x][y + 1] = sf::Color::Green;

      y = -1;
      x = 5;
    }
  }
  if(new_shape == shapes::j_shape_turned_thrice)
  {
    if(y == vertical_squares - 1 || grid[x - 2][y] == sf::Color::Green || grid[x - 1][y] == sf::Color::Green || grid[x][y + 1] == sf::Color::Green)
    {
      grid[x - 2][y - 1] = sf::Color::Green;
      grid[x - 1][y - 1] = sf::Color::Green;
      grid[x][y - 1] = sf::Color::Green;
      grid[x][y] = sf::Color::Green;

      y = -1;
      x = 5;
    }
  }
  if(new_shape == shapes::l_shape)
  {
    if(y == vertical_squares || grid[x][y] == sf::Color::Green || grid[x + 1][y] == sf::Color::Green)
    {
      grid[x][y - 3] = sf::Color::Green;
      grid[x][y - 2] = sf::Color::Green;
      grid[x][y - 1] = sf::Color::Green;
      grid[x + 1][y - 1] = sf::Color::Green;

      y = -1;
      x = 5;
    }
  }
  if(new_shape == shapes::l_shape_turned_once)
  {
    if(y == vertical_squares - 1 || grid[x + 1][y] == sf::Color::Green || grid[x + 2][y] == sf::Color::Green || grid[x][y + 1] == sf::Color::Green)
    {
      grid[x][y - 1] = sf::Color::Green;
      grid[x + 1][y - 1] = sf::Color::Green;
      grid[x + 2][y - 1] = sf::Color::Green;
      grid[x][y] = sf::Color::Green;

      y = -1;
      x = 5;
    }
  }
  if(new_shape == shapes::l_shape_turned_twice)
  {
    if(y == vertical_squares - 2 || grid[x - 1][y] == sf::Color::Green || grid[x][y - 2] == sf::Color::Green)
    {
      grid[x - 1][y - 1] = sf::Color::Green;
      grid[x][y - 1] = sf::Color::Green;
      grid[x][y] = sf::Color::Green;
      grid[x][y + 1] = sf::Color::Green;

      y = -1;
      x = 5;
    }
  }
  if(new_shape == shapes::l_shape_turned_thrice)
  {
    if(y == vertical_squares || grid[x - 2][y] == sf::Color::Green || grid[x - 1][y] == sf::Color::Green || grid[x][y] == sf::Color::Green)
    {
      grid[x - 2][y - 1] = sf::Color::Green;
      grid[x - 1][y - 1] = sf::Color::Green;
      grid[x][y - 1] = sf::Color::Green;
      grid[x][y - 2] = sf::Color::Green;

      y = -1;
      x = 5;
    }
  }
  if(new_shape == shapes::o_shape)
  {
    if(y == vertical_squares || grid[x - 1][y] == sf::Color::Green || grid[x][y] == sf::Color::Green)
    {
      grid[x - 1][y - 2] = sf::Color::Green;
      grid[x][y - 2] = sf::Color::Green;
      grid[x - 1][y - 1] = sf::Color::Green;
      grid[x][y - 1] = sf::Color::Green;

      y = -1;
      x = 5;
    }
  }
  if(new_shape == shapes::t_shape)
  {
    if(y == vertical_squares || grid[x - 1][y] == sf::Color::Green || grid[x][y] == sf::Color::Green || grid[x + 1][y] == sf::Color::Green)
    {
      grid[x][y - 2] = sf::Color::Green;
      grid[x - 1][y - 1] = sf::Color::Green;
      grid[x][y - 1] = sf::Color::Green;
      grid[x + 1][y - 1] = sf::Color::Green;

      y = -1;
      x = 5;
    }
  }
  if(new_shape == shapes::t_shape_turned_once)
  {
    if(y == vertical_squares - 1 || grid[x + 1][y] == sf::Color::Green || grid[x][y + 1] == sf::Color::Green)
    {
      grid[x][y - 2] = sf::Color::Green;
      grid[x][y - 1] = sf::Color::Green;
      grid[x + 1][y - 1] = sf::Color::Green;
      grid[x][y] = sf::Color::Green;

      y = -1;
      x = 5;
    }
  }
  if(new_shape == shapes::t_shape_turned_twice)
  {
    if(y == vertical_squares - 1 || grid[x - 1][y] == sf::Color::Green || grid[x + 1][y] == sf::Color::Green || grid[x][y + 1] == sf::Color::Green)
    {
      grid[x - 1][y - 1] = sf::Color::Green;
      grid[x][y - 1] = sf::Color::Green;
      grid[x + 1][y - 1] = sf::Color::Green;
      grid[x][y] = sf::Color::Green;

      y = -1;
      x = 5;
    }
  }
  if(new_shape == shapes::t_shape_turned_thrice)
  {
    if(y == vertical_squares - 1 || grid[x - 1][y] == sf::Color::Green || grid[x][y - 1] == sf::Color::Green)
    {
      grid[x][y] = sf::Color::Green;
      grid[x - 1][y - 1] = sf::Color::Green;
      grid[x][y - 1] = sf::Color::Green;
      grid[x][y - 2] = sf::Color::Green;

      y = -1;
      x = 5;
    }
  }
  if(new_shape == shapes::s_shape)
  {
    if(y == vertical_squares || grid[x + 1][y - 1] == sf::Color::Green || grid[x - 1][y] == sf::Color::Green || grid[x][y] == sf::Color::Green)
    {
      grid[x][y - 2] = sf::Color::Green;
      grid[x + 1][y - 2] = sf::Color::Green;
      grid[x - 1][y - 1] = sf::Color::Green;
      grid[x][y - 1] = sf::Color::Green;

      y = -1;
      x = 5;
    }
  }
  if(new_shape == shapes::s_shape_turned)
  {
    if(y == vertical_squares - 1 || grid[x - 1][y] == sf::Color::Green || grid[x][y + 1] == sf::Color::Green)
    {
      grid[x - 1][y - 2] = sf::Color::Green;
      grid[x - 1][y - 1] = sf::Color::Green;
      grid[x][y - 1] = sf::Color::Green;
      grid[x][y] = sf::Color::Green;

      y = -1;
      x = 5;
    }
  }
  if(new_shape == shapes::z_shape)
  {
    if(y == vertical_squares || grid[x - 1][y - 1] == sf::Color::Green || grid[x][y] == sf::Color::Green || grid[x + 1][y] == sf::Color::Green)
    {
      grid[x - 1][y - 2] = sf::Color::Green;
      grid[x][y - 2] = sf::Color::Green;
      grid[x][y - 1] = sf::Color::Green;
      grid[x + 1][y - 1] = sf::Color::Green;

      y = -1;
      x = 5;
    }
  }
  if(new_shape == shapes::z_shape_turned)
  {
    if(y == vertical_squares - 1 || grid[x + 1][y] == sf::Color::Green || grid[x][y + 1] == sf::Color::Green)
    {
      grid[x + 1][y - 2] = sf::Color::Green;
      grid[x + 1][y - 1] = sf::Color::Green;
      grid[x][y - 1] = sf::Color::Green;
      grid[x][y] = sf::Color::Green;

      y = -1;
      x = 5;
    }
  }
}
void do_down(shapes &new_shape, const int x, const int horizontal_squares)
{
  switch(new_shape)
  {
    case shapes::i_shape:
      if(x <= horizontal_squares - 4)
      {
        new_shape = shapes::i_shape_turned;
      }
      break;
    case shapes::i_shape_turned:
      new_shape = shapes::i_shape;
      break;
    case shapes::j_shape:
      if(x >= 2)
      {
        new_shape = shapes::j_shape_turned_once;
      }
      break;
    case shapes::j_shape_turned_once:
      if(x <= horizontal_squares - 2)
      {
        new_shape = shapes::j_shape_turned_twice;
      }
      break;
    case shapes::j_shape_turned_twice:
      if(x >= 2)
      {
        new_shape = shapes::j_shape_turned_thrice;
      }
      break;
    case shapes::j_shape_turned_thrice:
      if(x <= horizontal_squares - 2)
      {
        new_shape = shapes::j_shape;
      }
      break;
    case shapes::l_shape:
      if(x <= horizontal_squares - 3)
      {
        new_shape = shapes::l_shape_turned_once;
      }
      break;
    case shapes::l_shape_turned_once:
      if(x >= 1)
      {
        new_shape = shapes::l_shape_turned_twice;
      }
      break;
    case shapes::l_shape_turned_twice:
      if(x <= horizontal_squares - 3)
      {
        new_shape = shapes::l_shape_turned_thrice;
      }
      break;
    case shapes::l_shape_turned_thrice:
      if(x >= 1)
      {
        new_shape = shapes::l_shape;
      }
      break;
    case shapes::t_shape:
      if(x <= horizontal_squares - 2)
      {
        new_shape = shapes::t_shape_turned_once;
      }
      break;
    case shapes::t_shape_turned_once:
      if(x >= 1)
      {
        new_shape = shapes::t_shape_turned_twice;
      }
      break;
    case shapes::t_shape_turned_twice:
      new_shape = shapes::t_shape_turned_thrice;
      break;
    case shapes::t_shape_turned_thrice:
      if(x >= 2)
      {
        new_shape = shapes::t_shape;
      }
      break;
    case shapes::s_shape:
      new_shape = shapes::s_shape_turned;
      break;
    case shapes::s_shape_turned:
      if(x <= horizontal_squares - 2)
      {
        new_shape = shapes::s_shape;
      }
      break;
    case shapes::z_shape:
      if(x <= horizontal_squares - 2)
      {
        new_shape = shapes::z_shape_turned;
      }
      break;
    case shapes::z_shape_turned:
      if(x >= 2)
      {
        new_shape = shapes::z_shape;
      }
      break;
    default:
      break;
  }
}
void do_right(std::vector <std::vector<sf::Color>> &grid, shapes &new_shape, int &x, const int y, const int horizontal_squares)
{
  if(new_shape == shapes::i_shape)
  {
    if(x <= horizontal_squares - 2)
    {
      if(grid[x + 1][y - 2] != sf::Color::Green && grid[x + 1][y - 1] != sf::Color::Green &&
         grid[x + 1][y] != sf::Color::Green && grid[x + 1][y + 1] != sf::Color::Green)
      {
        x += 1;
        assert(x <= horizontal_squares - 1);
      }
    }
  }
  if(new_shape == shapes::i_shape_turned)
  {
    if(x <= horizontal_squares - 3)
    {
      x += 1;
      assert(x <= horizontal_squares - 2);
    }
  }
  if(new_shape == shapes::j_shape)
  {
    if(x <= horizontal_squares - 2)
    {
      if(grid[x + 1][y - 2] != sf::Color::Green && grid[x + 1][y - 1] != sf::Color::Green && grid[x + 1][y] != sf::Color::Green)
      {
        x += 1;
        assert(x <= horizontal_squares - 1);
      }
    }
  }
  if(new_shape == shapes::j_shape_turned_once)
  {
    if(x <= horizontal_squares - 4)
    {
      if(grid[x + 1][y - 1] != sf::Color::Green && grid[x + 3][y] != sf::Color::Green)
      {
        x += 1;
        assert(x <= horizontal_squares - 3);
      }
    }
  }
  if(new_shape == shapes::j_shape_turned_twice)
  {
    if(x <= horizontal_squares - 3)
    {
      if(grid[x + 2][y] != sf::Color::Green && grid[x + 1][y + 1] != sf::Color::Green && grid[x + 1][y + 2] != sf::Color::Green)
      {
        x += 1;
        assert(x <= horizontal_squares - 2);
      }
    }
  }
  if(new_shape == shapes::j_shape_turned_thrice)
  {
    if(x <= horizontal_squares - 2)
    {
      if(grid[x + 1][y] != sf::Color::Green && grid[x + 1][y + 1] != sf::Color::Green)
      {
        x += 1;
        assert(x <= horizontal_squares - 1);
      }
    }
  }
  if(new_shape == shapes::l_shape)
  {
    if(x <= horizontal_squares - 3)
    {
      if(grid[x + 1][y - 2] != sf::Color::Green && grid[x + 1][y - 1] != sf::Color::Green && grid[x + 2][y] != sf::Color::Green)
      {
        x += 1;
        assert(x <= horizontal_squares - 2);
      }
    }
  }
  if(new_shape == shapes::l_shape_turned_once)
  {
    if(x <= horizontal_squares - 4)
    {
      if(grid[x + 3][y] != sf::Color::Green && grid[x + 1][y + 1] != sf::Color::Green)
      {
        x += 1;
        assert(x <= horizontal_squares - 3);
      }
    }
  }
  if(new_shape == shapes::l_shape_turned_twice)
  {
    if(x <= horizontal_squares - 2)
    {
      if(grid[x + 1][y] != sf::Color::Green && grid[x + 1][y - 1] != sf::Color::Green && grid[x + 1][y - 2] != sf::Color::Green)
      {
        x += 1;
        assert(x <= horizontal_squares - 1);
      }
    }
  }
  if(new_shape == shapes::l_shape_turned_thrice)
  {
    if(x <= horizontal_squares - 2)
    {
      if(grid[x + 1][y] != sf::Color::Green && grid[x + 1][y - 1] != sf::Color::Green)
      {
        x += 1;
        assert(x <= horizontal_squares - 1);
      }
    }
  }
  if(new_shape == shapes::o_shape)
  {
    if(x <= horizontal_squares - 2)
    {
      if(grid[x + 1][y - 1] != sf::Color::Green && grid[x][y] != sf::Color::Green)
      {
        x += 1;
        assert(x <= horizontal_squares - 1);
      }
    }
  }
  if(new_shape == shapes::t_shape)
  {
    if(x <= horizontal_squares - 3)
    {
      if(grid[x + 1][y - 1] != sf::Color::Green && grid[x + 2][y] != sf::Color::Green)
      {
        x += 1;
        assert(x <= horizontal_squares - 2);
      }
    }
  }
  if(new_shape == shapes::t_shape_turned_once)
  {
    if(x <= horizontal_squares - 3)
    {
      if(grid[x + 1][y - 1] != sf::Color::Green && grid[x + 2][y] != sf::Color::Green && grid[x + 1][y + 1] != sf::Color::Green)
      {
        x += 1;
        assert(x <= horizontal_squares - 2);
      }
    }
  }
  if(new_shape == shapes::t_shape_turned_twice)
  {
    if(x <= horizontal_squares - 3)
    {
      if(grid[x + 2][y] != sf::Color::Green && grid[x + 1][y + 1] != sf::Color::Green)
      {
        x += 1;
        assert(x <= horizontal_squares - 2);
      }
    }
  }
  if(new_shape == shapes::t_shape_turned_thrice)
  {
    if(x <= horizontal_squares - 2)
    {
      if(grid[x + 1][y + 1] != sf::Color::Green && grid[x + 1][y] != sf::Color::Green && grid[x + 1][y - 1] != sf::Color::Green)
      {
        x += 1;
        assert(x <= horizontal_squares - 1);
      }
    }
  }
  if(new_shape == shapes::s_shape)
  {
    if(x <= horizontal_squares - 3)
    {
      if(grid[x + 2][y - 1] != sf::Color::Green && grid[x + 1][y] != sf::Color::Green)
      {
        x += 1;
        assert(x <= horizontal_squares - 2);
      }
    }
  }
  if(new_shape == shapes::s_shape_turned)
  {
    if(x <= horizontal_squares - 2)
    {
      if(grid[x][y - 1] != sf::Color::Green && grid[x + 1][y] != sf::Color::Green && grid[x + 1][y + 1] != sf::Color::Green)
      {
        x += 1;
        assert(x <= horizontal_squares - 1);
      }
    }
  }
  if(new_shape == shapes::z_shape)
  {
    if(x <= horizontal_squares - 3)
    {
      if(grid[x + 1][y - 1] != sf::Color::Green && grid[x + 2][y] != sf::Color::Green)
      {
        x += 1;
        assert(x <= horizontal_squares - 2);
      }
    }
  }
  if(new_shape == shapes::z_shape_turned)
  {
    if(x <= horizontal_squares - 3)
    {
      if(grid[x + 2][y - 1] != sf::Color::Green && grid[x + 2][y] != sf::Color::Green && grid[x + 1][y] != sf::Color::Green)
      {
        x += 1;
        assert(x <= horizontal_squares - 2);
      }
    }
  }
}
void do_left(std::vector <std::vector<sf::Color>> &grid, shapes &new_shape, int &x, const int y)
{
  if(new_shape == shapes::i_shape)
  {
    if(x >= 1)
    {
      if(grid[x - 1][y - 2] != sf::Color::Green && grid[x - 1][y - 1] != sf::Color::Green &&
         grid[x - 1][y] != sf::Color::Green && grid[x - 1][y + 1] != sf::Color::Green)
      {
        x -= 1;
        assert(x >= 0);
      }
    }
  }
  if(new_shape == shapes::i_shape_turned)
  {
    if(x >= 3)
    {
      x -= 1;
      assert(x >= 2);
    }
  }
  if(new_shape == shapes::j_shape)
  {
    if(x >= 2)
    {
      if(grid[x - 1][y - 2] != sf::Color::Green && grid[x - 1][y - 1] != sf::Color::Green && grid[x - 2][y] != sf::Color::Green)
      {
        x -= 1;
        assert(x >= 1);
      }
    }
  }
  if(new_shape == shapes::j_shape_turned_once)
  {
    if(x >= 1)
    {
      if(grid[x - 1][y - 1] != sf::Color::Green && grid[x - 1][y] != sf::Color::Green)
      {
        x -= 1;
        assert(x >= 0);
      }
    }
  }
  if(new_shape == shapes::j_shape_turned_twice)
  {
    if(x >= 1)
    {
      if(grid[x - 1][y] != sf::Color::Green && grid[x - 1][y + 1] != sf::Color::Green && grid[x - 1][y + 2] != sf::Color::Green)
      {
        x -= 1;
        assert(x >= 0);
      }
    }
  }
  if(new_shape == shapes::j_shape_turned_thrice)
  {
    if(x >= 3)
    {
      if(grid[x - 3][y] != sf::Color::Green && grid[x - 1][y + 1] != sf::Color::Green)
      {
        x -= 1;
        assert(x >= 2);
      }
    }
  }
  if(new_shape == shapes::l_shape)
  {
    if(x >= 1)
    {
      if(grid[x - 1][y - 2] != sf::Color::Green && grid[x - 1][y - 1] != sf::Color::Green && grid[x - 1][y] != sf::Color::Green)
      {
        x -= 1;
        assert(x >= 0);
      }
    }
  }
  if(new_shape == shapes::l_shape_turned_once)
  {
    if(x >= 1)
    {
      if(grid[x - 1][y] != sf::Color::Green && grid[x - 1][y + 1] != sf::Color::Green)
      {
        x -= 1;
        assert(x >= 0);
      }
    }
  }
  if(new_shape == shapes::l_shape_turned_twice)
  {
    if(x >= 2)
    {
      if(grid[x - 2][y] != sf::Color::Green && grid[x - 1][y - 1] != sf::Color::Green && grid[x - 1][y - 2] != sf::Color::Green)
      {
        x -= 1;
        assert(x >= 0);
      }
    }
  }
  if(new_shape == shapes::l_shape_turned_thrice)
  {
    if(x >= 3)
    {
      if(grid[x - 3][y] != sf::Color::Green && grid[x - 1][y - 1] != sf::Color::Green)
      {
        x -= 1;
        assert(x >= 2);
      }
    }
  }
  if(new_shape == shapes::o_shape)
  {
    if(x >= 2)
    {
      if(grid[x - 2][y - 1] != sf::Color::Green && grid[x - 2][y] != sf::Color::Green)
      {
        x -= 1;
        assert(x >= 1);
      }
    }
  }
  if(new_shape == shapes::t_shape)
  {
    if(x >= 3)
    {
      if(grid[x - 1][y - 1] != sf::Color::Green && grid[x - 2][y] != sf::Color::Green)
      {
        x -= 1;
        assert(x >= 2);
      }
    }
  }
  if(new_shape == shapes::t_shape_turned_once)
  {
    if(x >= 1)
    {
      if(grid[x - 1][y - 1] != sf::Color::Green && grid[x - 1][y] != sf::Color::Green && grid[x - 1][y + 1] != sf::Color::Green)
      {
        x -= 1;
        assert(x >= 0);
      }
    }
  }
  if(new_shape == shapes::t_shape_turned_twice)
  {
    if(x >= 2)
    {
      if(grid[x - 2][y] != sf::Color::Green && grid[x - 1][y + 1] != sf::Color::Green)
      {
        x -= 1;
        assert(x >= 1);
      }
    }
  }
  if(new_shape == shapes::t_shape_turned_thrice)
  {
    if(x >= 2)
    {
      if(grid[x - 1][y + 1] != sf::Color::Green && grid[x - 2][y] != sf::Color::Green && grid[x - 1][y - 1] != sf::Color::Green)
      {
        x -= 1;
        assert(x >= 1);
      }
    }
  }
  if(new_shape == shapes::s_shape)
  {
    if(x >= 2)
    {
      if(grid[x - 1][y - 1] != sf::Color::Green && grid[x - 2][y] != sf::Color::Green)
      {
        x -= 1;
        assert(x >= 1);
      }
    }
  }
  if(new_shape == shapes::s_shape_turned)
  {
    if(x >= 2)
    {
      if(grid[x - 2][y - 1] != sf::Color::Green && grid[x - 2][y] != sf::Color::Green && grid[x - 1][y + 1] != sf::Color::Green)
      {
        x -= 1;
        assert(x >= 1);
      }
    }
  }
  if(new_shape == shapes::z_shape)
  {
    if(x >= 3)
    {
      if(grid[x - 2][y - 1] != sf::Color::Green && grid[x - 1][y] != sf::Color::Green)
      {
        x -= 1;
        assert(x >= 2);
      }
    }
  }
  if(new_shape == shapes::z_shape_turned)
  {
    if(x >= 1)
    {
      if(grid[x][y - 1] != sf::Color::Green && grid[x - 1][y] != sf::Color::Green && grid[x - 1][y + 1] != sf::Color::Green)
      {
        x -= 1;
        assert(x >= 0);
      }
    }
  }
}
void do_up(std::vector <std::vector<sf::Color>> &grid, shapes &new_shape, const int x, int &y, const int vertical_squares)
{
  // HERE
  if(new_shape == shapes::i_shape)
  {
    do
    {
      y += 1;
      assert(y <= vertical_squares);
    }
    while(grid[x][y] != sf::Color::Green && y != vertical_squares - 1);
    std::cout << y << std::endl;
    if(y == vertical_squares - 1 && grid[x][y] == sf::Color::Green)
    {
      y -= 1;
      assert(y <= vertical_squares - 2);
    }
    else if(y < vertical_squares - 1)
    {
      y -= 1;
      assert(y <= vertical_squares - 2);
    }
  }
  if(new_shape == shapes::i_shape_turned)
  {
    do
    {
      y += 1;
    }
    while(grid[x][y] != sf::Color::Green && grid[x + 1][y] != sf::Color::Green &&
          grid[x + 2][y] != sf::Color::Green && grid[x + 3][y] != sf::Color::Green && y != vertical_squares);
    if(y == vertical_squares - 1 && (grid[x][y] == sf::Color::Green || grid[x + 1][y] == sf::Color::Green ||
                   grid[x + 2][y] == sf::Color::Green || grid[x + 3][y] == sf::Color::Green))
    {
      y -= 1;
      assert(y <= vertical_squares - 2);
    }
    else if(y == vertical_squares)
    {
      y -= 1;
      assert(y <= vertical_squares - 1);
    }
    else if(y < vertical_squares - 1)
    {
      y -= 1;
      assert(y <= vertical_squares - 2);
    }
  }
  if(new_shape == shapes::j_shape)
  {
    do
    {
      y += 1;
      assert(y <= vertical_squares);
    }
    while(grid[x][y] != sf::Color::Green && grid[x + 1][y] != sf::Color::Green && y != vertical_squares - 1);
    if(y == vertical_squares - 1 && (grid[x][y] == sf::Color::Green || grid[x + 1][y] == sf::Color::Green))
    {
      y -= 1;
      assert(y <= vertical_squares - 2);
    }
    else if(y < vertical_squares - 1)
    {
      y -= 1;
      assert(y <= vertical_squares - 2);
    }
  }
  if(new_shape == shapes::j_shape_turned_once)
  {
    do
    {
      y += 1;
      assert(y <= vertical_squares);
    }
    while(grid[x - 2][y] != sf::Color::Green && grid[x - 1][y] != sf::Color::Green && grid[x][y] != sf::Color::Green && y != vertical_squares - 1);
    if(y == vertical_squares - 1 && (grid[x - 2][y] == sf::Color::Green || grid[x - 1][y] == sf::Color::Green || grid[x][y] == sf::Color::Green))
    {
      y -= 1;
      assert(y <= vertical_squares - 2);
    }
    else if(y < vertical_squares - 1)
    {
      y -= 1;
      assert(y <= vertical_squares - 2);
    }
  }
  if(new_shape == shapes::j_shape_turned_twice)
  {
    do
    {
      y += 1;
      assert(y <= vertical_squares);
    }
    while(grid[x][y] != sf::Color::Green && grid[x + 1][y - 2] != sf::Color::Green && y != vertical_squares - 1);
    if(y == vertical_squares - 1 && (grid[x][y] == sf::Color::Green || grid[x + 1][y - 2] == sf::Color::Green))
    {
      y -= 1;
      assert(y <= vertical_squares - 2);
    }
    else if(y < vertical_squares - 1)
    {
      y -= 1;
      assert(y <= vertical_squares - 2);
    }
  }
  if(new_shape == shapes::j_shape_turned_thrice)
  {
    do
    {
      y += 1;
      assert(y <= vertical_squares);
    }
    while(grid[x - 2][y - 1] != sf::Color::Green && grid[x - 1][y - 1] != sf::Color::Green && grid[x][y - 1] != sf::Color::Green && y != vertical_squares - 1);
    if(y == vertical_squares - 1 && (grid[x - 2][y - 1] == sf::Color::Green || grid[x - 1][y - 1] == sf::Color::Green || grid[x][y - 1] == sf::Color::Green))
    {
      y -= 1;
      assert(y <= vertical_squares - 2);
    }
    else if(y < vertical_squares - 1)
    {
      y -= 1;
      assert(y <= vertical_squares - 2);
    }
  }
  if(new_shape == shapes::l_shape)
  {
    do
    {
      y += 1;
      assert(y <= vertical_squares);
    }
    while(grid[x][y] != sf::Color::Green && grid[x - 1][y] != sf::Color::Green && y != vertical_squares - 1);
    if(y == vertical_squares - 1 && (grid[x][y] == sf::Color::Green || grid[x - 1][y] == sf::Color::Green))
    {
      y -= 1;
      assert(y <= vertical_squares - 2);
    }
    else if(y < vertical_squares - 1)
    {
      y -= 1;
      assert(y <= vertical_squares - 2);
    }
  }
  if(new_shape == shapes::l_shape_turned_once)
  {
    do
    {
      y += 1;
      assert(y <= vertical_squares);
    }
    while(grid[x][y] != sf::Color::Green && grid[x + 1][y - 1] != sf::Color::Green && grid[x + 2][y - 1] != sf::Color::Green && y != vertical_squares - 1);
    if(y == vertical_squares - 1 && (grid[x][y] == sf::Color::Green || grid[x + 1][y - 1] == sf::Color::Green || grid[x + 2][y - 1] == sf::Color::Green))
    {
      y -= 1;
      assert(y <= vertical_squares - 2);
    }
    else if(y < vertical_squares - 1)
    {
      y -= 1;
      assert(y <= vertical_squares - 2);
    }
  }
  if(new_shape == shapes::l_shape_turned_twice)
  {
    do
    {
      y += 1;
      assert(y <= vertical_squares);
    }
    while(grid[x][y] != sf::Color::Green && grid[x - 1][y - 2] != sf::Color::Green && y != vertical_squares - 1);
    if(y == vertical_squares - 1 && (grid[x][y] == sf::Color::Green || grid[x - 1][y - 2] == sf::Color::Green))
    {
      y -= 1;
      assert(y <= vertical_squares - 2);
    }
    else if(y < vertical_squares - 1)
    {
      y -= 1;
      assert(y <= vertical_squares - 2);
    }
  }
  if(new_shape == shapes::l_shape_turned_thrice)
  {
    do
    {
      y += 1;
      assert(y <= vertical_squares);
    }
    while(grid[x][y] != sf::Color::Green && grid[x + 1][y] != sf::Color::Green && grid[x + 2][y] != sf::Color::Green && y != vertical_squares - 1);
    if(y == vertical_squares - 1 && (grid[x][y] == sf::Color::Green || grid[x + 1][y] == sf::Color::Green || grid[x + 2][y] == sf::Color::Green))
    {
      y -= 1;
      assert(y <= vertical_squares - 2);
    }
    else if(y < vertical_squares - 1)
    {
      y -= 1;
      assert(y <= vertical_squares - 2);
    }
  }
  if(new_shape == shapes::o_shape)
  {
    do
    {
      y += 1;
      assert(y <= vertical_squares);
    }
    while(grid[x - 1][y] != sf::Color::Green && grid[x][y] != sf::Color::Green && y != vertical_squares - 1);
    std::cout << y << std::endl;
    if(y == vertical_squares - 1 && (grid[x - 1][y] == sf::Color::Green || grid[x][y] == sf::Color::Green))
    {
      y -= 1;
      assert(y <= vertical_squares - 2);
    }
    else if(y < vertical_squares - 1)
    {
      y -= 1;
      assert(y <= vertical_squares - 2);
    }
  }
  if(new_shape == shapes::t_shape)
  {
    do
    {
      y += 1;
      assert(y <= vertical_squares);
    }
    while(grid[x - 2][y] != sf::Color::Green && grid[x - 1][y] != sf::Color::Green && grid[x][y] != sf::Color::Green && y != vertical_squares - 1);
    std::cout << y << std::endl;
    if(y == vertical_squares - 1 && (grid[x - 2][y] == sf::Color::Green || grid[x - 1][y] == sf::Color::Green || grid[x][y] == sf::Color::Green))
    {
      y -= 1;
      assert(y <= vertical_squares - 2);
    }
    else if(y < vertical_squares - 1)
    {
      y -= 1;
      assert(y <= vertical_squares - 2);
    }
  }
  if(new_shape == shapes::t_shape_turned_once)
  {
    do
    {
      y += 1;
      assert(y <= vertical_squares);
    }
    while(grid[x][y] != sf::Color::Green && grid[x + 1][y - 1] != sf::Color::Green && y != vertical_squares - 1);
    if(y == vertical_squares - 1 &&(grid[x][y] == sf::Color::Green || grid[x + 1][y - 1] == sf::Color::Green))
    {
      y -= 1;
      assert(y <= vertical_squares - 2);
    }
    else if(y < vertical_squares - 1)
    {
      y -= 1;
      assert(y <= vertical_squares - 2);
    }
  }
  if(new_shape == shapes::t_shape_turned_twice)
  {
    do
    {
      y += 1;
      assert(y <= vertical_squares);
    }
    while(grid[x - 1][y - 1] != sf::Color::Green && grid[x][y] != sf::Color::Green && grid[x + 1][y - 1] != sf::Color::Green && y != vertical_squares - 1);
    if(y == vertical_squares - 1 && (grid[x - 1][y - 1] == sf::Color::Green || grid[x][y] == sf::Color::Green || grid[x + 1][y - 1] == sf::Color::Green))
    {
      y -= 1;
      assert(y <= vertical_squares - 2);
    }
    else if(y < vertical_squares - 1)
    {
      y -= 1;
      assert(y <= vertical_squares - 2);
    }
  }
  if(new_shape == shapes::t_shape_turned_thrice)
  {
    do
    {
      y += 1;
      assert(y <= vertical_squares);
    }
    while(grid[x - 1][y - 1] != sf::Color::Green && grid[x][y] != sf::Color::Green && y != vertical_squares - 1);
    if(y == vertical_squares - 1 && (grid[x - 1][y - 1] == sf::Color::Green || grid[x][y] == sf::Color::Green))
    {
      y -= 1;
      assert(y <= vertical_squares - 2);
    }
    else if(y < vertical_squares - 1)
    {
      y -= 1;
      assert(y <= vertical_squares - 2);
    }
  }
  if(new_shape == shapes::s_shape)
  {
    do
    {
      y += 1;
      assert(y <= vertical_squares);
    }
    while(grid[x - 1][y] != sf::Color::Green && grid[x][y] != sf::Color::Green && grid[x + 1][y - 1] != sf::Color::Green && y != vertical_squares - 1);
    std::cout << y << std::endl;
    if(y == vertical_squares - 1 && (grid[x - 1][y] == sf::Color::Green || grid[x][y] == sf::Color::Green || grid[x + 1][y - 1] == sf::Color::Green))
    {
      y -= 1;
      assert(y <= vertical_squares - 2);
    }
    else if(y < vertical_squares - 1)
    {
      y -= 1;
      assert(y <= vertical_squares - 2);
    }
  }
  if(new_shape == shapes::s_shape_turned)
  {
    do
    {
      y += 1;
      assert(y <= vertical_squares);
    }
    while(grid[x - 1][y - 1] != sf::Color::Green && grid[x][y] != sf::Color::Green && y != vertical_squares - 1);
    if(y == vertical_squares - 1 && (grid[x - 1][y - 1] == sf::Color::Green || grid[x][y] == sf::Color::Green))
    {
      y -= 1;
      assert(y <= vertical_squares - 2);
    }
    else if(y < vertical_squares - 1)
    {
      y -= 1;
      assert(y <= vertical_squares - 2);
    }
  }
  if(new_shape == shapes::z_shape)
  {
    do
    {
      y += 1;
      assert(y <= vertical_squares);
    }
    while(grid[x - 2][y - 1] != sf::Color::Green && grid[x - 1][y] != sf::Color::Green && grid[x][y] != sf::Color::Green && y != vertical_squares - 1);
    std::cout << y << std::endl;
    if(y == vertical_squares - 1 && (grid[x - 2][y - 1] == sf::Color::Green || grid[x - 1][y] == sf::Color::Green || grid[x][y] == sf::Color::Green))
    {
      y -= 1;
      assert(y <= vertical_squares - 2);
    }
    else if(y < vertical_squares - 1)
    {
      y -= 1;
      assert(y <= vertical_squares - 2);
    }
  }
  if(new_shape == shapes::z_shape_turned)
  {
    do
    {
      y += 1;
      assert(y <= vertical_squares);
    }
    while(grid[x][y] != sf::Color::Green && grid[x + 1][y - 1] != sf::Color::Green && y != vertical_squares - 1);
    if(y == vertical_squares - 1 && (grid[x][y] == sf::Color::Green || grid[x + 1][y - 1] == sf::Color::Green))
    {
      y -= 1;
      assert(y <= vertical_squares - 2);
    }
    else if(y < vertical_squares - 1)
    {
      y -= 1;
      assert(y <= vertical_squares - 2);
    }
  }
}
void choose_random_shape(shapes &new_shape, const int y)
{
  if(y == -1)
  {
    //new_shape = static_cast<shapes>(6);
    new_shape = static_cast<shapes>(rand() % 7);
  }
}
std::vector <sf::Vector2i> choose_new_shape(shapes new_shape, const int x, const int y)
{
  if(new_shape == shapes::i_shape)
  {
    std::vector <sf::Vector2i> i_shape =
    {                              //                 _
      sf::Vector2i(x, y - 2),      // 1              |1|
      sf::Vector2i(x, y - 1),      // 2              |2|
      sf::Vector2i(x, y),          // 3              |3|
      sf::Vector2i(x, y + 1)       // 4              |4|
    };                             //
    return i_shape;
  }
  if(new_shape == shapes::i_shape_turned)
  {
    std::vector <sf::Vector2i> i_shape_turned =
    {                              //
      sf::Vector2i(x - 2, y),      // 1
      sf::Vector2i(x - 1, y),      // 2            _ _ _ _
      sf::Vector2i(x, y),          // 3           |1|2|3|4|
      sf::Vector2i(x + 1, y)       // 4
    };                             //
    return i_shape_turned;
  }
  if(new_shape == shapes::j_shape)
  {
    std::vector <sf::Vector2i> j_shape =
    {                              //
      sf::Vector2i(x, y - 2),      // 1               _
      sf::Vector2i(x, y - 1),      // 2              |1|
      sf::Vector2i(x, y),          // 3             _|2|
      sf::Vector2i(x - 1, y)       // 4            |4|3|
    };                             //
    return j_shape;
  }
  if(new_shape == shapes::j_shape_turned_once)
  {
    std::vector <sf::Vector2i> j_shape_turned_once =
    {                              //
      sf::Vector2i(x, y - 1),      // 1               _
      sf::Vector2i(x, y),          // 2              |1|_ _
      sf::Vector2i(x + 1, y),      // 3              |2|3|4|
      sf::Vector2i(x + 2, y)       // 4
    };                             //
    return j_shape_turned_once;
  }
  if(new_shape == shapes::j_shape_turned_twice)
  {
    std::vector <sf::Vector2i> j_shape_turned_twice =
    {                              //
      sf::Vector2i(x, y),          // 1               _ _
      sf::Vector2i(x + 1, y),      // 2              |1|2|
      sf::Vector2i(x, y + 1),      // 3              |3|
      sf::Vector2i(x, y + 2)       // 4              |4|
    };                             //
    return j_shape_turned_twice;
  }
  if(new_shape == shapes::j_shape_turned_thrice)
  {
    std::vector <sf::Vector2i> j_shape_turned_thrice =
    {                              //
      sf::Vector2i(x - 2, y),      // 1
      sf::Vector2i(x - 1, y),      // 2              _ _ _
      sf::Vector2i(x, y),          // 3             |1|2|3|
      sf::Vector2i(x, y + 1)       // 4                 |4|
    };                             //
    return j_shape_turned_thrice;
  }
  if(new_shape == shapes::l_shape)
  {
    std::vector <sf::Vector2i> l_shape =
    {                             //
      sf::Vector2i(x, y - 2),     // 1              _
      sf::Vector2i(x, y - 1),     // 2             |1|
      sf::Vector2i(x, y),         // 3             |2|_
      sf::Vector2i(x + 1, y)      // 4             |3|4|
    };                            //
    return l_shape;
  }
  if(new_shape == shapes::l_shape_turned_once)
  {
    std::vector <sf::Vector2i> l_shape_turned_once =
    {                             //
      sf::Vector2i(x, y),         // 1
      sf::Vector2i(x + 1, y),     // 2                _ _ _
      sf::Vector2i(x + 2, y),     // 3               |1|2|3|
      sf::Vector2i(x, y + 1)      // 4               |4|
    };                            //
    return l_shape_turned_once;
  }
  if(new_shape == shapes::l_shape_turned_twice)
  {
    std::vector <sf::Vector2i> l_shape_turned_twice =
    {                             //
      sf::Vector2i(x - 1, y),     // 1                _ _
      sf::Vector2i(x, y),         // 2               |1|2|
      sf::Vector2i(x, y + 1),     // 3                 |3|
      sf::Vector2i(x, y + 2)      // 4                 |4|
    };                            //
    return l_shape_turned_twice;
  }
  if(new_shape == shapes::l_shape_turned_thrice)
  {
    std::vector <sf::Vector2i> l_shape_turned_thrice =
    {                             //
      sf::Vector2i(x - 2, y),     // 1                     _
      sf::Vector2i(x - 1, y),     // 2                 _ _|4|
      sf::Vector2i(x, y),         // 3                |1|2|3|
      sf::Vector2i(x, y - 1)      // 4
    };                            //
    return l_shape_turned_thrice;
  }
  if(new_shape == shapes::o_shape)
  {
    std::vector <sf::Vector2i> o_shape =
    {                             //
      sf::Vector2i(x - 1, y - 1), // 1              _ _
      sf::Vector2i(x, y - 1),     // 2             |1|2|
      sf::Vector2i(x - 1, y),     // 3             |3|4|
      sf::Vector2i(x, y)          // 4
    };                            //
    return o_shape;
  }
  if(new_shape == shapes::t_shape)
  {
    std::vector <sf::Vector2i> t_shape =
    {                             //
      sf::Vector2i(x, y - 1),     // 1                _
      sf::Vector2i(x - 1, y),     // 2              _|1|_
      sf::Vector2i(x, y),         // 3             |2|3|4|
      sf::Vector2i(x + 1, y)      // 4
    };                            //
    return t_shape;
  }
  if(new_shape == shapes::t_shape_turned_once)
  {
    std::vector <sf::Vector2i> t_shape_turned_once =
    {                             //
      sf::Vector2i(x, y - 1),     // 1                _
      sf::Vector2i(x, y),         // 2               |1|_
      sf::Vector2i(x + 1, y),     // 3               |2|3|
      sf::Vector2i(x, y + 1)      // 4               |4|
    };                            //
    return t_shape_turned_once;
  }
  if(new_shape == shapes::t_shape_turned_twice)
  {
    std::vector <sf::Vector2i> t_shape_turned_twice =
    {                             //
      sf::Vector2i(x - 1, y),     // 1              _ _ _
      sf::Vector2i(x, y),         // 2             |1|2|3|
      sf::Vector2i(x + 1, y),     // 3               |4|
      sf::Vector2i(x, y + 1)      // 4
    };                            //
    return t_shape_turned_twice;
  }
  if(new_shape == shapes::t_shape_turned_thrice)
  {
    std::vector <sf::Vector2i> t_shape_turned_thrice =
    {                             //
      sf::Vector2i(x, y + 1),     // 1                _
      sf::Vector2i(x - 1, y),     // 2              _|1|
      sf::Vector2i(x, y),         // 3             |2|3|
      sf::Vector2i(x, y - 1)      // 4               |4|
    };                            //
    return t_shape_turned_thrice;
  }
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
  if(new_shape == shapes::s_shape_turned)
  {
    std::vector <sf::Vector2i> s_shape_turned =
    {                             //
      sf::Vector2i(x - 1, y - 1), // 1               _
      sf::Vector2i(x - 1, y),     // 2              |1|_
      sf::Vector2i(x, y),         // 3              |2|3|
      sf::Vector2i(x, y + 1)      // 4                |4|
    };                            //
    return s_shape_turned;
  }
  if(new_shape == shapes::z_shape)
  {
    std::vector <sf::Vector2i> z_shape =
    {                             //
      sf::Vector2i(x - 1, y - 1), // 1              _ _
      sf::Vector2i(x, y - 1),     // 2             |1|2|_
      sf::Vector2i(x, y),         // 3               |3|4|
      sf::Vector2i(x + 1, y)      // 4
    };                            //
    return z_shape;
  }
  if(new_shape == shapes::z_shape_turned)
  {
    std::vector <sf::Vector2i> z_shape_turned =
    {                             //
      sf::Vector2i(x + 1, y - 1), // 1                 _
      sf::Vector2i(x + 1, y),     // 2               _|1|
      sf::Vector2i(x, y),         // 3              |3|2|
      sf::Vector2i(x, y + 1)      // 4              |4|
    };                            //
    return z_shape_turned;
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
