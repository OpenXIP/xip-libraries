/*
Copyright (c) 2011, Siemens Corporate Research a Division of Siemens Corporation 
All rights reserved.

Licensed under the Apache License, Version 2.0 (the "License");
you may not use this file except in compliance with the License.
You may obtain a copy of the License at

  http://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing, software
distributed under the License is distributed on an "AS IS" BASIS,
WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
See the License for the specific language governing permissions and
limitations under the License.
*/
using System;
using System.Text;
using System.Xml;
using System.Collections;

namespace CustomPropGrid
{
    //small struct for holding the xml attributes name and value
    public struct attr
    {
        public String attrName;
        public String attrVal;
    }

    #region delegates
    /*
     * Delegates for callback's for elements
     * used for reciving notifications/callbacks on the xml parsing.
     */
    public delegate void OnElementStartD(String name, String ns, Int32 numAttribs, Array attribs);
    public delegate void OnElementEndD(String name);
    public delegate void OnElementDataD(String name, String CData);
    #endregion

    public class XmlParser
    {
        public XmlParser()
        {
            reader = null;
            fileName = "";
            m_names = new Stack();
        }

        //returns 1 on success, 0 on failed
        public int Load(String filename)
        {
            fileName = filename;
            reader = new XmlTextReader(fileName);
            
            if (reader == null) return 0; //failed
            return 1;
        }

        //returns 1 on success, 0 on failed
        public int Parse()
        {
            if (reader == null) return 0;

            while (reader.Read())
            {
                switch (reader.NodeType)
                {
                    case XmlNodeType.Element:
                        m_names.Push(reader.Name);
                        //m_name = reader.Name;
                        attr[] attrs = new attr[reader.AttributeCount];
                        if (reader.HasAttributes)
                        {
                            for (int i = 0; i < reader.AttributeCount; i++)
                            {
                                reader.MoveToAttribute(i);
                                attr na = new attr();
                                na.attrName = reader.Name;
                                na.attrVal = reader.Value;
                                attrs[i] = na;
                            }
                        }
                        if (OnElementStart != null) OnElementStart((String)m_names.Peek(), reader.NamespaceURI, reader.AttributeCount, attrs);
                        break;

                    case XmlNodeType.EndElement:
                        m_names.Pop();
                        if (OnElementEnd != null) OnElementEnd(reader.Name);
                        break;

                    case XmlNodeType.Text:
                        String name = (String)m_names.Peek();
                        if (OnElementData != null) OnElementData(name, reader.Value);
                        break;
                }
            }
            return 1;
        }

        #region events
        /*
         * Event declerations for the delegates for the parser callbacks
         */
        public event OnElementStartD OnElementStart;
        public event OnElementEndD OnElementEnd;
        public event OnElementDataD OnElementData;
        #endregion

        #region privates
        //private data
        private String fileName;
        Stack m_names;
        private XmlTextReader reader;
        #endregion
    }
}
