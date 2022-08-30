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

void MergeFilter::filter(const char* filename) 
{
    std::cout << "merge filter" << std::endl;
    std::cout << "filename :" << filename << std::endl;
    Json::Reader reader;// 解析json用Json::Reader  
    Json::Value root; // Json::Value是一种很重要的类型，可以代表任意类型。如int, string, object, array        
 
    std::ifstream ifs; 
    ifs.open (filename, std::ios::binary);

    std::ofstream os;
	os.open("merge.json", std::ios::out);
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
                if (signalSize > 1 && propertyType != "INT32_VEC" && propertyType != "FLOAT_VEC") {
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

void CombinFilter::filter(const char* filename)
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

void Specialtreat::filter(const char* filename)
{
    
}