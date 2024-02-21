#include "cube.h"
#include <iostream>

int main() {
  uiuc::Cube c;
  c.setLength(3.48);
  double volume = c.getVolume();
  std::cout << "Volume: " << volume << std::endl;
  return 0;  
}
