TEMPLATE = subdirs

SUBDIRS = DataProvider \
          DataProvider/DataProviderTest \
          DataBinding \
          DataBinding/DataBindingTest \
          RequestResponseData \
          RequestResponseData/RequestResponseDataTest \
          DemoWidgetApp \
          DemoQmlApp \
          IntegrationTest

PRE_TARGETDEPS += RequestResponseData DataProvider DataBinding

RequestResponseData/RequestResponseDataTest.depends   = RequestResponseData
DataProvider.depends                  = RequestResponseData
DataBinding.depends                   = RequestResponseData
DataProvider/DataProviderTest.depends = DataProvider
DataBinding/DataBindingTest.depends   = DataBinding
DemoWidgetApp.depends                 = RequestResponseData DataProvider DataBinding
DemoQmlApp.depends                    = RequestResponseData DataProvider DataBinding
IntegrationTest.depends               = RequestResponseData DataProvider DataBinding

OTHER_FILES += doc/ClassDiagram.png \
               doc/ClassDiagram.uml \
               LICENSE.txt



