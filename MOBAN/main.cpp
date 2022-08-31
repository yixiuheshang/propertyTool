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
    static std::map<const char*, const char*> projectMap = {
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

    std::cout << "start xxx" << std::endl;
    std::cout << "argv[1] : " << argv[1] << std::endl;
    std::cout << "argv[2] : " << argv[2] << std::endl;
    std::cout << "argv[3] : " << argv[3] << std::endl;

    if () {

    }    
    switch (argv[1][0])
    {
    case 'm': {
        std::cout << "merge" << std::endl;
        auto mergeFilter = std::make_shared<MergeFilter>();
        // mergeFilter->init();
        mergeFilter->filter(argv[2], argv[3]);
        break;
    }
        
    case 'c': {
        std::cout << "combin" << std::endl;
        auto combinFilter = std::make_shared<CombinFilter>();
        // combinFilter->init();
        combinFilter->filter(argv[2], argv[3]);
        break;
    }
    
    case 's': {
        std::cout << "special" << std::endl;
        auto specialtreatFilter = std::make_shared<Specialtreat>();
        // specialtreatFilter->init();
        specialtreatFilter->filter(argv[2], argv[3]);
        break;
    }

    default:
        std::cout << "input empty" << std::endl;
        break;
    }

    
    return 0;
}