/**
  ******************************************************************************
  * @file    threeline.c
  * @author  AST Embedded Analytics Research Platform
  * @date    Sun Mar  3 00:00:07 2024
  * @brief   AI Tool Automatic Code Generator for Embedded NN computing
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2024 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  ******************************************************************************
  */


#include "threeline.h"
#include "threeline_data.h"

#include "ai_platform.h"
#include "ai_platform_interface.h"
#include "ai_math_helpers.h"

#include "core_common.h"
#include "core_convert.h"

#include "layers.h"



#undef AI_NET_OBJ_INSTANCE
#define AI_NET_OBJ_INSTANCE g_threeline
 
#undef AI_THREELINE_MODEL_SIGNATURE
#define AI_THREELINE_MODEL_SIGNATURE     "bd9417f0434353ab6eb6a3e774db050e"

#ifndef AI_TOOLS_REVISION_ID
#define AI_TOOLS_REVISION_ID     ""
#endif

#undef AI_TOOLS_DATE_TIME
#define AI_TOOLS_DATE_TIME   "Sun Mar  3 00:00:07 2024"

#undef AI_TOOLS_COMPILE_TIME
#define AI_TOOLS_COMPILE_TIME    __DATE__ " " __TIME__

#undef AI_THREELINE_N_BATCHES
#define AI_THREELINE_N_BATCHES         (1)

static ai_ptr g_threeline_activations_map[1] = AI_C_ARRAY_INIT;
static ai_ptr g_threeline_weights_map[1] = AI_C_ARRAY_INIT;



/**  Array declarations section  **********************************************/
/* Array#0 */
AI_ARRAY_OBJ_DECLARE(
  conv2d_2_conv2d_bias_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 16, AI_STATIC)
/* Array#1 */
AI_ARRAY_OBJ_DECLARE(
  dense_12_dense_weights_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 39936, AI_STATIC)
/* Array#2 */
AI_ARRAY_OBJ_DECLARE(
  dense_12_dense_bias_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 64, AI_STATIC)
/* Array#3 */
AI_ARRAY_OBJ_DECLARE(
  dense_13_dense_weights_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 4096, AI_STATIC)
/* Array#4 */
AI_ARRAY_OBJ_DECLARE(
  dense_13_dense_bias_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 64, AI_STATIC)
/* Array#5 */
AI_ARRAY_OBJ_DECLARE(
  dense_14_dense_weights_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 4096, AI_STATIC)
/* Array#6 */
AI_ARRAY_OBJ_DECLARE(
  dense_14_dense_bias_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 64, AI_STATIC)
/* Array#7 */
AI_ARRAY_OBJ_DECLARE(
  dense_15_dense_weights_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 4096, AI_STATIC)
/* Array#8 */
AI_ARRAY_OBJ_DECLARE(
  dense_15_dense_bias_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 64, AI_STATIC)
/* Array#9 */
AI_ARRAY_OBJ_DECLARE(
  dense_16_dense_weights_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 4096, AI_STATIC)
/* Array#10 */
AI_ARRAY_OBJ_DECLARE(
  dense_16_dense_bias_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 64, AI_STATIC)
/* Array#11 */
AI_ARRAY_OBJ_DECLARE(
  dense_17_dense_weights_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 256, AI_STATIC)
/* Array#12 */
AI_ARRAY_OBJ_DECLARE(
  dense_17_dense_bias_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 4, AI_STATIC)
/* Array#13 */
AI_ARRAY_OBJ_DECLARE(
  input_0_output_array, AI_ARRAY_FORMAT_FLOAT|AI_FMT_FLAG_IS_IO,
  NULL, NULL, 39, AI_STATIC)
/* Array#14 */
AI_ARRAY_OBJ_DECLARE(
  conv2d_2_conv2d_output_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 624, AI_STATIC)
/* Array#15 */
AI_ARRAY_OBJ_DECLARE(
  conv2d_2_output_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 624, AI_STATIC)
/* Array#16 */
AI_ARRAY_OBJ_DECLARE(
  dense_12_dense_output_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 64, AI_STATIC)
/* Array#17 */
AI_ARRAY_OBJ_DECLARE(
  dense_12_output_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 64, AI_STATIC)
/* Array#18 */
AI_ARRAY_OBJ_DECLARE(
  dense_13_dense_output_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 64, AI_STATIC)
/* Array#19 */
AI_ARRAY_OBJ_DECLARE(
  dense_13_output_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 64, AI_STATIC)
/* Array#20 */
AI_ARRAY_OBJ_DECLARE(
  dense_14_dense_output_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 64, AI_STATIC)
/* Array#21 */
AI_ARRAY_OBJ_DECLARE(
  dense_14_output_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 64, AI_STATIC)
/* Array#22 */
AI_ARRAY_OBJ_DECLARE(
  dense_15_dense_output_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 64, AI_STATIC)
/* Array#23 */
AI_ARRAY_OBJ_DECLARE(
  dense_15_output_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 64, AI_STATIC)
/* Array#24 */
AI_ARRAY_OBJ_DECLARE(
  dense_16_dense_output_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 64, AI_STATIC)
/* Array#25 */
AI_ARRAY_OBJ_DECLARE(
  dense_16_output_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 64, AI_STATIC)
/* Array#26 */
AI_ARRAY_OBJ_DECLARE(
  dense_17_dense_output_array, AI_ARRAY_FORMAT_FLOAT|AI_FMT_FLAG_IS_IO,
  NULL, NULL, 4, AI_STATIC)
/* Array#27 */
AI_ARRAY_OBJ_DECLARE(
  conv2d_2_conv2d_weights_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 64, AI_STATIC)
/**  Tensor declarations section  *********************************************/
/* Tensor #0 */
AI_TENSOR_OBJ_DECLARE(
  conv2d_2_conv2d_bias, AI_STATIC,
  0, 0x0,
  AI_SHAPE_INIT(4, 1, 16, 1, 1), AI_STRIDE_INIT(4, 4, 4, 64, 64),
  1, &conv2d_2_conv2d_bias_array, NULL)

/* Tensor #1 */
AI_TENSOR_OBJ_DECLARE(
  dense_12_dense_weights, AI_STATIC,
  1, 0x0,
  AI_SHAPE_INIT(4, 624, 64, 1, 1), AI_STRIDE_INIT(4, 4, 2496, 159744, 159744),
  1, &dense_12_dense_weights_array, NULL)

/* Tensor #2 */
AI_TENSOR_OBJ_DECLARE(
  dense_12_dense_bias, AI_STATIC,
  2, 0x0,
  AI_SHAPE_INIT(4, 1, 64, 1, 1), AI_STRIDE_INIT(4, 4, 4, 256, 256),
  1, &dense_12_dense_bias_array, NULL)

/* Tensor #3 */
AI_TENSOR_OBJ_DECLARE(
  dense_13_dense_weights, AI_STATIC,
  3, 0x0,
  AI_SHAPE_INIT(4, 64, 64, 1, 1), AI_STRIDE_INIT(4, 4, 256, 16384, 16384),
  1, &dense_13_dense_weights_array, NULL)

/* Tensor #4 */
AI_TENSOR_OBJ_DECLARE(
  dense_13_dense_bias, AI_STATIC,
  4, 0x0,
  AI_SHAPE_INIT(4, 1, 64, 1, 1), AI_STRIDE_INIT(4, 4, 4, 256, 256),
  1, &dense_13_dense_bias_array, NULL)

/* Tensor #5 */
AI_TENSOR_OBJ_DECLARE(
  dense_14_dense_weights, AI_STATIC,
  5, 0x0,
  AI_SHAPE_INIT(4, 64, 64, 1, 1), AI_STRIDE_INIT(4, 4, 256, 16384, 16384),
  1, &dense_14_dense_weights_array, NULL)

/* Tensor #6 */
AI_TENSOR_OBJ_DECLARE(
  dense_14_dense_bias, AI_STATIC,
  6, 0x0,
  AI_SHAPE_INIT(4, 1, 64, 1, 1), AI_STRIDE_INIT(4, 4, 4, 256, 256),
  1, &dense_14_dense_bias_array, NULL)

/* Tensor #7 */
AI_TENSOR_OBJ_DECLARE(
  dense_15_dense_weights, AI_STATIC,
  7, 0x0,
  AI_SHAPE_INIT(4, 64, 64, 1, 1), AI_STRIDE_INIT(4, 4, 256, 16384, 16384),
  1, &dense_15_dense_weights_array, NULL)

/* Tensor #8 */
AI_TENSOR_OBJ_DECLARE(
  dense_15_dense_bias, AI_STATIC,
  8, 0x0,
  AI_SHAPE_INIT(4, 1, 64, 1, 1), AI_STRIDE_INIT(4, 4, 4, 256, 256),
  1, &dense_15_dense_bias_array, NULL)

/* Tensor #9 */
AI_TENSOR_OBJ_DECLARE(
  dense_16_dense_weights, AI_STATIC,
  9, 0x0,
  AI_SHAPE_INIT(4, 64, 64, 1, 1), AI_STRIDE_INIT(4, 4, 256, 16384, 16384),
  1, &dense_16_dense_weights_array, NULL)

/* Tensor #10 */
AI_TENSOR_OBJ_DECLARE(
  dense_16_dense_bias, AI_STATIC,
  10, 0x0,
  AI_SHAPE_INIT(4, 1, 64, 1, 1), AI_STRIDE_INIT(4, 4, 4, 256, 256),
  1, &dense_16_dense_bias_array, NULL)

/* Tensor #11 */
AI_TENSOR_OBJ_DECLARE(
  dense_17_dense_weights, AI_STATIC,
  11, 0x0,
  AI_SHAPE_INIT(4, 64, 4, 1, 1), AI_STRIDE_INIT(4, 4, 256, 1024, 1024),
  1, &dense_17_dense_weights_array, NULL)

/* Tensor #12 */
AI_TENSOR_OBJ_DECLARE(
  dense_17_dense_bias, AI_STATIC,
  12, 0x0,
  AI_SHAPE_INIT(4, 1, 4, 1, 1), AI_STRIDE_INIT(4, 4, 4, 16, 16),
  1, &dense_17_dense_bias_array, NULL)

/* Tensor #13 */
AI_TENSOR_OBJ_DECLARE(
  input_0_output, AI_STATIC,
  13, 0x0,
  AI_SHAPE_INIT(4, 1, 1, 13, 3), AI_STRIDE_INIT(4, 4, 4, 4, 52),
  1, &input_0_output_array, NULL)

/* Tensor #14 */
AI_TENSOR_OBJ_DECLARE(
  conv2d_2_conv2d_output, AI_STATIC,
  14, 0x0,
  AI_SHAPE_INIT(4, 1, 16, 13, 3), AI_STRIDE_INIT(4, 4, 4, 64, 832),
  1, &conv2d_2_conv2d_output_array, NULL)

/* Tensor #15 */
AI_TENSOR_OBJ_DECLARE(
  conv2d_2_output, AI_STATIC,
  15, 0x0,
  AI_SHAPE_INIT(4, 1, 16, 13, 3), AI_STRIDE_INIT(4, 4, 4, 64, 832),
  1, &conv2d_2_output_array, NULL)

/* Tensor #16 */
AI_TENSOR_OBJ_DECLARE(
  conv2d_2_output0, AI_STATIC,
  16, 0x0,
  AI_SHAPE_INIT(4, 1, 624, 1, 1), AI_STRIDE_INIT(4, 4, 4, 2496, 2496),
  1, &conv2d_2_output_array, NULL)

/* Tensor #17 */
AI_TENSOR_OBJ_DECLARE(
  dense_12_dense_output, AI_STATIC,
  17, 0x0,
  AI_SHAPE_INIT(4, 1, 64, 1, 1), AI_STRIDE_INIT(4, 4, 4, 256, 256),
  1, &dense_12_dense_output_array, NULL)

/* Tensor #18 */
AI_TENSOR_OBJ_DECLARE(
  dense_12_output, AI_STATIC,
  18, 0x0,
  AI_SHAPE_INIT(4, 1, 64, 1, 1), AI_STRIDE_INIT(4, 4, 4, 256, 256),
  1, &dense_12_output_array, NULL)

/* Tensor #19 */
AI_TENSOR_OBJ_DECLARE(
  dense_13_dense_output, AI_STATIC,
  19, 0x0,
  AI_SHAPE_INIT(4, 1, 64, 1, 1), AI_STRIDE_INIT(4, 4, 4, 256, 256),
  1, &dense_13_dense_output_array, NULL)

/* Tensor #20 */
AI_TENSOR_OBJ_DECLARE(
  dense_13_output, AI_STATIC,
  20, 0x0,
  AI_SHAPE_INIT(4, 1, 64, 1, 1), AI_STRIDE_INIT(4, 4, 4, 256, 256),
  1, &dense_13_output_array, NULL)

/* Tensor #21 */
AI_TENSOR_OBJ_DECLARE(
  dense_14_dense_output, AI_STATIC,
  21, 0x0,
  AI_SHAPE_INIT(4, 1, 64, 1, 1), AI_STRIDE_INIT(4, 4, 4, 256, 256),
  1, &dense_14_dense_output_array, NULL)

/* Tensor #22 */
AI_TENSOR_OBJ_DECLARE(
  dense_14_output, AI_STATIC,
  22, 0x0,
  AI_SHAPE_INIT(4, 1, 64, 1, 1), AI_STRIDE_INIT(4, 4, 4, 256, 256),
  1, &dense_14_output_array, NULL)

/* Tensor #23 */
AI_TENSOR_OBJ_DECLARE(
  dense_15_dense_output, AI_STATIC,
  23, 0x0,
  AI_SHAPE_INIT(4, 1, 64, 1, 1), AI_STRIDE_INIT(4, 4, 4, 256, 256),
  1, &dense_15_dense_output_array, NULL)

/* Tensor #24 */
AI_TENSOR_OBJ_DECLARE(
  dense_15_output, AI_STATIC,
  24, 0x0,
  AI_SHAPE_INIT(4, 1, 64, 1, 1), AI_STRIDE_INIT(4, 4, 4, 256, 256),
  1, &dense_15_output_array, NULL)

/* Tensor #25 */
AI_TENSOR_OBJ_DECLARE(
  dense_16_dense_output, AI_STATIC,
  25, 0x0,
  AI_SHAPE_INIT(4, 1, 64, 1, 1), AI_STRIDE_INIT(4, 4, 4, 256, 256),
  1, &dense_16_dense_output_array, NULL)

/* Tensor #26 */
AI_TENSOR_OBJ_DECLARE(
  dense_16_output, AI_STATIC,
  26, 0x0,
  AI_SHAPE_INIT(4, 1, 64, 1, 1), AI_STRIDE_INIT(4, 4, 4, 256, 256),
  1, &dense_16_output_array, NULL)

/* Tensor #27 */
AI_TENSOR_OBJ_DECLARE(
  dense_17_dense_output, AI_STATIC,
  27, 0x0,
  AI_SHAPE_INIT(4, 1, 4, 1, 1), AI_STRIDE_INIT(4, 4, 4, 16, 16),
  1, &dense_17_dense_output_array, NULL)

/* Tensor #28 */
AI_TENSOR_OBJ_DECLARE(
  conv2d_2_conv2d_weights, AI_STATIC,
  28, 0x0,
  AI_SHAPE_INIT(4, 1, 2, 2, 16), AI_STRIDE_INIT(4, 4, 4, 64, 128),
  1, &conv2d_2_conv2d_weights_array, NULL)



/**  Layer declarations section  **********************************************/


AI_TENSOR_CHAIN_OBJ_DECLARE(
  dense_17_dense_chain, AI_STATIC_CONST, 4,
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &dense_16_output),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &dense_17_dense_output),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 2, &dense_17_dense_weights, &dense_17_dense_bias),
  AI_TENSOR_LIST_OBJ_EMPTY
)

AI_LAYER_OBJ_DECLARE(
  dense_17_dense_layer, 7,
  DENSE_TYPE, 0x0, NULL,
  dense, forward_dense,
  &dense_17_dense_chain,
  NULL, &dense_17_dense_layer, AI_STATIC, 
)

AI_TENSOR_CHAIN_OBJ_DECLARE(
  dense_16_chain, AI_STATIC_CONST, 4,
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &dense_16_dense_output),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &dense_16_output),
  AI_TENSOR_LIST_OBJ_EMPTY,
  AI_TENSOR_LIST_OBJ_EMPTY
)

AI_LAYER_OBJ_DECLARE(
  dense_16_layer, 6,
  NL_TYPE, 0x0, NULL,
  nl, forward_relu,
  &dense_16_chain,
  NULL, &dense_17_dense_layer, AI_STATIC, 
  .nl_params = NULL, 
)

AI_TENSOR_CHAIN_OBJ_DECLARE(
  dense_16_dense_chain, AI_STATIC_CONST, 4,
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &dense_15_output),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &dense_16_dense_output),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 2, &dense_16_dense_weights, &dense_16_dense_bias),
  AI_TENSOR_LIST_OBJ_EMPTY
)

AI_LAYER_OBJ_DECLARE(
  dense_16_dense_layer, 6,
  DENSE_TYPE, 0x0, NULL,
  dense, forward_dense,
  &dense_16_dense_chain,
  NULL, &dense_16_layer, AI_STATIC, 
)

AI_TENSOR_CHAIN_OBJ_DECLARE(
  dense_15_chain, AI_STATIC_CONST, 4,
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &dense_15_dense_output),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &dense_15_output),
  AI_TENSOR_LIST_OBJ_EMPTY,
  AI_TENSOR_LIST_OBJ_EMPTY
)

AI_LAYER_OBJ_DECLARE(
  dense_15_layer, 5,
  NL_TYPE, 0x0, NULL,
  nl, forward_relu,
  &dense_15_chain,
  NULL, &dense_16_dense_layer, AI_STATIC, 
  .nl_params = NULL, 
)

AI_TENSOR_CHAIN_OBJ_DECLARE(
  dense_15_dense_chain, AI_STATIC_CONST, 4,
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &dense_14_output),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &dense_15_dense_output),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 2, &dense_15_dense_weights, &dense_15_dense_bias),
  AI_TENSOR_LIST_OBJ_EMPTY
)

AI_LAYER_OBJ_DECLARE(
  dense_15_dense_layer, 5,
  DENSE_TYPE, 0x0, NULL,
  dense, forward_dense,
  &dense_15_dense_chain,
  NULL, &dense_15_layer, AI_STATIC, 
)

AI_TENSOR_CHAIN_OBJ_DECLARE(
  dense_14_chain, AI_STATIC_CONST, 4,
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &dense_14_dense_output),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &dense_14_output),
  AI_TENSOR_LIST_OBJ_EMPTY,
  AI_TENSOR_LIST_OBJ_EMPTY
)

AI_LAYER_OBJ_DECLARE(
  dense_14_layer, 4,
  NL_TYPE, 0x0, NULL,
  nl, forward_relu,
  &dense_14_chain,
  NULL, &dense_15_dense_layer, AI_STATIC, 
  .nl_params = NULL, 
)

AI_TENSOR_CHAIN_OBJ_DECLARE(
  dense_14_dense_chain, AI_STATIC_CONST, 4,
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &dense_13_output),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &dense_14_dense_output),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 2, &dense_14_dense_weights, &dense_14_dense_bias),
  AI_TENSOR_LIST_OBJ_EMPTY
)

AI_LAYER_OBJ_DECLARE(
  dense_14_dense_layer, 4,
  DENSE_TYPE, 0x0, NULL,
  dense, forward_dense,
  &dense_14_dense_chain,
  NULL, &dense_14_layer, AI_STATIC, 
)

AI_TENSOR_CHAIN_OBJ_DECLARE(
  dense_13_chain, AI_STATIC_CONST, 4,
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &dense_13_dense_output),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &dense_13_output),
  AI_TENSOR_LIST_OBJ_EMPTY,
  AI_TENSOR_LIST_OBJ_EMPTY
)

AI_LAYER_OBJ_DECLARE(
  dense_13_layer, 3,
  NL_TYPE, 0x0, NULL,
  nl, forward_relu,
  &dense_13_chain,
  NULL, &dense_14_dense_layer, AI_STATIC, 
  .nl_params = NULL, 
)

AI_TENSOR_CHAIN_OBJ_DECLARE(
  dense_13_dense_chain, AI_STATIC_CONST, 4,
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &dense_12_output),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &dense_13_dense_output),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 2, &dense_13_dense_weights, &dense_13_dense_bias),
  AI_TENSOR_LIST_OBJ_EMPTY
)

AI_LAYER_OBJ_DECLARE(
  dense_13_dense_layer, 3,
  DENSE_TYPE, 0x0, NULL,
  dense, forward_dense,
  &dense_13_dense_chain,
  NULL, &dense_13_layer, AI_STATIC, 
)

AI_TENSOR_CHAIN_OBJ_DECLARE(
  dense_12_chain, AI_STATIC_CONST, 4,
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &dense_12_dense_output),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &dense_12_output),
  AI_TENSOR_LIST_OBJ_EMPTY,
  AI_TENSOR_LIST_OBJ_EMPTY
)

AI_LAYER_OBJ_DECLARE(
  dense_12_layer, 2,
  NL_TYPE, 0x0, NULL,
  nl, forward_relu,
  &dense_12_chain,
  NULL, &dense_13_dense_layer, AI_STATIC, 
  .nl_params = NULL, 
)

AI_TENSOR_CHAIN_OBJ_DECLARE(
  dense_12_dense_chain, AI_STATIC_CONST, 4,
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &conv2d_2_output0),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &dense_12_dense_output),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 2, &dense_12_dense_weights, &dense_12_dense_bias),
  AI_TENSOR_LIST_OBJ_EMPTY
)

AI_LAYER_OBJ_DECLARE(
  dense_12_dense_layer, 2,
  DENSE_TYPE, 0x0, NULL,
  dense, forward_dense,
  &dense_12_dense_chain,
  NULL, &dense_12_layer, AI_STATIC, 
)

AI_TENSOR_CHAIN_OBJ_DECLARE(
  conv2d_2_chain, AI_STATIC_CONST, 4,
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &conv2d_2_conv2d_output),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &conv2d_2_output),
  AI_TENSOR_LIST_OBJ_EMPTY,
  AI_TENSOR_LIST_OBJ_EMPTY
)

AI_LAYER_OBJ_DECLARE(
  conv2d_2_layer, 0,
  NL_TYPE, 0x0, NULL,
  nl, forward_relu,
  &conv2d_2_chain,
  NULL, &dense_12_dense_layer, AI_STATIC, 
  .nl_params = NULL, 
)

AI_TENSOR_CHAIN_OBJ_DECLARE(
  conv2d_2_conv2d_chain, AI_STATIC_CONST, 4,
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &input_0_output),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &conv2d_2_conv2d_output),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 3, &conv2d_2_conv2d_weights, &conv2d_2_conv2d_bias, NULL),
  AI_TENSOR_LIST_OBJ_EMPTY
)

AI_LAYER_OBJ_DECLARE(
  conv2d_2_conv2d_layer, 0,
  CONV2D_TYPE, 0x0, NULL,
  conv2d, forward_conv2d_if32of32wf32,
  &conv2d_2_conv2d_chain,
  NULL, &conv2d_2_layer, AI_STATIC, 
  .groups = 1, 
  .filter_stride = AI_SHAPE_2D_INIT(1, 1), 
  .dilation = AI_SHAPE_2D_INIT(1, 1), 
  .filter_pad = AI_SHAPE_INIT(4, 0, 0, 1, 1), 
  .in_ch_format = AI_LAYER_FORMAT_CHANNEL_LAST_VALID, 
  .out_ch_format = AI_LAYER_FORMAT_CHANNEL_LAST_VALID, 
)


#if (AI_TOOLS_API_VERSION < AI_TOOLS_API_VERSION_1_5)

AI_NETWORK_OBJ_DECLARE(
  AI_NET_OBJ_INSTANCE, AI_STATIC,
  AI_BUFFER_INIT(AI_FLAG_NONE,  AI_BUFFER_FORMAT_U8,
    AI_BUFFER_SHAPE_INIT(AI_SHAPE_BCWH, 4, 1, 227920, 1, 1),
    227920, NULL, NULL),
  AI_BUFFER_INIT(AI_FLAG_NONE,  AI_BUFFER_FORMAT_U8,
    AI_BUFFER_SHAPE_INIT(AI_SHAPE_BCWH, 4, 1, 2752, 1, 1),
    2752, NULL, NULL),
  AI_TENSOR_LIST_IO_OBJ_INIT(AI_FLAG_NONE, AI_THREELINE_IN_NUM, &input_0_output),
  AI_TENSOR_LIST_IO_OBJ_INIT(AI_FLAG_NONE, AI_THREELINE_OUT_NUM, &dense_17_dense_output),
  &conv2d_2_conv2d_layer, 0, NULL)

#else

AI_NETWORK_OBJ_DECLARE(
  AI_NET_OBJ_INSTANCE, AI_STATIC,
  AI_BUFFER_ARRAY_OBJ_INIT_STATIC(
  	AI_FLAG_NONE, 1,
    AI_BUFFER_INIT(AI_FLAG_NONE,  AI_BUFFER_FORMAT_U8,
      AI_BUFFER_SHAPE_INIT(AI_SHAPE_BCWH, 4, 1, 227920, 1, 1),
      227920, NULL, NULL)
  ),
  AI_BUFFER_ARRAY_OBJ_INIT_STATIC(
  	AI_FLAG_NONE, 1,
    AI_BUFFER_INIT(AI_FLAG_NONE,  AI_BUFFER_FORMAT_U8,
      AI_BUFFER_SHAPE_INIT(AI_SHAPE_BCWH, 4, 1, 2752, 1, 1),
      2752, NULL, NULL)
  ),
  AI_TENSOR_LIST_IO_OBJ_INIT(AI_FLAG_NONE, AI_THREELINE_IN_NUM, &input_0_output),
  AI_TENSOR_LIST_IO_OBJ_INIT(AI_FLAG_NONE, AI_THREELINE_OUT_NUM, &dense_17_dense_output),
  &conv2d_2_conv2d_layer, 0, NULL)

#endif	/*(AI_TOOLS_API_VERSION < AI_TOOLS_API_VERSION_1_5)*/


/******************************************************************************/
AI_DECLARE_STATIC
ai_bool threeline_configure_activations(
  ai_network* net_ctx, const ai_network_params* params)
{
  AI_ASSERT(net_ctx)

  if (ai_platform_get_activations_map(g_threeline_activations_map, 1, params)) {
    /* Updating activations (byte) offsets */
    
    input_0_output_array.data = AI_PTR(g_threeline_activations_map[0] + 100);
    input_0_output_array.data_start = AI_PTR(g_threeline_activations_map[0] + 100);
    
    conv2d_2_conv2d_output_array.data = AI_PTR(g_threeline_activations_map[0] + 256);
    conv2d_2_conv2d_output_array.data_start = AI_PTR(g_threeline_activations_map[0] + 256);
    
    conv2d_2_output_array.data = AI_PTR(g_threeline_activations_map[0] + 256);
    conv2d_2_output_array.data_start = AI_PTR(g_threeline_activations_map[0] + 256);
    
    dense_12_dense_output_array.data = AI_PTR(g_threeline_activations_map[0] + 0);
    dense_12_dense_output_array.data_start = AI_PTR(g_threeline_activations_map[0] + 0);
    
    dense_12_output_array.data = AI_PTR(g_threeline_activations_map[0] + 256);
    dense_12_output_array.data_start = AI_PTR(g_threeline_activations_map[0] + 256);
    
    dense_13_dense_output_array.data = AI_PTR(g_threeline_activations_map[0] + 0);
    dense_13_dense_output_array.data_start = AI_PTR(g_threeline_activations_map[0] + 0);
    
    dense_13_output_array.data = AI_PTR(g_threeline_activations_map[0] + 256);
    dense_13_output_array.data_start = AI_PTR(g_threeline_activations_map[0] + 256);
    
    dense_14_dense_output_array.data = AI_PTR(g_threeline_activations_map[0] + 0);
    dense_14_dense_output_array.data_start = AI_PTR(g_threeline_activations_map[0] + 0);
    
    dense_14_output_array.data = AI_PTR(g_threeline_activations_map[0] + 256);
    dense_14_output_array.data_start = AI_PTR(g_threeline_activations_map[0] + 256);
    
    dense_15_dense_output_array.data = AI_PTR(g_threeline_activations_map[0] + 0);
    dense_15_dense_output_array.data_start = AI_PTR(g_threeline_activations_map[0] + 0);
    
    dense_15_output_array.data = AI_PTR(g_threeline_activations_map[0] + 256);
    dense_15_output_array.data_start = AI_PTR(g_threeline_activations_map[0] + 256);
    
    dense_16_dense_output_array.data = AI_PTR(g_threeline_activations_map[0] + 0);
    dense_16_dense_output_array.data_start = AI_PTR(g_threeline_activations_map[0] + 0);
    
    dense_16_output_array.data = AI_PTR(g_threeline_activations_map[0] + 256);
    dense_16_output_array.data_start = AI_PTR(g_threeline_activations_map[0] + 256);
    
    dense_17_dense_output_array.data = AI_PTR(g_threeline_activations_map[0] + 0);
    dense_17_dense_output_array.data_start = AI_PTR(g_threeline_activations_map[0] + 0);
    
    return true;
  }
  AI_ERROR_TRAP(net_ctx, INIT_FAILED, NETWORK_ACTIVATIONS);
  return false;
}



/******************************************************************************/
AI_DECLARE_STATIC
ai_bool threeline_configure_weights(
  ai_network* net_ctx, const ai_network_params* params)
{
  AI_ASSERT(net_ctx)

  if (ai_platform_get_weights_map(g_threeline_weights_map, 1, params)) {
    /* Updating weights (byte) offsets */
    
    conv2d_2_conv2d_bias_array.format |= AI_FMT_FLAG_CONST;
    conv2d_2_conv2d_bias_array.data = AI_PTR(g_threeline_weights_map[0] + 0);
    conv2d_2_conv2d_bias_array.data_start = AI_PTR(g_threeline_weights_map[0] + 0);
    
    dense_12_dense_weights_array.format |= AI_FMT_FLAG_CONST;
    dense_12_dense_weights_array.data = AI_PTR(g_threeline_weights_map[0] + 64);
    dense_12_dense_weights_array.data_start = AI_PTR(g_threeline_weights_map[0] + 64);
    
    dense_12_dense_bias_array.format |= AI_FMT_FLAG_CONST;
    dense_12_dense_bias_array.data = AI_PTR(g_threeline_weights_map[0] + 159808);
    dense_12_dense_bias_array.data_start = AI_PTR(g_threeline_weights_map[0] + 159808);
    
    dense_13_dense_weights_array.format |= AI_FMT_FLAG_CONST;
    dense_13_dense_weights_array.data = AI_PTR(g_threeline_weights_map[0] + 160064);
    dense_13_dense_weights_array.data_start = AI_PTR(g_threeline_weights_map[0] + 160064);
    
    dense_13_dense_bias_array.format |= AI_FMT_FLAG_CONST;
    dense_13_dense_bias_array.data = AI_PTR(g_threeline_weights_map[0] + 176448);
    dense_13_dense_bias_array.data_start = AI_PTR(g_threeline_weights_map[0] + 176448);
    
    dense_14_dense_weights_array.format |= AI_FMT_FLAG_CONST;
    dense_14_dense_weights_array.data = AI_PTR(g_threeline_weights_map[0] + 176704);
    dense_14_dense_weights_array.data_start = AI_PTR(g_threeline_weights_map[0] + 176704);
    
    dense_14_dense_bias_array.format |= AI_FMT_FLAG_CONST;
    dense_14_dense_bias_array.data = AI_PTR(g_threeline_weights_map[0] + 193088);
    dense_14_dense_bias_array.data_start = AI_PTR(g_threeline_weights_map[0] + 193088);
    
    dense_15_dense_weights_array.format |= AI_FMT_FLAG_CONST;
    dense_15_dense_weights_array.data = AI_PTR(g_threeline_weights_map[0] + 193344);
    dense_15_dense_weights_array.data_start = AI_PTR(g_threeline_weights_map[0] + 193344);
    
    dense_15_dense_bias_array.format |= AI_FMT_FLAG_CONST;
    dense_15_dense_bias_array.data = AI_PTR(g_threeline_weights_map[0] + 209728);
    dense_15_dense_bias_array.data_start = AI_PTR(g_threeline_weights_map[0] + 209728);
    
    dense_16_dense_weights_array.format |= AI_FMT_FLAG_CONST;
    dense_16_dense_weights_array.data = AI_PTR(g_threeline_weights_map[0] + 209984);
    dense_16_dense_weights_array.data_start = AI_PTR(g_threeline_weights_map[0] + 209984);
    
    dense_16_dense_bias_array.format |= AI_FMT_FLAG_CONST;
    dense_16_dense_bias_array.data = AI_PTR(g_threeline_weights_map[0] + 226368);
    dense_16_dense_bias_array.data_start = AI_PTR(g_threeline_weights_map[0] + 226368);
    
    dense_17_dense_weights_array.format |= AI_FMT_FLAG_CONST;
    dense_17_dense_weights_array.data = AI_PTR(g_threeline_weights_map[0] + 226624);
    dense_17_dense_weights_array.data_start = AI_PTR(g_threeline_weights_map[0] + 226624);
    
    dense_17_dense_bias_array.format |= AI_FMT_FLAG_CONST;
    dense_17_dense_bias_array.data = AI_PTR(g_threeline_weights_map[0] + 227648);
    dense_17_dense_bias_array.data_start = AI_PTR(g_threeline_weights_map[0] + 227648);
    
    conv2d_2_conv2d_weights_array.format |= AI_FMT_FLAG_CONST;
    conv2d_2_conv2d_weights_array.data = AI_PTR(g_threeline_weights_map[0] + 227664);
    conv2d_2_conv2d_weights_array.data_start = AI_PTR(g_threeline_weights_map[0] + 227664);
    
    return true;
  }
  AI_ERROR_TRAP(net_ctx, INIT_FAILED, NETWORK_WEIGHTS);
  return false;
}


/**  PUBLIC APIs SECTION  *****************************************************/


AI_DEPRECATED
AI_API_ENTRY
ai_bool ai_threeline_get_info(
  ai_handle network, ai_network_report* report)
{
  ai_network* net_ctx = AI_NETWORK_ACQUIRE_CTX(network);

  if (report && net_ctx)
  {
    ai_network_report r = {
      .model_name        = AI_THREELINE_MODEL_NAME,
      .model_signature   = AI_THREELINE_MODEL_SIGNATURE,
      .model_datetime    = AI_TOOLS_DATE_TIME,
      
      .compile_datetime  = AI_TOOLS_COMPILE_TIME,
      
      .runtime_revision  = ai_platform_runtime_get_revision(),
      .runtime_version   = ai_platform_runtime_get_version(),

      .tool_revision     = AI_TOOLS_REVISION_ID,
      .tool_version      = {AI_TOOLS_VERSION_MAJOR, AI_TOOLS_VERSION_MINOR,
                            AI_TOOLS_VERSION_MICRO, 0x0},
      .tool_api_version  = AI_STRUCT_INIT,

      .api_version            = ai_platform_api_get_version(),
      .interface_api_version  = ai_platform_interface_api_get_version(),
      
      .n_macc            = 60356,
      .n_inputs          = 0,
      .inputs            = NULL,
      .n_outputs         = 0,
      .outputs           = NULL,
      .params            = AI_STRUCT_INIT,
      .activations       = AI_STRUCT_INIT,
      .n_nodes           = 0,
      .signature         = 0x0,
    };

    if (!ai_platform_api_get_network_report(network, &r)) return false;

    *report = r;
    return true;
  }
  return false;
}


AI_API_ENTRY
ai_bool ai_threeline_get_report(
  ai_handle network, ai_network_report* report)
{
  ai_network* net_ctx = AI_NETWORK_ACQUIRE_CTX(network);

  if (report && net_ctx)
  {
    ai_network_report r = {
      .model_name        = AI_THREELINE_MODEL_NAME,
      .model_signature   = AI_THREELINE_MODEL_SIGNATURE,
      .model_datetime    = AI_TOOLS_DATE_TIME,
      
      .compile_datetime  = AI_TOOLS_COMPILE_TIME,
      
      .runtime_revision  = ai_platform_runtime_get_revision(),
      .runtime_version   = ai_platform_runtime_get_version(),

      .tool_revision     = AI_TOOLS_REVISION_ID,
      .tool_version      = {AI_TOOLS_VERSION_MAJOR, AI_TOOLS_VERSION_MINOR,
                            AI_TOOLS_VERSION_MICRO, 0x0},
      .tool_api_version  = AI_STRUCT_INIT,

      .api_version            = ai_platform_api_get_version(),
      .interface_api_version  = ai_platform_interface_api_get_version(),
      
      .n_macc            = 60356,
      .n_inputs          = 0,
      .inputs            = NULL,
      .n_outputs         = 0,
      .outputs           = NULL,
      .map_signature     = AI_MAGIC_SIGNATURE,
      .map_weights       = AI_STRUCT_INIT,
      .map_activations   = AI_STRUCT_INIT,
      .n_nodes           = 0,
      .signature         = 0x0,
    };

    if (!ai_platform_api_get_network_report(network, &r)) return false;

    *report = r;
    return true;
  }
  return false;
}

AI_API_ENTRY
ai_error ai_threeline_get_error(ai_handle network)
{
  return ai_platform_network_get_error(network);
}

AI_API_ENTRY
ai_error ai_threeline_create(
  ai_handle* network, const ai_buffer* network_config)
{
  return ai_platform_network_create(
    network, network_config, 
    &AI_NET_OBJ_INSTANCE,
    AI_TOOLS_API_VERSION_MAJOR, AI_TOOLS_API_VERSION_MINOR, AI_TOOLS_API_VERSION_MICRO);
}

AI_API_ENTRY
ai_error ai_threeline_create_and_init(
  ai_handle* network, const ai_handle activations[], const ai_handle weights[])
{
    ai_error err;
    ai_network_params params;

    err = ai_threeline_create(network, AI_THREELINE_DATA_CONFIG);
    if (err.type != AI_ERROR_NONE)
        return err;
    if (ai_threeline_data_params_get(&params) != true) {
        err = ai_threeline_get_error(*network);
        return err;
    }
#if defined(AI_THREELINE_DATA_ACTIVATIONS_COUNT)
    if (activations) {
        /* set the addresses of the activations buffers */
        for (int idx=0;idx<params.map_activations.size;idx++)
            AI_BUFFER_ARRAY_ITEM_SET_ADDRESS(&params.map_activations, idx, activations[idx]);
    }
#endif
#if defined(AI_THREELINE_DATA_WEIGHTS_COUNT)
    if (weights) {
        /* set the addresses of the weight buffers */
        for (int idx=0;idx<params.map_weights.size;idx++)
            AI_BUFFER_ARRAY_ITEM_SET_ADDRESS(&params.map_weights, idx, weights[idx]);
    }
#endif
    if (ai_threeline_init(*network, &params) != true) {
        err = ai_threeline_get_error(*network);
    }
    return err;
}

AI_API_ENTRY
ai_buffer* ai_threeline_inputs_get(ai_handle network, ai_u16 *n_buffer)
{
  if (network == AI_HANDLE_NULL) {
    network = (ai_handle)&AI_NET_OBJ_INSTANCE;
    ((ai_network *)network)->magic = AI_MAGIC_CONTEXT_TOKEN;
  }
  return ai_platform_inputs_get(network, n_buffer);
}

AI_API_ENTRY
ai_buffer* ai_threeline_outputs_get(ai_handle network, ai_u16 *n_buffer)
{
  if (network == AI_HANDLE_NULL) {
    network = (ai_handle)&AI_NET_OBJ_INSTANCE;
    ((ai_network *)network)->magic = AI_MAGIC_CONTEXT_TOKEN;
  }
  return ai_platform_outputs_get(network, n_buffer);
}

AI_API_ENTRY
ai_handle ai_threeline_destroy(ai_handle network)
{
  return ai_platform_network_destroy(network);
}

AI_API_ENTRY
ai_bool ai_threeline_init(
  ai_handle network, const ai_network_params* params)
{
  ai_network* net_ctx = ai_platform_network_init(network, params);
  if (!net_ctx) return false;

  ai_bool ok = true;
  ok &= threeline_configure_weights(net_ctx, params);
  ok &= threeline_configure_activations(net_ctx, params);

  ok &= ai_platform_network_post_init(network);

  return ok;
}


AI_API_ENTRY
ai_i32 ai_threeline_run(
  ai_handle network, const ai_buffer* input, ai_buffer* output)
{
  return ai_platform_network_process(network, input, output);
}

AI_API_ENTRY
ai_i32 ai_threeline_forward(ai_handle network, const ai_buffer* input)
{
  return ai_platform_network_process(network, input, NULL);
}



#undef AI_THREELINE_MODEL_SIGNATURE
#undef AI_NET_OBJ_INSTANCE
#undef AI_TOOLS_DATE_TIME
#undef AI_TOOLS_COMPILE_TIME

