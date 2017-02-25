/******************************************************************************
 ***** File Name : HttpRequest.cpp
 **** Created By : kyaz758
 *** Description :
 * Creation Date : 2017-02-17 11:22
 * Last Modified : 2017-02-17 13:24
 ******************************************************************************/

#include "HttpRequest.hpp"
#include <sys/socket.h>
#include <sys/types.h>

void HttpRequest::readData()
{
    uint8_t buf[1024];
again:
    int ret = recv(_clientFd, buf, 1024, 0);
    if (ret == -1)
    {
        if (errno == EINTR)
            goto again;
        return ;
    }
    if (ret == 0)
    {
        _isreadable = false;
        return ;
    }
    _buf.append((char *)buf, ret);
}

bool HttpRequest::isHasNextLine()
{
    while (1) 
    {
        if (!_isreadable)
            return false;
        if (_buf.find("\r\n") == std::string::npos)
            readData();
        else 
          return true;
    }
    /*
    while (_buf.find("\r\n") && _isreadable) 
    {
        readData(); //按需加载，惰性求值（避免无意义的计算）
    }
    return _buf.find("\r\n") != -1;
    */
}

std::string HttpRequest::getNextLine()
{
    std::string line = _buf.substr(0, _buf.find("\r\n"));
    _buf.erase(0, line.length()+2);
    return line;
}


