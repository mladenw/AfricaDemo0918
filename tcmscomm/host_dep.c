/**********************************************************************
Copyright (C) Siemens AG 1997 All rights reserved. Confidential

Permission is hereby granted, without written agreement and without
license or royalty fees, to use and modify this software and its
documentation for the use with SIEMENS PC104 cards.

IN NO EVENT SHALL SIEMENS AG BE LIABLE TO ANY PARTY FOR DIRECT,
INDIRECT, SPECIAL, INCIDENTAL, OR CONSEQUENTIAL DAMAGES ARISING OUT
OF THE USE OF THIS SOFTWARE AND ITS DOCUMENTATION, EVEN IF SIEMENS AG
HAS BEEN ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

SIEMENS AG SPECIFICALLY DISCLAIMS ANY WARRANTIES,INCLUDING, BUT NOT
LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
A PARTICULAR PURPOSE.  THE SOFTWARE PROVIDED HEREUNDER IS ON AN
"AS IS" BASIS, AND SIEMENS AG HAS NO OBLIGATION TO PROVIDE MAINTENANCE,
SUPPORT, UPDATES, ENHANCEMENTS, OR MODIFICATIONS.
**=====================================================================
** PROJECT::   TCN
** MODULE::    PC104 CLASS1.1-1.3
** WORKFILE::  $Workfile:   host_dep.c  $
**---------------------------------------------------------------------
** TASK::
   Application Programmers Interface (API) for PC104 access.
   Functions which depend on the host-system

**---------------------------------------------------------------------
** AUTHOR::    REINWALD_LU
** CREATED::   13.01.1998
**---------------------------------------------------------------------
** CONTENTS::
      functions:
        writeWordToTS()
        readWordFromTS()
        MVB_INT_ENABLE()
        MVB_INT_DISABLE()
        Wait2MS()
        Wait100US()

    #if defined (MVB_M)
         ReadMVBMConfig()
         SaveMVBMConfig()
    #endif

**---------------------------------------------------------------------
** NOTES::     -

**=====================================================================
** HISTORY::   AUTHOR::   Graf Ralf
               REVISION:: 2.2
               MODTIME::  Apr 15 1999
**---------------------------------------------------------------------

**********************************************************************/

#include "config.h"
#include "host_dep.h"
#include "dpr_dep.h"
#include "cl1_ret.h"
#include "cl1_1.h"

//#define DEBUG
/*---------- access to traffic-store --------------------------------*/

#ifdef __QNX__

/* {{{ QNXRTP */

#include <sys/mman.h>
#include <errno.h>
#include <stdio.h>

#ifdef __QNXNTO__
#include <sys/neutrino.h>
#else
#include <fcntl.h>
#endif // __QNXNTO__

static void* mmaped_device_memory = 0L;
//static void* original_addr = 0L;

void* mmap_address( void* addr )
{
  unsigned long a;
  void* new_addr;
#ifdef __WATCOMC__ // for QNX4
  int fd;
#endif
#ifdef __QNXNTO__
  ThreadCtl(_NTO_TCTL_IO, 0);
#endif // __QNXNTO__

  /* map the mvb device memory */
  if( mmaped_device_memory == 0L )
    {
#ifdef DEBUG
      printf( "Lets mmap %p!\n", addr );
#endif // DEBUG

#ifdef __WATCOMC__ // for QNX4
      if( (fd = shm_open( "Physical", O_RDWR, 0 )) == -1)
        {
          printf("Error opening shared memory, error %d\n", errno );
          exit( 1 );
        }
      mmaped_device_memory =
        mmap( 0, 65536, PROT_READ|PROT_WRITE, MAP_SHARED, fd, 0xd0000 );
#else // __WATCOM__
      mmaped_device_memory =
        mmap_device_memory( /*addr*/ 0,
                            /*len*/  65536,
                            /*prot*/ PROT_NOCACHE | PROT_READ | PROT_WRITE,
                            /*flags*/0,
                            /*physical*/ 0xd0000 );
#endif // __WATCOM__

      if ( mmaped_device_memory == MAP_FAILED )
        {
          printf("Mapping failed with code %d\n", errno );
          switch( errno )
            {
            case EINVAL: printf("The flags type is invalid.\n");
              break;
            case ENOMEM: printf("The address range requested is outside of the allowed process address range, or there wasn't enough memory to satisfy the request.\n");
              break;
            case ENXIO: printf("The address from off for len bytes is invalid for the requested object, or if MAP_FIXED specified and addr, len, off are invalid for the requested object.\n");
            default:
              break;
            }
          exit( 10 );
        }
#ifdef DEBUG
      printf( "Mapped mem addr: %p\n", mmaped_device_memory );
#endif
    }

  a = (unsigned long) addr & 0xFFFF;
  new_addr = (void*)( a + (unsigned long)mmaped_device_memory );
  return new_addr;
}

#ifdef __QNXNTO__

#if 0
static void munmap_address()
{
  ThreadCtl(_NTO_TCTL_IO, 0);
#ifdef DEBUG
  printf( "Lets munmap %p!\n", original_addr );
#endif
  /* map the mvb device memory */
  if( munmap_device_memory( /*addr*/ (void*)0xd0000,
                            /*len*/  65536 ) == -1 )
    {
      printf("Unmapping failed with code %d\n", errno );
      switch( errno )
        {
        case ENOMEM: printf("The address range requested is outside of the allowed process address range, or there wasn't enough memory to satisfy the request.\n");
          break;
        case ENXIO: printf("The address from off for len bytes is invalid for the requested object, or if MAP_FIXED specified and addr, len, off are invalid for the requested object.\n");
          break;
        case EINVAL: printf("The addresses in the specified range are outside the range allowed for the address space of a process.\n");
          break;
        case ENOSYS: printf("The function munmap() isn't supported by this implementation.\n");
        default:
          break;
        }
      exit( 10 );
    }
  original_addr = mmaped_device_memory = 0L;
}
#endif // 0

#endif // __QNXNTO__

void writeWordToTS(void* addr, TM_TYPE_WORD val)
{
  /*      PREFIX_WRITE_TS */
  addr = mmap_address( addr );
  *(TM_TYPE_WORD*) addr = val;
  /*      POSTFIX_WRITE_TS */
  //printf("writeWord: Address %p, Val %d\n", addr, val );
  //munmap_address();
  return;
} /* writeWordToTS */


TM_TYPE_WORD readWordFromTS(void* addr)
{
  TM_TYPE_WORD val = 0;
  /*      PREFIX_READ_TS */
  addr = mmap_address( addr );
  val = (*(TM_TYPE_WORD*) addr);
  /*      POSTFIX_READ_TS */
  //printf("readWord: Address %p, Val %d\n", addr, val );
  //munmap_address();
  return (val);
} /* readWordFromTS */

/* ================================================= original */

/* }}} */

//#else //__QNXRTP__


//#endif //__QNXRTP__

#endif //__QNX__







#ifdef linux

#include <sys/mman.h>
#include <errno.h>
#include <stdio.h>

#include <fcntl.h>
#include <stdlib.h>

static void* mmaped_device_memory = 0L;

void* mmap_address( void* addr )
{
  unsigned long a;
  void* new_addr;
  int fd;

  /* map the mvb device memory */
  if( mmaped_device_memory == 0L )
    {
#ifdef DEBUG
      printf( "Lets mmap %p!\n", addr );
#endif // DEBUG

      if( (fd = open( "/dev/mem", O_RDWR, 0 )) == -1)
        {
          printf("Error opening shared memory, error %d\n", errno );
          exit( 1 );
        }
      mmaped_device_memory =
        mmap( 0, 65536, PROT_READ|PROT_WRITE, MAP_SHARED, fd, 0xd0000 );

      if ( mmaped_device_memory == MAP_FAILED )
        {
          printf("Mapping failed with code %d\n", errno );
          switch( errno )
            {
            case EINVAL: printf("The flags type is invalid.\n");
              break;
            case ENOMEM: printf("The address range requested is outside of the allowed process address range, or there wasn't enough memory to satisfy the request.\n");
              break;
            case ENXIO: printf("The address from off for len bytes is invalid for the requested object, or if MAP_FIXED specified and addr, len, off are invalid for the requested object.\n");
            default:
              break;
            }
          exit( 10 );
        }
#ifdef DEBUG
      printf( "Mapped mem addr: %p\n", mmaped_device_memory );
#endif
    }

  a = (unsigned long) addr & 0xFFFF;
  new_addr = (void*)( a + (unsigned long)mmaped_device_memory );
  return new_addr;
}

void writeWordToTS(void* addr, TM_TYPE_WORD val)
{
  /*      PREFIX_WRITE_TS */
  addr = mmap_address( addr );
  *(TM_TYPE_WORD*) addr = val;
  /*      POSTFIX_WRITE_TS */
  //printf("writeWord: Address %p, Val %d\n", addr, val );
  //munmap_address();
  return;
} /* writeWordToTS */


TM_TYPE_WORD readWordFromTS(void* addr)
{
  TM_TYPE_WORD val = 0;
  /*      PREFIX_READ_TS */
  addr = mmap_address( addr );
  val = (*(TM_TYPE_WORD*) addr);
  /*      POSTFIX_READ_TS */
  //printf("readWord: Address %p, Val %d\n", addr, val );
  //munmap_address();
  return (val);
} /* readWordFromTS */

/* ================================================= original */

/* }}} */


#endif // __LINUX__


#if 0

void writeWordToTS(void* addr, TM_TYPE_WORD val)
{
  /*      PREFIX_WRITE_TS */
  *(TM_TYPE_WORD*) addr = val;
  /*      POSTFIX_WRITE_TS */
  printf("writeWord: Address %p, Val %d\n", addr, val );
  return;
} /* writeWordToTS */


TM_TYPE_WORD readWordFromTS(void* addr)
{
  TM_TYPE_WORD val = 0;
  /*      PREFIX_READ_TS */
  val = (*(TM_TYPE_WORD*) addr);
  /*      POSTFIX_READ_TS */
  printf("readWord: Address %p, Val %d\n", addr, val );
  return (val);
} /* readWordFromTS */

#endif //__QNXRTP__

/*---------- interrupt-handling -------------------------------------*/
void MVB_INT_ENABLE(void)
{
  /*
#error  Please insert function to enable interrupts on hostsystem here
  */
}


void MVB_INT_DISABLE(void)
{
  /*
#error  Please insert function to disable interrupts on hostsystem here
  */
}


/*---------- waiting-functions --------------------------------------*/
void Wait2MS(void)
{
  /*
#error  Please insert wait function for about 2 ms here to clear MVBC rx buffer
  */


}


void Wait100US(void)
{

  /*
    #error  Please insert wait function for about 100 us here to allow MVBC access to traffic store
  */
  Wait2MS();

}


/*---------- functions for MVB-M ---------*/
#if defined (MVB_M)
UNSIGNED8 ReadMVBMConfig(
    UNSIGNED8          *buffer,
    UNSIGNED16         bytes
)
{

#error  Please insert function to read the MVBM-Configuration
/* Return values:
                 MVBM_OK
                 MVBM_CONFIG_NOT_AVAIL */
}

UNSIGNED8 SaveMVBMConfig(
    UNSIGNED8          *buffer,
    UNSIGNED16         bytes
)
{
#error  Please insert function to save the MVBM-Configuration
/* Return values:
                 MVBM_OK
                 MVBM_CONFIG_NOT_SAVED */



}
#endif

