#include "mywebview.h"

MyWebView::MyWebView()
{
    this->page()->setNetworkAccessManager(new MyNetworkAccessManager);
}
