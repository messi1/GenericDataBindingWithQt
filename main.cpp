// Qt includes
#include <QApplication>
#include <QDebug>
#include <QFile>
#include <QFont>
#include <QLineEdit>
#include <QObject>
#include <QPushButton>
#include <QStyleFactory>
#include <QToolTip>
#include <QTranslator>
#include <QWidget>
#include <QThread>

#include "DataProvider/DataProvider.h"
#include "DataProvider/DataProxy.h"
#include "RequestData/RequestCommand.h"
#include "RequestData/RequestData.h"
#include "RequestBroker/IConnector.h"

struct TestValues
{
  QStringList values1 = {"5","10","20",""};
  QStringList values2 = {"7","44","33",""};
  QStringList values3 = {"true", "false", "true"};
  QStringList values4 = {"false", "true", "false"};

  RequestCmdVector commandVector1 = { RequestCmd::WlanList,
                                      RequestCmd::WlanState,
                                      RequestCmd::EthState };

  RequestCmdVector commandVector2 = { RequestCmd::Language,
                                      RequestCmd::DateTime,
                                      RequestCmd::BatteryState };

};

class MockConnector final: public RequestBroker::IConnector
{
  public:
    bool requestData(const RequestData& requestData, RequestData& responseData) override
    {
        TestValues testData;
        responseData = requestData;

        if( responseData.requestCmdVector() == testData.commandVector1)
        {
          StringMatrix valueMatrix;
          valueMatrix.append(testData.values1);
          responseData.setValueMatrix(valueMatrix);
          return true;
        }

        return false;
    }
};



int main(int argc, char* argv[])
{
  QApplication app(argc, argv);

  app.font().setHintingPreference(QFont::PreferVerticalHinting);
  app.setDesktopSettingsAware(false);
  app.setStyle("Windows");
  app.setQuitOnLastWindowClosed(false);

  QWidget* widget = new QWidget;
    widget->setGeometry(0, 100, 400, 300);
    widget->show();
//  widget->showMaximized();
//  widget->showFullScreen();

  QPushButton *bla = new QPushButton(widget);
  bla->setGeometry(0, 0, 100, 40);
  bla->setText("BBBBBBBBBBBBBBBBBB");
  bla->setToolTip("BlaBla");
  bla->show();
  QLineEdit* el = new QLineEdit(widget);
  el->setGeometry(0, 100, 100, 40);
  el->setToolTip("Gugus");
  el->show();

  app.font().setHintingPreference(QFont::PreferVerticalHinting);
//    app.setDesktopSettingsAware(false);
//    app.setStyle("Windows");
  app.setQuitOnLastWindowClosed(true);

  TestValues testValues;
  QThread* dataThread = new QThread;
  dataThread->setObjectName("dataThread");
  MockConnector mockConnector;
  DataProvider* dataProvider  = new DataProvider(mockConnector);
  DataProxy* dataProxy1       = new DataProxy(dataProvider, nullptr);
  DataProxy* dataProxy2       = new DataProxy(dataProvider, nullptr);

  RequestData     requestData1;
  requestData1.setDataProxy(dataProxy1);
  requestData1.setRequestType(RequestType::GetValues);
  requestData1.setRequestCmdVector(testValues.commandVector1);

  RequestData     requestData2;
  requestData2.setDataProxy(dataProxy2);
  requestData2.setRequestType(RequestType::GetValues);
  requestData2.setRequestCmdVector(testValues.commandVector1);


  qWarning() << "Current Thread: " << QThread::currentThreadId();
  qWarning() << "Current WorkerThread: " << dataProvider->thread();

  dataProvider->moveToThread(dataThread);
  qWarning() << "New WorkerThread: " << dataProvider->thread();

  dataThread->start();
  dataProxy1->requestData(requestData1);
  dataProxy2->requestData(requestData2);

  return app.exec();
}

