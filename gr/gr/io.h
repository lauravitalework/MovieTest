
#define _CRT_SECURE_NO_WARNINGS
#ifndef _PTL_UTILITIES_IO_H
#define _PTL_UTILITIES_IO_H
#include <ostream>
#include <istream>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cstdlib>
#include "sparser.h"

namespace ptl {


#ifdef _PTL_VECTOR_H
  template <class T1, class T2>
  std::ostream& operator<< (std::ostream& os, const vector_base<T1, T2>& v)
  {
    os << '<' << v[0];
    for (typename vector_base<T1, T2>::size_type i = 1; i < v.size(); i ++) os << ',' << v[i];
    return os << '>';
  }
#endif

  template <class T>
  inline void write_binary(std::ostream& os, const T& v)
  {
    os.write(reinterpret_cast<const char*>(&v), sizeof(v));
  }

  template <class T>
  inline void read_binary(std::istream& is, T& v)
  {
    is.read(reinterpret_cast<char*>(&v), sizeof(v));
  }

  template <class T>
  inline void write_binary(std::ostream& os, const T* v, const int n)
  {
    os.write(reinterpret_cast<const char*>(v), sizeof(T)*n);
  }

  template <class T>
  inline void read_binary(std::istream& is, T* v, const int n)
  {
    is.read(reinterpret_cast<char*>(v), sizeof(T)*n);
  }

  template <class container_interface>
  class numeric_container_parser_event _EXTENDS numeric_parser_event_base
  {
    public:

      typedef container_interface container_type;
      typedef _TYPENAME container_type::value_type value_type;

      inline void set_container(container_type& x) { p = &x; }

    protected:

      inline void on_newdata(value_type x) { p->push_back(x); }

    private:
      container_type *p;
  };

  template <class container_interface, class container_interface2>
  class numeric_container_parser_event2
    _EXTENDS numeric_container_parser_event<container_interface>
  {
    public:
      typedef numeric_container_parser_event<container_interface> parents_type;
      typedef _TYPENAME parents_type::value_type value_type;

      inline void set_container(container_interface& x1,
                                container_interface2& x2)
      { parents_type::set_container(x1); p = &x2; }

    protected:

      inline void on_initialize() { count = 0; }
      inline void on_finalize()   { if (count) p->push_back(count); }
      inline void on_newdata(value_type x) { parents_type::on_newdata(x); count ++; }
      inline void on_delimiter() { if (count) p->push_back(count); count = 0; }

    private:
      container_interface2* p;
      unsigned count;
  };

  template <class container_interface>
  class numeric_container_parser_event3 _EXTENDS numeric_parser_event_base
  {
    public:
      typedef numeric_container_parser_event<container_interface> parents_type;
      typedef _TYPENAME parents_type::value_type containter_type;
      typedef _TYPENAME containter_type::value_type value_type;

      inline void set_container(container_interface& x) { p = &x; }

    protected:

      inline void on_initialize() { temp.clear(); }
      inline void on_finalize()   { if (!temp.empty()) p->push_back(temp); }
      inline void on_newdata(value_type x) { temp.push_back(x); }
      inline void on_delimiter() { if (!temp.empty()) p->push_back(temp); temp.clear(); }

    private:
      container_interface* p;
      containter_type temp;
  };

  template <_INTERFACE char_type, _INTERFACE container_type>
  void sscan(const char_type* buffer, container_type& data)
  {
    typedef _TYPENAME container_type::value_type value_type;
    typedef numeric_container_parser_event<container_type> event_type;

    simple_parser<numeric_parser<value_type, event_type> > parser;

    parser.set_container(data);

    for (register const char_type* p = buffer; *p != '\0'; p ++)
    {
      parser.next(*p);
    }
    parser.finalize();
  }

  template <_INTERFACE char_type, _INTERFACE container_type, _INTERFACE container_type2>
  void sscan(const char_type* buffer, container_type& data, container_type2& format)
  {

    typedef _TYPENAME container_type::value_type value_type;
    typedef numeric_container_parser_event2<container_type, container_type2> event_type;

    simple_parser<delimiter_event<numeric_parser<value_type, event_type> > > parser;

    parser.set_container(data, format);

    for (register const char_type* p = buffer; *p != '\0'; p ++)
    {
      parser.next(*p);
    }
    parser.finalize();
  }

  template<_INTERFACE container_type>
  void sscan(std::istream& is, container_type& data)
  {
    typedef numeric_container_parser_event<container_type> event_type;
    typedef _TYPENAME event_type::value_type value_type;

    simple_parser<numeric_parser<value_type, event_type> > parser;

    parser.set_container(data);

    std::istream::char_type c;
    while (true)
    {
      c = is.get();
      if(is.eof()) break;
      parser.next(c);
    }
    parser.finalize();
  }

  template<_INTERFACE container_type>
  void sscan_matrix(std::istream& is, container_type& data)
  {
    typedef numeric_container_parser_event3<container_type> event_type;
    typedef _TYPENAME event_type::value_type value_type;

    simple_parser<delimiter_event<numeric_parser<value_type, event_type> > > parser;

    parser.set_container(data);

    std::istream::char_type c;
    while (true)
    {
      c = is.get();
      if(is.eof()) break;
      parser.next(c);
    }
    parser.finalize();
  }

  template<_INTERFACE container_type, _INTERFACE container_type2>
  void sscan(std::istream& is, container_type& data, container_type2& format)
  {

    typedef _TYPENAME container_type::value_type value_type;
    typedef numeric_container_parser_event2<container_type, container_type2> event_type;

    simple_parser<delimiter_event<numeric_parser<value_type, event_type> > > parser;

    parser.set_container(data, format);

    std::istream::char_type c;
    while (true)
    {
      c = is.get();
      if(is.eof()) break;
      parser.next(c);
    }
    parser.finalize();
  }

  template<_INTERFACE char_type, _INTERFACE container_type>
  void sscan_matrix(char_type* input, container_type& data)
  {
    typedef _TYPENAME container_type::value_type container_type1;
    typedef _TYPENAME container_type1::value_type value_type;

    std::vector<std::vector<value_type> > temp;

    const char* p = input;
    std::string filename, num;
    std::ifstream file;
    while (1)
    {
      if(*p == '#')
      {
        if (!file.is_open())
        {
          file.open(filename.c_str());
          if (!file.is_open())
          {
            std::string err = "Can't open file - "; err += filename;
            throw err;
          }
          temp.clear();
          sscan_matrix(file, temp);
          if (temp.empty())
          {
            std::string err = "No data in file - " +  filename;
            throw err;
          }
          filename.clear();
        }
        while (1)
        {
          p ++;
          if (*p == ':' || *p == '\0')
          {
            if (num == "*")
            {
              unsigned size = temp[0].size();
              for (unsigned i = 1; i < temp.size(); i ++)
              {
                if (temp[i].size() != size)
                {
                  std::string err = "#* doesn't work for non-regular matrix";
                  throw err;
                }
              }
              for (unsigned col = 0; col < size; col ++)
              {
                data.resize(data.size()+1);
                for (unsigned i = 0; i < temp.size(); i ++)
                {
                  data.back().push_back(temp[i][col]);
                }
              }
            }
            else
            {
              int col = ::atoi(num.c_str())-1;
              if (col < 0)
              {
                std::string err = "Wrong format with - #" + num;
                throw err;
              }
              data.resize(data.size()+1);
              for (unsigned i = 0; i < temp.size(); i ++)
              {
                if (col >= int(temp[i].size()))
                {
                  char s[256];


                  //sprintf(s, "%d", i+1);
                  std::string err = "Column# " + num + " did't exist in line# " + s;
                  throw err;
                }
                data.back().push_back(temp[i][col]);
              }
            }
            num.clear();
            if (*p == '\0') return;
            p ++;
            break;
          }
          num += *p;
        }
      }
      else if (*p == ':' || *p == '\0')
      {
        file.open(filename.c_str());
        if (!file.is_open())
        {
          std::string err = "Can't open file - "; err += filename;
          throw err;
        }
        temp.clear();
        sscan_matrix(file, temp);
        if (temp.empty())
        {
          std::string err = "No data in file - " +  filename;
          throw err;
        }
        filename.clear();
        unsigned size = temp[0].size();
        for (unsigned i = 1; i < temp.size(); i ++)
        {
          if (temp[i].size() != size)
          {
            std::string err = "#* doesn't work for non-regular matrix";
            throw err;
          }
        }
        for (unsigned col = 0; col < size; col ++)
        {
          data.resize(data.size()+1);
          for (unsigned i = 0; i < temp.size(); i ++)
          {
            data.back().push_back(temp[i][col]);
          }
        }
        if (*p == '\0') return;
        p ++;
      }
      else
      {
        if (file.is_open())
        {
          file.close();
          file.clear();
        }
        filename += *p;
        p ++;
      }
    }

  }



}
#endif
