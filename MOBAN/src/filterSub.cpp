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

void MergeFilter::filter(const char* filename, const char* projectKey) 
{
    std::cout << "merge filter" << std::endl;
    std::cout << "filename :" << filename << std::endl;
    std::cout << "projectKey :" << projectKey << std::endl;

    auto projectMapIter = projectMap.find(projectKey);
    if (projectMapIter == projectMap.end()) {
        std::cout << projectKey << " is not in map!" << std::endl;
        return;
    }
    const char *projectName = projectMapIter->second;
    
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
                    Json::Value::Members member = valSignal[j]["isProjectExit"].getMemberNames();
                    auto iter = member.begin();
                    for (; iter != member.end(); ++iter) {
                        if (*iter == projectName) break;
                    }
                    if (iter == member.end()) {
                        std::cout << projectName << "not found!" << std::endl;
                        return;
                    }
                    
                    // std::cout << valSignal[j]["signaleName"].asString() << " -->." <<std::endl;
                    bool isNeedMerge = valSignal[j]["isProjectExit"][projectName].asBool();
                    // std::cout << root["propertyInfo"][i]["propertyName"].asString() << "-->" 
                    //             << valSignal[j]["signaleName"].asString() <<" --> " 
                    //             << *iter << " --> " << isNeedMerge << std::endl;        
                    if (isNeedMerge) {
                        propertyInfo["propertyName"] = root["propertyInfo"][i]["propertyName"];
                        sig["signalName"] = valSignal[j]["signaleName"];
                        sig["messagName"] = valSignal[j]["messagName"];
                        if (!sig.empty()) {
                            propertyInfo["signal"].append(sig);
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
    outputFileName.append(projectKey);
    
    std::string outputJson = outputFileName.append(".json");
    jsonOutput(outputJson, propertyInfos);

    std::string outputTXT = outputFileName.append(".txt");
    txtOutput(outputTXT, propertyInfos);
}

void MergeFilter::allOutput(const char* filename)
{  
    for (auto iter : projectMap) {
        filter(filename, iter.first);
    }
}

void CombinFilter::filter(const char* filename, const char* projectKey)
{
    std::cout << "combin filter" << std::endl;
    std::cout << "filename :" << filename << std::endl;
    std::cout << "projectKey :" << projectKey << std::endl;

    Json::Reader reader;
    Json::Value root;
 
    std::ifstream ifs; 
    ifs.open (filename, std::ios::in);

    auto projectMapIter = projectMap.find(projectKey);
    if (projectMapIter == projectMap.end()) {
        std::cout << projectKey << " is not in map!" << std::endl;
        return;
    }

    Json::Value propertyInfos;
    if (reader.parse(ifs, root, false)) 
    { 
        std::string code; 
        if (!root["propertyInfo"].isNull()) { 
            int size = root["propertyInfo"].size();
            // std::cout << "propertyInfo " << "size :" << size << std::endl;
            
            for(int i = 0; i < size; ++i)
            { 
                std::string propertyType = root["propertyInfo"][i]["propertyType"].asString();
                // std::cout << "propertyType :" << propertyType << std::endl;
                Json::Value valSignal = root["propertyInfo"][i]["signal"]; 
                int signalSize = valSignal.size();
                Json::Value propertyInfo;
                if (signalSize > 1 && (propertyType == "INT32_VEC" || propertyType == "FLOAT_VEC")) {
                    Json::Value sig;
                    for (int j=0; j<signalSize; j++) {
                            
                            // ======================================================
                            Json::Value::Members member = valSignal[j]["isProjectExit"].getMemberNames();
                            auto iter = member.begin();
                            for (; iter != member.end(); ++iter) {
                                if (*iter == projectMapIter->second) {
                                    break;
                                }
                            }
                            if (iter == member.end()) {
                                std::cout << projectMapIter->second << "not found!" << std::endl;
                                return;
                            }
                           
                            // std::cout << valSignal[j]["signaleName"].asString() << " -->." <<std::endl;
                            bool isNeedCombin = valSignal[j]["isProjectExit"][projectMapIter->second].asBool();
                            std::cout << root["propertyInfo"][i]["propertyName"].asString() << "-->" 
                                      << valSignal[j]["signaleName"].asString() <<" --> " 
                                      << *iter << " --> " << isNeedCombin << std::endl;        
                            if (isNeedCombin) {
                                propertyInfo["propertyName"] = root["propertyInfo"][i]["propertyName"];
                                sig["signalName"] = valSignal[j]["signaleName"];
                                sig["messagName"] = valSignal[j]["messagName"];
                                if (!sig.empty()) {
                                    propertyInfo["signal"].append(sig);
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

    }
    ifs.close();
    
    std::string outputFileName = "combin";
    outputFileName.append(projectKey);
    outputFileName.append(".json");
    jsonOutput(outputFileName, propertyInfos);
}

void CombinFilter::allOutput(const char* filename)
{  
    for (auto iter : projectMap) {
        filter(filename, iter.first);
    }
}