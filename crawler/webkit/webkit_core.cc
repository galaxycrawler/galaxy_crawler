/**
 * @Copyright 2012 GalaxyCrawler.
 * @file      crawler/webkit/webkit_core.cc
 * @namespace org::galaxycrawler::crawler::webkit
 * @version   1.0
 * @author    Chuck
 * @date      2012-02-16
 * @brief     这个类是你可以直接使用的webkit浏览器对象。
 * Change Log:
 */

#ifndef CPAGELOADER_CPP
#define CPAGELOADER_CPP

#include "webkit_core.h"

namespace org { namespace galaxycrawler { namespace crawler { namespace webkit {

// public:
WebkitCore::WebkitCore() : QObject(NULL) {
  this->webview_ = new QWebView(NULL);

  this->time_used_ = 0;

  this->url_ = "";

  this->wait_time_ = 20;

  this->disk_cache_ = new QNetworkDiskCache();

  this->timer_ = new QTimer();

  this->last_op_time_ = time(unsigned(NULL));

  this->is_download_success_ = false;

  this->is_show_window_ = false;

  this->last_clean_cache_time_ = time(unsigned(NULL));

  this->clean_cache_interval_ = 3600;

  // 绑定事件，完成页面加载，和超时。
  connect(webview_, SIGNAL(loadFinished(bool)), this, SLOT(Finished(bool)));
  connect(timer_, SIGNAL(timeout()), this, SLOT(CheckEventloop()));

  // 使用本地缓存，设置本地缓存路径
  QString cache_path = "./caches/cache";
  QDir dir;
  dir.mkpath(cache_path);
  this->disk_cache_->setCacheDirectory(cache_path);
  this->networkaccessmanager_.setCache(this->disk_cache_);

  // 给webview设置WebPage
  // 不加载图片
  this->webpage_.settings()->setAttribute(QWebSettings::AutoLoadImages, false);
  // 使用DNS缓存
  this->webpage_.settings()->setAttribute(QWebSettings::DnsPrefetchEnabled, true);
  this->webview_->setPage(&(this->webpage_));
  this->webview_->page()->setLinkDelegationPolicy(QWebPage::DelegateAllLinks);

  // 给webview设置NetworkAccessManager
  this->webview_->page()->setNetworkAccessManager((QNetworkAccessManager*)(&(this->networkaccessmanager_)));

  // 设置窗口大小
  // this->webview_->setGeometry(0, 0, 1024, 768);
}

WebkitCore::~WebkitCore() {
  delete this->webview_;
  delete this->timer_;
  delete this->disk_cache_;
}

void WebkitCore::Get(const QUrl url,
                     int retry_times,
                     int wait_time,
                     bool is_load_image,
                     QMap<QString, QString> http_header) {
  // 遍历重试次数
  for (int rt = 0; rt < retry_times; rt++) {

    // 设置下载操作的时间
    this->last_op_time_ = time(unsigned(NULL));

    // 直接返回空的请求
    if (url.toString() == "about:blank" ||
        url.toString() == "http://about:blank" ||
        url.toString() == "http://") {
      return;
    }

    // 跳出上次的加载操作
    while (this->eventloop_.isRunning() == true) {
      this->webview_->page()->triggerAction(QWebPage::Stop);
      this->webview_->page()->triggerAction(QWebPage::StopScheduledPageRefresh);
      this->eventloop_.exit();
    }
    while (this->timer_->isActive() == true) {
      this->timer_->stop();
    }

    // 设置默认下载为成功状态，如果超时会在超时函数里设置为false
    this->is_download_success_ = true;

    // 记录本次下载的URL
    this->url_ = url;

    // 设置超时时间
    this->wait_time_ = wait_time;

    // 检查缓存，看是否需要清理
    this->CheckCache();

    // 定时器和计时器
    this->timer_->start(this->wait_time_ * 1000);
    this->elapsed_timer_.restart();

    // 创建Request，用于加载页面，并附加http header
    if (http_header.size() > 0) {
      QMap<QString, QString>::const_iterator hhit = http_header.find("User-Agent");
      if (hhit == http_header.end()) {
        hhit = http_header.find("user-agent");
      }
      if (hhit != http_header.end()) {
        this->webpage_.ClearUserAgent();
        this->webpage_.AddUserAgent(hhit.value());
      }
      this->networkaccessmanager_.SetHttpHeader(http_header);
    }

    // 加载页面
    qDebug() << "WebkitCore::Get() Loading Url: " << url.toString();
    this->webview_->load(this->url_);

    // 是否显示浏览器窗口
    if (true == this->is_show_window_) {
      this->webview_->show();
    }

    // 等待下载完成，或者下载超时
    qDebug() << "WebkitCore::Get() eventloop exec.";
    this->eventloop_.exec();
    qDebug() << "WebkitCore::Get() eventloop quit.";

    // 将相对URL转换为绝对URL
    this->AbsoluteUrl(this->webview_->page()->mainFrame()->documentElement(), this->webview_->url());

    // 下载失败，sleep 2秒，然后重试。
    if (this->is_download_success_ == false) {
      sleep(2);
      continue;
    } else {
      break;
    }
  }
}

void WebkitCore::EvaluateJavaScript(QString js) {
  if (js.trimmed() == "") {
    return;
  }
  // 定时器和计时器
  this->timer_->start(this->wait_time_ * 1000);
  this->elapsed_timer_.restart();

  QVariant result = this->webview_->page()->mainFrame()->evaluateJavaScript(js);
  // qDebug() << result.toString();

  this->eventloop_.exec();
  this->AbsoluteUrl(this->webview_->page()->mainFrame()->documentElement(), this->webview_->url());
}

QWebView * WebkitCore::GetWebView() {
  return this->webview_;
}

QWebElement WebkitCore::GetWebElement() {
  return this->webview_->page()->mainFrame()->documentElement();
}

bool WebkitCore::IsDownLoadSuccess() {
  return this->is_download_success_;
}

void WebkitCore::AbsoluteUrl(const QWebElement &parentElement, const QUrl & currentUrl) {
  QWebElement element = parentElement.firstChild();
  while (!element.isNull()) {
    // 将相对URL转换为绝对URL
    if (element.tagName() == "a" || element.tagName() == "A") {
      if (element.attribute("href").toLower().startsWith("http://") == false &&
          element.attribute("href").toLower().startsWith("javascript") == false) {
        QUrl relativeUrl(element.attribute("href"));
        if (relativeUrl.toString() != "") {
          QUrl absoluteUrl = currentUrl.resolved(relativeUrl);
          element.setAttribute("href", absoluteUrl.toString());
        }
      }
    }
    this->AbsoluteUrl(element, currentUrl);
    element = element.nextSibling();
  }
}

void WebkitCore::CheckCache() {
  // 当cache超时，清理缓存。
  if (time(unsigned(NULL)) - this->last_clean_cache_time_ >= this->clean_cache_interval_) {
    QString cachePath = this->disk_cache_->cacheDirectory() + "/http/";
    QDir dir;
    dir.setPath(cachePath);
    QStringList fileList = dir.entryList(QDir::Files);
    for (int i = 0; i < fileList.size(); i++) {
      dir.remove(cachePath + fileList[i]);
    }
    this->last_clean_cache_time_ = time(unsigned(NULL));
  }
  // 删除当前下载URL对应的本地缓存。
  this->disk_cache_->remove(this->url_);
}

// private slots:
void WebkitCore::Finished(bool b) {
  this->time_used_ = this->elapsed_timer_.elapsed();
  if (this->eventloop_.isRunning() == true) {
    this->eventloop_.quit();
  }
}

void WebkitCore::CheckEventloop() {
  int now_time = time(unsigned(NULL));
  if (now_time - this->last_op_time_ >= this->wait_time_) {
    if (this->eventloop_.isRunning() == true) {
      // qDebug() << "WebkitCore::CheckEventloop() eventloop exec for a long time, force quit.";
      this->eventloop_.quit();
      this->is_download_success_ = false;
      this->webview_->page()->triggerAction(QWebPage::Stop);
      this->webview_->page()->triggerAction(QWebPage::StopScheduledPageRefresh);
      this->Finished(false);
    }
  }
}



// ==================================================================

WebkitCore * WebkitCoreSingleton::m_pageloader = NULL;
int WebkitCoreSingleton::m_used_count = 0;
WebkitCore * WebkitCoreSingleton::GetInstance() {
  if (WebkitCoreSingleton::m_pageloader == NULL) {
    WebkitCoreSingleton::m_pageloader = new WebkitCore();
  }
  if (WebkitCoreSingleton::m_used_count++ > 10) {
    WebkitCoreSingleton::m_used_count = 0;
    delete WebkitCoreSingleton::m_pageloader;
    WebkitCoreSingleton::m_pageloader = new WebkitCore();
  }
  return WebkitCoreSingleton::m_pageloader;
}

} } } }  ///< end of namespace

#endif //CPAGELOADER_CPP

