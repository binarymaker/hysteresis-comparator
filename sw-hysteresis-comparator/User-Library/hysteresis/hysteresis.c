
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

#include "hysteresis.h"
#include "hysteresis-cfg.h"

void
hysteresis_create(hysteresis_t *context, int32_t threshold,
                  uint32_t delay_time)
{
  context->threshold = threshold;
  context->delay_time = delay_time;
  context->last_time = 0;
  context->hys_state = false;
  context->last_state = false;
}

bool
hysteresis_compare(hysteresis_t *context, int32_t value)
{
  bool compare;
  uint32_t now = TICK_TIMER;

  /* compare value to threshold */
  if (value > context->threshold)
  {
    compare = true;
  }
  else
  {
    compare = false;
  }

  /* Mark last data changed time */
  if (compare != context->last_state)
  {
    context->last_state = compare;
    context->last_time = now;
  }

  /* compare last data time to present time */
  if (now - context->last_time > context->delay_time)
  {
    context->hys_state = compare;
  }

  return context->hys_state;
}

void
hysteresis_set_threshold(hysteresis_t *context,
                         int32_t threshold)
{
  context->threshold = threshold;
}