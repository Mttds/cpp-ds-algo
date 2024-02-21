/**
 * @file HSLAPixel.h
 *
 * @author University of Illinois CS 225 Course Staff
 * @version 2018r1-lab1 - Updated for CS 400
 */

#pragma once

#include <iostream>
#include <sstream>

namespace uiuc {
  class HSLAPixel {
    public:
      double h; // hue
      double s; // saturation
      double l; // luminance
      double a; // alpha channel
      static constexpr double MAX_HUE = 360;
      
      HSLAPixel() {}
      HSLAPixel(double h, double s, double l, double a) : h(h), s(s), l(l), a(a) {}
  };
}
