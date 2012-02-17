/**
 * @Copyright 2012 GalaxyCrawler.
 * @file      crawler/webkit/webkit_core_web_page.h
 * @namespace org::galaxycrawler::crawler::webkit
 * @version   1.0
 * @author    Chuck
 * @date      2012-02-16
 * @brief     这个类继承自QWebPage，用来更改默认UserAgent，以及禁用JavaScript弹窗。
 * Change Log:
 */

#ifndef WEBKIT_CORE_WEB_PAGE_H
#define WEBKIT_CORE_WEB_PAGE_H

#include <QtWebKit/QWebPage>
#include <QtCore/QString>
#include <QtCore/QObject>
#include <QtCore/QDebug>
#include <QtCore/QList>
#include <QtCore/QTime>

namespace org { namespace galaxycrawler { namespace crawler { namespace webkit {

class WebkitCoreWebPage : public QWebPage {
 public:

  /// @brief 默认构造函数, 调用父类构造函数，以及设置默认UserAgent
  WebkitCoreWebPage();

  /// @brief 添加一条UserAgent，不再使用默认UserAgent，可多次调用，多条UserAgent将会随机被使用
  /// @param useragent useragent字符串
  void AddUserAgent(const QString & useragent);

  // @brief 清除用户自己添加的UserAgent，将恢复使用默认UserAgent
  void ClearUserAgent();

 protected:
  /// @brief 重写，使之能够变换UserAgent, 
  /// @param url webkit内部即将访问的url
  /// @return 即将访问的url所使用的UserAgent, 将被webkit内核所使用
  virtual QString userAgentForUrl(const QUrl & url) const;

  /// @brief 以下三个成员函数用来继承原始的Webkit浏览器JavaScript弹窗行为，
  ///        使之不进行任何弹窗操作。防止浏览器线程被阻塞。
  virtual void javaScriptAlert(QWebFrame *originatingFrame, const QString &msg);
  virtual bool javaScriptConfirm(QWebFrame *originatingFrame, const QString &msg);
  virtual bool javaScriptPrompt(QWebFrame *originatingFrame, const QString &msg, const QString &defaultValue, QString *result);

 private:
  /// 默认的UserAgent
  QString default_user_agent_;

  /// 用户添加的UserAgent列表;
  QList<QString> user_agent_list_;
};

} } } }  ///< end of namespace

#endif

