#ifndef _PTL_MAC_H
#define _PTL_MAC_H


#define _INTERFACE class
#define _EXTENDS  : public
#define _TYPENAME typename


#ifndef _REINTERPRET_CAST
#define _REINTERPRET_CAST(T, arg) reinterpret_cast<T> (arg)
#endif

#ifndef _STATIC_CAST
#define _STATIC_CAST(T, arg) static_cast<T> (arg)
#endif

#ifndef _ALIAS
#define _ALIAS(TYPE, NEWNAME, OLDNAME) \
public: TYPE& NEWNAME() { return OLDNAME(); } \
const TYPE& NEWNAME() const { return OLDNAME(); }
#endif

#ifndef _DEFAULT_IMPLEMENT
#define _DEFAULT_IMPLEMENT(TYPE, NAME) \
public: TYPE& NAME() { return self.__ptl_var_##NAME; } \
const TYPE& NAME() const { return self.__ptl_var_##NAME; } \
protected: TYPE __ptl_var_##NAME;
#endif

#ifndef _DEFAULT_CONST_IMPLEMENT
#define _DEFAULT_CONST_IMPLEMENT(TYPE, NAME) \
public: const TYPE& NAME() const { return self.__ptl_var_##NAME; } \
protected: TYPE& NAME() { return self.__ptl_var_##NAME; } \
private: TYPE __ptl_var_##NAME;
#endif

#ifndef _DEFAULT_ARRAY_IMPLEMENT
#define _DEFAULT_ARRAY_IMPLEMENT(TYPE, NAME, SIZE) \
public: TYPE& NAME(int i) { return self.__ptl_var_##NAME[i]; } \
const TYPE& NAME(int i) const { return self.__ptl_var_##NAME[i]; } \
private: TYPE __ptl_var_##NAME[SIZE];
#endif

#ifndef _TYPE_INHERIT
#define _TYPE_INHERIT(PARENTS, TYPE)\
typedef _TYPENAME PARENTS::TYPE TYPE;
#endif

#ifndef _ALIAS_TYPE_INHERIT
#define _ALIAS_TYPE_INHERIT(PARENTS, OLD_TYPE, NEW_TYPE)\
typedef _TYPENAME PARENTS::OLD_TYPE NEW_TYPE;
#endif

#define PTL ptl

#ifndef self
#define self (*this)
#endif

#ifndef method
#define method static inline
#endif


#endif
