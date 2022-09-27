#pragma once
#include <vector>
#include <map>
#include <memory>
#include "STLAux.h"
#include "json.h"

static const std::map<const std::string, const std::string> projectMap = {
        {"1","A07传统动力"},
        {"2","A07新能源"},
        {"3","A08传统动力"},
        {"4","A08新能源"},
        {"5","B02传统动力"},
        {"6","B02新能源"},
        {"7","B03"},
        {"8","B07/B16(国内&海外）"},
        {"9","D01/D02/D03传统动力"},
        {"10","D01/D02/D03新能源"},
        {"11","D02海外P0"},
        {"12","D02海外P2"},
        {"13","EC24"},
        {"14","EC24海外"},
        {"15","EC31"},
        {"16","ES13"},
        {"17","ES24"},
        {"18","P01海外HEV动力"},
        {"19","P01海外传统动力"},
        {"20","P02传统动力"},
        {"21","P02海外传统动力"},
        {"22","P02海外新能源"},
        {"23","P02新能源"},
        {"24","P03传统动力"},
        {"25","P03海外传统动力"},
        {"26","P03海外新能源"},
        {"27","P03新能源"},
        {"28","P05PHEV6*6"},
        {"29","P05传统动力"},
        {"30","P05海外HEV"},
        {"31","P05海外传统动力"},
        {"32","P05新能源"},
        {"33","P09 EV"},
        {"34","P09传统动力"},
        {"35","P09新能源"},
        {"36","P11"}    
    };


struct Signal
{
    std::string mSignaleName;
    std::string mMessagName;
    std::string mMessageID;
    std::string mFirstCoding; // 每锟斤拷锟脚号讹拷应锟斤拷coding
    std::string mSecondCoding; // 锟接口讹拷应锟斤拷coding
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
    std::vector<std::shared_ptr<Signal>> mSignal; // 一锟斤拷锟接口讹拷应锟斤拷锟斤拷锟脚猴拷
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

// 锟脚猴拷锟斤拷锟捷碉拷锟斤拷
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
extern PropertyInstance& getPropertyInstance(); // 锟结供锟斤拷锟解部使锟矫的接匡拷

// 锟斤拷锟斤拷json锟侥硷拷锟斤拷锟斤拷
class ParseJSON 
{

};

class FilterBase
{
public: 
    FilterBase() = default;
    virtual ~FilterBase() {}

    virtual void allOutput(const char* filename) = 0;
    virtual void filter(const char* filename, std::string projectKey) = 0; // 锟斤拷锟斤拷锟斤拷,锟斤拷锟斤拷锟斤拷要锟津开碉拷锟侥硷拷锟斤拷

    void parseJson(const char* filename, Json::Value &root);
    void jsonOutput(const std::string &outputFileName, const Json::Value &propertyInfos);
    void txtOutput(const std::string &outputFileName, const Json::Value &propertyInfos);
    void fiterSameNameSignal(Json::Value &propertyInfos);
};


