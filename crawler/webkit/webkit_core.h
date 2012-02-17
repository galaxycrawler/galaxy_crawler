/**
 * @Copyright 2012 GalaxyCrawler.
 * @file      crawler/webkit/webkit_core.h
 * @namespace org::galaxycrawler::crawler::webkit
 * @version   1.0
 * @author    Chuck
 * @date      2012-02-16
 * @brief     这个类是你可以直接使用的webkit浏览器对象。
 * Change Log:
 */

#ifndef WEBKIT_CORE_H
#define WEBKIT_CORE_H

#include "webkit_core_web_page.h"
#include "webkit_core_network_access_manager.h"

#include <QtGui/QApplication>
#include <QtCore/QCoreApplication>
#include <QtCore/QElapsedTimer>
#include <QtCore/QEventLoop>
#include <QtCore/QObject>
#include <QtCore/QString>
#include <QtCore/QDebug>
#include <QtCore/QTimer>
#include <QtCore/QList>
#include <QtCore/QDir>
#include <QtWebKit/QWebView>
#include <QtWebKit/QWebPage>
#include <QtWebKit/QWebFrame>
#include <QtWebKit/QWebElement>
#include <QtNetwork/QNetworkProxy>
#include <QtNetwork/QNetworkRequest>
#include <QtNetwork/QNetworkAccessManager>
#include <QtNetwork/QNetworkDiskCache>

namespace org { namespace galaxycrawler { namespace crawler { namespace webkit {

class WebkitCore : public QObject {
 Q_OBJECT
 public:
  /// @brief 默认构造函数
  explicit WebkitCore();

  /// @brief 默认析构函数
  ~WebkitCore();

  /// @brief 执行Http Get请求加载页面
  /// @param 
  void Get(const QUrl url,
           int retry_times = 3,
           int wait_time = 20, /* wait 20 seconds */
           bool is_load_image = false,
           QMap<QString, QString> http_header = QMap<QString, QString>());

  /// @brief 执行JavaScript
  void EvaluateJavaScript(QString js); // 执行JavaScript代码

  /// 获取WebView对象
  QWebView * GetWebView();

  /// 获取Dom树的WebView对象
  QWebElement GetWebElement();

  /// 获取是否下载成功
  bool IsDownLoadSuccess();

 private:
  // 将相对URL转换为绝对URL
  void AbsoluteUrl(const QWebElement &parentElement, const QUrl & currentUrl);

  // 检查并清理缓存
  void CheckCache();

 private slots:
  // 页面载入完成。
  void Finished(bool b);

  // 检查eventloop状态
  void CheckEventloop();

 private:
  // webkit浏览器的窗体
  QWebView * webview_;

  // 载入页面所消耗的时间
  int time_used_;

  // 要载入的URL
  QUrl url_;

  // 事件循环，必须等待载入完成或者载入超时才退出
  QEventLoop eventloop_;

  // 载入超时的时间
  int wait_time_;

  // Network Disk Caching 本地缓存
  QNetworkDiskCache *disk_cache_;

  // webview使用的NetworkAccessManager，控制proxy和cache的加载。
  WebkitCoreNetworkAccessManager networkaccessmanager_;

  // 重载webpage，用来变换UserAgent, 以及控制加载图片和DNS缓存
  WebkitCoreWebPage webpage_;
  
  // 超时定时器
  QTimer *timer_;
 
  // 上次加载页面的时间,单位秒
  int last_op_time_;

  // 页面载入时间计时器
  QElapsedTimer elapsed_timer_;

  // 上次清除缓存的时间
  int last_clean_cache_time_; 

  // 清理缓存的时间间隔
  int clean_cache_interval_; 

  // 是否显示浏览器窗口
  bool is_show_window_;  
  
  // 页面是否加载成功，没有超时
  bool is_download_success_;

};

/// WebkitCore 的单例模式，使用: WebkitCore * wc = WebkitCoreSingleton::GetInstance();
class WebkitCoreSingleton {
 public:
  static WebkitCore * GetInstance();

 private:
  static WebkitCore * m_pageloader;
  static int m_used_count;
};

} } } }  ///< end of namespace

#endif // CPAGELOADER_H

