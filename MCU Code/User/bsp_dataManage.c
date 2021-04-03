/*
 * @Author: Chao
 * @Date: 2021-03-22 22:44:47
 * @LastEditTime: 2021-04-03 21:33:58
 * @Description:  
 */

#include "bsp_dataManage.h"

extern uint8_t pADC_MaxValue;
extern uint32_t ADC_ReceiveData[3]; //16���ƣ��Ĵ����ڵ�ֵ
extern uint32_t ADC_MaxValue[3];
extern float ADC_Vol[3]; //10���ƣ�ʵ�ʵ�ѹ�������Ķ�;  ADC_Vol =(float) ADC_ReceiveData/4096*(float)3.3

/**
 * @brief  ����̨������ֵ
 * @param  beCompared   ���ֵ
 * @param  toCompare    Ҫ�Ƚϵ���
 */
void compareAndGetMaxValue(uint32_t *beCompared, uint32_t *toCompare)
{
    if (*beCompared < *toCompare)
    {
        *beCompared = *toCompare;
    }
}

/**
 * @brief ˢ�µ�ѹ����ֵ
 */
void refreshADC_MaxValue()
{
    for (pADC_MaxValue = 0; pADC_MaxValue <= 2; pADC_MaxValue++)
    {
        ADC_Vol[pADC_MaxValue] = (float)ADC_MaxValue[pADC_MaxValue]  * (float)3.3 / 4096;
        ADC_MaxValue[pADC_MaxValue] = 0;
        printf("%f\n", ADC_Vol[pADC_MaxValue]);
    }
}

/**
 * @brief ��õ�ѹ���ֵ�����Ҳ���ֵ��
 */
void getADC_MaxValue()
{
    uint32_t samplingTimes = 0;
    while (samplingTimes++ <= 100000)
    {
        for (pADC_MaxValue = 0; pADC_MaxValue <= 2; pADC_MaxValue++)
        {
            compareAndGetMaxValue(&ADC_MaxValue[pADC_MaxValue], &ADC_ReceiveData[pADC_MaxValue]);
        }
    }
    refreshADC_MaxValue();
}

/**
 * @brief ����������
 * @return �������ֵ
 */
float getInputResistance()
{
    return (INPUT_VOLTAGE / INPUT_CURRENT);
}

/**
 * @brief ����������
 * @return �������ֵ
 */
float getOutputRsistance()
{
    float voltage0; //�޸��ص������ѹ
    float voltage1; //�и��ص������ѹ
    voltage0 = OUTPUT_VOLTAGE;
    HAL_GPIO_WritePin(GPIOB, GPIO_PIN_0, GPIO_PIN_SET);
    getADC_MaxValue();
    voltage1 = OUTPUT_VOLTAGE;
    HAL_GPIO_WritePin(GPIOB, GPIO_PIN_0, GPIO_PIN_RESET);
    return ((voltage0 / voltage1 - 1) * LOAD_RESISTANCE);
}
