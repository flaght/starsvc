//  Copyright (c) 2015-2016 The KID Authors. All rights reserved.
//  Created on: 2016.2.18 Author: yangge

#include "push/push_kafka.h"
#include "basic/basic_util.h"
#include "basic/radom_in.h"
#include "basic/template.h"
#include "logic/logic_comm.h"
#include "logic/logic_unit.h"
#include "logic/time.h"
#include <mysql.h>
#include <set>
#include <sstream>

void PushMsgConsume (rd_kafka_message_t *rkmessage, void *opaque){
  
}

namespace push_logic {

CPushKafka::CPushKafka(config::FileConfig *config) {
  /* if (CONSUMER_INIT_SUCCESS
   != kafka_consumer_.Init(
   0,
   "kafka_newsparser_algo",
   "192.168.1.85:9091,192.168.1.80:9091,192.168.1.81:9091",
   NULL))*/

  LOG_DEBUG2("config kafka_list_ size:[%d]", config->kafka_list_.size());
  for(std::list<base::ConnAddr>::iterator it = config->kafka_list_.begin();
          it != config->kafka_list_.end(); ++it) {
    base::ConnAddr addr = (*it);
    if (CONSUMER_INIT_SUCCESS
        != kafka_consumer_.Init(addr)){
      LOG_DEBUG2("consumer init failed: host:%s source %s additional %s",
               addr.host().c_str(), addr.source().c_str(),addr.additional().c_str());
    }
    else{
      LOG_DEBUG2("consumer init success: host:%s source %s additional %s",
             addr.host().c_str(), addr.source().c_str(),addr.additional().c_str());
      break;
    }
    
  }
}

CPushKafka::CPushKafka(const int32 svc_id, base::ConnAddr& addr) {
    std::string source = addr.source() + "_" + base::BasicUtil::StringUtil::Int64ToString(svc_id);
    base::ConnAddr new_addr(svc_id, addr.host(), addr.port(),
                            addr.usr(), addr.pwd(),source);

    if (CONSUMER_INIT_SUCCESS != kafka_consumer_.Init(new_addr))
        LOG_MSG("kafka consumer kafka_task_algo init failed");
    else
        LOG_MSG("kafka consumer kafka_task_algo init success");
}

CPushKafka::~CPushKafka() {
    kafka_consumer_.Close();
    LOG_MSG("~CPushKafka()");
}

bool CPushKafka::FectchBatchTask(std::list<base_logic::DictionaryValue*> *list) {

    std::set < std::string > data_list;
    std::string data;
    for (int i = 0; i < 1000; i++) {
        int pull_re = kafka_consumer_.PullData(data);
        if (CONSUMER_CONFIG_ERROR == pull_re) {
            LOG_DEBUG2("CONSUMER_CONFIG_ERROR,pull_re=%d", pull_re);
        }
        if (PULL_DATA_DATA_NULL == pull_re) {
            break;
        }
        if (PULL_DATA_TIMEOUT == pull_re) {
            LOG_DEBUG2("consumer get url timeout,pull_re=%d", pull_re);
            break;
        }
        data_list.insert(data);
    }
    LOG_DEBUG2("data_list size[%d]", data_list.size());

    for (std::set<std::string>::iterator it = data_list.begin();
            it != data_list.end(); it++) {
        std::string data = *it;
        LOG_DEBUG2("%s",data.c_str());
        base_logic::ValueSerializer *engine = base_logic::ValueSerializer::Create(
                0, &data);
        int error_code = 0;
        std::string error_str;
        base_logic::Value *value = engine->Deserialize(&error_code, &error_str);
        if (0 != error_code || NULL == value)
            continue;
        base_logic::DictionaryValue *task_info_dic =
            (base_logic::DictionaryValue *) value;
        list->push_back(task_info_dic);
        base_logic::ValueSerializer::DeleteSerializer(0, engine);
    }  // LOG_DEBUG2("update task info, total task num:%d", list->size());
    return true;

}

}  // namespace push_logic
