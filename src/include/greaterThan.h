// Template class to check if an array has a value greater than k
// we then count the number of elements
#ifndef greaterThan_h
#define greaterThan_h 1
#include <iostream>
#include <array>

// Template CLASS to return the count of elements 
// from the array which are greater than k 
template <typename T>
class greaterThan{
private:
  int l,r;
  int leftGreater;
  int size;
public:
  greaterThan(std::vector<T> vec,int n,T k);
  T countGreater();
};
template<typename T>
greaterThan<T>::greaterThan(std::vector<T> vec,int n,T k) { 
  size=n;
  l = 0; 
  r = n - 1; 
  
  // Stores the index of the left most element 
  // from the array which is greater than k 
  leftGreater = n; 
  
  // Finds number of elements greater than k 
  while (l <= r) { 
    int m = l + (r - l) / 2; 
    
    // If mid element is greater than 
    // k update leftGreater and r 
    if (vec[m] > k) { 
      leftGreater = m; 
      r = m - 1; 
    } 
    // If mid element is less than 
    // or equal to k update l 
    else
      l = m + 1; 
    //std::cout<<"checking how this works: "<<l<<" : "<<m<<" : "<<leftGreater<<std::endl;
  } 
  
  // Return the count of elements greater than k 
  countGreater();
} 
template<typename T>
T greaterThan<T>::countGreater(){
  return (size - leftGreater); 
}
#endif
