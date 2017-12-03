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
    mod->inputTypeDropDown->setCurrentIndex(0);
    mod->urlBox->setText("asdf");

    QString result("get_page(\"asdf\");\n");
    QCOMPARE(mod->getCode(), result);

    mod->inputTypeDropDown->setCurrentIndex(1);
    result = QString("get_page(top());\n");
    QCOMPARE(mod->getCode(), result);

    mod->inputTypeDropDown->setCurrentIndex(2);
    mod->urlBox->setText("asdf");
    result = QString("get_page(\"asdf\");\n");
    QCOMPARE(mod->getCode(), result);

    mod->inputTypeDropDown->setCurrentIndex(0);
    mod->urlBox->setText("");
    result = COMPILE_ERROR;
    QCOMPARE(mod->getCode(), result);

    mod->inputTypeDropDown->setCurrentIndex(2);
    mod->urlBox->setText("");
    result = COMPILE_ERROR;
    QCOMPARE(mod->getCode(), result);
}

QTEST_MAIN(UnittestTest)

#include "tst_unittesttest.moc"
