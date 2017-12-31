/**
  ******************************************************************************
  * @file           : usbd_dfu_if.h
  * @brief          : Header for usbd_dfu_if file.
  ******************************************************************************
  * This notice applies to any and all portions of this file
  * that are not between comment pairs USER CODE BEGIN and
  * USER CODE END. Other portions of this file, whether 
  * inserted by the user or by software development tools
  * are owned by their respective copyright owners.
  *
  * Copyright (c) 2017 STMicroelectronics International N.V. 
  * All rights reserved.
  *
  * Redistribution and use in source and binary forms, with or without 
  * modification, are permitted, provided that the following conditions are met:
  *
  * 1. Redistribution of source code must retain the above copyright notice, 
  *    this list of conditions and the following disclaimer.
  * 2. Redistributions in binary form must reproduce the above copyright notice,
  *    this list of conditions and the following disclaimer in the documentation
  *    and/or other materials provided with the distribution.
  * 3. Neither the name of STMicroelectronics nor the names of other 
  *    contributors to this software may be used to endorse or promote products 
  *    derived from this software without specific written permission.
  * 4. This software, including modifications and/or derivative works of this 
  *    software, must execute solely and exclusively on microcontroller or
  *    microprocessor devices manufactured by or for STMicroelectronics.
  * 5. Redistribution and use of this software other than as permitted under 
  *    this license is void and will automatically terminate your rights under 
  *    this license. 
  *
  * THIS SOFTWARE IS PROVIDED BY STMICROELECTRONICS AND CONTRIBUTORS "AS IS" 
  * AND ANY EXPRESS, IMPLIED OR STATUTORY WARRANTIES, INCLUDING, BUT NOT 
  * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY, FITNESS FOR A 
  * PARTICULAR PURPOSE AND NON-INFRINGEMENT OF THIRD PARTY INTELLECTUAL PROPERTY
  * RIGHTS ARE DISCLAIMED TO THE FULLEST EXTENT PERMITTED BY LAW. IN NO EVENT 
  * SHALL STMICROELECTRONICS OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
  * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
  * LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, 
  * OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF 
  * LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING 
  * NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
  * EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
  *
  ******************************************************************************
*/

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __USBD_DFU_IF_H
#define __USBD_DFU_IF_H

#ifdef __cplusplus
extern "C" {
#endif
/* Includes ------------------------------------------------------------------*/
#include "usbd_dfu.h"
/* USER CODE BEGIN INCLUDE */
/* USER CODE END INCLUDE */

/** @addtogroup STM32_USB_DEVICE_LIBRARY
  * @{
  */

/** @defgroup USBD_MEDIA
  * @brief header file for the usbd_dfu_if.c file
  * @{
  */

/** @defgroup USBD_MEDIA_Exported_Defines
  * @{
  */
/* USER CODE BEGIN EXPORTED_DEFINES */
/* Define flash address */
// BLANK 1
#define ADDR_FLASH_SECTOR_0 0x08000000
#define ADDR_FLASH_SECTOR_1 0x08004000
#define ADDR_FLASH_SECTOR_2 0x08008000
#define ADDR_FLASH_SECTOR_3 0x0800C000
#define ADDR_FLASH_SECTOR_4 0x08010000
#define ADDR_FLASH_SECTOR_5 0x08020000
#define ADDR_FLASH_SECTOR_6 0x08040000
#define ADDR_FLASH_SECTOR_7 0x08060000
#define ADDR_FLASH_SECTOR_8 0x08080000
#define ADDR_FLASH_SECTOR_9 0x080A0000
#define ADDR_FLASH_SECTOR_10 0x080C0000
#define ADDR_FLASH_SECTOR_11 0x080E0000
// BLANK 2
#define ADDR_FLASH_SECTOR_12 0x08100000
#define ADDR_FLASH_SECTOR_13 0x08104000
#define ADDR_FLASH_SECTOR_14 0x08108000
#define ADDR_FLASH_SECTOR_15 0x0810C000
#define ADDR_FLASH_SECTOR_16 0x08110000
#define ADDR_FLASH_SECTOR_17 0x08120000
#define ADDR_FLASH_SECTOR_18 0x08140000
#define ADDR_FLASH_SECTOR_19 0x08160000
#define ADDR_FLASH_SECTOR_20 0x08180000
#define ADDR_FLASH_SECTOR_21 0x081A0000
#define ADDR_FLASH_SECTOR_22 0x081C0000
#define ADDR_FLASH_SECTOR_23 0x081E0000

/* Flash oprate time from datasheet page 128 */
#define FLASH_SECTOR_16KB_WRITE_ERASE_TIME 500 //500 usb frame,means 500ms
#define FLASH_SECTOR_64KB_WRITE_ERASE_TIME 1100
#define FLASH_SECTOR_128KB_WRITE_ERASE_TIME 2000
/* USER CODE END EXPORTED_DEFINES */

/**
  * @}
  */

/** @defgroup USBD_MEDIA_Exported_Types
  * @{
  */
/* USER CODE BEGIN EXPORTED_TYPES */
/* USER CODE END EXPORTED_TYPES */

/**
  * @}
  */

/** @defgroup USBD_MEDIA_Exported_Macros
  * @{
  */
/* USER CODE BEGIN EXPORTED_MACRO */
/* USER CODE END EXPORTED_MACRO */

/**
  * @}
  */

/** @defgroup USBD_MEDIA_Exported_Variables
  * @{
  */

extern USBD_DFU_MediaTypeDef USBD_DFU_fops_HS;

/* USER CODE BEGIN EXPORTED_VARIABLES */
/* USER CODE END EXPORTED_VARIABLES */

/**
  * @}
  */

/** @defgroup USBD_MEDIA_Exported_FunctionsPrototype
  * @{
  */

/* USER CODE BEGIN EXPORTED_FUNCTIONS */
/* USER CODE END EXPORTED_FUNCTIONS */
/**
  * @}
  */

/**
  * @}
  */

/**
* @}
*/
#ifdef __cplusplus
}
#endif

#endif /* __USBD_DFU_IF_H */
/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
