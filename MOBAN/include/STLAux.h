#pragma once
#include <string>
#include <utility>
#include <algorithm>
#include <tuple>
#include <functional>
#include <memory>
#include <iostream>
#include <sstream>

/*
helper class to apply std algorithm for entire container sequence.
*/

typedef char char_t;

template<typename T>
class STLAux
{
public:
   STLAux(T& container) :mpContainer(&container) {}
   STLAux():mHolder(new T()){
      mpContainer = mHolder.get();
   }

   explicit STLAux(std::shared_ptr<T> container) {
      mHolder = container;
      mpContainer = mHolder.get();
   }



   template<typename TValue = typename T::value_type>
   inline bool contain(const TValue & item)const
   {
      return std::end(*mpContainer) != std::find(std::begin(*mpContainer), std::end(*mpContainer), item);
   }

   template<typename T2 >
   inline bool containAny(const T2& container)
   {
	   return std::any_of(std::begin(container), std::end(container), [this](const typename T2::value_type& x) {return this->contain(x); });
   }

   template<typename T2 >
   inline bool containAll(const T2& container)
   {
      return std::all_of(std::begin(container), std::end(container), [this](const typename T2::value_type& x) {return this->contain(x); });
   }

   template<typename TValue>
   inline typename T::iterator find(const TValue & item)
   {
      return std::find(std::begin(*mpContainer), std::end(*mpContainer), item);
   }

   template<class Fn>
   typename T::iterator find_if(Fn fn)
   {
       return std::find_if(std::begin(*mpContainer), std::end(*mpContainer), fn);
   }

   template<typename TValue>
   inline typename T::value_type* findV(const TValue & item)
   {
      auto iter = this->find(item);
      return iter == mpContainer->end() ? nullptr : &(*iter);
   }

   template<class Fn>
   typename T::value_type* findV_if(Fn fn)
   {
      auto iter = this->find_if(fn);
      return iter == mpContainer->end() ? nullptr : &(*iter);
   }

   template<class Fn>
   inline Fn for_each(Fn fn)
   {
      return std::for_each(std::begin(*mpContainer), std::end(*mpContainer), fn);
   }

   T* operator->()
   {
      return mpContainer;
   }

   T& operator *()
   {
      return *mpContainer;
   }

   T* mpContainer;
   std::shared_ptr<T> mHolder;
};

template <>
class STLAux<std::string>
{
public:
    STLAux(std::string& container) :mpContainer(&container) {}
   STLAux() :mHolder(new std::string()) {
      mpContainer = mHolder.get();
   }
    std::string& repalce(const char_t* search, const char_t* replace) {
        return this->repalce(std::string(search),std::string(replace));
    }

    std::string& repalce(const std::string& search,const std::string& replace) {
        size_t pos = 0U;
        while ((pos = mpContainer->find(search, pos)) != std::string::npos) {
            mpContainer->replace(pos, search.length(), replace);
            pos += replace.length();
        }

        return *mpContainer;
    }

   template<typename T>
   typename std::remove_reference<T>::type to()
   {
      std::istringstream ss(*mpContainer);
      typename std::remove_reference<T>::type  value;
      ss >> value;
      return value;
   }

   template<typename T>
   std::string& from(T value)
   {
      std::ostringstream ss;
      ss << value;
      *mpContainer = ss.str();
      return *mpContainer;
   }

    operator std::string&()
    {
        return *mpContainer;
    }

   std::vector<std::string> split(char_t delim) {
      std::stringstream ss(*mpContainer);
      std::string item;
      std::vector<std::string> elems;
      while ((bool)(std::getline(ss, item, delim))) {
         elems.push_back(std::move(item)); // if C++11 (based on comment from @mchiasson)
      }
      return elems;
   }

   bool startsWith(const std::string &prefix) 
   {
      if (mpContainer->length() < prefix.length()) { return false; }
      return (mpContainer->find(prefix) == 0);
   }

   bool endsWith(const std::string &suffix) 
   {
      if (mpContainer->length() < suffix.length()) { return false; }
      return (mpContainer->rfind(suffix) == (mpContainer->length() - suffix.length()));
   }

   /*
   void ltrim() {
      mpContainer->erase(mpContainer->begin(), std::find_if(std::begin(*mpContainer), std::end(*mpContainer), , std::not1(std::ptr_fun<int, int>(std::isspace))));
   }

   // trim from end
   void rtrim() {
      mpContainer->erase(std::find_if(std::rbegin(*mpContainer), std::rend(*mpContainer), std::not1(std::ptr_fun<int, int>(std::isspace))).base(), mpContainer->end());
   }

   void trim() {
      ltrim();
      rtrim();
   }
   */

    std::string* mpContainer;
   std::shared_ptr<std::string> mHolder;
};

//can remove this since c++ 17
#define STLAux(x) STLAux<std::decay<decltype(x)>::type>(x)