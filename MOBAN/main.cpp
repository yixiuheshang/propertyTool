#include <iostream>
#include "filterBase.h"
#include "filterSub.h"
#include <fstream>
#include "json.h"
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
    static std::map<const char*, const char*> projectMap = {
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