#include <QtCore/QtCore>
#include <QtCore/QCoreApplication>
#include <Qt/qapplication.h>

#include "./webkit_core.h"

using namespace org::galaxycrawler::crawler::webkit;

int main(int argc, char ** argv) {
  QApplication a(argc, argv);

  WebkitCore * wc = new WebkitCore();

  QMap<QString, QString> http_header;
  QString text;

  http_header["User-Agent"] = "Chrome";
  http_header["Cookie"] = "Nice Cookie";
  wc->Get(QUrl("http://www.baidu.com"),
               3,
               20,
               false,
               http_header
               );
  text = wc->GetWebElement().toPlainText();
  qDebug() << text;

}

