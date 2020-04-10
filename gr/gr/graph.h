#ifndef _PTL_ALGORITHM_GRAPH_H
#define _PTL_ALGORITHM_GRAPH_H

#include <list>
#include <vector>
#include <string>
#include "mac.h"
#include "io.h"

#define BEGIN_SPECIALIZE_WEIGHT_NODE(TYPE, BASE_NODE_TYPE, BASE_EDGE_TYPE, CONTAINER_TYPE, ADJACENT_TYPE) \
template <class T> struct TYPE;\
template <class T> struct TYPE \
_EXTENDS BASE_NODE_TYPE<CONTAINER_TYPE<BASE_EDGE_TYPE<TYPE<T>,T> >, ADJACENT_TYPE> \
{ typedef BASE_NODE_TYPE<CONTAINER_TYPE<BASE_EDGE_TYPE<TYPE<T>,T> >, ADJACENT_TYPE> parents_type;

#define BEGIN_WEIGHT_NODE(TYPE, CONTAINTER_TYPE, ADJACENT_TYPE) \
BEGIN_SPECIALIZE_WEIGHT_NODE(TYPE,ptl::node_base,ptl::edge_base,CONTAINTER_TYPE, ADJACENT_TYPE)

#define BEGIN_VECTOR_WEIGHT_NODE(TYPE, ADJACENT_TYPE) \
BEGIN_WEIGHT_NODE(TYPE, std::vector, ADJACENT_TYPE)

#define  BEGIN_SPECIALIZE_NODE(TYPE, BASE_TYPE, CONTAINER_TYPE, ADJACENT_TYPE) \
struct TYPE;\
struct TYPE _EXTENDS BASE_TYPE<CONTAINER_TYPE<TYPE*>, ADJACENT_TYPE>  \
{ typedef BASE_TYPE<CONTAINER_TYPE<TYPE*>, ADJACENT_TYPE> parents_type;

#define  BEGIN_NODE(TYPE, CONTAINER_TYPE, ADJACENT_TYPE) \
BEGIN_SPECIALIZE_NODE(TYPE, ptl::node_base, CONTAINER_TYPE, ADJACENT_TYPE)

#define  BEGIN_VECTOR_NODE(TYPE, ADJACENT_TYPE) \
BEGIN_NODE(TYPE, std::vector, ADJACENT_TYPE)

//
#define BEGIN_SPECIALIZE_WEIGHT_NODE(TYPE, BASE_NODE_TYPE, BASE_EDGE_TYPE, CONTAINER_TYPE, ADJACENT_TYPE) \
template <class T> struct TYPE;\
template <class T> struct TYPE \
_EXTENDS BASE_NODE_TYPE<CONTAINER_TYPE<BASE_EDGE_TYPE<TYPE<T>,T> >, ADJACENT_TYPE> \
{ typedef BASE_NODE_TYPE<CONTAINER_TYPE<BASE_EDGE_TYPE<TYPE<T>,T> >, ADJACENT_TYPE> parents_type;

#define BEGIN_WEIGHT_NODE(TYPE, CONTAINTER_TYPE, ADJACENT_TYPE) \
BEGIN_SPECIALIZE_WEIGHT_NODE(TYPE,ptl::node_base,ptl::edge_base,CONTAINTER_TYPE, ADJACENT_TYPE)

#define BEGIN_VECTOR_WEIGHT_NODE(TYPE, ADJACENT_TYPE) \
BEGIN_WEIGHT_NODE(TYPE, std::vector, ADJACENT_TYPE)

//
#define  BEGIN_SPECIALIZE_NODE2(TYPE, BASE_TYPE, CONTAINER_TYPE, ADJACENT_TYPE) \
struct TYPE _EXTENDS BASE_TYPE<CONTAINER_TYPE<TYPE*>, ADJACENT_TYPE>  \
{ typedef BASE_TYPE<CONTAINER_TYPE<TYPE*>, ADJACENT_TYPE> parents_type;

#define  BEGIN_NODE2(TYPE, CONTAINER_TYPE, ADJACENT_TYPE) \
BEGIN_SPECIALIZE_NODE2(TYPE, ptl::node_base, CONTAINER_TYPE, ADJACENT_TYPE)

#define  BEGIN_VECTOR_NODE2(TYPE, ADJACENT_TYPE) \
BEGIN_NODE2(TYPE, std::vector, ADJACENT_TYPE)

//
#define BEGIN_SPECIALIZE_WEIGHT_NODE2(TYPE, BASE_NODE_TYPE, BASE_EDGE_TYPE, CONTAINER_TYPE, ADJACENT_TYPE) \
template <class T> struct TYPE;\
template <class T> struct TYPE \
_EXTENDS BASE_NODE_TYPE<CONTAINER_TYPE<BASE_EDGE_TYPE<TYPE<T>,T> >, ADJACENT_TYPE> \
{ typedef BASE_NODE_TYPE<CONTAINER_TYPE<BASE_EDGE_TYPE<TYPE<T>,T> >, ADJACENT_TYPE> parents_type;

#define BEGIN_WEIGHT_NODE2(TYPE, CONTAINTER_TYPE, ADJACENT_TYPE) \
BEGIN_SPECIALIZE_WEIGHT_NODE2(TYPE,ptl::node_base,ptl::edge_base,CONTAINTER_TYPE, ADJACENT_TYPE)

#define BEGIN_VECTOR_WEIGHT_NODE2(TYPE, ADJACENT_TYPE) \
BEGIN_WEIGHT_NODE2(TYPE, std::vector, ADJACENT_TYPE)

//
#define END_SPECLAILIZE_NODE };
#define END_NODE };

namespace ptl {

  typedef int adjacent_type;

  struct adjacent
  {
    static const adjacent_type nondirectional   = 0x00;
    static const adjacent_type inwards          = 0x01;
    static const adjacent_type outwards         = 0x02;
    static const adjacent_type bidirectional    = inwards|outwards;
  };

  template <class T, class weight_interface>
  class edge_base _EXTENDS weight_interface
  {
    public:
      typedef T node_type;

      typedef T& reference;
      typedef const T& const_reference;

      typedef T* pointer;
      typedef const T* const_pointer;

      typedef weight_interface weight_type;

      inline edge_base() : weight_type() {}

      inline edge_base(T* x) : weight_type() { __pt = x; }

      template <class T2>
      inline edge_base(T* x, const T2& w) : weight_type(w) { __pt = x; }

      inline pointer operator-> () { return __pt; }
      inline const_pointer operator->() const { return __pt; }

      inline reference operator*() { return *__pt; }
      inline const_reference operator*() const { return *__pt; }

      inline bool operator == (const void* p) const
      {
        return __pt == p;
      }

      inline bool operator < (const void* p) const
      {
        return __pt < p;
      }

      inline bool operator > (const void* p) const
      {
        return __pt > p;
      }

      inline bool operator <= (const void* p) const
      {
        return __pt <= p;
      }

      inline bool operator >= (const void* p) const
      {
        return __pt >= p;
      }

    private:
      T* __pt;
  };

  template <_INTERFACE container_interface, adjacent_type type = adjacent::outwards>
  class node_base
  {
    inline node_base() { }
  };

  template <_INTERFACE container_interface>
  class node_base<container_interface, adjacent::nondirectional> _EXTENDS container_interface
  {
    public:

      typedef container_interface                         parents_type;
      typedef parents_type                                inwards;
      typedef parents_type                                outwards;
      typedef _TYPENAME parents_type::value_type          edge_type;
      typedef _TYPENAME outwards::value_type              outwards_edge_type;
      typedef _TYPENAME inwards::value_type               inwards_edge_type;

      typedef _TYPENAME parents_type::size_type           size_type;
      typedef _TYPENAME parents_type::iterator            iterator;

      //
      // Degree
      //
      inline const size_type degree() const           { return self.size(); }
      inline const size_type outwards_degree() const  { return self.size(); }
      inline const size_type inwards_degree()  const  { return self.size(); }

      //
      // Add
      //
      template <class T>
      inline void add(T* n)
      {
        this->push_back(n);
        n->push_back(static_cast<T*>(this));
      }
      template <class T>
      inline void add_outwards(T* n) { add(n); }
      template <class T>
      inline void add_inwards(T* n)  { add(n); }

      template <class T1, class T2>
      inline void add(T1* n, const T2& edge_property)
      {
        this->push_back(edge_type(n,edge_property));
        n->push_back(edge_type(static_cast<T1*>(this), edge_property));
      }

      template <class T1, class T2>
      inline void add_outwards(T1* n, const T2& edge_property) { add(n, edge_property); }
      template <class T1, class T2>
      inline void add_inwards(T1* n, const T2& edge_property) { add(n, edge_property); }

      //
      // Remove
      //
      inline void remove(iterator position)
      {
        *position = self.back();
        self.pop_back();
      }
      inline void remove_inwards(_TYPENAME inwards::iterator position)    { remove(position); }
      inline void remove_outwards(_TYPENAME outwards::iterator position)  { remove(position); }

      //
      // Type
      //
      static inline const adjacent_type type() { return adjacent::nondirectional; }
  };

  template <_INTERFACE container_interface>
  class node_base<container_interface, adjacent::inwards> _EXTENDS container_interface
  {
    public:

      typedef container_interface                         parents_type;
      typedef container_interface                         inwards;

      typedef _TYPENAME parents_type::value_type          edge_type;
      typedef _TYPENAME inwards::value_type               inwards_edge_type;

      typedef _TYPENAME parents_type::size_type           size_type;

      inline const size_type inwards_degree() const { return inwards::size();}

      template <class T>
      inline void add(T* n)
      {
        add_inwards(n);
      }

      template <class T>
      inline void add_outwards(T* n)
      {
        n->inwards::push_back(static_cast<T*>(this));
      }
      template <class T>
      inline void add_inwards(T* n)
      {
        this->inwards::push_back(n);
      }

      template <class T1, class T2>
      inline void add(T1* n, const T2& edge_property)
      {
        add_inwards(n, edge_property);
      }

      template <class T1, class T2>
      inline void add_inwards(T1* n, const T2& edge_property)
      {
        this->inwards::push_back(inwards_edge_type(n,edge_property));
      }

      template <class T1, class T2>
      inline void add_outwards(T1* n, const T2& edge_property)
      {
        n->inwards::push_back(inwards_edge_type(static_cast<T1*>(this),edge_property));
      }

      inline void remove_inwards(_TYPENAME inwards::iterator position)
      {
        *position = inwards::back();
        inwards::pop_back();
      }

      static inline const adjacent_type type() { return adjacent::inwards; }
  };

  template <_INTERFACE container_interface>
  class node_base<container_interface, adjacent::outwards> _EXTENDS container_interface
  {
    public:

      typedef container_interface                         parents_type;
      typedef container_interface                         outwards;

      typedef _TYPENAME parents_type::value_type          edge_type;
      typedef _TYPENAME outwards::value_type              outwards_edge_type;

      typedef _TYPENAME parents_type::size_type           size_type;

      inline const size_type outwards_degree() const { return outwards::size();}

      template <class T>
      inline void add(T* n)
      {
        add_outwards(n);
      }

      template <class T>
      inline void add_outwards(T* n)
      {
        this->outwards::push_back(n);
      }

      template <class T>
      inline void add_inwards(T* n)
      {
        n->outwards::push_back(static_cast<T*>(this));
      }

      template <class T1, class T2>
      inline void add(T1* n, const T2& edge_property)
      {
        add_outwards(n, edge_property);
      }

      template <class T1, class T2>
      inline void add_outwards(T1* n, const T2& edge_property)
      {
        this->outwards::push_back(outwards_edge_type(n,edge_property));
      }

      template <class T1, class T2>
      inline void add_inwards(T1* n, const T2& edge_property)
      {
        n->outwards::push_back(outwards_edge_type(this,edge_property));
      }

      inline void remove_outwards(_TYPENAME outwards::iterator position)
      {
        *position = outwards::back();
        outwards::pop_back();
      }

      static inline const adjacent_type type() { return adjacent::outwards; }
  };

  template <_INTERFACE outwards_interface, _INTERFACE inwards_interface>
  class binode_base : public outwards_interface, public inwards_interface
  {
    public:

      typedef outwards_interface                          outwards;
      typedef inwards_interface                           inwards;
      typedef _TYPENAME outwards::value_type              outwards_edge_type;
      typedef _TYPENAME inwards::value_type               inwards_edge_type;

      typedef _TYPENAME outwards::size_type               size_type;

      template <class T>
      inline void add_outwards(T* n)
      {
        this->outwards::push_back(n);
        n->inwards::push_back(static_cast<T*>(this));
      }

      template <class T>
      inline void add_inwards(T* n)
      {
        n->outwards::push_back(static_cast<T*>(this));
        this->inwards::push_back(n);
      }

      template <class T1, class T2>
      inline void add_outwards(T1* n, const T2& edge_property)
      {
        this->outwards::push_back(outwards_edge_type(n,edge_property));
        n->inwards::push_back(inwards_edge_type(static_cast<T1*>(this), edge_property));
      }

      template <class T1, class T2>
      inline void add_inwards(T1* n, const T2& edge_property)
      {
        n->outwards::push_back(outwards_edge_type(static_cast<T1*>(this),edge_property));
        this->inwards::push_back(inwards_edge_type(n,edge_property));
      }

      static inline const adjacent_type type() { return adjacent::bidirectional; }
  };

  template <_INTERFACE container_interface>
  class node_base<container_interface, adjacent::bidirectional>
    _EXTENDS binode_base<node_base<container_interface, adjacent::outwards>,
                          node_base<container_interface, adjacent::inwards> >
  {
  };

  template <class T>
  struct search_out_node _EXTENDS T
  {
    typedef T parents_type;
    typedef _TYPENAME parents_type::outwards outwards;

    typedef _TYPENAME outwards::iterator iterator;
    typedef _TYPENAME outwards::const_iterator const_iterator;
    typedef _TYPENAME outwards::reverse_iterator reverse_iterator;
    typedef _TYPENAME outwards::const_reverse_iterator const_reverse_iterator;

    iterator begin () { return this->outwards::begin(); }
    const_iterator begin () const { return this->outwards::begin(); }
    iterator end () { return this->outwards::end(); }
    const_iterator end () const { return this->outwards::end(); }
    reverse_iterator rbegin () { return this->outwards::rbegin(); }
    const_reverse_iterator rbegin () const { return this->outwards::rbegin(); }
    reverse_iterator rend () { return this->outwards::rend(); }
    const_reverse_iterator rend () const { return this->outwards::rend(); }
  };


  template <class T>
  struct search_in_node _EXTENDS T
  {
    typedef T parents_type;
    typedef _TYPENAME parents_type::inwards inwards;

    typedef _TYPENAME inwards::iterator iterator;
    typedef _TYPENAME inwards::const_iterator const_iterator;
    typedef _TYPENAME inwards::reverse_iterator reverse_iterator;
    typedef _TYPENAME inwards::const_reverse_iterator const_reverse_iterator;

    iterator begin () { return this->inwards::begin(); }
    const_iterator begin () const { return this->inwards::begin(); }
    iterator end () { return this->inwards::end(); }
    const_iterator end () const { return this->inwards::end(); }
    reverse_iterator rbegin () { return this->inwards::rbegin(); }
    const_reverse_iterator rbegin () const { return this->inwards::rbegin(); }
    reverse_iterator rend () { return this->inwards::rend(); }
    const_reverse_iterator rend () const { return this->inwards::rend(); }
  };


  template <class node_type>
  inline search_out_node<node_type>* search_out_cast(node_type* p)
  {
    return _REINTERPRET_CAST(search_out_node<node_type>*, p);
  }

  template <class node_type>
  inline search_in_node<node_type>* search_in_cast(node_type* p)
  {
    return _REINTERPRET_CAST(search_in_node<node_type>*, p);
  }


  template <class new_node_type>
  inline new_node_type* search_cast(_TYPENAME new_node_type::parents_type* p)
  {
    return _REINTERPRET_CAST(new_node_type*, p);
  }

  template <_INTERFACE container_interface,
            _INTERFACE node_interface  = _TYPENAME container_interface::value_type>
  class link_graph_base _EXTENDS container_interface
  {
    public:
      typedef container_interface                       parents;
      typedef node_interface                            node_type;
      typedef _TYPENAME node_type::size_type            size_type;
  };

  template<_INTERFACE task_interface>
  class breadth_first_search _EXTENDS task_interface
  {
    public:

      typedef task_interface                          task_type;

      typedef _TYPENAME task_type::container_type     container_type;
      typedef _TYPENAME task_type::size_type          size_type;

      template <class graph_type, class node_type>
      void search(graph_type& graph, node_type* start);

      template <class graph_type, class node_type>
      inline void search_out(graph_type& graph, node_type* start)
      {
        search(graph, search_out_cast(start));
      }

      template <class graph_type, class node_type>
      inline void search_in(graph_type& graph, node_type* start)
      {
        search(graph, search_in_cast(start));
      }
      
      template <class graph_type, class node_type, class task_type2>
      void search(graph_type& graph, node_type* start, task_type2 task);

      template <class graph_type, class node_type, class task_type2>
      inline void search_out(graph_type& graph, node_type* start, task_type2 task)
      {
        search(graph, search_out_cast(start), task);
      }

      template <class graph_type, class node_type, class task_type2>
      inline void search_in(graph_type& graph, node_type* start, task_type2 task)
      {
        search(graph, search_in_cast(start), task);
      }
  };

  template <_INTERFACE task_interface>
  template <class graph_type, class node_type>
  void breadth_first_search<task_interface>::
  search(graph_type& graph, node_type* start)
  {

    register size_type distance = 1;
    register node_type *current = start;
    register container_type* last_layer;

    entry(last_layer, current);

    do
    {
      for (register _TYPENAME container_type::iterator i = last_layer->begin();
            i != last_layer->end(); i ++)
      {
        register node_type* pnode = _REINTERPRET_CAST(node_type*, *i);

        for (register _TYPENAME node_type::iterator j = pnode->begin();
              j != pnode->end(); j ++)
        {
          current = _REINTERPRET_CAST(node_type*, &**j);

          if (current->distance() >= distance+1)
          {
            current->distance() = distance;
            if (update(current)) return;
          }
        }
      }

    } while (next_layer(last_layer, distance));
  }

  template <_INTERFACE task_interface>
  template <class graph_type, class node_type, class task_type2>
  void breadth_first_search<task_interface>::
  search(graph_type& graph, node_type* start, task_type2 task)
  {

    register size_type distance = 1;
    register node_type *current = start;
    register container_type* last_layer;

    entry(last_layer, current);
    task(current, start);

    do
    {
      for (register _TYPENAME container_type::iterator i = last_layer->begin();
            i != last_layer->end(); i ++)
      {
        register node_type* pnode = _REINTERPRET_CAST(node_type*, *i);

        for (register _TYPENAME node_type::iterator j = pnode->begin();
              j != pnode->end(); j ++)
        {
          current = _REINTERPRET_CAST(node_type*, &**j);

          if (current->distance() >= distance+1)
          {
            current->distance() = distance;
            task(current, start);
            if (update(current)) return;
          }
        }
      }

    } while (next_layer(last_layer, distance));
  }

  template <_INTERFACE task_interface>
  class depth_first_search _EXTENDS task_interface
  {

    public:

      typedef task_interface                          task_type;

      template <class graph_type, class node_type>
      void search(graph_type& graph, node_type* start);

      template <class graph_type, class node_type>
      inline void search_out(graph_type& graph, node_type* start)
      {
        search(graph, search_out_cast(start));
      }

      template <class graph_type, class node_type>
      inline void search_in(graph_type& graph, node_type* start)
      {
        search(graph, search_in_cast(start));
      }

    private:

      template <class node_type, class iterator_type>
      struct search_stack
      {
        node_type*                      node;
        iterator_type                   iterator;
      };
  };

  template <_INTERFACE task_interface>
  template <class graph_type, class node_type>
  void depth_first_search<task_interface>::
  search(graph_type& graph, node_type* start)
  {

    typedef _TYPENAME node_type::size_type size_type;
    typedef _TYPENAME node_type::iterator  iterator;
    typedef search_stack<node_type, iterator> stack_type;

    register node_type *current = start;
    register iterator current_iterator = current->begin();

    register stack_type *stack_top = new stack_type[graph.size()];
    register stack_type *stack_pointer = stack_top;

    self.entry(current);

    while (true)
    {
      if (current_iterator == current->end()
          || pop_condition(current, current_iterator))
      {

        if (stack_pointer == stack_top) break;

        pop(current, current_iterator);

        -- stack_pointer;
        current           = stack_pointer->node;
        current_iterator  = stack_pointer->iterator;

      }
      else
      {

        register node_type* next = _REINTERPRET_CAST(node_type*, &**current_iterator);

        if (push_condition(current, next, current_iterator))
        {
          push(current, next, current_iterator);

          stack_pointer->node       = current;
          stack_pointer->iterator   = current_iterator;
          ++ stack_pointer->iterator;
          ++ stack_pointer;

          current = next;
          current_iterator = current->begin();
        }
        else
        {
          ++ current_iterator;
        }
      }
    }

    self.exit(current);

    delete [] stack_top;
  }

  struct search_task_base
  {
    template <class graph_type>
    static inline void initialize(graph_type& g){ }
  };

  template <class container_interface>
  struct breadth_first_search_task_base _EXTENDS search_task_base
  {

    typedef container_interface                       container_type;
    typedef search_task_base                          parents_type;
    _TYPE_INHERIT(container_type, size_type)

    template <class node_type>
    inline void entry(container_type*& last_layer, node_type* current){}

    template <class node_type>
    inline bool update(node_type* p){ return false; }

    inline bool next_layer(container_type*& last_layer, size_type& distance)
    { return false; }

  };

  template <class container_interface>
  class bf_distance_search_task
        _EXTENDS breadth_first_search_task_base<container_interface>
  {

    public:

      typedef container_interface                                 container_type;
      typedef breadth_first_search_task_base<container_interface> parents_type;
      _TYPE_INHERIT(container_type, size_type)

      template <class graph_type>
      static void initialize(graph_type& graph);

      template <class node_type>
      inline void entry(container_type*& last_layer, node_type* current)
      {
        current_layer = &t1, last_layer = &t2;
        last_layer->clear(), current_layer->clear();
        last_layer->push_back(current);
        current->distance() = 0;
      }

      template <class node_type>
      inline bool update(node_type* p)
      {
        current_layer->push_back(p);
        return false;
      }

      inline bool next_layer(container_type*& last_layer, size_type& distance)
      {
        register container_type* temp = last_layer;
        last_layer = current_layer, current_layer = temp;
        current_layer->clear();
        distance ++;
        return !last_layer->empty();
      }

    protected:

      container_type t1, t2, *current_layer;

  };

  template <class container_interface>
  template <class graph_type>
  void bf_distance_search_task<container_interface>::
  initialize(graph_type& graph)
  {
    for (typename graph_type::iterator p = graph.begin(); p != graph.end(); p ++)
    {
      //p->second.distance() = graph.size();
      p->distance() = graph.size();
    }
  }

  template <class container_interface>
  class bf_cut_distance_search_task
        _EXTENDS bf_distance_search_task<container_interface>
  {
    public:

      typedef container_interface                       container_type;
      typedef bf_distance_search_task<container_type>   parents_type;
      _TYPE_INHERIT(container_type, size_type)

      template <class graph_type>
      void initialize(graph_type& graph) const;

      inline bool next_layer(container_type*& last_layer, size_type& distance)
      {
        return parents_type::next_layer(last_layer, distance) && distance < self.cut();
      }

      _DEFAULT_IMPLEMENT(size_type, cut)
  };

  template <class container_interface>
  template <class graph_type>
  void bf_cut_distance_search_task<container_interface>::
  initialize(graph_type& graph) const
  {
    for (typename graph_type::iterator p = graph.begin(); p != graph.end(); p ++)
    {
      p->distance() = self.cut();
    }
  }

  class depth_first_search_task_base _EXTENDS search_task_base
  {

    public:

      template <class graph_type>
      void initialize(graph_type& graph) const;

    protected:

      template <class node_type>
      static inline void entry(node_type* current)
      {
        current->used() = true;
      }

      template <class node_type>
      static inline void exit(node_type* current)
      {
        current->used() = false;
      }

      template <class node_type, class iterator_type>
      static inline const bool
      push_condition(node_type* current, node_type* next, iterator_type)
      {
        return !next->used();
      }

      template <class node_type, class iterator_type>
      static inline void push(node_type* current, node_type* next, iterator_type)
      {
        next->used() = true;
      }

      template <class node_type, class iterator_type>
      static inline const bool pop_condition(node_type* current, iterator_type)
      {
        return false;
      }

      template <class node_type, class iterator_type>
      static inline void pop(node_type* current, iterator_type)
      {
        current->used() = false;
      }

  };

  template <class graph_type>
  void depth_first_search_task_base::initialize(graph_type& graph) const
  {
    for (typename graph_type::iterator p = graph.begin(); p != graph.end(); p ++)
    {
      p->used() = false;
    }
  }

  class df_connectivity_search_task _EXTENDS depth_first_search_task_base
  {

    public:

      typedef depth_first_search_task_base parents_type;

      template <class graph_type>
      void initialize(graph_type& graph);

    protected:

      template <class node_type>
      inline void entry(node_type* current) const
      {
        current->type() = self.type_num();
      }

      template <class node_type>
      inline void exit(node_type* current)
      {
        self.type_num() ++;
      }

      template <class node_type, class iterator_type>
      inline const bool push_condition(node_type* current,node_type* next, iterator_type) const
      {
        return next->type() != self.type_num();
      }

      template <class node_type, class iterator_type>
      inline void push(node_type* current, node_type* next, iterator_type) const
      {
        next->type() = self.type_num();
      }

      template <class node_type, class iterator_type>
      static inline void pop(node_type* current, iterator_type)
      {
      }

      _DEFAULT_IMPLEMENT(size_t, type_num)

  };

  template <class graph_type>
  void df_connectivity_search_task::initialize(graph_type& graph)
  {
    self.type_num() = 0;
    unsigned i = 0;
    for (i = 0; i != graph.size(); i ++)
    {
      graph[i].type() = graph.size();
    }
    /*
    return;
      _TYPENAME graph_type::iterator p = graph.begin(), p1 = graph.end();
      cout << "hehe" << graph.size() << endl;
    for (; p != graph.end(); ++ p)
    {
      cout << i ++ << endl;
      p->type() = graph.size();
    }
    */
  }

  template <_INTERFACE node_interface>
  class common_link_graph _EXTENDS link_graph_base<std::vector<node_interface> >
  {
    
  public:
    
    typedef node_interface                          node_type;
    typedef _TYPENAME node_type::size_type          size_type;
    typedef link_graph_base<std::vector<node_type> > parents_type;
    typedef node_type*                      iterator;
    typedef const node_type*               const_iterator;
    
    inline const_iterator begin() const { return &*parents_type::begin(); }
    inline iterator begin() { return &*parents_type::begin(); }
    
    inline const_iterator end() const { return &*parents_type::end(); }
    inline iterator end() { return &*parents_type::end(); }
    
    inline size_type index_of(const node_type* node) const
    {
      return size_type(node-begin());
    }
  };
  
  template <_INTERFACE node_interface>
  class common_link_graph2 _EXTENDS link_graph_base<std::vector<node_interface*>, node_interface>
  {
    
  public:
    
    typedef node_interface                          node_type;
    typedef _TYPENAME node_type::size_type          size_type;
    typedef link_graph_base<std::vector<node_type*>, node_interface> parents_type;
    typedef _TYPENAME parents_type::iterator iterator;
    
    inline size_type index_of(const node_type* node) const
    {
      return node->index();
    }
  };
  
  template <_INTERFACE node_interface>
  class common_list_graph _EXTENDS link_graph_base<std::list<node_interface> >
  {
    
  public:
    
    typedef node_interface                          node_type;
    typedef _TYPENAME node_type::size_type          size_type;
    
    template <class T>
    inline size_type index_of(T node) const { return node->index(); }
  };
  
  template <class graph_type>
  void load_graph(std::istream& is, graph_type& g)
  {
    typedef _TYPENAME graph_type::node_type::size_type size_type;
    
    size_type i;
    std::vector<unsigned> data;
    
    sscan(is, data);
    
    g.clear();
    if (data.empty()) return;
    
    size_type size = *std::max_element(data.begin(), data.end())+1;
    
    g.reserve(size);
    g.resize(size);
    
    for (i = 0; i < data.size()/2; i ++)
    {
      g[data[2*i]].add_outwards(&g[data[2*i+1]]);
    }
  }
  
  template <class graph_type>
  void load_weight_graph(std::istream& is, graph_type& g)
  {
    typedef _TYPENAME graph_type::node_type::size_type size_type;
    
    size_type n, i;
    std::vector<unsigned> data;
    
    sscan(is, data);
    
    g.clear();
    if (data.empty()) return;
    
    size_type size = *std::max_element(data.begin(), data.end())+1;
    
    g.reserve(size);
    g.resize(size);
    
    for (i = 0; i < data.size()/3; i ++)
    {
      g[data[3*i]].add_outwards(&g[data[3*i+1]], data[3*i+2]);
    }
  }
  
  template <_INTERFACE container_type>
  inline std::istream& operator >> (std::istream& is, link_graph_base<container_type>& g)
  {
    load_graph(is, g);
    return is;
  }
  
  template <_INTERFACE node_type>
  std::ostream& operator << (std::ostream& os, const common_link_graph<node_type>& g)
  {
    typedef typename common_link_graph<node_type>::const_iterator iterator;
    typedef typename node_type::outwards outwards;
    typedef typename outwards::const_iterator n_iterator;
    for (iterator i = g.begin(); i != g.end(); i ++)
    {
      for (n_iterator j = i->outwards::begin(); j != i->outwards::end(); j ++)
      {
        os << g.index_of(i) << '\t' << g.index_of(&**j) << '\n';
      }
    }
    
    return os;
  }
  
  template<class G1, class G2>
  void copy_bigraph(const G1& g1, G2& g2) //copy g1 to g2 without directions
  {
    g2.clear();
    g2.resize(g1.size());
    
    typedef typename G1::value_type node_type1;
    typedef typename G2::value_type node_type2;
    
    
    for (int i = 0; i < g1.size(); i ++)
    {
      const node_type1 *p = &g1[i];
      node_type2 *p1 = &g2[i];
      
      for (typename node_type1::outwards::const_iterator j = p->node_type1::outwards::begin();
           j != p->node_type1::outwards::end(); j++)
      {
        node_type2* p2 = &g2[g1.index_of(&(**j))];
        if (std::find(p1->node_type2::outwards::begin(),
                      p1->node_type2::outwards::end(), p2) == p1->node_type2::outwards::end())
        {
          p1->add_outwards(p2);
          p2->add_outwards(p1);
        }
      }
    }
  }
  
  template<_TYPENAME graph_type, _TYPENAME node_type>
  inline void search_distance(graph_type& graph, node_type* start)
  {
    breadth_first_search<bf_distance_search_task<std::vector<void*> > > dsearch;
    
    dsearch.initialize(graph);
    dsearch.search(graph, start);
  }
  
  template<_TYPENAME graph_type, _TYPENAME node_type>
  inline void search_distance(graph_type& graph, node_type* start,
                              const _TYPENAME graph_type::size_type cut_distance)
  {
    breadth_first_search<bf_cut_distance_search_task<std::vector<void*> > > dsearch;
    
    dsearch.cut() = cut_distance;
    dsearch.initialize(graph);
    dsearch.search(graph, start);
  }
  
  template<_TYPENAME graph_type, _TYPENAME node_type, _TYPENAME task_type>
  inline void search_distance_task(graph_type& graph, node_type* start, task_type task)
  {
    breadth_first_search<bf_distance_search_task<std::vector<void*> > > dsearch;
    
    dsearch.initialize(graph);
    dsearch.search(graph, start, task);
  }
  
  template<_TYPENAME graph_type, _TYPENAME node_type, _TYPENAME task_type>
  inline void search_distance_task(graph_type& graph, node_type* start,
                                   const _TYPENAME graph_type::size_type cut_distance,
                                   task_type task)
  {
    breadth_first_search<bf_cut_distance_search_task<std::vector<void*> > > dsearch;
    
    dsearch.cut() = cut_distance;
    dsearch.initialize(graph);
    dsearch.search(graph, start, task);
  }
  
  
  template<_TYPENAME graph_type, _TYPENAME task_type>
  _TYPENAME graph_type::size_type search_clusters(graph_type& graph,
                                                  task_type& task)
  {
    typedef _TYPENAME graph_type::size_type size_type;
    typedef _TYPENAME graph_type::node_type node_type;
    
    size_type i, size = graph.size();
    
    task.initialize(graph);
    for (i = 0; i < size; i ++)
    {
      node_type* p = &graph[i];
      if (p->type() == size) task.search(graph, p);
    }
    return task.type_num();
  }
  
  template<_TYPENAME graph_type>
  inline _TYPENAME graph_type::size_type search_clusters(graph_type& graph)
  {
    depth_first_search<df_connectivity_search_task> task;
    return search_clusters(graph, task);
  }
  
  BEGIN_VECTOR_NODE(nondi_node, adjacent::nondirectional)END_NODE
  BEGIN_VECTOR_NODE(inwards_node, adjacent::inwards)END_NODE
  BEGIN_VECTOR_NODE(outwards_node, adjacent::outwards)END_NODE
  BEGIN_VECTOR_NODE(bidi_node, adjacent::bidirectional)END_NODE
  
  BEGIN_VECTOR_WEIGHT_NODE(w_nondi_node, adjacent::nondirectional)END_NODE
  BEGIN_VECTOR_WEIGHT_NODE(w_inwards_node, adjacent::inwards)END_NODE
  BEGIN_VECTOR_WEIGHT_NODE(w_outwards_node, adjacent::outwards)END_NODE
  BEGIN_VECTOR_WEIGHT_NODE(w_bidi_node, adjacent::bidirectional)END_NODE
  
  
  class weakly_connected_component
  {
    BEGIN_VECTOR_NODE(node_type, adjacent::outwards)
    _DEFAULT_IMPLEMENT(size_type, type)
    END_NODE
    
    typedef common_link_graph<node_type> graph_type;
    
    graph_type g;
    std::vector<int> cluster_size;
  public:
    template<class T>
    weakly_connected_component(const T& __g)
    {
      copy_bigraph(__g, g);
      
      cluster_size.resize(search_clusters(g),0);
      for (int i = 0; i < g.size(); i ++)
      {
        cluster_size[g[i].type()] ++;
      }
    }
    double giant_cluster_fraction() const
    {
      return double(*max_element(cluster_size.begin(), cluster_size.end()))/g.size();
    }
    double average_cluster_sizes() const
    {
      if (cluster_size.size() <= 1) return 0;
      double S = 0, max_S = 0;
      for (int i = 0; i < cluster_size.size(); i ++)
      {
        S += cluster_size[i];
        if (cluster_size[i] > max_S) max_S = cluster_size[i];
      }
      return (S-max_S)/(cluster_size.size()-1);
    }
    
  };

}

#endif
