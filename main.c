#define F_CPU 8000000UL

#include <avr/io.h>

void PORT_INIT(void);
void SPI_SLAVE_INIT(void);
char SPI_DATA_EXCHANGE(char databyte);

int main(void){
	DDRA = 0xFF;
	
	PORT_INIT();
	SPI_SLAVE_INIT();
	
	char receive = SPI_DATA_EXCHANGE('A');
	
	PORTA = receive;
}

/*!
 *	@brief Initialize ports.
 */

void PORT_INIT(void){
	DDRB &= ~((1<<PB4)|(1<<PB5)|(1<<PB7));			///< Set MOSI, SCK and SS pins to input.
	DDRB |= (1<<PB6);					///< Set MISO pin to output.
}

/*!
 *	@brief Initialize SPI in master mode.
 */

void SPI_SLAVE_INIT(void){
	SPCR = (1<<SPE);					///< Enable SPI in Slave SPI mode.
}

/*!
 *	@brief Exchange a databyte over SPI.
 *	@param Databyte to be sent.
 *	@return Databyte received.
 */

char SPI_DATA_EXCHANGE(char databyte){
	SPDR = databyte;					///< Load the data byte to the SPDR shift register to transmit.
	while(!(SPSR & (1<<SPIF)));				///< Wait until the full data byte is received.
	return SPDR;						///< Return the received databyte.
}
