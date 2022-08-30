#pragma once
#include <vector>
#include <map>
#include <memory>
#include "STLAux.h"
#include "json.h"

struct Signal
{
    std::string mSignaleName;
    std::string mMessagName;
    std::string mMessageID;
    std::string mFirstCoding; // 每个信号对应的coding
    std::string mSecondCoding; // 接口对应的coding
    /*
        {
            "D01" : false,
            "D01" : false,
            "P01" : true
        }
    */
    std::map<std::string, bool> mIsProjectExit;
    Signal(const std::string &signaleName,
           const std::string &messagName,
           const std::string &messageID,
           const std::string &firstCoding,
           const std::string &secondCoding,
           const std::map<std::string, bool>& isProjectExit)
           :  mSignaleName(signaleName),
              mMessagName(messagName),
              mMessageID(messageID),
              mFirstCoding(firstCoding),
              mSecondCoding(secondCoding),
              mIsProjectExit(isProjectExit) {}
};

struct PropertyInfo 
{
    std::string mPropertyName;
    std::string mPropertyType;
    std::string mAccess;
    std::string mChangeMode; 
    std::string mComment;
    std::vector<std::shared_ptr<Signal>> mSignal; // 一个接口对应几个信号
    PropertyInfo(const std::string &propertyName, 
                 const std::string &propertyType,
                 const std::string &access,
                 const std::string &changeMode,
                 const std::string &comment,
                 const std::vector<std::shared_ptr<Signal>>& signal)
            : mPropertyName(propertyName), 
              mPropertyType(propertyType),
              mAccess(access),
              mChangeMode(changeMode),
              mComment(comment),
              mSignal(signal) {}                   
};

// 信号数据单例
class PropertyInstance 
{
public:
    std::vector<std::shared_ptr<PropertyInfo>> mPropertyInfo; // 

    PropertyInstance(const PropertyInstance&) = delete;
    PropertyInstance& operator=(const PropertyInstance&) = delete;
    
    static PropertyInstance& getInstance()
    {
      static PropertyInstance instance;
      return instance;
    }

    // void init(std::sharedp_tr<PropertyInfo>& sigData) {
    //     STLAux(mPropertyInfo).for_each([&](std::sharedp_tr<PropertyInfo>& sigData) {
    //         mPropertyInfo.emplace_back(sigData);
    //     });
    // }

    void init(std::shared_ptr<PropertyInfo>&& sigData) {
        mPropertyInfo.emplace_back(sigData);
    }
private:
    PropertyInstance() = default;
};
extern PropertyInstance& getPropertyInstance(); // 提供给外部使用的接口

// 解析json文件的类
class ParseJSON 
{

};

class FilterBase
{
public:
    virtual void filter(const char* filename) = 0; // 过滤器,传入需要打开的文件名
    FilterBase() = default;
    virtual ~FilterBase() {}
};


