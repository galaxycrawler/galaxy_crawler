/**
 * @Copyright 2012 GalaxyCrawler.
 * @file      crawler/webkit/webkit_core_network_access_manager.h
 * @namespace org::galaxycrawler::crawler::webkit
 * @version   1.0
 * @author    Chuck
 * @date      2012-02-16
 * @brief     这个类继承自QNetworkAccessManager，可以用来控制浏览器访问URL的规则，比如禁止访问某些广告链接的URL。
 * Change Log:
 */

#include "webkit_core_network_access_manager.h"

namespace org { namespace galaxycrawler { namespace crawler { namespace webkit {

WebkitCoreNetworkAccessManager::WebkitCoreNetworkAccessManager() {
  QNetworkAccessManager();
  // 您可以在这里初始化this->refuse_url_list_ ，用来禁止访问某些URL。
}

void WebkitCoreNetworkAccessManager::SetHttpHeader(const QMap<QString, QString> & http_header) {
  this->http_header_.clear();
  this->http_header_ = http_header;
}

QNetworkReply * WebkitCoreNetworkAccessManager::createRequest(Operation op, const QNetworkRequest & req, QIODevice * outgoingData) {
  QString req_url = req.url().toString();
  // 查看是否为拒绝访问的URL
  for (int i = 0; i < this->refuse_url_list_.size(); i++) {
    if (req_url.indexOf(this->refuse_url_list_[i]) != -1) {
      QNetworkRequest invalidReq;
      invalidReq.setUrl(QUrl("about:blank"));
      qDebug() << "WebkitCoreNetworkAccessManager::createRequest() Found refuse url: " << req_url;
      return QNetworkAccessManager::createRequest(op, invalidReq, outgoingData);
    }
  }
  // Set Http Header, when this->http_header_.size() > 0
  if (this->http_header_.size() > 0) {
    QNetworkRequest req_2(req);
    for (QMap<QString, QString>::const_iterator it = this->http_header_.begin(); it != this->http_header_.end(); it++) {
      if (it.key() == "User-Agent") {
        continue;
      }
      req_2.setRawHeader(it.key().toAscii(), it.value().toAscii());
    }
    return QNetworkAccessManager::createRequest(op, req_2, outgoingData);
  }
  // 使用默认的request行为
  return QNetworkAccessManager::createRequest(op,req,outgoingData);
}

} } } }  ///< end of namespace

