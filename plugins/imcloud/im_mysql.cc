
#include "imcloud/im_mysql.h"

#include <mysql/mysql.h>
#include <sstream>

#include "storage/data_engine.h"
#include "comm/comm_head.h"

#include "logic/logic_comm.h"
#include "basic/basic_util.h"

namespace im_mysql {

Im_Mysql::Im_Mysql(config::FileConfig* config) {
  mysql_engine_ = base_logic::DataEngine::Create(MYSQL_TYPE);
  mysql_engine_->InitParam(config->mysql_db_list_);
}

Im_Mysql::~Im_Mysql() {
  if (mysql_engine_) {
    delete mysql_engine_;
  }
  mysql_engine_ = NULL;
}
//写用户信息
int32 Im_Mysql::SetUserInfo(int64 userid, int64 phonenum, std::string name,std::string accid,std::string token,
                        DicValue* dic){
  int32 err = 0;
  bool r = false;
  do {
    std::string sql;

    sql = "call star_addcloudinfo("
      + base::BasicUtil::StringUtil::Int64ToString(userid) + ","
      + base::BasicUtil::StringUtil::Int64ToString(phonenum) + ",'"
      + name + "','"
      + accid + "','"
      + token + "'" + ");";

    //std::string m_sql = "call star_addcloudinfo(123,1770640,'m_name','m_accid')";
    dic->SetString(L"sql", sql);
    LOG_DEBUG2("%s", sql.c_str());
    r = mysql_engine_->ReadData(0, (base_logic::Value*) (dic),NULL);
    if (!r) {
      err = SQL_EXEC_ERR;
      break;
    }
    if (dic->empty()) {
      err = PHONE_OR_PASSWD_ERR;
      break;
    }
  } while (0);

  return err;
}
//读用户信息
int32 Im_Mysql::GetStaticInfo(int64 phonenum,  DicValue* dic) {
  int32 err = 0;
  bool r = false;
  do {
    std::string sql;
    sql = "call star_getcloudinfo("
      + base::BasicUtil::StringUtil::Int64ToString(phonenum)
      +  ");";
    dic->SetString(L"sql", sql);
    LOG_DEBUG2("%s", sql.c_str());
    r = mysql_engine_->ReadData(0, (base_logic::Value*) (dic),
                                CallStaticSelect);
    if (!r) {
      err = SQL_EXEC_ERR;
      break;
    }
    if (dic->empty()) {
      err = PHONE_OR_PASSWD_ERR;
      break;
    }
  } while (0);
  base_logic::DictionaryValue *userinfo = NULL;
  dic->GetDictionary(L"userinfo", &userinfo);
  std::string username;
  std::string accid;
  std::string tokenvalue;
  userinfo->GetString(L"username", &username);
  userinfo->GetString(L"accid", &accid);
  userinfo->GetString(L"tokenvalue", &tokenvalue);
  LOG_DEBUG2("li============%s,%s",username.c_str(),accid.c_str(),tokenvalue.c_str());
  return err;
}
void Im_Mysql::CallStaticSelect(void* param, base_logic::Value* value) {
  base_storage::DBStorageEngine* engine =
      (base_storage::DBStorageEngine*) (param);
  MYSQL_ROW rows;
  int32 num = engine->RecordCount();

  base_logic::DictionaryValue *userinfo = new base_logic::DictionaryValue();
  DicValue* dict = reinterpret_cast<DicValue*>(value);
  if (num > 0) {
    while (rows = (*(MYSQL_ROW*) (engine->FetchRows()->proc))) {
      if (rows[0] != NULL)
        userinfo->SetString(L"username", rows[0]);
      if (rows[1] != NULL)
        userinfo->SetString(L"accid", rows[1]);
      if (rows[2] != NULL)
        userinfo->SetString(L"tokenvalue", rows[2]);
      dict->Set(L"userinfo", (base_logic::Value *) (userinfo));
    }
  } else {
    LOG_ERROR ("CallUserLoginSelect count < 0");
  }
  dict->Remove(L"sql", &value);
}
bool Im_Mysql::ReduceTalkingtimes(std::string& accid,std::string& faccid){
	bool r = false;
	DicValue dic;
	std::string sql;
	sql = "call proc_reducetalkingseconds('"
	  + accid 
	  + "','" + faccid 
	  +  "');";
	dic.SetString(L"sql", sql);
	LOG_DEBUG2("%s", sql.c_str());
	r = mysql_engine_->ReadData(0, (base_logic::Value*) (&dic),
	                            Callreducetalkingtimes);
	if (!r || dic.empty()) {
	  return false;
	}

	base_logic::DictionaryValue *ret = new base_logic::DictionaryValue();
	int64 result;
	bool r1 = dic.GetDictionary(L"resultvalue", &ret);
	bool r2 = ret->GetBigInteger(L"result", &result);
	if(r1 && r2){
		if(result == 1)
			return true;
	}
	return false;
}
void Im_Mysql::Callreducetalkingtimes(void* param, base_logic::Value* value){
	base_storage::DBStorageEngine* engine =
	  (base_storage::DBStorageEngine*) (param);
	MYSQL_ROW rows;
	int32 num = engine->RecordCount();

	base_logic::DictionaryValue *ret = new base_logic::DictionaryValue();
	DicValue* dict = reinterpret_cast<DicValue*>(value);
	if (num > 0) {
	while (rows = (*(MYSQL_ROW*) (engine->FetchRows()->proc))) {
	  if (rows[0] != NULL){
	  		ret->SetBigInteger(L"result", atoi(rows[0]));
	  		dict->Set(L"resultvalue", (base_logic::Value *) (ret));
	  	}
	}
	}
	else {
		LOG_ERROR ("CallUserLoginSelect count < 0");
	}
	dict->Remove(L"sql", &value);
}


}

