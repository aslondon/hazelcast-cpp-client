//
// Created by sancar koyunlu on 9/12/13.
// Copyright (c) 2013 hazelcast. All rights reserved.




#ifndef HAZELCAST_CollectionRemoveRequest
#define HAZELCAST_CollectionRemoveRequest

#include "hazelcast/client/collection/CollectionRequest.h"
#include "hazelcast/client/serialization/Data.h"

namespace hazelcast {
    namespace client {
        namespace serialization {
            class Data;
        }
        namespace collection {
            class HAZELCAST_API CollectionRemoveRequest : public CollectionRequest {
            public:
                CollectionRemoveRequest(const std::string &name, const std::string &serviceName, const serialization::Data &data);

                int getClassId() const;

                void write(serialization::PortableWriter &writer) const;

            private:
                serialization::Data data;
            };
        }
    }
}

#endif //HAZELCAST_CollectionRemoveRequest
