# c++版电力统计

# 源码编译

参考[drogon中文wiki](https://github.com/drogonframework/drogon/wiki/CHN-02-%E5%AE%89%E8%A3%85)

## Ubuntu: 
### 基础环境:
- 基础软件
```
sudo apt install git
sudo apt install gcc
sudo apt install g++
sudo apt install cmake
sudo apt install libjsoncpp-dev
sudo apt install uuid-dev
sudo apt install zlib1g-dev
sudo apt install libyaml-cpp-dev  // drogon中文wiki没有
```
- OpenSSL (可选，提供HTTPS支持)
```
sudo apt install openssl
sudo apt install libssl-dev
```
- mariaDB数据库
```
sudo apt install libmariadbclient-dev
```
### 编译安装drogon:
```shell
cd $WORK_PATH
git clone https://github.com/drogonframework/drogon
cd drogon
git submodule update --init
mkdir build
cd build
cmake ..
make && sudo make install
```
> 默认是编译debug版本，如果想编译release版本，cmake命令要带如下参数：
```shell
cmake -DCMAKE_BUILD_TYPE=Release ..
```
安装结束后，将有如下文件被安装在系统中(CMAKE_INSTALL_PREFIX可以改变安装位置)：  
+ drogon的头文件被安装到/usr/local/include/drogon中；  
+ drogon的库文件libdrogon.a被安装到/usr/local/lib中；  
+ drogon的命令行工具drogon_ctl被安装到/usr/local/bin中；  
+ trantor的头文件被安装到/usr/local/include/trantor中；  
+ trantor的库文件libtrantor.a被安装到/usr/local/lib中；  