﻿/*
 * (c) Copyright Ascensio System SIA 2010-2019
 *
 * This program is a free software product. You can redistribute it and/or
 * modify it under the terms of the GNU Affero General Public License (AGPL)
 * version 3 as published by the Free Software Foundation. In accordance with
 * Section 7(a) of the GNU AGPL its Section 15 shall be amended to the effect
 * that Ascensio System SIA expressly excludes the warranty of non-infringement
 * of any third-party rights.
 *
 * This program is distributed WITHOUT ANY WARRANTY; without even the implied
 * warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR  PURPOSE. For
 * details, see the GNU AGPL at: http://www.gnu.org/licenses/agpl-3.0.html
 *
 * You can contact Ascensio System SIA at 20A-12 Ernesta Birznieka-Upisha
 * street, Riga, Latvia, EU, LV-1050.
 *
 * The  interactive user interfaces in modified source and object code versions
 * of the Program must display Appropriate Legal Notices, as required under
 * Section 5 of the GNU AGPL version 3.
 *
 * Pursuant to Section 7(b) of the License you must retain the original Product
 * logo when distributing the program. Pursuant to Section 7(e) we decline to
 * grant you any rights under trademark law for use of our trademarks.
 *
 * All the Product's GUI elements, including illustrations and icon sets, as
 * well as technical writing content are licensed under the terms of the
 * Creative Commons Attribution-ShareAlike 4.0 International. See the License
 * terms at http://creativecommons.org/licenses/by-sa/4.0/legalcode
 *
 */

#include "../../../common/StringExt.h"
#include "../../../graphics/pro/Fonts.h"

#include "EmfFile.h"

#ifdef _DEBUG
    #include <iostream>
#endif

#if defined(DrawText)
#undef DrawText
#endif

namespace MetaFile
{
static const struct ActionNamesEmf
{
    int     actionNumber;
    std::wstring actionName;
} actionNamesEmf[] =
{
{	0,							L"Unknown"},
{	EMR_HEADER,					L"EMR_HEADER"},
{	EMR_POLYBEZIER,				L"EMR_POLYBEZIER"},
{	EMR_POLYGON,				L"EMR_POLYGON"},
{	EMR_POLYLINE,				L"EMR_POLYLINE"},
{	EMR_POLYBEZIERTO,			L"EMR_POLYBEZIERTO"},
{	EMR_POLYLINETO,				L"EMR_POLYLINETO"},
{	EMR_POLYPOLYLINE,			L"EMR_POLYPOLYLINE"},
{	EMR_POLYPOLYGON,			L"EMR_POLYPOLYGON"},
{	EMR_SETWINDOWEXTEX,			L"EMR_SETWINDOWEXTEX"},
{	EMR_SETWINDOWORGEX,			L"EMR_SETWINDOWORGEX"},
{	EMR_SETVIEWPORTEXTEX,		L"EMR_SETVIEWPORTEXTEX"},
{	EMR_SETVIEWPORTORGEX,		L"EMR_SETVIEWPORTORGEX"},
{	EMR_SETBRUSHORGEX,			L"EMR_SETBRUSHORGEX"},
{	EMR_EOF,					L"EMR_EOF"},
{	EMR_SETPIXELV,				L"EMR_SETPIXELV"},
{	EMR_SETMAPPERFLAGS,			L"EMR_SETMAPPERFLAGS"},
{	EMR_SETMAPMODE,				L"EMR_SETMAPMODE"},
{	EMR_SETBKMODE,				L"EMR_SETBKMODE"},
{	EMR_SETPOLYFILLMODE,		L"EMR_SETPOLYFILLMODE"},
{	EMR_SETROP2,				L"EMR_SETROP2"},
{	EMR_SETSTRETCHBLTMODE,		L"EMR_SETSTRETCHBLTMODE"},
{	EMR_SETTEXTALIGN,			L"EMR_SETTEXTALIGN"},
{	EMR_SETCOLORADJUSTMENT,		L"EMR_SETCOLORADJUSTMENT"},
{	EMR_SETTEXTCOLOR,			L"EMR_SETTEXTCOLOR"},
{	EMR_SETBKCOLOR,				L"EMR_SETBKCOLOR"},
{	EMR_OFFSETCLIPRGN,			L"EMR_OFFSETCLIPRGN"},
{	EMR_MOVETOEX,				L"EMR_MOVETOEX"},
{	EMR_SETMETARGN,				L"EMR_SETMETARGN"},
{	EMR_EXCLUDECLIPRECT,		L"EMR_EXCLUDECLIPRECT"},
{	EMR_INTERSECTCLIPRECT,		L"EMR_INTERSECTCLIPRECT"},
{	EMR_SCALEVIEWPORTEXTEX,		L"EMR_SCALEVIEWPORTEXTEX"},
{	EMR_SCALEWINDOWEXTEX,		L"EMR_SCALEWINDOWEXTEX"},
{	EMR_SAVEDC,					L"EMR_SAVEDC"},
{	EMR_RESTOREDC,				L"EMR_RESTOREDC"},
{	EMR_SETWORLDTRANSFORM,		L"EMR_SETWORLDTRANSFORM"},
{	EMR_MODIFYWORLDTRANSFORM,	L"EMR_MODIFYWORLDTRANSFORM"},
{	EMR_SELECTOBJECT,			L"EMR_SELECTOBJECT"},
{	EMR_CREATEPEN,				L"EMR_CREATEPEN"},
{	EMR_CREATEBRUSHINDIRECT,	L"EMR_CREATEBRUSHINDIRECT"},
{	EMR_DELETEOBJECT,			L"EMR_DELETEOBJECT"},
{	EMR_ANGLEARC,				L"EMR_ANGLEARC"},
{	EMR_ELLIPSE,				L"EMR_ELLIPSE"},
{	EMR_RECTANGLE,				L"EMR_RECTANGLE"},
{	EMR_ROUNDRECT,				L"EMR_ROUNDRECT"},
{	EMR_ARC,					L"EMR_ARC"},
{	EMR_CHORD,					L"EMR_CHORD"},
{	EMR_PIE,					L"EMR_PIE"},
{	EMR_SELECTPALETTE,			L"EMR_SELECTPALETTE"},
{	EMR_CREATEPALETTE,			L"EMR_CREATEPALETTE"},
{	EMR_SETPALETTEENTRIES,		L"EMR_SETPALETTEENTRIES"},
{	EMR_RESIZEPALETTE,			L"EMR_RESIZEPALETTE"},
{	EMR_REALIZEPALETTE,			L"EMR_REALIZEPALETTE"},
{	EMR_EXTFLOODFILL,			L"EMR_EXTFLOODFILL"},
{	EMR_LINETO,					L"EMR_LINETO"},
{	EMR_ARCTO,					L"EMR_ARCTO"},
{	EMR_POLYDRAW,				L"EMR_POLYDRAW"},
{	EMR_SETARCDIRECTION,		L"EMR_SETARCDIRECTION"},
{	EMR_SETMITERLIMIT,			L"EMR_SETMITERLIMIT"},
{	EMR_BEGINPATH,				L"EMR_BEGINPATH"},
{	EMR_ENDPATH,				L"EMR_ENDPATH"},
{	EMR_CLOSEFIGURE,			L"EMR_CLOSEFIGURE"},
{	EMR_FILLPATH,				L"EMR_FILLPATH"},
{	EMR_STROKEANDFILLPATH,		L"EMR_STROKEANDFILLPATH"},
{	EMR_STROKEPATH,				L"EMR_STROKEPATH"},
{	EMR_FLATTENPATH,			L"EMR_FLATTENPATH"},
{	EMR_WIDENPATH,				L"EMR_WIDENPATH"},
{	EMR_SELECTCLIPPATH,			L"EMR_SELECTCLIPPATH"},
{	EMR_ABORTPATH,				L"EMR_ABORTPATH"},
{	69,							L"Unknown"},
{	EMR_GDICOMMENT,				L"EMR_GDICOMMENT"},
{	EMR_FILLRGN,				L"EMR_FILLRGN"},
{	EMR_FRAMERGN,				L"EMR_FRAMERGN"},
{	EMR_INVERTRGN,				L"EMR_INVERTRGN"},
{	EMR_PAINTRGN,				L"EMR_PAINTRGN"},
{	EMR_EXTSELECTCLIPRGN,		L"EMR_EXTSELECTCLIPRGN"},
{	EMR_BITBLT,					L"EMR_BITBLT"},
{	EMR_STRETCHBLT,				L"EMR_STRETCHBLT"},
{	EMR_MASKBLT,				L"EMR_MASKBLT"},
{	EMR_PLGBLT,					L"EMR_PLGBLT"},
{	EMR_SETDIBITSTODEVICE,		L"EMR_SETDIBITSTODEVICE"},
{	EMR_STRETCHDIBITS,			L"EMR_STRETCHDIBITS"},
{	EMR_EXTCREATEFONTINDIRECTW,	L"EMR_EXTCREATEFONTINDIRECTW"},
{	EMR_EXTTEXTOUTA,			L"EMR_EXTTEXTOUTA"},
{	EMR_EXTTEXTOUTW,			L"EMR_EXTTEXTOUTW"},
{	EMR_POLYBEZIER16,			L"EMR_POLYBEZIER16"},
{	EMR_POLYGON16,				L"EMR_POLYGON16"},
{	EMR_POLYLINE16,				L"EMR_POLYLINE16"},
{	EMR_POLYBEZIERTO16,			L"EMR_POLYBEZIERTO16"},
{	EMR_POLYLINETO16,			L"EMR_POLYLINETO16"},
{	EMR_POLYPOLYLINE16,			L"EMR_POLYPOLYLINE16"},
{	EMR_POLYPOLYGON16,			L"EMR_POLYPOLYGON16"},
{	EMR_POLYDRAW16,				L"EMR_POLYDRAW16"},
{	EMR_CREATEMONOBRUSH,		L"EMR_CREATEMONOBRUSH"},
{	EMR_CREATEDIBPATTERNBRUSHPT,L"EMR_CREATEDIBPATTERNBRUSHPT"},
{	EMR_EXTCREATEPEN,			L"EMR_EXTCREATEPEN"},
{	EMR_POLYTEXTOUTA,			L"EMR_POLYTEXTOUTA"},
{	EMR_POLYTEXTOUTW,			L"EMR_POLYTEXTOUTW"},
{	EMR_SETICMMODE,				L"EMR_SETICMMODE"},
{	EMR_CREATECOLORSPACE,		L"EMR_CREATECOLORSPACE"},
{	EMR_SETCOLORSPACE,			L"EMR_SETCOLORSPACE"},
{	EMR_DELETECOLORSPACE,		L"EMR_DELETECOLORSPACE"},
{	EMR_GLSRECORD,				L"EMR_GLSRECORD"},
{	EMR_GLSBOUNDEDRECORD,		L"EMR_GLSBOUNDEDRECORD"},
{	EMR_PIXELFORMAT,			L"EMR_PIXELFORMAT"},
{	EMR_RESERVED_105,			L"EMR_RESERVED_105"},
{	EMR_RESERVED_106,			L"EMR_RESERVED_106"},
{	EMR_RESERVED_107,			L"EMR_RESERVED_107"},
{	EMR_RESERVED_108,			L"EMR_RESERVED_108"},
{	EMR_RESERVED_109,			L"EMR_RESERVED_109"},
{	EMR_RESERVED_110,			L"EMR_RESERVED_110"},
{	EMR_COLORCORRECTPALETTE,	L"EMR_COLORCORRECTPALETTE"},
{	EMR_SETICMPROFILEA,			L"EMR_SETICMPROFILEA"},
{	EMR_SETICMPROFILEW,			L"EMR_SETICMPROFILEW"},
{	EMR_ALPHABLEND,				L"EMR_ALPHABLEND"},
{	EMR_SETLAYOUT,				L"EMR_SETLAYOUT"},
{	EMR_TRANSPARENTBLT,			L"EMR_TRANSPARENTBLT"},
{	EMR_RESERVED_117,			L"EMR_RESERVED_117"},
{	EMR_GRADIENTFILL,			L"EMR_GRADIENTFILL"},
{	EMR_RESERVED_119,			L"EMR_RESERVED_119"},
{	EMR_RESERVED_120,			L"EMR_RESERVED_120"},
{	EMR_COLORMATCHTOTARGETW,	L"EMR_COLORMATCHTOTARGETW"},
{	EMR_CREATECOLORSPACEW,		L"EMR_CREATECOLORSPACEW	"}
};
}
