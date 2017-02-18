# 网络编程

## 头文件
- <sys/soket.h> 
- <sys/types.h> 
- <arpa/inet.h>

## API
- socket(

    > 具体操作
    <pre><code>struct sockaddr_in socketAddr;
    bzero(&socketAddr, sizeof(socketAddr));
    socketAddr.sin_family = AF_INET;
    inet_pton(AF_INET, IP, &(socketAddr.sin_addr.s_addr));
    socketAddr.sin_port = htons(PORT);</code></pre>

- bind(  

- listen(  

    > listen操作的意义：转换socket的状态，因为accept无法接收主动状态的socket
    > 其第二个参数(second argument) backlog的意义:
    > - 已经完成链接，但还未被accept接收的socket，存放于队列中，参数指定此队列大小
    > - 一般超出其大小会导致操作失败，但有些实现具有重连机制，会延迟报错，等待成功
- accept(  

    > 首先，无法接收主动状态的socket，需要listen先进行转换
    > 其次，socket状态的设置意义：主动状态的socekt无需存放队列或其他系统资源来建立链接
    > accept进行的时间：在三次握手第二次时就已经建立了链接，已经可以携带将要传输的数据了

### Last_lesson

> 证明 形式化的符号工具
>
> 《程序设计语言理论》
> 函数是编程lisp是历史上的第一个实现GC的高级语言

> effctive C++
> 视C++为一个语言联邦

> 视硬件为一个函数库 乱序执行
> 操作系统 -> 软件架构（CPU）软件和硬件打交道（硬件底层支持、cpu电路支持）

> 程序理论 图灵机 什么问题是可计算的，对象范围

> 自动机理论 可计算性理论 计算复杂性理论（心法） 任督二脉

> 图灵完备 （原型转化---集群计算---GPU计算）
> 人工智障------>机械姬
> 计算机永远是交叉学科，和任何学科融合 （自然语言——计算机——数学）
> 功不唐捐（一切一点点努力都不会白费）
> 数学 TODU    
