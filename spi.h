#ifndef __SPI_H
#define __SPI_H
#include <pconfig.h>

#include "p18cxxx.h"
/* PIC18 SPI peripheral library header */


/* SSPSTAT REGISTER */

// Master SPI mode only

#define   SMPEND        0b10000000           // Input data sample at end of data out             
#define   SMPMID        0b00000000           // Input data sample at middle of data out


#define   MODE_00       0b00000000              // Setting for SPI bus Mode 0,0
//CKE           0x40                   // SSPSTAT register 
//CKP           0x00                   // SSPCON1 register 

#define   MODE_01       0b00000001              // Setting for SPI bus Mode 0,1
//CKE           0x00                   // SSPSTAT register 
//CKP           0x00                   // SSPCON1 register

#define   MODE_10       0b00000010              // Setting for SPI bus Mode 1,0
//CKE           0x40                   // SSPSTAT register
//CKP           0x10                   // SSPCON1 register

#define   MODE_11       0b00000011              // Setting for SPI bus Mode 1,1
//CKE           0x00                   // SSPSTAT register
//CKP           0x10                   // SSPCON1 register

/* SSPCON1 REGISTER */
#define   SSPENB        0b00100000           // Enable serial port and configures SCK, SDO, SDI

#define   SPI_FOSC_4    0b00000000              // SPI Master mode, clock = Fosc/4
#define   SPI_FOSC_16   0b00000001              // SPI Master mode, clock = Fosc/16
#define   SPI_FOSC_64   0b00000010              // SPI Master mode, clock = Fosc/64
#define   SPI_FOSC_TMR2 0b00000011              // SPI Master mode, clock = TMR2 output/2
#define   SLV_SSON      0b00000100              // SPI Slave mode, /SS pin control enabled
#define   SLV_SSOFF     0b00000101              // SPI Slave mode, /SS pin control disabled
//************************************************************************************************//

/*  25Cxxx EEPROM instruction set */
#define   SPI_WREN          6              // write enable latch
#define   SPI_WRDI          4              // reset the write enable latch
#define   SPI_RDSR          5              // read status register
#define   SPI_WRSR          1              // write status register
#define   SPI_READ          3              // read data from memory
#define   SPI_WRITE         2              // write data to memory

/*  Bits within status register of 25Cxxx */
#define   WIP           0              // write in progress status
#define   WEL           1              // write enable latch status
#define   BP0           2              // block protection bit status
#define   BP1           3              // block protection bit status


/* FUNCTION PROTOTYPES */

#define PARAM_SCLASS auto


/* These devices have two SPI modules */
#if defined (SPI_V2) || defined (SPI_V3) || defined (SPI_V5)

/* ***** SPI1 ***** */
#define  CloseSPI 		CloseSPI1

#define  DataRdySPI 	DataRdySPI1

#define  ReadSPI        ReadSPI1

/* CloseSPI1
 * Disable SPI1 module
 */
#define  CloseSPI1()    (SSP1CON1 &=0xDF)

/* DataRdySPI1
 * Test if SSP1BUF register is full
 */
#define  DataRdySPI1()  (SSP1STATbits.BF)

/* getcSPI1
 * Read byte from SSP1BUF register
 */
#define  getcSPI1  ReadSPI1
#define  getcSPI   getcSPI1

#define OpenSPI OpenSPI1

#define WriteSPI WriteSPI1

/* putcSPI1
 * Write byte to SSP1BUF register
 */
#define  putcSPI1  WriteSPI1
#define  putcSPI putcSPI1

#define getsSPI getsSPI1

#define putsSPI putsSPI1


/* OpenSPI1
 */
void OpenSPI1( PARAM_SCLASS unsigned char sync_mode,
               PARAM_SCLASS unsigned char bus_mode,
               PARAM_SCLASS unsigned char smp_phase );
			   
/* WriteSPI1
 * Write byte to SSP1BUF register
 */
unsigned char WriteSPI1( PARAM_SCLASS unsigned char data_out );

/* getsSPI1
 * Write string to SSP1BUF
 */
void getsSPI1( PARAM_SCLASS unsigned char *rdptr, PARAM_SCLASS unsigned char length );

/* putsSPI1
 * Read string from SSP1BUF
 */
void putsSPI1( PARAM_SCLASS unsigned char *wrptr );

/* ReadSPI1
 * Read byte from SSP1BUF register
 */
unsigned char ReadSPI1( void );

#endif
/* ***** SPI2 ***** */

#if defined (SPI_V3) || defined (SPI_V5)

/* CloseSPI2
 * Disable SPI2 module
 */
#define  CloseSPI2()      (SSP2CON1 &=0xDF)

/* DataRdySPI2
 * Test if SSP2BUF register is full
 */
#define  DataRdySPI2()    (SSP2STATbits.BF)

/* getcSPI2
 * Read byte from SSP2BUF register
 */
#define  getcSPI2  ReadSPI2

/* putcSPI2
 * Write byte to SSP2BUF register
 */
#define  putcSPI2  WriteSPI2


/* OpenSPI2
 */
void OpenSPI2( PARAM_SCLASS unsigned char sync_mode,
               PARAM_SCLASS unsigned char bus_mode,
               PARAM_SCLASS unsigned char smp_phase );

/* WriteSPI2
 * Write byte to SSP2BUF register
 */
unsigned char WriteSPI2( PARAM_SCLASS unsigned char data_out );

/* getsSPI2
 * Write string to SSP2BUF
 */
void getsSPI2( PARAM_SCLASS unsigned char *rdptr, PARAM_SCLASS unsigned char length );

/* putsSPI2
 * Read string from SSP2BUF
 */
void putsSPI2( PARAM_SCLASS unsigned char *wrptr );

/* ReadSPI2
 * Read byte from SSP2BUF register
 */
unsigned char ReadSPI2( void );

#endif // v2 and v3

#if defined (SPI_V1) || defined (SPI_V4)

/* ***** SPI ***** */

/* CloseSPI1
 * Disable SPI1 module
 */
#define  CloseSPI()    (SSPCON1 &=0xDF)

/* DataRdySPI
 * Test if SSPBUF register is full
 */
#define  DataRdySPI()    (SSPSTATbits.BF)

/* getcSPI
 * Read byte from SSPBUF register
 */
#define  getcSPI  ReadSPI

/* putcSPI
 * Write byte to SSPBUF register
 */
#define  putcSPI  WriteSPI

/* OpenSPI
 */
void OpenSPI( PARAM_SCLASS unsigned char sync_mode,
              PARAM_SCLASS unsigned char bus_mode,
              PARAM_SCLASS unsigned char smp_phase );

/* WriteSPI
 * Write byte to SSPBUF register
 */
unsigned char WriteSPI( PARAM_SCLASS unsigned char data_out );

/* getsSPI
 * Write string to SSPBUF
 */
void getsSPI( PARAM_SCLASS unsigned char *rdptr, PARAM_SCLASS unsigned char length );

/* putsSPI
 * Read string from SSPBUF
 */
void putsSPI( PARAM_SCLASS unsigned char *wrptr );

/* ReadSPI
 * Read byte from SSPBUF register
 */
unsigned char ReadSPI( void );

#endif 


#endif  /* __SPI_H */

