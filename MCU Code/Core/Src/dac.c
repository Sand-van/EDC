/**
  ******************************************************************************
  * @file    dac.c
  * @brief   This file provides code for the configuration
  *          of the DAC instances.
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2021 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under BSD 3-Clause license,
  * the "License"; You may not use this file except in compliance with the
  * License. You may obtain a copy of the License at:
  *                        opensource.org/licenses/BSD-3-Clause
  *
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "dac.h"

/* USER CODE BEGIN 0 */

uint16_t Sine12bit[POINT_NUM] = {
    124, 141, 157, 173, 187, 201, 213, 224, 233, 240, 245, 248, 248, 247,
    243, 237, 229, 219, 207, 194, 180, 165, 149, 132, 116, 99, 83, 68, 54,
    41, 29, 20, 12, 6, 2, 0, 1, 3, 8, 15, 24, 35, 47, 61, 76, 91, 108, 124};

/* USER CODE END 0 */

DAC_HandleTypeDef hdac;
DMA_HandleTypeDef hdma_dac_ch1;

/* DAC init function */
void MX_DAC_Init(void)
{

    /* USER CODE BEGIN DAC_Init 0 */

    /* USER CODE END DAC_Init 0 */

    DAC_ChannelConfTypeDef sConfig = {0};

    /* USER CODE BEGIN DAC_Init 1 */

    /* USER CODE END DAC_Init 1 */
    /** DAC Initialization
  */
    hdac.Instance = DAC;
    if (HAL_DAC_Init(&hdac) != HAL_OK)
    {
        Error_Handler();
    }
    /** DAC channel OUT1 config
  */
    sConfig.DAC_Trigger = DAC_TRIGGER_T6_TRGO;
    sConfig.DAC_OutputBuffer = DAC_OUTPUTBUFFER_ENABLE;
    if (HAL_DAC_ConfigChannel(&hdac, &sConfig, DAC_CHANNEL_1) != HAL_OK)
    {
        Error_Handler();
    }
    /* USER CODE BEGIN DAC_Init 2 */

    /* USER CODE END DAC_Init 2 */
}

void HAL_DAC_MspInit(DAC_HandleTypeDef *dacHandle)
{

    GPIO_InitTypeDef GPIO_InitStruct = {0};
    if (dacHandle->Instance == DAC)
    {
        /* USER CODE BEGIN DAC_MspInit 0 */

        /* USER CODE END DAC_MspInit 0 */
        /* DAC clock enable */
        __HAL_RCC_DAC_CLK_ENABLE();

        __HAL_RCC_GPIOA_CLK_ENABLE();
        /**DAC GPIO Configuration
    PA4     ------> DAC_OUT1
    */
        GPIO_InitStruct.Pin = GPIO_PIN_4;
        GPIO_InitStruct.Mode = GPIO_MODE_ANALOG;
        HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

        /* DAC DMA Init */
        /* DAC_CH1 Init */
        hdma_dac_ch1.Instance = DMA2_Channel3;
        hdma_dac_ch1.Init.Direction = DMA_MEMORY_TO_PERIPH;
        hdma_dac_ch1.Init.PeriphInc = DMA_PINC_DISABLE;
        hdma_dac_ch1.Init.MemInc = DMA_MINC_ENABLE;
        hdma_dac_ch1.Init.PeriphDataAlignment = DMA_PDATAALIGN_HALFWORD;
        hdma_dac_ch1.Init.MemDataAlignment = DMA_MDATAALIGN_HALFWORD;
        hdma_dac_ch1.Init.Mode = DMA_CIRCULAR;
        hdma_dac_ch1.Init.Priority = DMA_PRIORITY_HIGH;
        if (HAL_DMA_Init(&hdma_dac_ch1) != HAL_OK)
        {
            Error_Handler();
        }

        __HAL_LINKDMA(dacHandle, DMA_Handle1, hdma_dac_ch1);

        /* USER CODE BEGIN DAC_MspInit 1 */

        /* USER CODE END DAC_MspInit 1 */
    }
}

void HAL_DAC_MspDeInit(DAC_HandleTypeDef *dacHandle)
{

    if (dacHandle->Instance == DAC)
    {
        /* USER CODE BEGIN DAC_MspDeInit 0 */

        /* USER CODE END DAC_MspDeInit 0 */
        /* Peripheral clock disable */
        __HAL_RCC_DAC_CLK_DISABLE();

        /**DAC GPIO Configuration
    PA4     ------> DAC_OUT1
    */
        HAL_GPIO_DeInit(GPIOA, GPIO_PIN_4);

        /* DAC DMA DeInit */
        HAL_DMA_DeInit(dacHandle->DMA_Handle1);
        /* USER CODE BEGIN DAC_MspDeInit 1 */

        /* USER CODE END DAC_MspDeInit 1 */
    }
}

/* USER CODE BEGIN 1 */

/* USER CODE END 1 */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
