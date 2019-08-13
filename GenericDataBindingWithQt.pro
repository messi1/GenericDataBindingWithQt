TEMPLATE = subdirs

SUBDIRS = DataProvider \
          DataProviderTest \
          DataBinding \
          DataBindingTest \
          RequestResponseData \
          RequestResponseDataTest \
          DemoWidgetApp \
          DemoQmlApp \
          IntegrationTest

RequestResponseDataTest.subdir  = RequestResponseData/RequestResponseDataTest
DataProviderTest.subdir         = DataProvider/DataProviderTest
DataBindingTest.subdir          = DataBinding/DataBindingTest

DataProvider.depends            = RequestResponseData
DataBinding.depends             = RequestResponseData
RequestResponseDataTest.depends = RequestResponseData
DataProviderTest.depends        = DataProvider
DataBindingTest.depends         = DataBinding
DemoWidgetApp.depends           = RequestResponseData DataProvider DataBinding
DemoQmlApp.depends              = RequestResponseData DataProvider DataBinding
IntegrationTest.depends         = RequestResponseData DataProvider DataBinding

OTHER_FILES += doc/ClassDiagram.png \
               doc/ClassDiagram.uml \
               LICENSE.txt
