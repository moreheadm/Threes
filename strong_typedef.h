
#ifndef BOOST_STRONG_TYPEDEF_HPP
#define BOOST_STRONG_TYPEDEF_HPP

// MS compatible compilers support #pragma once
#if defined(_MSC_VER) && (_MSC_VER >= 1020)
# pragma once
#endif

/////////1/////////2/////////3/////////4/////////5/////////6/////////7/////////8
// strong_typedef.h:

// (C) Copyright 2002 Robert Ramey - http://www.rrsd.com.
// Use, modification and distribution is subject to the Boost Software
// License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

// macro used to implement a strong typedef.  strong typedef
// guarentees that two types are distinguised even though the
// share the same underlying implementation.  typedef does not create
// a new type. STRONG_TYPEDEF(T, D) creates a new type named D
// that operates as a type T.

#if !defined(__BORLANDC__) || __BORLANDC__ >= 0x590
    #define STRONG_TYPEDEF(T, D)                              \
        struct D                                                        \
    {                                                               \
                T t;                                                        \
                explicit D(const T t_) : t(t_) {};                          \
                D(){};                                                      \
                D(const D & t_) : t(t_.t){}                                 \
                D & operator=(const D & rhs) { t = rhs.t; return *this;}    \
                D & operator=(const T & rhs) { t = rhs; return *this;}      \
                operator const T & () const {return t; }                    \
                operator T & () { return t; }                               \
                bool operator==(const D & rhs) const { return t == rhs.t; } \
                bool operator<(const D & rhs) const { return t < rhs.t; }   \
            };
#else
    #define STRONG_TYPEDEF(T, D)                              \
        struct D                                                        \
    {                                                               \
                T t;                                                        \
                explicit D(const T t_) : t(t_) {};                          \
                D(){};                                                      \
                D(const D & t_) : t(t_.t){}                                 \
                D & operator=(const D & rhs) { t = rhs.t; return *this;}    \
                D & operator=(const T & rhs) { t = rhs; return *this;}      \
                /*operator const T & () const {return t; }*/                \
                operator T & () { return t; }                               \
                bool operator==(const D & rhs) const { return t == rhs.t; } \
                bool operator<(const D & rhs) const { return t < rhs.t; }   \
            };
#endif // !defined(__BORLANDC) || __BORLANDC__ >= 0x590

#endif // BOOST_STRONG_TYPEDEF_HPP

