#ifndef APPLICATION_HEADERS_RETARGET_H_
#define APPLICATION_HEADERS_RETARGET_H_

int _write (int fd, char *ptr, int len);
int _read (int fd, char *ptr, int len);
void _ttywrch(int ch);

#endif /* APPLICATION_HEADERS_RETARGET_H_ */
