/*************************************************************************
	> File Name: macro.h
	> Author: kwb
	> Mail: 
	> Created Time: Mon 21 Mar 2022 09:01:23 PM CST
 ************************************************************************/

#ifndef _MACRO_H
#define _MACRO_H

#include "color.h"
/* 宏定义：自动定义 set 和 get 方法; 变量名加了一个 下划线 
 * ##：将两个字符串连接；如果不用 ##，将视为普通变量
 */
#define GETSETVAR(type, name) \
        private: \
            type name##_; \
        public: \
            const type& name() const {\
                return name##_;\
            } \
            void set_##name(const type& val) { \
                name##_ = val; \
            }

#define GETSETSTR(size, name) \
        private:\
            char name##_[size];\
        public:\
            const char* name() const {\
                return name##_;\
            }\
            void set_##name(const char* val) {\
                strncpy(name##_, val, size);\
            }

#define _SERVER
#define _REACTOR

#ifdef _SERVER
#define SERVER(fmt, args...) printf(fmt, ##args)
#else
#define SERVER(fmt, args...)
#endif
#ifdef _REACTOR
#define REACTOR(fmt, args...) printf(fmt, ##args)
#else
#define REACTOR(fmt, args...)
#endif


#endif
