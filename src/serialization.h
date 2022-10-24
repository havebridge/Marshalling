#pragma once

#include "hashtable/test/test.h"
#include "serialization/test/testPrimitive.h"
#include "serialization/test/testString.h"
#include "serialization/test/testObject.h"
#include "serialization/test/testObject.h"
#include "serialization/test/HashtableSerialize.h"


#include "serialization/core.h"

#define DEBUG 1
#define RELEASE 0

#if DEBUG

#define TEST_PUT 0
#define TEST_REMOVE 0
#define TEST_GET 0
#define TEST_PRINT 0
#define TEST_HASH 0
#define TEST_SERIALIZE 0
#define TEST_DESERIALIZE 1

#endif