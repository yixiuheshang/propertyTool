#pragma once
#include <vector>
#include <map>
#include <memory>
#include "STLAux.h"
#include "json.h"

static const std::map<const std::string, const std::string> projectMap = {
    {"1","A07��ͳ����"},
    {"2","A07����Դ"},
    {"3","A08��ͳ����"},
    {"4","A08����Դ"},
    {"5","B02��ͳ����"},
    {"6","B02����Դ"},
    {"7","B03"},
    {"8","B07/B16(����&���⣩"},
    {"9","D01/D02/D03��ͳ����"},
    {"10","D01/D02/D03����Դ"},
    {"11","D02����P0"},
    {"12","D02����P2"},
    {"13","EC24"},
    {"14","EC24����"},
    {"15","EC31"},
    {"16","ES13"},
    {"17","ES24"},
    {"18","P01����HEV����"},
    {"19","P01���⴫ͳ����"},
    {"20","P02��ͳ����"},
    {"21","P02���⴫ͳ����"},
    {"22","P02��������Դ"},
    {"23","P02����Դ"},
    {"24","P03��ͳ����"},
    {"25","P03���⴫ͳ����"},
    {"26","P03��������Դ"},
    {"27","P03����Դ"},
    {"28","P05PHEV6*6"},
    {"29","P05��ͳ����"},
    {"30","P05����HEV"},
    {"31","P05���⴫ͳ����"},
    {"32","P05����Դ"},
    {"33","P09 EV"},
    {"34","P09��ͳ����"},
    {"35","P09����Դ"},
    {"36","P11"}    
};


struct Signal
{
    std::string mSignaleName;
    std::string mMessagName;
    std::string mMessageID;
    std::string mFirstCoding; // ÿ���źŶ�Ӧ��coding
    std::string mSecondCoding; // �ӿڶ�Ӧ��coding
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
    std::vector<std::shared_ptr<Signal>> mSignal; // һ���ӿڶ�Ӧ�����ź�
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

// �ź����ݵ���
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
extern PropertyInstance& getPropertyInstance(); // �ṩ���ⲿʹ�õĽӿ�

// ����json�ļ�����
class ParseJSON 
{

};

class FilterBase
{
public: 
    FilterBase() = default;
    virtual ~FilterBase() {}

    virtual void allOutput(const char* filename) = 0;
    virtual void filter(const char* filename, std::string projectKey) = 0; // ������,������Ҫ�򿪵��ļ���

    void parseJson(const char* filename, Json::Value &root);
    void jsonOutput(const std::string &outputFileName, const Json::Value &propertyInfos);
    void txtOutput(const std::string &outputFileName, const Json::Value &propertyInfos);
    void fiterSameNameSignal(Json::Value &propertyInfos);
};


