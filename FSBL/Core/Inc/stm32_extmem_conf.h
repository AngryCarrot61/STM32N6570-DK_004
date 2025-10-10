/**
 ******************************************************************************
 * @file    Template_FSBL_XIP/FSBL/Inc/stm32_extmem_conf.h
 * @author  GPM Application Team
 * @brief   Header configuration for extmem module
 ******************************************************************************
 * @attention
 *
 * Copyright (c) 2023 STMicroelectronics.
 * All rights reserved.
 *
 * This software is licensed under terms that can be found in the LICENSE file
 * in the root directory of this software component.
 * If no LICENSE file comes with this software, it is provided AS-IS.
 *
 ******************************************************************************
 */

#ifndef EXTMEM_CONF_H_
#define EXTMEM_CONF_H_

#ifdef __cplusplus
extern "C" {
#endif

#define EXTMEM_DRIVER_NOR_SFDP   1
#define EXTMEM_DRIVER_PSRAM      0
#define EXTMEM_DRIVER_SDCARD     0
#define EXTMEM_DRIVER_USER       0

#if (EXTMEM_DRIVER_PSRAM == 0)
#define EXTMEM_DRIVER_COUNT      1
#else
#define EXTMEM_DRIVER_COUNT      2
#endif

/* Management of the driver layer enable */
#define EXTMEM_SAL_XSPI          1
#define EXTMEM_SAL_SD            0

/* Aps256xx APMemory memory */

/* Read Operations */
#define READ_CMD                                0x00
#define READ_LINEAR_BURST_CMD                   0x20
#define READ_HYBRID_BURST_CMD                   0x3F

/* Write Operations */
#define WRITE_CMD                               0x80
#define WRITE_LINEAR_BURST_CMD                  0xA0
#define WRITE_HYBRID_BURST_CMD                  0xBF

/* Reset Operations */
#define RESET_CMD                               0xFF

/* Registers definition */
#define MR0                                     0x00000000
#define MR1                                     0x00000001
#define MR2                                     0x00000002
#define MR3                                     0x00000003
#define MR4                                     0x00000004
#define MR8                                     0x00000008

/* Register Operations */
#define READ_REG_CMD                            0x40
#define WRITE_REG_CMD                           0xC0

/* Default dummy clocks cycles, 7(6+1) to support up to 200MHz CLK */
#define DUMMY_CLOCK_CYCLES_READ                 6
#define DUMMY_CLOCK_CYCLES_WRITE                6

/* Size of buffers */
#define BUFFERSIZE                              10240
#define KByte                                   1024

/* Includes ------------------------------------------------------------------*/
#include "stm32n6xx_hal.h"
#include "stm32_extmem.h"
#include "stm32_extmem_type.h"
#include "boot/stm32_boot_xip.h"

/* Import of the HAL handles for MEMORRY_SERIAL_0 */
extern XSPI_HandleTypeDef       hxspi2;

/* Import of the HAL handles for MEMORY_PSRAM_0 */
extern XSPI_HandleTypeDef       hxspi1;

/* Exported types ------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/

/* EXTMEM_CONF_Exported_constants EXTMEM_CONF exported constants */
enum {
  EXTMEMORY_1  = 0, /*!< ID 0 of extmem_list_config */
  EXTMEMORY_2  = 1, /*!< ID 1 of extmem_list_config */
};

#define EXTMEM_MEMORY_BOOTXIP   EXTMEMORY_1
#define EXTMEM_XIP_IMAGE_OFFSET 0x00100000
#define EXTMEM_HEADER_OFFSET    0x00000400

/* Exported configuration --------------------------------------------------------*/

/* EXTMEM_CONF_Exported_configuration EXTMEM_CONF exported configuration definition */
extern EXTMEM_DefinitionTypeDef extmem_list_config[EXTMEM_DRIVER_COUNT];
#if defined(EXTMEM_C)
EXTMEM_DefinitionTypeDef extmem_list_config[EXTMEM_DRIVER_COUNT] =
{
  /* MEMORY_SERIAL_0 */
  {
    .MemType = EXTMEM_NOR_SFDP,
    .Handle = (void*)&hxspi2,
    .ConfigType = EXTMEM_LINK_CONFIG_8LINES,
    .NorSfdpObject =    
    {
      {0}
    }
  },
#if (EXTMEM_DRIVER_PSRAM == 1)
  /* MEMORY_PSRAM_0 */
  {
    .MemType = EXTMEM_PSRAM,
    .Handle = (void*)&hxspi1,
    .ConfigType = EXTMEM_LINK_CONFIG_16LINES,
    .PsramObject =
    {
      .psram_public = {
        .MemorySize = HAL_XSPI_SIZE_256MB,  /* memory size is 256Mbit */
        .FreqMax = 200000000u, /* 200Mhz */
        .NumberOfConfig = 1,
        /* Config */
        {
          {.WriteMask = 0x40, .WriteValue = 0x40, .REGAddress = 8}
        },
        
        /* Memory command configuration */
        .ReadREG           = 0x40u,
        .WriteREG          = 0xC0u,
        .ReadREGSize       = 2u,
        .REG_DummyCycle    = 4u,
        
        .Write_command     = 0xA0u,
        .Write_DummyCycle  = 4u,
        .Read_command      = 0x20u,
        .Read_DummyCycle   = 4u,
      }
    }
  }
#endif
};
#endif /* EXTMEM_C */

/* Exported trace --------------------------------------------------------*/

/* EXTMEM_CONF_Exported_debug EXTMEM_CONF exported debug definition */

/* Debug level of the different layers */
#define EXTMEM_DEBUG_LEVEL                   0
#define EXTMEM_DRIVER_NOR_SFDP_DEBUG_LEVEL   0
#define EXTMEM_DRIVER_PSRAM_DEBUG_LEVEL      0
#define EXTMEM_SAL_XSPI_DEBUG_LEVEL          0

/**
* @brief  Write mode register
* @param  Ctx Component object pointer
* @param  Address Register address
* @param  Value Register value pointer
* @retval error status
*/
uint32_t APS256_WriteReg(XSPI_HandleTypeDef *Ctx, uint32_t Address, uint8_t *Value);

/**
* @brief  Read mode register value
* @param  Ctx Component object pointer
* @param  Address Register address
* @param  Value Register value pointer
* @param  LatencyCode Latency used for the access
* @retval error status
*/
uint32_t APS256_ReadReg(XSPI_HandleTypeDef *Ctx, uint32_t Address, uint8_t *Value, uint32_t LatencyCode);

/**
* @brief  Switch from Octal Mode to Hexa Mode on the memory
* @param  None
* @retval None
*/
void Configure_APMemory(void);

/**
* @brief  Switch from Octal Mode to Hexa Mode on the memory
* @param  None
* @retval None
*/
void Configure_APMemory_Mapped_Mode(void);

#ifdef __cplusplus
}
#endif

#endif /* EXTMEM_CONF_H_ */
