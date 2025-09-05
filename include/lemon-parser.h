#ifndef LEMON_PARSER
#define LEMON_PARSER

#include <vector>
#include <stdint.h>
#include <string>
#include <fstream>
#include <typeinfo>

namespace lemon {
    namespace parser {

        class LemonParserObject
        {
        public:
            LemonParserObject(const char * path);
            ~LemonParserObject();
        public:
            void AddVariable(const char* text);
            template<typename T>
            void AddItem(const char* name, T value);
            void PreBodyTag(const char* tag);
            void AddBody();
            void EndBody();
            void SwitchMode();
        private:
            bool m_newLine = true;
            std::string m_msg;
            const char* m_path;
            uint32_t m_dent = 0;
            std::string m_bTag = "";

            template <typename T>
            bool m_isSimple() {
                if constexpr (std::is_fundamental<T>()) {
                    return true;
                } else {
                    return false;
                }
            };
        };

        LemonParserObject* create(const char* location);

        template <typename T>
        inline void LemonParserObject::AddItem(const char *name, T value)
        {
            m_msg.append(4 * m_dent,' ');
            m_msg.append("[");
            m_msg.append(name);
            m_msg.append("]");
            m_msg.append(" => ");

            if (m_isSimple<T>()) {
                if (typeid(value) == typeid(bool)) {
                    m_msg.append(value ? "true" : "false");
                } else if (typeid(value) == typeid(int) || typeid(value) == typeid(float) || typeid(value) == typeid(double))
                {
                    m_msg.append(std::to_string(value));
                    if (typeid(value) == typeid(float)) {
                        m_msg.append("f");
                    } else if (typeid(value) == typeid(double))
                    {
                        m_msg.append("d");
                    }

                    if (m_newLine) {
                        m_msg.append("\n");
                    }
                    
                }else {
                    if (typeid(value) == typeid(char)) {
                        m_msg + value;
                    } else {
                        m_msg.append(value);
                    }
                }
                
            }
        }
    };
}

#endif