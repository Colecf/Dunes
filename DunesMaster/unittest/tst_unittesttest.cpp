#include <QString>
#include <QtTest>
#define TESTING
#include "../Dunes/modules/downloadmodule.h"

class UnittestTest : public QObject
{
    Q_OBJECT

public:
    UnittestTest();

private Q_SLOTS:
    void testDownloadModuleGetCodeAndGetConfig();
};

UnittestTest::UnittestTest()
{
}

void UnittestTest::testDownloadModuleGetCodeAndGetConfig()
{
    DownloadModule* mod = new DownloadModule;
    mod->urlBox->setText("asdf");
    mod->inputTypeDropDown->setCurrentIndex(0);

    QString result("get_page(\"asdf\");\n");
    QCOMPARE(mod->getCode(), result);
}

QTEST_MAIN(UnittestTest)

#include "tst_unittesttest.moc"
