#pragma once



#include "http_proxy_server_t.h"

class proxy_server_t : 
    public singleton<proxy_server_t>,
    public inet_tcp_handler
{
public:
    proxy_server_t(void);
    ~proxy_server_t(void);

    bool start() ;

protected:
    virtual bool on_connect(net_conn_ptr pConn, bool bConnected = true) ;
    virtual bool on_disconnect(net_conn_ptr pConn) ;
    virtual bool on_read(net_conn_ptr pConn, const char* buff, size_t len) ;
    virtual bool on_write(net_conn_ptr pConn, size_t len) ;
    virtual bool on_accept(net_conn_ptr pListen, net_conn_ptr pNewConn, bool bSuccess = true) ;

protected:
    proxy_server_i* http_proxy_;

};

