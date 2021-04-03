/**
 * @file bsp_dataManage.h
 * @brief 
 * @author Chao
 * @version 1.0
 * @date 2021-04-01
 */

#ifndef __BSP_DATAMANAGE_H
#define __BSP_DATAMANAGE_H

#include "stdint.h"
#include <stdio.h>
#include "stm32f1xx_hal.h"
#include "tim.h"

#define SAMPLE_RESISTANCE   15  //��������ֵ
#define SAMPLE_VOLTAGE      ADC_Vol[0]     //��������ĵ�ѹ
#define SAMPLE_VOLTAGE_GAIN 400     //������ѹ�˷�����

#define INPUT_CURRENT       SAMPLE_VOLTAGE / SAMPLE_VOLTAGE_GAIN / SAMPLE_RESISTANCE    //�������
#define INPUT_VOLTAGE       ADC_Vol[1]     //�����ѹ

#define OUTPUT_VOLTAGE      ADC_Vol[2]     //�����ѹ

#define GAIN                OUTPUT_VOLTAGE / INPUT_VOLTAGE

#define LOAD_RESISTANCE     5000    //���ص���

void compareAndGetMaxValue(uint32_t *beCompared, uint32_t *toCompare);
void refreshADC_MaxValue(void);
void getADC_MaxValue(void);

#endif
