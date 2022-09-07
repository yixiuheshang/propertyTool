#include "filterBase.h"
#include <fstream>

PropertyInstance& getPropertyInstance()
{
    return PropertyInstance::getInstance();
}


void FilterBase::parseJson(const char* filename, Json::Value &root)
{
    Json::Reader reader;
    std::ifstream ifs; 
    ifs.open(filename, std::ios::in);
    if (!reader.parse(ifs, root, false)) {
        std::cout << "reader parse faild!" << std::endl;
        return;
    }
    ifs.close();
}

void FilterBase::jsonOutput(const std::string &outputFileName, const Json::Value &propertyInfos)
{
    std::ofstream os;
    os.open(outputFileName, std::ios::out);
    Json::StyledWriter sw;
    os << sw.write(propertyInfos);
    os.close();
}

void FilterBase::txtOutput(const std::string &outputFileName, const Json::Value &propertyInfos)
{
    std::ofstream os;
    os.open(outputFileName, std::ios::out);
    if (!propertyInfos["propertyInfo"].isNull()) {
        for(int i = 0; i < propertyInfos["propertyInfo"].size(); ++i) {
            os << propertyInfos["propertyInfo"][i]["propertyName"].asString() << " ";
            for (int j = 0; j < propertyInfos["propertyInfo"][i]["signal"].size(); ++j) {
                os << propertyInfos["propertyInfo"][i]["signal"][j]["signalName"].asString() << " ";
            }
            os << std::endl;
        }
    }
    
    os.close();
}