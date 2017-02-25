/******************************************************************************
 ***** File Name : HttpResponse.cpp
 **** Created By : kyaz758
 *** Description :
 * Creation Date : 2017-02-14 17:39
 * Last Modified : 2017-02-14 18:58
 ******************************************************************************/

#ifndef HTTPRESPONSE_H
#define HTTPRESPONSE_H
#define LFCR "/r/n" //FIXME TODO XXX
//纯C++头文件：HPP
//和CPP无任何区别，业界约定俗成，区分.h文件

#include <iostream>
#include <unordered_map>
#include <vector>
#include <stdint.h>
#include <iterator>

using std::cin;
using std::cout;
using std::endl;

class HttpResponse
{
private:
    typedef uint16_t HTTPState;
    static const HTTPState HTTP_200 = 200;
    static const HTTPState HTTP_404 = 404;
    static std::unordered_map<HTTPState, std::string> _stateTable;
    HTTPState _state;
    std::unordered_map<std::string, std::string> _headers; 
    std::vector<uint8_t> _body;
    //static const char * const LFCR = "/r/n";
public:
    HttpResponse(HTTPState state):_state(state) {}
    HttpResponse& headersAdd(const std::string key, const std::string value)
    {
        //_headers.insert({key, value});
        _headers[key] = value;
        return *this;
    }
    void writeBody(const std::string &body) 
    {
        _body.clear(); //重复调用问题？设计。。。
        //迭代器适配器
        //std::copy(body.begin(), body.end(), _body.begin());
        std::copy(body.begin(), body.end(), std::back_inserter(_body));
    }   
    std::string getPackage() const
    {
        std::string package;
        package.append("HTTP/1.0 ");
        package.append(_stateTable[_state]); //表驱动，数据驱动
        package.append(LFCR);
        for (auto e : _headers)
        {
            package.append(e.first);
            package.append(":");
            package.append(e.second);
            package.append(LFCR);
        }
        package.append(LFCR);
        package.append(_body.begin(), _body.end());
        
        return package;
    }
//    ~HttpResponse();
};

#endif /* HTTPRESPONSE_H */
