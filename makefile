all: tree.cpp FRONTEND/parser.cpp FRONTEND/main.cpp libraries/FileProcessing.cpp libraries/common.cpp libraries/stack.cpp libraries/stack_common.cpp BACKEND/backend.cpp BACKEND/main.cpp
	clang tree.cpp FRONTEND/parser.cpp FRONTEND/main.cpp libraries/FileProcessing.cpp libraries/common.cpp libraries/stack.cpp libraries/stack_common.cpp -fsanitize=address -g -o FRONT
	clang tree.cpp REVERSE_FRONTEND/reverse_frontend.cpp REVERSE_FRONTEND/main.cpp libraries/FileProcessing.cpp libraries/common.cpp libraries/stack.cpp libraries/stack_common.cpp -fsanitize=address -g -o BACK

frontend: tree.cpp FRONTEND/parser.cpp FRONTEND/main.cpp libraries/FileProcessing.cpp libraries/common.cpp libraries/stack.cpp libraries/stack_common.cpp
	clang tree.cpp FRONTEND/parser.cpp FRONTEND/main.cpp libraries/FileProcessing.cpp libraries/common.cpp libraries/stack.cpp libraries/stack_common.cpp -fsanitize=address -g -o FRONT

reverse_frontend: tree.cpp REVERSE_FRONTEND/reverse_frontend.cpp REVERSE_FRONTEND/main.cpp libraries/FileProcessing.cpp libraries/common.cpp libraries/stack.cpp libraries/stack_common.cpp
	clang tree.cpp REVERSE_FRONTEND/reverse_frontend.cpp REVERSE_FRONTEND/main.cpp libraries/FileProcessing.cpp libraries/common.cpp libraries/stack.cpp libraries/stack_common.cpp -fsanitize=address -g -o REVERSE

backend: tree.cpp BACKEND/backend.cpp BACKEND/main.cpp libraries/FileProcessing.cpp libraries/common.cpp libraries/stack.cpp libraries/stack_common.cpp 
	clang tree.cpp REVERSE_FRONTEND/reverse_frontend.cpp REVERSE_FRONTEND/main.cpp libraries/FileProcessing.cpp libraries/common.cpp libraries/stack.cpp libraries/stack_common.cpp -fsanitize=address -g -o REVERSE