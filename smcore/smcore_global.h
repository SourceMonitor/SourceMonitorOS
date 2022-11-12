#ifndef SMCORE_GLOBAL_H
#define SMCORE_GLOBAL_H

#include <QtCore/qglobal.h>

#if defined(SMCORE_LIBRARY)
#  define SMCORE_EXPORT Q_DECL_EXPORT
#else
#  define SMCORE_EXPORT Q_DECL_IMPORT
#endif

#endif // SMCORE_GLOBAL_H
