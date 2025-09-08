#ifndef LEMON_PARSER
#define LEMON_PARSER

#include <vector>
#include <stdint.h>
#include <string>
#include <fstream>
#include <typeinfo>
#include <any>

template<typename T>
concept Lemon_IsAClass = std::is_class_v<T> && requires(T obj) {
    { obj.LemonLengthRead() } -> std::same_as<uint32_t>;
    { obj.LemonRead(0) } -> std::same_as<std::any>; // Added (0) argument!
};

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

            void AddSeparator(const char* seperatorText = nullptr);

            void SwitchMode();
        private:
            bool m_newLine = true;
            std::string m_msg;
            const char* m_path;
            uint32_t m_dent = 0;
            std::string m_bTag = "";
        };

        LemonParserObject* create(const char* location);

        
        template <typename T>
        inline void LemonParserObject::AddItem(const char* name, T value)
        {
            m_msg.append(4 * m_dent, ' ');
            m_msg.append("[");
            m_msg.append(name);
            m_msg.append("] => ");
        
            if constexpr (std::is_fundamental_v<T>) {
                if constexpr (std::is_same_v<T, bool>) {
                    m_msg.append(value ? "true" : "false");
                } else if constexpr (std::is_same_v<T, int> ||
                                     std::is_same_v<T, float> ||
                                     std::is_same_v<T, double>) {
                    m_msg.append(std::to_string(value));
                    if constexpr (std::is_same_v<T, float>) {
                        m_msg.append("f");
                    } else if constexpr (std::is_same_v<T, double>) {
                        m_msg.append("d");
                    }
                } else if constexpr (std::is_same_v<T, char>) {
                    m_msg.append("'");
                    m_msg += value;
                    m_msg.append("'");
                }
                
            } else if constexpr (Lemon_IsAClass<T>) {
                uint32_t repeatLength = value.LemonLengthRead();
            
                std::string classValues("(");
            
                for (uint32_t i = 0; i < repeatLength + 1; ++i) {
                    std::any val = value.LemonRead(i);
                
                    if (val.type() == typeid(int)) {
                        classValues.append(std::to_string(std::any_cast<int>(val)));
                    } else if (val.type() == typeid(double)) {
                        classValues.append(std::to_string(std::any_cast<double>(val)) + "d");
                    } else if (val.type() == typeid(bool)) {
                        classValues.append(std::any_cast<bool>(val) ? "true" : "false");
                    } else if (val.type() == typeid(std::string)) {
                        classValues.append("\"" + std::any_cast<std::string>(val) + "\"");
                    } else {
                        classValues.append("<unknown>");
                    }
                
                    if (i < repeatLength - 1)
                        classValues.append(", ");
                }
            
                classValues += ")";
                m_msg.append(classValues);
            } else {
                if constexpr (std::is_convertible_v<T, std::string>) {
                    m_msg += '"';
                    m_msg.append(value);
                    m_msg += '"';
                } else {
                    m_msg.append("<unsupported type>");
                }
            }
        
            if (m_newLine) {
                m_msg.append("\n");
            }
        }

    };
}

#endif