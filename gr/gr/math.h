#ifndef _PTL_UTILITIES_MATH_H
#define _PTL_UTILITIES_MATH_H

/***************************************************************************
 *
 * exmath   -  Encapsulation of standard C/C++ math libarty
 *             for the Plug-in Template Library vector
 *
 ***************************************************************************
 *
 * Copyright (c) 2003
 * Author - Chaoming Song
 *
 **************************************************************************/

#include <limits>
#include <cmath>
#include <complex>
#include "mac.h"

#ifdef max
  #undef max
#endif

#ifdef min
  #undef min
#endif


#ifdef min_value
  #undef min_value
#endif

#ifdef max_value
  #undef max_value
#endif

#ifdef pi
  #undef pi
#endif

#ifdef sq
  #undef sq
#endif

#ifdef acos
  #undef acos
#endif

#ifdef asin
  #undef asin
#endif

#ifdef atan
  #undef atan
#endif

#ifdef ceil
  #undef ceil
#endif

#ifdef cosh
  #undef cosh
#endif

#ifdef exp
  #undef exp
#endif

#ifdef floor
  #undef floor
#endif

#ifdef frexp
  #undef frexp
#endif

#ifdef ldexp
  #undef ldexp
#endif

#ifdef log
  #undef log
#endif

#ifdef log10
  #undef log10
#endif

#ifdef modf
  #undef modf
#endif

#ifdef pow
  #undef pow
#endif

#ifdef sin
  #undef sinh
#endif

#ifdef sqrt
  #undef sqrt
#endif

#ifdef tan
  #undef sqrt
#endif

#ifdef tanh
  #undef sqrt
#endif

namespace ptl {


  template <class value_interface>
  class math_base _EXTENDS std::numeric_limits<value_interface>
  {

    public:

      typedef value_interface               value_type;
      typedef std::complex<value_type>      complex_value_type;

      static inline const value_type abs(const value_type& t)
      {
        if (t > 0)
          return t;
        else
          return -t;
      }

      static inline const value_type sign(const value_type& a, const value_type& b)
      {
        return b >= 0 ? (a >= 0 ? a : -a) : (a >= 0 ? -a : a);
      }

      static inline void swap(value_type& a, value_type& b)
      {
        value_type c = a;
        a = b, b = c;
      }

      static inline const value_type max(const value_type& t1, const value_type& t2)
      {
        if (t1 > t2)
          return t1;
        else
          return t2;
      }

      static inline const value_type min(const value_type& t1, const value_type& t2)
      {
        if (t1 < t2)
          return t1;
        else
          return t2;
      }

      static inline const value_type sq(const value_type& t)
      {
        return t*t;
      }

      static inline const value_type max_value()
      {
        return std::numeric_limits<value_type>::max();
      }

      static inline const value_type  min_value()
      {
        return std::numeric_limits<value_type>::min();
      }

      static inline const value_type  pi()
      {
        return 3.14159265358979323846;
      }

// complex type

      static inline value_type abs(const complex_value_type& c)
      {
        return std::abs(c);
      }
      static inline value_type arg(const complex_value_type& x)
      {
        return std::arg(x);
      }
      static inline complex_value_type conj(const complex_value_type& c)
      {
        return std::conj(c);
      }

      static inline complex_value_type cos(const complex_value_type& c)
      {
        return std::cos(c);
      }

      static inline complex_value_type cosh(const complex_value_type& c)
      {
        return std::cosh(c);
      }

      static inline complex_value_type exp(const complex_value_type& x)
      {
        return std::exp(x);
      }

      static inline value_type imag(const complex_value_type& c)
      {
        return std::imag(c);
      }

      static inline complex_value_type log(const complex_value_type& x)
      {
        return std::log(x);
      }

      static inline complex_value_type log10(const complex_value_type& x)
      {
        return std::log10(x);
      }

      static inline value_type norm(const complex_value_type& c)
      {
        return std::norm(c);
      }

      static inline complex_value_type polar(const value_type& m, const value_type& a = 0)
      {
        return std::polar(m, a);
      }

      static inline complex_value_type pow(const complex_value_type& x, int y)
      {
        return std::pow(x, y);
      }

      static inline complex_value_type pow(const complex_value_type& x, const value_type& y)
      {
        return std::pow(x,y);
      }

      static inline complex_value_type pow(const complex_value_type& x, const complex_value_type& y)
      {
        return std::pow(x,y);
      }

      static inline complex_value_type pow(const value_type& x, const complex_value_type& y)
      {
        return std::pow(x,y);
      }

      static inline value_type real(const complex_value_type& c)
      {
        return std::real(c);
      }

      static inline complex_value_type sin(const complex_value_type& c)
      {
        return std::sin(c);
      }

      static inline complex_value_type sinh(const complex_value_type& c)
      {
        return std::sinh(c);
      }

      static inline complex_value_type sqrt(const complex_value_type& x)
      {
        return std::sqrt(x);
      }

      static inline complex_value_type tan(const complex_value_type& x)
      {
        return std::tan(x);
      }

      static inline complex_value_type tanh(const complex_value_type& x)
      {
        return std::tanh(x);
      }
  };

  template <class value_type>
  class std_math _EXTENDS math_base<value_type>
  {
  };


  template <>
  class std_math<double> _EXTENDS math_base<double>
  {

    public:

      typedef double         value_type;

      static inline double acos(double x)
      {
        return ::acos(x);
      }

      static inline double asin(double x)
      {
        return ::asin(x);
      }

      static inline double atan(double x)
      {
        return ::atan(x);
      }

      static inline double atan(double y, double x)
      {
        return ::atan2(y,x);
      }

      static inline double ceil(double x)
      {
        return ::ceil(x);
      }

      static inline double cosh(double x)
      {
        return ::cosh(x);
      }

      static inline double exp(double x)
      {
        return ::exp(x);
      }

      static inline double floor(double x)
      {
        return ::floor(x);
      }

      static inline double fmod(double x, double y)
      {
        return ::fmod(x,y);
      }

      static inline double frexp(double x, int *exponent)
      {
        return ::frexp(x,exponent);
      }

      static inline double ldexp(double x, int exp)
      {
        return ::ldexp(x, exp);
      }

      static inline double log(double x)
      {
        return ::log(x);
      }

      static inline double log10(double x)
      {
        return ::log10(x);
      }

      static inline double modf(double x, double *ipart)
      {
        return ::modf(x, ipart);
      }

      static inline double pow(double x, double y)
      {
        return ::pow(x, y);
      }

      static inline double sin(double x)
      {
        return ::sin(x);
      }

      static inline double sinh(double x)
      {
        return ::sinh(x);
      }

      static inline double sqrt(double x)
      {
        return ::sqrt(x);
      }

      static inline double tan(double x)
      {
        return ::tan(x);
      }

      static inline double tanh(double x)
      {
        return ::tanh(x);
      }
  };

  template <>
  class std_math<long double> _EXTENDS math_base<long double>
  {

    public:

      typedef long double         value_type;

      static inline long double acos(long double x)
      {
        return ::acosl(x);
      }

      static inline long double asin(long double x)
      {
        return ::asinl(x);
      }

      static inline long double atan(long double x)
      {
        return ::atanl(x);
      }

      static inline long double atan(long double y, long double x)
      {
        return ::atan2l(y,x);
      }

      static inline long double ceil(long double x)
      {
        return ::ceill(x);
      }

      static inline long double cosh(long double x)
      {
        return ::coshl(x);
      }

      static inline long double exp(long double x)
      {
        return ::expl(x);
      }

      static inline long double floor(long double x)
      {
        return ::floorl(x);
      }

      static inline long double fmod(long double x, long double y)
      {
        return ::fmodl(x,y);
      }

      static inline long double frexp(long double x, int *exponent)
      {
        return ::frexpl(x,exponent);
      }

      static inline long double ldexp(long double x, int exp)
      {
        return ::ldexpl(x, exp);
      }

      static inline long double log(long double x)
      {
        return ::logl(x);
      }

      static inline long double log10(long double x)
      {
        return ::log10l(x);
      }

      static inline long double modf(long double x, long double *ipart)
      {
        return ::modfl(x, ipart);
      }

      static inline long double pow(long double x, long double y)
      {
        return ::powl(x, y);
      }

      static inline long double sin(long double x)
      {
        return ::sinl(x);
      }

      static inline long double sinh(long double x)
      {
        return ::sinhl(x);
      }

      static inline long double sqrt(long double x)
      {
        return ::sqrtl(x);
      }

      static inline long double tan(long double x)
      {
        return ::tanl(x);
      }

      static inline long double tanh(long double x)
      {
        return ::tanhl(x);
      }
  };

  typedef std_math<double>                          dmath;
//  typedef std_math<long double>                     ldmath;

}

#endif

