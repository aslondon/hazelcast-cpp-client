//
// Created by sancar koyunlu on 6/25/13.
// Copyright (c) 2013 hazelcast. All rights reserved.

#ifndef HAZELCAST_CollectionRequest
#define HAZELCAST_CollectionRequest

#include "hazelcast/client/impl/PortableRequest.h"
#include <string>

namespace hazelcast {
    namespace client {
        namespace collection {

            class HAZELCAST_API CollectionRequest : public impl::PortableRequest {
            public:
                CollectionRequest(const std::string &name, const std::string &serviceName);

                virtual int getFactoryId() const;

                virtual void write(serialization::PortableWriter &writer) const;

            private:
                std::string name;
                std::string serviceName;

            };
        }
    }
}


#endif //HAZELCAST_CollectionRequest
