//
// Created by sancar koyunlu on 5/3/13.
// Copyright (c) 2013 sancar koyunlu. All rights reserved.
//
// To change the template use AppCode | Preferences | File Templates.
//



#ifndef HAZELCAST_STRING_UTIL
#define HAZELCAST_STRING_UTIL

#include <iostream>


namespace hazelcast {
    namespace client {
        namespace util {
            class StringUtil {
            public:

                static std::string to_string(int);
            };
        }
    }
}


#endif //HAZELCAST_STRING_UTIL