#include <iostream>
#include "filterBase.h"
#include "filterSub.h"
#include <fstream>
#include "json.h"
/*
输入：一个json格式的文件，里面是所有待过滤的信号属性
输出：文件通过过滤器，剩下需要过滤的文件信息，输出还是一个json格式的文件
例子：
./propertyExcelTool merge json_text.json -->输出 merge.json
./propertyExcelTool combin  json_text.json -->输出 combin.json
*/

using namespace std;
using namespace Json;
int main(int argc, char **argv) 
{
    // std::map<std::string, std::shared_ptr<FilterBase>> cmd = {
    //     "merge" : std::make_shared<MergeFilter>,
    //     "combin" : std::make_shared<CombinFilter>,
    //     "specialTreat" : std::make_shared<Specialtreat>
    // }
    // if (*argv[1] == "merge") {
    //     cmd.find(*argv[1]);
    // }
    
    // filter->init();
    // // 数据通过过滤器
    // std::vector<std::shared_ptr<PropertyInfo>> output;
    // filter->merge(output);
    // std::vector<std::shared_ptr<PropertyInfo>> combinRet;
    // combin(combinRet);
    // std::vector<std::shared_ptr<PropertyInfo>> commentRet;
    // specialTreat(commentRet); 
    // // 最后再生成文件 output.txt combinRet.txt commentRet.txt

    // std::map<std::string, bool> D01 = {{"D01",false},{"P01",true}};
    // std::map<std::string, bool> D02 = {{"D01",false},{"P01",true}};
    // auto sig1 = std::make_shared<Signal>("1","2","3","4","5",D01);
    // auto sig2 = std::make_shared<Signal>("1","2","3","4","5",D02);
    // std::vector<std::shared_ptr<Signal>> signal = {sig1,sig2}; 
    // PropertyInstance::getInstance().mPropertyInfo.emplace_back(std::make_shared<PropertyInfo>("1","2","3","4","5",signal));
    // if (!PropertyInstance::getInstance().mPropertyInfo.empty()) {
    //     std::cout << PropertyInstance::getInstance().mPropertyInfo[0]->mPropertyName << std::endl;
    //     std::cout << PropertyInstance::getInstance().mPropertyInfo[0]->mPropertyType << std::endl;
    //     std::cout << PropertyInstance::getInstance().mPropertyInfo[0]->mAccess << std::endl;
    //     std::cout << PropertyInstance::getInstance().mPropertyInfo[0]->mChangeMode << std::endl;
    //     std::cout << PropertyInstance::getInstance().mPropertyInfo[0]->mComment << std::endl;
    // }

    // 使用json解析数据
    // ifstream ifs("json_text.json");
    // if (ifs)
    // {
    //     string line, jsonStr;
    //     while (getline(ifs, line))
    //         jsonStr.append(line);
    //     CharReader *reader = CharReaderBuilder().newCharReader();
    //     Value root;
    //     JSONCPP_STRING errs;
    //     if (reader->parse(jsonStr.c_str(), jsonStr.c_str() + jsonStr.size(), &root, &errs))
    //     {
    //         auto faceId = root["face"][0]["face_id"].asString();
    //         auto imgWidth = root["img_width"].asInt();
    //         auto imgHeight = root["img_height"].asInt();
    //         auto resCode = root["res_code"].asString();
    //         auto url = root["url"].asString();
    //         cout << "face_id:\t" << faceId << endl;
    //         cout << "img_width:\t" << imgWidth << endl;
    //         cout << "img_height:\t" << imgHeight << endl;
    //         cout << "res_code:\t" << resCode << endl;
    //         cout << "url:\t\t" << url << endl;
    //     }
    //     else
    //         cout << errs << endl;
    //     delete reader;
    // }

    std::cout << "start xxx" << std::endl;
    std::cout << "argv[1] : " << argv[1] << std::endl;
    std::cout << "argv[2] : " << argv[2] << std::endl;
    switch (argv[1][0])
    {
    case 'm': {
        std::cout << "merge" << std::endl;
        auto mergeFilter = std::make_shared<MergeFilter>();
        // mergeFilter->init();
        mergeFilter->filter(argv[2]);
        break;
    }
        
    case 'c': {
        std::cout << "combin" << std::endl;
        auto combinFilter = std::make_shared<CombinFilter>();
        // combinFilter->init();
        combinFilter->filter(argv[2]);
        break;
    }
    
    case 's': {
        std::cout << "special" << std::endl;
        auto specialtreatFilter = std::make_shared<Specialtreat>();
        // specialtreatFilter->init();
        specialtreatFilter->filter(argv[2]);
        break;
    }

    default:
        std::cout << "input empty" << std::endl;
        break;
    }

    
    return 0;
}