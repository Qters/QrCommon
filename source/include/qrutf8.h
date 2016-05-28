#ifndef QRUTF8_H
#define QRUTF8_H

/*!
 *  for support utf8 encoding(such like chinese), avoid chinese garbled appear in the software interface.
 *
 *  how to use:
 *  first, format of your source file must be utf-8 with bom.
 *  and, include this header file,
 *  now you can use `QString s = "中文";` instead of `QString s = QStringLiteral("中文");`.
 *
 *  example:
 *  chinese.cpp(utf8+bom)
 *  #include "qrutf8.h"
 *  void chinenseTest(){
 *      QString s = "我是中文";
 *  };
 *
*/

#if defined(_MSC_VER) && (_MSC_VER >= 1600) //  VS2010
# pragma execution_character_set("utf-8")
#endif

#endif // QRUTF8_H

