#ifndef Application_Macros_H
#define Application_Macros_H

/**
Macro to help creating for loops which use const_iterators on a STL-like container.
*/
#define FOR_IT_CONST(type, it, iterable) for(type::const_iterator it = iterable.begin(); it != iterable.end(); ++it)

/**
Macro to help creating for loops which use iterators on a STL-like container.
*/
#define FOR_IT(type, it, iterable) for(type::iterator it = iterable.begin(); it != iterable.end(); ++it)

#endif