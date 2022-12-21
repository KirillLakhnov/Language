all: tree.cpp FRONTEND/parser.cpp FRONTEND/main.cpp libraries/FileProcessing.cpp libraries/common.cpp libraries/stack.cpp libraries/stack_common.cpp BACKEND/backend.cpp BACKEND/main.cpp CPU/CPU/CPU.cpp CPU/CPU/CPU_main.cpp CPU/libr/Stack.cpp CPU/libr/Guard.cpp CPU/Assembler/Assembler.cpp CPU/Assembler/Assembler_main.cpp CPU/libr/Str_lib.cpp CPU/Disassembler/Disassembler.cpp CPU/Disassembler/Disassembler_main.cpp
	clang tree.cpp FRONTEND/parser.cpp FRONTEND/main.cpp libraries/FileProcessing.cpp libraries/common.cpp libraries/stack.cpp libraries/stack_common.cpp -fsanitize=address -g -o FRONT
	clang tree.cpp BACKEND/backend.cpp BACKEND/main.cpp libraries/FileProcessing.cpp libraries/common.cpp libraries/stack.cpp libraries/stack_common.cpp -fsanitize=address -g -o BACK
	g++ CPU/Assembler/Assembler.cpp CPU/Assembler/Assembler_main.cpp CPU/libr/Str_lib.cpp -o MY_ASM
	g++ CPU/CPU/CPU.cpp CPU/CPU/CPU_main.cpp CPU/libr/Stack.cpp CPU/libr/Guard.cpp -o MY_CPU

frontend: tree.cpp FRONTEND/parser.cpp FRONTEND/main.cpp libraries/FileProcessing.cpp libraries/common.cpp libraries/stack.cpp libraries/stack_common.cpp
	clang tree.cpp FRONTEND/parser.cpp FRONTEND/main.cpp libraries/FileProcessing.cpp libraries/common.cpp libraries/stack.cpp libraries/stack_common.cpp -fsanitize=address -g -o FRONT

reverse_frontend: tree.cpp REVERSE_FRONTEND/reverse_frontend.cpp REVERSE_FRONTEND/main.cpp libraries/FileProcessing.cpp libraries/common.cpp libraries/stack.cpp libraries/stack_common.cpp
	clang tree.cpp REVERSE_FRONTEND/reverse_frontend.cpp REVERSE_FRONTEND/main.cpp libraries/FileProcessing.cpp libraries/common.cpp libraries/stack.cpp libraries/stack_common.cpp -fsanitize=address -g -o REVERSE

backend: tree.cpp BACKEND/backend.cpp BACKEND/main.cpp libraries/FileProcessing.cpp libraries/common.cpp libraries/stack.cpp libraries/stack_common.cpp 
	clang tree.cpp REVERSE_FRONTEND/reverse_frontend.cpp REVERSE_FRONTEND/main.cpp libraries/FileProcessing.cpp libraries/common.cpp libraries/stack.cpp libraries/stack_common.cpp -fsanitize=address -g -o REVERSE

CPU: CPU/CPU/CPU.cpp CPU/CPU/CPU_main.cpp CPU/libr/Stack.cpp CPU/libr/Guard.cpp
	g++ CPU/CPU/CPU.cpp CPU/CPU/CPU_main.cpp CPU/libr/Stack.cpp CPU/libr/Guard.cpp -o MY_CPU

Assembler: CPU/Assembler/Assembler.cpp CPU/Assembler/Assembler_main.cpp CPU/libr/Str_lib.cpp
	g++ CPU/Assembler/Assembler.cpp CPU/Assembler/Assembler_main.cpp CPU/libr/Str_lib.cpp -o MY_ASM

Disassembler: CPU/Disassembler/Disassembler.cpp CPU/Disassembler/Disassembler_main.cpp CPU/libr/Str_lib.cpp
	g++ CPU/Disassembler/Disassembler.cpp CPU/Disassembler/Disassembler_main.cpp CPU/libr/Str_lib.cpp -o MY_DIS_ASM