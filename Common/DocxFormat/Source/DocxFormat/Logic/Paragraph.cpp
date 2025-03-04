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
#include "../DocxFlat.h"

#include "Paragraph.h"
#include "Annotations.h"
#include "Run.h"
#include "RunProperty.h"
#include "ParagraphProperty.h"
#include "FldSimple.h"
#include "Bdo.h"
#include "Sdt.h"
#include "Hyperlink.h"
#include "SmartTag.h"
#include "Dir.h"
#include "../Comments.h"
#include "../Math/oMathPara.h"
#include "../Math/OMath.h"

// TO DO: Нехватающие классы:
//        <w:customXml>
//        <w:moveFrom>
//        <w:moveTo>
//        <w:subDoc>


namespace OOX
{
	namespace Logic
	{
		//--------------------------------------------------------------------------------
		// CParagraph 17.3.1.22 (Part 1)
		//--------------------------------------------------------------------------------	

		void CParagraph::fromXML(XmlUtils::CXmlNode& oNode)
		{
			m_oParagraphProperty = NULL;

            XmlMacroReadAttributeBase( oNode, _T("w:rsidDel"),      m_oRsidDel );
            XmlMacroReadAttributeBase( oNode, _T("w:rsidP"),        m_oRsidP );
            XmlMacroReadAttributeBase( oNode, _T("w:rsidR"),        m_oRsidR );
            XmlMacroReadAttributeBase( oNode, _T("w:rsidRDefault"), m_oRsidRDefault );
            XmlMacroReadAttributeBase( oNode, _T("w:rsidRPr"),      m_oRsidRPr );

			XmlUtils::CXmlNodes oChilds;
			if ( oNode.GetNodes( _T("*"), oChilds ) )
			{
				XmlUtils::CXmlNode oItem;
				for ( int nIndex = 0; nIndex < oChilds.GetCount(); nIndex++ )
				{
					if ( oChilds.GetAt( nIndex, oItem ) )
					{
						std::wstring sName = oItem.GetName();
						WritingElement *pItem = NULL;

						if ( _T("w:bdo") == sName )
							pItem = new CBdo( oItem );
						else if ( _T("w:bookmarkEnd") == sName )
							pItem = new CBookmarkEnd( oItem );
						else if ( _T("w:bookmarkStart") == sName )
							pItem = new CBookmarkStart( oItem );
						else if ( _T("w:commentRangeEnd") == sName )
							pItem = new CCommentRangeEnd( oItem );
						else if ( _T("w:commentRangeStart") == sName )
							pItem = new CCommentRangeStart( oItem );
						//else if ( _T("w:customXml") == sName )
						//	pItem = new CCustomXml( oItem );
						else if ( _T("w:customXmlDelRangeEnd") == sName )
							pItem = new CCustomXmlDelRangeEnd( oItem );
						else if ( _T("w:customXmlDelRangeStart") == sName )
							pItem = new CCustomXmlDelRangeStart( oItem );
						else if ( _T("w:customXmlInsRangeEnd") == sName )
							pItem = new CCustomXmlInsRangeEnd( oItem );
						else if ( _T("w:customXmlInsRangeStart") == sName )
							pItem = new CCustomXmlInsRangeStart( oItem );
						else if ( _T("w:customXmlMoveFromRangeEnd") == sName ) 
							pItem = new CCustomXmlMoveFromRangeEnd( oItem );
						else if ( _T("w:customXmlMoveFromRangeStart") == sName )
							pItem = new CCustomXmlMoveFromRangeStart( oItem );
						else if ( _T("w:customXmlMoveToRangeEnd") == sName ) 
							pItem = new CCustomXmlMoveToRangeEnd( oItem );
						else if ( _T("w:customXmlMoveToRangeStart") == sName )
							pItem = new CCustomXmlMoveToRangeStart( oItem );
						//else if ( _T("w:del") == sName )
						//	pItem = new CDel( oItem );
						else if ( _T("w:dir") == sName )
							pItem = new CDir( oItem );
						else if ( _T("w:fldSimple") == sName )
							pItem = new CFldSimple( oItem );
						else if ( _T("w:hyperlink") == sName )
							pItem = new CHyperlink( oItem );
						//else if ( _T("w:ins") == sName )
						//	pItem = new CIns( oItem );
						//else if ( _T("w:moveFrom") == sName )
						//	pItem = new CMoveFrom( oItem );
						else if ( _T("w:moveFromRangeEnd") == sName )
							pItem = new CMoveFromRangeEnd( oItem );
						else if ( _T("w:moveFromRangeStart") == sName )
							pItem = new CMoveFromRangeStart( oItem );
						//else if ( _T("w:moveTo") == sName )
						//	pItem = new CMoveTo( oItem );
						else if ( _T("w:moveToRangeEnd") == sName )
							pItem = new CMoveToRangeEnd( oItem );
						else if ( _T("w:moveToRangeStart") == sName )
							pItem = new CMoveToRangeStart( oItem );
						else if ( _T("m:oMath") == sName )
							pItem = new COMath( oItem );
						else if ( _T("m:oMathPara") == sName )
							pItem = new COMathPara( oItem );
						else if ( _T("w:permEnd") == sName )
							pItem = new CPermEnd( oItem );
						else if ( _T("w:permStart") == sName )
							pItem = new CPermStart( oItem );
						else if ( _T("w:pPr") == sName )
						{
							if (m_oParagraphProperty)
							{
								CParagraphProperty prop2(oItem);
								CParagraphProperty newProp = CParagraphProperty::Merge(*m_oParagraphProperty, prop2);

								pItem = m_oParagraphProperty = new CParagraphProperty(newProp);
							}
							else
							{
								pItem = m_oParagraphProperty = new CParagraphProperty( oItem );
							}
						}
						else if ( _T("w:proofErr") == sName )
							pItem = new CProofErr( oItem );
						else if ( _T("w:r") == sName )
							pItem = new CRun( oItem );
						else if ( _T("w:sdt") == sName )
							pItem = new CSdt( oItem );
						else if ( _T("w:smartTag") == sName )
							pItem = new CSmartTag( oItem );
						//else if ( _T("w:subDoc") == sName )
						//	pItem = new CSubDoc( oItem );

						if ( pItem )
							m_arrItems.push_back( pItem );
					}
				}
			}
		}

		void CParagraph::fromXML(XmlUtils::CXmlLiteReader& oReader)
		{
			m_oParagraphProperty = NULL;

			ReadAttributes(oReader);

			if (oReader.IsEmptyNode())
				return;

			int nParentDepth = oReader.GetDepth();

			fromXML(nParentDepth, oReader);
		}
		void CParagraph::fromXML(int nDepth, XmlUtils::CXmlLiteReader& oReader)
		{
			if ( oReader.IsEmptyNode() )
				return;

			OOX::Document* document = WritingElement::m_pMainDocument;

			while( oReader.ReadNextSiblingNode(nDepth) )
			{
				std::wstring sName = oReader.GetName();
				WritingElement *pItem = NULL;

				if ( _T("w:bdo") == sName )
					pItem = new CBdo( document );
				else if ( _T("w:bookmarkEnd") == sName )
					pItem = new CBookmarkEnd( document );
				else if ( _T("w:bookmarkStart") == sName )
					pItem = new CBookmarkStart( document );
				else if ( _T("w:commentRangeEnd") == sName )
					pItem = new CCommentRangeEnd( document );
				else if ( _T("w:commentRangeStart") == sName )
					pItem = new CCommentRangeStart( document );
				else if ( L"aml:annotation" == sName) //Bookmark 
				{
					nullable_string sType;
					WritingElement_ReadAttributes_ReadSingle2(oReader, L"w:type", sType);
					
					if (sType.IsInit() && std::wstring::npos != sType->find(L"Bookmark.Start"))
						pItem = new CBookmarkStart( document );
					else if (sType.IsInit()  && std::wstring::npos != sType->find(L"Bookmark.End"))
						pItem = new CBookmarkEnd( document );
					else if (sType.IsInit()  && std::wstring::npos != sType->find(L"Comment.Start"))
						pItem = new CCommentRangeStart( document );
					else if (sType.IsInit()  && std::wstring::npos != sType->find(L"Comment.End"))
						pItem = new CCommentRangeEnd( document );
					else if (sType.IsInit()  && std::wstring::npos != sType->find(L"Comment"))
					{
						pItem = new CComment( oReader );
						
						CDocxFlat* docx_flat = dynamic_cast<CDocxFlat*>(document);
						if (docx_flat)
						{
							CComment* pComment = dynamic_cast<CComment*>(pItem);
							if ((pComment) && (pComment->m_oId.IsInit()))
							{
								docx_flat->m_oComments.m_mapComments.insert( std::make_pair( pComment->m_oId->GetValue(), docx_flat->m_oComments.m_arrComments.size()));
							}
							docx_flat->m_oComments.m_arrComments.push_back( pComment );	

							pItem = NULL;
						}
					}
				}
				//else if ( _T("w:customXml") == sName )
				//	pItem = new CCustomXml( document );
				else if ( _T("w:customXmlDelRangeEnd") == sName )
					pItem = new CCustomXmlDelRangeEnd( document );
				else if ( _T("w:customXmlDelRangeStart") == sName )
					pItem = new CCustomXmlDelRangeStart( document );
				else if ( _T("w:customXmlInsRangeEnd") == sName )
					pItem = new CCustomXmlInsRangeEnd( document );
				else if ( _T("w:customXmlInsRangeStart") == sName )
					pItem = new CCustomXmlInsRangeStart( document );
				else if ( _T("w:customXmlMoveFromRangeEnd") == sName ) 
					pItem = new CCustomXmlMoveFromRangeEnd( document );
				else if ( _T("w:customXmlMoveFromRangeStart") == sName )
					pItem = new CCustomXmlMoveFromRangeStart( document );
				else if ( _T("w:customXmlMoveToRangeEnd") == sName ) 
					pItem = new CCustomXmlMoveToRangeEnd( document );
				else if ( _T("w:customXmlMoveToRangeStart") == sName )
					pItem = new CCustomXmlMoveToRangeStart( document );
				else if ( _T("w:del") == sName )
					pItem = new CDel( document );
				else if ( _T("w:dir") == sName )
					pItem = new CDir( document );
				else if ( _T("w:fldSimple") == sName )
					pItem = new CFldSimple( document );
				else if ( _T("w:hyperlink") == sName || _T("w:hlink") == sName )
					pItem = new CHyperlink( document );
				else if ( _T("w:ins") == sName )
					pItem = new CIns( document );
				else if ( _T("w:moveFrom") == sName )
					pItem = new CMoveFrom( document );
				else if ( _T("w:moveFromRangeEnd") == sName )
					pItem = new CMoveFromRangeEnd( document );
				else if ( _T("w:moveFromRangeStart") == sName )
					pItem = new CMoveFromRangeStart( document );
				else if ( _T("w:moveTo") == sName )
					pItem = new CMoveTo( document );
				else if ( _T("w:moveToRangeEnd") == sName )
					pItem = new CMoveToRangeEnd( document );
				else if ( _T("w:moveToRangeStart") == sName )
					pItem = new CMoveToRangeStart( document );
				else if ( _T("m:oMath") == sName )
					pItem = new COMath( document );
				else if ( _T("m:oMathPara") == sName )
					pItem = new COMathPara( document );
				else if ( _T("w:permEnd") == sName )
					pItem = new CPermEnd( document );
				else if ( _T("w:permStart") == sName )
					pItem = new CPermStart( document );
				else if ( _T("w:pPr") == sName )
				{// c копией  .. для быстрого доступа/анализа
					if (m_oParagraphProperty)
					{
						CParagraphProperty prop2(document);
						prop2.fromXML(oReader);
						
						CParagraphProperty newProp = CParagraphProperty::Merge(*m_oParagraphProperty, prop2);

						pItem = m_oParagraphProperty = new CParagraphProperty(newProp);
						m_arrItems.push_back( pItem );
						continue;
					}
					else
					{
						pItem = m_oParagraphProperty = new CParagraphProperty( document );
					}
				}
				else if ( _T("w:proofErr") == sName )
					pItem = new CProofErr( document );
				else if ( _T("w:r") == sName )
					pItem = new CRun( document );
				else if ( _T("w:sdt") == sName )
					pItem = new CSdt( document );
				else if ( _T("w:smartTag") == sName )
					pItem = new CSmartTag( document );
				//else if ( _T("w:subDoc") == sName )
				//	pItem = new CSubDoc( document );
				else if (_T("w:sdtContent") == sName)
				{
					int nDepthChild = oReader.GetDepth();
					fromXML(nDepthChild, oReader);
				}

				if ( pItem )
				{
					m_arrItems.push_back( pItem );
					pItem->fromXML(oReader);
				}
			}
		}
		std::wstring CParagraph::toXML() const
		{
			std::wstring sResult = _T("<w:p ");

			ComplexTypes_WriteAttribute( _T("w:rsidDel=\""),      m_oRsidDel );
			ComplexTypes_WriteAttribute( _T("w:rsidP=\""),        m_oRsidP );
			ComplexTypes_WriteAttribute( _T("w:rsidR=\""),        m_oRsidR );
			ComplexTypes_WriteAttribute( _T("w:rsidRDefault=\""), m_oRsidRDefault );
			ComplexTypes_WriteAttribute( _T("w:rsidRPr=\""),      m_oRsidRPr );
			ComplexTypes_WriteAttribute( _T("w14:paraId=\""),     m_oParaId );
			ComplexTypes_WriteAttribute( _T("w14:textId=\""),     m_oTextId );

			sResult += _T(">");

			if (m_oParagraphProperty)
			{
				sResult += m_oParagraphProperty->toXML();
			}

            for ( size_t i = 0; i < m_arrItems.size(); ++i)
            {
                if ( m_arrItems[i] )
                {
                    if ( m_arrItems[i]->getType() == OOX::et_w_pPr ) continue;

                    sResult += m_arrItems[i]->toXML();
                }
            }

			sResult += _T("</w:p>");

			return sResult;
		}

		void CParagraph::ReadAttributes(XmlUtils::CXmlLiteReader& oReader)
		{
			WritingElement_ReadAttributes_Start( oReader )

			WritingElement_ReadAttributes_Read_if     ( oReader, _T("w:rsidDel"),      m_oRsidDel )
			WritingElement_ReadAttributes_Read_else_if( oReader, _T("w:rsidP"),        m_oRsidP )
			WritingElement_ReadAttributes_Read_else_if( oReader, _T("w:rsidR"),        m_oRsidR )
			WritingElement_ReadAttributes_Read_else_if( oReader, _T("w:rsidRDefault"), m_oRsidRDefault )
			WritingElement_ReadAttributes_Read_else_if( oReader, _T("w:rsidRPr"),      m_oRsidRPr )
			WritingElement_ReadAttributes_Read_else_if( oReader, _T("w14:paraId"),		m_oParaId )
			WritingElement_ReadAttributes_Read_else_if( oReader, _T("w14:textId"),      m_oTextId )

			WritingElement_ReadAttributes_End( oReader )
		}
		void CParagraph::AddRun(CRun *pRun)
		{
			m_arrItems.push_back( (WritingElement*)pRun );
		}
		void CParagraph::AddText(std::wstring& sText)
		{
			WritingElement *pR = new CRun();
			if ( !pR )
				return;

			WritingElement *pT = new CText();
			if ( !pT )
			{
				delete pR;
				return;
			}

			CText *pText = (CText*)pT;
			pText->m_sText  = sText;
			pText->m_oSpace = new SimpleTypes::CXmlSpace<>();
			pText->m_oSpace->SetValue( SimpleTypes::xmlspacePreserve );


			((CRun*)pR)->m_arrItems.push_back( pT );

			m_arrItems.push_back( pR );
		}
        void CParagraph::AddText(std::wstring& sText, CRunProperty * pProperty)
		{
			WritingElement *pR = new CRun();
			if ( !pR )
				return;

			WritingElement *pT = new CText();
			if ( !pT )
			{
				delete pR;
				return;
			}

			CText *pText = (CText*)pT;
			pText->m_sText  = sText;
			pText->m_oSpace = new SimpleTypes::CXmlSpace<>();
			pText->m_oSpace->SetValue( SimpleTypes::xmlspacePreserve );

			if ( pProperty )
			{
				((CRun*)pR)->m_arrItems.push_back( (WritingElement*)pProperty );
				((CRun*)pR)->m_oRunProperty	= pProperty;//копия для удобства
			}

			((CRun*)pR)->m_arrItems.push_back( pT );

			m_arrItems.push_back( pR );
		}
		void CParagraph::AddTab()
		{
			WritingElement *pR = new CRun();
			if ( !pR )
				return;

			WritingElement *pTab = new CTab();
			if ( !pTab )
			{
				delete pR;
				return;
			}

			((CRun*)pR)->m_arrItems.push_back( pTab );

			m_arrItems.push_back( pR );
		}


		void CParagraph::AddTab(CRunProperty *pProperty)
		{
			WritingElement *pR = new CRun();
			if ( !pR )
				return;

			WritingElement *pTab = new CTab();
			if ( !pTab )
			{
				delete pR;
				return;
			}
			if ( pProperty )
				((CRun*)pR)->m_arrItems.push_back( (WritingElement*)pProperty );

			((CRun*)pR)->m_arrItems.push_back( pTab );

			m_arrItems.push_back( pR );
		}


		void CParagraph::AddBreak(SimpleTypes::EBrType eType)
		{
			WritingElement *pR = new CRun();
			if ( !pR )
				return;

			WritingElement *pBr = new CBr();
			if ( !pBr )
			{
				delete pR;
				return;
			}

			((CBr*)pBr)->m_oType.SetValue( eType );

			((CRun*)pR)->m_arrItems.push_back( pBr );

			m_arrItems.push_back( pR );
		}


		void CParagraph::AddSpace(const int nCount)
		{
			WritingElement *pR = new CRun();
			if ( !pR )
				return;

			WritingElement *pT = new CText();
			if ( !pT )
			{
				delete pR;
				return;
			}

			CText *pText = (CText*)pT;
			
			char *sString = new char[nCount + 1];
			::memset( sString, 0x20, nCount );
            sString[nCount] = '\0';
			std::string s(sString);
			pText->m_sText = std::wstring(s.begin(), s.end());
			delete sString;
			pText->m_oSpace = new SimpleTypes::CXmlSpace<>();
			pText->m_oSpace->SetValue( SimpleTypes::xmlspacePreserve );

			((CRun*)pR)->m_arrItems.push_back( pT );

			m_arrItems.push_back( pR );
		}
		void CParagraph::AddSpace(const int nCount, CRunProperty *pProperty)
		{
			WritingElement *pR = new CRun();
			if ( !pR )
				return;

			WritingElement *pT = new CText();
			if ( !pT )
			{
				delete pR;
				return;
			}

			CText *pText = (CText*)pT;
			char *sString = new char[nCount + 1];
			::memset( sString, 0x20, nCount );
			sString[nCount] = '\0';
            std::string s(sString);
            pText->m_sText = std::wstring(s.begin(), s.end());
			delete sString;
			pText->m_oSpace = new SimpleTypes::CXmlSpace<>();
			pText->m_oSpace->SetValue( SimpleTypes::xmlspacePreserve );

			if ( pProperty )
				((CRun*)pR)->m_arrItems.push_back( (WritingElement*)pProperty );

			((CRun*)pR)->m_arrItems.push_back( pT );

			m_arrItems.push_back( pR );
		}


		void CParagraph::AddBookmarkStart(int nId, std::wstring& sName)
		{
			WritingElement *pBS = new CBookmarkStart();
			if ( !pBS )
				return;

			((CBookmarkStart*)pBS)->m_oId   = new SimpleTypes::CDecimalNumber<>();
			((CBookmarkStart*)pBS)->m_oId->SetValue( nId );
			((CBookmarkStart*)pBS)->m_sName = sName;

			m_arrItems.push_back( pBS );
		}	
		void CParagraph::AddBookmarkEnd  (int nId)
		{
			WritingElement *pBE = new CBookmarkEnd();
			if ( !pBE )
				return;

			((CBookmarkEnd*)pBE)->m_oId = new SimpleTypes::CDecimalNumber<>();
			((CBookmarkEnd*)pBE)->m_oId->SetValue( nId );

			m_arrItems.push_back( pBE );
		}


	} // namespace Logic
} // namespace OOX
