/*
 * Copyright (C) 2017, 2019   Ken Rabold, Alexander Entinger
 *
 * This file is subject to the terms and conditions of the GNU Lesser
 * General Public License v2.1. See the file LICENSE in the top level
 * directory for more details.
 */

OUTPUT_ARCH( "riscv" )

ENTRY( __start )

MEMORY
{
  flash (rxai!w) : ORIGIN = 0x20010000, LENGTH = 0x0006a120
  ram   (wxa!ri) : ORIGIN = 0x80000000, LENGTH = 0x00004000
  itim  (wxa!ri) : ORIGIN = 0x08000000, LENGTH = 0x00002000
}

PHDRS
{
  flash PT_LOAD;
  ram_init PT_LOAD;
  ram PT_NULL;
}

SECTIONS
{
  __stack_size    = DEFINED(__stack_size) ? __stack_size : 1K;
  __heap_size     = DEFINED(__heap_size)  ? __heap_size  : 1k;

  .init           :
  {
    KEEP (*(SORT_NONE(.init)))
  } >flash AT>flash :flash

  .text           :
  {
    *(.text.unlikely .text.unlikely.*)
    *(.text.startup .text.startup.*)
    *(.text .text.*)
    *(.gnu.linkonce.t.*)
  } >flash AT>flash :flash

  .fini           :
  {
    KEEP (*(SORT_NONE(.fini)))
  } >flash AT>flash :flash

  PROVIDE (__etext = .);
  PROVIDE (_etext = .);
  PROVIDE (etext = .);

  .rodata         :
  {
    *(.rdata)
    *(.rodata .rodata.*)
    *(.gnu.linkonce.r.*)
  } >flash AT>flash :flash

  . = ALIGN(4);

  .preinit_array  :
  {
    PROVIDE (__preinit_array_start = .);
    KEEP (*(.preinit_array))
    PROVIDE (__preinit_array_end = .);
  } >flash AT>flash :flash

  .init_array     :
  {
    PROVIDE (__init_array_start = .);
    KEEP (*(SORT_BY_INIT_PRIORITY(.init_array.*) SORT_BY_INIT_PRIORITY(.ctors.*)))
    KEEP (*(.init_array EXCLUDE_FILE (*crtbegin.o *crtbegin?.o *crtend.o *crtend?.o ) .ctors))
    PROVIDE (__init_array_end = .);
  } >flash AT>flash :flash

  .fini_array     :
  {
    PROVIDE (__fini_array_start = .);
    KEEP (*(SORT_BY_INIT_PRIORITY(.fini_array.*) SORT_BY_INIT_PRIORITY(.dtors.*)))
    KEEP (*(.fini_array EXCLUDE_FILE (*crtbegin.o *crtbegin?.o *crtend.o *crtend?.o ) .dtors))
    PROVIDE (__fini_array_end = .);
  } >flash AT>flash :flash

  .ctors          :
  {
    /* gcc uses crtbegin.o to find the start of
       the constructors, so we make sure it is
       first.  Because this is a wildcard, it
       doesn't matter if the user does not
       actually link against crtbegin.o; the
       linker won't look for a file to match a
       wildcard.  The wildcard also means that it
       doesn't matter which directory crtbegin.o
       is in.  */
    KEEP (*crtbegin.o(.ctors))
    KEEP (*crtbegin?.o(.ctors))
    /* We don't want to include the .ctor section from
       the crtend.o file until after the sorted ctors.
       The .ctor section from the crtend file contains the
       end of ctors marker and it must be last */
    KEEP (*(EXCLUDE_FILE (*crtend.o *crtend?.o ) .ctors))
    KEEP (*(SORT(.ctors.*)))
    KEEP (*(.ctors))
  } >flash AT>flash :flash

  .dtors          :
  {
    KEEP (*crtbegin.o(.dtors))
    KEEP (*crtbegin?.o(.dtors))
    KEEP (*(EXCLUDE_FILE (*crtend.o *crtend?.o ) .dtors))
    KEEP (*(SORT(.dtors.*)))
    KEEP (*(.dtors))
  } >flash AT>flash :flash

  .lalign         :
  {
    . = ALIGN(4);
    PROVIDE( __data_src_start = . );
  } >flash AT>flash :flash

  .dalign         :
  {
    . = ALIGN(4);
 		PROVIDE( __data_dst_start = . );
  } >ram AT>flash :ram_init

  .data          :
  {
    *(.ramfunc .ramfunc.*)
    *(.data .data.*)
    *(.gnu.linkonce.d.*)
    . = ALIGN(8);
    PROVIDE( __global_pointer$ = . + 0x800 );
    *(.sdata .sdata.*)
    *(.gnu.linkonce.s.*)
    . = ALIGN(8);
    *(.srodata.cst16)
    *(.srodata.cst8)
    *(.srodata.cst4)
    *(.srodata.cst2)
    *(.srodata .srodata.*)
  } >ram AT>flash :ram_init

  . = ALIGN(4);
  PROVIDE( __data_dst_end = . );

  PROVIDE( __bss_start = . );
  .bss            :
  {
    *(.sbss*)
    *(.gnu.linkonce.sb.*)
    *(.bss .bss.*)
    *(.gnu.linkonce.b.*)
    *(COMMON)
    . = ALIGN(4);
  } >ram AT>ram :ram

  . = ALIGN(8);
  PROVIDE( __bss_end = . );

  .stack :
  {
    PROVIDE( __stack_start = . );
    . = __stack_size;
    PROVIDE( __stack_end = .) ;
  } >ram AT>ram :ram

  .heap :
	{
		PROVIDE( __heap_start = . );
		. = __heap_size;
		. = __heap_size == 0 ? 0 : ORIGIN(ram) + LENGTH(ram);
		PROVIDE( __heap_end = . );
	} >ram AT>ram :ram
}
