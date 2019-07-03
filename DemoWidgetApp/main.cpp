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
#include <QMetaObject>

#include "DataProvider/DataProvider.h"
#include "DataProvider/DataProxy.h"
#include "RequestResponseData/RequestCommand.h"
#include "RequestResponseData/RequestData.h"
#include "RequestBroker/IConnector.h"

#include "DataClientManagers/BaseFrame.h"
#include "DataClients/DCLineEdit.h"

#include "RequestResponseData/RequestResponseDataTest/TestRequestValues.h"
#include "RequestResponseData/RequestResponseDataTest/TestResponseValues.h"

class MockConnector: public IConnector
{
  public:
    bool requestData(const RequestData& requestData, ResponseData& responseData) override
    {
        TestResponseValues testData;

        if( requestData.requestMap().keys() == testData.responseData1.responseMap().keys())
        {
          responseData.clearAllData();

          responseData.addResponse(testData.request1);
          responseData.addResponse(testData.request2, testData.valueList1);
          responseData.addResponse(testData.request3, testData.valueList2, testData.rangeList1);
          responseData.addResponse(testData.request4, testData.valueList3, testData.rangeList2, testData.errorList1);

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
  app.setQuitOnLastWindowClosed(true);

  MockConnector mockConnector;
  DataProvider dataProvider(mockConnector);
  DataProxy dataProxy(dataProvider, nullptr);

  QThread* dataThread = new QThread;
  dataThread->setObjectName("dataThread");
  dataProvider.moveToThread(dataThread);

  BaseFrame* baseWidget = new BaseFrame(dataProxy);
  baseWidget->setGeometry(0, 100, 400, 300);

  DCLineEdit* lineEdit = new DCLineEdit(*baseWidget);
  lineEdit->setPlaceholderText("Please enter ...");

  QPushButton *bla = new QPushButton(baseWidget);
  bla->setGeometry(0, 0, 100, 40);
  bla->setText("BBBBBBBBBBBBBBBBBB");
  bla->setToolTip("BlaBla");
  bla->show();
  QLineEdit* el = new QLineEdit(baseWidget);
  el->setGeometry(0, 100, 100, 40);
  el->setToolTip("Gugus");

  baseWidget->show();

  dataThread->start();

  return app.exec();
}

