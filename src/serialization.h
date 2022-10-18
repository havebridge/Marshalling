#pragma once

#include "hashtable/test/test.h"
#include "serialization/test/testPrimitive.h"
//#include "serialization/test/testArray.h"
#include "serialization/test/testString.h"
#include "serialization/test/testObject.h"
#include "serialization/test/testSerialize.h"

#include "serialization/core.h"

#define DEBUG 0
#define RELEASE 1

#if DEBUG

#define TEST_PUT 1
#define TEST_REMOVE 1
#define TEST_GET 0
#define TEST_PRINT 1 
#define TEST_HASH 0
#define TEST_SERIALIZE 1

#endif