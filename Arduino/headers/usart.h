#ifndef __USART_H__
#define __USART_H__

#define BAUD 9600
#define UBBR_VALUE (16000000UL/(16UL * BAUD) - 1)

void USARTSetup() {
  UBRR0H = (unsigned char)(UBBR_VALUE >> 8);
  UBRR0L = (unsigned char)UBBR_VALUE;
  UCSR0B = (1 << TXEN0) | (1 << RXEN0); // ENABLE TRANSMIT AND RECEIVE
  UCSR0C = (1 << UCSZ01) | (1 << UCSZ00) | (1 << USBS0); // ENABLE 8 BIT DATA FRAME, 1 STOP BIT
}

void USARTWriteChar(unsigned char data) {
  while ((UCSR0A & (1 << UDRE0)) == 0 ) {}
  UDR0 = data;
}

void USARTWriteString(char* data) {
  if (data == NULL) {
    return;
  }

  while(*data != '\0') {
    USARTWriteChar(*data);
    data++;
  }
}

#endif
