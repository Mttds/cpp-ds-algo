/**
 * Simple C++ class for representing a Cube (with constructors).
 * 
 * @author
 *   Wade Fagen-Ulmschneider <waf@illinois.edu>
 */

#pragma once // required to instruct compiler to compile only once

namespace uiuc {
  class Cube {
    public: // public protection region
      Cube();  // Custom default constructor
      Cube(const Cube & obj);  // Custom copy constructor

      double getVolume();
      double getSurfaceArea();
      void setLength(double length);

    private: // private protection region
      double length_; // google style guide to have _ appendend for private members
  };
}
