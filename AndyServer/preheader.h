#ifndef PREHEADER_H
#define PREHEADER_H
#include <QMainWindow>
#include <QtWidgets>
#include <QByteArray>
#include <QDataStream>
#include <QFileDialog>
#include <QHostAddress>
#include <QIODevice>
#include <QString>
#include <QTcpSocket>
#include <QTcpServer>
#define SafeDelete(p) if (nullptr != p) { delete p; p = nullptr; }

#endif // PREHEADER_H
