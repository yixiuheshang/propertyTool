# propertyTool
# 此款软件仅供学习使用

# 编译的时候请按照一下方法
cd build 
cmake ..
make
# 此时会生成可执行文件
# 使用方法如下 json_text.json 可以是任意json文件
# -->输出 merge.json
./propertyExcelTool merge json_text.json 
# -->输出 combin.json
./propertyExcelTool combin  json_text.json 