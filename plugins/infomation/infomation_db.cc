
#include <mysql/mysql.h>
#include <sstream>

#include "storage/data_engine.h"
#include "comm/comm_head.h"

#include "logic/logic_comm.h"
#include "basic/basic_util.h"
#include "infomation_db.h"

namespace infomation_mysql {

Infomation_Mysql::Infomation_Mysql(config::FileConfig* config) {
  mysql_engine_ = base_logic::DataEngine::Create(MYSQL_TYPE);
  mysql_engine_->InitParam(config->mysql_db_list_);
}

Infomation_Mysql::~Infomation_Mysql() {
  if (mysql_engine_) {
    delete mysql_engine_;
  }
  mysql_engine_ = NULL;
}
void Infomation_Mysql::Callgetfanscomments(void* param, base_logic::Value* value){
	base_storage::DBStorageEngine* engine =
	  (base_storage::DBStorageEngine*) (param);
	MYSQL_ROW rows;
	int32 num = engine->RecordCount();
	base_logic::ListValue *list = new base_logic::ListValue();
	
	DicValue* dict = reinterpret_cast<DicValue*>(value);
	int64 startnum;
	dict->GetBigInteger(L"startnum",&startnum);
	int64 endnum;
	dict->GetBigInteger(L"endnum",&endnum);
	LOG_MSG2("starnum = %d,endnum = %d",startnum,endnum);
	if (num > 0) {

	int count = 1;
	while (rows = (*(MYSQL_ROW*) (engine->FetchRows()->proc))) {
	  base_logic::DictionaryValue *ret = new base_logic::DictionaryValue();
	  if (rows[0] != NULL){
			ret->SetString(L"comment", rows[0]);
		}
	  if (rows[1] != NULL){
			ret->SetString(L"times", rows[1]);
		}
	  if (rows[2] != NULL){
			ret->SetString(L"nickname", rows[2]);
		}
	  if (rows[3] != NULL){
			ret->SetString(L"headurl", rows[3]);
		}
	  if(count >= startnum && count <= endnum){
			list->Append((base_logic::Value *) (ret));
	  }
	  count++;
	}
	dict->SetInteger(L"totalnum",num);
	dict->Set(L"resultvalue", (base_logic::Value *) (list));
	}
	else {
		LOG_ERROR ("CallUserLoginSelect count < 0");
	}
	dict->Remove(L"sql", &value);
}
bool Infomation_Mysql::getfanscomments(const std::string& starcode,DicValue &ret_result,int64& startnum,int64& endnum){
	bool r = false;
    DicValue* dic = new DicValue();
	std::string sql;
	
	sql = "call proc_getfanscomments('"+ starcode +  "');";
	dic->SetBigInteger(L"startnum", startnum);
	dic->SetBigInteger(L"endnum", endnum);

	
	dic->SetString(L"sql", sql);
	LOG_DEBUG2("%s", sql.c_str());
	r = mysql_engine_->ReadData(0, (base_logic::Value*) (dic),Callgetfanscomments);
	if (!r) {
	  return false;
	}
	int64 result;
	int32 num;
	base_logic::ListValue *listvalue;
	if(!dic->GetInteger(L"totalnum",&num))
		return false;
	r = dic->GetList(L"resultvalue",&listvalue);
	if(r && listvalue->GetSize()>0){
		
	    ret_result.Set("list",(base_logic::Value*)listvalue);
		ret_result.SetInteger(L"totalnum",num);
		return true;
	}
	return false;
}
bool Infomation_Mysql::getstarnews(const std::string& code,const std::string& name,DicValue &ret_result,
								   int64& startnum,int64& endnum,int64& all){
	bool r = false;
    DicValue* dic = new DicValue();
	std::string sql;
	if(all == 0){
	  sql = "call proc_getstarnewsinfo('"
	  + code + "','"
	  + name +  "');";
	}else{
	  sql = "call proc_getallstarnewsinfo()";
	  dic->SetBigInteger(L"startnum", startnum);
	  dic->SetBigInteger(L"endnum", endnum);
	}
	
	dic->SetString(L"sql", sql);
	LOG_DEBUG2("%s", sql.c_str());
	r = mysql_engine_->ReadData(0, (base_logic::Value*) (dic),Callgetstarnewsinfo);
	if (!r) {
	  return false;
	}
	int64 result;
	base_logic::ListValue *listvalue;
	r = dic->GetList(L"resultvalue",&listvalue);
	if(r && listvalue->GetSize()>0){
		
	    ret_result.Set("list",(base_logic::Value*)listvalue);
		return true;
	}
	return false;
}
bool Infomation_Mysql::getorderstarinfo(const std::string& code,const std::string& phone,DicValue &ret_result){
	bool r = false;
    DicValue* dic = new DicValue();
	std::string sql;
	sql = "call proc_getorderstarinfo('"
	  + code + "','"
	  + phone +  "');";

	dic->SetString(L"sql", sql);
	LOG_DEBUG2("%s", sql.c_str());
	r = mysql_engine_->ReadData(0, (base_logic::Value*) (dic),Callgetorderstarinfo);
	if (!r) {
	  return false;
	}
	int64 result;
	base_logic::ListValue *listvalue;
	r = dic->GetList(L"resultvalue",&listvalue);
	if(r && listvalue->GetSize()>0){
		
	    ret_result.Set("list",(base_logic::Value*)listvalue);
		return true;
	}
	return false;
}

void Infomation_Mysql::Callgetstarnewsinfo(void* param, base_logic::Value* value){
	base_storage::DBStorageEngine* engine =
	  (base_storage::DBStorageEngine*) (param);
	MYSQL_ROW rows;
	int32 num = engine->RecordCount();
	base_logic::ListValue *list = new base_logic::ListValue();
	
	DicValue* dict = reinterpret_cast<DicValue*>(value);
	int64 startnum;
	dict->GetBigInteger(L"startnum",&startnum);
	int64 endnum;
	dict->GetBigInteger(L"endnum",&endnum);
	LOG_MSG2("starnum = %d,endnum = %d",startnum,endnum);
	if (num > 0) {

	int count = 1;
	while (rows = (*(MYSQL_ROW*) (engine->FetchRows()->proc))) {
	  base_logic::DictionaryValue *ret = new base_logic::DictionaryValue();
	  if (rows[0] != NULL){
			ret->SetBigInteger(L"id", atoi(rows[0]));
		}
	  if (rows[1] != NULL){
			ret->SetString(L"starname", rows[1]);
		}
	  if (rows[2] != NULL){
			ret->SetString(L"starcode", rows[2]);
		}
	  if (rows[3] != NULL){
			ret->SetString(L"showpic_url", rows[3]);
		}
	  if (rows[4] != NULL){
			ret->SetString(L"subject_name", rows[4]);
		}
	  if (rows[5] != NULL){
			ret->SetString(L"link_url", rows[5]);
		}
	  if (rows[6] != NULL){
			ret->SetString(L"remarks", rows[6]);
		}
	  if (rows[7] != NULL){
			ret->SetString(L"times", rows[7]);
		}
	  if(count >= startnum && count <= endnum){
			list->Append((base_logic::Value *) (ret));
	  }
	  count++;
	}
	dict->Set(L"resultvalue", (base_logic::Value *) (list));
	}
	else {
		LOG_ERROR ("CallUserLoginSelect count < 0");
	}
	dict->Remove(L"sql", &value);
}

void Infomation_Mysql::Callgetorderstarinfo(void* param, base_logic::Value* value){
	base_storage::DBStorageEngine* engine =
	  (base_storage::DBStorageEngine*) (param);
	MYSQL_ROW rows;
	int32 num = engine->RecordCount();
	base_logic::ListValue *list = new base_logic::ListValue();
	
	DicValue* dict = reinterpret_cast<DicValue*>(value);
	if (num > 0) {
	while (rows = (*(MYSQL_ROW*) (engine->FetchRows()->proc))) {
	  base_logic::DictionaryValue *ret = new base_logic::DictionaryValue();
	  if (rows[0] != NULL){
			ret->SetString(L"starname", rows[0]);
		}
	  if (rows[1] != NULL){
			ret->SetString(L"faccid", rows[1]);
		}
	  if (rows[2] != NULL){
			ret->SetString(L"starcode", rows[2]);
		}
	  if (rows[3] != NULL){
			ret->SetBigInteger(L"ownseconds", atoi(rows[3]));
		}
	  list->Append((base_logic::Value *) (ret));
	}
	dict->Set(L"resultvalue", (base_logic::Value *) (list));
	}
	else {
		LOG_ERROR ("CallUserLoginSelect count < 0");
	}
	dict->Remove(L"sql", &value);
}
bool Infomation_Mysql::getbannerinfo(const std::string& code,DicValue &ret_result,int64 all){
	bool r = false;
    DicValue* dic = new DicValue();
	std::string sql;
    if(all==0){
		sql = "call proc_getbannerinfo('"
	  + code +  "');";
	}else
		sql = "call proc_getbannerinfoall()";
	
    
	dic->SetString(L"sql", sql);
	LOG_DEBUG2("%s", sql.c_str());
	r = mysql_engine_->ReadData(0, (base_logic::Value*) (dic),Callgetbannerinfo);
	if (!r) {
	  return false;
	}
	int64 result;
	base_logic::ListValue *listvalue;
	r = dic->GetList(L"resultvalue",&listvalue);
	if(r && listvalue->GetSize()>0){
	    ret_result.Set("list",(base_logic::Value*)listvalue);
		return true;
	}
	return false;
}
void Infomation_Mysql::Callgetbannerinfo(void* param, base_logic::Value* value){
	base_storage::DBStorageEngine* engine =
	  (base_storage::DBStorageEngine*) (param);
	MYSQL_ROW rows;
	int32 num = engine->RecordCount();
	base_logic::ListValue *list = new base_logic::ListValue();
	
	DicValue* dict = reinterpret_cast<DicValue*>(value);
	if (num > 0) {
	while (rows = (*(MYSQL_ROW*) (engine->FetchRows()->proc))) {
	  base_logic::DictionaryValue *ret = new base_logic::DictionaryValue();
	  if (rows[0] != NULL){
			ret->SetString(L"code", rows[0]);
		}
	  if (rows[1] != NULL){
			ret->SetString(L"pic_url", rows[1]);
		}
	  if (rows[2] != NULL){
			ret->SetBigInteger(L"type", atoi(rows[2]));
		}
	  if (rows[3] != NULL){
			ret->SetString(L"name", rows[3]);
		}
	  list->Append((base_logic::Value *) (ret));
	}
	dict->Set(L"resultvalue", (base_logic::Value *) (list));
	}
	else {
		LOG_ERROR ("CallUserLoginSelect count < 0");
	}
	dict->Remove(L"sql", &value);
}

bool Infomation_Mysql::getstarinfo(const std::string& code,const std::string& phone,DicValue &ret_result,int64 all){
  bool r = false;
  DicValue* dic = new DicValue();
  std::string sql;
    if(all==0){
		sql = "call proc_getstarinfo('"
	  + code + "','"
	  + phone +  "');";
	}else{
    sql = "call proc_getstarinfoall()";
  }
  
  
	dic->SetString(L"sql", sql);
	LOG_DEBUG2("%s", sql.c_str());
	r = mysql_engine_->ReadData(0, (base_logic::Value*) (dic),Callgetinfo);
	if (!r) {
	  return false;
	}
	int64 result;
	base_logic::ListValue *listvalue;
	r = dic->GetList(L"resultvalue",&listvalue);
	if(r && listvalue->GetSize()>0){
	    ret_result.Set("list",(base_logic::Value*)listvalue);
		return true;
	}
	return false;
}
void Infomation_Mysql::Callgetinfo(void* param, base_logic::Value* value){
	base_storage::DBStorageEngine* engine =
	  (base_storage::DBStorageEngine*) (param);
	MYSQL_ROW rows;
	int32 num = engine->RecordCount();
    base_logic::ListValue *list = new base_logic::ListValue();
	
	DicValue* dict = reinterpret_cast<DicValue*>(value);
	if (num > 0) {
	while (rows = (*(MYSQL_ROW*) (engine->FetchRows()->proc))) {
	  base_logic::DictionaryValue *ret = new base_logic::DictionaryValue();
	  if (rows[0] != NULL){
	  		ret->SetString(L"code", rows[0]);
	  	}
	  if (rows[1] != NULL){
	  		ret->SetString(L"phone", rows[1]);
	  	}
	  if (rows[2] != NULL){
	  		ret->SetString(L"name", rows[2]);
	  	}
	  if (rows[3] != NULL){
	  		ret->SetBigInteger(L"gender", atoi(rows[3]));
	  	}
	  if (rows[4] != NULL){
	  		ret->SetString(L"brief", rows[4]);
	  	}
	  if (rows[5] != NULL){
	  		ret->SetBigInteger(L"price", atoi(rows[5]));
	  	}
	  if (rows[6] != NULL){
	  		ret->SetString(L"accid", rows[6]);
	  	}
	  if (rows[7] != NULL){
	  		ret->SetString(L"pic_url", rows[7]);
	  	}
    if (rows[8] != NULL){
	  		ret->SetString(L"pic1", rows[8]);
	  	}
	  //dict->Set(L"resultvalue", (base_logic::Value *) (ret));
	  list->Append((base_logic::Value *) (ret));
	}
	dict->Set(L"resultvalue", (base_logic::Value *) (list));
	}
	else {
		LOG_ERROR ("Callgetinfo count < 0");
	}
	dict->Remove(L"sql", &value);
}

bool Infomation_Mysql::addstarinfo(const std::string& code,
  						const std::string& phone,
  						const std::string& name,
  						const int64 gender,
  						const std::string& brief_url,
  						const double price,
  						const std::string& accid,
  						const std::string& picurl){
	bool r = false;
    DicValue* dic = new DicValue();
	std::string sql;

	sql = "call proc_addstarinfo('"
	  + code + "','"
	  + phone + "','"
	  + name + "','"
	  + base::BasicUtil::StringUtil::Int64ToString(gender) + "','"
	  + brief_url + "','"
	  + base::BasicUtil::StringUtil::DoubleToString(price) + "','"
	  + accid + "','" + picurl + "');";

	dic->SetString(L"sql", sql);
	LOG_DEBUG2("%s", sql.c_str());
	r = mysql_engine_->ReadData(0, (base_logic::Value*) (dic),Callpublicback);
	if (!r) {
	  return false;
	}
	base_logic::DictionaryValue *ret = new base_logic::DictionaryValue();
	int64 result;
	dic->GetDictionary(L"resultvalue",&ret);
	r = ret->GetBigInteger(L"result", &result);
	if(r && result == 1){
			return true;
	}
	return false;
}
void Infomation_Mysql::Callpublicback(void* param, base_logic::Value* value){
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

bool Infomation_Mysql::getstarservicelist(const std::string& code,DicValue &ret_result){
	bool r = false;
  DicValue* dic = new DicValue();
	std::string sql;
	sql = "call proc_GetStarServiceInfo('"
	  + code + "');";

	dic->SetString(L"sql", sql);
	LOG_DEBUG2("%s", sql.c_str());
	r = mysql_engine_->ReadData(0, (base_logic::Value*) (dic),Callgetstarservicelist);
	if (!r) {
	  return false;
	}
	int64 result;
	base_logic::ListValue *listvalue;
	r = dic->GetList(L"resultvalue",&listvalue);
	if(r && listvalue->GetSize()>0){
	    ret_result.Set("list",(base_logic::Value*)listvalue);
		return true;
	}
	return false;
}

void Infomation_Mysql::Callgetstarservicelist(void* param, base_logic::Value* value){
	base_storage::DBStorageEngine* engine =
	  (base_storage::DBStorageEngine*) (param);
	MYSQL_ROW rows;
	int32 num = engine->RecordCount();
	base_logic::ListValue *list = new base_logic::ListValue();
	
	DicValue* dict = reinterpret_cast<DicValue*>(value);
	if (num > 0) {
		while (rows = (*(MYSQL_ROW*) (engine->FetchRows()->proc))) {
		  base_logic::DictionaryValue *ret = new base_logic::DictionaryValue();
		  if (rows[0] != NULL){
				ret->SetBigInteger(L"mid", atoi(rows[0]));
			}
		  if (rows[1] != NULL){
				ret->SetString(L"url1", rows[1]);
			}
		  if (rows[2] != NULL){
				ret->SetString(L"url2", rows[2]);
			}
		  if (rows[3] != NULL){
				ret->SetString(L"name", rows[3]);
			}
		  if (rows[4] != NULL){
				ret->SetString(L"price", rows[4]);
			}
			list->Append((base_logic::Value *) (ret));
		}
		dict->Set(L"resultvalue", (base_logic::Value *) (list));
	}
	else {
		LOG_ERROR ("Callgetstarservicelist count < 0");
	}
	dict->Remove(L"sql", &value);
}

bool Infomation_Mysql::userorderstarservice(const int64 uid, const std::string& starcode,
  	        const int64 mid,const std::string& cityname,const std::string& appointtime,
  	        const int64 meettype,const std::string& comment){
	bool r = false;
  DicValue* dic = new DicValue();
  base_logic::DictionaryValue *info_value = NULL;
	std::string sql;
	sql = "call proc_UserOrderStarService('"
	  + base::BasicUtil::StringUtil::Int64ToString(uid) + "','"
	  + starcode + "','"
	  + base::BasicUtil::StringUtil::Int64ToString(mid) + "','"
	  + cityname + "','"
	  + appointtime + "','"
	  + base::BasicUtil::StringUtil::Int64ToString(meettype) + "','"
	  + comment + "');";

	dic->SetString(L"sql", sql);
	LOG_DEBUG2("%s", sql.c_str());
	r = mysql_engine_->ReadData(0, (base_logic::Value*) (dic),Calluserorderstarservice);
	if (!r) {
	  return false;
	}
	
	r = dic->GetDictionary(L"resultvalue", &info_value);
	if (!r) {
	  return false;
	}
	int result;
  r = info_value->GetInteger(L"result", &result);
  r = (r && result == 1) ? true : false;
	
	return r;
}

void Infomation_Mysql::Calluserorderstarservice(void* param, base_logic::Value* value){	
	base_logic::DictionaryValue *dict = (base_logic::DictionaryValue *) (value);
  base_storage::DBStorageEngine *engine =
      (base_storage::DBStorageEngine *) (param);
  MYSQL_ROW rows;
  base_logic::DictionaryValue *info_value = new base_logic::DictionaryValue();
  int32 num = engine->RecordCount();
  if (num > 0) {
    while (rows = (*(MYSQL_ROW *) (engine->FetchRows())->proc)) {
      if (rows[0] != NULL)
        info_value->SetInteger(L"result", atoi(rows[0]));
    }
    dict->Set(L"resultvalue", (base_logic::Value *) (info_value));
  }
  else {
		LOG_ERROR ("Calluserorderstarservice count < 0");
	}
  
  dict->Remove(L"sql", &value);
}

bool Infomation_Mysql::getuserstaramount(const int64 uid,int64& num){
	bool r = false;
  DicValue* dic = new DicValue();
	std::string sql;
	sql = "call proc_GetUserStarAmount('"
	  + base::BasicUtil::StringUtil::Int64ToString(uid) + "');";

	dic->SetString(L"sql", sql);
	LOG_DEBUG2("%s", sql.c_str());
	r = mysql_engine_->ReadData(0, (base_logic::Value*) (dic),Callgetuserstaramount);
	if (!r) {
	  return false;
	}
  
  base_logic::DictionaryValue *ret = new base_logic::DictionaryValue();
	bool r1 = dic->GetDictionary(L"resultvalue",&ret);
	bool r2 = ret->GetBigInteger(L"amount", &num);
	if(!r1 || !r2){
	  return false;
	}
	
	return r;
}

void Infomation_Mysql::Callgetuserstaramount(void* param, base_logic::Value* value){	
	base_logic::DictionaryValue *dict = (base_logic::DictionaryValue *) (value);
  base_storage::DBStorageEngine *engine =
      (base_storage::DBStorageEngine *) (param);
  MYSQL_ROW rows;
  base_logic::DictionaryValue *info_value = new base_logic::DictionaryValue();
  int32 num = engine->RecordCount();
  if (num > 0) {
    while (rows = (*(MYSQL_ROW *) (engine->FetchRows())->proc)) {
      if (rows[0] != NULL)
        info_value->SetBigInteger(L"amount", atoi(rows[0]));
    }
    dict->Set(L"resultvalue", (base_logic::Value *) (info_value));
  }
  else {
		LOG_ERROR ("Callgetuserstaramount count < 0");
	}
  
  dict->Remove(L"sql", &value);
}

bool Infomation_Mysql::getuserstartime(const int64 uid, const std::string starcode, int64& time){
	bool r = false;
  DicValue* dic = new DicValue();
	std::string sql;
	sql = "call proc_GetOwnStarTime('"
	  + base::BasicUtil::StringUtil::Int64ToString(uid) + "','"
    + starcode + "');";

	dic->SetString(L"sql", sql);
	LOG_DEBUG2("%s", sql.c_str());
	r = mysql_engine_->ReadData(0, (base_logic::Value*) (dic),Callgetuserstartime);
	if (!r) {
	  return false;
	}
  
  base_logic::DictionaryValue *ret = new base_logic::DictionaryValue();
	bool r1 = dic->GetDictionary(L"resultvalue",&ret);
	bool r2 = ret->GetBigInteger(L"star_time", &time);
	if(!r1 || !r2){
	  return false;
	}
	
	return r;
}

void Infomation_Mysql::Callgetuserstartime(void* param, base_logic::Value* value){	
	base_logic::DictionaryValue *dict = (base_logic::DictionaryValue *) (value);
  base_storage::DBStorageEngine *engine =
      (base_storage::DBStorageEngine *) (param);
  MYSQL_ROW rows;
  base_logic::DictionaryValue *info_value = new base_logic::DictionaryValue();
  int32 num = engine->RecordCount();
  if (num > 0) {
    while (rows = (*(MYSQL_ROW *) (engine->FetchRows())->proc)) {
      if (rows[0] != NULL)
        info_value->SetBigInteger(L"star_time", atoi(rows[0]));
    }
    dict->Set(L"resultvalue", (base_logic::Value *) (info_value));
  }
  else {
		LOG_ERROR ("Callgetuserstartime count < 0");
	}
  
  dict->Remove(L"sql", &value);
}

bool Infomation_Mysql::getstartime(const std::string starcode, int64& time){
	bool r = false;
  DicValue* dic = new DicValue();
	std::string sql;
	sql = "call proc_GetStarTime('"
    + starcode + "');";

	dic->SetString(L"sql", sql);
	LOG_DEBUG2("%s", sql.c_str());
	r = mysql_engine_->ReadData(0, (base_logic::Value*) (dic),Callgetstartime);
	if (!r) {
	  return false;
	}
  
  base_logic::DictionaryValue *ret = new base_logic::DictionaryValue();
	bool r1 = dic->GetDictionary(L"resultvalue",&ret);
	bool r2 = ret->GetBigInteger(L"star_time", &time);
	if(!r1 || !r2){
	  return false;
	}
	
	return r;
}

void Infomation_Mysql::Callgetstartime(void* param, base_logic::Value* value){	
	base_logic::DictionaryValue *dict = (base_logic::DictionaryValue *) (value);
  base_storage::DBStorageEngine *engine =
      (base_storage::DBStorageEngine *) (param);
  MYSQL_ROW rows;
  base_logic::DictionaryValue *info_value = new base_logic::DictionaryValue();
  int32 num = engine->RecordCount();
  if (num > 0) {
    while (rows = (*(MYSQL_ROW *) (engine->FetchRows())->proc)) {
      if (rows[0] != NULL)
        info_value->SetBigInteger(L"star_time", atoi(rows[0]));
    }
    dict->Set(L"resultvalue", (base_logic::Value *) (info_value));
  }
  else {
		LOG_ERROR ("Callgetstartime count < 0");
	}
  
  dict->Remove(L"sql", &value);
}

bool Infomation_Mysql::getUserStarMeetinfo(const int64 uid,const int64 pos,const int64 count,
																	DicValue &ret_result){
	bool r = false;
  DicValue* dic = new DicValue();
	std::string sql;
	sql = "call proc_GetUserStarMeetinfo('"
	  + base::BasicUtil::StringUtil::Int64ToString(uid) + "');";

	dic->SetString(L"sql", sql);
	LOG_DEBUG2("%s", sql.c_str());
	r = mysql_engine_->ReadData(0, (base_logic::Value*) (dic),CallgetUserStarMeetinfo);
	if (!r) {
	  return false;
	}
	int64 result;
	base_logic::ListValue *listvalue;
	r = dic->GetList(L"resultvalue",&listvalue);

	if(r && listvalue->GetSize()>0){
	  int32 t_start = 0;
	  int32 t_count = 0;
	  int32 ipos = pos;
	  int32 icount = count;
	  base_logic::Value* value;
	  base_logic::ListValue *templistvalue = new base_logic::ListValue();

	  while(listvalue->GetSize() > 0){
	  	listvalue->Remove(0, &value);
	  	if(t_start >= ipos && t_count<icount){
	  		templistvalue->Append(value);
	  		++t_count;
	  	}else{
	  		if(value){
        	delete value;
        	value = NULL;
        }
	  	}

	  	++t_start;
	  }
	  LOG_DEBUG2("get size %d,return size %d, pos %ld, count %ld.", 
	  				listvalue->GetSize(),templistvalue->GetSize(),pos,count);

		ret_result.Set("list",(base_logic::Value*)templistvalue);

		if(listvalue){
			delete listvalue;
			listvalue = NULL;
		}
		return true;
	}
	return false;
}

void Infomation_Mysql::CallgetUserStarMeetinfo(void* param, base_logic::Value* value){
	base_storage::DBStorageEngine* engine =
	  (base_storage::DBStorageEngine*) (param);
	MYSQL_ROW rows;
	int32 num = engine->RecordCount();
	base_logic::ListValue *list = new base_logic::ListValue();
	
	DicValue* dict = reinterpret_cast<DicValue*>(value);
	if (num > 0) {
		while (rows = (*(MYSQL_ROW*) (engine->FetchRows()->proc))) {
		  base_logic::DictionaryValue *ret = new base_logic::DictionaryValue();
		  if (rows[0] != NULL){
				ret->SetString(L"star_code", rows[0]);
			}
		  if (rows[1] != NULL){
				ret->SetString(L"star_name", rows[1]);
			}
		  if (rows[2] != NULL){
				ret->SetString(L"star_pic", rows[2]);
			}
		  if (rows[3] != NULL){
				ret->SetBigInteger(L"star_type", atoi(rows[3]));
			}
		  if (rows[4] != NULL){
				ret->SetBigInteger(L"meet_id", atoi(rows[4]));
			}
			if (rows[5] != NULL){
				ret->SetString(L"meet_name", rows[5]);
			}
			if (rows[6] != NULL){
				ret->SetString(L"meet_city", rows[6]);
			}
			if (rows[7] != NULL){
				ret->SetString(L"meet_time", rows[7]);
			}
			if (rows[8] != NULL){
				ret->SetBigInteger(L"meet_type", atoi(rows[8]));
			}
			if (rows[9] != NULL){
				ret->SetString(L"comment", rows[9]);
			}
			
			list->Append((base_logic::Value *) (ret));
		}
		dict->Set(L"resultvalue", (base_logic::Value *) (list));
	}
	else {
		LOG_ERROR ("proc_GetUserStarMeetinfo count < 0");
	}
	dict->Remove(L"sql", &value);
}


bool Infomation_Mysql::OngetOnestarInfo(const std::string& starcode, DicValue* dic){
	bool r = false;
	std::string sql = "call proc_GetOneStarInfo('"
    + starcode + "');";

	dic->SetString(L"sql", sql);
	LOG_DEBUG2("%s", sql.c_str());
	r = mysql_engine_->ReadData(0, (base_logic::Value*) (dic),CallgetOnestarInfo);
	if (!r) {
	  return false;
	}
	
	return r;
}

void Infomation_Mysql::CallgetOnestarInfo(void* param, base_logic::Value* value){	
	base_logic::DictionaryValue *dict = (base_logic::DictionaryValue *) (value);
  base_storage::DBStorageEngine *engine =
      (base_storage::DBStorageEngine *) (param);
  MYSQL_ROW rows;
  base_logic::DictionaryValue *info_value = new base_logic::DictionaryValue();
  int32 num = engine->RecordCount();
  if (num > 0) {
    while (rows = (*(MYSQL_ROW *) (engine->FetchRows())->proc)) {
      if (rows[0] != NULL)
        info_value->SetString(L"star_code", rows[0]);

      if (rows[1] != NULL)
        info_value->SetString(L"star_name", rows[1]);

      if (rows[2] != NULL)
        info_value->SetInteger(L"star_tpye", atoi(rows[2]));

      if (rows[3] != NULL)
        info_value->SetString(L"head_url", rows[3]);

      if (rows[4] != NULL)
        info_value->SetString(L"back_pic", rows[4]);

      if (rows[5] != NULL)
        info_value->SetString(L"portray1", rows[5]);
      if (rows[6] != NULL)
        info_value->SetString(L"portray2", rows[6]);
      if (rows[7] != NULL)
        info_value->SetString(L"portray3", rows[7]);
      if (rows[8] != NULL)
        info_value->SetString(L"portray4", rows[8]);

      if (rows[9] != NULL)
        info_value->SetBigInteger(L"acc_id", atoi(rows[9]));
    }
    dict->Set(L"resultvalue", (base_logic::Value *) (info_value));
  }
  else {
		LOG_ERROR ("proc_GetOneStarInfo count < 0");
	}
  
  dict->Remove(L"sql", &value);
}

bool Infomation_Mysql::OngetSysParamValue(const std::string& paramcode, std::string& retstring){
	bool r = false;
	DicValue* dic = new DicValue();
	std::string sql = "call proc_GetSysParamVlue('"
    + paramcode + "');";

	dic->SetString(L"sql", sql);
	LOG_DEBUG2("%s", sql.c_str());
	r = mysql_engine_->ReadData(0, (base_logic::Value*) (dic),CallgetSysParamValue);
	if (!r) {
	  return false;
	}

	base_logic::DictionaryValue *ret = new base_logic::DictionaryValue();
	bool r1 = dic->GetDictionary(L"resultvalue",&ret);
	r = ret->GetString(L"param_value", &retstring);
	if(!r1 || !r){
	  return false;
	}
	
	return r;
}

void Infomation_Mysql::CallgetSysParamValue(void* param, base_logic::Value* value){	
	base_logic::DictionaryValue *dict = (base_logic::DictionaryValue *) (value);
	base_storage::DBStorageEngine *engine =
      (base_storage::DBStorageEngine *) (param);
	MYSQL_ROW rows;
	base_logic::DictionaryValue *info_value = new base_logic::DictionaryValue();
	int32 num = engine->RecordCount();
	if (num > 0) {
		while (rows = (*(MYSQL_ROW *) (engine->FetchRows())->proc)) {
			if (rows[0] != NULL)
				info_value->SetString(L"param_value", rows[0]);
		
		}
    	dict->Set(L"resultvalue", (base_logic::Value *) (info_value));
  	}
	else {
		LOG_ERROR ("proc_GetSysParamVlue count < 0");
	}
  
	dict->Remove(L"sql", &value);
}

void Infomation_Mysql::Callgetbarragedata(void* param, base_logic::Value* value){
	DicValue* dict = reinterpret_cast<DicValue*>(value);
	base_storage::DBStorageEngine* engine =
	  (base_storage::DBStorageEngine*) (param);
	MYSQL_ROW rows;
	int32 num = engine->RecordCount();
	base_logic::ListValue *list = new base_logic::ListValue();
	
	if (num > 0) {
		while (rows = (*(MYSQL_ROW*) (engine->FetchRows()->proc))) {
		  base_logic::DictionaryValue *info_value = new base_logic::DictionaryValue();
		  if (rows[0] != NULL)
				info_value->SetString(L"user_name", rows[0]);
			
		  if (rows[1] != NULL)
				info_value->SetString(L"head_url", rows[1]);
			
		  if (rows[2] != NULL)
				info_value->SetInteger(L"order_type", atoi(rows[2]));
			
		  if (rows[3] != NULL)
				info_value->SetInteger(L"order_num", atoi(rows[3]));

			if (rows[4] != NULL)
				info_value->SetReal(L"order_price", atof(rows[4]));
			
			list->Append((base_logic::Value *) (info_value));
		}
		dict->Set(L"resultvalue", (base_logic::Value *) (list));
	}
	else {
		LOG_ERROR ("getbarragedata count < 0");
	}
	dict->Remove(L"sql", &value);
}
bool Infomation_Mysql::getbarragedata(int64& startnum,int64& endnum,base_logic::ListValue*& listvalue){
	bool r = false;
	DicValue* dic = new DicValue();
	std::string sql = "select a.user_name,a.head_url,a.order_type,a.order_num,a.order_price from star_barragedata a order by create_time limit "
	+ base::BasicUtil::StringUtil::Int64ToString(startnum) +", "
	+ base::BasicUtil::StringUtil::Int64ToString(endnum) +";";
	
	dic->SetString(L"sql", sql);
	LOG_DEBUG2("%s", sql.c_str());
	r = mysql_engine_->ReadData(0, (base_logic::Value*) (dic),Callgetbarragedata);
	if (!r) {
	  return false;
	}
	
	r = dic->GetList(L"resultvalue",&listvalue);
	return r;
}

}

