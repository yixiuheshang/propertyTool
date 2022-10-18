#pragma once
#include <vector>
#include <map>
#include <memory>
#include <iostream>
#ifdef WIN32
#include "json/json.h"
#else
#include "json.h"
#endif


// static const std::map<const std::string, const std::string> projectMap = {
//     {"1","A07锟斤拷统锟斤拷锟斤拷"},
//     {"2","A07锟斤拷锟斤拷源"},
//     {"3","A08锟斤拷统锟斤拷锟斤拷"},
//     {"4","A08锟斤拷锟斤拷源"},
//     {"5","B02锟斤拷统锟斤拷锟斤拷"},
//     {"6","B02锟斤拷锟斤拷源"},
//     {"7","B03"},
//     {"8","B07/B16(锟斤拷锟斤拷&锟斤拷锟解）"},
//     {"9","D01/D02/D03锟斤拷统锟斤拷锟斤拷"},
//     {"10","D01/D02/D03锟斤拷锟斤拷源"},
//     {"11","D02锟斤拷锟斤拷P0"},
//     {"12","D02锟斤拷锟斤拷P2"},
//     {"13","EC24"},
//     {"14","EC24锟斤拷锟斤拷"},
//     {"15","EC31"},
//     {"16","ES13"},
//     {"17","ES24"},
//     {"18","P01锟斤拷锟斤拷HEV锟斤拷锟斤拷"},
//     {"19","P01锟斤拷锟解传统锟斤拷锟斤拷"},
//     {"20","P02锟斤拷统锟斤拷锟斤拷"},
//     {"21","P02锟斤拷锟解传统锟斤拷锟斤拷"},
//     {"22","P02锟斤拷锟斤拷锟斤拷锟斤拷源"},
//     {"23","P02锟斤拷锟斤拷源"},
//     {"24","P03锟斤拷统锟斤拷锟斤拷"},
//     {"25","P03锟斤拷锟解传统锟斤拷锟斤拷"},
//     {"26","P03锟斤拷锟斤拷锟斤拷锟斤拷源"},
//     {"27","P03锟斤拷锟斤拷源"},
//     {"28","P05PHEV6*6"},
//     {"29","P05锟斤拷统锟斤拷锟斤拷"},
//     {"30","P05锟斤拷锟斤拷HEV"},
//     {"31","P05锟斤拷锟解传统锟斤拷锟斤拷"},
//     {"32","P05锟斤拷锟斤拷源"},
//     {"33","P09 EV"},
//     {"34","P09锟斤拷统锟斤拷锟斤拷"},
//     {"35","P09锟斤拷锟斤拷源"},
//     {"36","P11"}    
// };

static const std::map<const std::string, const std::vector<std::string>> projectMap = {
    {"A07",{"A07传统动力","A07新能源"}},
    {"A08",{"A08传统动力","A08新能源"}},
    {"B02",{"B02传统动力","B02新能源"}},
    {"B03",{"B03"}},
    {"B07",{"B07/B16(国内&海外）"}},
    {"B16",{"B07/B16(国内&海外）"}},
    {"D01",{"D01/D02/D03传统动力","D01/D02/D03新能源"}},
    {"D02",{"D01/D02/D03传统动力","D01/D02/D03新能源"}},
    {"D03",{"D01/D02/D03传统动力","D01/D02/D03新能源"}},
    {"EC24",{"EC24","EC24海外"}},
    {"EC31",{"EC31"}},
    {"ES13",{"ES13"}},
    {"ES24",{"ES24"}},
    {"P01",{"P01海外HEV动力","P01海外传统动力"}},
    {"P02",{"P02传统动力","P02海外传统动力","P02海外新能源","P02新能源"}},
    {"P03",{"P03传统动力","P03海外传统动力","P03海外新能源","P03新能源"}},
    {"P05",{"P05PHEV6*6","P05传统动力","P05海外HEV","P05海外传统动力","P05新能源"}},
    {"P09",{"P09 EV","P09传统动力","P09新能源"}},
    {"P11",{"P11"}}
};

struct Signal
{
    std::string mSignaleName;
    std::string mMessagName;
    std::string mMessageID;
    std::string mFirstCoding; 
    std::string mSecondCoding; 
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
    std::vector<std::shared_ptr<Signal>> mSignal;
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
    void init(std::shared_ptr<PropertyInfo>&& sigData) {
        mPropertyInfo.emplace_back(sigData);
    }
private:
    PropertyInstance() = default;
};
extern PropertyInstance& getPropertyInstance();

class ParseJSON 
{

};

class FilterBase
{
public: 
    FilterBase() = default;
    virtual ~FilterBase() {}

    virtual void allOutput(const char* filename) = 0;
    virtual void filter(const char* filename, std::string projectKey) = 0;

    void parseJson(const char* filename, Json::Value &root);
    void jsonOutput(const std::string &outputFileName, const Json::Value &propertyInfos);
    void txtOutput(const std::string &outputFileName, const Json::Value &propertyInfos);
    void fiterSameNameSignal(Json::Value &propertyInfos);
};


