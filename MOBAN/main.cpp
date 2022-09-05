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
    std::cout << "start xxx" << std::endl;
    std::cout << "argv[1] : " << argv[1] << std::endl;
    std::cout << "argv[2] : " << argv[2] << std::endl;
    //std::cout << "argv[3] : " << argv[3] << std::endl;

       
    switch (argv[1][0])
    {
    case 'm': {
        std::cout << "merge" << std::endl;
        auto mergeFilter = std::make_unique<MergeFilter>();
        // mergeFilter->init();
        mergeFilter->filter(argv[2], argv[3]);
        break;
    }
        
    case 'c': {
        std::cout << "combin" << std::endl;
        auto combinFilter = std::make_unique<CombinFilter>();
        // combinFilter->init();
        combinFilter->filter(argv[2], argv[3]);
        break;
    }
 
    case 'a': {
        // 这里一键输出所有项目的merge和combin
        std::cout << "all output " << std::endl;
        auto combin = std::make_unique<CombinFilter>();
        // combinFilter->init();
        combin->allOutput(argv[2]);

        auto merge = std::make_unique<MergeFilter>();
        merge->allOutput(argv[2]);
        
        break;
    }

    default:
        std::cout << "input empty" << std::endl;
        break;
    }

    
    return 0;
}