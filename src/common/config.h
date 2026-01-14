/*Pragma once--> avoid duplicate definion error
  (means ise define nahi karoge to config.h ko multiple file 
  like sender.cpp and receiver.cpp dono me add nahi
  kar sakte error aaega multiple definition error) 
  and #pragma preprocessor ke time par chalta hai
 
*Old version of pragma once is
 *#ifndef FILE_H
 *#define FILE_H
 *---code---
 *#endif
 */
#pragma once
//cstddef-->ye standard definitions provide karta hai jaise size_t type ke liye
#include <cstddef>
//defining constant values - here port number and buffer size defined as 8080 and 1024 respectively now anywhere if likha hoga port ya buffer_size to ye values hi lega apne aap
#define PORT 8080
#define CHUNK_SIZE (64 * 1024) //64KB
//#define RECEIVE_DIR "received"-->macro(constant) jo cpp me dev define karta hai jise hum use kar sakte hain
#define RECEIVE_DIR "recived"
//buffer size--Ek baar me kitna data (bytes) hum read / write karenge (sender 1024 bytes me data bhejega and receiver 1024 bytes me data lega)
#define BUFFER_SIZE 1024
