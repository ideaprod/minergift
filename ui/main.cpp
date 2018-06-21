#include <QApplication>
#include <QLabel>
#include <QDebug>
#include <QCommandLineParser>
#include <QCommandLineOption>
#include "mainwindow.h"

int main(int argc, char **argv)
{
    QApplication application(argc, argv);
    QCommandLineParser parser;
    application.setApplicationVersion(PRODUCT_VERSION);
    application.setApplicationDisplayName(PRODUCT_DISPLAY_NAME);
    application.setApplicationName(PRODUCT_NAME);

    parser.setApplicationDescription(PRODUCT_DESCRIPTION);
    parser.addHelpOption();
    parser.addVersionOption();

    // A boolean option for running it via GUI (--bg)
    QCommandLineOption guiOption(QStringList() << "bg", "Running in background.");
    parser.addOption(guiOption);

    // Prevent the app to close when trayed
    QApplication::setQuitOnLastWindowClosed(false);

    // Process the actual command line arguments given by the user
    parser.process(application);

    MainWindow w;
    if (!parser.isSet(guiOption))
    {
        w.hide();
    }
    else
    {
        qDebug() << "Running in headless mode";
    }

    return application.exec();
}
