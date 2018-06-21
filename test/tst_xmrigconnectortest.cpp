#include <QtTest>
#include <QCoreApplication>

#include "XmrigConnector/XmrigConnector.h"

class XmrigConnectorTest : public QObject
{
    Q_OBJECT

public:
    XmrigConnectorTest();
    ~XmrigConnectorTest();

private:
    XmrigConnector *xmc;

private slots:
    void initTestCase();
    void cleanupTestCase();
    void init();
    void cleanup();
    void test_start_initialStartOk();
    void test_start_secondStartKo();
    void test_stop_initialStopOk();
    void test_stop_stopAfterStartOk();
    void test_stop_secondStopOk();
    void test_getStatus_initial();
    void test_getStatus_started();
    void test_getStatus_stopped();
};

XmrigConnectorTest::XmrigConnectorTest()
{
}

XmrigConnectorTest::~XmrigConnectorTest()
{
}

void XmrigConnectorTest::initTestCase()
{
    // will be called before the first test function is executed.
}

void XmrigConnectorTest::cleanupTestCase()
{
    // will be called after the last test function was executed.
}

void XmrigConnectorTest::init()
{
    // will be called before each test function is executed.
    xmc = new XmrigConnector();
}

void XmrigConnectorTest::cleanup()
{
    // will be called after every test function.
    xmc->deleteLater();
}

void XmrigConnectorTest::test_start_initialStartOk()
{
    qDebug() << "test_start_initialStartOk";
    QCOMPARE(xmc->start(), 1);
}

void XmrigConnectorTest::test_start_secondStartKo()
{
    qDebug() << "test_start_secondStartKo";
    QCOMPARE(xmc->start(), 1);
    QCOMPARE(xmc->start(), 0);
}

void XmrigConnectorTest::test_stop_initialStopOk()
{
    qDebug() << "test_stop_initialStopOk";
    QCOMPARE(xmc->stop(), 1);
}

void XmrigConnectorTest::test_stop_stopAfterStartOk()
{
    qDebug() << "test_stop_stopAfterStartOk";
    QCOMPARE(xmc->start(), 1);
    QCOMPARE(xmc->stop(), 1);
}

void XmrigConnectorTest::test_stop_secondStopOk()
{
    qDebug() << "test_stop_secondStopOk";
    QCOMPARE(xmc->start(), 1);
    QCOMPARE(xmc->stop(), 1);
    QCOMPARE(xmc->stop(), 1);
}

void XmrigConnectorTest::test_getStatus_initial()
{
    qDebug() << "test_getStatus_initial";
    QCOMPARE(xmc->getStatus(), MinerApi::MinerStatus::STOPPED);
}

void XmrigConnectorTest::test_getStatus_started()
{
    qDebug() << "test_getStatus_started";
    QCOMPARE(xmc->start(), 1);
    QCOMPARE(xmc->getStatus(), MinerApi::MinerStatus::STARTED);
}

void XmrigConnectorTest::test_getStatus_stopped()
{
    qDebug() << "test_getStatus_stopped";
    QCOMPARE(xmc->stop(), 1);
    QCOMPARE(xmc->getStatus(), MinerApi::MinerStatus::STOPPED);
}

QTEST_GUILESS_MAIN(XmrigConnectorTest)

#include "tst_xmrigconnectortest.moc"
