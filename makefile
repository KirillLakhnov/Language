frontend: tree.cpp FRONTEND/parser.cpp FRONTEND/main.cpp libraries/FileProcessing.cpp libraries/common.cpp libraries/stack.cpp libraries/stack_common.cpp
	clang tree.cpp FRONTEND/parser.cpp FRONTEND/main.cpp libraries/FileProcessing.cpp libraries/common.cpp libraries/stack.cpp libraries/stack_common.cpp -fsanitize=address -g -o FRONT

reverse_frontend: tree.cpp REVERSE_FRONTEND/reverse_frontend.cpp REVERSE_FRONTEND/main.cpp libraries/FileProcessing.cpp libraries/common.cpp libraries/stack.cpp libraries/stack_common.cpp
	clang tree.cpp REVERSE_FRONTEND/reverse_frontend.cpp REVERSE_FRONTEND/main.cpp libraries/FileProcessing.cpp libraries/common.cpp libraries/stack.cpp libraries/stack_common.cpp -fsanitize=address -g -o FRONT
