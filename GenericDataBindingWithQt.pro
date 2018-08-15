TEMPLATE       = subdirs

SUBDIRS = DataProvider \
          DataProvider/DataProviderTest \
          DataBinding \
          DataBinding/DataBindingTest \
          RequestData \
          RequestData/RequestDataTest \
          DemoApp.pro 

RequestData/RequestDataTest.depends   = RequestData
DataProvider.depends                  = RequestData
DataBinding.depends                   = RequestData
DataProvider/DataProviderTest.depends = DataProvider
DataBinding/DataBindingTest.depends   = DataBinding
DemoApp.pro.depends                   = RequestData DataProvider DataBinding


