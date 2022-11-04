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

//carType v3.5�С����ͣ���ʾʵ�����°�����ź����ޣ�(���ں��⹲��)����Ӧ��
static std::string GetProjectName(std::string& carType)
{
    if (0 == carType.find("B07"))
    {
        return "B16";
    }
    else if (0 == carType.find("D01"))
    {
        return "D01";
    }
    else if (0 == carType.find("EC24"))
    {
        return "EC24";
    }
    else if (0 == carType.find("EC31"))
    {
        return "EC31";
    }
    else if (0 == carType.find("P01"))
    {
        return "P01";
    }
    else if (0 == carType.find("P02"))
    {
        return "P02";
    }
    else if (0 == carType.find("P03"))
    {
        return "P03";
    }
    else if (0 == carType.find("P05"))
    {
        return "P05";
    }
    else if (0 == carType.find("P09"))
    {
        return "P09";
    }
    else if (0 == carType.find("P11"))
    {
        return "P11";
    }
    else
    {
        return "";
    }
}

static const std::map<const std::string, const std::vector<std::string>> projectMap = {
    {"A07",{"A07��ͳ����","A07����Դ"}},
    {"A08",{"A08��ͳ����","A08����Դ"}},
    {"B02",{"B02��ͳ����","B02����Դ"}},
    {"B03",{"B03"}},
    {"B07",{"B07/B16(����&���⣩"}},
    {"B16",{"B07/B16(����&���⣩"}},
    {"D01",{"D01/D02/D03��ͳ����","D01/D02/D03����Դ"}},
    {"D02",{"D01/D02/D03��ͳ����","D01/D02/D03����Դ"}},
    {"D03",{"D01/D02/D03��ͳ����","D01/D02/D03����Դ"}},
    {"EC24",{"EC24","EC24����"}},
    {"EC31",{"EC31"}},
    {"ES13",{"ES13"}},
    {"ES24",{"ES24"}},
    {"P01",{"P01����HEV����","P01���⴫ͳ����"}},
    {"P02",{"P02��ͳ����","P02���⴫ͳ����","P02��������Դ","P02����Դ"}},
    {"P03",{"P03��ͳ����","P03���⴫ͳ����","P03��������Դ","P03����Դ"}},
    {"P05",{"P05PHEV6*6","P05��ͳ����","P05����HEV","P05���⴫ͳ����","P05����Դ"}},
    {"P09",{"P09 EV","P09��ͳ����","P09����Դ"}},
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
    virtual void filter(const char* filename, std::string projectName) = 0;

    void parseJson(const char* filename, Json::Value &root);
    void jsonOutput(const std::string &outputFileName, const Json::Value &propertyInfos);
    void txtOutput(const std::string &outputFileName, const Json::Value &propertyInfos);
    void fiterSameNameSignal(Json::Value &propertyInfos);
};


