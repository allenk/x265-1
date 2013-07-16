/*****************************************************************************
 * x265: TShortYUV classes for short sized YUV-style frames
 *****************************************************************************
 * Copyright (C) 2013 x265 project
 *
 * Authors: Deepthi Nandakumar <deepthi@multicorewareinc.com>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02111, USA.
 *
 * This program is also available under a commercial proprietary license.
 * For more information, contact us at licensing@multicorewareinc.com
 *****************************************************************************/

#ifndef __TSHORTYUV__
#define __TSHORTYUV__

#include "TLibCommon/TComRom.h"

class TComYuv;

class TShortYUV
{
private:

    static int getAddrOffset(unsigned int partUnitIdx, unsigned int width)
    {
        int blkX = g_rasterToPelX[g_zscanToRaster[partUnitIdx]];
        int blkY = g_rasterToPelY[g_zscanToRaster[partUnitIdx]];

        return blkX + blkY * width;
    }

    static int getAddrOffset(unsigned int iTransUnitIdx, unsigned int iBlkSize, unsigned int width)
    {
        Int blkX = (iTransUnitIdx * iBlkSize) &  (width - 1);
        Int blkY = (iTransUnitIdx * iBlkSize) & ~(width - 1);

        return blkX + blkY * iBlkSize;
    }

public:

    short* YBuf;
    short* CbBuf;
    short* CrBuf;

    unsigned int width;
    unsigned int height;
    unsigned int Cwidth;
    unsigned int Cheight;

    TShortYUV();
    virtual ~TShortYUV();

    void create(unsigned int Width, unsigned int Height);
    void destroy();
    void clear();

    short*    getLumaAddr()    { return YBuf; }

    short*    getCbAddr()    { return CbBuf; }

    short*    getCrAddr()    { return CrBuf; }

    //  Access starting position of YUV partition unit buffer
    short* getLumaAddr(unsigned int partUnitIdx) { return YBuf + getAddrOffset(partUnitIdx, width); }

    short* getCbAddr(unsigned int partUnitIdx) { return CbBuf + (getAddrOffset(partUnitIdx, Cwidth) >> 1); }

    short* getCrAddr(unsigned int partUnitIdx) { return CrBuf + (getAddrOffset(partUnitIdx, Cwidth) >> 1); }

    //  Access starting position of YUV transform unit buffer
    short* getLumaAddr(unsigned int iTransUnitIdx, unsigned int iBlkSize) { return YBuf + getAddrOffset(iTransUnitIdx, iBlkSize, width); }

    short* getCbAddr(unsigned int iTransUnitIdx, unsigned int iBlkSize) { return CbBuf + getAddrOffset(iTransUnitIdx, iBlkSize, Cwidth); }

    short* getCrAddr(unsigned int iTransUnitIdx, unsigned int iBlkSize) { return CrBuf + getAddrOffset(iTransUnitIdx, iBlkSize, Cwidth); }

    void subtractLuma(TComYuv* pcYuvSrc0, TComYuv* pcYuvSrc1, unsigned int uiTrUnitIdx, unsigned int uiPartSize);
    void subtractChroma(TComYuv* pcYuvSrc0, TComYuv* pcYuvSrc1, unsigned int uiTrUnitIdx, unsigned int uiPartSize);
    void subtract(TComYuv* pcYuvSrc0, TComYuv* pcYuvSrc1, unsigned int uiTrUnitIdx, unsigned int uiPartSize);

    void    addClip(TShortYUV* pcYuvSrc0, TShortYUV* pcYuvSrc1, unsigned int uiTrUnitIdx, unsigned int uiPartSize);
    void    addClipLuma(TShortYUV* pcYuvSrc0, TShortYUV* pcYuvSrc1, unsigned int uiTrUnitIdx, unsigned int uiPartSize);
    void    addClipChroma(TShortYUV* pcYuvSrc0, TShortYUV* pcYuvSrc1, unsigned int uiTrUnitIdx, unsigned int uiPartSize);

    void    copyPartToPartYuv(TShortYUV* pcYuvDst, unsigned int uiPartIdx, unsigned int uiWidth, unsigned int uiHeight);
    void    copyPartToPartLuma(TShortYUV* pcYuvDst, unsigned int uiPartIdx, unsigned int uiWidth, unsigned int uiHeight);
    void    copyPartToPartChroma(TShortYUV* pcYuvDst, unsigned int uiPartIdx, unsigned int uiWidth, unsigned int uiHeight);
    void    copyPartToPartChroma(TShortYUV* pcYuvDst, unsigned int uiPartIdx, unsigned int iWidth, unsigned int iHeight, unsigned int chromaId);

    void    copyPartToPartYuv(TComYuv* pcYuvDst, unsigned int uiPartIdx, unsigned int uiWidth, unsigned int uiHeight);
    void    copyPartToPartLuma(TComYuv* pcYuvDst, unsigned int uiPartIdx, unsigned int uiWidth, unsigned int uiHeight);
    void    copyPartToPartChroma(TComYuv* pcYuvDst, unsigned int uiPartIdx, unsigned int uiWidth, unsigned int uiHeight);
    void    copyPartToPartChroma(TComYuv* pcYuvDst, unsigned int uiPartIdx, unsigned int iWidth, unsigned int iHeight, unsigned int chromaId);
};

#endif //end __TSHORTYUV__
