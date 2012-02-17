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

#ifndef WEBKIT_CORE_NETWORK_ACCESS_MANAGER_H
#define WEBKIT_CORE_NETWORK_ACCESS_MANAGER_H

#include <QtNetwork/QNetworkAccessManager>
#include <QtNetwork/QNetworkRequest>
#include <QtNetwork/QNetworkReply>
#include <QtCore/QString>
#include <QtCore/QDebug>
#include <QtCore/QList>

namespace org { namespace galaxycrawler { namespace crawler { namespace webkit {

class WebkitCoreNetworkAccessManager : public QNetworkAccessManager {
public:

  /// @brief 默认构造函数
  WebkitCoreNetworkAccessManager();

  /// @brief 设置http header, 仅对设置项进行修改，可以设置Cookie
  /// @param[in] http_header Example: http_header["Referer"] = "www.example.com"
  void SetHttpHeader(const QMap<QString, QString> & http_header);

protected:
  /// @brief 继承自QNetworkAccessManager，在发送Http请求前，拦截或者修改请求行为
  virtual QNetworkReply *createRequest(Operation op, const QNetworkRequest & req, QIODevice * outgoingData = 0);

private:
  /// 拒绝访问的URL列表
  QList<QString> refuse_url_list_;

  /// 用户设置的http_header
  QMap<QString, QString> http_header_;
};

} } } }  ///< end of namespace

#endif

