/*
 * Copyright (c) 2008-2018, Hazelcast, Inc. All Rights Reserved.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#ifndef HAZELCAST_UTIL_EXCEPTIONUTIL_H_
#define HAZELCAST_UTIL_EXCEPTIONUTIL_H_

#include "hazelcast/client/exception/IException.h"
#include "hazelcast/util/HazelcastDll.h"

#if  defined(WIN32) || defined(_WIN32) || defined(WIN64) || defined(_WIN64)
#pragma warning(push)
#pragma warning(disable: 4251) //for dll export
#endif

namespace hazelcast {
    namespace util {
        class HAZELCAST_API ExceptionUtil {
        public:
            /**
             * Interface used by rethrow/peel to wrap the peeled exception
             */
            class RuntimeExceptionFactory {
            public:
                virtual ~RuntimeExceptionFactory();

                virtual void rethrow(const client::exception::IException &throwable, const std::string &message) = 0;
            };

            static void rethrow(const client::exception::IException &e);

            static void rethrow(const client::exception::IException &e,
                                                          const boost::shared_ptr<RuntimeExceptionFactory> &runtimeExceptionFactory);

        private:
            class HazelcastExceptionFactory : public RuntimeExceptionFactory {
                virtual void rethrow(const client::exception::IException &throwable, const std::string &message);
            };

            static const boost::shared_ptr<RuntimeExceptionFactory> &HAZELCAST_EXCEPTION_FACTORY();

            static const boost::shared_ptr<RuntimeExceptionFactory> hazelcastExceptionFactory;
        };
    }
}

#if  defined(WIN32) || defined(_WIN32) || defined(WIN64) || defined(_WIN64)
#pragma warning(pop)
#endif

#endif //HAZELCAST_UTIL_EXCEPTIONUTIL_H_
