#pragma once

#include "net_socket.h"

class net_conn;
class inet_tcp_handler;

///< 网络接口类
class inetwork
{
public:
    inetwork(void) {}
    virtual ~inetwork(void) {}

public:
    ///< 初始化网络层接口，由tcp_net_facade调用
    virtual bool init_network(inet_tcp_handler* handler, size_t thread_num = 1) = 0; 

    ///< 设置连接超时时间
    virtual bool set_conn_timeout(size_t tm_seconds) = 0;

    ///< 运行网络层，创建线程这些
    virtual bool run_network() = 0;

    ///< 在建立的连接上投递一个读请求
    virtual bool try_read(net_conn* pConn) = 0;

    ///< 投递一个写请求
    virtual bool try_write(net_conn* pconn, const char* buff, size_t len) = 0;

    ///< 创建获取监听套接口
    virtual net_conn* try_listen(USHORT uLocalPort) = 0;
    
    ///< 投递连接到服务器
    virtual net_conn* try_connect(const char* addr, USHORT uport, void* bind_key = NULL) = 0;
};