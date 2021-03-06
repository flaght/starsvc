//  Copyright (c) 2017-2018 The STAR Authors. All rights reserved.
//  Created on: 2017年2月12日 Author: kerry

#ifndef STAR_HISTORY_OPERATOR_CODE_H_
#define STAR_HISTORY_OPERATOR_CODE_H_


#include "net/comm_head.h"
#include "comm/comm_head.h"


namespace record_logic {

#define R_TODAY_POSITION_RECORD  HISTORY_TYPE * 1000 + 1
#define S_TODAY_POSITION_RECORD  HISTORY_TYPE * 1000 + 2

#define R_ALL_POSITION_RECORD    HISTORY_TYPE * 1000 + 5
#define S_ALL_POSITION_RECORD    HISTORY_TYPE * 1000 + 6


#define R_TODAY_ORDER_RECORD  HISTORY_TYPE * 1000 + 7
#define S_TODAY_ORDER_RECORD  HISTORY_TYPE * 1000 + 8

#define R_ALL_ORDER_RECORD    HISTORY_TYPE * 1000 + 9
#define S_ALL_ORDER_RECORD    HISTORY_TYPE * 1000 + 10

#define R_FANS_POSITION      HISTORY_TYPE * 1000 + 11
#define S_FANS_POSITION      HISTORY_TYPE * 1000 + 12

#define R_FANS_ORDER         HISTORY_TYPE * 1000 + 15
#define S_FANS_ORDER         HISTORY_TYPE * 1000 + 16

#define R_POSITION_COUNT     HISTORY_TYPE * 1000 + 17
#define S_POSITION_COUNT     HISTORY_TYPE * 1000 + 18
}
#endif
