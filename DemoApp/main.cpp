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

#include "DataClientManagers/BaseFrame.h"

struct TestValues
{
  QStringList values1 = {"5","10","20",""};
  QStringList values2 = {"7","44","33",""};
  QStringList values3 = {"true", "false", "true"};
  QStringList values4 = {"false", "true", "false"};

  RequestVector commandVector1 = { {RequestCmd::WlanList},
                                   {RequestCmd::WlanState},
                                   {RequestCmd::EthState} };

  RequestVector commandVector2 = { {RequestCmd::Language},
                                   {RequestCmd::DateTime},
                                   {RequestCmd::BatteryState} };

};

class MockConnector final: public RequestBroker::IConnector
{
  public:
    bool requestData(const RequestData& requestData, RequestData& responseData) override
    {
        TestValues testData;
        responseData = requestData;

        if( responseData.requestVector() == testData.commandVector1)
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

  MockConnector mockConnector;
  DataProvider dataProvider(mockConnector);
  DataProxy dataProxy(dataProvider, nullptr);

  QThread* dataThread = new QThread;
  dataThread->setObjectName("dataThread");
  dataProvider.moveToThread(dataThread);

  BaseFrame* widget = new BaseFrame(dataProxy);
  widget->setGeometry(0, 100, 400, 300);

  QPushButton *bla = new QPushButton(widget);
  bla->setGeometry(0, 0, 100, 40);
  bla->setText("BBBBBBBBBBBBBBBBBB");
  bla->setToolTip("BlaBla");
  bla->show();
  QLineEdit* el = new QLineEdit(widget);
  el->setGeometry(0, 100, 100, 40);
  el->setToolTip("Gugus");

  widget->show();

  dataThread->start();

  return app.exec();
}

