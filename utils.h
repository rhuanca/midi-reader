/*
 * utils.h
 *
 *  Created on: Feb 7, 2014
 *      Author: renan
 */

#ifndef UTILS_H_
#define UTILS_H_

void print_byte_string(char byte);
char low_nibble(char byte);
char high_nibble(char byte);
short chars_to_int(char *buffer);
long chars_to_long(char *buffer);
long vql_to_long(char *buffer, int n);
int read_vql(char **buffer, char *vql);
void print_hex_chars(char *buffer, int n);
void print_as_string(char *buffer, int n);
char int_to_hex(int i);


#endif /* UTILS_H_ */
