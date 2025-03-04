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
#pragma once
#ifndef OOX_LOGIC_PARAGRAPH_PROPERTY_INCLUDE_H_
#define OOX_LOGIC_PARAGRAPH_PROPERTY_INCLUDE_H_

#include "../../Common/SimpleTypes_Shared.h"
#include "../../Common/SimpleTypes_Word.h"

#include "./../WritingElement.h"

#include "RunProperty.h"
#include "SectionProperty.h"

namespace ComplexTypes
{
	namespace Word
	{
		//--------------------------------------------------------------------------------
		// framePr (FramePr) 17.3.1.11 (Part 1)
		//--------------------------------------------------------------------------------
		class CFramePr : public ComplexType
		{
		public:
			ComplexTypes_AdditionConstructors(CFramePr)
			CFramePr()
			{
			}
			virtual ~CFramePr()
			{
			}

			virtual void    FromXML(XmlUtils::CXmlNode& oNode)
			{
				XmlMacroReadAttributeBase( oNode, L"w:anchorLock", m_oAnchorLock );
				XmlMacroReadAttributeBase( oNode, L"w:dropCap",    m_oDropCap );
				XmlMacroReadAttributeBase( oNode, L"w:h",          m_oH );
				XmlMacroReadAttributeBase( oNode, L"w:hAnchor",    m_oHAnchor );
				XmlMacroReadAttributeBase( oNode, L"w:hRule",      m_oHRule );
				XmlMacroReadAttributeBase( oNode, L"w:hSpace",     m_oHSpace );
				XmlMacroReadAttributeBase( oNode, L"w:lines",      m_oLines );
				XmlMacroReadAttributeBase( oNode, L"w:vAnchor",    m_oVAnchor );
				XmlMacroReadAttributeBase( oNode, L"w:vSpace",     m_oVSpace );
				XmlMacroReadAttributeBase( oNode, L"w:w",          m_oW );
				XmlMacroReadAttributeBase( oNode, L"w:wrap",       m_oWrap );
				XmlMacroReadAttributeBase( oNode, L"w:x",          m_oX );
				XmlMacroReadAttributeBase( oNode, L"w:xAlign",     m_oXAlign );
				XmlMacroReadAttributeBase( oNode, L"w:y",          m_oY );
				XmlMacroReadAttributeBase( oNode, L"w:yAlign",     m_oYAlign );
			}
			virtual void    FromXML(XmlUtils::CXmlLiteReader& oReader)
			{
				ReadAttributes(oReader);

				if ( !oReader.IsEmptyNode() )
					oReader.ReadTillEnd();
			}
			virtual std::wstring ToString() const
			{
				std::wstring sResult;

				if ( m_oAnchorLock.IsInit() )
				{
					sResult += L"w:anchorLock=\"";
					sResult += m_oAnchorLock->ToString();
					sResult += L"\" ";
				}

				if ( m_oDropCap.IsInit() )
				{
					sResult += L"w:dropCap=\"";
					sResult += m_oDropCap->ToString();
					sResult += L"\" ";
				}

				if ( m_oH.IsInit() )
				{
					sResult += L"w:h=\"";
					sResult += m_oH->ToString();
					sResult += L"\" ";
				}

				if ( m_oHAnchor.IsInit() )
				{
					sResult += L"w:hAnchor=\"";
					sResult += m_oHAnchor->ToString();
					sResult += L"\" ";
				}

				if ( m_oHRule.IsInit() )
				{
					sResult += L"w:hRule=\"";
					sResult += m_oHRule->ToString();
					sResult += L"\" ";
				}

				if ( m_oHSpace.IsInit() )
				{
					sResult += L"w:hSpace=\"";
					sResult += m_oHSpace->ToString();
					sResult += L"\" ";
				}

				if ( m_oLines.IsInit() )
				{
					sResult += L"w:lines=\"";
					sResult += m_oLines->ToString();
					sResult += L"\" ";
				}

				if ( m_oVAnchor.IsInit() )
				{
					sResult += L"w:vAnchor=\"";
					sResult += m_oVAnchor->ToString();
					sResult += L"\" ";
				}

				if ( m_oVSpace.IsInit() )
				{
					sResult += L"w:vSpace=\"";
					sResult += m_oVSpace->ToString();
					sResult += L"\" ";
				}

				if ( m_oW.IsInit() )
				{
					sResult += L"w:w=\"";
					sResult += m_oW->ToString();
					sResult += L"\" ";
				}

				if ( m_oWrap.IsInit() )
				{
					sResult += L"w:wrap=\"";
					sResult += m_oWrap->ToString();
					sResult += L"\" ";
				}

				if ( m_oX.IsInit() )
				{
					sResult += L"w:x=\"";
					sResult += m_oX->ToString();
					sResult += L"\" ";
				}

				if ( m_oXAlign.IsInit() )
				{
					sResult += L"w:xAlign=\"";
					sResult += m_oXAlign->ToString();
					sResult += L"\" ";
				}

				if ( m_oY.IsInit() )
				{
					sResult += L"w:y=\"";
					sResult += m_oY->ToString();
					sResult += L"\" ";
				}

				if ( m_oYAlign.IsInit() )
				{
					sResult += L"w:yAlign=\"";
					sResult += m_oYAlign->ToString();
					sResult += L"\" ";
				}

				return sResult;
			}
		private:

			void ReadAttributes(XmlUtils::CXmlLiteReader& oReader)
			{
				WritingElement_ReadAttributes_Start( oReader )
				WritingElement_ReadAttributes_Read_if     ( oReader, L"w:anchorLock", m_oAnchorLock )
				WritingElement_ReadAttributes_Read_else_if( oReader, L"w:dropCap",    m_oDropCap )
				WritingElement_ReadAttributes_Read_else_if( oReader, L"w:h",          m_oH )
				WritingElement_ReadAttributes_Read_else_if( oReader, L"w:hAnchor",    m_oHAnchor )
				WritingElement_ReadAttributes_Read_else_if( oReader, L"w:hRule",      m_oHRule )
				WritingElement_ReadAttributes_Read_else_if( oReader, L"w:hSpace",     m_oHSpace )
				WritingElement_ReadAttributes_Read_else_if( oReader, L"w:lines",      m_oLines )
				WritingElement_ReadAttributes_Read_else_if( oReader, L"w:vAnchor",    m_oVAnchor )
				WritingElement_ReadAttributes_Read_else_if( oReader, L"w:vSpace",     m_oVSpace )
				WritingElement_ReadAttributes_Read_else_if( oReader, L"w:w",          m_oW )
				WritingElement_ReadAttributes_Read_else_if( oReader, L"w:wrap",       m_oWrap )
				WritingElement_ReadAttributes_Read_else_if( oReader, L"w:x",          m_oX )
				WritingElement_ReadAttributes_Read_else_if( oReader, L"w:xAlign",     m_oXAlign )
				WritingElement_ReadAttributes_Read_else_if( oReader, L"w:y",          m_oY )
				WritingElement_ReadAttributes_Read_else_if( oReader, L"w:yAlign",     m_oYAlign )
				WritingElement_ReadAttributes_End( oReader )
			}

		public:

			nullable<SimpleTypes::COnOff<>            > m_oAnchorLock;
			nullable<SimpleTypes::CDropCap<>          > m_oDropCap;
			nullable<SimpleTypes::CTwipsMeasure       > m_oH;
			nullable<SimpleTypes::CHAnchor<>          > m_oHAnchor;
			nullable<SimpleTypes::CHeightRule<>       > m_oHRule;
			nullable<SimpleTypes::CTwipsMeasure       > m_oHSpace;
			nullable<SimpleTypes::CDecimalNumber<>    > m_oLines;
			nullable<SimpleTypes::CVAnchor<>          > m_oVAnchor;
			nullable<SimpleTypes::CTwipsMeasure       > m_oVSpace;
			nullable<SimpleTypes::CTwipsMeasure       > m_oW;
			nullable<SimpleTypes::CWrap<>             > m_oWrap;
			nullable<SimpleTypes::CSignedTwipsMeasure > m_oX;
			nullable<SimpleTypes::CXAlign<>           > m_oXAlign;
			nullable<SimpleTypes::CSignedTwipsMeasure > m_oY;
			nullable<SimpleTypes::CYAlign<>           > m_oYAlign;
		};
		//--------------------------------------------------------------------------------
		// ind (Ind) 17.3.1.12 (Part 1) + 9.2.1.2 (Part 4)
		//--------------------------------------------------------------------------------
		class CInd : public ComplexType
		{
		public:
			ComplexTypes_AdditionConstructors(CInd)
			CInd()
			{
			}
			virtual ~CInd()
			{
			}

			virtual void FromXML(XmlUtils::CXmlNode& oNode)
			{
				XmlMacroReadAttributeBase( oNode, L"w:end",            m_oEnd );
				XmlMacroReadAttributeBase( oNode, L"w:endChars",       m_oEndChars );
				XmlMacroReadAttributeBase( oNode, L"w:firstLine",      m_oFirstLine );
				XmlMacroReadAttributeBase( oNode, L"w:firstLineChars", m_oFirstLineChars );
				XmlMacroReadAttributeBase( oNode, L"w:hanging",        m_oHanging );
				XmlMacroReadAttributeBase( oNode, L"w:hangingChars",   m_oHangingChars );
				XmlMacroReadAttributeBase( oNode, L"w:start",          m_oStart );
				XmlMacroReadAttributeBase( oNode, L"w:startChars",     m_oStartChars );

				// См. 9.2.1.2 Part4
				if ( !m_oStart.IsInit() )
					XmlMacroReadAttributeBase( oNode, L"w:left", m_oStart );
				if ( !m_oStartChars.IsInit() )
					XmlMacroReadAttributeBase( oNode, L"w:leftChars", m_oStartChars );
				if ( !m_oEnd.IsInit() )
					XmlMacroReadAttributeBase( oNode, L"w:right", m_oEnd );
				if ( !m_oEndChars.IsInit() )
					XmlMacroReadAttributeBase( oNode, L"w:rightChars", m_oEndChars );
			}
			virtual void FromXML(XmlUtils::CXmlLiteReader& oReader)
			{
				ReadAttributes(oReader);

				if ( !oReader.IsEmptyNode() )
					oReader.ReadTillEnd();
			}
			virtual std::wstring ToString() const
			{
				std::wstring sResult;

				if ( m_oEnd.IsInit() )
				{
					sResult += L"w:end=\"";
					sResult += m_oEnd->ToString();
					sResult += L"\" ";
				}

				if ( m_oEndChars.IsInit() )
				{
					sResult += L"w:endChars=\"";
					sResult += m_oEndChars->ToString();
					sResult += L"\" ";
				}

				if ( m_oFirstLine.IsInit() )
				{
					sResult += L"w:firstLine=\"";
					sResult += m_oFirstLine->ToString();
					sResult += L"\" ";
				}

				if ( m_oFirstLineChars.IsInit() )
				{
					sResult += L"w:firstLineChars=\"";
					sResult += m_oFirstLineChars->ToString();
					sResult += L"\" ";
				}

				if ( m_oHanging.IsInit() )
				{
					sResult += L"w:hanging=\"";
					sResult += m_oHanging->ToString();
					sResult += L"\" ";
				}

				if ( m_oHangingChars.IsInit() )
				{
					sResult += L"w:hangingChars=\"";
					sResult += m_oHangingChars->ToString();
					sResult += L"\" ";
				}

				if ( m_oStart.IsInit() )
				{
					sResult += L"w:start=\"";
					sResult += m_oStart->ToString();
					sResult += L"\" ";
				}

				if ( m_oStartChars.IsInit() )
				{
					sResult += L"w:startChars=\"";
					sResult += m_oStartChars->ToString();
					sResult += L"\" ";
				}

				return sResult;
			}

			static const CInd Merge(const CInd& oPrev, const CInd& oCurrent)
			{
				CInd oProperties;
				oProperties.m_oEnd            = Merge( oPrev.m_oEnd,            oCurrent.m_oEnd );
				oProperties.m_oEndChars            = Merge( oPrev.m_oEndChars,            oCurrent.m_oEndChars );
				oProperties.m_oFirstLine            = Merge( oPrev.m_oFirstLine,            oCurrent.m_oFirstLine );
				oProperties.m_oFirstLineChars            = Merge( oPrev.m_oFirstLineChars,            oCurrent.m_oFirstLineChars );
				oProperties.m_oHanging            = Merge( oPrev.m_oHanging,            oCurrent.m_oHanging );
				oProperties.m_oHangingChars            = Merge( oPrev.m_oHangingChars,            oCurrent.m_oHangingChars );
				oProperties.m_oStart            = Merge( oPrev.m_oStart,            oCurrent.m_oStart );
				oProperties.m_oStartChars            = Merge( oPrev.m_oStartChars,            oCurrent.m_oStartChars );
				return oProperties;
			}
			template<typename Type>
			static nullable<Type>     Merge(const nullable<Type> &oPrev, const nullable<Type> &oCurrent)
			{
				nullable<Type> oResult;

				if ( oCurrent.IsInit() )
					oResult = oCurrent;
				else if ( oPrev.IsInit() )
					oResult = oPrev;

				return oResult;
			}
		private:

			void ReadAttributes(XmlUtils::CXmlLiteReader& oReader)
			{
				WritingElement_ReadAttributes_Start( oReader )
					WritingElement_ReadAttributes_Read_if     ( oReader, L"w:end",            m_oEnd )
					WritingElement_ReadAttributes_Read_else_if( oReader, L"w:endChars",       m_oEndChars )
					WritingElement_ReadAttributes_Read_else_if( oReader, L"w:firstLine",      m_oFirstLine )
					WritingElement_ReadAttributes_Read_else_if( oReader, L"w:firstLineChars", m_oFirstLineChars )
					WritingElement_ReadAttributes_Read_else_if( oReader, L"w:hanging",        m_oHanging )
					WritingElement_ReadAttributes_Read_else_if( oReader, L"w:hangingChars",   m_oHangingChars )
					WritingElement_ReadAttributes_Read_else_if( oReader, L"w:start",          m_oStart )
					WritingElement_ReadAttributes_Read_else_if( oReader, L"w:startChars",     m_oStartChars )
					WritingElement_ReadAttributes_Read_else_if( oReader, L"w:left",           m_oStart )
					WritingElement_ReadAttributes_Read_else_if( oReader, L"w:leftChars",      m_oStartChars )
					WritingElement_ReadAttributes_Read_else_if( oReader, L"w:right",          m_oEnd )
					WritingElement_ReadAttributes_Read_else_if( oReader, L"w:rightChars",     m_oEndChars )
//2003
					WritingElement_ReadAttributes_Read_else_if(oReader, L"w:first-line",		m_oFirstLine)
					WritingElement_ReadAttributes_Read_else_if(oReader, L"w:first-line-chars",	m_oFirstLineChars)
					WritingElement_ReadAttributes_Read_else_if(oReader, L"w:hanging-chars",		m_oHangingChars)
					WritingElement_ReadAttributes_Read_else_if(oReader, L"w:left-chars",		m_oStartChars)
					WritingElement_ReadAttributes_Read_else_if(oReader, L"w:right-charss",		m_oEndChars)
				WritingElement_ReadAttributes_End( oReader )
			}
		public:

			nullable<SimpleTypes::CSignedTwipsMeasure > m_oEnd;
			nullable<SimpleTypes::CDecimalNumber<>    > m_oEndChars;
			nullable<SimpleTypes::CSignedTwipsMeasure > m_oFirstLine;
			nullable<SimpleTypes::CDecimalNumber<>    > m_oFirstLineChars;
			nullable<SimpleTypes::CSignedTwipsMeasure > m_oHanging;
			nullable<SimpleTypes::CDecimalNumber<>    > m_oHangingChars;
			nullable<SimpleTypes::CSignedTwipsMeasure > m_oStart;
			nullable<SimpleTypes::CDecimalNumber<>    > m_oStartChars;
		};

		//--------------------------------------------------------------------------------
		// Spacing 17.3.1.33 (Part 1)
		//--------------------------------------------------------------------------------
		class CSpacing : public ComplexType
		{
		public:
			ComplexTypes_AdditionConstructors(CSpacing)
			CSpacing()
			{
			}
			virtual ~CSpacing()
			{
			}

			virtual void FromXML(XmlUtils::CXmlNode& oNode)
			{
				XmlMacroReadAttributeBase( oNode, L"w:after",             m_oAfter );
				XmlMacroReadAttributeBase( oNode, L"w:afterAutospacing",  m_oAfterAutospacing );
				XmlMacroReadAttributeBase( oNode, L"w:afterLines",        m_oAfterLines );
				XmlMacroReadAttributeBase( oNode, L"w:before",            m_oBefore );
				XmlMacroReadAttributeBase( oNode, L"w:beforeAutospacing", m_oBeforeAutospacing );
				XmlMacroReadAttributeBase( oNode, L"w:beforeLines",       m_oBeforeLines );
				XmlMacroReadAttributeBase( oNode, L"w:line",              m_oLine );
				XmlMacroReadAttributeBase( oNode, L"w:lineRule",          m_oLineRule );
			}
			virtual void FromXML(XmlUtils::CXmlLiteReader& oReader)
			{
				ReadAttributes(oReader);

				if ( !oReader.IsEmptyNode() )
					oReader.ReadTillEnd();
			}
			virtual std::wstring ToString() const
			{
				std::wstring sResult;

				if ( m_oAfter.IsInit() )
				{
					sResult += L"w:after=\"";
					sResult += m_oAfter->ToString();
					sResult += L"\" ";
				}

				if ( m_oAfterAutospacing.IsInit() )
				{
					sResult += L"w:afterAutospacing=\"";
					sResult += m_oAfterAutospacing->ToString();
					sResult += L"\" ";
				}

				if ( m_oAfterLines.IsInit() )
				{
					sResult += L"w:afterLines=\"";
					sResult += m_oAfterLines->ToString();
					sResult += L"\" ";
				}

				if ( m_oBefore.IsInit() )
				{
					sResult += L"w:before=\"";
					sResult += m_oBefore->ToString();
					sResult += L"\" ";
				}

				if ( m_oBeforeAutospacing.IsInit() )
				{
					sResult += L"w:beforeAutospacing=\"";
					sResult += m_oBeforeAutospacing->ToString();
					sResult += L"\" ";
				}

				if ( m_oBeforeLines.IsInit() )
				{
					sResult += L"w:beforeLines=\"";
					sResult += m_oBeforeLines->ToString();
					sResult += L"\" ";
				}

				if ( m_oLine.IsInit() )
				{
					sResult += L"w:line=\"";
					sResult += m_oLine->ToString();
					sResult += L"\" ";
				}

				if ( m_oLineRule.IsInit() )
				{
					sResult += L"w:lineRule=\"";
					sResult += m_oLineRule->ToString();
					sResult += L"\" ";
				}

				return sResult;
			}

			static const CSpacing Merge(const CSpacing& oPrev, const CSpacing& oCurrent)
			{
				CSpacing oProperties;
				oProperties.m_oAfter            = Merge( oPrev.m_oAfter,			oCurrent.m_oAfter );
				oProperties.m_oAfterAutospacing	= Merge( oPrev.m_oAfterAutospacing,	oCurrent.m_oAfterAutospacing );
				oProperties.m_oAfterLines		= Merge( oPrev.m_oAfterLines,		oCurrent.m_oAfterLines );
				oProperties.m_oBefore			= Merge( oPrev.m_oBefore,            oCurrent.m_oBefore );
				oProperties.m_oBeforeAutospacing	= Merge( oPrev.m_oBeforeAutospacing,	oCurrent.m_oBeforeAutospacing );
				oProperties.m_oBeforeLines		= Merge( oPrev.m_oBeforeLines,		oCurrent.m_oBeforeLines );
				oProperties.m_oLine				= Merge( oPrev.m_oLine,				oCurrent.m_oLine );
				oProperties.m_oLineRule			= Merge( oPrev.m_oLineRule,			oCurrent.m_oLineRule );
				return oProperties;
			}
			template<typename Type>
			static nullable<Type>     Merge(const nullable<Type> &oPrev, const nullable<Type> &oCurrent)
			{
				nullable<Type> oResult;

				if ( oCurrent.IsInit() )
					oResult = oCurrent;
				else if ( oPrev.IsInit() )
					oResult = oPrev;

				return oResult;
			}
		private:

			void ReadAttributes(XmlUtils::CXmlLiteReader& oReader)
			{
				WritingElement_ReadAttributes_Start( oReader )
					WritingElement_ReadAttributes_Read_if     ( oReader, L"w:after",             m_oAfter )
					WritingElement_ReadAttributes_Read_else_if( oReader, L"w:afterAutospacing",  m_oAfterAutospacing )
					WritingElement_ReadAttributes_Read_else_if( oReader, L"w:afterLines",        m_oAfterLines )
					WritingElement_ReadAttributes_Read_else_if( oReader, L"w:before",            m_oBefore )
					WritingElement_ReadAttributes_Read_else_if( oReader, L"w:beforeAutospacing", m_oBeforeAutospacing )
					WritingElement_ReadAttributes_Read_else_if( oReader, L"w:beforeLines",       m_oBeforeLines )
					WritingElement_ReadAttributes_Read_else_if( oReader, L"w:line",              m_oLine )
					WritingElement_ReadAttributes_Read_else_if( oReader, L"w:lineRule",          m_oLineRule )
					WritingElement_ReadAttributes_Read_else_if( oReader, L"w:before-autospacing", m_oBeforeAutospacing)
					WritingElement_ReadAttributes_Read_else_if(oReader, L"w:after-autospacing", m_oAfterAutospacing)
				WritingElement_ReadAttributes_End( oReader )
			}
		public:

			nullable<SimpleTypes::CTwipsMeasure       > m_oAfter;
			nullable<SimpleTypes::COnOff<>            > m_oAfterAutospacing;
			nullable<SimpleTypes::CDecimalNumber<>    > m_oAfterLines;
			nullable<SimpleTypes::CTwipsMeasure       > m_oBefore;
			nullable<SimpleTypes::COnOff<>            > m_oBeforeAutospacing;
			nullable<SimpleTypes::CDecimalNumber<>    > m_oBeforeLines;
			nullable<SimpleTypes::CSignedTwipsMeasure > m_oLine;
			nullable<SimpleTypes::CLineSpacingRule<>  > m_oLineRule;
		};

		//--------------------------------------------------------------------------------
		// TabStop 17.3.1.37 (Part 1)
		//--------------------------------------------------------------------------------
		class CTabStop : public ComplexType
		{
		public:
			ComplexTypes_AdditionConstructors(CTabStop)
			CTabStop()
			{
			}
			virtual ~CTabStop()
			{
			}

			virtual void    FromXML(XmlUtils::CXmlNode& oNode)
			{
				XmlMacroReadAttributeBase( oNode, L"w:leader", m_oLeader );
				XmlMacroReadAttributeBase( oNode, L"w:pos",    m_oPos );
				XmlMacroReadAttributeBase( oNode, L"w:val",    m_oVal );
			}
			virtual void    FromXML(XmlUtils::CXmlLiteReader& oReader)
			{
				ReadAttributes(oReader);

				if ( !oReader.IsEmptyNode() )
					oReader.ReadTillEnd();
			}
			virtual std::wstring ToString() const
			{
				std::wstring sResult;

				if ( m_oLeader.IsInit() )
				{
					sResult += L"w:leader=\"";
					sResult += m_oLeader->ToString();
					sResult += L"\" ";
				}

				if ( m_oPos.IsInit() )
				{
					sResult += L"w:pos=\"";
					sResult += m_oPos->ToString();
					sResult += L"\" ";
				}

				if ( m_oVal.IsInit() )
				{
					sResult += L"w:val=\"";
					sResult += m_oVal->ToString();
					sResult += L"\" ";
				}

				return sResult;
			}
		private:

			void ReadAttributes(XmlUtils::CXmlLiteReader& oReader)
			{
				// Читаем атрибуты
				WritingElement_ReadAttributes_Start( oReader )
				WritingElement_ReadAttributes_Read_if     ( oReader, L"w:leader", m_oLeader )
				WritingElement_ReadAttributes_Read_else_if( oReader, L"w:pos",    m_oPos )
				WritingElement_ReadAttributes_Read_else_if( oReader, L"w:val",    m_oVal )
				WritingElement_ReadAttributes_End( oReader )
			}

		public:

			nullable<SimpleTypes::CTabTlc<>           > m_oLeader;
			nullable<SimpleTypes::CSignedTwipsMeasure > m_oPos;
			nullable<SimpleTypes::CTabJc<>            > m_oVal;
		};

		//--------------------------------------------------------------------------------
		// TextAlignment 17.3.1.39 (Part 1)
		//--------------------------------------------------------------------------------
		class CTextAlignment : public ComplexType
		{
		public:
			ComplexTypes_AdditionConstructors(CTextAlignment)
			CTextAlignment()
			{
			}
			virtual ~CTextAlignment()
			{
			}

			virtual void    FromXML(XmlUtils::CXmlNode& oNode)
			{
				XmlMacroReadAttributeBase( oNode, L"w:val", m_oVal );
			}
			virtual void    FromXML(XmlUtils::CXmlLiteReader& oReader)
			{
				ReadAttributes(oReader);

				if ( !oReader.IsEmptyNode() )
					oReader.ReadTillEnd();
			}
			virtual std::wstring ToString() const
			{
				std::wstring sResult;

				if ( m_oVal.IsInit() )
				{
					sResult += L"w:val=\"";
					sResult += m_oVal->ToString();
					sResult += L"\" ";
				}

				return sResult;
			}
		private:

			void ReadAttributes(XmlUtils::CXmlLiteReader& oReader)
			{
				WritingElement_ReadAttributes_Start( oReader )
				WritingElement_ReadAttributes_ReadSingle( oReader, L"w:val", m_oVal )
				WritingElement_ReadAttributes_End( oReader )
			}

		public:

			nullable<SimpleTypes::CTextAlignment<>> m_oVal;
		};

		//--------------------------------------------------------------------------------
		// TextboxTightWrap 17.3.1.40 (Part 1)
		//--------------------------------------------------------------------------------
		class CTextboxTightWrap : public ComplexType
		{
		public:
			ComplexTypes_AdditionConstructors(CTextboxTightWrap)
			CTextboxTightWrap()
			{
			}
			virtual ~CTextboxTightWrap()
			{
			}

			virtual void    FromXML(XmlUtils::CXmlNode& oNode)
			{
				XmlMacroReadAttributeBase( oNode, L"w:val", m_oVal );
			}
			virtual void    FromXML(XmlUtils::CXmlLiteReader& oReader)
			{
				ReadAttributes(oReader);

				if ( !oReader.IsEmptyNode() )
					oReader.ReadTillEnd();
			}
			virtual std::wstring ToString() const
			{
				std::wstring sResult;

				if ( m_oVal.IsInit() )
				{
					sResult += L"w:val=\"";
					sResult += m_oVal->ToString();
					sResult += L"\" ";
				}

				return sResult;
			}
		private:

			void ReadAttributes(XmlUtils::CXmlLiteReader& oReader)
			{
				WritingElement_ReadAttributes_Start( oReader )
				WritingElement_ReadAttributes_ReadSingle( oReader, L"w:val", m_oVal )
				WritingElement_ReadAttributes_End( oReader )
			}

		public:

			nullable<SimpleTypes::CTextboxTightWrap<>> m_oVal;
		};

	} // Word
} // ComplexTypes

namespace OOX
{
	namespace Logic
	{
		//--------------------------------------------------------------------------------
		// NumPr 17.13.1.19 (Part 1)
		//--------------------------------------------------------------------------------
		class CNumPr : public WritingElement
		{
		public:
			WritingElement_AdditionConstructors(CNumPr)
			CNumPr()
			{
			}
			virtual ~CNumPr()
			{
			}

		public:
			virtual void fromXML(XmlUtils::CXmlNode& oNode)
			{
				if ( L"w:numPr" != oNode.GetName() && L"w:listPr" != oNode.GetName())
					return;

				XmlUtils::CXmlNode oChild;

				if ( oNode.GetNode( L"w:ilvl", oChild ) )
					m_oIlvl = oChild;

				if ( oNode.GetNode( L"w:ins", oChild ) )
					m_oIns = oChild;

				if ( oNode.GetNode( L"w:numId", oChild ) )
					m_oNumID = oChild;
				
				if ( oNode.GetNode( L"w:ilfo", oChild ) )
					m_oNumID = oChild;
			}
			virtual void fromXML(XmlUtils::CXmlLiteReader& oReader) 
			{
				if ( oReader.IsEmptyNode() )
					return;

				int nParentDepth = oReader.GetDepth();
				while( oReader.ReadNextSiblingNode( nParentDepth ) )
				{
					std::wstring sName = oReader.GetName();
					
					if ( L"w:ilvl" == sName )
						m_oIlvl = oReader;
					else if ( L"w:ins" == sName )
						m_oIns = oReader;
					else if ( L"w:numId" == sName || L"w:ilfo" == sName )
						m_oNumID = oReader;
				}
			}
			virtual std::wstring toXML() const
			{
				std::wstring sResult = L"<w:numPr>";

				if ( m_oIlvl.IsInit() )
				{
					sResult += L"<w:ilvl ";
					sResult += m_oIlvl->ToString();
					sResult += L"/>";
				}

				if ( m_oIns.IsInit() )
				{
					sResult += L"<w:ins ";
					sResult += m_oIns->ToString();
					sResult += L"/>";
				}

				if ( m_oNumID.IsInit() )
				{
					sResult += L"<w:numId ";
					sResult += m_oNumID->ToString();
					sResult += L"/>";
				}

				sResult += L"</w:numPr>";

				return sResult;
			}

			virtual EElementType getType() const
			{
				return et_w_numPr;
			}
		public:

			nullable<ComplexTypes::Word::CDecimalNumber > m_oIlvl;
			nullable<ComplexTypes::Word::CTrackChange   > m_oIns;
			nullable<ComplexTypes::Word::CDecimalNumber > m_oNumID;

		};

		//--------------------------------------------------------------------------------
		// PBdr 17.13.1.24 (Part 1)
		//--------------------------------------------------------------------------------
		class CPBdr : public WritingElement
		{
		public:
			WritingElement_AdditionConstructors(CPBdr)
			CPBdr()
			{
			}
			virtual ~CPBdr()
			{
			}
		public:

			virtual void fromXML(XmlUtils::CXmlNode& oNode)
			{
				if ( L"w:pBdr" != oNode.GetName() )
					return;

				XmlUtils::CXmlNode oChild;

				if ( oNode.GetNode( L"w:bar", oChild ) )
					m_oBar = oChild;

				if ( oNode.GetNode( L"w:between", oChild ) )
					m_oBetween = oChild;

				if ( oNode.GetNode( L"w:bottom", oChild ) )
					m_oBottom = oChild;

				if ( oNode.GetNode( L"w:left", oChild ) )
					m_oLeft = oChild;

				if ( oNode.GetNode( L"w:right", oChild ) )
					m_oRight = oChild;

				if ( oNode.GetNode( L"w:top", oChild ) )
					m_oTop = oChild;

			}
			virtual void fromXML(XmlUtils::CXmlLiteReader& oReader) 
			{
				if ( oReader.IsEmptyNode() )
					return;

				int nParentDepth = oReader.GetDepth();
				while( oReader.ReadNextSiblingNode( nParentDepth ) )
				{
					std::wstring sName = oReader.GetName();
					if ( L"w:bar" == sName )
						m_oBar = oReader;
					else if ( L"w:between" == sName )
						m_oBetween = oReader;
					else if ( L"w:bottom" == sName )
						m_oBottom = oReader;
					else if ( L"w:left" == sName )
						m_oLeft = oReader;
					else if ( L"w:right" == sName )
						m_oRight = oReader;
					else if ( L"w:top" == sName )
						m_oTop = oReader;
				}
			}
			virtual std::wstring toXML() const
			{
				std::wstring sResult = L"<w:pBdr>";

				if ( m_oBar.IsInit() )
				{
					sResult += L"<w:bar ";
					sResult += m_oBar->ToString();
					sResult += L"/>";
				}

				if ( m_oBetween.IsInit() )
				{
					sResult += L"<w:between ";
					sResult += m_oBetween->ToString();
					sResult += L"/>";
				}

				if ( m_oBottom.IsInit() )
				{
					sResult += L"<w:bottom ";
					sResult += m_oBottom->ToString();
					sResult += L"/>";
				}

				if ( m_oLeft.IsInit() )
				{
					sResult += L"<w:left ";
					sResult += m_oLeft->ToString();
					sResult += L"/>";
				}

				if ( m_oRight.IsInit() )
				{
					sResult += L"<w:right ";
					sResult += m_oRight->ToString();
					sResult += L"/>";
				}

				if ( m_oTop.IsInit() )
				{
					sResult += L"<w:top ";
					sResult += m_oTop->ToString();
					sResult += L"/>";
				}

				sResult += L"</w:pBdr>";

				return sResult;
			}

			virtual EElementType getType() const
			{
				return et_w_pBdr;
			}
			static const CPBdr Merge(const CPBdr& oPrev, const CPBdr& oCurrent)
			{
				CPBdr oProperties;
				oProperties.m_oBar            = Merge( oPrev.m_oBar,            oCurrent.m_oBar );
				oProperties.m_oBetween            = Merge( oPrev.m_oBetween,            oCurrent.m_oBetween );
				oProperties.m_oBottom            = Merge( oPrev.m_oBottom,            oCurrent.m_oBottom );
				oProperties.m_oLeft            = Merge( oPrev.m_oLeft,            oCurrent.m_oLeft );
				oProperties.m_oRight            = Merge( oPrev.m_oRight,            oCurrent.m_oRight );
				oProperties.m_oTop            = Merge( oPrev.m_oTop,            oCurrent.m_oTop );
				return oProperties;
			}
			template<typename Type>
			static nullable<Type>     Merge(const nullable<Type> &oPrev, const nullable<Type> &oCurrent)
			{
				nullable<Type> oResult;

				if ( oCurrent.IsInit() )
					oResult = oCurrent;
				else if ( oPrev.IsInit() )
					oResult = oPrev;

				return oResult;
			}
		public:

			nullable<ComplexTypes::Word::CBorder > m_oBar;
			nullable<ComplexTypes::Word::CBorder > m_oBetween;
			nullable<ComplexTypes::Word::CBorder > m_oBottom;
			nullable<ComplexTypes::Word::CBorder > m_oLeft;
			nullable<ComplexTypes::Word::CBorder > m_oRight;
			nullable<ComplexTypes::Word::CBorder > m_oTop;

		};
		//--------------------------------------------------------------------------------
		// PPrChange 17.13.5.29 (Part 1)
		//--------------------------------------------------------------------------------
		class CParagraphProperty;
		class CPPrChange : public WritingElement
		{
		public:
			CPPrChange();
			CPPrChange(XmlUtils::CXmlNode& oNode);
			CPPrChange(XmlUtils::CXmlLiteReader& oReader);
			const CPPrChange& operator =(const XmlUtils::CXmlNode &oNode);
			const CPPrChange& operator =(const XmlUtils::CXmlLiteReader& oReader);
			virtual ~CPPrChange();

		public:

			virtual void         fromXML(XmlUtils::CXmlNode& oNode);
			virtual void         fromXML(XmlUtils::CXmlLiteReader& oReader);
			virtual std::wstring      toXML() const;
			virtual EElementType getType() const;

		private:

			void ReadAttributes(XmlUtils::CXmlLiteReader& oReader);

		public:

			nullable<std::wstring                       > m_sAuthor;
			nullable<SimpleTypes::CDateTime        > m_oDate;
			nullable<SimpleTypes::CDecimalNumber<> > m_oId;
			nullable<std::wstring                       > m_sUserId;

			nullable<OOX::Logic::CParagraphProperty> m_pParPr;

		};
		//--------------------------------------------------------------------------------
		// Tabs 17.3.1.38 (Part 1)
		//--------------------------------------------------------------------------------
		class CTabs : public WritingElement
		{
		public:
			WritingElement_AdditionConstructors(CTabs)
			CTabs(OOX::Document *pMain = NULL) : WritingElement(pMain)
			{
			}
			virtual ~CTabs()
			{
				for ( unsigned int nIndex = 0; nIndex < m_arrTabs.size(); nIndex++ )
				{
					if ( m_arrTabs[nIndex] ) delete m_arrTabs[nIndex];
					m_arrTabs[nIndex] = NULL;
				}
				m_arrTabs.clear();
			}
			CTabs(const CTabs& oSrc)
			{
				*this = oSrc;
			}
			const CTabs& operator =(const CTabs &oTabs)
			{
				for(size_t i = 0; i < oTabs.m_arrTabs.size(); ++i)
				{
					m_arrTabs.push_back(new ComplexTypes::Word::CTabStop(*oTabs.m_arrTabs[i]));
				}
				return *this;
			}
			virtual void fromXML(XmlUtils::CXmlNode& oNode)
			{
				if ( L"w:tabs" != oNode.GetName() )
					return;

				XmlUtils::CXmlNodes oTabs;
				if ( oNode.GetNodes( L"w:tab", oTabs ) )
				{
					XmlUtils::CXmlNode oTab;
					for ( int nIndex = 0; nIndex < oTabs.GetCount(); nIndex++ )
					{
						if ( oTabs.GetAt( nIndex, oTab ) )
						{
							ComplexTypes::Word::CTabStop *oTabStop = new ComplexTypes::Word::CTabStop(oTab);
							if (oTabStop) m_arrTabs.push_back( oTabStop );
						}
					}
				}
			}
			virtual void fromXML(XmlUtils::CXmlLiteReader& oReader) 
			{
				if ( oReader.IsEmptyNode() )
					return;

				int nParentDepth = oReader.GetDepth();
				while( oReader.ReadNextSiblingNode( nParentDepth ) )
				{
					std::wstring sName = oReader.GetName();
					if ( L"w:tab" == sName )
					{
						ComplexTypes::Word::CTabStop *oTabStop = new ComplexTypes::Word::CTabStop(oReader);
						if (oTabStop) m_arrTabs.push_back( oTabStop );
					}
				}
			}
			virtual std::wstring      toXML() const
			{
				std::wstring sResult = L"<w:tabs>";

				for (unsigned int nIndex = 0; nIndex < m_arrTabs.size(); nIndex++ )
				{
					sResult += L"<w:tab ";
					if (m_arrTabs[nIndex])
						sResult += m_arrTabs[nIndex]->ToString();
					sResult += L"/>";
				}

				sResult += L"</w:tabs>";

				return sResult;
			}

			virtual EElementType getType() const
			{
				return et_w_tabs;
			}
		public:

			std::vector<ComplexTypes::Word::CTabStop*> m_arrTabs;
		};
		//--------------------------------------------------------------------------------
		// CParagraphProperty
		//--------------------------------------------------------------------------------
		class CParagraphProperty : public WritingElement
		{
		public:
			CParagraphProperty(OOX::Document *pMain = NULL) : WritingElement(pMain)
			{
				m_bPPrChange = false;
			}
			CParagraphProperty(XmlUtils::CXmlNode& oNode) : WritingElement(NULL)
			{
				m_bPPrChange = false;
				fromXML( oNode );
			}
			CParagraphProperty(XmlUtils::CXmlLiteReader& oReader) : WritingElement(NULL)
			{
				m_bPPrChange = false;
				fromXML( oReader );
			}
			virtual ~CParagraphProperty() {}
			const CParagraphProperty& operator =(const XmlUtils::CXmlNode &oNode)
			{
				fromXML( (XmlUtils::CXmlNode &)oNode );
				return *this;
			}
			const CParagraphProperty& operator =(const XmlUtils::CXmlLiteReader &oReader)
			{
				fromXML( (XmlUtils::CXmlLiteReader&)oReader );
				return *this;
			}
			virtual void fromXML(XmlUtils::CXmlNode& oNode);
			virtual void fromXML(XmlUtils::CXmlLiteReader& oReader);
			virtual std::wstring toXML() const;

			virtual EElementType getType() const
			{
				return et_w_pPr;
			}
			static const CParagraphProperty Merge(const CParagraphProperty& oPrev, const CParagraphProperty& oCurrent)
			{
				CParagraphProperty oProperties;
				
				oProperties.m_oAdjustRightInd		= Merge( oPrev.m_oAdjustRightInd,		oCurrent.m_oAdjustRightInd );
				oProperties.m_oAutoSpaceDE			= Merge( oPrev.m_oAutoSpaceDE,			oCurrent.m_oAutoSpaceDE );
				oProperties.m_oAutoSpaceDN			= Merge( oPrev.m_oAutoSpaceDN,			oCurrent.m_oAutoSpaceDN );
				oProperties.m_oBidi					= Merge( oPrev.m_oBidi,					oCurrent.m_oBidi );
				oProperties.m_oCnfStyle				= Merge( oPrev.m_oCnfStyle,				oCurrent.m_oCnfStyle );
				oProperties.m_oContextualSpacing	= Merge( oPrev.m_oContextualSpacing,	oCurrent.m_oContextualSpacing );
				oProperties.m_oDivID				= Merge( oPrev.m_oDivID,				oCurrent.m_oDivID );
				oProperties.m_oFramePr				= Merge( oPrev.m_oFramePr,				oCurrent.m_oFramePr );

				if ( oCurrent.m_oInd.IsInit() && oPrev.m_oInd.IsInit() )
					oProperties.m_oInd = ComplexTypes::Word::CInd::Merge(oPrev.m_oInd.get(), oCurrent.m_oInd.get());
				else
					oProperties.m_oInd				= Merge( oPrev.m_oInd,					oCurrent.m_oInd );

				oProperties.m_oJc					= Merge( oPrev.m_oJc,					oCurrent.m_oJc );
				oProperties.m_oKeepLines			= Merge( oPrev.m_oKeepLines,            oCurrent.m_oKeepLines );
				oProperties.m_oKeepNext				= Merge( oPrev.m_oKeepNext,				oCurrent.m_oKeepNext );
				oProperties.m_oKinsoku				= Merge( oPrev.m_oKinsoku,				oCurrent.m_oKinsoku );
				oProperties.m_oMirrorIndents		= Merge( oPrev.m_oMirrorIndents,		oCurrent.m_oMirrorIndents );
				oProperties.m_oNumPr				= Merge( oPrev.m_oNumPr,				oCurrent.m_oNumPr );
				oProperties.m_oOutlineLvl			= Merge( oPrev.m_oOutlineLvl,			oCurrent.m_oOutlineLvl );
				oProperties.m_oOverflowPunct		= Merge( oPrev.m_oOverflowPunct,		oCurrent.m_oOverflowPunct );
				oProperties.m_oPageBreakBefore		= Merge( oPrev.m_oPageBreakBefore,		oCurrent.m_oPageBreakBefore );

				if ( oCurrent.m_oPBdr.IsInit() && oPrev.m_oPBdr.IsInit() )
					oProperties.m_oPBdr	= OOX::Logic::CPBdr::Merge(oPrev.m_oPBdr.get(), oCurrent.m_oPBdr.get());
				else
					oProperties.m_oPBdr				= Merge( oPrev.m_oPBdr,            oCurrent.m_oPBdr );

				oProperties.m_oPPrChange			= Merge( oPrev.m_oPPrChange,		oCurrent.m_oPPrChange );
				oProperties.m_oPStyle				= Merge( oPrev.m_oPStyle,			oCurrent.m_oPStyle );
				oProperties.m_oRPr					= Merge( oPrev.m_oRPr,				oCurrent.m_oRPr );
				oProperties.m_oSectPr				= Merge( oPrev.m_oSectPr,			oCurrent.m_oSectPr );
				oProperties.m_oShd					= Merge( oPrev.m_oShd,				oCurrent.m_oShd );
				oProperties.m_oSnapToGrid			= Merge( oPrev.m_oSnapToGrid,		oCurrent.m_oSnapToGrid );

				if ( oCurrent.m_oSpacing.IsInit() && oPrev.m_oSpacing.IsInit() )
					oProperties.m_oSpacing	= ComplexTypes::Word::CSpacing::Merge(oPrev.m_oSpacing.get(), oCurrent.m_oSpacing.get());
				else 
					oProperties.m_oSpacing			= Merge( oPrev.m_oSpacing,	oCurrent.m_oSpacing );

				oProperties.m_oSuppressAutoHyphens	= Merge( oPrev.m_oSuppressAutoHyphens,	oCurrent.m_oSuppressAutoHyphens );
				oProperties.m_oSuppressLineNumbers	= Merge( oPrev.m_oSuppressLineNumbers,	oCurrent.m_oSuppressLineNumbers );
				oProperties.m_oSuppressOverlap		= Merge( oPrev.m_oSuppressOverlap,		oCurrent.m_oSuppressOverlap );
				oProperties.m_oTabs					= Merge( oPrev.m_oTabs,					oCurrent.m_oTabs );
				oProperties.m_oTextAlignment		= Merge( oPrev.m_oTextAlignment,		oCurrent.m_oTextAlignment );
				oProperties.m_oTextboxTightWrap		= Merge( oPrev.m_oTextboxTightWrap,		oCurrent.m_oTextboxTightWrap );
				oProperties.m_oTextDirection		= Merge( oPrev.m_oTextDirection,		oCurrent.m_oTextDirection );
				oProperties.m_oTopLinePunct			= Merge( oPrev.m_oTopLinePunct,			oCurrent.m_oTopLinePunct );
				oProperties.m_oWidowControl			= Merge( oPrev.m_oWidowControl,			oCurrent.m_oWidowControl );
				oProperties.m_oWordWrap				= Merge( oPrev.m_oWordWrap,				oCurrent.m_oWordWrap );
				
				return oProperties;
			}
			template<typename Type>
			static nullable<Type> Merge(const nullable<Type> &oPrev, const nullable<Type> &oCurrent)
			{
				nullable<Type> oResult;

				if ( oCurrent.IsInit() )
					oResult = oCurrent;
				else if ( oPrev.IsInit() )
					oResult = oPrev;

				return oResult;
			}
			const bool IsSimple() const
			{
				if ( m_oAdjustRightInd.IsInit() ) 
					return false;


				if ( m_oAutoSpaceDE.IsInit() ) 
					return false;

				if ( m_oAutoSpaceDN.IsInit() ) 
					return false;

				if ( m_oBidi.IsInit() ) 
					return false;

				if ( m_oCnfStyle.IsInit() ) 
					return false;

				if ( m_oContextualSpacing.IsInit() ) 
					return false;

				if ( m_oDivID.IsInit() ) 
					return false;

				if ( m_oFramePr.IsInit() )
					return false;

				if ( m_oInd.IsInit() )
					return false;

				if ( m_oJc.IsInit() ) 
					return false;

				if ( m_oKeepLines.IsInit() )
					return false;

				if ( m_oKeepNext.IsInit() ) 
					return false;

				if ( m_oKinsoku.IsInit() )
					return false;

				if ( m_oMirrorIndents.IsInit() ) 
					return false;
				
				if ( m_oNumPr.IsInit() ) 
					return false;

				if ( m_oOutlineLvl.IsInit() ) 
					return false;

				if ( m_oOverflowPunct.IsInit() ) 
					return false;

				if ( m_oPageBreakBefore.IsInit() ) 
					return false;

				if ( m_oPBdr.IsInit() )
					return false;

				if ( m_oPPrChange.IsInit() )
					return false;

				if ( m_oRPr.IsInit() && !m_oRPr->IsSimple() )
					return false;

				if ( m_oSectPr.IsInit() ) 
					return false;

				if ( m_oShd.IsInit() ) 
					return false;

				if ( m_oSnapToGrid.IsInit() ) 
					return false;

				if ( m_oSpacing.IsInit() ) 
					return false;

				if ( m_oSuppressAutoHyphens.IsInit() ) 
					return false;

				if ( m_oSuppressLineNumbers.IsInit() ) 
					return false;

				if ( m_oSuppressOverlap.IsInit() ) 
					return false;

				if ( m_oTabs.IsInit() ) 
					return false;

				if ( m_oTextAlignment.IsInit() ) 
					return false;

				if ( m_oTextboxTightWrap.IsInit() ) 
					return false;

				if ( m_oTextDirection.IsInit() )
					return false;

				if ( m_oTopLinePunct.IsInit() )
					return false;

				if ( m_oWidowControl.IsInit() ) 
					return false;

				if ( m_oWordWrap.IsInit() ) 
					return false;

				return true;
			}

//--------------------------------------------------------------------------------------------------------
			bool                                                           m_bPPrChange;

			nullable<ComplexTypes::Word::COnOff2<SimpleTypes::onoffTrue> > m_oAdjustRightInd;
			nullable<ComplexTypes::Word::COnOff2<SimpleTypes::onoffTrue> > m_oAutoSpaceDE;
			nullable<ComplexTypes::Word::COnOff2<SimpleTypes::onoffTrue> > m_oAutoSpaceDN;
			nullable<ComplexTypes::Word::COnOff2<SimpleTypes::onoffTrue> > m_oBidi;
			nullable<ComplexTypes::Word::CCnf                            > m_oCnfStyle;
			nullable<ComplexTypes::Word::COnOff2<SimpleTypes::onoffTrue> > m_oContextualSpacing;
			nullable<ComplexTypes::Word::CDecimalNumber                  > m_oDivID;
			nullable<ComplexTypes::Word::CFramePr                        > m_oFramePr;
			nullable<ComplexTypes::Word::CInd                            > m_oInd;
			nullable<ComplexTypes::Word::CJc                             > m_oJc;
			nullable<ComplexTypes::Word::COnOff2<SimpleTypes::onoffTrue> > m_oKeepLines;
			nullable<ComplexTypes::Word::COnOff2<SimpleTypes::onoffTrue> > m_oKeepNext;
			nullable<ComplexTypes::Word::COnOff2<SimpleTypes::onoffTrue> > m_oKinsoku;
			nullable<ComplexTypes::Word::COnOff2<SimpleTypes::onoffTrue> > m_oMirrorIndents;
			nullable<OOX::Logic::CNumPr                                  > m_oNumPr;
			nullable<ComplexTypes::Word::CDecimalNumber                  > m_oOutlineLvl;
			nullable<ComplexTypes::Word::COnOff2<SimpleTypes::onoffTrue> > m_oOverflowPunct;
			nullable<ComplexTypes::Word::COnOff2<SimpleTypes::onoffTrue> > m_oPageBreakBefore;
			nullable<OOX::Logic::CPBdr                                   > m_oPBdr;
			nullable<OOX::Logic::CPPrChange                              > m_oPPrChange;
			nullable<ComplexTypes::Word::String                        > m_oPStyle;
			nullable<OOX::Logic::CRunProperty                            > m_oRPr;
			nullable<OOX::Logic::CSectionProperty                        > m_oSectPr;
			nullable<ComplexTypes::Word::CShading                        > m_oShd;
			nullable<ComplexTypes::Word::COnOff2<SimpleTypes::onoffTrue> > m_oSnapToGrid;
			nullable<ComplexTypes::Word::CSpacing                        > m_oSpacing;
			nullable<ComplexTypes::Word::COnOff2<SimpleTypes::onoffTrue> > m_oSuppressAutoHyphens;
			nullable<ComplexTypes::Word::COnOff2<SimpleTypes::onoffTrue> > m_oSuppressLineNumbers;
			nullable<ComplexTypes::Word::COnOff2<SimpleTypes::onoffTrue> > m_oSuppressOverlap;
			nullable<OOX::Logic::CTabs                                   > m_oTabs;
			nullable<ComplexTypes::Word::CTextAlignment                  > m_oTextAlignment;
			nullable<ComplexTypes::Word::CTextboxTightWrap               > m_oTextboxTightWrap;
			nullable<ComplexTypes::Word::CTextDirection                  > m_oTextDirection;
			nullable<ComplexTypes::Word::COnOff2<SimpleTypes::onoffTrue> > m_oTopLinePunct;
			nullable<ComplexTypes::Word::COnOff2<SimpleTypes::onoffTrue> > m_oWidowControl;
			nullable<ComplexTypes::Word::COnOff2<SimpleTypes::onoffTrue> > m_oWordWrap;
		};

	} // namespace Logic
} // namespace OOX
#endif // OOX_LOGIC_PARAGRAPH_PROPERTY_INCLUDE_H_
