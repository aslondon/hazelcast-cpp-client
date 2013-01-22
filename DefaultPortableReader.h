//
//  DefaultPortableReader.h
//  Server
//
//  Created by sancar koyunlu on 1/10/13.
//  Copyright (c) 2013 sancar koyunlu. All rights reserved.
//

#ifndef __Server__DefaultPortableReader__
#define __Server__DefaultPortableReader__

#include <iostream>
#include <string>
#include <memory>
#include "Array.h"
#include "PortableReader.h"
class Portable;
class PortableSerializer;
class BufferObjectDataInput;
class FieldDefinitionImpl;
class ContextAwareDataInput;
class ClassDefinitionImpl;

typedef unsigned char byte;

using namespace std;

class DefaultPortableReader : public PortableReader {
public:
    DefaultPortableReader(PortableSerializer*, ContextAwareDataInput&, ClassDefinitionImpl*);
    
    int readInt(string) throw(ios_base::failure);
    
    long readLong(string) throw(ios_base::failure);
    
    bool readBoolean(string) throw(ios_base::failure);
    
    byte readByte(string) throw(ios_base::failure);
    
    char readChar(string) throw(ios_base::failure);
    
    double readDouble(string) throw(ios_base::failure);
    
    float readFloat(string) throw(ios_base::failure);
    
    short readShort(string) throw(ios_base::failure);
    
    string readUTF(string) throw(ios_base::failure);
    
    auto_ptr<Portable> readPortable(string) throw(ios_base::failure) ;
    
    Array<byte> readByteArray(string) throw(ios_base::failure);
    
    Array<char> readCharArray(string) throw(ios_base::failure);
    
    Array<int> readIntArray(string) throw(ios_base::failure);
    
    Array<long> readLongArray(string) throw(ios_base::failure);
    
    Array<double> readDoubleArray(string) throw(ios_base::failure);
    
    Array<float> readFloatArray(string) throw(ios_base::failure);
    
    Array<short> readShortArray(string) throw(ios_base::failure);
    
    Array< auto_ptr<Portable> > readPortableArray(string) throw(ios_base::failure);

protected:
    int getPosition(string) throw(ios_base::failure);

    int getPosition(FieldDefinitionImpl*) throw(ios_base::failure);
    
    PortableSerializer* serializer;//TODO
    ClassDefinitionImpl* cd;
    ContextAwareDataInput* input;
    int offset;
    
};


#endif /* defined(__Server__DefaultPortableReader__) */
