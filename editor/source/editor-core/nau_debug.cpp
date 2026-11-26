// Copyright 2024 N-GINN LLC. All rights reserved.
// Use of this source code is governed by a BSD-3 Clause license that can be found in the LICENSE file.

#include "nau_assert.hpp"
#include "nau_log.hpp"
#include "nau_debug.hpp"


// ** NauDebugTools

void Nau::DebugTools::QtMessageHandler(QtMsgType type, const QMessageLogContext& context, const QString& msg)
{
    QByteArray localMsg = msg.toUtf8();
    const char* file = context.file ? context.file : "";
    const char* function = context.function ? context.function : "";

    if (type == QtDebugMsg || type == QtInfoMsg) return;

    NED_ERROR("QtError: {} ({}:{}, {})", localMsg.constData(), file, context.line, function);

#ifdef Q_OS_WIN
    // Qt may fail to rearm a directory watch after the directory has already moved.
    if (type == QtCriticalMsg
        && msg.startsWith(QStringLiteral("QFileSystemWatcher: FindNextChangeNotification failed for "))) {
        return;
    }
#endif
    NED_ASSERT(type == QtDebugMsg || type == QtInfoMsg);
}
