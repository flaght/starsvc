//  Copyright (c) 2017-2018 The SWP Authors. All rights reserved.
//  Created on: 2017年2月12日 Author: kerry

#ifndef PAY_SCHDULER_ENGINE_H__
#define PAY_SCHDULER_ENGINE_H__

#include "logic/star_infos.h"
#include "manager/data_share_mgr.h"
#include "pay/pay_proto_buf.h"
#include "pay/pay_db.h"
#include "pay/wx_order.h"
#include "thread/base_thread_handler.h"
#include "thread/base_thread_lock.h"
#include "pay/unionpay_order.h"

namespace pay_logic {

class PayCache {

};

class PayManager {
 public:
  PayManager();
  virtual ~PayManager();
  void InitDB(pay_logic::PayDB* pay_db);
  void InitSchdulerEngine(manager_schduler::SchdulerEngine* schduler_engine);
  void Init();
 public:
  bool OnWXCreateOrder(const int socket, const int64 session,
                       const int32 reversed, const int64 uid,
                       const std::string& title, const double price,const int32 pay_type,
                       const std::string& open_id);

  bool OnUnionPayCreateOrder(const int socket, const int64 session,
                       const int32 reversed, const int64 uid,
                       const std::string& title, const double price,const int32 pay_type,
                       const std::string& open_id);

  bool OnWXClient(const int socket, const int64 session, const int32 reversed,
                  const int64 uid, const int64 rid, const int32 pay_result);

  bool OnWXServer(const int socket, const std::string& appid, const std::string& mch_id,
                  const int64 total_fee, const int64 rid,
                  const int64 result, const std::string& transaction_id);
  bool OnAliPayServer(const int socket, std::string& result );
  bool OnAliPayServer(const int socket, const std::string& appid, const std::string& mch_id,
                  const int64 total_fee, const int64 rid,
                  const int64 result, const std::string& transaction_id);

  bool OnSHFJServer(const int socket, const std::string& appid, const std::string& mch_id,
                  const int64 total_fee, const int64 rid,
                  const int64 result, const std::string& transaction_id);

  bool OnSHFJCashServer(const int socket, const std::string& mch_id, 
			const int64 total_fee, const std::string& transaction_id, 
			const int64 status, const std::string& rid); 
  bool OnAliPayCreateOrder(const int socket, const int64 session,
                       const int32 reversed, const int64 uid,
                       const std::string& title, const double price,const int32 pay_type,
                       const std::string& open_id);
  bool OnCanclePay(const int socket, const int64 uid, const int64 rid);
  bool UnionWithDraw(const int socket, const int64 uid, const int64 rid, const double price, const int session);
 private:
  bool WXOrder(const int socket, const std::string& title, const int64 rid,
               const double price,const int32 pay_type, const std::string& open_id,
               pay_logic::WXOrder& wx_order);

  bool ParserWXOrderResult(std::string& result, std::string& prepay_id);
//---unionpay

  bool UnionPayOrder(const int socket, const std::string& title, const int64 rid,
               const double price,const int32 pay_type, const std::string& open_id,
               pay_logic::UnionpayOrder &unionpay_order);

  bool ParserUnionPayOrderResult(std::string& result);


 private:
  pay_logic::PayDB* pay_db_;
  PayCache *pay_cache_;
  struct threadrw_t *lock_;
  manager_schduler::SchdulerEngine* schduler_engine_;
};

class PayEngine {
 private:
  static PayEngine* schduler_engine_;
  static PayManager* schduler_mgr_;

  PayEngine() {
  }
  virtual ~PayEngine() {
  }
 public:
  static PayManager* GetSchdulerManager() {
    if (schduler_mgr_ == NULL)
      schduler_mgr_ = new PayManager();
    return schduler_mgr_;
  }

  static PayEngine* GetSchdulerEngine() {
    if (schduler_engine_ == NULL)
      schduler_engine_ = new PayEngine();
    return schduler_engine_;
  }

  static void FreeSchdulerManager() {
    if (schduler_mgr_) {
      delete schduler_mgr_;
      schduler_mgr_ = NULL;
    }
  }

  static void FreeSchdulerEngine() {
    if (schduler_engine_) {
      delete schduler_engine_;
      schduler_engine_ = NULL;
    }
  }
};
}

#endif
