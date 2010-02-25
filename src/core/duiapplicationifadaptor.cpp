/*
 * This file was generated by qdbusxml2cpp version 0.7
 * Command line was: qdbusxml2cpp -c DuiApplicationIfAdaptor -a duiapplicationadaptor.h:duiapplicationadaptor.cpp DuiApplicationIfAdaptor.xml
 *
 * qdbusxml2cpp is Copyright (C) 2009 Nokia Corporation and/or its subsidiary(-ies).
 *
 * This is an auto-generated file.
 * Do not edit! All changes made to it will be lost.
 */

#include "duiapplicationifadaptor.h"
#include <QtCore/QMetaObject>
#include <QtCore/QByteArray>
#include <QtCore/QList>
#include <QtCore/QMap>
#include <QtCore/QString>
#include <QtCore/QStringList>
#include <QtCore/QVariant>
#include <DuiDebug>

/*
 * Implementation of adaptor class DuiApplicationIfAdaptor
 */

DuiApplicationIfAdaptor::DuiApplicationIfAdaptor(QObject *parent)
    : QDBusAbstractAdaptor(parent)
{
    // constructor
    setAutoRelaySignals(true);
}

DuiApplicationIfAdaptor::~DuiApplicationIfAdaptor()
{
    // destructor
}

void DuiApplicationIfAdaptor::close()
{
    duiDebug("DuiApplicationIfAdaptor") << "DuiApplicationIfAdaptor::close()";
    // handle method call com.nokia.DuiApplicationIfAdaptor.close
    QMetaObject::invokeMethod(parent(), "close");
}

void DuiApplicationIfAdaptor::exit()
{
    duiDebug("DuiApplicationIfAdaptor") << "DuiApplicationIfAdaptor::exit()";
    // handle method call com.nokia.DuiApplicationIfAdaptor.exit
    QMetaObject::invokeMethod(parent(), "exit");
}

void DuiApplicationIfAdaptor::launch()
{
    duiDebug("DuiApplicationIfAdaptor") << "DuiApplicationIfAdaptor::launch()";
    QMetaObject::invokeMethod(parent(), "launch");
}

void DuiApplicationIfAdaptor::launch(const QStringList &parameters)
{
    duiDebug("DuiApplicationIfAdaptor") << "DuiApplicationIfAdaptor::launch(const QStringList&)";
    QMetaObject::invokeMethod(parent(), "launch", Q_ARG(QStringList, parameters));
}
