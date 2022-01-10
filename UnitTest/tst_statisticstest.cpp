#include <QtTest>

// add necessary includes here
#include "../Game/statistics.hh"
#include "../CourseLib/interfaces/istatistics.hh"
#include <iostream>

class StatisticsTest : public QObject
{
    Q_OBJECT

public:
    StatisticsTest();
    ~StatisticsTest();

private slots:

    /**
     * @brief testBeer tests the behaviour of Statistics::beerDrunk()
     */
    void testBeer();

    /**
     * @brief testPulsu1Moves tests the behaviour of
     *        Statistics::pulsu1MoveTaken().
     */
    void testPulsu1Moves();

    /**
     * @brief testPulsu2Moves tests the behaviour of
     *        Statistics::pulsu2MoveTaken().
     */
    void testPulsu2Moves();
};

StatisticsTest::StatisticsTest()
{

}

StatisticsTest::~StatisticsTest()
{

}

void StatisticsTest::testBeer()
{
    Statistics s;
    QCOMPARE(s.howManyBeers(), 0u);
    s.beerDrunk();
    QCOMPARE(s.howManyBeers(), 1u);
    s.beerDrunk();
    QCOMPARE(s.howManyBeers(), 2u);
}

void StatisticsTest::testPulsu1Moves()
{
    Statistics s;
    QCOMPARE(s.howManyPulsu1Moves(), 0u);
    s.pulsu1MoveTaken();
    QCOMPARE(s.howManyPulsu1Moves(), 1u);
}

void StatisticsTest::testPulsu2Moves()
{
    Statistics s;
    QCOMPARE(s.howManyPulsu2Moves(), 0u);
    s.pulsu2MoveTaken();
    QCOMPARE(s.howManyPulsu2Moves(), 1u);
}

QTEST_APPLESS_MAIN(StatisticsTest)

#include "tst_statisticstest.moc"
