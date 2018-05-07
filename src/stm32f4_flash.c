/* Two 16k Flash blocks */
/* Procesor voltage need to be in range 3 (2.7V to 3.6V)*/
#include "stm32f4_flash.h"
//-----------------------------------------
static uint8_t Internal_Flash_Format(void);
static uint16_t Internal_Flash_CheckValidPage(uint8_t Operation);
static uint16_t Internal_Flash_VerifyPage(uint16_t Address, uint16_t Data);
static uint16_t Internal_Flash_TranferPage(uint16_t Address, uint16_t Data);

//----------------------------------------------------------------------------------------
uint8_t Internal_FLASH_Init(void)
{
  uint16_t PageStatus0;
	uint16_t PageStatus1;
  uint16_t indexLoop;
  int16_t x = -1;
  int32_t read_value;
  uint16_t dat;

	/* Unlocks the FLASH control register access */
  FLASH_Unlock();

	/* Write page adress */
  PageStatus0 = (*(__IO uint16_t*)PAGE0_BASE_ADDRESS);
  PageStatus1 = (*(__IO uint16_t*)PAGE1_BASE_ADDRESS);

	/* Check status */
	if(PageStatus0 == MEMORY_ERASED)
	{
		if (PageStatus1 == MEMORY_VALID_PAGE)
		{
			if(FLASH_EraseSector(PAGE0_ID,(uint8_t)VoltageRange_3) != FLASH_COMPLETE) {
				return 0; /* Error */
			}
    }
		else if (PageStatus1 == MEMORY_RECEIVE_DATA)
		{
			if(FLASH_EraseSector(PAGE0_ID, (uint8_t)VoltageRange_3) != FLASH_COMPLETE){
				return 0; /* Error */
			}
			if(FLASH_ProgramHalfWord(PAGE1_BASE_ADDRESS, MEMORY_VALID_PAGE) != FLASH_COMPLETE){
				return 0; /* Error */
			}
    }
    else
		{
			if (Internal_Flash_Format() != FLASH_COMPLETE) {
				return 0; /* Error */
			}
    }
	}
	else if(PageStatus0 == MEMORY_RECEIVE_DATA)
	{
		if (PageStatus1 == MEMORY_VALID_PAGE)
		{
			x=-1;
			for (indexLoop = 0; indexLoop < FLASH_MAX_ADDRESS; indexLoop++)
      {
				if (( *(__IO uint16_t*)(PAGE0_BASE_ADDRESS + 6)) == indexLoop) { x = indexLoop; }
        if (indexLoop != x)
				{
					read_value = Internal_FLASH_Read(indexLoop);
					if (read_value >= 0)
					{
						dat=(uint16_t)(read_value);

						if (Internal_Flash_VerifyPage(indexLoop, dat) != FLASH_COMPLETE) {
							return 0; /* Error */
						}
          }
        }
      }

			if(FLASH_ProgramHalfWord(PAGE0_BASE_ADDRESS, MEMORY_VALID_PAGE) != FLASH_COMPLETE) {
					return 0; /* Error */
			}

			if(FLASH_EraseSector(PAGE1_ID, (uint8_t)VoltageRange_3) != FLASH_COMPLETE) {
					return 0; /* Error */
			}
    }
		else if (PageStatus1 == MEMORY_ERASED)
		{
			if(FLASH_EraseSector(PAGE1_ID, (uint8_t)VoltageRange_3) != FLASH_COMPLETE) {
					return 0; /* Error */
			}
			if(FLASH_ProgramHalfWord(PAGE0_BASE_ADDRESS, MEMORY_VALID_PAGE) != FLASH_COMPLETE) {
					return 0; /* Error */
			}
    }
		else
		{
			if(Internal_Flash_Format() != FLASH_COMPLETE) {
					return 0; /* Error */
			}
    }
	}
	else if(PageStatus0 == MEMORY_VALID_PAGE)
	{
		if (PageStatus1 == MEMORY_VALID_PAGE)
		{
			if(Internal_Flash_Format() != FLASH_COMPLETE) {
					return 0; /* Error */
			}
    }
		else if (PageStatus1 == MEMORY_ERASED)
		{
			if(FLASH_EraseSector(PAGE1_ID, (uint8_t)VoltageRange_3) != FLASH_COMPLETE) {
					return 0; /* Error */
			}
    }
    else
		{
			x=-1;
			for (indexLoop = 0; indexLoop < FLASH_MAX_ADDRESS; indexLoop++)
			{
				if ((*(__IO uint16_t*)(PAGE1_BASE_ADDRESS + 6)) == indexLoop)
				{
					x = indexLoop;
        }
				if (indexLoop != x)
				{
					read_value = Internal_FLASH_Read(indexLoop);
					if (read_value >= 0)
					{
						dat=(uint16_t)(read_value);

						if(Internal_Flash_VerifyPage(indexLoop, dat) != FLASH_COMPLETE) {
							return 0; /* Error */
						}
          }
        }
      }
			if(FLASH_ProgramHalfWord(PAGE1_BASE_ADDRESS, MEMORY_VALID_PAGE)!= FLASH_COMPLETE) {
				return 0; /* Error */
			}
			if(FLASH_EraseSector(PAGE0_ID, (uint8_t)VoltageRange_3)!= FLASH_COMPLETE) {
				return 0; /* Error */
			}
		}
	}
	else
	{
		if(Internal_Flash_Format()!= FLASH_COMPLETE) {
				return 0; /* Error */
		}
	}

  return 1;
}
//----------------------------------------------------------------------------------------
uint16_t Internal_FLASH_Read(uint16_t readAddress)
{
  uint16_t return_value=0;
  uint16_t value = 0;
  uint16_t checkPage = 0;
  uint16_t AddressValue = 0;
  uint32_t Address = 0;
	uint32_t PageStartAddress = 0;

  if(readAddress>=FLASH_MAX_ADDRESS){ return 0; /* Error*/ }

  checkPage=Internal_Flash_CheckValidPage(READ_FROM_PAGE);

  if(checkPage==MEMORY_PAGE0)
	{
    PageStartAddress = (uint32_t)PAGE0_BASE_ADDRESS;
    Address = (uint32_t)(PAGE0_END_ADDRESS-1);
  }
  else if(checkPage==MEMORY_PAGE1)
	{
    PageStartAddress = (uint32_t)PAGE1_BASE_ADDRESS;
    Address = (uint32_t)(PAGE1_END_ADDRESS-1);
  }
  else
	{
    return  0; /* Error*/
  }

  while (Address > (PageStartAddress + 2))
	{
    AddressValue = (*(volatile uint16_t*)Address);

    if (AddressValue == readAddress)
		{
      value = (*(volatile uint16_t*)(Address - 2));
      return_value=0;
      break;
    }
    else
		{
      Address = Address - 4;
    }
  }

  if(return_value==0) {
		return (uint16_t)value;
	}

  return return_value;
}
//----------------------------------------------------------------------------------------
uint8_t Internal_FLASH_Write(uint16_t Address, uint16_t Data)
{
  uint16_t Status = MEMORY_NO_ERROR;

  if(Address>=FLASH_MAX_ADDRESS) { return 1; }

  if(Internal_Flash_VerifyPage(Address, Data) == MEMORY_PAGE_FULL) {
		  if(Internal_Flash_TranferPage(Address, Data) != FLASH_COMPLETE) {
				return 2;
			}
	}

  return 0;
}
//----------------------------------------------------------------------------------------
static uint8_t Internal_Flash_Format(void)
{
	uint8_t status;

  if (FLASH_EraseSector(PAGE0_ID, (uint8_t)VoltageRange_3) != FLASH_COMPLETE) { return 0; }
  if (FLASH_ProgramHalfWord(PAGE0_BASE_ADDRESS, NO_VALID_PAGE) != FLASH_COMPLETE) { return 0; }
	status = FLASH_EraseSector(PAGE1_ID, (uint8_t)VoltageRange_3);

  return status;
}
//----------------------------------------------------------------------------------------
static uint16_t Internal_Flash_CheckValidPage(uint8_t Operation)
{
  uint16_t PageStatus0;
	uint16_t PageStatus1;

  PageStatus0 = (*(__IO uint16_t*)PAGE0_BASE_ADDRESS);
  PageStatus1 = (*(__IO uint16_t*)PAGE1_BASE_ADDRESS);

  switch (Operation)
  {
    case WRITE_IN_PAGE:
      if (PageStatus1 == MEMORY_VALID_PAGE) {
        if (PageStatus0 == MEMORY_RECEIVE_DATA) {
          return MEMORY_PAGE0;
        }
        else {
          return MEMORY_PAGE1;
        }
      }
      else if (PageStatus0 == MEMORY_VALID_PAGE) {
        if (PageStatus1 == MEMORY_RECEIVE_DATA) {
          return MEMORY_PAGE1;
        }
        else {
          return MEMORY_PAGE0;
        }
      }
      else {
        return NO_VALID_PAGE;
      }
    break;
    case READ_FROM_PAGE :
      if (PageStatus0 == MEMORY_VALID_PAGE) {
        return MEMORY_PAGE0;
      }
      else if (PageStatus1 == MEMORY_VALID_PAGE) {
        return MEMORY_PAGE1;
      }
      else {
        return NO_VALID_PAGE ;
      }
    break;
    default:
      return MEMORY_PAGE0;
  }
}
//----------------------------------------------------------------------------------------
static uint16_t Internal_Flash_VerifyPage(uint16_t Address, uint16_t Data)
{
	FLASH_Status FlashStat;
  uint16_t CheckPage;
  uint32_t SelectAddress;
	uint32_t PageEndAddress;

  CheckPage = Internal_Flash_CheckValidPage(WRITE_IN_PAGE);

  if(CheckPage==MEMORY_PAGE0) {
    SelectAddress = (uint32_t)PAGE0_BASE_ADDRESS;
    PageEndAddress = (uint32_t)(PAGE0_END_ADDRESS-1);
  }
  else if(CheckPage==MEMORY_PAGE1) {
    SelectAddress = (uint32_t)PAGE1_BASE_ADDRESS;
    PageEndAddress = (uint32_t)(PAGE1_END_ADDRESS-1);
  }
  else {
    return  NO_VALID_PAGE;
	}

  while (SelectAddress < PageEndAddress) {
    if ((*(__IO uint32_t*)SelectAddress) == 0xFFFFFFFF) {
      FlashStat = FLASH_ProgramHalfWord(SelectAddress, Data);
      if (FlashStat != FLASH_COMPLETE) { return FlashStat; }

      FlashStat = FLASH_ProgramHalfWord(SelectAddress + 2, Address);
      return FlashStat;
    }
    else {
      SelectAddress = SelectAddress + 4;
    }
  }

  return MEMORY_PAGE_FULL;
}
//----------------------------------------------------------------------------------------
static uint16_t Internal_Flash_TranferPage(uint16_t Address, uint16_t Data)
{
	uint32_t SetPageAddress;
  uint16_t prevPageId;
  uint16_t CheckPage;
	uint16_t ValueIndex;
  uint16_t ReadValue;
  uint16_t Value;

  CheckPage = Internal_Flash_CheckValidPage(READ_FROM_PAGE);

  if (CheckPage == MEMORY_PAGE1) {
    SetPageAddress = PAGE0_BASE_ADDRESS;
    prevPageId = PAGE1_ID;
  }
  else if (CheckPage == MEMORY_PAGE0) {
    SetPageAddress = PAGE1_BASE_ADDRESS;
    prevPageId = PAGE0_ID;
  }
  else { return NO_VALID_PAGE; }

  if (FLASH_ProgramByte(SetPageAddress, 0xFF) != FLASH_COMPLETE) 				{ return 0; }
  if (Internal_Flash_VerifyPage(Address, Data) != FLASH_COMPLETE) 	{ return 0; }

  for (ValueIndex = 0; ValueIndex < FLASH_MAX_ADDRESS; ValueIndex++)
	{
    if (ValueIndex != Address)
		{
      ReadValue = Internal_FLASH_Read(ValueIndex);
      if (ReadValue >= 0) {
        if (Internal_Flash_VerifyPage(ValueIndex, ReadValue) != FLASH_COMPLETE) { return 0; }
      }
    }
  }

  if (FLASH_EraseSector(prevPageId, (uint8_t)VoltageRange_3) != FLASH_COMPLETE) 		{ return 0; }
  if (FLASH_ProgramHalfWord(SetPageAddress, MEMORY_VALID_PAGE) != FLASH_COMPLETE) 	{ return 0; }

  return 1;
}
