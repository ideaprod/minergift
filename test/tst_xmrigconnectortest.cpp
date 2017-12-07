#include <QtTest>
#include <QCoreApplication>

#include "minerapi.h"

class XmrigConnectorTest : public QObject
{
    Q_OBJECT

public:
    XmrigConnectorTest();
    ~XmrigConnectorTest();

private slots:
    void initTestCase();
    void cleanupTestCase();
    void test_start_ok();
    void test_start_ko();
};

XmrigConnectorTest::XmrigConnectorTest()
{

}

XmrigConnectorTest::~XmrigConnectorTest()
{

}

void XmrigConnectorTest::initTestCase()
{

}

void XmrigConnectorTest::cleanupTestCase()
{

}

void XmrigConnectorTest::test_start_ok()
{
    qDebug() << "test_start_ok";
}

void XmrigConnectorTest::test_start_ko()
{
    qDebug() << "test_start_ko";
}


QTEST_MAIN(XmrigConnectorTest)

#include "tst_xmrigconnectortest.moc"
