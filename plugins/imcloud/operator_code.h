#ifndef SWP_IMCLOUD_OPERATOR_CODE_H_
#define SWP_IMCLOUD_OPERATOR_CODE_H_


#include "net/comm_head.h"
#include "comm/comm_head.h"


namespace users_logic {
#define R_IMCLOUD_REGISTER    IM_TYPE * 1000 + 1
#define S_IMCLOUD_REGISTER    IM_TYPE * 1000 + 2

#define R_IMCLOUD_LOGIN  IM_TYPE * 1000 + 3
#define S_IMCLOUD_LOGIN  IM_TYPE * 1000 + 4

#define R_IMCLOUD_GETTOKEN IM_TYPE * 1000 + 5
#define S_IMCLOUD_GETTOKEN IM_TYPE * 1000 + 6

#define R_IMCLOUD_REFRESHTOKEN IM_TYPE * 1000 + 7
#define S_IMCLOUD_REFRESHTOKEN IM_TYPE * 1000 + 8

#define R_IMCLOUD_ADDFRIEND IM_TYPE * 1000 + 9
#define S_IMCLOUD_ADDFRIEND IM_TYPE * 1000 + 10

#define R_IMCLOUD_DELFRIEND IM_TYPE * 1000 + 11
#define S_IMCLOUD_DELFRIEND IM_TYPE * 1000 + 12

#define R_IMCLOUD_GETFRIENDLIST IM_TYPE * 1000 + 13
#define S_IMCLOUD_GETFRIENDLIST IM_TYPE * 1000 + 14

#define R_IMCLOUD_EDITFRIENDINFO IM_TYPE * 1000 + 15
#define S_IMCLOUD_EDITFRIENDINFO IM_TYPE * 1000 + 16

#define R_IMCLOUD_SENDMESSAGE IM_TYPE * 1000 + 17
#define S_IMCLOUD_SENDMESSAGE IM_TYPE * 1000 + 18


}
#endif