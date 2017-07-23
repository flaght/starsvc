//  Copyright (c) 2016-2017 The quotations Authors. All rights reserved.
//  Created on: 2017年5月30日 Author: kerry

#ifndef STAR_QUOTATIONS_OPERATOR_CODE_H_
#define STAR_QUOTATIONS_OPERATOR_CODE_H_


#include "net/comm_head.h"


namespace quatations_logic {

#define LOGIN_QUOTATIONS               2001
#define R_QUOTATIONS_REAL_TIME_DATA    QUOTATIONS_TYPE * 1000 + 1
#define S_QUOTATIONS_REAL_TIME_DATA    QUOTATIONS_TYPE * 1000 + 2
#define R_QUOTATIONS_TIME_LINE_DATA    QUOTATIONS_TYPE * 1000 + 3
#define S_QUOTATIONS_TIME_LINE_DATA    QUOTATIONS_TYPE * 1000 + 4
#define R_KCHART_TIME_LINE_DATA        QUOTATIONS_TYPE * 1000 + 5
#define S_KCHART_TIME_LINE_DATA        QUOTATIONS_TYPE * 1000 + 6
#define R_SYMBOL_LIST                  QUOTATIONS_TYPE * 1000 + 7
#define S_SYMBOL_LIST                  QUOTATIONS_TYPE * 1000 + 8
#define R_HOME_SYMBOL_LIST             QUOTATIONS_TYPE * 1000 + 9
#define S_HOME_SYMBOL_LIST             QUOTATIONS_TYPE * 1000 + 10
}
#endif
