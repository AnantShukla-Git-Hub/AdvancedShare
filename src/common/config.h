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
//defining constant values - here port number and buffer size defined as 8080 and 1024 respectively now anywhere if likha hoga port ya buffer_size to ye values hi lega apne aap
#define PORT 8080
//buffer size--Ek baar me kitna data (bytes) hum read / write karenge (sender 1024 bytes me data bhejega and receiver 1024 bytes me data lega)
#define BUFFER_SIZE 1024
