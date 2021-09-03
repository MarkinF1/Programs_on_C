#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>

struct Node
{
    int32_t key;
    int32_t left_idx;
    int32_t right_idx;
};

func(int32_t root)
{
    if (root->right_idx) {
        func(root->right_idx);
    }
    printf("%d\n", root->key);
    if (root->left_idx) {
        func(root->left_idx);
    }
}

int
main(int argc, char *argv[])
{
    
}
