#pragma once
#include "filterBase.h"

class MergeFilter : public FilterBase
{
private:
    template<typename T>
    inline int equals(T a, T b){
        return a == b;
    }

    // 功能：获取数组中元素的个数 
    // 参数1：需统计的数组，仅支持内置类型的数组
    // 参数2：保存结果，元素以及对应元素对应个数	
    template<typename T>
    void check(std::vector<T> &src, std::map<T,int> &dst);

public:
    MergeFilter(/* args */) = default; 
    virtual ~MergeFilter() override {}

    virtual void filter(const char* filename) override;
};

class CombinFilter : public FilterBase
{
private:
    /* data */
public:
    CombinFilter(/* args */) = default; 
    virtual ~CombinFilter() override {}

    virtual void filter(const char* filename) override;
};

class Specialtreat : public FilterBase
{
private:
    const std::vector<std::shared_ptr<PropertyInfo>> mOldData;
public:
    Specialtreat(/* args */) = default; 
    virtual ~Specialtreat() override {}

    virtual void filter(const char* filename) override;
};