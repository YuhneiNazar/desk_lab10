#include "pch.h"
#include "CppUnitTest.h"
#include "../desk_lab10/desk_lab10.cpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTestlab10
{
	TEST_CLASS(UnitTestlab10)
	{
	public:
		
		TEST_METHOD(TestMethod1)
		{
            // Create a test file
            ofstream testFile("test.txt");
            testFile << "4 4\n0 1 1\n0 2 2\n0 3 3\n1 2 4\n";
            testFile.close();

            initGraph("test.txt");

            // Check the results
            Assert::AreEqual(4, vertices);
            Assert::AreEqual(4, edges);
            Assert::AreEqual(1, weightInt[0][1]);
            Assert::AreEqual(2, weightInt[0][2]);
            Assert::AreEqual(3, weightInt[0][3]);
            Assert::AreEqual(4, weightInt[1][2]);
		}

        TEST_METHOD(TestMethod2)
        {
            // Initialize the graph
            vertices = 4;
            edges = 4;
            weightInt.assign(vertices, vector<int>(vertices, 0));
            weight.assign(vertices, vector<string>(vertices, "oo"));
            for (int i = 0; i < vertices; ++i) {
                weight[i][i] = "0";
            }
            weightInt[0][1] = 1;
            weightInt[0][2] = 2;
            weightInt[0][3] = 3;
            weightInt[1][2] = 4;
            weight[0][1] = "1";
            weight[0][2] = "2";
            weight[0][3] = "3";
            weight[1][2] = "4";

            // Check the results
            string expectedOutput =
                "| v\\v | v 0| v 1| v 2| v 3|\n"
                "| v 0 |  0 |  1 |  2 |  3 |\n"
                "| v 1 | oo |  0 |  4 | oo |\n"
                "| v 2 | oo | oo |  0 | oo |\n"
                "| v 3 | oo | oo | oo |  0 |\n";
            Assert::AreEqual(expectedOutput, weightMatrixToString());
        }



	};
}
