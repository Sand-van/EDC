/*
 * @Author: Chao
 * @Date: 2021-03-22 22:44:47
 * @LastEditTime: 2021-03-22 22:49:27
 * @Description:  
 */

#include "bsp_dataManage.h"

extern uint8_t pADC_MaxValue;
extern uint32_t ADC_ReceiveData[2]; //16进制，寄存器内的值
extern uint32_t ADC_MaxValue[2];
extern float ADC_Vol[2]; //10进制，实际电压，便于阅读;  ADC_Vol =(float) ADC_ReceiveData/4096*(float)3.3

/**
 * @brief  打擂台获得最大值
 * @param  beCompared   最大值
 * @param  toCompare    要比较的数
 */
void compareAndGetMaxValue(uint32_t *beCompared, uint32_t *toCompare)
{
    if (*beCompared < *toCompare)
    {
        *beCompared = *toCompare;
    }
}

/**
 * @brief 刷新电压采样值
 */
void refreshADC_MaxValue()
{
    for (pADC_MaxValue = 0; pADC_MaxValue <= 2; pADC_MaxValue++)
    {
        ADC_Vol[pADC_MaxValue] = (float)ADC_MaxValue[pADC_MaxValue] / 4096 * (float)3.3;
        ADC_MaxValue[pADC_MaxValue] = 0;
    }
}

/**
 * @brief 获得电压最大值（正弦波峰值）
 */
void getADC_MaxValue()
{
    uint32_t samplingTimes = 0;
    while (samplingTimes++ <= 100000)
    {
        for (pADC_MaxValue = 0; pADC_MaxValue <= 2; pADC_MaxValue++)
        {
            compareAndGetMaxValue(ADC_MaxValue, ADC_ReceiveData);
        }
    }
    refreshADC_MaxValue();
}

/**
 * @brief 获得输入电阻
 * @return 输入电阻值
 */
float getInputResistance()
{
    return (INPUT_VOLTAGE / INPUT_CURRENT);
}

/**
 * @brief 获得输出电阻
 * @return 输出电阻值
 */
float getOutputRsistance()
{
    float voltage0; //无负载的输出电压
    float voltage1; //有负载的输出电压
    voltage0 = OUTPUT_VOLTAGE;
    HAL_GPIO_WritePin(GPIOB, GPIO_PIN_0, GPIO_PIN_SET);
    getADC_MaxValue();
    voltage1 = OUTPUT_VOLTAGE;
    HAL_GPIO_WritePin(GPIOB, GPIO_PIN_0, GPIO_PIN_RESET);
    return ((voltage0 / voltage1 - 1) * LOAD_RESISTANCE);
}