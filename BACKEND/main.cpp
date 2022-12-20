#include "backend.h"

int main ()
{
    setlocale (LC_ALL, "ru_RU.cp1251");
    char name_file_language[MAX_LEN_STR] = "language_tree.awp";

    struct Text buffer_language = {};
    struct FileInfo file_language = {.file_name = name_file_language};
    struct Tree tree = {.file_language = &file_language, .buffer_language = &buffer_language};

    tree_backend_ctor (&tree);
}