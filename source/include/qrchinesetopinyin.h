/**
  *	@brief
  *	@author	adam
  *	@date	2016/7/12
  */


#ifndef CHINESETOPINYIN_H
#define CHINESETOPINYIN_H

#include <string>

#include "qrcommon_global.h"

NS_QRCOMMON_BEGIN

class QRCOMMONSHARED_EXPORT QrChineseToPinYin
{
public:
    /*!
     * \brief convert
     * \param chinese
     * \param onlyHead
     * \return
     */
    static std::string convert(const std::wstring &chinese, bool onlyHead = false);

private:
    static long searchUnicodePinYinIdx(unsigned long key);

private:
    typedef struct
    {
        signed long dwCode;
        const char *szText;
    }ST_PinyinData;

    static ST_PinyinData sPinYinData[];
};

NS_QRCOMMON_END

#endif // CHINESETOPINYIN_H
