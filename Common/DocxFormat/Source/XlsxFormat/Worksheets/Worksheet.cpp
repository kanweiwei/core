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
#include "../Workbook/Workbook.h"

#include "Worksheet.h"

#include "../Comments/Comments.h"
#include "../Comments/ThreadedComments.h"

#include "../../DocxFormat/External/HyperLink.h"
#include "../../DocxFormat/Media/Image.h"
#include "../../DocxFormat/VmlDrawing.h"

#include "../../XlsbFormat/Xlsb.h"

#include "../../XlsbFormat/WorkSheetStream.h"
#include "../../XlsbFormat/ChartSheetStream.h"

#include "../../XlsbFormat/Biff12_unions/HLINKS.h"
#include "../../XlsbFormat/Biff12_unions/MERGECELLS.h"

namespace OOX
{
	namespace Spreadsheet
	{
		CWorksheet::CWorksheet(OOX::Document* pMain) : OOX::File(pMain), OOX::IFileContainer(pMain), WritingElement(pMain)
		{
			m_bSpreadsheets = true;
			m_bWriteDirectlyToFile = false;
			m_pComments = NULL;
			m_pThreadedComments = NULL;
            m_bIsChartSheet = false;

			CXlsx* xlsx = dynamic_cast<CXlsx*>(pMain);
			if (xlsx)
			{
				m_bPrepareForBinaryWriter = true; // подготовка для бинарника при чтении
				
				xlsx->m_arWorksheets.push_back( this );
				//xlsx->m_mapWorksheets.insert( std::make_pair(rId, this) );
			}
			else 
				m_bPrepareForBinaryWriter = false;
		}
        CWorksheet::CWorksheet(OOX::Document* pMain, const CPath& oRootPath, const CPath& oPath, const std::wstring & rId, bool isChartSheet) : OOX::File(pMain), OOX::IFileContainer(pMain), WritingElement(pMain)
		{
			m_bSpreadsheets = true;
			m_bWriteDirectlyToFile = false;
			m_pComments = NULL;
			m_pThreadedComments = NULL;
            m_bIsChartSheet = isChartSheet;

			CXlsx* xlsx = dynamic_cast<CXlsx*>(pMain);
			if (xlsx)
			{
				m_bPrepareForBinaryWriter = true;
				
				xlsx->m_arWorksheets.push_back( this );
				xlsx->m_mapWorksheets.insert( std::make_pair(rId, this) );
			}
			else 
				m_bPrepareForBinaryWriter = false;

			read( oRootPath, oPath );
		}
		CWorksheet::~CWorksheet()
		{
			ClearItems();
		}

        void CWorksheet::readBin(const CPath& oPath)
        {
            CXlsb* xlsb = dynamic_cast<CXlsb*>(File::m_pMainDocument);
            if (xlsb)
            {
                if(m_bIsChartSheet)
                {
                    XLSB::ChartSheetStreamPtr chartSheetStream = std::make_shared<XLSB::ChartSheetStream>();

                    xlsb->ReadBin(oPath, chartSheetStream.get());

                    if(chartSheetStream != nullptr)
                    {
                        if (chartSheetStream->m_BrtMargins != nullptr)
                            m_oPageMargins = chartSheetStream->m_BrtMargins;
                        if (chartSheetStream->m_HEADERFOOTER != nullptr)
                            m_oHeaderFooter = chartSheetStream->m_HEADERFOOTER;
                        if (chartSheetStream->m_BrtDrawing != nullptr)
                            m_oDrawing = chartSheetStream->m_BrtDrawing;
                        if (chartSheetStream->m_BrtLegacyDrawing != nullptr)
                            m_oLegacyDrawing = chartSheetStream->m_BrtLegacyDrawing;
                        if (chartSheetStream->m_BrtLegacyDrawingHF != nullptr)
                            m_oLegacyDrawingHF = chartSheetStream->m_BrtLegacyDrawingHF;
                        if (chartSheetStream->m_BrtBkHim != nullptr)
                            m_oPicture = chartSheetStream->m_BrtBkHim;
                        if (chartSheetStream->m_CSVIEWS != nullptr)
                            m_oSheetViews = chartSheetStream->m_CSVIEWS;
                        if (chartSheetStream->m_BrtCsProp != nullptr)
                            m_oSheetPr = chartSheetStream->m_BrtCsProp;
                        if (chartSheetStream->m_BrtCsPageSetup != nullptr)
                            m_oPageSetup = chartSheetStream->m_BrtCsPageSetup;

                        if (chartSheetStream->m_BrtCsProtectionIso != nullptr)
                            m_oSheetProtection = chartSheetStream->m_BrtCsProtectionIso;
                        else if(chartSheetStream->m_BrtCsProtection != nullptr)
                            m_oSheetProtection = chartSheetStream->m_BrtCsProtection;

                    }
                }
                else
                {
                    XLSB::WorkSheetStreamPtr workSheetStream = std::make_shared<XLSB::WorkSheetStream>();

                    xlsb->ReadBin(oPath, workSheetStream.get());

					if (workSheetStream != nullptr)
					{
						if (!workSheetStream->m_arCOLINFOS.empty())
							m_oCols = workSheetStream->m_arCOLINFOS;
						if (workSheetStream->m_BrtWsDim != nullptr)
							m_oDimension = workSheetStream->m_BrtWsDim;
						if (workSheetStream->m_BrtDrawing != nullptr)
							m_oDrawing = workSheetStream->m_BrtDrawing;
						if (workSheetStream->m_BrtLegacyDrawing != nullptr)
							m_oLegacyDrawing = workSheetStream->m_BrtLegacyDrawing;
						if (workSheetStream->m_BrtLegacyDrawingHF != nullptr)
							m_oLegacyDrawingHF = workSheetStream->m_BrtLegacyDrawingHF;
						if (workSheetStream->m_HLINKS != nullptr)
							m_oHyperlinks = static_cast<XLSB::HLINKS*>(workSheetStream->m_HLINKS.get())->m_arHlinks;
						if (workSheetStream->m_MERGECELLS != nullptr)
							m_oMergeCells = static_cast<XLSB::MERGECELLS*>(workSheetStream->m_MERGECELLS.get())->m_arBrtMergeCell;
						if (workSheetStream->m_CELLTABLE != nullptr)
						{
							m_oSheetData = new CSheetData(File::m_pMainDocument);
							m_oSheetData->fromBin(workSheetStream->m_CELLTABLE);
						}
                        if (workSheetStream->m_BrtWsFmtInfo != nullptr)
                            m_oSheetFormatPr = workSheetStream->m_BrtWsFmtInfo;
                        if (workSheetStream->m_WSVIEWS2 != nullptr)
                            m_oSheetViews = workSheetStream->m_WSVIEWS2;
                        if (workSheetStream->m_BrtMargins != nullptr)
                            m_oPageMargins = workSheetStream->m_BrtMargins;
                        if (workSheetStream->m_BrtPageSetup != nullptr)
                            m_oPageSetup = workSheetStream->m_BrtPageSetup;
                        if (workSheetStream->m_BrtPrintOptions != nullptr)
                            m_oPrintOptions = workSheetStream->m_BrtPrintOptions;
                        if (workSheetStream->m_HEADERFOOTER != nullptr)
                            m_oHeaderFooter = workSheetStream->m_HEADERFOOTER;

                        if (workSheetStream->m_BrtSheetProtectionIso != nullptr)
                            m_oSheetProtection = workSheetStream->m_BrtSheetProtectionIso;
                        else if(workSheetStream->m_BrtSheetProtection != nullptr)
                            m_oSheetProtection = workSheetStream->m_BrtSheetProtection;

                        if (workSheetStream->m_LISTPARTS != nullptr)
                            m_oTableParts = workSheetStream->m_LISTPARTS;
                        if (workSheetStream->m_SORTSTATE != nullptr)
                            m_oSortState = workSheetStream->m_SORTSTATE;
                        if (!workSheetStream->m_arCONDITIONALFORMATTING.empty())
                                for(auto &item : workSheetStream->m_arCONDITIONALFORMATTING)
                                    m_arrConditionalFormatting.push_back(new OOX::Spreadsheet::CConditionalFormatting(item));

                        if (workSheetStream->m_AUTOFILTER != nullptr)
                            m_oAutofilter = workSheetStream->m_AUTOFILTER;
                        if (workSheetStream->m_DVALS != nullptr)
                            m_oDataValidations = workSheetStream->m_DVALS;
                        if (workSheetStream->m_OLEOBJECTS != nullptr)
                            m_oOleObjects = workSheetStream->m_OLEOBJECTS;
                        if (workSheetStream->m_ACTIVEXCONTROLS != nullptr)
                            m_oControls = workSheetStream->m_ACTIVEXCONTROLS;
                        if (workSheetStream->m_BrtWsProp != nullptr)
                            m_oSheetPr = workSheetStream->m_BrtWsProp;
                        if (workSheetStream->m_BrtBkHim != nullptr)
                            m_oPicture = workSheetStream->m_BrtBkHim;
                        if (workSheetStream->m_RWBRK != nullptr)
                            m_oRowBreaks = workSheetStream->m_RWBRK;
                        if (workSheetStream->m_COLBRK != nullptr)
                            m_oColBreaks = workSheetStream->m_COLBRK;
                        if (workSheetStream->m_DCON != nullptr)
                            m_oDataConsolidate = workSheetStream->m_DCON;

                        if (!workSheetStream->m_arBrtRangeProtectionIso.empty())
                            m_oProtectedRanges = workSheetStream->m_arBrtRangeProtectionIso;
                        else if(!workSheetStream->m_arBrtRangeProtection.empty())
                            m_oProtectedRanges = workSheetStream->m_arBrtRangeProtection;

                        if (workSheetStream->m_FRTWORKSHEET != nullptr)
                            m_oExtLst = workSheetStream->m_FRTWORKSHEET;
                    }

                }

            }
        }

		void CWorksheet::read(const CPath& oRootPath, const CPath& oPath)
		{
			m_oReadPath = oPath;
			IFileContainer::Read( oRootPath, oPath );

            if( m_oReadPath.GetExtention() == _T(".bin"))
            {
                readBin(m_oReadPath);
			}
			else
			{
				XmlUtils::CXmlLiteReader oReader;
				if (!oReader.FromFile(oPath.GetPath()))
					return;
				if (!oReader.ReadNextNode())
					return;

				std::wstring sName = XmlUtils::GetNameNoNS(oReader.GetName());
				if (L"worksheet" == sName || L"chartsheet" == sName)
				{
					fromXML(oReader);
				}
			}
		}
		void CWorksheet::PrepareAfterRead()
		{
			PrepareComments(m_pComments, m_pThreadedComments, m_oLegacyDrawing.GetPointer());
			PrepareConditionalFormatting();
			PrepareDataValidations();
		}
		void CWorksheet::fromXML(XmlUtils::CXmlLiteReader& oReader)
		{
			ReadAttributes( oReader );

			if ( oReader.IsEmptyNode() )
				return;
			
			int nDocumentDepth = oReader.GetDepth();
			std::wstring sName;

			while ( oReader.ReadNextSiblingNode( nDocumentDepth ) )
			{
				sName = XmlUtils::GetNameNoNS(oReader.GetName());

				if (L"cols" == sName)
					m_oCols = oReader;
				else if (L"dimension" == sName)
					m_oDimension = oReader;
				else if (L"drawing" == sName)
					m_oDrawing = oReader;
				else if (L"hyperlinks" == sName)
				{
					m_oHyperlinks = new CHyperlinks(OOX::WritingElement::m_pMainDocument);
					m_oHyperlinks->fromXML(oReader);
				}
				else if (L"mergeCells" == sName)
				{
					m_oMergeCells = new CMergeCells(OOX::WritingElement::m_pMainDocument);
					m_oMergeCells->fromXML(oReader);
				}
				else if (L"pageMargins" == sName)
					m_oPageMargins = oReader;
				else if (_T("pageSetup") == sName)
					m_oPageSetup = oReader;
				else if (L"printOptions" == sName)
					m_oPrintOptions = oReader;
				else if (L"sheetData" == sName || L"Table" == sName) // 2002 XML Format
				{
					m_oSheetData = new CSheetData(OOX::WritingElement::m_pMainDocument);
					m_oSheetData->fromXML(oReader);
				}
				else if (L"WorksheetOptions" == sName) // 2002 XML Format
				{
					ReadWorksheetOptions(oReader);
				}
				else if (L"Names" == sName)
				{
					CDefinedNames names(oReader);

					CXlsxFlat* xlsx_flat = dynamic_cast<CXlsxFlat*>(WritingElement::m_pMainDocument);
					if (xlsx_flat)
					{
						for (size_t i = 0; i < names.m_arrItems.size(); i++)
						{
							if (names.m_arrItems[i])
							{
								if ((names.m_arrItems[i]->m_oName.IsInit()) && (*names.m_arrItems[i]->m_oName == L"Print_Area"))
								{
									names.m_arrItems[i]->m_oName = L"_xlnm.Print_Area";
								}
								if (false == xlsx_flat->m_pWorkbook->m_oDefinedNames.IsInit())
									xlsx_flat->m_pWorkbook->m_oDefinedNames.Init();

								names.m_arrItems[i]->m_oLocalSheetId = (unsigned int)(xlsx_flat->m_arWorksheets.size() - 1);
								xlsx_flat->m_pWorkbook->m_oDefinedNames->m_arrItems.push_back(names.m_arrItems[i]);
								names.m_arrItems[i] = NULL;
							}
						}
						names.m_arrItems.clear();
					}
				}
				else if (L"conditionalFormatting" == sName)
					m_arrConditionalFormatting.push_back(new CConditionalFormatting(oReader));
				else if (L"sheetFormatPr" == sName)
					m_oSheetFormatPr = oReader;
				else if (L"sheetViews" == sName)
					m_oSheetViews = oReader;
				else if (L"protectedRanges" == sName)
					m_oProtectedRanges = oReader;
				else if ( L"autoFilter" == sName )
					m_oAutofilter = oReader;
				else if ( _T("tableParts") == sName )
					m_oTableParts = oReader;
				else if ( _T("legacyDrawing") == sName )
					m_oLegacyDrawing = oReader;
				else if ( _T("legacyDrawingHF") == sName )
					m_oLegacyDrawingHF = oReader;
				else if ( _T("oleObjects") == sName )
					m_oOleObjects = oReader;
				else if ( _T("controls") == sName )
					m_oControls = oReader;
				else if ( _T("headerFooter") == sName )
					m_oHeaderFooter = oReader;
				else if (_T("sheetPr") == sName)
					m_oSheetPr = oReader;
				else if (_T("extLst") == sName)
					m_oExtLst = oReader;
				else if (_T("picture") == sName)
					m_oPicture = oReader;
				else if (_T("rowBreaks") == sName)
					m_oRowBreaks = oReader;
				else if (_T("colBreaks") == sName)
					m_oColBreaks = oReader;
				else if (_T("sheetProtection") == sName)
					m_oSheetProtection = oReader;
				else if (_T("dataValidations") == sName)
					m_oDataValidations = oReader;
				else if (_T("dataConsolidate") == sName)
					m_oDataConsolidate = oReader;
				else if (_T("sortState") == sName)
					m_oSortState = oReader;
				else if (L"DataValidation" == sName)
				{
					if (false == m_oDataValidations.IsInit())
					{
						m_oDataValidations.Init();
					}
					CDataValidation* validation = new CDataValidation(OOX::WritingElement::m_pMainDocument);
					validation->fromXML(oReader);

					m_oDataValidations->m_arrItems.push_back(validation);
				}
				else if (L"ConditionalFormatting" == sName)
				{
					CConditionalFormatting* cond_formating = new CConditionalFormatting(OOX::WritingElement::m_pMainDocument);
					cond_formating->fromXML(oReader);

					m_arrConditionalFormatting.push_back(cond_formating);
				}
				else if (L"AlternateContent" == sName)
				{
					int nSubDepth = oReader.GetDepth();
					while( oReader.ReadNextSiblingNode( nSubDepth ) )
					{
						std::wstring sSubName = XmlUtils::GetNameNoNS(oReader.GetName());
						if ( L"Choice" == sSubName )
						{
							fromXML(oReader);
						}
					}
				}
			}
		}


		//void CWorksheet::ReadWorksheetOptions(XmlUtils::CXmlLiteReader& oReader);//SheetData.cpp

		void CWorksheet::ReadAttributes(XmlUtils::CXmlLiteReader& oReader)
		{
			nullable_string sName;
			
			WritingElement_ReadAttributes_Start( oReader )
				WritingElement_ReadAttributes_Read_if	( oReader, L"ss:Name", sName )
			WritingElement_ReadAttributes_End( oReader )

			CXlsxFlat* xlsx_flat = dynamic_cast<CXlsxFlat*>(WritingElement::m_pMainDocument);
			if (xlsx_flat)
			{
				if (false == xlsx_flat->m_pWorkbook->m_oSheets.IsInit())
				{
					xlsx_flat->m_pWorkbook->m_oSheets = new CSheets(WritingElement::m_pMainDocument);
				}
				CSheet* pSheet = new CSheet( WritingElement::m_pMainDocument );
				xlsx_flat->m_pWorkbook->m_oSheets->m_arrItems.push_back(pSheet);

				pSheet->m_oState = new SimpleTypes::Spreadsheet::CVisibleType<>(SimpleTypes::Spreadsheet::visibleVisible);
				if (sName.IsInit())
				{
					pSheet->m_oName = sName;
				}
				pSheet->m_oSheetId.Init();
				pSheet->m_oSheetId->SetValue(xlsx_flat->m_pWorkbook->m_oSheets->m_arrItems.size());
			}
		}
		void CWorksheet::PrepareDataValidations()
		{
			if (m_oExtLst.IsInit() == false) return;

			for (size_t i = 0; i < m_oExtLst->m_arrExt.size(); ++i)
			{
				if (false == m_oExtLst->m_arrExt[i]->m_oDataValidations.IsInit()) continue;

				for (size_t j = 0; j < m_oExtLst->m_arrExt[i]->m_oDataValidations->m_arrItems.size(); ++j)
				{
					if (NULL == m_oExtLst->m_arrExt[i]->m_oDataValidations->m_arrItems[j]) continue;

					if (false == m_oDataValidations.IsInit())
					{
						m_oDataValidations.Init();
						m_oDataValidations->m_oDisablePrompts = m_oExtLst->m_arrExt[i]->m_oDataValidations->m_oDisablePrompts;
						m_oDataValidations->m_oXWindow = m_oExtLst->m_arrExt[i]->m_oDataValidations->m_oXWindow;
						m_oDataValidations->m_oYWindow = m_oExtLst->m_arrExt[i]->m_oDataValidations->m_oYWindow;
					}
					m_oDataValidations->m_arrItems.push_back(m_oExtLst->m_arrExt[i]->m_oDataValidations->m_arrItems[j]);
					m_oExtLst->m_arrExt[i]->m_oDataValidations->m_arrItems[j] = NULL;
				}
			}
		}

		void CWorksheet::PrepareConditionalFormatting()
		{
			if (m_oExtLst.IsInit() == false) return;

			for (size_t i = 0; i < m_oExtLst->m_arrExt.size(); ++i)
			{
				for (size_t j = 0; j < m_oExtLst->m_arrExt[i]->m_arrConditionalFormatting.size(); ++j)
				{
					if (NULL == m_oExtLst->m_arrExt[i]->m_arrConditionalFormatting[j]) continue;

					for (size_t k = 0; k < m_oExtLst->m_arrExt[i]->m_arrConditionalFormatting[j]->m_arrItems.size(); ++k)
					{
						if (NULL == m_oExtLst->m_arrExt[i]->m_arrConditionalFormatting[j]->m_arrItems[k]) continue;

						if (m_oExtLst->m_arrExt[i]->m_arrConditionalFormatting[j]->m_arrItems[k]->m_oId.IsInit())
						{
							std::wstring id = m_oExtLst->m_arrExt[i]->m_arrConditionalFormatting[j]->m_arrItems[k]->m_oId.get2();
							m_mapConditionalFormattingEx.insert(std::make_pair(id, m_oExtLst->m_arrExt[i]->m_arrConditionalFormatting[j]->m_arrItems[k]));
						}
					}
				}
			}
		}
		void CWorksheet::PrepareComments(OOX::Spreadsheet::CComments* pComments, OOX::Spreadsheet::CThreadedComments* pThreadedComments, OOX::Spreadsheet::CLegacyDrawingWorksheet* pLegacyDrawing)
		{
			OOX::CVmlDrawing* pVmlDrawing = NULL;
			if(NULL != pLegacyDrawing && pLegacyDrawing->m_oId.IsInit())
			{
				OOX::RId oRId(pLegacyDrawing->m_oId->GetValue());

				smart_ptr<OOX::File> oVmlDrawing = IFileContainer::Find(oRId);

				if (oVmlDrawing.IsInit() && OOX::FileTypes::VmlDrawing == oVmlDrawing->type())
				{
					pVmlDrawing	= static_cast<OOX::CVmlDrawing*>(oVmlDrawing.GetPointer());
				}
			}
			//2.3.7.3.1 Reconciliation
			//if Corresponding placeholder is not found, Delete the entire comment thread.
			if(!pComments || !pVmlDrawing)
				return;
			std::unordered_map<std::wstring, int> mapCheckCopyThreadedComments;
			std::vector<std::wstring> & arAuthors = pComments->m_oAuthors->m_arrItems;
			
			if(pComments->m_oCommentList.IsInit())
			{
                std::vector<OOX::Spreadsheet::CComment*> & aComments = pComments->m_oCommentList->m_arrItems;
				
				for ( size_t i = 0; i < aComments.size(); ++i)
				{
					OOX::Spreadsheet::CComment* pComment = aComments[i];

					if (!pComment) continue;

					bool bThreadedCommentCopy = false;
					OOX::Spreadsheet::CThreadedComment* pThreadedComment = NULL;
					if(pThreadedComments)
					{
						std::unordered_map<std::wstring, CThreadedComment*>::iterator pFind = pThreadedComments->m_mapTopLevelThreadedComments.end();

						bool isPlaceholder = false;
						if(pComment->m_oAuthorId.IsInit())
						{
							unsigned int nAuthorId = pComment->m_oAuthorId->GetValue();

							if (nAuthorId >= 0 && nAuthorId < arAuthors.size())
							{
								const std::wstring& sAuthor = arAuthors[nAuthorId];
								if(0 == sAuthor.compare(0, 3, L"tc="))
								{
									isPlaceholder = true;
									std::wstring sGUID = sAuthor.substr(3);
									//todo IsZero() is added to fix comments with zero ids(5.4.0)(bug 42947). Remove after few releases
									if (L"{00000000-0000-0000-0000-000000000000}" == sGUID && pComment->m_oRef.IsInit())
									{
										for (std::unordered_map<std::wstring, CThreadedComment*>::iterator it = pThreadedComments->m_mapTopLevelThreadedComments.begin(); it != pThreadedComments->m_mapTopLevelThreadedComments.end(); ++it)
										{
											if (it->second->ref.IsInit() && pComment->m_oRef->GetValue() == it->second->ref.get())
											{
												pFind = it;
												break;
											}
										}
									}
									else
									{
										pFind = pThreadedComments->m_mapTopLevelThreadedComments.find(sGUID);
									}

								}
							}
						}
						if(pThreadedComments->m_mapTopLevelThreadedComments.end() != pFind)
						{
							pThreadedComment = pFind->second;
							if(mapCheckCopyThreadedComments.end() != mapCheckCopyThreadedComments.find(pThreadedComment->id->ToString()))
							{
								bThreadedCommentCopy = true;
							}
							else
							{
								mapCheckCopyThreadedComments[pThreadedComment->id->ToString()] = 1;
							}
						}
						else if(isPlaceholder)
						{
							continue;
						}
					}

					if(pComment->m_oRef.IsInit() && pComment->m_oAuthorId.IsInit())
					{
						int nRow, nCol;
						if(CCell::parseRef(pComment->m_oRef->GetValue(), nRow, nCol))
						{
							CCommentItem* pCommentItem = new CCommentItem();
							pCommentItem->m_nRow = nRow - 1;
							pCommentItem->m_nCol = nCol - 1;

							unsigned int nAuthorId = pComment->m_oAuthorId->GetValue();
							
							if (nAuthorId >= 0 && nAuthorId < arAuthors.size())
							{
								pCommentItem->m_sAuthor = arAuthors[nAuthorId];
							}
							OOX::Spreadsheet::CSi* pSi = pComment->m_oText.GetPointerEmptyNullable();
							if(NULL != pSi)
								pCommentItem->m_oText.reset(pSi);

							pCommentItem->m_pThreadedComment = pThreadedComment;
							pCommentItem->m_bThreadedCommentCopy = bThreadedCommentCopy;

							std::wstring sNewId = std::to_wstring(pCommentItem->m_nRow.get()) + L"-" + std::to_wstring(pCommentItem->m_nCol.get());
							m_mapComments [sNewId] = pCommentItem;
						}
					}
				}
			}

			for ( size_t i = 0; i < pVmlDrawing->m_arrItems.size(); ++i)
			{
                OOX::Vml::CShape* pShape =  dynamic_cast<OOX::Vml::CShape*>(pVmlDrawing->m_arrItems[i]);
				
				if (pShape == NULL) continue;

                if (pShape->m_sId.IsInit())
                {//mark shape as used
                    boost::unordered_map<std::wstring, OOX::CVmlDrawing::_vml_shape>::iterator pFind = pVmlDrawing->m_mapShapes.find(pShape->m_sId.get());
                    if (pFind != pVmlDrawing->m_mapShapes.end())
                    {
                        pFind->second.bUsed = true;
                    }
                }
                for ( size_t j = 0; j < pShape->m_arrItems.size(); ++j)
				{
                    OOX::WritingElement* pElem = pShape->m_arrItems[j];

					if ( !pElem ) continue;
					
					if( OOX::et_v_ClientData == pElem->getType())
					{
						OOX::Vml::CClientData* pClientData = static_cast<OOX::Vml::CClientData*>(pElem);
						if(pClientData->m_oRow.IsInit() && pClientData->m_oColumn.IsInit())
						{
							int nRow = pClientData->m_oRow->GetValue();
							int nCol = pClientData->m_oColumn->GetValue();
							std::wstring sId = std::to_wstring(nRow) + L"-" + std::to_wstring(nCol);

							boost::unordered_map<std::wstring, CCommentItem*>::const_iterator pPair = m_mapComments.find(sId);
							if(pPair != m_mapComments.end())
							{
								CCommentItem* pCommentItem = pPair->second;
								if(pShape->m_sGfxData.IsInit())
									pCommentItem->m_sGfxdata = *pShape->m_sGfxData;
								std::vector<int> m_aAnchor;
								pClientData->getAnchorArray(m_aAnchor);
								if(8 <= m_aAnchor.size())
								{
									pCommentItem->m_nLeft = abs(m_aAnchor[0]);
									pCommentItem->m_nLeftOffset = abs(m_aAnchor[1]);
									pCommentItem->m_nTop = abs(m_aAnchor[2]);
									pCommentItem->m_nTopOffset = abs(m_aAnchor[3]);
									pCommentItem->m_nRight = abs(m_aAnchor[4]);
									pCommentItem->m_nRightOffset = abs(m_aAnchor[5]);
									pCommentItem->m_nBottom = abs(m_aAnchor[6]);
									pCommentItem->m_nBottomOffset =abs( m_aAnchor[7]);
								}
								pCommentItem->m_bMove = pClientData->m_oMoveWithCells;
								pCommentItem->m_bSize = pClientData->m_oSizeWithCells;
								pCommentItem->m_bVisible = pClientData->m_oVisible;

								if (pShape->m_oFillColor.IsInit())
								{
									BYTE r = pShape->m_oFillColor->Get_R();
									BYTE g = pShape->m_oFillColor->Get_G();
									BYTE b = pShape->m_oFillColor->Get_B();
									
									std::wstringstream sstream;
									sstream << boost::wformat( L"%02X%02X%02X" ) % r % g % b;

									pCommentItem->m_sFillColorRgb = sstream.str();
								}

								for(size_t k = 0; k < pShape->m_oStyle->m_arrProperties.size(); ++k)
								{
									if (pShape->m_oStyle->m_arrProperties[k] == NULL) continue;

									SimpleTypes::Vml::CCssProperty *oProperty = pShape->m_oStyle->m_arrProperties[k].get();
									if(SimpleTypes::Vml::cssptMarginLeft == oProperty->get_Type())
									{
										SimpleTypes::Vml::UCssValue oUCssValue= oProperty->get_Value();
										if(SimpleTypes::Vml::cssunitstypeUnits == oUCssValue.oValue.eType)
										{
											SimpleTypes::CPoint oPoint;
											oPoint.FromPoints(oUCssValue.oValue.dValue);
											pCommentItem->m_dLeftMM = oPoint.ToMm();
										}
									}
									else if(SimpleTypes::Vml::cssptMarginTop == oProperty->get_Type())
									{
										SimpleTypes::Vml::UCssValue oUCssValue= oProperty->get_Value();
										if(SimpleTypes::Vml::cssunitstypeUnits == oUCssValue.oValue.eType)
										{
											SimpleTypes::CPoint oPoint;
											oPoint.FromPoints(oUCssValue.oValue.dValue);
											pCommentItem->m_dTopMM = oPoint.ToMm();
										}
									}
									else if(SimpleTypes::Vml::cssptWidth == oProperty->get_Type())
									{
										SimpleTypes::Vml::UCssValue oUCssValue= oProperty->get_Value();
										if(SimpleTypes::Vml::cssunitstypeUnits == oUCssValue.oValue.eType)
										{
											SimpleTypes::CPoint oPoint;
											oPoint.FromPoints(oUCssValue.oValue.dValue);
											pCommentItem->m_dWidthMM = oPoint.ToMm();
										}
									}
									else if(SimpleTypes::Vml::cssptHeight == oProperty->get_Type())
									{
										SimpleTypes::Vml::UCssValue oUCssValue= oProperty->get_Value();
										if(SimpleTypes::Vml::cssunitstypeUnits == oUCssValue.oValue.eType)
										{
											SimpleTypes::CPoint oPoint;
											oPoint.FromPoints(oUCssValue.oValue.dValue);
											pCommentItem->m_dHeightMM = oPoint.ToMm();
										}
									}
								}
							}
						}
					}
				}
			}
		}
		void CWorksheet::PrepareToWrite()
		{
			if(false == m_oSheetFormatPr.IsInit())
				m_oSheetFormatPr.Init();
			if(false == m_oSheetFormatPr->m_oDefaultRowHeight.IsInit())
			{
				m_oSheetFormatPr->m_oDefaultRowHeight = 15.;
			}
			if(false == m_oSheetViews.IsInit())
				m_oSheetViews.Init();
			
			if(m_oSheetViews->m_arrItems.empty())
				m_oSheetViews->m_arrItems.push_back(new CSheetView());
			
			CSheetView* pSheetView = m_oSheetViews->m_arrItems.front();

			if(false == pSheetView->m_oWorkbookViewId.IsInit())
			{
				pSheetView->m_oWorkbookViewId.Init();
				pSheetView->m_oWorkbookViewId->SetValue(0);
			}

			if (false == m_oSheetData.IsInit())
			{
				m_oSheetData.Init();
			}
		}
		void CWorksheet::toXML(NSStringUtils::CStringBuilder& writer) const
		{
			if(m_oSheetPr.IsInit())
				m_oSheetPr->toXML(writer);
			if(m_oSheetViews.IsInit())
				m_oSheetViews->toXML(writer);
			if(m_oSheetFormatPr.IsInit())
				m_oSheetFormatPr->toXML(writer);
			if(m_oCols.IsInit())
				m_oCols->toXML(writer);
			if(m_oSheetData.IsInit())
				m_oSheetData->toXML(writer);
			if(m_oSheetProtection.IsInit())
				m_oSheetProtection->toXML(writer);
			if(m_oAutofilter.IsInit())
				m_oAutofilter->toXML(writer);
			if(m_oSortState.IsInit())
				m_oSortState->toXML(writer);
			if(m_oDataConsolidate.IsInit())
				m_oDataConsolidate->toXML(writer);
			if(m_oMergeCells.IsInit())
				m_oMergeCells->toXML(writer);
			for (size_t nIndex = 0, nLength = m_arrConditionalFormatting.size(); nIndex < nLength; ++nIndex)
				m_arrConditionalFormatting[nIndex]->toXML(writer);
			if(m_oDataValidations.IsInit())
				m_oDataValidations->toXML(writer);
			if(m_oHyperlinks.IsInit())
				m_oHyperlinks->toXML(writer);
			if(m_oPrintOptions.IsInit())
				m_oPrintOptions->toXML(writer);
			if(m_oPageMargins.IsInit())
				m_oPageMargins->toXML(writer);
			if(m_oPageSetup.IsInit())
				m_oPageSetup->toXML(writer);
			if(m_oHeaderFooter.IsInit())
				m_oHeaderFooter->toXML(writer);
			if(m_oRowBreaks.IsInit())
				m_oRowBreaks->toXML(writer);
			if(m_oColBreaks.IsInit())
				m_oColBreaks->toXML(writer);
			if(m_oDrawing.IsInit())
				m_oDrawing->toXML(writer);
			if(m_oLegacyDrawing.IsInit())
				m_oLegacyDrawing->toXML(writer);
			if(m_oLegacyDrawingHF.IsInit())
				m_oLegacyDrawingHF->toXML(writer);
			if(m_oPicture.IsInit())
				m_oPicture->toXML(writer);
			if(m_oOleObjects.IsInit())
				m_oOleObjects->toXML(writer);
			if(m_oControls.IsInit())
				m_oControls->toXML(writer);
			if(m_oTableParts.IsInit())
				m_oTableParts->toXML(writer);
			if(m_oExtLst.IsInit())
			{
				writer.WriteString(m_oExtLst->toXMLWithNS(L""));
			}
		}
		void CWorksheet::write(const CPath& oPath, const CPath& oDirectory, CContentTypes& oContent) const
		{
			if (!m_bWriteDirectlyToFile)
			{
				NSStringUtils::CStringBuilder sXml;
				
				toXMLStart(sXml);
					toXML(sXml);
				toXMLEnd(sXml);

				NSFile::CFileBinary::SaveToFile(oPath.GetPath(), sXml.GetData());

				oContent.Registration( type().OverrideType(), oDirectory, oPath.GetFilename() );
				IFileContainer::Write( oPath, oDirectory, oContent );
			}
			else
			{
				CPath oRealPath(oPath.GetDirectory() + FILE_SEPARATOR_STR + m_sOutputFilename);
				oContent.Registration( type().OverrideType(), oDirectory, oRealPath.GetFilename() );
				IFileContainer::Write( oRealPath, oDirectory, oContent );
			}
		}
		void CWorksheet::toXMLStart(NSStringUtils::CStringBuilder& writer) const
		{
			writer.WriteString(L"<?xml version=\"1.0\" encoding=\"UTF-8\" standalone=\"yes\"?>\
<worksheet \
xmlns=\"http://schemas.openxmlformats.org/spreadsheetml/2006/main\" \
xmlns:r=\"http://schemas.openxmlformats.org/officeDocument/2006/relationships\" \
xmlns:xdr=\"http://schemas.openxmlformats.org/drawingml/2006/spreadsheetDrawing\" \
xmlns:x14=\"http://schemas.microsoft.com/office/spreadsheetml/2009/9/main\" \
xmlns:mc=\"http://schemas.openxmlformats.org/markup-compatibility/2006\" \
xmlns:x14ac=\"http://schemas.microsoft.com/office/spreadsheetml/2009/9/ac\" \
xmlns:xr=\"http://schemas.microsoft.com/office/spreadsheetml/2014/revision\" \
xmlns:xr2=\"http://schemas.microsoft.com/office/spreadsheetml/2015/revision2\" \
xmlns:xr3=\"http://schemas.microsoft.com/office/spreadsheetml/2016/revision3\" \
mc:Ignorable=\"x14ac\">");
		}
		void CWorksheet::toXMLEnd(NSStringUtils::CStringBuilder& writer) const
		{
			writer.WriteString(L"</worksheet>");
		}

		const OOX::RId CWorksheet::AddHyperlink (std::wstring& sHref)
		{
			std::wstring sExistRId = IsExistHyperlink(sHref);
			if(sExistRId.empty())
			{
				smart_ptr<OOX::File> oHyperlinkFile = smart_ptr<OOX::File>( new OOX::HyperLink( File::m_pMainDocument, OOX::CPath(sHref, false) ) );
				const OOX::RId rId = Add( oHyperlinkFile );
				return rId;
			}
			else
			{
				const OOX::RId rId(sExistRId);
				return rId;
			}
		}
		void CWorksheet::ClearItems()
		{
			for (boost::unordered_map<std::wstring, CCommentItem*>::const_iterator it = m_mapComments.begin(); it != m_mapComments.end(); ++it)
			{
				delete it->second;
			}

			m_mapComments.clear();

			m_mapConditionalFormattingEx.clear();

			// delete Conditional Formatting
			for (size_t nIndex = 0, nLength = m_arrConditionalFormatting.size(); nIndex < nLength; ++nIndex)
			{
				delete m_arrConditionalFormatting[nIndex];
			}
			m_arrConditionalFormatting.clear();
		}

		smart_ptr<OOX::WritingElement> CWorksheet::FindVmlObject(const std::wstring &spid)
		{
			smart_ptr<OOX::WritingElement> oElement;

			if (!m_oLegacyDrawing.IsInit()) return oElement;
			if (!m_oLegacyDrawing->m_oId.IsInit()) return oElement;
            
			smart_ptr<OOX::File>		oFile		= this->Find(m_oLegacyDrawing->m_oId->GetValue());
			smart_ptr<OOX::CVmlDrawing> oVmlDrawing = oFile.smart_dynamic_cast<OOX::CVmlDrawing>();

			OOX::WritingElement* pShapeElem	= NULL;
			if (oVmlDrawing.IsInit())
			{
				oElement = oVmlDrawing->FindVmlObject(spid);	
			}
			return oElement;
		}
//----------------------------------------------------------------------------------------------------------------------
		void CCol::ReadAttributes(XmlUtils::CXmlLiteReader& oReader)
		{
			CXlsxFlat* xlsx_flat = dynamic_cast<CXlsxFlat*>(m_pMainDocument);

			nullable_double ptWidth;
			nullable_bool bAutoFit;
			nullable_string sStyleID;

			WritingElement_ReadAttributes_Start(oReader)
				WritingElement_ReadAttributes_Read_if(oReader, _T("bestFit"), m_oBestFit)
				WritingElement_ReadAttributes_Read_else_if(oReader, _T("collapsed"), m_oCollapsed)
				WritingElement_ReadAttributes_Read_else_if(oReader, _T("customWidth"), m_oCustomWidth)
				WritingElement_ReadAttributes_Read_else_if(oReader, _T("hidden"), m_oHidden)
				WritingElement_ReadAttributes_Read_else_if(oReader, _T("max"), m_oMax)
				WritingElement_ReadAttributes_Read_else_if(oReader, _T("min"), m_oMin)
				WritingElement_ReadAttributes_Read_else_if(oReader, _T("outlineLevel"), m_oOutlineLevel)
				WritingElement_ReadAttributes_Read_else_if(oReader, _T("phonetic"), m_oPhonetic)
				WritingElement_ReadAttributes_Read_else_if(oReader, _T("style"), m_oStyle)
				WritingElement_ReadAttributes_Read_else_if(oReader, _T("width"), m_oWidth)

				WritingElement_ReadAttributes_Read_else_if(oReader, _T("ss:Width"), ptWidth)
				WritingElement_ReadAttributes_Read_else_if(oReader, _T("ss:AutoFitWidth"), bAutoFit)

				WritingElement_ReadAttributes_Read_else_if(oReader, _T("ss:StyleID"), sStyleID)
				WritingElement_ReadAttributes_End(oReader)

				if (ptWidth.IsInit())
				{
					m_oWidth.Init();
					double pixDpi = *ptWidth / 72.0 * 96.; if (pixDpi < 5) pixDpi = 7; // ~
					double maxDigitSize = 4.25;
					m_oWidth->SetValue((int((pixDpi /*/ 0.75*/ - 5) / maxDigitSize * 100. + 0.5)) / 100. * 0.9);

					m_oCustomWidth.Init();
					m_oCustomWidth->FromBool(true);
				}

			if (bAutoFit.IsInit() && (*bAutoFit == false))
			{
			}
			else if (xlsx_flat)
			{
				m_oBestFit.Init();
				m_oBestFit->FromBool(true);

				if (false == ptWidth.IsInit())
				{
					m_oCustomWidth.Init();
					m_oCustomWidth->FromBool(true);

					m_oWidth.Init();
					m_oWidth->SetValue(9);
				}
			}
		}
	}
}
