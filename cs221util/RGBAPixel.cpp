/**
 * @file RGBAPixel.cpp
 * Implementation of the RGBAPixel class for use in with the PNG library.
 *
 * @author CS 225: Data Structures
 * @version 2018r1
 */

#include "RGBAPixel.h"
#include <cmath>
#include <iostream>
using namespace std;

namespace cs221util {
  RGBAPixel::RGBAPixel() {
    r = 0;
    g = 0;
    b = 0;
    a = 1.0;
  }

  RGBAPixel::RGBAPixel(const RGBAPixel& other) {
      r = other.r;
      g = other.g;
      b = other.b;
      a = other.a;
  }

  RGBAPixel::RGBAPixel(int red, int green, int blue){
    r = red;
    g = green;
    b = blue;
    a = 1.0;
  }
  RGBAPixel::RGBAPixel(int red, int green, int blue, double alpha){
    r = red;
    g = green;
    b = blue;
    a = alpha;
  }

  RGBAPixel & RGBAPixel::operator=(RGBAPixel const & other) {
    this->r = other.r;
    this->g = other.g;
    this->b = other.b;
    this->a = other.a;
    return *this;
  }

  bool RGBAPixel::operator== (RGBAPixel const & other) const {
    // thank/blame Wade for the following function
    // adapted by cinda to allow for slight deviations in RGB

    if ( a == 0 ) { return true; }
    if (fabs(a - other.a) > 0.01) { return false; }

    if (fabs(r - other.r) > 2) { return false; } 
    if (fabs(g - other.g) > 2) { return false; } 
    if (fabs(b - other.b) > 2) { return false; } 

    return true;
}

  bool RGBAPixel::operator!= (RGBAPixel const & other) const {
    return !(*this == other);
  }

  bool RGBAPixel::operator<  (RGBAPixel const & other) const {
    // Cinda is not sure where this is used. Fairly arb total
    // order is reflected here. R->G->B.
      if (*this == other) { return false; }

      if (r < other.r)
          return true;
      else if ((r == other.r) && (g < other.g))
          return true;
      else if ((r == other.r) && (g == other.g) && (b < other.b))
          return true;

      return false;
  }


  /**
   * Computes the RGBA color distance between this pixel and another pixel.
   *
   * @param other the other RGBAPixel to compare to this one
   */
  double RGBAPixel::distanceTo(RGBAPixel other) {
      // this pixel's color channels
      double r_this = (r / 255.0) * a;
      double g_this = (g / 255.0) * a;
      double b_this = (b / 255.0) * a;

      // other pixel's color channels
      double r_other = (other.r / 255.0) * other.a;
      double g_other = (other.g / 255.0) * other.a;
      double b_other = (other.b / 255.0) * other.a;

      double r_diff = r_other - r_this;
      double g_diff = g_other - g_this;
      double b_diff = b_other - b_this;

      double alphadiff = other.a - a;

      double maxdiff_r = max(r_diff * r_diff, (r_diff - alphadiff) * (r_diff - alphadiff));
      double maxdiff_g = max(g_diff * g_diff, (g_diff - alphadiff) * (g_diff - alphadiff));
      double maxdiff_b = max(b_diff * b_diff, (b_diff - alphadiff) * (b_diff - alphadiff));

      return maxdiff_r + maxdiff_g + maxdiff_b;
  }

  std::ostream & operator<<(std::ostream & out, RGBAPixel const & pixel) {
    out << "(" << pixel.r << ", " << pixel.g << ", " << pixel.b << (pixel.a != 1 ? ", " + std::to_string(pixel.a) : "") << ")";

    return out;
  }

}
