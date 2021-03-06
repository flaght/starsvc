
#ifndef PLUGINS_MARKET_MYSQL_H_
#define PLUGINS_MARKET_MYSQL_H_

#include "config/config.h"
#include "basic/basictypes.h"
#include "logic/star_infos.h"
#include "storage/data_engine.h"
#include "net/typedef.h"

namespace market_mysql {

class Market_Mysql {
 public:
  Market_Mysql(config::FileConfig* config);
  ~Market_Mysql();
  
  bool getmarketstartransfer(const std::string& code,int64 startnum,int64 endnum,DicValue &ret);
  static void callgetmarketstartransfer(void* param, base_logic::Value* value);
  
  bool getmarketstarseek(const std::string& code,int64 startnum,int64 endnum,DicValue &ret);
  static void callgetmarketstarseek(void* param, base_logic::Value* value);
  
  bool addoptionstar(const std::string& phone,const std::string& starcode);
  static void calladdoptionstar(void* param, base_logic::Value* value);
  
  bool getoptionstarlist(const std::string& code,int64 startnum,int64 endnum,DicValue &ret);
  
  static void callgetoptionstarlist(void* param, base_logic::Value* value);
  
  bool addstarinfo(const std::string& code,
  						const std::string& phone,
  						const std::string& name,
  						const int64 gender,
  						const std::string& brief_url,
  						const double price,
  						const std::string& accid,
  						const std::string& picurl);
  bool getstarachive(const std::string& code,DicValue &ret);
  static void callgetstarachive(void* param, base_logic::Value* value);

  bool getstarexperience(const std::string& code,DicValue &ret);
  static void callgetstarexperience(void* param, base_logic::Value* value);
  
  bool searchstarlist(const std::string& code,DicValue &ret);
  static void callsearchstarlist(void* param, base_logic::Value* value);
  
  bool getstarbrief(const std::string& code,DicValue &ret);
  static void callgetstarbrief(void* param, base_logic::Value* value);
  
  bool getmarkettypes(DicValue &ret);
  static void callgetmarkettypes(void* param, base_logic::Value* value);

  bool getmarketstarlist(int64& type,DicValue &ret,int64& startnum,int64& endnum,int64 sorttype);
  static void callgetmarketstarlist(void* param, base_logic::Value* value);
  //获取明星信息
  bool getstarinfo(const std::string& code,const std::string& phone,DicValue &ret,int64 all);

  //获取banner信息
  bool getbannerinfo(const std::string& code,DicValue &ret,int64 all);
  
  //获取预约明星列表
  bool getorderstarinfo(const std::string& code,const std::string& phone,DicValue &ret);

  //获取咨询列表
  bool getstarnews(const std::string& code,const std::string& name,DicValue &ret,
  					int64& startnum,int64& endnum,int64& all);
 //add bytw  
  bool OnStarsInfo(std::list<star_logic::StarInfo>* list);//更新缓存内容 
  bool OnStarsbrief(std::list<star_logic::StarBrief>* list);//更新缓存内容 

  static void CallStarInfo(void* param, base_logic::Value* value);
  static void CallStarbrief(void* param, base_logic::Value* value);
 //end add
  static void Callpublicback(void* param, base_logic::Value* value);
  
  static void Callgetinfo(void* param, base_logic::Value* value);

  static void Callgetbannerinfo(void* param, base_logic::Value* value);

  static void Callgetorderstarinfo(void* param, base_logic::Value* value);

  static void Callgetstarnewsinfo(void* param, base_logic::Value* value);
  private:
  base_logic::DataEngine* mysql_engine_;
};

}  // namespace 

#endif
