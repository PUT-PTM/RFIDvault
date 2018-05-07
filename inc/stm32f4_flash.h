#ifndef __STM32F4_FLASH_H
#define __STM32F4_FLASH_H

#include "stm32f4xx.h"
#include "stm32f4xx_flash.h"

/* EEPROM MAX SIZE ADDRESS */
#define  FLASH_MAX_ADDRESS   10

/* Two sectors may be used in flash */
#define FLASH_SECTOR_SIZE    			((uint32_t)0x4000)     // 16kByte
#define FLASH_SECTOR02_ADDR_START     	((uint32_t)0x08008000) /* Base @ of Sector 2, 16 Kbytes */
#define FLASH_SECTOR03_ADDR_START     	((uint32_t)0x0800C000) /* Base @ of Sector 3, 16 Kbytes */

/* Rest sectors */
#define FLASH_SECTOR00_ADDR_START    	((uint32_t)0x08000000) /* Base @ of Sector 0, 16 Kbytes */
#define FLASH_SECTOR01_ADDR_START     	((uint32_t)0x08004000) /* Base @ of Sector 1, 16 Kbytes */
#define FLASH_SECTOR04_ADDR_START     	((uint32_t)0x08010000) /* Base @ of Sector 4, 64 Kbytes */
#define FLASH_SECTOR05_ADDR_START     	((uint32_t)0x08020000) /* Base @ of Sector 5, 128 Kbytes */
#define FLASH_SECTOR06_ADDR_START     	((uint32_t)0x08040000) /* Base @ of Sector 6, 128 Kbytes */
#define FLASH_SECTOR07_ADDR_START     	((uint32_t)0x08060000) /* Base @ of Sector 7, 128 Kbytes */
#define FLASH_SECTOR08_ADDR_START     	((uint32_t)0x08080000) /* Base @ of Sector 8, 128 Kbytes */
#define FLASH_SECTOR09_ADDR_START     	((uint32_t)0x080A0000) /* Base @ of Sector 9, 128 Kbytes */
#define FLASH_SECTOR10_ADDR_START    	((uint32_t)0x080C0000) /* Base @ of Sector 10, 128 Kbytes */
#define FLASH_SECTOR11_ADDR_START    	((uint32_t)0x080E0000) /* Base @ of Sector 11, 128 Kbytes */

/* Page 0 */
#define PAGE0_BASE_ADDRESS    ((uint32_t)(FLASH_SECTOR02_ADDR_START))
#define PAGE0_END_ADDRESS     ((uint32_t)(PAGE0_BASE_ADDRESS + (FLASH_SECTOR_SIZE - 1)))
#define PAGE0_ID              FLASH_Sector_2

/* Page 1 */
#define PAGE1_BASE_ADDRESS    ((uint32_t)(FLASH_SECTOR03_ADDR_START))
#define PAGE1_END_ADDRESS     ((uint32_t)(PAGE1_BASE_ADDRESS + (FLASH_SECTOR_SIZE - 1)))
#define PAGE1_ID              FLASH_Sector_3

#define MEMORY_PAGE0              ((uint16_t)0x0000)
#define MEMORY_PAGE1              ((uint16_t)0x0001)

#define MEMORY_ERASED        			0xFFFF
#define MEMORY_RECEIVE_DATA  			0xEEEE
#define MEMORY_VALID_PAGE    			0x0000

#define MEMORY_NO_ERROR       ((uint16_t)0x0000)
#define MEMORY_PAGE_FULL      ((uint16_t)0x0080)
#define NO_VALID_PAGE         ((uint16_t)0x00AB)

#define READ_FROM_PAGE  ((uint8_t)0x00)
#define WRITE_IN_PAGE   ((uint8_t)0x01)

uint8_t Internal_FLASH_Init(void);
uint16_t Internal_FLASH_Read(uint16_t readAddress);
uint8_t Internal_FLASH_Write(uint16_t Address, uint16_t Data);
uint8_t Internal_FLASH_Read8b(uint16_t readAddress);
uint8_t Internal_Flash_Write8b(uint16_t VirtAddress, uint8_t Data);

#endif //__STM32F4_FLASH_H
