#ifndef RANDOM_H
#define RANDOM_H

long unsigned int strlenk(const char *s);
ssize_t my_read_random(struct file *file, char __user *buf, size_t nbytes, loff_t *offset);


#endif /* !RANDOM_H */
