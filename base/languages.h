#ifndef LANGUAGES_H_INCLUDED
#define LANGUAGES_H_INCLUDED

namespace languages
{
    class language
    {
    public:
        string lang = "English";

        string souls = "souls: ";
        string shield = "E.S.: ";
        string healthPoints = "HP: ";
        string hatred = "hatred: ";
    };
    class languageManager
    {
    private:
        vector <language> langs;
        language Current;
    public:
        string lang;
        bool setLang();
        void load(string dir);
        language current();
    };

    void languageManager::load(string dir)
    {
        xml_document<> doc;
        std::ifstream file(dir.c_str());
        std::stringstream buffer;
        buffer << file.rdbuf();
        file.close();
        std::string content(buffer.str());
        doc.parse<0>(&content[0]);

        xml_node<> * tmpNode;
        xml_node<> * Root = doc.first_node();
        xml_node<> * currentNode = Root -> first_node("Lang");

        while(currentNode != NULL)
        {
            language tmp;
            tmp.lang = xml::getNodeAttribute(currentNode, "lang");

            //Dusze
            tmpNode = currentNode -> first_node("souls");
            tmp.souls = xml::getNodeAttribute(tmpNode, "text");
            //-----

            //Tarcza
            tmpNode = currentNode -> first_node("shield");
            tmp.shield = xml::getNodeAttribute(tmpNode, "text");
            //------

            //Punkty życia
            tmpNode = currentNode -> first_node("healthPoints");
            tmp.healthPoints = xml::getNodeAttribute(tmpNode, "text");
            //------------

            //Nienawiść
            tmpNode = currentNode -> first_node("hatred");
            tmp.hatred = xml::getNodeAttribute(tmpNode, "text");
            //---------

            langs.push_back(tmp);

            currentNode = currentNode -> next_sibling();
        }

        currentNode = Root -> first_node("Current");
        lang = xml::getNodeAttribute(currentNode, "lang");
    }

    bool languageManager::setLang()
    {
        for(int i = langs.size() - 1; i >= 0; i--)
        {
            if(langs[i].lang == lang)
            {
                Current = langs[i];
                return true;
            }
        }

        return false;
    }

    language languageManager::current()
    {
        return Current;
    }
}
languages::languageManager languageManager;

#endif
