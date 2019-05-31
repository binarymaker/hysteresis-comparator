
/**
  ******************************************************************************
  * ______  _                             ___  ___        _               
  * | ___ \(_)                            |  \/  |       | |              
  * | |_/ / _  _ __    __ _  _ __  _   _  | .  . |  __ _ | | __ ___  _ __ 
  * | ___ \| || '_ \  / _` || '__|| | | | | |\/| | / _` || |/ // _ \| '__|
  * | |_/ /| || | | || (_| || |   | |_| | | |  | || (_| ||   <|  __/| |   
  * \____/ |_||_| |_| \__,_||_|    \__, | \_|  |_/ \__,_||_|\_\\___||_|   
  *                                 __/ |                                 
  *                                |___/                                  
  *                                                                       
  * Copyright (C) 2019 Binary Maker - All Rights Reserved
  *
  * This program and the accompanying materials are made available
  * under the terms described in the LICENSE file which accompanies
  * this distribution.
  * Written by Binary Maker <https://github.com/binarymaker>
  ******************************************************************************
  */

#ifndef BM_2b5ba44c_837a_11e9_ace5_f914ac843fcc
#define BM_2b5ba44c_837a_11e9_ace5_f914ac843fcc

/**
 * @file hysteresis.h
 * @author binary maker <https://github.com/binarymaker>
 * @brief digital signal hysteresis comparetor (schmitt trigger)
 * @date 2019-05-31
 */

/*                                                   
                      /\/\                             ,  ,
signal            /\/\    /\/\                     /\/\ || /\/\
  threshold->-/\/\------------/\/\ ------------/\/\-----||-----/\/\--
                ^               ^  /\/\    /\/\  ^      ||            
                |               |      /\/\      |      ||             
             Noise make error in compare --------+      ^^-spike
                  ____________                     _____  _____       
caparator     ||||            ||||_____________||||     ||     ||||__ 
output
                     ______________                  _______________
hysteresis    ______|              |________________|               |_
comparetor
output

*/
#include "stdint.h"
#include "stdbool.h"

typedef struct hysteresis_s
{
  int32_t threshold;
  uint32_t delay_time;
  uint32_t last_time;
  bool last_state;
  bool hys_state;
} hysteresis_t;

/**
 * @brief Hysteresis object initialization 
 * 
 * @param context [in] instance of hysteresis object
 * @param threshold [in] comparator threshold value
 * @param delay_time [in] time taken for state change 
 *                        delay_time > Noise signal max width
 */
void hysteresis_create(hysteresis_t *context, int32_t threshold,
                       uint32_t delay_time);

/**
 * @brief Hysteresis value compare process
 * 
 * @param context [in] instance of hysteresis object
 * @param value [in] campare value
 * @return true - campare value is greaterthen threshold
 * @return false - campare value is lessthen or equal to threshold
 */
bool hysteresis_compare(hysteresis_t *context, int32_t value);

/**
 * @brief Assign comparator threshold value
 * 
 * @param context [in] instance of hysteresis object
 * @param threshold [in] comparator threshold value
 */
void hysteresis_set_threshold(hysteresis_t *context,
                              int32_t threshold);

#endif // BM_2b5ba44c_837a_11e9_ace5_f914ac843fcc
