#include <iostream>
#include <fstream>
#include "json.h"
#include "filterSub.h"

template<typename T>
void MergeFilter::check(std::vector<T> &src, std::map<T,int> &dst)
{ 
    for (size_t i = 0; i < src.size(); ++i) {
        T checkStr = src[i];
        bool flag = false;
        for (size_t j = 0; j < i; ++j) {
            if (equals(checkStr, src[j])) {
                flag = true;
                break;
            }
        }
        if (!flag) {
            int count = 1;
            for (size_t j = i + 1; j < src.size(); ++j) {
                if (equals(checkStr, src[j])){
                    ++count;
                }
            }
            dst.insert(std::pair<T, int>(checkStr, count));
        }
    }
}

void MergeFilter::filter(const char* filename, std::string projectKey) 
{
    std::cout << "merge filter" << std::endl;
    std::cout << "filename :" << filename << std::endl;
    std::cout << "projectKey :" << projectKey << std::endl;
    std::cout << "value :" << projectMap.at(projectKey)[0] << std::endl;

    auto projectMapIter = projectMap.find(projectKey);
    if (projectMapIter == projectMap.end()) {
        std::cout << projectKey << " is not in map!" << std::endl;
        return;
    }
    auto projectName = projectMapIter->second;
    
    Json::Value root;
    parseJson(filename, root);
    Json::Value propertyInfos; 
    if (!root["propertyInfo"].isNull()) { 
        for(int i = 0; i < root["propertyInfo"].size(); ++i) { 
            std::string propertyType = root["propertyInfo"][i]["propertyType"].asString();
            // std::cout << "propertyType :" << propertyType << std::endl;
            Json::Value valSignal = root["propertyInfo"][i]["signal"]; 
            int signalSize = valSignal.size();
            Json::Value propertyInfo;
            if (signalSize > 1 && propertyType != "INT32_VEC" && propertyType != "FLOAT_VEC") {
                Json::Value sig;
                for (int j=0; j<signalSize; j++) {
                    // ======================================================
                    for (int k=0; k<projectName.size(); k++) {
                        Json::Value::Members member = valSignal[j]["isProjectExit"].getMemberNames();
                        auto iter = member.begin();
                        for (; iter != member.end(); ++iter) {
                            if (*iter == projectName[k]) break;
                        }
                        if (iter == member.end()) {
                            std::cout << projectName[k] << "not found!" << std::endl;
                            return;
                        }
                        
                        bool isNeedMerge = valSignal[j]["isProjectExit"][projectName[k]].asBool();        
                        if (isNeedMerge) {
                            propertyInfo["propertyName"] = root["propertyInfo"][i]["propertyName"];
                            sig["signalName"] = valSignal[j]["signaleName"];
                            sig["messagName"] = valSignal[j]["messagName"];
                            if (!sig.empty()) {
                                propertyInfo["signal"].append(sig);
                            }
                            break;
                        }
                    }
                } 
                // std::cout << "(in) propertyType :" << propertyType << std::endl;
            }
            if (!propertyInfo.empty() && propertyInfo["signal"].size() > 1) {
                propertyInfos["propertyInfo"].append(propertyInfo);
            }
        } 
    }

    std::string outputFileName = "merge";
    std::string outputJson = outputFileName.append(projectKey);
    jsonOutput(outputJson.append(".json"), propertyInfos);
    
    std::string outputTXT = outputFileName;
    txtOutput(outputTXT.append(".txt"), propertyInfos);
}

void MergeFilter::allOutput(const char* filename)
{  
    for (auto iter : projectMap) {
        filter(filename, iter.first);
    }
}

void CombinFilter::filter(const char* filename, std::string projectKey)
{
    std::cout << "combin filter" << std::endl;
    std::cout << "filename :" << filename << std::endl;
    std::cout << "projectKey :" << projectKey << std::endl;
    std::cout << "value :" << projectMap.at(projectKey)[0] << std::endl;

    auto projectMapIter = projectMap.find(projectKey);
    if (projectMapIter == projectMap.end()) {
        std::cout << projectKey << " is not in map!" << std::endl;
        return;
    }
    auto projectName = projectMapIter->second;
    
    Json::Value root;
    parseJson(filename, root);
    Json::Value propertyInfos; 
    if (!root["propertyInfo"].isNull()) { 
        for(int i = 0; i < root["propertyInfo"].size(); ++i) { 
            std::string propertyType = root["propertyInfo"][i]["propertyType"].asString();
            // std::cout << "propertyType :" << propertyType << std::endl;
            Json::Value valSignal = root["propertyInfo"][i]["signal"]; 
            int signalSize = valSignal.size();
            Json::Value propertyInfo;
            if (signalSize > 1 && (propertyType == "INT32_VEC" || propertyType == "FLOAT_VEC")) {
                Json::Value sig;
                for (int j=0; j<signalSize; j++) {
                    // ======================================================
                    for (int k=0; k<projectName.size(); k++) {
                        Json::Value::Members member = valSignal[j]["isProjectExit"].getMemberNames();
                        auto iter = member.begin();
                        for (; iter != member.end(); ++iter) {
                            if (*iter == projectName[k]) break;
                        }
                        if (iter == member.end()) {
                            std::cout << projectName[k] << "not found!" << std::endl;
                            return;
                        }
    
                        bool isNeedCombin = valSignal[j]["isProjectExit"][projectName[k]].asBool();        
                        if (isNeedCombin) {
                            propertyInfo["propertyName"] = root["propertyInfo"][i]["propertyName"];
                            sig["signalName"] = valSignal[j]["signaleName"];
                            sig["messagName"] = valSignal[j]["messagName"];
                            if (!sig.empty()) {
                                propertyInfo["signal"].append(sig);
                            }
                            break;
                        }
                    }
                } 
                // std::cout << "(in) propertyType :" << propertyType << std::endl;
            }
            if (!propertyInfo.empty() && propertyInfo["signal"].size() > 1) {
                propertyInfos["propertyInfo"].append(propertyInfo);
            }
        } 
    }

    std::string outputFileName = "combin";
    std::string outputJson = outputFileName.append(projectKey);
    jsonOutput(outputJson.append(".json"), propertyInfos);

    std::string outputTXT = outputFileName;
    txtOutput(outputTXT.append(".txt"), propertyInfos);
}

void CombinFilter::allOutput(const char* filename)
{  
    for (auto iter : projectMap) {
        filter(filename, iter.first);
    }
}