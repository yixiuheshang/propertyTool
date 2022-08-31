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

void MergeFilter::filter(const char* filename, const char* projectName) 
{
    std::string proStr(projectName);
    std::cout << "merge filter" << std::endl;
    std::cout << "filename :" << filename << std::endl;
    std::cout << "projectName :" << proStr << std::endl;

    Json::Reader reader;// 解析json用Json::Reader  
    Json::Value root; // Json::Value是一种很重要的类型，可以代表任意类型。如int, string, object, array        
 
    std::ifstream ifs; 
    ifs.open (filename, std::ios::in);

    std::ofstream os;
    std::string outputFileName = "merge";
    // outputFileName.append(proStr);
    outputFileName.append(".json");

	os.open(outputFileName, std::ios::out);
	Json::Value propertyInfos;

    if (reader.parse(ifs, root, false)) 
    { 
        std::string code; 
        if (!root["propertyInfo"].isNull()) { // 访问节点，Access an object value by name, create a null member if it does not exist. 
            int size = root["propertyInfo"].size();
            // std::cout << "propertyInfo " << "size :" << size << std::endl;
            
            for(int i = 0; i < size; ++i)  // 遍历数组 
            { 
                std::string propertyType = root["propertyInfo"][i]["propertyType"].asString();
                // std::cout << "propertyType :" << propertyType << std::endl;
                Json::Value valSignal = root["propertyInfo"][i]["signal"]; 
                int signalSize = valSignal.size();
                Json::Value propertyInfo;
                if (signalSize > 1 && propertyType != "INT32_VEC" && propertyType != "FLOAT_VEC") {
                    Json::Value sig;
                    for (int j=0; j<signalSize; j++) {
                            
                            // ======================================================打印出isProjectExit的key值
                            Json::Value::Members member = valSignal[j]["isProjectExit"].getMemberNames();
                            auto iter = member.begin();
                            for (; iter != member.end(); ++iter) {
                                if (*iter == projectName) {
                                    break;
                                }
                            }
                            if (iter == member.end()) {
                                std::cout << projectName << "not found!" << std::endl;
                                return;
                            }
                           
                            // std::cout << valSignal[j]["signaleName"].asString() << " -->." <<std::endl;
                            bool isNeedMerge = valSignal[j]["isProjectExit"][projectName].asBool();
                            std::cout << root["propertyInfo"][i]["propertyName"].asString() << "-->" 
                                      << valSignal[j]["signaleName"].asString() <<" --> " 
                                      << projectName << " --> " << isNeedMerge << std::endl;        
                            if (isNeedMerge) {
                                propertyInfo["propertyName"] = root["propertyInfo"][i]["propertyName"];
                                sig["signalName"] = valSignal[j]["signaleName"];
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
    
    Json::StyledWriter sw;
	os << sw.write(propertyInfos);
	os.close();
}

void CombinFilter::filter(const char* filename, const char* projectName)
{
    std::cout << "combin filter" << std::endl;
    std::cout << "filename :" << filename << std::endl;
    Json::Reader reader;// 解析json用Json::Reader  
    Json::Value root; // Json::Value是一种很重要的类型，可以代表任意类型。如int, string, object, array        
 
    std::ifstream ifs; 
    ifs.open (filename, std::ios::binary);

    std::ofstream os;
	os.open("combin.json", std::ios::out);
	Json::Value propertyInfos;

    if (reader.parse(ifs, root, false)) 
    { 
        std::string code; 
        if (!root["propertyInfo"].isNull()) { // 访问节点，Access an object value by name, create a null member if it does not exist. 
            int size = root["propertyInfo"].size();
            //std::cout << "propertyInfo " << "size :" << size << std::endl;
            for(int i = 0; i < size; ++i)  // 遍历数组 
            { 
                Json::Value valSignal = root["propertyInfo"][i]["signal"]; 
                int signalSize = valSignal.size(); 
                // std::cout << "Number of signals" << "in the interface (" << root["propertyInfo"][i]["propertyName"].asString() << ") is :" << signalSize <<std::endl;
                Json::Value valPropertyType = root["propertyInfo"][i]["propertyType"];
                std::string propertyType = valPropertyType.asString();
                // std::cout << "propertyType :" << propertyType << std::endl;
                if (signalSize > 1 && propertyType == "INT32_VEC" || propertyType == "FLOAT_VEC") {
                    // for (int i=0; i<signalSize; i++) {
                    //     std::cout << valSignal[i]["signaleName"].asString() << " need merge." <<std::endl;
                    // }
                    // std::cout << "(in) propertyType :" << propertyType << std::endl;
                    propertyInfos["propertyInfo"].append(root["propertyInfo"][i]);
                }
            } 
        }

    }
    ifs.close();
    
    Json::StyledWriter sw;
	os << sw.write(propertyInfos);
	os.close();
}

void Specialtreat::filter(const char* filename, const char* projectName)
{
    
}