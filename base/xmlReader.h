#ifndef XMLREADER_H_INCLUDED
#define XMLREADER_H_INCLUDED

namespace xml
{
    class xmlDocument
    {
    private:
        xml_document<> document;
        xml_node<> * root;

        ifstream xmlFile;
        stringstream buffer;
        string content;
        string fileName;
    public:
        xmlDocument();
        xmlDocument(string doc);

        xml_node<> * getFirstNode(string nodeName, xml_node<> *Root);
        xml_node<> * getRootNode();

        string getNodeAttribute(xml_node<> *Root, string attributeName);
        void setNodeAttribute(xml_node<> *Root, string attributeName, const char * newValue);

        void flush();
    };

    xmlDocument::xmlDocument(string doc)
    {
        fileName = doc;
        xmlFile.open(doc.c_str());
        buffer << xmlFile.rdbuf();
        xmlFile.close();
        content = buffer.str();
        document.parse<0>(&content[0]);

        root = document.first_node();
    }

    xml_node<> * xmlDocument::getFirstNode(string nodeName, xml_node<> *Root)
    {
        return Root -> first_node(nodeName.c_str());
    }
    xml_node<> * xmlDocument::getRootNode()
    {
        return root;
    }
    string xmlDocument::getNodeAttribute(xml_node<> *Root, string attributeName)
    {
        xml_attribute<> *pAttr = Root -> first_attribute(attributeName.c_str());
        return pAttr -> value();
    }
    void xmlDocument::setNodeAttribute(xml_node<> *Root, string attributeName, const char * newValue)
    {
        Root -> first_attribute(attributeName.c_str()) -> value(newValue);

        string data;
        print(back_inserter(data), document);

        ofstream file;
        file.open(fileName.c_str());
        file << data;
        file.close();
    }

    void xmlDocument::flush()
    {

    }
    xmlDocument * weaponsXML[3];

    xml_node<> *getRootNode(string xmlFile)
    {
        xml_document<> doc;
        std::ifstream file(xmlFile.c_str());
        std::stringstream buffer;
        buffer << file.rdbuf();
        file.close();
        std::string content(buffer.str());
        doc.parse<0>(&content[0]);

        return doc.first_node();
    }

    string getNodeAttribute(xml_node<> *Root, string attributeName)
    {
        xml_attribute<> *pAttr = Root -> first_attribute(attributeName.c_str());
        return pAttr -> value();
    }
}

#endif // XMLREADER_H_INCLUDED
