#include "serialization.h"


int main(int argc, char** argv)
{
	(void)argc;
	(void)argv;
	
	TestFrame::testPrimitive();
	TestFrame::testString();
	TestFrame::testObject();

	return 0;
}
