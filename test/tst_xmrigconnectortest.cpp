#include <QtTest>
#include <QCoreApplication>

// add necessary includes here

class XmrigConnectorTest : public QObject
{
    Q_OBJECT

public:
    XmrigConnectorTest();
    ~XmrigConnectorTest();

private slots:
    void initTestCase();
    void cleanupTestCase();
    void test_case1();

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

void XmrigConnectorTest::test_case1()
{

}

QTEST_MAIN(XmrigConnectorTest)

#include "tst_xmrigconnectortest.moc"
