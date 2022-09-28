#include "filterBase.h"
#include <fstream>
#include <set>

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
            std::set<std::string> sigSet; 
            for (int j = 0; j < propertyInfos["propertyInfo"][i]["signal"].size(); ++j) {
                // std::cout << "++++++++++++++++++++" << propertyInfos["propertyInfo"][i]["signal"][j]["messageID"].asString() << std::endl;
                // std::cout << "++++++++++++++++++++" << propertyInfos["propertyInfo"][i]["signal"][j]["messageID"].asString() << std::endl;
                // std::cout << "--------------------" << propertyInfos["propertyInfo"][i]["signal"][j]["messagName"].asString() << std::endl;
                std::string signalNameAndMassageID = propertyInfos["propertyInfo"][i]["signal"][j]["signalName"].asString() + "." + propertyInfos["propertyInfo"][i]["signal"][j]["messagName"].asString();
                //std::cout << signalNameAndMassageID << std::endl;
                sigSet.insert(signalNameAndMassageID);
            }
            if (sigSet.size()>1) {
                os << propertyInfos["propertyInfo"][i]["propertyName"].asString() << " <========> ";
                for (auto &it : sigSet) {
                    // std::cout << it << std::endl;
                    os << it << " <----> ";
                }
                os << std::endl;
            }
        }
    }
    
    os.close();
}

void fiterSameNameSignal(Json::Value &propertyInfos)
{

}