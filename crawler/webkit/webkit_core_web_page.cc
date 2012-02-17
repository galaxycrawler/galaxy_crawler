/**
 * @Copyright 2012 GalaxyCrawler.
 * @file      crawler/webkit/webkit_core_web_page.cc
 * @namespace org::galaxycrawler::crawler::webkit
 * @version   1.0
 * @author    Chuck
 * @date      2012-02-16
 * @brief     这个类继承自QWebPage，用来更改默认UserAgent，以及禁用JavaScript弹窗。
 * Change Log:
 */

#include "./webkit_core_web_page.h"

namespace org { namespace galaxycrawler { namespace crawler { namespace webkit {

WebkitCoreWebPage::WebkitCoreWebPage() {
  // 调用父类构造函数
  QWebPage();
  // 初始化随机种子
  QTime time = QTime::currentTime();
  qsrand(time.msec() + (time.second() * 1000));
  // 设置默认的UserAgent为假冒的Chrome浏览器
  this->default_user_agent_ = "Mozilla/5.0 (Windows NT 6.1; WOW64) AppleWebKit/535.7 (KHTML, like Gecko) Chrome/16.0.912.63 Safari/535.7";
}

void WebkitCoreWebPage::AddUserAgent(const QString & useragent) {
  this->user_agent_list_.append(useragent);
}

void WebkitCoreWebPage::ClearUserAgent() {
  this->user_agent_list_.clear();
}

// 重写，使之能够变换UserAgent
QString WebkitCoreWebPage::userAgentForUrl(const QUrl &url) const {
  if (this->user_agent_list_.size() == 0 || url.isEmpty() == true) {
    return this->default_user_agent_;
  }
  int rand_index = qrand() % this->user_agent_list_.size();
  return this->user_agent_list_[rand_index];
}

// 重写JavaScript对话框动作接口，避免webkit弹出窗口，阻断当前运行过程。
void WebkitCoreWebPage::javaScriptAlert(QWebFrame *originatingFrame, const QString &msg) {
  return;
}

bool WebkitCoreWebPage::javaScriptConfirm(QWebFrame *originatingFrame, const QString &msg) {
  return false;
}

bool WebkitCoreWebPage::javaScriptPrompt(QWebFrame *originatingFrame, const QString &msg, const QString &defaultValue, QString *result) {
  return false;
}

} } } }  ///< end of namespace

