
//
// This file is part of the course materials for AMATH483/583 at the University of Washington,
// Spring 2020
//
// Licensed under Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License
// https://creativecommons.org/licenses/by-nc-sa/4.0/
//
// Author: Andrew Lumsdaine
//

#ifndef AMATH_583_UTIL_HPP
#define AMATH_583_UTIL_HPP


template<typename T>
struct is_sparse_matrix
{
private:
  typedef std::true_type yes;
  typedef std::false_type no;
 
  template<typename U> static auto test(int) 
    -> decltype(std::declval<U>().num_nonzeros() == 1, yes());
 
  template<typename> static no test(...);
 
public:
 
  static constexpr bool value = std::is_same<decltype(test<T>(0)),yes>::value;
};


template<typename T>
struct is_dense_matrix
{
private:
  typedef std::true_type yes;
  typedef std::false_type no;
 
  template<typename U> static auto test(int) 
    -> decltype(std::declval<U>()(0,0) == 1, yes());
 
  template<typename> static no test(...);
 
public:
 
  static constexpr bool value = std::is_same<decltype(test<T>(0)),yes>::value;
};


template<typename T>
struct is_dense_vector
{
private:
  typedef std::true_type yes;
  typedef std::false_type no;
 
  template<typename U> static auto test(int)
    -> decltype(std::declval<U>()(0) == 1, yes());
 
  template<typename> static no test(...);
 
public:
 
  static constexpr bool value = std::is_same<decltype(test<T>(0)),yes>::value;
};

#endif // AMATH_583_UTIL_HPP
