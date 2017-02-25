#ifndef HTTPREQUEST_H
#define HTTPREQUEST_H

#include <unordered_map>
#include <vector>
#include <iterator>

class HttpRequest
{
private:
    int _clientFd;
    std::string _buf;
    void readData();
    bool _isreadable;

public:
    HttpRequest(int clientFd):_clientFd(clientFd) {}
    bool isHasNextLine();
    std::string getNextLine();
//    ~HttpRequest();
};

#endif /* HTTPREQUEST_H */


// 1.读取数据
// 2.根据/r/n分割接收数据
// 分割存入数据函数
// while（ret == 0）
// {
//      if （/r/n）
//          存入数据成员；
//      else
//          继续读取数据；
// }
// 3.解析第一行函数
// 4.解析其他行函数
// 5.Get结果函数
