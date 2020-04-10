#ifndef _PTL_UTILITIES_SPARSER_H
#define _PTL_UTILITIES_SPARSER_H

#include <string>
#include "mac.h"
#include "math.h"

namespace ptl {

  struct parser_character
  {
    const static int meanless   = -1;
    const static int delimiter  = -2;
    const static int positive   = -3;
    const static int negative   = -4;
    const static int dot        = -5;
    const static int exponent   = -6;
  };

  struct numeric_parser_event_base
  {
    static inline void on_initialize() { }
    static inline void on_finalize()   { }
    template <class T> static inline void on_newdata(T) { }
    static inline void on_delimiter() { }
  };

  template <class T, class event_type>
  class numeric_parser
  {
  };

  template <class event_type>
  class numeric_parser<std::string, event_type> _EXTENDS event_type
  {
    public:

      typedef event_type parents_type;

      inline void clear()
      {
        have_data = false;
        data = "";
        parents_type::on_initialize();
      }

      inline void finalize()
      {
        on_meanless(0);
        parents_type::on_finalize();
      }

    protected:

      void init_table(int* table)
      {
        for (int i = 0; i < 256; i ++)
        {
          table[i] = parser_character::meanless;
        }
        for (int i = 32; i < 127; i ++) table[i] = i;
      }

      inline void on_meanless(int info)
      {
        if (have_data)
        {
          parents_type::on_newdata(data);
          have_data = false;
          data = "";
        }
      }

      inline void on_input(int info)
      {
        data += (char)info;
        have_data = true;
      }

    private:

      bool have_data;
      std::string data;
  };

  template <class event_type>
  class numeric_parser<unsigned, event_type> _EXTENDS event_type
  {
    public:

      typedef event_type parents_type;

      inline void clear()
      {
        have_data = false;
        data = 0;
        parents_type::on_initialize();
      }

      inline void finalize()
      {
        on_meanless(0);
        parents_type::on_finalize();
      }

    protected:

      void init_table(int* table);

      inline void on_meanless(int info)
      {
        if (have_data)
        {
          parents_type::on_newdata(data);
          have_data = false;
          data = 0;
        }
      }

      inline void on_input(int info)
      {
        data = 10*data+info;
        have_data = true;
      }

    private:

      bool have_data;
      unsigned data;
  };

  template <class event_type>
  void numeric_parser<unsigned, event_type>::init_table(int* table)
  {
    for (int i = 0; i < 256; i ++)
    {
      table[i] = parser_character::meanless;
    }
    for (int i = 0; i < 10; i ++)
    {
      table[i+'0'] = i;
    }
  }

  template <class event_type>
  class numeric_parser<int, event_type> _EXTENDS event_type
  {
    public:

      typedef event_type parents_type;

      inline void clear()
      {
        have_data = false;
        data = 0;
        negative = 1;
        parents_type::on_initialize();
      }

      inline void finalize()
      {
        on_meanless(0);
        parents_type::on_finalize();
      }

    protected:

      void init_table(int* table);

      inline void on_meanless(int info)
      {
        if (have_data)
        {
          parents_type::on_newdata(negative*data);
          have_data = false;
          negative = 1;
          data = 0;
        }
      }

      inline void on_input(int info)
      {
        if (info == parser_character::negative)
        {
          negative = -1;
        }
        else
        {
          data = 10*data+info;
          have_data = true;
        }
      }

    private:

      bool have_data;
      int data;
      int negative;
  };

  template <class event_type>
  void numeric_parser<int, event_type>::init_table(int* table)
  {
    for (int i = 0; i < 256; i ++)
    {
      table[i] = parser_character::meanless;
    }
    for (int i = 0; i < 10; i ++)
    {
      table[i+'0'] = i;
    }
    table['-'] = parser_character::negative;
  }

  template <class event_type>
  class numeric_parser<double, event_type> _EXTENDS event_type
  {
    public:

      typedef event_type parents_type;
      typedef double value_type;

      inline void clear()
      {
        data = 0.;
        exponent = 0.;
        sign = 1.;
        status = dec;
        have_data = false;
        parents_type::on_initialize();
      }

      inline void finalize()
      {
        on_meanless(0);
        parents_type::on_finalize();
      }

    protected:

      void init_table(int* table);

      inline void on_meanless(int info)
      {
        if (have_data)
        {
          parents_type::on_newdata(data*std_math<value_type>::pow(10., exponent));
          data = 0.;
          exponent = 0.;
          sign = 1.;
          status = dec;
          have_data = false;
        }
      }

      inline void on_input(int info)
      {
        if(info == parser_character::positive)        on_positive();
        else if (info == parser_character::negative)  on_negative();
        else if (info == parser_character::dot)       on_dot();
        else if (info == parser_character::exponent)  on_exponent();
        else                                          on_data(info);
      }
      inline void on_positive()
      {
        sign = 1.;
      }
      inline void on_negative()
      {
        sign = -1.;
      }
      inline void on_dot()
      {
        status = dot;
        fraction = sign;
      }
      inline void on_exponent()
      {
        status = exp;
        sign = 1.;
        exponent = 0.;
      }
      inline void on_data(int info)
      {
        if (status == exp)
        {
          exponent = 10.*exponent+sign*info;
        }
        else if (status == dot)
        {
          fraction *= 0.1;
          data += fraction*info;
        }
        else
        {
          data = 10.*data+sign*info;
        }
        have_data = true;
      }

    private:

      const static int dec = 0;
      const static int dot = 1;
      const static int exp = 2;

      int status;
      bool have_data;
      value_type data, exponent, fraction, sign;
  };

  template <class event_type>
  void numeric_parser<double, event_type>::init_table(int* table)
  {
    for (int i = 0; i < 256; i ++)
    {
      table[i] = parser_character::meanless;
    }
    for (int i = 0; i < 10; i ++)
    {
      table[i+'0'] = i;
    }
    table['+'] = parser_character::positive;
    table['-'] = parser_character::negative;
    table['.'] = parser_character::dot;
    table['e'] = parser_character::exponent;
    table['E'] = parser_character::exponent;

  }

  template <class event_type, char delimiter = '\n'>
  struct delimiter_event _EXTENDS event_type
  {
    typedef event_type parents_type;
    inline void init_table(int* table)
    {
      parents_type::init_table(table);
      table[delimiter] = parser_character::delimiter;
    }
    inline void on_input(int info)
    {
      if (info == parser_character::delimiter)
      {
        parents_type::on_meanless(info);
        parents_type::on_delimiter();
      }
      else parents_type::on_input(info);
    }
  };

  template <class event_type>
  class simple_parser _EXTENDS event_type
  {
    public:

      typedef event_type parents_type;

      inline simple_parser()
      {
        parents_type::init_table(table);
        parents_type::clear();
      }

      inline void next(char c)
      {
        register int info = table[int(c)];
        if (info == parser_character::meanless)
          event_type::on_meanless(info);
        else
          event_type::on_input(info);
      }

    private:
      int table[256];
  };

}
#endif
