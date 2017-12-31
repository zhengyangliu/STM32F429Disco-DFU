/**
  ******************************************************************************
  * @file           : usbd_dfu_if.c
  * @brief          :
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

/* Includes ------------------------------------------------------------------*/
#include "usbd_dfu_if.h"
/* USER CODE BEGIN INCLUDE */
/* USER CODE END INCLUDE */

/** @addtogroup STM32_USB_OTG_DEVICE_LIBRARY
  * @{
  */
/** @defgroup USBD_DFU 
  * @brief usbd core module
  * @{
  */

/** @defgroup USBD_DFU_Private_TypesDefinitions
  * @{
  */
/* USER CODE BEGIN PRIVATE_TYPES */
/* USER CODE END PRIVATE_TYPES */
/**
  * @}
  */

/** @defgroup USBD_DFU_Private_Defines
  * @{
  */
#define FLASH_DESC_STR "@Internal Flash   /0x08000000/03*016Ka,01*016Kg,01*064Kg,07*128Kg,04*016Kg,01*064Kg,07*128Kg"
/* USER CODE BEGIN PRIVATE_DEFINES */
/* USER CODE END PRIVATE_DEFINES */

/**
  * @}
  */

/** @defgroup USBD_DFU_Private_Macros
  * @{
  */
/* USER CODE BEGIN PRIVATE_MACRO */
/* USER CODE END PRIVATE_MACRO */

/**
  * @}
  */

/** @defgroup USBD_AUDIO_IF_Private_Variables
  * @{
  */
/* USER CODE BEGIN PRIVATE_VARIABLES */
static const uint16_t TimingTable[24] =
    {
        FLASH_SECTOR_16KB_WRITE_ERASE_TIME, // SECTOR0
        FLASH_SECTOR_16KB_WRITE_ERASE_TIME,
        FLASH_SECTOR_16KB_WRITE_ERASE_TIME,
        FLASH_SECTOR_16KB_WRITE_ERASE_TIME,
        FLASH_SECTOR_64KB_WRITE_ERASE_TIME,
        FLASH_SECTOR_128KB_WRITE_ERASE_TIME,
        FLASH_SECTOR_128KB_WRITE_ERASE_TIME,
        FLASH_SECTOR_128KB_WRITE_ERASE_TIME,
        FLASH_SECTOR_128KB_WRITE_ERASE_TIME,
        FLASH_SECTOR_128KB_WRITE_ERASE_TIME,
        FLASH_SECTOR_128KB_WRITE_ERASE_TIME,
        FLASH_SECTOR_128KB_WRITE_ERASE_TIME, // SECTOR11

        FLASH_SECTOR_16KB_WRITE_ERASE_TIME, // SECTOR12
        FLASH_SECTOR_16KB_WRITE_ERASE_TIME,
        FLASH_SECTOR_16KB_WRITE_ERASE_TIME,
        FLASH_SECTOR_16KB_WRITE_ERASE_TIME,
        FLASH_SECTOR_64KB_WRITE_ERASE_TIME,
        FLASH_SECTOR_128KB_WRITE_ERASE_TIME,
        FLASH_SECTOR_128KB_WRITE_ERASE_TIME,
        FLASH_SECTOR_128KB_WRITE_ERASE_TIME,
        FLASH_SECTOR_128KB_WRITE_ERASE_TIME,
        FLASH_SECTOR_128KB_WRITE_ERASE_TIME,
        FLASH_SECTOR_128KB_WRITE_ERASE_TIME,
        FLASH_SECTOR_128KB_WRITE_ERASE_TIME, // SECTOR23
};
/* USER CODE END PRIVATE_VARIABLES */

/**
  * @}
  */

/** @defgroup USBD_DFU_IF_Exported_Variables
  * @{
  */
extern USBD_HandleTypeDef hUsbDeviceHS;
/* USER CODE BEGIN EXPORTED_VARIABLES */
/* USER CODE END EXPORTED_VARIABLES */

/**
  * @}
  */

/** @defgroup USBD_DFU_Private_FunctionPrototypes
  * @{
  */

static uint16_t MEM_If_Init_HS(void);
static uint16_t MEM_If_Erase_HS(uint32_t Add);
static uint16_t MEM_If_Write_HS(uint8_t *src, uint8_t *dest, uint32_t Len);
static uint8_t *MEM_If_Read_HS(uint8_t *src, uint8_t *dest, uint32_t Len);
static uint16_t MEM_If_DeInit_HS(void);
static uint16_t MEM_If_GetStatus_HS(uint32_t Add, uint8_t Cmd, uint8_t *buffer);
/* USER CODE BEGIN PRIVATE_FUNCTIONS_DECLARATION */
/* USER CODE END PRIVATE_FUNCTIONS_DECLARATION */

/**
  * @}
  */

#if defined(__ICCARM__) /*!< IAR Compiler */
#pragma data_alignment = 4
#endif

__ALIGN_BEGIN USBD_DFU_MediaTypeDef USBD_DFU_fops_HS __ALIGN_END =
    {
        (uint8_t *)FLASH_DESC_STR,
        MEM_If_Init_HS,
        MEM_If_DeInit_HS,
        MEM_If_Erase_HS,
        MEM_If_Write_HS,
        MEM_If_Read_HS,
        MEM_If_GetStatus_HS,
};

/* Private functions ---------------------------------------------------------*/

/**
  * @brief  MEM_If_Init_HS
  *         Memory initialization routine.
  * @param  None
  * @retval 0 if operation is successful, MAL_FAIL else.
  */
uint16_t MEM_If_Init_HS(void)
{
  /* USER CODE BEGIN 6 */
  HAL_FLASH_Unlock();
  return (USBD_OK);
  /* USER CODE END 6 */
}

/**
  * @brief  MEM_If_DeInit_HS
   *         De-Initializes Memory.
  * @param  None
  * @retval 0 if operation is successful, MAL_FAIL else.
  */
uint16_t MEM_If_DeInit_HS(void)
{
  /* USER CODE BEGIN 7 */
  HAL_FLASH_Lock();
  return (USBD_OK);
  /* USER CODE END 7 */
}

/**
  * @brief  GetSector
   *         Calc the address belone to witch sector.
  * @param  the address
  * @retval sector number.
  */
static uint32_t GetSector(uint32_t Address)
{
  uint32_t sector = 0;

  if ((Address < ADDR_FLASH_SECTOR_1) && (Address >= ADDR_FLASH_SECTOR_0))
  {
    sector = FLASH_SECTOR_0;
  }
  else if ((Address < ADDR_FLASH_SECTOR_2) && (Address >= ADDR_FLASH_SECTOR_1))
  {
    sector = FLASH_SECTOR_1;
  }
  else if ((Address < ADDR_FLASH_SECTOR_3) && (Address >= ADDR_FLASH_SECTOR_2))
  {
    sector = FLASH_SECTOR_2;
  }
  else if ((Address < ADDR_FLASH_SECTOR_4) && (Address >= ADDR_FLASH_SECTOR_3))
  {
    sector = FLASH_SECTOR_3;
  }
  else if ((Address < ADDR_FLASH_SECTOR_5) && (Address >= ADDR_FLASH_SECTOR_4))
  {
    sector = FLASH_SECTOR_4;
  }
  else if ((Address < ADDR_FLASH_SECTOR_6) && (Address >= ADDR_FLASH_SECTOR_5))
  {
    sector = FLASH_SECTOR_5;
  }
  else if ((Address < ADDR_FLASH_SECTOR_7) && (Address >= ADDR_FLASH_SECTOR_6))
  {
    sector = FLASH_SECTOR_6;
  }
  else if ((Address < ADDR_FLASH_SECTOR_8) && (Address >= ADDR_FLASH_SECTOR_7))
  {
    sector = FLASH_SECTOR_7;
  }
  else if ((Address < ADDR_FLASH_SECTOR_9) && (Address >= ADDR_FLASH_SECTOR_8))
  {
    sector = FLASH_SECTOR_8;
  }
  else if ((Address < ADDR_FLASH_SECTOR_10) && (Address >= ADDR_FLASH_SECTOR_9))
  {
    sector = FLASH_SECTOR_9;
  }
  else if ((Address < ADDR_FLASH_SECTOR_11) && (Address >= ADDR_FLASH_SECTOR_10))
  {
    sector = FLASH_SECTOR_10;
  }
  else if ((Address < ADDR_FLASH_SECTOR_12) && (Address >= ADDR_FLASH_SECTOR_11))
  {
    sector = FLASH_SECTOR_11;
  }
  else if ((Address < ADDR_FLASH_SECTOR_13) && (Address >= ADDR_FLASH_SECTOR_12))
  {
    sector = FLASH_SECTOR_12;
  }
  else if ((Address < ADDR_FLASH_SECTOR_14) && (Address >= ADDR_FLASH_SECTOR_13))
  {
    sector = FLASH_SECTOR_13;
  }
  else if ((Address < ADDR_FLASH_SECTOR_15) && (Address >= ADDR_FLASH_SECTOR_14))
  {
    sector = FLASH_SECTOR_14;
  }
  else if ((Address < ADDR_FLASH_SECTOR_16) && (Address >= ADDR_FLASH_SECTOR_15))
  {
    sector = FLASH_SECTOR_15;
  }
  else if ((Address < ADDR_FLASH_SECTOR_17) && (Address >= ADDR_FLASH_SECTOR_16))
  {
    sector = FLASH_SECTOR_16;
  }
  else if ((Address < ADDR_FLASH_SECTOR_18) && (Address >= ADDR_FLASH_SECTOR_17))
  {
    sector = FLASH_SECTOR_17;
  }
  else if ((Address < ADDR_FLASH_SECTOR_19) && (Address >= ADDR_FLASH_SECTOR_18))
  {
    sector = FLASH_SECTOR_18;
  }
  else if ((Address < ADDR_FLASH_SECTOR_20) && (Address >= ADDR_FLASH_SECTOR_19))
  {
    sector = FLASH_SECTOR_19;
  }
  else if ((Address < ADDR_FLASH_SECTOR_21) && (Address >= ADDR_FLASH_SECTOR_20))
  {
    sector = FLASH_SECTOR_20;
  }
  else if ((Address < ADDR_FLASH_SECTOR_22) && (Address >= ADDR_FLASH_SECTOR_21))
  {
    sector = FLASH_SECTOR_21;
  }
  else if ((Address < ADDR_FLASH_SECTOR_23) && (Address >= ADDR_FLASH_SECTOR_22))
  {
    sector = FLASH_SECTOR_22;
  }
  else
  {
    sector = FLASH_SECTOR_23;
  }
  return sector;
}

/**
  * @brief  MEM_If_Erase_HS
  *         Erase sector.
  * @param  Add: Address of sector to be erased.
  * @retval 0 if operation is successful, MAL_FAIL else.
  */
uint16_t MEM_If_Erase_HS(uint32_t Add)
{
  /* USER CODE BEGIN 8 */
  uint32_t startsector = 0;
  uint32_t sectornb = 0;
  /* Variable contains Flash operation status */
  HAL_StatusTypeDef status;
  FLASH_EraseInitTypeDef eraseinitstruct;

  /* Get the number of sector */
  startsector = GetSector(Add);

  eraseinitstruct.TypeErase = FLASH_TYPEERASE_SECTORS;
  eraseinitstruct.VoltageRange = FLASH_VOLTAGE_RANGE_3;
  eraseinitstruct.Sector = startsector;
  eraseinitstruct.NbSectors = 1;
  status = HAL_FLASHEx_Erase(&eraseinitstruct, &sectornb);

  if (status != HAL_OK)
  {
    return (USBD_FAIL);
  }
  return (USBD_OK);
  /* USER CODE END 8 */
}

/**
  * @brief  MEM_If_Write_HS
  *         Memory write routine.
  * @param  src: Pointer to the source buffer. Address to be written to.
  * @param  dest: Pointer to the destination buffer.
  * @param  Len: Number of data to be written (in bytes).
  * @retval 0 if operation is successful, MAL_FAIL else.
  */
uint16_t MEM_If_Write_HS(uint8_t *src, uint8_t *dest, uint32_t Len)
{
  /* USER CODE BEGIN 9 */
  uint32_t i = 0;

  for (i = 0; i < Len; i += 4)
  {
    /* Device voltage range supposed to be [2.7V to 3.6V], the operation will
       be done by byte */
    if (HAL_FLASH_Program(FLASH_TYPEPROGRAM_WORD, (uint32_t)(dest + i), *(uint32_t *)(src + i)) == HAL_OK)
    {
      /* Check the written value */
      if (*(uint32_t *)(src + i) != *(uint32_t *)(dest + i))
      {
        /* Flash content doesn't match SRAM content */
        return (USBD_FAIL);
      }
    }
    else
    {
      /* Error occurred while writing data in Flash memory */
      return (USBD_FAIL);
    }
  }
  return (USBD_OK);
  /* USER CODE END 9 */
}

/**
  * @brief  MEM_If_Read_HS
  *         Memory read routine.
  * @param  src: Pointer to the source buffer. Address to be written to.
  * @param  dest: Pointer to the destination buffer.
  * @param  Len: Number of data to be read (in bytes).
  * @retval Pointer to the physical address where data should be read.
  */
uint8_t *MEM_If_Read_HS(uint8_t *src, uint8_t *dest, uint32_t Len)
{
  /* Return a valid address to avoid HardFault */
  /* USER CODE BEGIN 10 */
  uint32_t i = 0;
  uint8_t *psrc = src;

  for (i = 0; i < Len; i++)
  {
    dest[i] = *psrc++;
  }
  /* Return a valid address to avoid HardFault */
  return (uint8_t *)(dest);
  /* USER CODE END 10 */
}

/**
  * @brief  Flash_If_GetStatus_HS
  *         Get status routine.
  * @param  Add: Address to be read from.
  * @param  Cmd: Number of data to be read (in bytes).
  * @param  buffer: used for returning the time necessary for a program or an erase operation
  * @retval 0 if operation is successful
  */
uint16_t MEM_If_GetStatus_HS(uint32_t Add, uint8_t Cmd, uint8_t *buffer)
{
  /* USER CODE BEGIN 11 */
  uint16_t time;

  time = TimingTable[GetSector(Add)];

  switch (Cmd)
  {
  case DFU_MEDIA_PROGRAM:
    buffer[1] = (uint8_t)time;
    buffer[2] = (uint8_t)(time << 8);
    buffer[3] = 0;
    break;

  case DFU_MEDIA_ERASE:
  default:
    buffer[1] = (uint8_t)time;
    buffer[2] = (uint8_t)(time << 8);
    buffer[3] = 0;
    break;
  }
  return (USBD_OK);
  /* USER CODE END 11 */
}

/* USER CODE BEGIN PRIVATE_FUNCTIONS_IMPLEMENTATION */
/* USER CODE END PRIVATE_FUNCTIONS_IMPLEMENTATION */

/**
  * @}
  */

/**
  * @}
  */
/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
