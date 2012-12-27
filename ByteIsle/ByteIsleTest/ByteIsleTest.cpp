#include "tinytest.h"
#include "../ByteIsle.h"

struct RemoverTester {
	static int testFindFirstInterval() {
		IntervalRemover remover;
		remover.add(3, 4);
		remover.add(6, 6);
		TINYTEST_ASSERT(remover.findFirstIntervalToTheRight(2) == 3);
		TINYTEST_ASSERT(remover.findFirstIntervalToTheRight(3) == 3);
		TINYTEST_ASSERT(remover.findFirstIntervalToTheRight(4) == 3);
		TINYTEST_ASSERT(remover.findFirstIntervalToTheRight(5) == 6);
		TINYTEST_ASSERT(remover.findFirstIntervalToTheRight(6) == 6);
		TINYTEST_ASSERT(remover.findFirstIntervalToTheRight(7) == -1);
		return 1;
	}

	static int testFindLastInterval() {
		IntervalRemover remover;
		remover.add(3, 4);
		remover.add(6, 6);
		TINYTEST_ASSERT(remover.findFistIntervalToTheLeft(2) == -1);
		TINYTEST_ASSERT(remover.findFistIntervalToTheLeft(3) == 4);
		TINYTEST_ASSERT(remover.findFistIntervalToTheLeft(4) == 4);
		TINYTEST_ASSERT(remover.findFistIntervalToTheLeft(5) == 4);
		TINYTEST_ASSERT(remover.findFistIntervalToTheLeft(6) == 6);
		TINYTEST_ASSERT(remover.findFistIntervalToTheLeft(7) == 6);
		return 1;
	}

	static int testGetNumberOfPoints() {
		IntervalRemover remover;
		remover.add(3, 4);
		remover.add(6, 6);
		TINYTEST_ASSERT(remover.getNumberOfPoinst(remover.begins.find(3), remover.begins.find(6)) == 2);
		TINYTEST_ASSERT(remover.getNumberOfPoinst(remover.begins.find(6), remover.begins.end()) == 1);
		TINYTEST_ASSERT(remover.getNumberOfPoinst(remover.begins.find(3), remover.begins.end()) == 3);
		return 1;

	}

	static int testIntervalRemoving() {
		IntervalRemover remover;
		remover.add(3, 4);
		remover.add(6, 6);
		TINYTEST_ASSERT(remover.removeIntervals(5, 9, 2) == 1); // 1 point removed
		TINYTEST_ASSERT(remover.size() == 1);
		TINYTEST_ASSERT(remover.getInterval(3) == 4);

		remover.clear();
		remover.add(3, 4);
		remover.add(6, 6);
		TINYTEST_ASSERT(remover.removeIntervals(4, 9, 2) == 2); // 1 point removed
		TINYTEST_ASSERT(remover.size() == 1);
		TINYTEST_ASSERT(remover.getInterval(3) == 3);

		remover.clear();
		remover.add(3, 4);
		remover.add(6, 6);
		TINYTEST_ASSERT(remover.removeIntervals(4, 9, 1) == 0);
		TINYTEST_ASSERT(remover.size() == 2);
		TINYTEST_ASSERT(remover.getInterval(3) == 4);
		TINYTEST_ASSERT(remover.getInterval(6) == 6);

		remover.clear();
		remover.add(3, 4);
		remover.add(6, 6);
		TINYTEST_ASSERT(remover.removeIntervals(1, 10, 5) == 3);
		TINYTEST_ASSERT(remover.size() == 0);

		remover.clear();
		TINYTEST_ASSERT(remover.removeIntervals(1, 10, 5) == 0);
		TINYTEST_ASSERT(remover.size() == 0);

		return 1;
	}
};

int Test1()
{
	if (!RemoverTester::testFindFirstInterval()) return 0;
	if (!RemoverTester::testFindLastInterval()) return 0;
	if (!RemoverTester::testGetNumberOfPoints()) return 0;
	if (!RemoverTester::testIntervalRemoving()) return 0;
	return 1;

}

TINYTEST_START_SUITE(SimpleSuite);
	TINYTEST_ADD_TEST(Test1);
TINYTEST_END_SUITE();

TINYTEST_MAIN_SINGLE_SUITE(SimpleSuite);