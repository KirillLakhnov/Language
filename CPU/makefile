all: CPU/CPU.cpp CPU/CPU_main.cpp libr/Stack.cpp libr/Guard.cpp Assembler/Assembler.cpp Assembler/Assembler_main.cpp libr/Str_lib.cpp Disassembler/Disassembler.cpp Disassembler/Disassembler_main.cpp
	g++ Assembler/Assembler.cpp Assembler/Assembler_main.cpp libr/Str_lib.cpp -o MY_ASM
	g++ CPU/CPU.cpp CPU/CPU_main.cpp libr/Stack.cpp libr/Guard.cpp -o MY_CPU



CPU: CPU/CPU.cpp CPU/CPU_main.cpp libr/Stack.cpp libr/Guard.cpp
	g++ CPU/CPU.cpp CPU/CPU_main.cpp libr/Stack.cpp libr/Guard.cpp -o MY_CPU

Assembler: Assembler/Assembler.cpp Assembler/Assembler_main.cpp libr/Str_lib.cpp
	g++ Assembler/Assembler.cpp Assembler/Assembler_main.cpp libr/Str_lib.cpp -o MY_ASM

Disassembler: Disassembler/Disassembler.cpp Disassembler/Disassembler_main.cpp libr/Str_lib.cpp
	g++ Disassembler/Disassembler.cpp Disassembler/Disassembler_main.cpp libr/Str_lib.cpp -o MY_DIS_ASM