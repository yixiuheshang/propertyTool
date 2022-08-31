#pragma once
#include "filterBase.h"

class MergeFilter : public FilterBase
{
private:
    template<typename T>
    inline int equals(T a, T b){
        return a == b;
    }
    template<typename T>
    void check(std::vector<T> &src, std::map<T,int> &dst);

public:
    MergeFilter(/* args */) = default; 
    virtual ~MergeFilter() override {}

    virtual void filter(const char* filename, const char* projectName) override;
};

class CombinFilter : public FilterBase
{
private:
    /* data */
public:
    CombinFilter(/* args */) = default; 
    virtual ~CombinFilter() override {}

    virtual void filter(const char* filename, const char* projectName) override;
};

class Specialtreat : public FilterBase
{
private:
    const std::vector<std::shared_ptr<PropertyInfo>> mOldData;
public:
    Specialtreat(/* args */) = default; 
    virtual ~Specialtreat() override {}

    virtual void filter(const char* filename, const char* projectName) override;
};