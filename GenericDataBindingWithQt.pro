TEMPLATE = subdirs

SUBDIRS = DataProvider \
          DataProvider/DataProviderTest \
          DataBinding \
          DataBinding/DataBindingTest \
          RequestData \
          RequestData/RequestDataTest \
          DemoWidgetApp \
          DemoQmlApp \
          IntegrationTest

PRE_TARGETDEPS += RequestData DataProvider DataBinding

RequestData/RequestDataTest.depends   = RequestData
DataProvider.depends                  = RequestData
DataBinding.depends                   = RequestData
DataProvider/DataProviderTest.depends = DataProvider
DataBinding/DataBindingTest.depends   = DataBinding
DemoWidgetApp.depends                 = RequestData DataProvider DataBinding
DemoQmlApp.depends                    = RequestData DataProvider DataBinding
IntegrationTest.depends               = RequestData DataProvider DataBinding

OTHER_FILES += doc/ClassDiagram.png \
               doc/ClassDiagram.uml \
               LICENSE.txt



