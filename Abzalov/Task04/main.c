#include <stdio.h>

void other() {
    printf("Congratulations!\n");
    printf("You have entered in the secret function!\n");
}

void input() {
    char buffer[20];

    printf("Enter some text:\n");
    if (scanf("%s", buffer) == 1){};
    printf("You entered: %s\n", buffer);
}

int main() {
    input();
    return 0;
}
