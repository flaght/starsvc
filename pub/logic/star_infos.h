//  Copyright (c) 2015-2015 The quotations Authors. All rights reserved.
//  Created on: 2017年5月30日 Author: kerry

#ifndef STAR_PUB_LOGIC_STAR_INFOS_H_
#define STAR_PUB_LOGIC_STAR_INFOS_H_

#include <string>
#include <map>
#include <list>

#include "basic/basictypes.h"
#include "logic/base_values.h"
#include "basic/radom_in.h"

#define HEAD_URL "http://tva2.sinaimg.cn/crop.0.0.180.180.180/71bf6552jw1e8qgp5bmzyj2050050aa8.jpg"
enum INFOTYPE {
    NO_TYPE = 100,
    TRADES_POSITION_TYPE,
    TRADES_ORDER_TYPE
};

enum PAYTYPE {
    WX_APP = 1,
    UNIPNPAY = 2,
    ALIPAY = 3
};

enum {
    STOCK_TYPE = 1,
    GOODS_TYPE = 2,
    FUTURES_TYPE = 3,
    FORXE_TYPE = 4,
    STAR_TYPE = 5
};

enum BSTYPE {
    BUY_TYPE = 1,
    SELL_TYPE = -1
};

enum TIMETYPE {
    ONE_MINUTE = 60,
    FIVE_MINUTE = 300,
    HALF_HOUR = 1800,
    ONE_HOUR = 3600
};

//委托类型
enum HANDLETYPE {
    CANCEL_POSITION = -2, //委托取消
    NO_HANDLE = -1,//委托异常
    POSITION_HANDLE = 0, //委托中
    MATCHES_HANDLE = 1, //匹配中
    COMPLETE_HANDLE = 2 //委託完成
};

//订单类型
enum ORDERTYPE {
    NO_ORDER = -4,//订单异常
    MONEY_LESS_THAN = -3,//求购发资金不足
    TIME_LESS_THAN = -2,//转让方时间不足
    CANCEL_ORDER = -1,//取消订单
    MATCHES_ORDER = 0,//匹配中
    CONFIRM_ORDER = 1,//确认
    COMPLETE_ORDER = 2//完成
};

namespace star_logic {

class Auction {
 public:
    Auction();
    Auction(const Auction& auction);

    Auction& operator =(const Auction& auction);
    ~Auction() {
        if (data_ != NULL) {
            data_->Release();
        }
    }

    void set_aid(const int64 aid) {
        data_->aid_ = aid;
    }

    void set_buy_count(const int32 buy_count) {
        data_->buy_count_ = buy_count;
    }

    void set_sell_count(const int32 sell_count) {
        data_->sell_count_ = sell_count;
    }

    void set_sell_time(const int64 sell_time) {
        data_->sell_time_ = sell_time;
    }

    void set_buy_time(const int64 buy_time) {
        data_->buy_time_ = buy_time;
    }

    void set_start_time(const int64 start_time) {
        data_->start_time_ = start_time;
    }

    void set_end_time(const int64 end_time) {
        data_->end_time_ = end_time;
    }

    void set_symbol(const std::string& symbol) {
        data_->symbol_ = symbol;
    }

    int64 aid() const {
        return data_->aid_;
    }

    int32 buy_count() const {
        return data_->buy_count_;
    }

    int32 sell_count() const {
        return data_->sell_count_;
    }

    int64 sell_time() const {
        return data_->sell_time_;
    }

    int64 buy_time() const {
        return data_->buy_time_;
    }

    std::string& symbol() const {
        return data_->symbol_;
    }


    class Data {
    public:
        Data()
            : refcount_(1),
              aid_(0),
              buy_count_(0),
              sell_count_(0),
              buy_time_(0),
              sell_time_(0),
              start_time_(0),
              end_time_(0){
        }


    public:
        int64 aid_;
        int32 buy_count_;
        int32 sell_count_;
        int64 buy_time_;
        int64 sell_time_;
        int64 start_time_;
        int64 end_time_;
        std::string symbol_;
        void AddRef() {
            __sync_fetch_and_add(&refcount_, 1);
        }
        void Release() {
            __sync_fetch_and_sub(&refcount_, 1);
            if (!refcount_)
                delete this;
        }
    private:
        int refcount_;
    };
    Data* data_;
};


class Withdrawals {
public:
    Withdrawals();
    Withdrawals(const Withdrawals& withdrawals);
    Withdrawals& operator =(const Withdrawals& withdrawals);

    ~Withdrawals() {
        if (data_ != NULL) {
            data_->Release();
        }
    }

    static bool close_after(const Withdrawals& t_withdrawals,
                            const Withdrawals& r_withdrawals) {
        return Data::close_after(t_withdrawals.data_, r_withdrawals.data_);
    }

    void set_uid(const int64 uid) {
        data_->uid_ = uid;
    }
    void set_wid(const int64 wid) {
        data_->wid_ = wid;
    }
    void set_status(const int32 status) {
        data_->status_ = status;
    }
    void set_amount(const double amount) {
        data_->amount_ = amount;
    }
    void set_charge(const double charge) {
        data_->charge_ = charge;
    }
    void set_withdraw_unix_time(const int64 withdraw_unix_time) {
        data_->withdraw_unix_time_ = withdraw_unix_time;
    }
    void set_withdraw_time(const std::string& withdraw_time) {
        data_->withdraw_time_ = withdraw_time;
    }
    void set_handle_time(const std::string& handle_time) {
        data_->handle_time_ = handle_time;
    }
    void set_bank(const std::string& bank) {
        data_->bank_ = bank;
    }

    void set_branch_bank(const std::string& branch_bank) {
        data_->branch_bank_ = branch_bank;
    }

    void set_card_no(const std::string& card_no) {
        data_->card_no_ = card_no;
    }

    void set_name(const std::string& name) {
        data_->name_ = name;
    }

    void set_comment(const std::string& comment) {
        data_->comment_ = comment;
    }

    const int64 uid() const {
        return data_->uid_;
    }

    const int64 wid() const {
        return data_->wid_;
    }

    const int32 status() const {
        return data_->status_;
    }

    const double amount() const {
        return data_->amount_;
    }

    const double charge() const {
        return data_->charge_;
    }

    const int64 withdraw_unix_time() const {
        return data_->withdraw_unix_time_;
    }

    const std::string& withdraw_time() const {
        return data_->withdraw_time_;
    }

    const std::string& handle_time() const {
        return data_->handle_time_;
    }

    const std::string& bank() const {
        return data_->bank_;
    }

    const std::string& branch_bank() const {
        return data_->branch_bank_;
    }

    const std::string& card_no() const {
        return data_->card_no_;
    }

    const std::string& name() const {
        return data_->name_;
    }

    const std::string& comment() const {
        return data_->comment_;
    }

    void ValueSerialization(base_logic::DictionaryValue* dict);

    class Data {
    public:
        Data()
            : refcount_(1),
              uid_(0),
              wid_(0),
              status_(0),
              amount_(0.0),
              charge_(0.0),
              withdraw_unix_time_(0) {
        }

        static bool close_after(const Data* t_data, const Data* r_data) {
            return t_data->withdraw_unix_time_ > r_data->withdraw_unix_time_;
        }

    public:
        int64 uid_;
        int64 wid_;
        int32 status_;
        double amount_;
        double charge_;
        int64 withdraw_unix_time_;
        std::string withdraw_time_;
        std::string handle_time_;
        std::string bank_;
        std::string branch_bank_;
        std::string card_no_;
        std::string name_;
        std::string comment_;
        void AddRef() {
            __sync_fetch_and_add(&refcount_, 1);
        }
        void Release() {
            __sync_fetch_and_sub(&refcount_, 1);
            if (!refcount_)
                delete this;
        }
    private:
        int refcount_;
    };
    Data* data_;
};

class Recharge {
public:
    Recharge();
    Recharge(const Recharge& recharge);
    Recharge& operator =(const Recharge& recharge);

    ~Recharge() {
        if (data_ != NULL) {
            data_->Release();
        }
    }

    static bool close_after(const Recharge& t_recharge,
                            const Recharge& r_recharge) {
        return Data::close_after(t_recharge.data_, r_recharge.data_);
    }

    void set_rid(const int64 rid) {
        data_->rid_ = rid;
    }

    void set_uid(const int64 uid) {
        data_->uid_ = uid;
    }

    void set_status(const int32 status) {
        data_->status_ = status;
    }

    void set_amount(const double amount) {
        data_->amount_ = amount;
    }

    void set_deposit_type(const int32 deoposit_type) {
        data_->deposit_type_ = deoposit_type;
    }

    void set_deposit_time(const std::string& deposit_time) {
        data_->deposit_time_ = deposit_time;
    }

    void set_deposit_name(const std::string& deposit_name) {
        data_->deposit_name_ = deposit_name;
    }
    void set_transaction_id(const std::string& transaction_id) {
        data_->transaction_id_ = transaction_id;
    }

    void set_deposit_unix_time(const int64 unix_time) {
        data_->deposit_unix_time_ = unix_time;
    }
    
    void set_recharge_type(const int32 recharge_type) {
        data_->recharge_type_ = recharge_type;
    }

    const int64 rid() const {
        return data_->rid_;
    }

    const int64 uid() const {
        return data_->uid_;
    }

    const int32 deposit_type() const {
        return data_->deposit_type_;
    }

    const double amount() const {
        return data_->amount_;
    }

    const int32 status() const {
        return data_->status_;
    }

    const int64 deposit_unix_time() const {
        return data_->deposit_unix_time_;
    }

    const std::string& deposit_time() const {
        return data_->deposit_time_;
    }

    const std::string& deposit_name() const {
        return data_->deposit_name_;
    }
    const std::string& transaction_id() const {
        return data_->transaction_id_;
    }
    
    const int32 recharge_type() const {
        return data_->recharge_type_;
    }

    void ValueSerialization(base_logic::DictionaryValue* dict);

    class Data {
    public:
        Data()
            : refcount_(1),
              rid_(0),
              status_(0),
              amount_(0.0),
              deposit_type_(0),
              deposit_unix_time_(0),
              uid_(0),
              recharge_type_(0) {
        }

        static bool close_after(const Data* t_data, const Data* r_data) {
            return t_data->deposit_unix_time_ > r_data->deposit_unix_time_;
        }

    public:
        int64 rid_;
        int32 status_;
        int64 uid_;
        double amount_;
        int32 deposit_type_;
        int64 deposit_unix_time_;
        std::string deposit_time_;
        std::string deposit_name_;
        int32 recharge_type_;
        std::string transaction_id_;
        void AddRef() {
            __sync_fetch_and_add(&refcount_, 1);
        }
        void Release() {
            __sync_fetch_and_sub(&refcount_, 1);
            if (!refcount_)
                delete this;
        }
    private:
        int refcount_;
    };
    Data* data_;
};

class UserInfo {
public:
    UserInfo();
    UserInfo(const UserInfo& userinfo);
    UserInfo& operator =(const UserInfo& userinfo);

    ~UserInfo() {
        if (data_ != NULL) {
            data_->Release();
        }
    }
    const int64 uid() const {
        return data_->uid_;
    }
    const double balance() const {
        return data_->balance_;
    }
    const double market_capitalization() const {
        return data_->market_capitalization_;
    }
    const int socket_fd() const {
        return data_->socket_fd_;
    }
    const int32 gender() const {
        return data_->gender_;
    }
    const int32 type() const {
        return data_->type_;
    }
    const std::string& phone_num() const {
        return data_->phone_num_;
    }
    const std::string nickname() {
        return data_->nickname_;
    }
    const std::string& token() const {
        return data_->token_;
    }
    const int64 token_time() const {
        return data_->token_time_;
    }
    const std::string& head_url() const {
        return data_->head_url_;
    }

    const int32 send_error_count() const {
        return data_->send_error_count_;
    }

    const int32 recv_error_count() const {
        return data_->recv_error_count_;
    }

    const bool is_effective() const {
        return data_->is_effective_;
    }

    const time_t send_last_time() const {
        return data_->send_last_time_;
    }

    const time_t recv_last_time() const {
        return data_->recv_last_time_;
    }
    const std::string realname() const {
        return data_->real_name_;
    }
    const std::string id_card() const {
        return data_->id_card_;
    }
    const std::string starcode() const {
        return data_->starcode_;
    }
    const std::string channel() const {
        return data_->channel_;
    }

    void set_type(const int32 type) {
        data_->type_ = type;
    }
    void set_uid(const int64 uid) {
        data_->uid_ = uid;
    }
    void set_socket_fd(const int socket_fd) {
        data_->socket_fd_ = socket_fd;
    }
    void set_gender(const int32 gender) {
        data_->gender_ = gender;
    }
    void set_phone_num(const std::string& phone_num) {
        data_->phone_num_ = phone_num;
    }
    void set_nickname(const std::string& nickname) {
        data_->nickname_ = nickname;
    }
    void set_token(const std::string& token) {
        data_->token_ = token;
    }
    void set_token_time(const int64 token_time) {
        data_->token_time_ = token_time;
    }
    void set_head_url(const std::string& head_url) {
        data_->head_url_ = head_url;
    }
    void set_realname(const std::string& value) {
        data_->real_name_ = value;
    }
    void set_id_card(const std::string& value) {
        data_->id_card_ = value;
    }
    void set_channel(const std::string& value) {
        data_->channel_ = value;
    }
    void set_starcode(const std::string& value) {
        data_->starcode_ = value;
    }

    void set_balance(const double balance) {
        data_->balance_ = balance;
    }

    void set_is_effective(const bool is_effective) {
        data_->is_effective_ = is_effective;
    }

    void set_send_last_time(const time_t send_last_time) {
        data_->send_last_time_ = send_last_time;
    }

    void set_recv_last_time(const time_t recv_last_time) {
        data_->recv_last_time_ = recv_last_time;
    }

    void add_send_error_count() {
        __sync_fetch_and_add(&data_->send_error_count_, 1);
    }

    void add_recv_error_count() {
        __sync_fetch_and_add(&data_->recv_error_count_, 1);
    }


    void ValueSerialization(base_logic::DictionaryValue* dict);

    class Data {
    public:
        Data()
            : refcount_(1),
              uid_(0),
              socket_fd_(0),
              gender_(0),
              type_(0),
              balance_(0.0),
              market_capitalization_(0.0),
              is_effective_(false),
              recv_last_time_(0),
              send_last_time_(0),
              recv_error_count_(0),
              send_error_count_(0) {
            real_name_ = "";
            id_card_ = "";
            channel_ = "";
            starcode_ = "";
        }

    public:
        int64 uid_;
        int socket_fd_;
        int32 gender_;
        int32 type_;
        int32 send_error_count_;
        int32 recv_error_count_;
        double balance_; //余额
        bool is_effective_;
        time_t send_last_time_;
        time_t recv_last_time_;
        std::string phone_num_;
        std::string nickname_;
        std::string token_;
        int64 token_time_;
        std::string head_url_;
        std::string real_name_;
        std::string id_card_;
        std::string channel_;
        std::string starcode_;
        double market_capitalization_;
        void AddRef() {
            __sync_fetch_and_add(&refcount_, 1);
        }
        void Release() {
            __sync_fetch_and_sub(&refcount_, 1);
            if (!refcount_)
                delete this;
        }
    private:
        int refcount_;
    };
    Data* data_;
};

class TradesPosition {
public:
    TradesPosition();
    TradesPosition(const TradesPosition& trades_positions);

    TradesPosition& operator =(const TradesPosition& trades_positions);

    ~TradesPosition() {
        if (data_ != NULL) {
            data_->Release();
        }
    }

    static bool close_after(const TradesPosition& t_trades_position,
                            const TradesPosition& r_trades_position) {
        return Data::close_after(t_trades_position.data_, r_trades_position.data_);
    }


    static bool open_after(const TradesPosition& t_trades_position,
                            const TradesPosition& r_trades_position) {
        return Data::open_after(t_trades_position.data_, r_trades_position.data_);
    }

    static bool price_after(const TradesPosition& t_trades_position,
                        const TradesPosition& r_trades_position) {
        return Data::price_after(t_trades_position.data_,r_trades_position.data_);
    }

    void ValueSerialization(base_logic::DictionaryValue* dict);

    base_logic::DictionaryValue* GetValue();
    void c_gross_profit() {
        if (data_->close_type_)
            data_->gross_profit_ = data_->open_cost_;
    }

    void create_position_id() {
        data_->position_id_ = base::SysRadom::GetInstance()->GetRandomID();
    }

    void set_uid(const int64 uid) {
        data_->uid_ = uid;
    }

    void set_position_id(const int64 position_id) {
        data_->position_id_ = position_id;
    }

    void set_code_id(const int32 code_id) {
        data_->code_id_ = code_id;
    }

    void set_buy_sell(const int32 buy_sell) {
        data_->buy_sell_ = buy_sell;
    }

    void set_close_type(const int32 close_type) {
        data_->close_type_ = close_type;
    }

    void set_is_deferred(const bool is_deferred) {
        data_->deferred_ = is_deferred;
    }

    void set_amount(const int64 amount) {
        data_->amount_ = amount;
    }

    void set_r_amount(const int64 r_amount) {
        data_->r_amount_= r_amount;
    }

    void set_open_position_time(const int64 open_position_time) {
        data_->open_position_time_ = open_position_time;
    }

    void set_close_position_time(const int64 close_position_time) {
        data_->close_position_time_ = close_position_time;
    }

    void set_open_price(const double open_price) {
        data_->open_price_ = open_price;
    }

    void set_open_cost(const double open_cost) {
        data_->open_cost_ = open_cost;
    }

    void set_open_all_cost(const double open_all_cost) {
        data_->open_all_cost_ = open_all_cost;
    }

    void set_open_charge(const double open_charge) {
        data_->open_charge_ = open_charge;
    }

    void set_close_price(const double close_price) {
        data_->close_price_ = close_price;
    }

    void set_limit(const double limit) {
        data_->limit_ = limit;
    }

    void set_stop(const double stop) {
        data_->stop_ = stop;
    }

    void set_deferred(const double deferred) {
        data_->deferred_ = deferred;
    }

    void set_code(const std::string& code) {
        data_->code_ = code;
    }

    void set_symbol(const std::string& symbol) {
        data_->symbol_ = symbol;
    }

    void set_name(const std::string& name) {
        data_->name_ = name;
    }

    void set_result(const bool result) {
        data_->result_ = result;
    }

    void set_handle(const int32 handle) {
        data_->handle_ = handle;
    }

    void set_gross_profit(const double gross_profit) {
        data_->gross_profit_ = gross_profit;
    }

    void set_goods_key(const std::string& goods_key) {
        data_->goods_key_ = goods_key;
    }

    void set_order_id(const int64 order_id) {
        data_->order_id_ = order_id;
    }
    const int64 uid() const {
        return data_->uid_;
    }

    const int64 position_id() const {
        return data_->position_id_;
    }

    const int32 code_id() const {
        return data_->code_id_;
    }

    const int32 buy_sell() const {
        return data_->buy_sell_;
    }

    const int32 close_type() const {
        return data_->close_type_;
    }

    const bool is_deferred() const {
        return data_->is_deferred_;
    }

    const int64 amount() const {
        return data_->amount_;
    }

    const int64 r_amount() const {
        return data_->r_amount_;
    }

    const int32 handle() const {
        return data_->handle_;
    }
    const int64 open_position_time() const {
        return data_->open_position_time_;
    }

    const int64 close_position_time() const {
        return data_->close_position_time_;
    }

    const double open_price() const {
        return data_->open_price_;
    }

    const double open_cost() const {
        return data_->open_cost_;
    }

    const double open_all_cost() const {
        return data_->open_all_cost_;
    }

    const double open_charge() const {
        return data_->open_charge_;
    }

    const double close_price() const {
        return data_->close_price_;
    }

    const double limit() const {
        return data_->limit_;
    }

    const double stop() const {
        return data_->stop_;
    }

    const double gross_profit() const {
        return data_->gross_profit_;
    }

    const double deferred() const {
        return data_->deferred_;
    }

    const bool result() const {
        return data_->result_;
    }

    const std::string& code() const {
        return data_->code_;
    }

    const std::string& symbol() const {
        return data_->symbol_;
    }

    const std::string& name() const {
        return data_->name_;
    }

    const std::string& goods_key() const {
        return data_->goods_key_;
    }

    const int32 type() const {
        return data_->type_;
    }

    const int64 order_id() const {
        return data_->order_id_;
    }

private:
    class Data {
    public:
        Data()
            : refcount_(1),
              uid_(0),
              position_id_(0),
              code_id_(0),
              buy_sell_(0),
              close_type_(0),
              is_deferred_(false),
              result_(false),
              amount_(0),
              r_amount_(0),
              handle_(NO_HANDLE),
              open_position_time_(0),
              close_position_time_(0),
              gross_profit_(0.0),
              open_price_(0.0),
              open_cost_(0.0),
              open_all_cost_(0.0),
              open_charge_(0.0),
              close_price_(0.0),
              limit_(0.0),
              stop_(0.0),
              type_(TRADES_POSITION_TYPE),
              deferred_(0.0) {
        }

        static bool close_after(const Data* t_data, const Data* r_data) {
            return t_data->close_position_time_ > r_data->close_position_time_;
        }

        static bool open_after(const Data* t_data, const Data* r_data) {
            return t_data->open_position_time_ > r_data->open_position_time_;
        }

        static bool price_after(const Data* t_data, const Data* r_data) {
            return t_data->open_price_ > r_data->open_price_;
        }
    public:
        int64 uid_;
        int64 position_id_;
        int32 code_id_;  //属于哪个商品
        int32 buy_sell_;  // 1,买 2,卖
        int32 close_type_;
        int32 handle_;
        int32 type_;
        bool is_deferred_;
        bool result_;
        int64 amount_; //明星用于表示时间精确到秒
        int64 r_amount_; //实际成交数
        int64 open_position_time_;
        int64 close_position_time_;
        double gross_profit_;
        double open_price_;
        double open_cost_;
        double open_all_cost_;
        double open_charge_;
        double close_price_;
        double limit_;
        double stop_;
        double deferred_;
        int64  s_uid_;//来源//若为0，表明系统的
        std::string code_;
        std::string symbol_;
        std::string name_;
        std::string goods_key_;
        int64 order_id_;

        void AddRef() {
            __sync_fetch_and_add(&refcount_, 1);
        }
        void Release() {
            __sync_fetch_and_sub(&refcount_, 1);
            if (!refcount_)
                delete this;
        }
    private:
        int refcount_;
    };
    Data* data_;
};

class TradesOrder {
 public: 
    TradesOrder();
    TradesOrder(const TradesOrder& trades_);

    TradesOrder& operator =(const TradesOrder& trades_order);

    ~TradesOrder() {
        if (data_ != NULL) {
            data_->Release();
        }
    }

    base_logic::DictionaryValue* GetValue();

    void ValueSerialization(base_logic::DictionaryValue* dict);


    static bool open_after(const TradesOrder& t_trades_order,
                            const TradesOrder& r_trades_order) {
        return Data::open_after(t_trades_order.data_, r_trades_order.data_);
    }
    
    static bool open_price_after(const TradesOrder& t_trades_order,
                            const TradesOrder& r_trades_order) {
        return Data::open_price_after(t_trades_order.data_, r_trades_order.data_);
    }

    static bool price_after(const TradesOrder& t_trades_order,
                        const TradesOrder& r_trades_order){
        return Data::price_after(t_trades_order.data_, r_trades_order.data_);
    }

    void create_order_id() {
        data_->order_id_ = base::SysRadom::GetInstance()->GetRandomID();
    }

    const int64 order_id() const {
        return data_->order_id_;
    }

    const int64 buy_position_id() const {
        return data_->buy_position_id_;
    }

    const int64 sell_position_id() const {
        return data_->sell_position_id_;
    }

    const int64 buy_uid() const {
        return data_->buy_uid_;
    }

    const int64 sell_uid() const {
        return data_->sell_uid_;
    }

    const int64 amount() const {
        return data_->amount_;
    }

    const int64 open_position_time() const {
        return data_->open_position_time_;
    }

    const int64 close_position_time() const {
        return data_->close_position_time_;
    }

    const double gross_profit() const {
        return data_->gross_profit_;
    }

    const double open_price() const {
        return data_->open_price_;
    }

    const double open_charge() const {
        return data_->open_charge_;
    }

    const int32 handle_type() const {
        return data_->handle_type_;
    }

    const int32 sell_handle_type() const {
        return data_->sell_handle_type_;
    }

    const int32 buy_handle_type() const {
        return data_->buy_handle_type_;
    }

    const std::string& symbol() const {
        return data_->symbol_;
    }

    void set_symbol(const std::string& symbol) {
        data_->symbol_ = symbol;
    }

    void set_order_id(const int64 order_id) {
        data_->order_id_ = order_id;
    }

    void set_buy_position_id(const int64 buy_position_id) {
        data_->buy_position_id_ = buy_position_id;
    }

    void set_sell_position_id(const int64 sell_position_id) {
        data_->sell_position_id_ = sell_position_id;
    }

    void set_buy_uid(const int64 buy_uid) {
        data_->buy_uid_ = buy_uid;
    }

    void set_sell_uid(const int64 sell_uid) {
        data_->sell_uid_ = sell_uid;
    }

    void set_amount(const int64 amount) {
        data_->amount_ = amount;
    }

    void set_open_position_time(const int64 open_position_time) {
        data_->open_position_time_ = open_position_time;
    }

    void set_close_position_time(const int64 close_position_time) {
        data_->close_position_time_ = close_position_time;
    }

    void set_gross_profit(const double gross_profit) {
        data_->gross_profit_ = gross_profit;
    }

    void set_open_price(const double open_price) {
        data_->open_price_ = open_price;
    }

    void set_open_charge(const double open_charge) {
        data_->open_charge_ = open_charge;
    }

    void set_handle_type(const int32 handle_type) {
        data_->handle_type_ = handle_type;
    }

    void set_sell_handle_type(const int32 handle_type) {
        data_->sell_handle_type_ = handle_type;
    }

    void set_buy_handle_type(const int32 handle_type) {
        data_->buy_handle_type_ = handle_type;
    }

    const int32 type() const {
        return data_->type_;
    }
    
    void set_match_type(){
        data_->buy_handle_type_ = MATCHES_ORDER;
        data_->sell_handle_type_ = MATCHES_ORDER;
        data_->handle_type_ = MATCHES_ORDER;
    }

    bool is_complete() {
        if (data_->buy_handle_type_==CONFIRM_ORDER && data_->sell_handle_type_==CONFIRM_ORDER){
            data_->handle_type_ = COMPLETE_ORDER;
            return true;
        }else
            return false;
    }

 private:
    class Data {
       public:
        Data()
            :refcount_(1)
            ,order_id_(0)
            ,buy_position_id_(0)
            ,sell_position_id_(0)
            ,buy_uid_(0)
            ,sell_uid_(0)
            ,amount_(0)
            ,open_position_time_(0)
            ,close_position_time_(0)
            ,gross_profit_(0.0)
            ,open_price_(0.0)
            ,open_charge_(0.0)
            ,type_(TRADES_ORDER_TYPE)
            ,handle_type_(NO_ORDER)
            ,sell_handle_type_(NO_ORDER)
            ,buy_handle_type_(NO_ORDER){}

        public:
            int64         order_id_;
            int64         buy_position_id_;
            int64         sell_position_id_;
            int64         buy_uid_;
            int64         sell_uid_;
            int64         amount_;
            int64         open_position_time_;
            int64         close_position_time_;
            int32         handle_type_;
            int32         sell_handle_type_;
            int32         buy_handle_type_;
            int32         type_;
            double        gross_profit_;
            double        open_price_;
            double        open_charge_;
            std::string   symbol_;


        static bool open_after(const Data* t_data, const Data* r_data) {
            return t_data->open_position_time_ > r_data->open_position_time_;
        }
        
        static bool open_price_after(const Data* t_data, const Data* r_data) {
                return t_data->open_price_ >= r_data->open_price_ && t_data->open_position_time_ > r_data->open_position_time_;
        }

        static bool price_after(const Data* t_data, const Data* r_data){
            return t_data->open_price_ > r_data->open_price_;
        }
        void AddRef() {
            __sync_fetch_and_add(&refcount_, 1);
        }
        void Release() {
            __sync_fetch_and_sub(&refcount_, 1);
            if (!refcount_)
                delete this;
        }

        private:
            int refcount_;
    };
    Data*  data_;
};

class Quotations {
public:
    Quotations();

    Quotations(const Quotations& quotations);

    Quotations& operator =(const Quotations& quotations);

    ~Quotations() {
        if (data_ != NULL) {
            data_->Release();
        }
    }

    static bool before(const Quotations& t_info, const Quotations& r_info) {
        return Data::before(t_info.data_, r_info.data_);
    }

    static bool after(const Quotations& t_info, const Quotations& r_info) {
        return Data::after(t_info.data_, r_info.data_);
    }

    static bool cmp(const Quotations& t_info, const Quotations& r_info) {
        return Data::after(t_info.data_, r_info.data_);
    }

    static bool asc(const Quotations& t_info, const Quotations& r_info) {
        return Data::asc(t_info.data_, r_info.data_);
    }

    static bool desc(const Quotations& t_info, const Quotations& r_info) {
        return Data::desc(t_info.data_, r_info.data_);
    }

    void set_platform_name(const std::string& platform) {
        if (data_)
            data_->platform_name_ = platform;
    }

    void set_symbol(const std::string& symbol) {
        if (data_)
            data_->symbol_ = symbol;
    }

    void set_exchange_name(const std::string& exchange_name) {
        if (data_)
            data_->exchange_name_ = exchange_name;
    }

    void set_current_price(const double current_price) {
        if (data_)
            data_->current_price_ = current_price;
    }

    void set_high_price(const double high_price) {
        if (data_)
            data_->high_price_ = high_price;
    }

    void set_low_price(const double low_price) {
        if (data_)
            data_->low_price_ = low_price;
    }

    void set_opening_today_price(const double opening_today_price) {
        if (data_)
            data_->opening_today_price_ = opening_today_price;
    }

    void set_closed_yesterday_price(const double closed_yesterday_price) {
        if (data_)
            data_->closed_yesterday_price_ = closed_yesterday_price;
    }

    void set_change(const double change) {
        if (data_)
            data_->change_ = change;
    }

    void set_pchg(const double pchg) {
        if (data_)
            data_->pchg_ = pchg;
    }

    void set_type(const int32 type) {
        if (data_)
            data_->type_ = type;
    }

    void set_current_unix_time(const int64 current_unix_time) {
        if (data_)
            data_->current_unix_time_ = current_unix_time;
    }

    const std::string& platform() const {
        if (data_)
            return data_->platform_name_;
    }

    const std::string& symbol() const {
        if (data_)
            return data_->symbol_;
    }

    const std::string& exchange_name() const {
        if (data_)
            return data_->exchange_name_;
    }
    const double current_price() const {
        if (data_)
            return data_->current_price_;
    }

    const double high_price() const {
        if (data_)
            return data_->high_price_;
    }

    const double low_price() const {
        if (data_)
            return data_->low_price_;
    }

    const double opening_today_price() const {
        if (data_)
            return data_->opening_today_price_;
    }

    const double closed_yesterday_price() const {
        if (data_)
            return data_->closed_yesterday_price_;
    }

    const double change() const {
        if (data_)
            return data_->change_;
    }

    const double pchg() const {
        if (data_)
            return data_->pchg_;
    }

    const int64 current_unix_time() const {
        if (data_)
            return data_->current_unix_time_;
    }

    const int32 type() const {
        if (data_)
            return data_->type_;
    }

    std::string ValueSerialize();
    void ValueDeserialize(std::string& str);

private:
    class Data {
    public:
        Data()
            : refcount_(1),
              type_(0),
              current_price_(0.0),
              high_price_(0.0),
              low_price_(0.0),
              opening_today_price_(0.0),
              closed_yesterday_price_(0.0),
              change_(0.0),
              pchg_(0.0),
              current_unix_time_(0) {
        }

        ~Data() {
        }

    public:
        std::string platform_name_;
        std::string symbol_;
        std::string exchange_name_;
        int32 type_;  //1,股票 2，现货 3，期货 4，明星
        double current_price_;
        double high_price_;
        double low_price_;
        double opening_today_price_;
        double closed_yesterday_price_;
        double change_;
        double pchg_;
        int64 current_unix_time_;

        static bool before(const Data* t_info, const Data* r_info) {
            if (t_info == NULL || r_info == NULL)
                return false;
            return t_info->current_unix_time_ <= r_info->current_unix_time_;
        }

        static bool after(const Data* t_info, const Data* r_info) {
            if (t_info == NULL || r_info == NULL)
                return false;
            return t_info->current_unix_time_ > r_info->current_unix_time_;
        }

        static bool asc(const Data* t_info, const Data* r_info) {
            if (t_info == NULL || r_info == NULL)
                return false;
            return t_info->change_ <= r_info->change_;
        }

        static bool desc(const Data* t_info, const Data* r_info) {
            if (t_info == NULL || r_info == NULL)
                return false;
            return t_info->change_ > r_info->change_;
        }
        void AddRef() {
            __sync_fetch_and_add(&refcount_, 1);
        }
        void Release() {
            __sync_fetch_and_sub(&refcount_, 1);
            if (!refcount_)
                delete this;
        }

    private:
        int refcount_;
    };
    Data* data_;
};

//
class StarInfo {
public:
    StarInfo();
    StarInfo(const StarInfo& starinfo);
    StarInfo& operator =(const StarInfo& starinfo);

    ~StarInfo() {
        if (data_ != NULL) {
            data_->Release();
        }
    }
    static bool sort_add_time(const StarInfo& t_info, const StarInfo& r_info) {
        return Data::sort_add_time(t_info.data_, r_info.data_);
    }

    static bool sort_hot_priority(const StarInfo& t_info, const StarInfo& r_info) {
        return Data::sort_hot_priority(t_info.data_, r_info.data_);
    }


    const double updown() const {
        return data_->updown_;
    }

    const int64 gender() const {
        return data_->gender_;
    }
    const int64 owntimes() const {
        return data_->owntimes_;
    }
    const int32 type() const {
        return data_->type_;
    }
    const int32 vip() const {
        return data_->vip_;
    }
    const std::string& symbol() const {
        return data_->symbol_;
    }
    const std::string& phone() const {
        return data_->phone_;
    }
    const std::string& name() const {
        return data_->name_;
    }
    const std::string& brief_url() const {
        return data_->brief_url_;
    }
    const std::string& pic() const {
        return data_->pic_;
    }
    const std::string& accid() const {
        return data_->accid_;
    }
    const std::string& weibo_index_id() const {
        return data_->weibo_index_id_;
    }
    const std::string& nationality() const {
        return data_->nationality_;
    }
    const std::string& nation() const{
        return data_->nation_;
    }
    const std::string& introduction() const {
        return data_->introduction_;
    }
    const std::string& quanpin() const {
        return data_->quanpin_;
    }

    const std::string& jianpin() const {
        return data_->jianpin_;
    }
    const int32 display_on_home() const {
        return data_->display_on_home_;
    }
    const int64 hot_priority1() const {
        return data_->hot_priority1_;
    }
    const int64 hot_priority2() const {
        return data_->hot_priority2_;
    }
    const std::string& home_pic() const {
        return data_->home_pic_;
    }
    const std::string& home_button_pic() const {
        return data_->home_button_pic_;
    }
    const int64 hot_add_time() const {
        return data_->add_time_;
    }
    const int32 publish_type() const {
        return data_->publish_type_;
    }
//----
    void set_weibo_index_id(const std::string& weibo_index_id) {
        data_->weibo_index_id_ = weibo_index_id;
    }

    void set_gender(const int64 gender) {
        data_->gender_ = gender;
    }
    void set_owntimes(const int64 owntimes) {
        data_->owntimes_ = owntimes;
    }
    void set_type(const int32 type) {
        data_->type_ = type;
    }
    void set_vip(const int64 vip) {
        data_->vip_ = vip;
    }

    void set_updown(const double updown) {
        data_->updown_ = updown;
    }

    void set_symbol(const std::string& symbol) {
        data_->symbol_ = symbol;
    }
    void set_phone(const std::string& phone) {
        data_->phone_ = phone;
    }
    void set_name(const std::string& value) {
        data_->name_ = value;
    }
    void set_brief_url(const std::string& value) {
        data_->brief_url_ = value;
    }
    void set_pic(const std::string& value) {
        data_->pic_ = value;
    }
    void set_accid(const std::string& value) {
        data_->accid_ = value;
    }
    void set_nation(const std::string& nation) {
        data_->nation_ = nation;
    }
    void set_nationality(const std::string& nationality) {
        data_->nationality_ = nationality;
    }
    void set_introduction(const std::string& introduction) {
        data_->introduction_ = introduction;
    }

    void set_jianpin(const std::string& jianpin) {
        data_->jianpin_ = jianpin;
    }

    void set_quanpin(const std::string& quanpin) {
        data_->quanpin_ = quanpin;
    }
    void set_display_on_home(const int32 i) {
        data_->display_on_home_ = i;
    }
    void set_hot_priority1(const int64 l) {
        data_->hot_priority1_ = l;
    }
    void set_hot_priority2(const int64 l) {
        data_->hot_priority2_ = l;
    }
    void set_home_pic(const std::string& pic) {
        data_->home_pic_ = pic;
    }
    void set_home_button_pic(const std::string& pic) {
        data_->home_button_pic_ = pic;
    }
    void set_add_time(const int64 l) {
        data_->add_time_ = l;
    }
    void set_publish_type(const int32 i) {
        data_->publish_type_ = i;
    }

    void ValueSerialization(base_logic::DictionaryValue* dict);

    class Data {
    public:
        Data()
            : refcount_(1),
              owntimes_(0),
              gender_(0),
              type_(0),
              vip_(0),
              updown_(0.0) {
        }

    public:
        int64 gender_;
        int64 owntimes_;
        int32 type_;
        int32 vip_; //加v明星
        double updown_;
        std::string symbol_; //明星代码
        std::string phone_;
        std::string name_;
        std::string brief_url_;
        std::string pic_;
        std::string accid_; //云信ip
        std::string weibo_index_id_;//微博热指数ID
        std::string nation_;//民族
        std::string nationality_;//国籍
        std::string introduction_;//简介
        std::string jianpin_;
        std::string quanpin_;
        int32 display_on_home_;//是否在主页显示 1-显示
        int64 hot_priority1_;//热度优先级1
        int64 hot_priority2_;//热度优先级2
        std::string home_pic_;//主页大图
        std::string home_button_pic_;//主页底部图片
        int64 add_time_;//创建时间
        int32 publish_type_;//0-预售 1-发售 2-流通

        static bool sort_add_time(const Data* t_info, const Data* r_info) {
            if (t_info == NULL || r_info == NULL)
                return false;
            return t_info->add_time_ > r_info->add_time_;
        }
        static bool sort_hot_priority(const Data* t_info, const Data* r_info) {
            if (t_info == NULL || r_info == NULL)
                return false;
            if(t_info->hot_priority1_ > r_info->hot_priority1_){
                return true;
            }else if(t_info->hot_priority1_ < r_info->hot_priority1_){
                return false;
            }else{
                return t_info->hot_priority2_ > r_info->hot_priority2_;
            }
        }

        void AddRef() {
            __sync_fetch_and_add(&refcount_, 1);
        }
        void Release() {
            __sync_fetch_and_sub(&refcount_, 1);
            if (!refcount_)
                delete this;
        }
    private:
        int refcount_;
    };
    Data* data_;
};


class TOwnStar {
public:
    TOwnStar();
    TOwnStar(const TOwnStar& starinfo);
    TOwnStar& operator =(const TOwnStar& starinfo);

    ~TOwnStar() {
        if (data_ != NULL) {
            data_->Release();
        }
    }
    const int64 uid() const {
        return data_->uid_;
    }
    const int64 ownseconds() const {
        return data_->ownseconds_;
    }
    const int32 appoint() const {
        return data_->appoint_;
    }

    const std::string& starname() const {
        return data_->starname_ ;
    }
    const std::string& starcode() const {
        return data_->starcode_;
    }
    const std::string& faccid() const {
        return data_->faccid_;
    }
    const std::string& headurl() const {
        return data_->head_url_;
    }
//----
    void set_uid(const int64 value) {
        data_->uid_ = value;
    }
    void set_ownseconds(const int64 value) {
        data_->ownseconds_ = value;
    }
    void set_appoint(const int32 value) {
        data_->appoint_ = value;
    }

    void set_starcode(const std::string& code) {
        data_->starcode_ = code;
    }
    void set_starname(const std::string& value) {
        data_->starname_ = value;
    }
    void set_faccid(const std::string& value) {
        data_->faccid_ = value;
    }
    void set_headurl(const std::string& value) {
        data_->head_url_ = value;
    }

    void ValueSerialization(base_logic::DictionaryValue* dict);

    class Data {
    public:
        Data()
            : uid_(1),
              ownseconds_(0),
              appoint_(0),
              refcount_(1) {
        }

    public:
        int64 uid_;
        int64 ownseconds_;
        int32 appoint_; //预约
        std::string starcode_; //明星代码
        std::string starname_;
        std::string faccid_;
        std::string head_url_;
        void AddRef() {
            __sync_fetch_and_add(&refcount_, 1);
        }
        void Release() {
            __sync_fetch_and_sub(&refcount_, 1);
            if (!refcount_)
                delete this;
        }
    private:
        int refcount_;
    };

    Data* data_;
};


class Comments {
 public:
  Comments();

  Comments(const Comments& comments);

  Comments& operator =(const Comments& comments);

  ~Comments() {
    if (data_ != NULL) {
      data_->Release();
    }
  }

  static bool before(const Comments& t_info, const Comments& r_info) {
    return Data::before(t_info.data_, r_info.data_);
  }

  static bool after(const Comments& t_info, const Comments& r_info) {
    return Data::after(t_info.data_, r_info.data_);
  }

  static bool cmp(const Comments& t_info, const Comments& r_info) {
    return Data::after(t_info.data_, r_info.data_);
  }

  void set_star_code(const std::string& value) {
    if (data_)
      data_->star_code_= value;
  }

  void set_fans_id(const std::string& value) {
    if (data_)
      data_->fans_id_ = value;
  }
  void set_nick_name(const std::string& value) {
    if (data_)
      data_->nick_name_ = value;
  }
  void set_comments(const std::string& value) {
    if (data_)
      data_->comments_= value;
  }
  void set_head_url(const std::string& value) {
    if (data_)
      data_->head_url_ = value;
  }
  void set_current_unix_time(const int64 current_unix_time) {
    if (data_)
      data_->current_unix_time_ = current_unix_time;
  }

  const std::string& star_code() const {
    if (data_)
      return data_->star_code_;
  }
  const std::string& comments() const {
    if (data_)
      return data_->comments_;
  }
  const std::string& head_url() const {
    if (data_)
      return data_->head_url_;
  }

  const std::string& fans_id() const {
    if (data_)
      return data_->fans_id_;
  }

  const std::string& nick_name() const {
    if (data_)
      return data_->nick_name_;
  }

  const int64 current_unix_time() const {
    if (data_)
      return data_->current_unix_time_;
  }

  std::string ValueSerialize();
  void ValueDeserialize(std::string& str);

 private:
  class Data {
   public:
    Data()
        : refcount_(1),
          current_unix_time_(0) {
    }

    ~Data() {
    }

   public:
    std::string star_code_; //platform_name_;
    std::string fans_id_; //symbol_;
    std::string nick_name_;//exchange_name_;
    std::string comments_;
    std::string head_url_;

    int64 current_unix_time_;

    static bool before(const Data* t_info, const Data* r_info) {
      if (t_info == NULL || r_info == NULL)
        return false;
      return t_info->current_unix_time_ <= r_info->current_unix_time_;
    }

    static bool after(const Data* t_info, const Data* r_info) {
      if (t_info == NULL || r_info == NULL)
        return false;
      return t_info->current_unix_time_ > r_info->current_unix_time_;
    }

    void AddRef() {
      __sync_fetch_and_add(&refcount_, 1);
    }
    void Release() {
      __sync_fetch_and_sub(&refcount_, 1);
      if (!refcount_)
        delete this;
    }

   private:
    int refcount_;
  };
  Data* data_;
};


class StarBrief {
 public:
  StarBrief();
  StarBrief(const StarBrief& starhead);
  StarBrief& operator =(const StarBrief& starhead);

  ~StarBrief() {
    if (data_ != NULL) {
      data_->Release();
    }
  }

  const int64 gender() const {
    return data_->gender_;
  }
  const int64 owntimes() const {
    return data_->owntimes_;
  }
  /*
  const int32 type() const {
    return data_->type_;
  }
  */
  const int32 vip() const {
    return data_->vip_;
  }
  const std::string& symbol() const {
    return data_->symbol_;
  }
  const std::string& nationality() const {
    return data_->nationality_;
  }
  const std::string& name() const {
    return data_->name_;
  }
  const std::string& head_url() const {
    return data_->head_url_;
  }
  const std::string& nation() const {
    return data_->nation_;
  }
  const std::string& work() const {
    return data_->work_;
  }
  const std::string& weibo_index_id() const {
   return data_->weibo_index_id_;
  }
  const std::string& constellaction() const {
   return data_->constellaction_;
  }
  const std::string& pic_url() const {
   return data_->pic_url_;
  }
  const std::string& birth() const {
   return data_->birth_;
  }
  const std::string& colleage() const {
   return data_->colleage_;
  }
  const std::string& introduction() const {
   return data_->introduction_;
  }
//----
  void set_weibo_index_id(const std::string& weibo_index_id) {
    data_->weibo_index_id_ = weibo_index_id;
  }

  void set_gender(const int64 gender) {
    data_->gender_ = gender;
  }
  
  void set_owntimes(const int64 owntimes) {
    data_->owntimes_ = owntimes;
  }
  /*
  void set_type(const int32 type) {
    data_->type_ = type;
  }
  */
  void set_vip(const int64 vip) {
    data_->vip_ = vip;
  }

  void set_introduction(const std::string &introduction) {
    data_->introduction_ = introduction;
  }

  void set_symbol(const std::string& symbol) {
    data_->symbol_ = symbol;
  }
  void set_nationality(const std::string& nationality) {
    data_->nationality_ = nationality;
  }
  void set_name(const std::string& value) {
    data_->name_ = value;
  }
  void set_head_url(const std::string& value) {
    data_->head_url_ = value;
  }
  void set_nation(const std::string& value) {
    data_->nation_ = value;
  }
  void set_work(const std::string& value) {
    data_->work_ = value;
  }
  void set_constellaction(const std::string& value) {
    data_->constellaction_ = value;
  }

  void set_pic_url(const std::string& value) {
    data_->pic_url_ = value;
  }

  void set_birth(const std::string& value) {
    data_->birth_ = value;
  }

  void set_colleage(const std::string& value) {
    data_->colleage_ = value;
  }
  void ValueSerialization(base_logic::DictionaryValue* dict);

  class Data {
   public:
    Data()
        : refcount_(1),
          owntimes_(0),
          gender_(0), 
          //type_(0),
          vip_(0) {
    }

   public:
    int64 gender_;
    int64 owntimes_;
//   int32 type_;
    int32 vip_; //加v明星
    std::string symbol_; //明星代码
    std::string nationality_; //国籍
    std::string name_;
    std::string head_url_; //头像
    std::string nation_; //民族
    std::string work_;//工作; 
    std::string weibo_index_id_;//微博热指数ID
    std::string constellaction_;//星座
    std::string pic_url_; //图片url
    std::string birth_; //生日
    std::string colleage_; //
    std::string introduction_; //简介

    void AddRef() {
      __sync_fetch_and_add(&refcount_, 1);
    }
    void Release() {
      __sync_fetch_and_sub(&refcount_, 1);
      if (!refcount_)
        delete this;
    }
   private:
    int refcount_;
  };
  Data* data_;
};

}  // namespace quotations_logic

#endif /* QUOTATIONS_PUB_LOGIC_QUOTATIONS_INFOS_H_ */
