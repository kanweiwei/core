/*
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
﻿using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Xml;
using System.Xml.Schema;
using System.Xml.Serialization;
using System.IO;
using System.Collections;
using System.CodeDom;
using System.CodeDom.Compiler;

namespace codegen
{
    class CodeGenXmlJS
    {
        Dictionary<string, GenClassPivot> m_mapGeneratedClasses = new Dictionary<string, GenClassPivot>();

        //string gc_sXsd = "xl14.xsd";
        //string[] gc_aTargetTypes = new string[] { "CT_SlicerCacheDefinition" };
        //string gc_sTargetNamespace = "http://schemas.microsoft.com/office/spreadsheetml/2009/9/main";

        //string gc_sXsd = "xl14.xsd";
        //string[] gc_aTargetTypes = new string[] { "CT_SlicerCaches", "CT_SlicerRefs", "CT_SlicerStyles", "CT_Slicers" };
        //string gc_sTargetNamespace = "http://schemas.microsoft.com/office/spreadsheetml/2009/9/main";

        //string gc_sXsd = "xlslicercache15.xsd";
        //string[] gc_aTargetTypes = new string[] { "CT_TableSlicerCache", "CT_SlicerCacheHideNoData" };
        //string gc_sTargetNamespace = "http://schemas.microsoft.com/office/spreadsheetml/2010/11/main";

        //string gc_sXsd = "5.2.xsd";
        //string[] gc_aTargetTypes = new string[] { "CT_Slicer" };
        //string gc_sTargetNamespace = "http://schemas.microsoft.com/office/drawing/2010/slicer";

        //string gc_sXsd = "xlslicercache15.xsd";
        //string[] gc_aTargetTypes = new string[] { "CT_Timeline", "CT_TimelineCacheRefs" };
        //string gc_sTargetNamespace = "http://schemas.microsoft.com/office/spreadsheetml/2010/11/main";

        //string gc_sXsd = "xlslicercache15.xsd";
        //string[] gc_aTargetTypes = new string[] { "CT_Connection" };
        //string gc_sTargetNamespace = "http://schemas.microsoft.com/office/spreadsheetml/2010/11/main";

        //string gc_sXsd = "5.26.xsd";
        //string[] gc_aTargetTypes = new string[] { "CT_NamedSheetViews" };
        //string gc_sTargetNamespace = "http://schemas.microsoft.com/office/spreadsheetml/2019/namedsheetviews";

        //string gc_sXsd = "xlsx-ext/sml.xsd";
        //string[] gc_aTargetTypes = new string[] { "CT_Stylesheet" };
        //string gc_sTargetNamespace = "http://schemas.openxmlformats.org/spreadsheetml/2006/main";

        string gc_sXsd = "wml.xsd";
        string[] gc_aTargetTypes = new string[] { "CT_Document" };
        string gc_sTargetNamespace = "http://purl.oclc.org/ooxml/wordprocessingml/main";


        public void Start(string sDirIn, string sDirCppXmlOut, string sDirCppBinOut, string sDirJsBinOut, ValidationEventHandler oValidationEventHandler)
        {
            string sXsdPath = sDirIn + gc_sXsd;
            XmlSchemaSet schemaSet = new XmlSchemaSet();
            schemaSet.ValidationEventHandler += oValidationEventHandler;
            schemaSet.Add(null, sXsdPath);
            schemaSet.Compile();
            XmlSchema chartSchema = null;
            XmlSchemas schemas = new XmlSchemas();
            foreach (XmlSchema schema in schemaSet.Schemas())
            {
                if (schema.TargetNamespace == gc_sTargetNamespace)
                {
                    chartSchema = schema;
                    schemas.Add(schema);
                }
            }
            if (null != chartSchema)
            {
                CodeNamespace ns = new CodeNamespace();
                XmlCodeExporter exporter = new XmlCodeExporter(ns);

                CodeGenerationOptions generationOptions = CodeGenerationOptions.GenerateProperties;


                XmlSchemaImporter importer = new XmlSchemaImporter(schemas, generationOptions, new ImportContext(new CodeIdentifiers(), false));

                foreach (XmlSchemaElement element in chartSchema.Elements.Values)
                {
                    XmlTypeMapping mapping = importer.ImportTypeMapping(element.QualifiedName);
                    exporter.ExportTypeMapping(mapping);
                }
                CodeGenerator.ValidateIdentifiers(ns);

                ////Microsoft.CSharp.CSharpCodeProvider oProvider;

                //// output the C# code
                //Microsoft.CSharp.CSharpCodeProvider codeProvider = new Microsoft.CSharp.CSharpCodeProvider();

                //using (StringWriter writer = new StringWriter())
                //{
                //    codeProvider.GenerateCodeFromNamespace(ns, writer, new CodeGeneratorOptions());
                //    string sCode = writer.GetStringBuilder().ToString();
                //}

                List<GenClassPivot> aGenClasses = PreProcess(ns, chartSchema);

                aGenClasses = FilterClassesSlicer(aGenClasses);

                (new CodeGenXmlJSCPP()).Process(sDirCppXmlOut, aGenClasses, gc_sTargetNamespace);
                //(new CodegenJS()).Process(sDirJsBinOut, aGenClasses);
            }
            else
            {
                throw new Exception();
            }
        }
        List<GenClassPivot> FilterClassesSlicer(List<GenClassPivot> aInput)
        {
            Queue<GenClassPivot> aTemp = new Queue<GenClassPivot>();
            List<GenClassPivot> aRes = new List<GenClassPivot>();

            Dictionary<string, bool> mapTargetSubTypes = new Dictionary<string, bool>();
            Dictionary<string, bool> namspaces = new Dictionary<string, bool>();

            Dictionary<string, GenClassPivot> mapAllClasses = new Dictionary<string, GenClassPivot>();
            for (int i = 0; i < aInput.Count; ++i)
            {
                GenClassPivot oGenClass = aInput[i];
                if (0 == gc_aTargetTypes.Length || -1 != Array.IndexOf(gc_aTargetTypes, oGenClass.sName))
                    aTemp.Enqueue(oGenClass);
                mapAllClasses[oGenClass.sName] = oGenClass;
            }
            while (aTemp.Count > 0)
            {
                GenClassPivot oGenClass = aTemp.Dequeue();
                if (!mapTargetSubTypes.ContainsKey(oGenClass.sName))
                {
                    mapTargetSubTypes.Add(oGenClass.sName, true);
                    aRes.Add(oGenClass);
                    for (int j = 0; j < oGenClass.aMembers.Count; ++j)
                    {
                        GenMemberPivot oGenMember = oGenClass.aMembers[j];

                        GenClassPivot oTempClass;
                        if (null != oGenMember.sType && mapAllClasses.TryGetValue(oGenMember.sType, out oTempClass))
                        {
                            namspaces[oTempClass.sNamespace] = true;

                            aTemp.Enqueue(oTempClass);
                        }
                        if (null != oGenMember.aArrayTypes)
                        {
                            for (int k = 0; k < oGenMember.aArrayTypes.Count; ++k)
                            {
                                GenMemberPivot oGenMemberArrayTypes = oGenMember.aArrayTypes[k];
                                if (null != oGenMemberArrayTypes.sType && mapAllClasses.TryGetValue(oGenMemberArrayTypes.sType, out oTempClass))
                                {
                                    aTemp.Enqueue(oTempClass);
                                }
                            }
                        }
                    }
                }
            }
            return aRes;
        }
        List<GenClassPivot> PreProcess(CodeNamespace code, XmlSchema schema)
        {
            List<GenClassPivot> aGenClasses = new List<GenClassPivot>();
            for (int i = 0; i < code.Types.Count; ++i)
            {
                GenClassPivot oNewClass = PreProcessClass(aGenClasses, code.Types[i]);
                if (null != oNewClass)
                    aGenClasses.Add(oNewClass);
            }
            return aGenClasses;
        }
        GenClassPivot PreProcessClass(List<GenClassPivot> aGenClasses, CodeTypeDeclaration type)
        {
            GenClassPivot oGenClass = null;
            //получаем xml namespace
            string sNamespace = null;
            bool bIncludeInSchema = true;
            string sRootName = "";
            for (int i = 0; i < type.CustomAttributes.Count; i++)
            {
                CodeAttributeDeclaration attribute = type.CustomAttributes[i];
                if (attribute.Name == "System.Xml.Serialization.XmlTypeAttribute")
                {
                    foreach (CodeAttributeArgument argument in attribute.Arguments)
                    {
                        if (argument.Name == "Namespace")
                            sNamespace = ((CodePrimitiveExpression)argument.Value).Value.ToString();
                        else if (argument.Name == "IncludeInSchema")
                            bIncludeInSchema = Convert.ToBoolean(((CodePrimitiveExpression)argument.Value).Value);
                        //todo argument.Name == "TypeName"
                    }
                }
                else if (attribute.Name == "System.Xml.Serialization.XmlRootAttribute")
                {
                    foreach (CodeAttributeArgument argument in attribute.Arguments)
                    {
                        if (argument.Name == "Namespace")
                            sNamespace = ((CodePrimitiveExpression)argument.Value).Value.ToString();
                        else if ("" == argument.Name)
                            sRootName = ((CodePrimitiveExpression)argument.Value).Value.ToString();
                    }
                }
            }
            if (bIncludeInSchema)
            {
                oGenClass = new GenClassPivot(type.Name, sNamespace);
                oGenClass.sRootName = sRootName;
                int nItemsElementName = 0;
                if (type.IsEnum)
                {
                    oGenClass.bIsEnum = true;
                    for (int i = 0; i < type.Members.Count; ++i)
                    {
                        CodeTypeMember member = type.Members[i];
                        GenMemberPivot oGenMember = new GenMemberPivot(member.Name);
                        for (int j = 0; j < member.CustomAttributes.Count; j++)
                        {
                            CodeAttributeDeclaration attribute = member.CustomAttributes[j];
                            if (attribute.Name == "System.Xml.Serialization.XmlEnumAttribute")
                                ParseArguments(attribute.Arguments, oGenMember);
                        }
                        oGenClass.aMembers.Add(oGenMember);
                    }
                }
                else
                {
                    for (int i = 0; i < type.Members.Count; ++i)
                    {
                        CodeTypeMember member = type.Members[i];
                        //CodeMemberField пропускаем
                        CodeMemberProperty codeMemberProperty = member as CodeMemberProperty;
                        if (codeMemberProperty != null)
                        {
                            GenMemberPivot oNewGenMember = PreProcessProperty(aGenClasses, codeMemberProperty, oGenClass, ref nItemsElementName);
                            if (null != oNewGenMember)
                                oGenClass.aMembers.Add(oNewGenMember);
                        }
                    }
                }
            }
            return oGenClass;
        }
        GenMemberPivot PreProcessProperty(List<GenClassPivot> aGenClasses, CodeMemberProperty codeMemberProperty, GenClassPivot oGenClass, ref int nItemsElementName)
        {
            GenMemberPivot oGenMember = new GenMemberPivot(codeMemberProperty.Name);
            bool bIgnore = false;
            InitMemberType(oGenMember, codeMemberProperty.Type.BaseType);
            if (null != codeMemberProperty.Type.ArrayElementType)
            {
                oGenMember.nArrayRank = codeMemberProperty.Type.ArrayElementType.ArrayRank;
            }
            bool bXmlElementAttribute = false;
            List<GenMemberPivot> aTempMemebers = new List<GenMemberPivot>();
            for (int i = 0; i < codeMemberProperty.CustomAttributes.Count; i++)
            {
                CodeAttributeDeclaration attribute = codeMemberProperty.CustomAttributes[i];
                if (attribute.Name == "System.Xml.Serialization.XmlAttributeAttribute")
                {
                    oGenMember.bQualified = false;
                    oGenMember.bIsAttribute = true;
                    ParseArguments(attribute.Arguments, oGenMember);
                    //todo могут быть повторы имен атрибутов и child nodes.
                }
                else if (attribute.Name == "System.ComponentModel.DefaultValueAttribute")
                {
                    if (attribute.Arguments.Count > 0)
                    {
                        CodeExpression oCodeExpression = attribute.Arguments[attribute.Arguments.Count - 1].Value;
                        //todo other
                        if (oCodeExpression is CodePrimitiveExpression)
                            oGenMember.sDefAttribute = ((oCodeExpression as CodePrimitiveExpression)).Value.ToString();
                        else if (oCodeExpression is CodeFieldReferenceExpression)
                            oGenMember.sDefAttribute = ((oCodeExpression as CodeFieldReferenceExpression)).FieldName;
                    }
                }
                else if (attribute.Name == "System.Xml.Serialization.XmlIgnoreAttribute")
                    bIgnore = true;
                else if (attribute.Name == "System.Xml.Serialization.XmlElementAttribute")
                {
                    bXmlElementAttribute = true;
                    GenMemberPivot oTemp = new GenMemberPivot(null);
                    ParseArguments(attribute.Arguments, oTemp);
                    aTempMemebers.Add(oTemp);
                }
                else if (attribute.Name == "System.Xml.Serialization.XmlArrayItemAttribute")
                {
                    GenMemberPivot oTemp = new GenMemberPivot(null);
                    ParseArguments(attribute.Arguments, oTemp);
                    aTempMemebers.Add(oTemp);
                }
                else if (attribute.Name == "System.Xml.Serialization.XmlArrayAttribute")
                {
                    ParseArguments(attribute.Arguments, oGenMember);
                }
                //todo не всегда прописан
                //else if (attribute.Name == "System.Xml.Serialization.XmlChoiceIdentifierAttribute")
                //{
                //    if (attribute.Arguments.Count > 0)
                //    {
                //        CodePrimitiveExpression oPrimitiveExpression = attribute.Arguments[0].Value as CodePrimitiveExpression;
                //        oGenMember.sChoiceIdentifier = oPrimitiveExpression.Value.ToString();
                //    }
                //}
            }
            if (bIgnore)
                return null;
            else
            {
                if (aTempMemebers.Count > 0)
                {
                    if (1 == aTempMemebers.Count)
                    {
                        GenMemberPivot TempMember = aTempMemebers[0];
                        TempMember.merge(oGenMember);
                        TempMember.nArrayRank = null;
                    }
                        oGenMember.aArrayTypes = aTempMemebers;
                        if (bXmlElementAttribute)
                            oGenMember.bIsArrayTypesHidden = true;
                        else
                            oGenMember.bIsArrayTypesHidden = false;
                }
                else
                {
                    oGenMember.nArrayRank = null;
                }
                oGenMember.completeDefaults();
                return oGenMember;
            }
        }
        void ParseArguments(CodeAttributeArgumentCollection oArguments, GenMemberPivot oGenMember)
        {
            CodePrimitiveExpression oPrimitiveExpression = null;
            CodeTypeOfExpression oTypeOfExpression = null;
            string sNamespace = null;
            bool? bForm = null;
            foreach (CodeAttributeArgument argument in oArguments)
            {
                if ("" == argument.Name)
                {
                    if (argument.Value is CodePrimitiveExpression)
                        oPrimitiveExpression = argument.Value as CodePrimitiveExpression;
                    else if (argument.Value is CodeTypeOfExpression)
                        oTypeOfExpression = argument.Value as CodeTypeOfExpression;
                }
                else if ("Namespace" == argument.Name)
                    sNamespace = ((CodePrimitiveExpression)argument.Value).Value.ToString();
                else if ("Form" == argument.Name)
                {
                    string sValue = ((CodeFieldReferenceExpression)argument.Value).FieldName;
                    if ("Qualified" == sValue)
                        bForm = true;
                    else if ("Unqualified" == sValue)
                        bForm = false;
                }
            }
            if (null != oPrimitiveExpression)
                oGenMember.sName = oPrimitiveExpression.Value.ToString();
            if (null != oTypeOfExpression)
                InitMemberType(oGenMember, oTypeOfExpression.Type.BaseType);
            if (null != sNamespace)
                oGenMember.sNamespace = sNamespace;
            if (bForm.HasValue)
                oGenMember.bQualified = bForm.Value;
        }
        void InitMemberType(GenMemberPivot oGenMember, string sBaseType)
        {
            if (-1 != sBaseType.IndexOf("System."))
            {
                oGenMember.oSystemType = Type.GetType(sBaseType);
                if (null == oGenMember.oSystemType)
                    oGenMember.oSystemType = typeof(string);
            }
            else
                oGenMember.sType = sBaseType;
        }
    }
}
