#include <stdio.h>

int main()
{
    char path[123];

    char* system_path = "LLLL";
    snprintf(path, 123, "%s/share/sevenstars/sevenstars.ss", system_path);

    return 0;
}
