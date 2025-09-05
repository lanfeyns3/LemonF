#include "include/lemon-parser.h"

namespace lemon {
    namespace parser
    {

        LemonParserObject::LemonParserObject(const char* path)
            : m_path(path)
        {

        }

        LemonParserObject::~LemonParserObject() {
            std::ofstream file(m_path);

            if (!file) {
                return;
            }

            file << m_msg;
            file.close();
        }

        LemonParserObject* create(const char* location) {
            return new LemonParserObject(location);
        }

        void LemonParserObject::SwitchMode() {
            m_newLine =  !m_newLine;
        }

        void LemonParserObject::AddVariable(const char* text) {
            m_msg.append(4 * m_dent,' ');
            m_msg.append("[");
            m_msg.append(text);
            m_msg.append("]");
            if (m_newLine) {
                m_msg.append("\n");
            }
        }

       void LemonParserObject::AddBody() {
            m_msg.append(4 * m_dent,' ');
            if (m_bTag != "") {
                m_msg += '-';
                m_msg.append(m_bTag);
                m_msg += ' ';
                m_bTag = "";
            }
            m_msg.append("{\n");
            m_dent += 1;
       }
       
       void LemonParserObject::EndBody() {
            m_dent -= 1;
            m_msg.append(4 * m_dent,' ');
            m_msg.append("}\n");
       }

       void LemonParserObject::PreBodyTag(const char* tag) {
            m_bTag = tag;
       }
    }
}
