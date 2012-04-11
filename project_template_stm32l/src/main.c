
#include <stddef.h>
#include "stm32l1xx.h"

#ifdef USE_STM32L152_EVAL
 #include "stm32_eval.h"
 #include "stm32l152_eval_lcd.h"
#elif defined USE_STM32L_DISCOVERY
 #include "discover_board.h"
 #include "stm32l_discovery_lcd.h"
#endif

/* Private typedef */
/* Private define  */


/* Private macro */
/* Private variables */


USART_InitTypeDef USART_InitStructure;

/* Private function prototypes */
/* Private functions */
#ifdef USE_STM32L_DISCOVERY
 void Init_GPIOs (void);
 void RCC_Configuration(void);

 static volatile uint32_t TimingDelay;
 RCC_ClocksTypeDef RCC_Clocks;

 void Config_Systick()
 {
   RCC_GetClocksFreq(&RCC_Clocks);
   SysTick_Config(RCC_Clocks.HCLK_Frequency / 1000);
 }
#endif

/**
**===========================================================================
**
**  Abstract: main program
**
**===========================================================================
*/


 //--

 /* this variable can be used for accelerate the scrolling exit when push user button */
 bool KeyPressed = FALSE;

  /*bar0 bar2 */


 /******************* (C) COPYRIGHT 2011 STMicroelectronics *****END OF FILE****/

 //--
int main(void)
{
  int i = 0;

  /*!< At this stage the microcontroller clock setting is already configured,
        this is done through SystemInit() function which is called from startup
        file (startup_stm32l1xx_md.s) before to branch to application main.
        To reconfigure the default setting of SystemInit() function, refer to
        system_stm32l1xx.c file
      */

#ifdef USE_STM32L152_EVAL
  /* Initialize LEDs */
  STM_EVAL_LEDInit(LED1);
  STM_EVAL_LEDInit(LED2);
  STM_EVAL_LEDInit(LED3);
  STM_EVAL_LEDInit(LED4);

  /* Turn on LEDs */
  STM_EVAL_LEDOn(LED1);
  STM_EVAL_LEDOn(LED2);
  STM_EVAL_LEDOn(LED3);
  STM_EVAL_LEDOn(LED4);

  /* Initialize the LCD */
  STM32L152_LCD_Init();

  /* Display message on STM3210X-EVAL LCD */
  /* Clear the LCD */
  LCD_Clear(White);

  /* Set the LCD Back Color */
  LCD_SetBackColor(Blue);
  /* Set the LCD Text Color */
  LCD_SetTextColor(White);
  LCD_DisplayStringLine(Line0, (uint8_t *)MESSAGE1);
  LCD_DisplayStringLine(Line1, (uint8_t *)MESSAGE2);
  LCD_DisplayStringLine(Line2, (uint8_t *)MESSAGE3);
  LCD_DisplayStringLine(Line3, (uint8_t *)MESSAGE4);
  LCD_DisplayStringLine(Line4, (uint8_t *)MESSAGE5);
  LCD_DisplayStringLine(Line5, (uint8_t *)MESSAGE6);

  /* USARTx configured as follow:
        - BaudRate = 115200 baud
        - Word Length = 8 Bits
        - One Stop Bit
        - No parity
        - Hardware flow control disabled (RTS and CTS signals)
        - Receive and transmit enabled
  */
  USART_InitStructure.USART_BaudRate = 115200;
  USART_InitStructure.USART_WordLength = USART_WordLength_8b;
  USART_InitStructure.USART_StopBits = USART_StopBits_1;
  USART_InitStructure.USART_Parity = USART_Parity_No;
  USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
  USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;

  STM_EVAL_COMInit(COM1, &USART_InitStructure);

#elif defined USE_STM32L_DISCOVERY
  RCC_Configuration();
  /* Init I/O ports */
  Init_GPIOs ();

  /* Init Systick */
  Config_Systick();

  /* Initializes the LCD glass */


  /* Switch on the leds at start */
  GPIO_HIGH(LD_PORT,LD_GREEN);
  GPIO_LOW(LD_PORT,LD_BLUE);
#endif

  /* TODO - Add your application code here */

  /* Infinite loop */
  while (1)
  {
	i++;
#ifdef USE_STM32L152_EVAL
	STM_EVAL_LEDToggle(LED1);
#elif defined USE_STM32L_DISCOVERY
    /* Check if the User Button is pressed */
/*
    if ((GPIOA->IDR & USER_GPIO_PIN) != 0x0)
    {
      //LCD_GLASS_DisplayString((uint8_t*)"BLUE   ");
       Toggle blue LED
      GPIO_TOGGLE(LD_PORT,LD_BLUE);
    }
    else
    {
      //LCD_GLASS_DisplayString((uint8_t*)"GREEN  ");
       Toggle green LED
      GPIO_TOGGLE(LD_PORT,LD_GREEN);
    }
*/
#endif
  }
  return 0;
}

#ifdef  USE_FULL_ASSERT

/**
  * @brief  Reports the name of the source file and the source line number
  *   where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t* file, uint32_t line)
{
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */

  /* Infinite loop */
  while (1)
  {
  }
}
#endif

/*
 * Minimal __assert_func used by the assert() macro
 * */
void __assert_func(const char *file, int line, const char *func, const char *failedexpr)
{
  while(1)
  {}
}

/*
 * Minimal __assert() uses __assert__func()
 * */
void __assert(const char *file, int line, const char *failedexpr)
{
   __assert_func (file, line, NULL, failedexpr);
}

#ifdef USE_SEE
#ifndef USE_DEFAULT_TIMEOUT_CALLBACK
/**
  * @brief  Basic management of the timeout situation.
  * @param  None.
  * @retval sEE_FAIL.
  */
uint32_t sEE_TIMEOUT_UserCallback(void)
{
  /* Return with error code */
  return sEE_FAIL;
}
#endif
#endif /* USE_SEE */


//#ifdef USE_STM32L_DISCOVERY
/**
  * @brief  Configures the different system clocks.
  * @param  None
  * @retval None
  */
void RCC_Configuration(void)
{
  /* Enable the GPIOs Clock */
  RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOA | RCC_AHBPeriph_GPIOB | RCC_AHBPeriph_GPIOC| RCC_AHBPeriph_GPIOD| RCC_AHBPeriph_GPIOE| RCC_AHBPeriph_GPIOH, ENABLE);

  /* Enable comparator clock */
  RCC_APB1PeriphClockCmd(RCC_APB1Periph_COMP | RCC_APB1Periph_LCD | RCC_APB1Periph_PWR,ENABLE);

  /* Enable SYSCFG */
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_SYSCFG , ENABLE);

  /* Allow access to the RTC */
  PWR_RTCAccessCmd(ENABLE);

  /* Reset Backup Domain */
  RCC_RTCResetCmd(ENABLE);
  RCC_RTCResetCmd(DISABLE);

  /*!< LSE Enable */
  RCC_LSEConfig(RCC_LSE_ON);

  /*!< Wait till LSE is ready */
  while (RCC_GetFlagStatus(RCC_FLAG_LSERDY) == RESET)
  {}

  /*!< LCD Clock Source Selection */
  RCC_RTCCLKConfig(RCC_RTCCLKSource_LSE);
}

/**
  * @brief  To initialize the I/O ports
  * @caller main
  * @param None
  * @retval None
  */
void  Init_GPIOs (void)
{
  GPIO_InitTypeDef GPIO_InitStructure;

  /* Configure User Button pin as input */
  GPIO_InitStructure.GPIO_Pin = USER_GPIO_PIN;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;
  GPIO_Init(BUTTON_GPIO_PORT, &GPIO_InitStructure);


/* Configure the GPIO_LED pins  LD3 & LD4*/
  GPIO_InitStructure.GPIO_Pin = LD_GREEN|LD_BLUE;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;
  GPIO_Init(LD_PORT, &GPIO_InitStructure);
  GPIO_LOW(LD_PORT,LD_GREEN);
  GPIO_LOW(LD_PORT,LD_BLUE);
}
//--


/**
  * @brief  Inserts a delay time.
  * @param  nTime: specifies the delay time length, in 10 ms.
  * @retval None
  */
void Delay(uint32_t nTime)
{
  TimingDelay = nTime;

  while(TimingDelay != 0);

}

/**
  * @brief  Decrements the TimingDelay variable.
  * @param  None
  * @retval None
  */
void TimingDelay_Decrement(void)
{

  if (TimingDelay != 0x00)
  {
    TimingDelay--;
  }

}

