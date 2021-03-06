
#ifndef SWP_IMCLOUD_IM_LOGIC_
#define SWP_IMCLOUD_IM_LOGIC_

#include "basic/basictypes.h"
#include "core/common.h"
#include "net/comm_head.h"
#include "net/packet_processing.h"
#include "manager/data_share_mgr.h"
#include "im_mysql.h"
namespace im_logic {

class Imlogic {
 public:
  Imlogic();
  virtual ~Imlogic();
 private:
  bool OnQutations(struct server* srv, int socket, struct PacketHead *packet);
 private:
  static Imlogic *instance_;
  im_mysql::Im_Mysql *sqlengine;
 public:
  static Imlogic *GetInstance();
  static void FreeInstance();
  bool OnImConnect(struct server *srv, const int socket);

  bool OnImMessage(struct server *srv, const int socket, const void *msg,
                        const int len);

  bool OnImClose(struct server *srv, const int socket);

  bool OnBroadcastConnect(struct server *srv, const int socket,
                          const void *data, const int len);

  bool OnBroadcastMessage(struct server *srv, const int socket, const void *msg,
                          const int len);

  bool OnBroadcastClose(struct server *srv, const int socket);

  bool OnIniTimer(struct server *srv);

  bool OnTimeout(struct server *srv, char *id, int opcode, int time);

  bool OnRegisterImcloud(struct server* srv,int socket ,struct PacketHead* packet);
  
  bool OnLoginImcloud(struct server* srv,int socket ,struct PacketHead* packet);

  bool OnGetTokenImcloud(struct server* srv,int socket ,struct PacketHead* packet);

  bool OnRefreshTokenImcloud(struct server* srv,int socket ,struct PacketHead* packet);

  bool OnAddCloudFriend(struct server* srv,int socket ,struct PacketHead* packet);
  
  bool OnDelCloudFriend(struct server* srv,int socket ,struct PacketHead* packet);

  bool OnGetFriendList(struct server* srv,int socket ,struct PacketHead* packet);

  bool OnEditFriendInfo(struct server* srv,int socket ,struct PacketHead* packet);

  //明星发送消息处理，需要扣除订购者的时间
  bool OnStarSendMessage(struct server* srv,int socket ,struct PacketHead* packet);
 private:
  bool Init();
};
}  // namespace im_logic

#endif
