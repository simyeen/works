/*
 Data Structure programming assignment.  The same address book program with hashing with chaining.

Will take a hash prime p, not too big, probably 17, for an easy test.

Give a function name_to_num().

Define the hash function hash(name)= name_to_num(name) mod p. 


The list of first three hundred primes:

{2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43, 47, 53, 59, 61, \
67, 71, 73, 79, 83, 89, 97, 101, 103, 107, 109, 113, 127, 131, 137, \
139, 149, 151, 157, 163, 167, 173, 179, 181, 191, 193, 197, 199, 211, \
223, 227, 229, 233, 239, 241, 251, 257, 263, 269, 271, 277, 281, 283, \
293, 307, 311, 313, 317, 331, 337, 347, 349, 353, 359, 367, 373, 379, \
383, 389, 397, 401, 409, 419, 421, 431, 433, 439, 443, 449, 457, 461, \
463, 467, 479, 487, 491, 499, 503, 509, 521, 523, 541, 547, 557, 563, \
569, 571, 577, 587, 593, 599, 601, 607, 613, 617, 619, 631, 641, 643, \
647, 653, 659, 661, 673, 677, 683, 691, 701, 709, 719, 727, 733, 739, \
743, 751, 757, 761, 769, 773, 787, 797, 809, 811, 821, 823, 827, 829, \
839, 853, 857, 859, 863, 877, 881, 883, 887, 907, 911, 919, 929, 937, \
941, 947, 953, 967, 971, 977, 983, 991, 997, 1009, 1013, 1019, 1021, \
1031, 1033, 1039, 1049, 1051, 1061, 1063, 1069, 1087, 1091, 1093, \
1097, 1103, 1109, 1117, 1123, 1129, 1151, 1153, 1163, 1171, 1181, \
1187, 1193, 1201, 1213, 1217, 1223, 1229, 1231, 1237, 1249, 1259, \
1277, 1279, 1283, 1289, 1291, 1297, 1301, 1303, 1307, 1319, 1321, \
1327, 1361, 1367, 1373, 1381, 1399, 1409, 1423, 1427, 1429, 1433, \
1439, 1447, 1451, 1453, 1459, 1471, 1481, 1483, 1487, 1489, 1493, \
1499, 1511, 1523, 1531, 1543, 1549, 1553, 1559, 1567, 1571, 1579, \
1583, 1597, 1601, 1607, 1609, 1613, 1619, 1621, 1627, 1637, 1657, \
1663, 1667, 1669, 1693, 1697, 1699, 1709, 1721, 1723, 1733, 1741, \
1747, 1753, 1759, 1777, 1783, 1787, 1789, 1801, 1811, 1823, 1831, \
1847, 1861, 1867, 1871, 1873, 1877, 1879, 1889, 1901, 1907, 1913, \
1931, 1933, 1949, 1951, 1973, 1979, 1987}

*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "backend-hash-open-addressing.h"

#define HASH_PRIME 17
#define STR_POOL_SIZE 1000


// Note that we still use only the first three letters for hashing.
// So "abc" and "abcdef" have the same hash value. 
int name_to_num(char *name)
{
  int x;

  x=name[0];
  x=x<<8;
  x=x+name[1];
  x=x<<8;
  return x+name[2];
}

int hash(char *name)
{
  return name_to_num(name)%HASH_PRIME;
}
/* "abc" and "bbb" have the same hash value.  So do abt and bbs. */ 


// memory pool for strings 
char str_pool[STR_POOL_SIZE];

// The first available position of str_pool[].
char *curr_pos=str_pool;

// The last position of str_pool[].
char *str_pool_end=str_pool+STR_POOL_SIZE-1;  // note the pointer arithmetic.

struct record {
  char *name_ptr;
  char *number_ptr;
};
  
// utility function declarations
int compare(char *key, char *p);
void print_data(char *);
  
// Hash table: an array of struct records.
struct record hash_table[HASH_PRIME];

// Initialize hash table so that the name_ptr's to be NULL.
// That is, an empty slot s is indicated by s.name_idx==NULL.
void init_hash_table()
{
  int i;
  
  for(i=0;i<HASH_PRIME;i++)
    hash_table[i].name_ptr=NULL; 
}

void init()
{
  init_hash_table();
}


// This function is used to write on the str_pool[].
// It returns NULL if overflow occurs. (strcpy() doesn't check overflow :)
// Otherwise returns the position of the string that just has been written.
// Also maintains curr_pos. 
char *write_str(char *str)
{

}

void roll_back(char *str)
{
  curr_pos = curr_pos - strlen(str) - 1;  // careful with pointer arithmetic
}

/**************************
IMPORTANT NOTE on add()
 1. Allow duplicate names.
 2. Use linear probing, h(K), h(K)+1, h(K)+2, ....
**************************/
void add(char *name, char *number)
{
  int hh;
  char *p;
  static int num_insertions=0;

  if(++num_insertions > HASH_PRIME)
    printf("Can't add; Address Book is full!\n");
  else {
    hh=hash(name);
    
    while(hash_table[hh].name_ptr!=NULL) // find the next empty slot
      hh=(hh+1)%HASH_PRIME;

    if ((p=write_str(name))==NULL) {
      printf("Can't add; The string pool is about to overflow!\n");
      return;
    }
    hash_table[hh].name_ptr=p;

    if ((p=write_str(number))==NULL) {
      printf("Can't add; The string pool is about to overflow!\n");
      roll_back(name); // ROLLBACK!!!
      hash_table[hh].name_ptr=NULL; 
      return;
    }
    hash_table[hh].number_ptr=p;
    
    printf("The name was successfully added!\n");
  }
}
  
/**************************
IMPORTANT NOTE on search()
For duplicate names, search() finds the first-added name.
Prints the number of comparisons.
**************************/
void search(char *name)  
{
  int hh=hash(name);
  char *p;
  int num_comparisons=0;
  
  //  printf("Couldn't find the name.\n");
  //  printf("%d key comparisons were made.\n", num_comparisons);
}


/* Just a wrapper of strcmp().
 Negative value if key is smaller.
​ 0​ if equal.
 Positive value if key is greater. */
int compare(char *key, char *p)
{
  return strcmp(key, p);  
}

void print_data(char *str)
{
  printf("%s", str);
}

