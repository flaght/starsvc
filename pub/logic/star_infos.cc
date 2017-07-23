//  Copyright (c) 2015-2015 The quotations Authors. All rights reserved.
//  Created on: 2017年1月3日 Author: kerry

#include "logic/star_infos.h"
#include "basic/template.h"
#include "logic/logic_comm.h"

namespace star_logic {

Auction::Auction() {
    data_ = new Data();
}

Auction::Auction(const Auction& aution)
    : data_(aution.data_) {
    if (data_ != NULL) {
        data_->AddRef();
    }
}

Auction& Auction::operator =(const Auction& auction) {
    if (auction.data_ != NULL) {
        auction.data_->AddRef();
    }

    if (data_ != NULL) {
        data_->Release();
    }

    data_ = auction.data_;
    return (*this);
}



UserInfo::UserInfo() {
    data_ = new Data();
}

UserInfo::UserInfo(const UserInfo& userinfo)
    : data_(userinfo.data_) {
    if (data_ != NULL) {
        data_->AddRef();
    }
}

UserInfo& UserInfo::operator =(const UserInfo& userinfo) {
    if (userinfo.data_ != NULL) {
        userinfo.data_->AddRef();
    }

    if (data_ != NULL) {
        data_->Release();
    }

    data_ = userinfo.data_;
    return (*this);
}

void UserInfo::ValueSerialization(base_logic::DictionaryValue* dict) {
  dict->GetBigInteger(L"uid", &data_->uid_);
  dict->GetReal(L"balance", &data_->balance_);
  dict->GetString(L"phone", &data_->phone_num_);
  dict->GetInteger(L"type", &data_->type_);
  dict->GetInteger(L"gender", &data_->gender_);
  dict->GetString(L"nickname", &data_->nickname_);
  dict->GetString(L"head_url", &data_->head_url_);
  dict->GetString(L"channel", &data_->channel_);
  dict->GetString(L"starcode", &data_->starcode_);
  dict->GetBigInteger(L"token_time", &data_->token_time_);
}



Withdrawals::Withdrawals() {
    data_ = new Data();
}

Withdrawals::Withdrawals(const Withdrawals& withdrawals)
    : data_(withdrawals.data_) {
    if (data_ != NULL) {
        data_->AddRef();
    }
}

Withdrawals& Withdrawals::operator =(const Withdrawals& withdrawals) {
    if (withdrawals.data_ != NULL) {
        withdrawals.data_->AddRef();
    }

    if (data_ != NULL) {
        data_->Release();
    }

    data_ = withdrawals.data_;
    return (*this);
}

void Withdrawals::ValueSerialization(base_logic::DictionaryValue* dict) {
    dict->GetBigInteger(L"uid", &data_->uid_);
    dict->GetBigInteger(L"wid", &data_->wid_);
    dict->GetInteger(L"status", &data_->status_);
    dict->GetReal(L"money",&data_->amount_);
    dict->GetReal(L"charge", &data_->charge_);
    dict->GetBigInteger(L"withdraw_unix_time", &data_->withdraw_unix_time_);
    dict->GetString(L"withdraw_time", &data_->withdraw_time_);
    dict->GetString(L"handle_time", &data_->handle_time_);
    dict->GetString(L"bankName", &data_->bank_);
    dict->GetString(L"branchBank", &data_->branch_bank_);
    dict->GetString(L"account",&data_->card_no_);
    dict->GetString(L"bank_username", &data_->name_);
    dict->GetString(L"comment", &data_->comment_);
}


Recharge::Recharge() {
    data_ = new Data();
}

Recharge::Recharge(const Recharge& recharge)
    : data_(recharge.data_) {
    if (data_ != NULL) {
        data_->AddRef();
    }
}

Recharge& Recharge::operator =(const Recharge& recharge) {
    if (recharge.data_ != NULL) {
        recharge.data_->AddRef();
    }

    if (data_ != NULL) {
        data_->Release();
    }

    data_ = recharge.data_;
    return (*this);
}

void Recharge::ValueSerialization(base_logic::DictionaryValue* dict) {
    dict->GetBigInteger(L"rid", &data_->rid_);
    dict->GetBigInteger(L"uid", &data_->uid_);

    int32 status = 0;
    dict->GetInteger(L"status", &status);
    if (status == 0 ||status == 1)
        data_->status_ = 1;
    else if (status == 3)
        data_->status_ = 2;
    else if (status == 4)
        data_->status_ = 4;
    else
        data_->status_ = 2;

    dict->GetReal(L"amount", &data_->amount_);
    dict->GetString(L"deposit_time", &data_->deposit_time_);
    dict->GetBigInteger(L"deposit_unit_time", &data_->deposit_unix_time_);
    dict->GetInteger(L"deposit_type", &data_->deposit_type_);
    if (data_->deposit_type_ == 1)
        data_->deposit_name_ = "微信";
    else if (data_->deposit_type_ == 2)
        data_->deposit_name_ = "银联";
    else if (data_->deposit_type_ == 3)
        data_->deposit_name_ = "支付宝";
    else
        data_->deposit_name_ = "未知";
    dict->GetInteger(L"recharge_type", &data_->recharge_type_);
    dict->GetString(L"transaction_id", &data_->transaction_id_);
}

TradesOrder::TradesOrder() {
    data_ = new Data();
}

TradesOrder::TradesOrder(const TradesOrder& trades_order)
    : data_(trades_order.data_) {
    if (data_ != NULL) {
        data_->AddRef();
    }
}

TradesOrder& TradesOrder::operator =(
    const TradesOrder& trades_order) {
    if (trades_order.data_ != NULL) {
        trades_order.data_->AddRef();
    }

    if (data_ != NULL) {
        data_->Release();
    }

    data_ = trades_order.data_;
    return (*this);
}


void TradesOrder::ValueSerialization(base_logic::DictionaryValue* dict) {
    int64 big_handle_type = 0;
    int64 big_sell_handle_type = 0;
    int64 big_buy_handle_type = 0;
    dict->GetBigInteger(L"order_id", &data_->order_id_);
    dict->GetBigInteger(L"buy_position_id", &data_->buy_position_id_); 
    dict->GetBigInteger(L"sell_position_id", &data_->sell_position_id_);
    dict->GetBigInteger(L"buy_uid", &data_->buy_uid_);
    dict->GetBigInteger(L"sell_uid", &data_->sell_uid_);
    dict->GetBigInteger(L"amount", &data_->amount_);
    dict->GetBigInteger(L"open_position_time", &data_->open_position_time_);
    dict->GetBigInteger(L"close_position_time", &data_->close_position_time_);
    dict->GetReal(L"gross_profit", &data_->gross_profit_);
    dict->GetReal(L"open_price", &data_->open_price_);
    dict->GetReal(L"open_charge", &data_->open_charge_);
    dict->GetBigInteger(L"handle", &big_handle_type);
    data_->handle_type_ = big_handle_type;
    dict->GetBigInteger(L"sell_handle_type", &big_sell_handle_type);
    data_->sell_handle_type_ = big_sell_handle_type;
    dict->GetBigInteger(L"buy_handle_type", &big_buy_handle_type);
    data_->buy_handle_type_ = big_buy_handle_type;
    dict->GetString(L"symbol",&data_->symbol_);
}


base_logic::DictionaryValue* TradesOrder::GetValue() {
    if (data_ == NULL)
        return NULL;
    base_logic::DictionaryValue* dict = new base_logic::DictionaryValue();
    if (data_->order_id_ != 0)
        dict->SetBigInteger(L"order_id",data_->order_id_);
    if (data_->buy_position_id_ != 0)
        dict->SetBigInteger(L"buy_position_id",data_->buy_position_id_);
    
    if (data_->sell_position_id_ != 0)
        dict->SetBigInteger(L"sell_position_id",data_->sell_position_id_);

    if (data_->buy_uid_ != 0)
        dict->SetBigInteger(L"buy_uid", data_->buy_uid_);

    if (data_->sell_uid_ != 0)
        dict->SetBigInteger(L"sell_uid", data_->sell_uid_);

    if (data_->amount_ != 0)
        dict->SetBigInteger(L"amount",data_->amount_);

    if (data_->open_position_time_ != 0)
        dict->SetBigInteger(L"open_position_time", data_->open_position_time_);

    if (data_->close_position_time_ != 0)
        dict->SetBigInteger(L"close_position_time", data_->close_position_time_);

    if (data_->gross_profit_ != 0.0)
        dict->SetReal(L"gross_profit", data_->gross_profit_);

    if (data_->open_price_ != 0.0)
        dict->SetReal(L"open_price", data_->open_price_);

    if(data_->open_charge_ != 0.0)
        dict->SetReal(L"open_charge", data_->open_charge_);

    dict->SetInteger(L"type", data_->type_);
    dict->SetInteger(L"handle",data_->handle_type_);
    dict->SetInteger(L"sell_handle_type", data_->sell_handle_type_);
    dict->SetInteger(L"buy_handle_type", data_->buy_handle_type_);
    if (!data_->symbol_.empty())
        dict->SetString(L"symbol", data_->symbol_);
    return dict;
}


TradesPosition::TradesPosition() {
    data_ = new Data();
}

TradesPosition::TradesPosition(const TradesPosition& trades_positions)
    : data_(trades_positions.data_) {
    if (data_ != NULL) {
        data_->AddRef();
    }
}

TradesPosition& TradesPosition::operator =(
    const TradesPosition& trades_positions) {
    if (trades_positions.data_ != NULL) {
        trades_positions.data_->AddRef();
    }

    if (data_ != NULL) {
        data_->Release();
    }

    data_ = trades_positions.data_;
    return (*this);
}

void TradesPosition::ValueSerialization(base_logic::DictionaryValue* dict) {
    int64 big_buy_sell = 0;
    int64 big_handle = 0;
    dict->GetBigInteger(L"tid", &data_->position_id_);
    dict->GetBigInteger(L"uid", &data_->uid_);
    dict->GetInteger(L"code_id", &data_->code_id_);
    dict->GetBigInteger(L"buy_sell", &big_buy_sell);
    data_->buy_sell_ = big_buy_sell;
    dict->GetString(L"symbol", &data_->symbol_);
    dict->GetString(L"name", &data_->name_);
    dict->GetInteger(L"close_type", &data_->close_type_);
    dict->GetBigInteger(L"amount", &data_->amount_);
    dict->GetBigInteger(L"r_amount", &data_->r_amount_);
    dict->GetBigInteger(L"open_position_time", &data_->open_position_time_);
    dict->GetBigInteger(L"close_position_time", &data_->close_position_time_);
    dict->GetReal(L"gross_profit", &data_->gross_profit_);
    dict->GetReal(L"open_price", &data_->open_price_);
    dict->GetReal(L"open_cost", &data_->open_cost_);
    dict->GetReal(L"open_charge", &data_->open_charge_);
    dict->GetReal(L"close_price", &data_->close_price_);
    dict->GetReal(L"pos_limit", &data_->limit_);
    dict->GetReal(L"stop", &data_->stop_);
    dict->GetReal(L"deferred", &data_->deferred_);
    int32 int_result = 0;
    dict->GetInteger(L"result", &int_result);
    if (int_result == 1)
        data_->result_ = true;
    else
        data_->result_ = false;

    dict->GetBigInteger(L"handle", &big_handle);
    data_->handle_ = big_handle;
}

base_logic::DictionaryValue* TradesPosition::GetValue() {
    if (data_ == NULL)
        return NULL;
    base_logic::DictionaryValue* dict = new base_logic::DictionaryValue();
    if (data_->uid_ != 0)
        dict->SetBigInteger(L"uid",data_->uid_);
    if (data_->position_id_ != 0)
        dict->SetBigInteger(L"tid",data_->position_id_);
    if (data_->code_id_ != 0)
        dict->SetInteger(L"code_id", data_->code_id_);
    if (data_->buy_sell_ != 0)
        dict->SetInteger(L"buy_sell", data_->buy_sell_);
    if (data_->close_type_ != 0)
        dict->SetInteger(L"close_type", data_->close_type_);
    dict->SetInteger(L"handle",data_->handle_);
    dict->SetInteger(L"type", data_->type_);
    if(data_->result_==false)
        dict->SetInteger(L"result", 1);
    else
        dict->SetInteger(L"result", 0);
    if(data_->amount_ != 0)
        dict->SetBigInteger(L"amount",data_->amount_);
    if (data_->r_amount_ != 0)
        dict->SetBigInteger(L"r_amount",data_->r_amount_);
    if (data_->open_position_time_ != 0.0)
        dict->SetBigInteger(L"open_position_time",data_->open_position_time_);
    if (data_->close_position_time_ != 0)
        dict->SetBigInteger(L"close_position_time",data_->close_position_time_);
    if(data_->gross_profit_ != 0.0)
        dict->SetReal(L"gross_profit", data_->gross_profit_);
    if(data_->open_price_ != 0.0)
        dict->SetReal(L"open_price", data_->open_price_);
    if(data_->open_cost_ != 0.0)
        dict->SetReal(L"open_cost", data_->open_cost_);
    if(data_->open_all_cost_ != 0.0)
        dict->SetReal(L"open_all_cost", data_->open_all_cost_);
    if(data_->open_charge_ != 0.0)
        dict->SetReal(L"open_charge", data_->open_charge_);
    if(data_->close_price_ != 0.0)
        dict->SetReal(L"close_price", data_->close_price_);
    if(data_->limit_ != 0.0)
        dict->SetReal(L"limit", data_->limit_);
    if(data_->stop_ != 0.0)
        dict->SetReal(L"stop", data_->stop_);
    if(data_->deferred_ != 0.0)
        dict->SetReal(L"deferred", data_->deferred_);
    if(!data_->code_.empty())
        dict->SetString(L"code", data_->code_);
    if(!data_->symbol_.empty())
        dict->SetString(L"symbol", data_->symbol_);
    if(!data_->name_.empty())
        dict->SetString(L"name",data_->name_);

    return dict;

}

Quotations::Quotations() {
    data_ = new Data();
}

Quotations::Quotations(const Quotations& quotations)
    : data_(quotations.data_) {
    if (data_ != NULL) {
        data_->AddRef();
    }
}

Quotations& Quotations::operator =(const Quotations& quotations) {
    if (quotations.data_ != NULL) {
        quotations.data_->AddRef();
    }

    if (data_ != NULL) {
        data_->Release();
    }

    data_ = quotations.data_;
    return (*this);
}

void Quotations::ValueDeserialize(std::string& str) {
    int32 error_code;
    std::string error_str;
    base_logic::ValueSerializer* engine = base_logic::ValueSerializer::Create(
            base_logic::IMPL_JSON);
    if (engine == NULL) {
        LOG_ERROR("engine create null");
    }
    base_logic::DictionaryValue* dict = (base_logic::DictionaryValue*) engine
                                        ->Deserialize(&str, &error_code, &error_str);
    dict->GetReal(L"current_price", &data_->current_price_);
    dict->GetReal(L"high_price", &data_->high_price_);
    dict->GetReal(L"low_price", &data_->low_price_);
    dict->GetReal(L"opening_today_price", &data_->opening_today_price_);
    dict->GetReal(L"closed_yesterday_price", &data_->closed_yesterday_price_);
    dict->GetReal(L"change", &data_->change_);
    dict->GetReal(L"pchg", &data_->pchg_);
    dict->GetBigInteger(L"current_unix_time", &data_->current_unix_time_);
    dict->GetString(L"platform_name", &data_->platform_name_);
    dict->GetString(L"symbol", &data_->symbol_);
    dict->GetString(L"exchange_name", &data_->exchange_name_);
}

std::string Quotations::ValueSerialize() {
    std::string json_content;
    base_logic::DictionaryValue dict;
    if (!data_)
        return "";
    dict.SetReal(L"current_price", data_->current_price_);
    dict.SetReal(L"high_price", data_->high_price_);
    dict.SetReal(L"low_price", data_->low_price_);
    dict.SetReal(L"opening_today_price", data_->opening_today_price_);
    dict.SetReal(L"closed_yesterday_price", data_->closed_yesterday_price_);
    dict.SetReal(L"change", data_->change_);
    dict.SetReal(L"pchg", data_->pchg_);
    dict.SetBigInteger(L"current_unix_time", data_->current_unix_time_);
    if (!data_->platform_name_.empty())
        dict.SetString(L"platform_name", data_->platform_name_);
    if (!data_->symbol_.empty())
        dict.SetString(L"symbol", data_->symbol_);
    if (!data_->exchange_name_.empty())
        dict.SetString(L"exchange_name", data_->exchange_name_);

    base_logic::ValueSerializer* engine = base_logic::ValueSerializer::Create(
            base_logic::IMPL_JSON);
    if (engine == NULL) {
        LOG_ERROR("engine create null");
    }
    bool r = engine->Serialize(dict, &json_content);
    return json_content;
}
//---------------------------------

StarInfo::StarInfo() {
    data_ = new Data();
}

StarInfo::StarInfo(const StarInfo& starinfo)
    : data_(starinfo.data_) {
    if (data_ != NULL) {
        data_->AddRef();
    }
}

StarInfo& StarInfo::operator =(const StarInfo& starinfo) {
    if (starinfo.data_ != NULL) {
        starinfo.data_->AddRef();
    }

    if (data_ != NULL) {
        data_->Release();
    }

    data_ = starinfo.data_;
    return (*this);
}

void StarInfo::ValueSerialization(base_logic::DictionaryValue* dict) {
    dict->GetReal(L"updown", &data_->updown_);

    dict->GetBigInteger(L"gender", &data_->gender_);
    dict->GetBigInteger(L"star_owntimes", &data_->owntimes_);
    dict->GetInteger(L"type", &data_->type_);
    dict->GetInteger(L"star_vip", &data_->vip_);
    dict->GetString(L"symbol", &data_->symbol_);
    dict->GetString(L"phone", &data_->phone_);
    dict->GetString(L"name", &data_->name_);
    dict->GetString(L"pic", &data_->pic_);
    dict->GetString(L"brief_url", &data_->brief_url_);
    dict->GetString(L"accid", &data_->accid_);
    dict->GetString(L"pic", &data_->pic_);
    dict->GetString(L"weibo_index_id", &data_->weibo_index_id_);
    dict->GetString(L"nation", &data_->nation_);
    dict->GetString(L"nationality", &data_->nationality_);
    dict->GetString(L"introduction", &data_->introduction_);
    dict->GetString(L"jianpin", &data_->jianpin_);
    dict->GetString(L"quanpin", &data_->quanpin_);
    dict->GetInteger(L"display_on_home", &data_->display_on_home_);
    dict->GetBigInteger(L"hot_priority1", &data_->hot_priority1_);
    dict->GetBigInteger(L"hot_priority2", &data_->hot_priority2_);
    dict->GetString(L"pic1", &data_->home_pic_);
    dict->GetString(L"home_button_pic", &data_->home_button_pic_);
    dict->GetBigInteger(L"add_time", &data_->add_time_);
    dict->GetInteger(L"publish_type", &data_->publish_type_);
}
///TOwnStar

TOwnStar::TOwnStar() {
    data_ = new Data();
}

TOwnStar::TOwnStar(const TOwnStar& starinfo)
    : data_(starinfo.data_) {
    if (data_ != NULL) {
        data_->AddRef();
    }
}

TOwnStar& TOwnStar::operator =(const TOwnStar& starinfo) {
    if (starinfo.data_ != NULL) {
        starinfo.data_->AddRef();
    }

    if (data_ != NULL) {
        data_->Release();
    }

    data_ = starinfo.data_;
    return (*this);
}


void TOwnStar::ValueSerialization(base_logic::DictionaryValue* dict) {

    dict->GetBigInteger(L"uid", &data_->uid_);
    dict->GetBigInteger(L"ownseconds", &data_->ownseconds_);
    dict->GetInteger(L"appoint", &data_->appoint_);
    dict->GetString(L"starname", &data_->starname_);
    dict->GetString(L"starcode", &data_->starcode_);
    dict->GetString(L"faccid", &data_->faccid_);
    dict->GetString(L"head_url", &data_->head_url_);
}

Comments::Comments() {
  data_ = new Data();
}

Comments::Comments(const Comments& comments)
    : data_(comments.data_) {
  if (data_ != NULL) {
    data_->AddRef();
  }
}

Comments& Comments::operator =(const Comments& comments) {
  if (comments.data_ != NULL) {
    comments.data_->AddRef();
  }

  if (data_ != NULL) {
    data_->Release();
  }

  data_ = comments.data_;
  return (*this);
}

void Comments::ValueDeserialize(std::string& str) {
  int32 error_code;
  std::string error_str;
  base_logic::ValueSerializer* engine = base_logic::ValueSerializer::Create(
      base_logic::IMPL_JSON);
  if (engine == NULL) {
    LOG_ERROR("engine create null");
  }
  base_logic::DictionaryValue* dict = (base_logic::DictionaryValue*) engine
      ->Deserialize(&str, &error_code, &error_str);

  dict->GetBigInteger(L"cms_time", &data_->current_unix_time_);
  dict->GetString(L"star_code", &data_->star_code_);
  dict->GetString(L"fans_id", &data_->fans_id_);
  dict->GetString(L"nick_name", &data_->nick_name_);
  dict->GetString(L"comments", &data_->comments_);
  dict->GetString(L"head_url", &data_->head_url_);
}

std::string Comments::ValueSerialize() {
  std::string json_content;
  base_logic::DictionaryValue dict;
  if (!data_)
    return "";
  dict.SetBigInteger(L"current_unix_time", data_->current_unix_time_);
  dict.SetString(L"star_code", data_->star_code_);
  dict.SetString(L"fans_id", data_->fans_id_);

  dict.SetString(L"nick_name", data_->nick_name_);
  dict.SetString(L"comments", data_->comments_);
  if (!data_->head_url_.empty())
    dict.SetString(L"head_url", data_->head_url_);
  /*
  if (!data_->platform_name_.empty())
    dict.SetString(L"platform_name", data_->platform_name_);
  if (!data_->symbol_.empty())
    dict.SetString(L"symbol", data_->symbol_);
  if (!data_->exchange_name_.empty())
    dict.SetString(L"exchange_name", data_->exchange_name_);
*/
  base_logic::ValueSerializer* engine = base_logic::ValueSerializer::Create(
      base_logic::IMPL_JSON);
  if (engine == NULL) {
    LOG_ERROR("engine create null");
  }
  bool r = engine->Serialize(dict, &json_content);
  return json_content;
}
//_____starbrief

StarBrief::StarBrief() {
  data_ = new Data();
}

StarBrief::StarBrief(const StarBrief& starhead)
    : data_(starhead.data_) {
  if (data_ != NULL) {
    data_->AddRef();
  }
}

StarBrief& StarBrief::operator =(const StarBrief& starhead) {
  if (starhead.data_ != NULL) {
    starhead.data_->AddRef();
  }

  if (data_ != NULL) {
    data_->Release();
  }

  data_ = starhead.data_;
  return (*this);
}

void StarBrief::ValueSerialization(base_logic::DictionaryValue* dict) {

  dict->GetString(L"symbol", &data_->symbol_);
  dict->GetString(L"nationality", &data_->nationality_);
  dict->GetString(L"name", &data_->name_);
  dict->GetBigInteger(L"gender", &data_->gender_);

  dict->GetString(L"head_url", &data_->head_url_);
  dict->GetString(L"nation", &data_->nation_);
  dict->GetString(L"work", &data_->work_);
  dict->GetInteger(L"star_vip", &data_->vip_);
  dict->GetString(L"introduction", &data_->introduction_);
  dict->GetString(L"weibo_index_id", &data_->weibo_index_id_);
  dict->GetString(L"constellaction", &data_->constellaction_);
  dict->GetString(L"birth", &data_->birth_);
  dict->GetString(L"colleage", &data_->colleage_);
  dict->GetString(L"pic_url", &data_->pic_url_);
  dict->GetBigInteger(L"owntimes", &data_->owntimes_);
}


}  // namespace quotations_logic
