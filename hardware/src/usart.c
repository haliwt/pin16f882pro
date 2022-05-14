#include "../inc/usart.h"

volatile eusart_status_t eusartRxLastError;

/**
  Section: EUSART APIs
  SPEN: Serial Port Enable bit 
*/

void (*EUSART_FramingErrorHandler)(void);
void (*EUSART_OverrunErrorHandler)(void);
void (*EUSART_ErrorHandler)(void);

void EUSART_DefaultFramingErrorHandler(void);
void EUSART_DefaultOverrunErrorHandler(void);
void EUSART_DefaultErrorHandler(void);

void EUSART_Initialize(void)
{
    
    
    // disable interrupts before changing states
    //PIE1bits.RCIE = 0;
   // EUSART_SetRxInterruptHandler(EUSART_Receive_ISR);
   // PIE1bits.TXIE = 0;
   // EUSART_SetTxInterruptHandler(EUSART_Transmit_ISR);

    // Set the EUSART module to the options selected in the user interface.

    // ABDOVF no_overflow; SCKP Non-Inverted; BRG16=16bit_generator; WUE disabled; ABDEN disabled; 
   //BAUD = 0x08;

    // receive status and control reg: SPEN enabled; RX9 8-bit; CREN enabled; ADDEN disabled; SREN disabled; 
    RCSTA = 0x90;

    //transmit status and control reg:TX9 8-bit; TX9D 0; SENDB sync_break_complete; TXEN enabled; SYNC asynchronous; BRGH hi_speed; 
    TXSTA = 0x24;

    // BRGH 0; 
    BRGH = 0x00;
    // SPBRG 6 ,BAUD RATE 9600
    SPBRG = 0x6;

   


    EUSART_SetFramingErrorHandler(EUSART_DefaultFramingErrorHandler);
    EUSART_SetOverrunErrorHandler(EUSART_DefaultOverrunErrorHandler);
    EUSART_SetErrorHandler(EUSART_DefaultErrorHandler);

    eusartRxLastError.status = 0;

    // enable receive interrupt
    //PIE1bits.RCIE = 1;

}

bool EUSART_is_tx_ready(void)
{
    return (bool)(PIR1bits.TXIF && TXSTAbits.TXEN);
}

bool EUSART_is_rx_ready(void)
{
    return (bool)(PIR1bits.RCIF);
}

bool EUSART_is_tx_done(void)
{
    return TXSTAbits.TRMT;
}

eusart_status_t EUSART_get_last_status(void){
    return eusartRxLastError;
}

uint8_t EUSART_Read(void)
{
    while(!PIR1bits.RCIF)
    {
    }

    eusartRxLastError.status = 0;
    
    if(1 == RCSTAbits.OERR)
    {
        // EUSART error - restart

        RCSTAbits.CREN = 0; 
        RCSTAbits.CREN = 1; 
    }

    return RCREG;
}

void EUSART_Write(uint8_t txData)
{
    while(0 == PIR1bits.TXIF)
    {
    }

    TXREG = txData;    // Write the data byte to the USART.
}

char getch(void)
{
    return EUSART_Read();
}

void putch(char txData)
{
    EUSART_Write(txData);
}



void EUSART_DefaultFramingErrorHandler(void){}

void EUSART_DefaultOverrunErrorHandler(void){
    // EUSART error - restart

    RCSTAbits.CREN = 0;
    RCSTAbits.CREN = 1;

}

void EUSART_DefaultErrorHandler(void){
}

void EUSART_SetFramingErrorHandler(void (* interruptHandler)(void)){
    EUSART_FramingErrorHandler = interruptHandler;
}

void EUSART_SetOverrunErrorHandler(void (* interruptHandler)(void)){
    EUSART_OverrunErrorHandler = interruptHandler;
}

void EUSART_SetErrorHandler(void (* interruptHandler)(void)){
    EUSART_ErrorHandler = interruptHandler;
}


/**
  End of File
*/
