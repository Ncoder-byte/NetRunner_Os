#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main() {
    pid_t pid = fork();  // Create child process

    if (pid < 0) {
        perror("fork failed");
        exit(1);
    }

    if (pid == 0) {
        // Child process
        printf("Child process is running (PID: %d)\n", getpid());
        sleep(2);  // Simulate some work
        printf("Child process is done.\n");
        exit(42);  // Child exits with status 42
    } else {
        // Parent process
        int status;
        pid_t waited_pid = wait(&status);  // Wait for child to finish

        if (waited_pid == -1) {
            perror("wait failed");
            exit(1);
        }

        printf("Parent: Child process %d has finished.\n", waited_pid);

        if (WIFEXITED(status)) {
            printf("Parent: Child exited with status %d\n", WEXITSTATUS(status));
        } else {
            printf("Parent: Child did not exit normally.\n");
        }
    }

    return 0;
}
