#include <linux/module.h>
#include <linux/printk.h>
#include <linux/random.h>
#include <linux/string.h>
#include <linux/uaccess.h>
#include <linux/errno.h>
#define BLOCK_SIZE_RANDOM 1000

// Define alphabet parameters
static char *alphabet = NULL;
module_param(alphabet, charp, S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP);
MODULE_PARM_DESC(alphabet, "alphabet of the random world");

// Return the len of the string s
long unsigned int strlenk(const char *s)
{
    unsigned int i = 0;
    for (; s[i] != '\0'; ++i);
    return i--;
}

// Put random bytes into user buffer
// Return : The number of bytes we have read
ssize_t level3(char __user *buf, size_t nbytes) {

    // Create random buffer and some variable
    unsigned char random[BLOCK_SIZE_RANDOM];
    int min, errno, byte_read;

    // If there is no bytes
    if (nbytes == 0)
        return 0;

    errno = 0;
    byte_read = 0;
    // As long as there are bytes to get
    while (nbytes) {
        // Get the random bytes
        get_random_bytes(&random, sizeof(random));

        // Get max of that there are still left to print
        min = nbytes < BLOCK_SIZE_RANDOM ? nbytes : BLOCK_SIZE_RANDOM;
        // Pass to user space
        if (copy_to_user(buf, random, min)) {
            errno = -EFAULT;
            return errno;
        }

        // Actualize variable
        nbytes -= min;
        buf += min;
        byte_read += min;
    }
    // The number of bytes we have read
    return byte_read;
}

// Put random bytes into user buffer
// Return : The number of bytes we have read
ssize_t level4(char __user *buf, size_t nbytes, long unsigned int len) {
    // Create random buffer of 1 and some variable
    unsigned char random[1];
    int errno, byte_read;

    // If there is no bytes
    if ((nbytes == 0 || len == 0))
        return 0;

    errno = 0;
    byte_read = 0;

    // As long as there are bytes to get
    while (nbytes) {

        // Get the random bytes
        get_random_bytes(&random, sizeof(random));

        // Put the random bytes corresponding in the alphabet in user space
        put_user(alphabet[random[0] % len], buf++);

        // Actualize variable
        nbytes--;
        byte_read++;
    }
    // The number of bytes we have read
    return byte_read;
}

// Take into account the alphabet parameter
// Return : The number of bytes we have read
ssize_t my_read_random(struct file *file, char __user *buf, size_t nbytes, loff_t *offset)
{
    if (alphabet != NULL)
        return level4(buf, nbytes, strlenk(alphabet));
    return level3(buf, nbytes);
}

MODULE_LICENSE("Random");
MODULE_DESCRIPTION("Random module");
MODULE_AUTHOR("Clara CHALUMEAU");
