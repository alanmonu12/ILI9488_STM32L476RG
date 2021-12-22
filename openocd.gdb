target extended-remote :3333

file build/ILI9488_STM32L476.elf

load

# print demangled symbols
set print asm-demangle on

# detect unhandled exceptions, hard faults and panics
#break DefaultHandler
#break HardFault
#break rust_begin_unwind
break main

monitor arm semihosting enable

# start the process but immediately halt the processor
c

# Se activa el cliente grafico de GDB
tui enable