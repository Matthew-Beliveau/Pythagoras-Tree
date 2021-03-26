#include <SFML/Graphics.hpp>
//#include <ConvexShape.hpp>
#include <SFML/Window.hpp>
#include <iostream>
#include <cmath>
#include <ctime>
using namespace sf;


class PTree: public Drawable
{

public:
  PTree(int _depth, float sideLength);
private:
  void generateTree(RenderTarget& target, const Vector2f& b1,
                      const Vector2f& b2, double sidelength, int _depth) const;
  void draw(RenderTarget &target, RenderStates states) const;
  float sideLength;
  int depth;
  int angle;
};

void PTree::draw(RenderTarget& target, RenderStates states) const
{

  float window_length = 9 * sideLength;
  float window_height = 6 * sideLength;
  float x1 = (window_length / 2 - sideLength / 2) - window_length/1.7F;
  float x2 = x1 + sideLength;
  float y2 = (window_height - 10) + window_height/2.8f;
  float y1 = y2 - sideLength;
  Vector2f b1(x1, y1);
  Vector2f b2(x2, y2);
  generateTree(target, b1, b2, sideLength, depth);
}

void PTree::generateTree(RenderTarget& target, const Vector2f& b1,
                          const Vector2f& b2, double sideLength,
                          int _depth) const
{
  // Base Case
  if (!_depth)
  {
    return;
  }
  Vector2f base1 = b1;
  Vector2f base2 = b2;
  float delx = base2.x - base1.x;
  float dely = base1.y - base2.y;

  Vector2f base3((base2.x - dely), (base2.y - delx));
  Vector2f base4((base1.x - dely), (base1.y - delx));

  Vector2f base5(((base1.x - dely) + ((delx - dely)/angle)),
                  ((base1.y - delx) - ((delx+dely)/angle)));


  Color color;
  switch(rand() % 4)
  {
    case 0:
      color = Color::Red; break;
    case 1:
      color = Color::Green; break;
    case 2:
      color = Color::Yellow; break;
    case 3:
      color = Color::White; break;
    default:
      break;
  }

  ConvexShape square;
  square.setOutlineThickness(1);
  square.setOutlineColor(color);
  square.setFillColor(Color::Transparent);

  square.setPointCount(4);
  square.setPoint(0, base1);
  square.setPoint(1, base2);
  square.setPoint(2, base3);
  square.setPoint(3, base4);
  square.rotate(-45);
  target.draw(square);

  sideLength /= 2;
  generateTree(target, base4, base5, sideLength, _depth-1);
  generateTree(target, base5, base3, sideLength, _depth-1);
}

PTree::PTree(int _depth, float length)
{
  sideLength = length;
  depth = _depth;
  srand(time(NULL));
  angle = rand() % 5 + 2;
  std::cout << "The angle is: " << angle << std::endl;
}

int main (int argc, char ** argv)
{

  // bring in the CLA
  double l = atof (argv[1]);
  int n = atof (argv[2]);

  // Create The RenderWindow

  RenderWindow window (VideoMode (9*l, 6*l), "SFML Window");

  PTree tree(n, l);
  window.draw(tree);

  while (window.isOpen())
  {
    //Process events
    Event event;
    while (window.pollEvent(event))
    {
      // Close window: exit
      if (event.type == Event::Closed)
        window.close();
    }
    window.display();
  }
  return EXIT_SUCCESS;
}
