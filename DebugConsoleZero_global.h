#ifndef DEBUGCONSOLEZERO_GLOBAL_H
#define DEBUGCONSOLEZERO_GLOBAL_H

#include <QtCore/qglobal.h>
#include <QString>

#if defined(DEBUGCONSOLEZERO_LIBRARY)
#define DEBUGCONSOLEZERO_EXPORT Q_DECL_EXPORT
#else
#define DEBUGCONSOLEZERO_EXPORT Q_DECL_IMPORT
#endif

#endif // DEBUGCONSOLEZERO_GLOBAL_H
