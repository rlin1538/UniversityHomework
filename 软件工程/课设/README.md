# 基于Android的游戏圈交流系统部署手册

## 1.后端服务

​	压缩包内software_coursedesign为后端代码文件，其采用spring boot框架搭建，用maven构建。

​	采取的JDK版本为1.8.0_211。

​	配套数据库为Mysql，压缩包内包含初始数据库包game_circle.sql该库对应本后端服务，版本为Mysql 5.7。 后端的数据库配置位于src\main\resources\application.properties文件中。

​	后端运行后的端口为8080，接口如http://127.0.0.1:8080/api/gamecircle

​	当前后端服务已部署在个人服务器，可以直接安装压缩包内的游戏圈v1.0.1.apk直接使用。

## 2.客户端

​	客户端采用Flutter框架构建，压缩包内game_circle文件夹为客户端的代码文件，源码目录在lib子文件夹中。

​	构建后可以输出.apk文件，在安卓手机上安装使用，IOS应用需使用Mac平台的Xcode进行构建。

