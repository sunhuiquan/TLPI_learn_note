#include <tlpi_hdr.h>
#include <wait.h>
#include <assert.h>

int main()
{
    pid_t pid = vfork();
    switch (pid)
    {
    case -1:
        errExit("vfork");

    case 0:
        if (close(STDIN_FILENO) == -1)
            errExit("close");
        assert(write(STDIN_FILENO, "c\n", 2) == -1);
        _exit(EXIT_SUCCESS);

    default:
        if (write(STDIN_FILENO, "p\n", 2) != 2)
            errExit("write");
        exit(EXIT_SUCCESS);
    }
}