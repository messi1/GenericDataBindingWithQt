#include <QGuiApplication>
#include <QQmlContext>
#include <QQmlEngine>
#include <QQuickView>
#include <QUrl>

#include "DCComponent.h"

int main(int argc, char* argv[])
{
  QGuiApplication app(argc, argv);
  app.setDesktopSettingsAware(false);
  app.setQuitOnLastWindowClosed(true);

  QQuickView view;

  view.setResizeMode(QQuickView::SizeRootObjectToView);

  QQmlContext *context = view.rootContext();

//  qmlRegisterType<DCComponent>("", 1, 9, "DCComponent");

  if(context)
  {

  }

  view.show();

   return app.exec();
}
