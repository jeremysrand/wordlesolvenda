/*
 * main.h
 * wordlesolvenda
 *
 * Created by Jeremy Rand on 2024-07-17.
 * Copyright (c) 2024 ___ORGANIZATIONNAME___. All rights reserved.
 *
 */

#ifndef _GUARD_PROJECTwordlesolvenda_FILEmain_
#define _GUARD_PROJECTwordlesolvenda_FILEmain_


#define WS_RES_WINDOW 1001

#define WS_RES_WIN_X 10
#define WS_RES_WIN_Y 28
#define WS_RES_WIN_WIDTH 300
#define WS_RES_WIN_HEIGHT 167

#define WS_RES_CONTROL_LIST 1002

#define WS_RES_BTN_0_0 2001
#define WS_RES_BTN_0_1 2002
#define WS_RES_BTN_0_2 2003
#define WS_RES_BTN_0_3 2004
#define WS_RES_BTN_0_4 2005

#define WS_RES_BTN_1_0 2006
#define WS_RES_BTN_1_1 2007
#define WS_RES_BTN_1_2 2008
#define WS_RES_BTN_1_3 2009
#define WS_RES_BTN_1_4 2010

#define WS_RES_BTN_2_0 2011
#define WS_RES_BTN_2_1 2012
#define WS_RES_BTN_2_2 2013
#define WS_RES_BTN_2_3 2014
#define WS_RES_BTN_2_4 2015

#define WS_RES_BTN_3_0 2016
#define WS_RES_BTN_3_1 2017
#define WS_RES_BTN_3_2 2018
#define WS_RES_BTN_3_3 2019
#define WS_RES_BTN_3_4 2020

#define WS_RES_BTN_4_0 2021
#define WS_RES_BTN_4_1 2022
#define WS_RES_BTN_4_2 2023
#define WS_RES_BTN_4_3 2024
#define WS_RES_BTN_4_4 2025

#define WS_RES_BTN_5_0 2026
#define WS_RES_BTN_5_1 2027
#define WS_RES_BTN_5_2 2028
#define WS_RES_BTN_5_3 2029
#define WS_RES_BTN_5_4 2030

#define WS_RES_BTN_0_OK 2031
#define WS_RES_BTN_1_OK 2032
#define WS_RES_BTN_2_OK 2033
#define WS_RES_BTN_3_OK 2034
#define WS_RES_BTN_4_OK 2035
#define WS_RES_BTN_5_OK 2036

#define WS_RES_BTN_RESTART 2037

#define WS_RES_POPUP 2038
#define WS_RES_TEXT_1 2039
#define WS_RES_TEXT_2 2040

#define WS_RES_BTN_STR_EMPTY 3001
#define WS_RES_BTN_STR_A 3002
#define WS_RES_BTN_STR_B 3003
#define WS_RES_BTN_STR_C 3004
#define WS_RES_BTN_STR_D 3005
#define WS_RES_BTN_STR_E 3006
#define WS_RES_BTN_STR_F 3007
#define WS_RES_BTN_STR_G 3008
#define WS_RES_BTN_STR_H 3009
#define WS_RES_BTN_STR_I 3010
#define WS_RES_BTN_STR_J 3011
#define WS_RES_BTN_STR_K 3012
#define WS_RES_BTN_STR_L 3013
#define WS_RES_BTN_STR_M 3014
#define WS_RES_BTN_STR_N 3015
#define WS_RES_BTN_STR_O 3016
#define WS_RES_BTN_STR_P 3017
#define WS_RES_BTN_STR_Q 3018
#define WS_RES_BTN_STR_R 3019
#define WS_RES_BTN_STR_S 3020
#define WS_RES_BTN_STR_T 3021
#define WS_RES_BTN_STR_U 3022
#define WS_RES_BTN_STR_V 3023
#define WS_RES_BTN_STR_W 3024
#define WS_RES_BTN_STR_X 3025
#define WS_RES_BTN_STR_Y 3026
#define WS_RES_BTN_STR_Z 3027
#define WS_RES_BTN_STR_OK 3028
#define WS_RES_BTN_STR_NYT 3029
#define WS_RES_BTN_STR_CQ2 3030
#define WS_RES_BTN_STR_VARIANT 3031
#define WS_RES_BTN_STR_RESTART 3032

#define WS_RS_BTN_WHITE 4001
#define WS_RS_BTN_GREEN 4002
#define WS_RS_BTN_YELLOW 4003

#define WS_RES_MENU 5001
#define WS_RES_MENU_ITEM_NYT 5002
#define WS_RES_MENU_ITEM_CQ2 5003

#define WS_RES_BTN_SPACE_X 5
#define WS_RES_BTN_SPACE_Y 3
#define WS_RES_BTN_SPACE_WIDTH 35
#define WS_RES_BTN_SPACE_HEIGHT 14

#define WS_RES_BTN_OK_WIDTH 50

#define WS_RES_TEXT_HEIGHT 10
#define WS_RES_TEXT_1_Y 18
#define WS_RES_TEXT_2_Y WS_RES_TEXT_1_Y+WS_RES_TEXT_HEIGHT

#define WS_RES_BTN_ROW_0 40
#define WS_RES_BTN_ROW_1 WS_RES_BTN_ROW_0+WS_RES_BTN_SPACE_HEIGHT+WS_RES_BTN_SPACE_Y
#define WS_RES_BTN_ROW_2 WS_RES_BTN_ROW_1+WS_RES_BTN_SPACE_HEIGHT+WS_RES_BTN_SPACE_Y
#define WS_RES_BTN_ROW_3 WS_RES_BTN_ROW_2+WS_RES_BTN_SPACE_HEIGHT+WS_RES_BTN_SPACE_Y
#define WS_RES_BTN_ROW_4 WS_RES_BTN_ROW_3+WS_RES_BTN_SPACE_HEIGHT+WS_RES_BTN_SPACE_Y
#define WS_RES_BTN_ROW_5 WS_RES_BTN_ROW_4+WS_RES_BTN_SPACE_HEIGHT+WS_RES_BTN_SPACE_Y

#define WS_RES_BTN_COL_0 (4*WS_RES_BTN_SPACE_X)
#define WS_RES_BTN_COL_1 WS_RES_BTN_COL_0+WS_RES_BTN_SPACE_WIDTH+WS_RES_BTN_SPACE_X
#define WS_RES_BTN_COL_2 WS_RES_BTN_COL_1+WS_RES_BTN_SPACE_WIDTH+WS_RES_BTN_SPACE_X
#define WS_RES_BTN_COL_3 WS_RES_BTN_COL_2+WS_RES_BTN_SPACE_WIDTH+WS_RES_BTN_SPACE_X
#define WS_RES_BTN_COL_4 WS_RES_BTN_COL_3+WS_RES_BTN_SPACE_WIDTH+WS_RES_BTN_SPACE_X
#define WS_RES_BTN_COL_OK WS_RES_BTN_COL_4+WS_RES_BTN_SPACE_WIDTH+(2*WS_RES_BTN_SPACE_X)

#define WS_RES_BTN_RESTART_WIDTH 100
#define WS_RES_BIN_RESTART_LEFT (WS_RES_WIN_WIDTH-WS_RES_BTN_RESTART_WIDTH)/2
#define WS_RES_BIN_RESTART_RIGHT (WS_RES_WIN_WIDTH+WS_RES_BTN_RESTART_WIDTH)/2
#define WS_RES_BTN_RESTART_Y WS_RES_BTN_ROW_5+WS_RES_BTN_SPACE_HEIGHT+(2*WS_RES_BTN_SPACE_Y)

#endif /* defined(_GUARD_PROJECTwordlesolvenda_FILEmain_) */
