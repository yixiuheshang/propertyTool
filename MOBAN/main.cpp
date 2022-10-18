#include <iostream>
#include "filterBase.h"
#include "filterSub.h"
#include <fstream>
#ifdef WIN32
#include "json/json.h"
#else
#include "json.h"
#endif
/*
���룺һ��json��ʽ���ļ������������д����˵��ź�����
������ļ�ͨ����������ʣ����Ҫ���˵��ļ���Ϣ���������һ��json��ʽ���ļ�
���ӣ�
./propertyExcelTool merge json_text.json -->��� merge.json
./propertyExcelTool combin  json_text.json -->��� combin.json
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
        // ����һ�����������Ŀ��merge��combin
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