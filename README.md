# 使用说明
    {"A07",{"A07传统动力","A07新能源"}},
    {"A08",{"A08传统动力","A08新能源"}},
    {"B02",{"B02传统动力","B02新能源"}},
    {"B03",{"B03"}},
    {"B07",{"B07/B16(国内&海外）"}},
    {"B16",{"B07/B16(国内&海外）"}},
    {"D01",{"D01/D02/D03传统动力","D01/D02/D03新能源"}},
    {"D02",{"D01/D02/D03传统动力","D01/D02/D03新能源"}},
    {"D03",{"D01/D02/D03传统动力","D01/D02/D03新能源"}},
    {"EC24",{"EC24","EC24海外"}},
    {"EC31",{"EC31"}},
    {"ES13",{"ES13"}},
    {"ES24",{"ES24"}},
    {"P01",{"P01海外HEV动力","P01海外传统动力"}},
    {"P02",{"P02传统动力","P02海外传统动力","P02海外新能源","P02新能源"}},
    {"P03",{"P03传统动力","P03海外传统动力","P03海外新能源","P03新能源"}},
    {"P05",{"P05PHEV6*6","P05传统动力","P05海外HEV","P05海外传统动力","P05新能源"}},
    {"P09",{"P09 EV","P09传统动力","P09新能源"}},
    {"P11",{"P11"}}

输入：将v3.5文档映射的json文件如：propertyInfo.json 放入bin目录下

输出：输出文档如：combinXXX.json mergeXXX.json combinXXX.txt mergeXXX.txt，分别是接口对应的信号需要组合、接口对应的信号需要合并



操作步骤

1.下载软件压缩包：propertyTool.tar.gz

2.将压缩上传到linux环境解压

3.进入build目录执行：cmake ..;make   这是在bin目录下会生成可执行文件propertyExcelTool 如下图



4.将v3.5文档映射的json文件如：propertyInfo.json 放入bin目录下

5.筛选A07传统动力项目的合并信号执行 ./propertyExcelTool m propertyInfo.json A07

6.此时在bin目录下就会生成mergeA07.json 和 mergeA07.txt文件，这就是需要合并的A07传统动力信号文件

7.组合信号输入./propertyExcelTool c propertyInfo.json A07

8.如何想一键筛选所有项目的合并组合信号则执行：./propertyExcelTool a propertyInfo.json

注意：如果bin目录已经有propertyExcelTool，则直接执行4-8