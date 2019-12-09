/**************************************************************************************
 * INCLUDE
 **************************************************************************************/

#include <stdint.h>

#include <algorithm>

/**************************************************************************************
 * TYPEDEFS
 **************************************************************************************/

typedef void(*FuncType)(void);

/**************************************************************************************
 * GLOBAL VARIABLES
 **************************************************************************************/

/* These external variables are defined by the linker script and define various
 * sections which need to be preset with a certain value or (bss sections needs
 * to be zeroed, data section needs to be initialized with data stored in flash,
 * ctors of static global objects need to be called, ...)
 */
extern uintptr_t  __bss_start;
extern uintptr_t  __bss_end;
extern uintptr_t  __data_src_start;
extern uintptr_t  __data_dst_start;
extern uintptr_t  __data_dst_end;

extern FuncType   __preinit_array_start[];
extern FuncType   __preinit_array_end  [];
extern FuncType   __init_array_start   [];
extern FuncType   __init_array_end     [];
extern FuncType   __fini_array_start   [];
extern FuncType   __fini_array_end     [];

/**************************************************************************************
 * FUNCTION PROTOTYPES
 **************************************************************************************/

extern "C" void __start(void) __attribute__ ((noreturn)) __attribute__ ((section (".text.startup")));

void init_bss     ();
void init_data    ();
void preinit_array();
void init_array   ();
void fini_array   ();

/**************************************************************************************
 * FUNCTION IMPLEMENTATION
 **************************************************************************************/

extern "C" void __start(void)
{
  /* Load global pointer */
  asm volatile("la gp, __global_pointer$");

  /* Initialize stack pointer */
  asm volatile("la sp, __stack_end");
  asm volatile("andi sp, sp, -16");

  /* Clear the BSS segment */
  init_bss();

  /* Perform the ROM-to-RAM initialisation */
  init_data();

  /* Perform preinit/init steps - call static ctors */
  preinit_array();
  init_array();

  /* Jump to main */
  asm volatile("call main");

  /* In case we should return from main perform deinitialisation - calling static dtors */
  fini_array();

  /* Loop forever and don't return */
  for(;;) { }
}

void init_bss()
{
  std::fill(&__bss_start, &__bss_end, 0U);
}

void init_data()
{
  /* Calculate the size of the data section */
  std::size_t const cnt = (&__data_dst_end - &__data_dst_start);

  /* Copy the data initialisation code from flash to RAM */
  std::copy(&__data_src_start,
            &__data_src_start + cnt,
            &__data_dst_start);
}

void preinit_array()
{
  std::for_each(__preinit_array_start,
                __preinit_array_end,
                [](FuncType const func)
                {
                  func();
                });
}

void init_array()
{
  std::for_each(__init_array_start,
                __init_array_end,
                [](FuncType const func)
                {
                  func();
                });
}

void fini_array()
{
  std::for_each(__fini_array_start,
                __fini_array_end,
                [](FuncType const func)
                {
                  func();
                });
}
