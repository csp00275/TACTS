/**
  ******************************************************************************
  * @file    fourline_data_params.h
  * @author  AST Embedded Analytics Research Platform
  * @date    Tue Nov 19 15:13:08 2024
  * @brief   AI Tool Automatic Code Generator for Embedded NN computing
  ******************************************************************************
  * Copyright (c) 2024 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  ******************************************************************************
  */

#ifndef FOURLINE_DATA_PARAMS_H
#define FOURLINE_DATA_PARAMS_H
#pragma once

#include "ai_platform.h"

/*
#define AI_FOURLINE_DATA_WEIGHTS_PARAMS \
  (AI_HANDLE_PTR(&ai_fourline_data_weights_params[1]))
*/

#define AI_FOURLINE_DATA_CONFIG               (NULL)


#define AI_FOURLINE_DATA_ACTIVATIONS_SIZES \
  { 3584, }
#define AI_FOURLINE_DATA_ACTIVATIONS_SIZE     (3584)
#define AI_FOURLINE_DATA_ACTIVATIONS_COUNT    (1)
#define AI_FOURLINE_DATA_ACTIVATION_1_SIZE    (3584)



#define AI_FOURLINE_DATA_WEIGHTS_SIZES \
  { 281168, }
#define AI_FOURLINE_DATA_WEIGHTS_SIZE         (281168)
#define AI_FOURLINE_DATA_WEIGHTS_COUNT        (1)
#define AI_FOURLINE_DATA_WEIGHT_1_SIZE        (281168)



#define AI_FOURLINE_DATA_ACTIVATIONS_TABLE_GET() \
  (&g_fourline_activations_table[1])

extern ai_handle g_fourline_activations_table[1 + 2];



#define AI_FOURLINE_DATA_WEIGHTS_TABLE_GET() \
  (&g_fourline_weights_table[1])

extern ai_handle g_fourline_weights_table[1 + 2];


#endif    /* FOURLINE_DATA_PARAMS_H */
