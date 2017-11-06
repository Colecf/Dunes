#include <QString>
#include <QtTest>

class UnittestTest : public QObject
{
    Q_OBJECT

public:
    UnittestTest();

private Q_SLOTS:
    void testCase1();
};

UnittestTest::UnittestTest()
{
}

void UnittestTest::testCase1()
{
    QVERIFY2(true, "Failure");
}

QTEST_APPLESS_MAIN(UnittestTest)

#include "tst_unittesttest.moc"
