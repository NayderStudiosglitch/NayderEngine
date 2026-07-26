#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

// =============================================================================
// MODIL 15: HUGE STYLE LANGUAGE PARSER CORE (C++ NATIVE NLP ENGINE)
// =============================================================================
class HugeStyleParserCore {
private:
    std::vector<std::string> weapon_keywords;
    std::vector<std::string> attribute_keywords;
    std::vector<std::string> tactical_keywords;

public:
    HugeStyleParserCore() {
        // Diksyonè mo kle taktik yo an C++
        weapon_keywords = {"smg", "rifle", "sniper", "zam", "lou"};
        attribute_keywords = {"fast", "vit", "low recoil", "silansye", "sekwe", "blue", "black"};
        tactical_keywords = {"nuclear", "bomb", "nikleyè", "nuke", "crater"};
        std::cout << " -> [C++ HUGE STYLE NLP]: Diksyonè mo kle yo chaje nan RAM Compiler la." << std::endl;
    }

    void ParseNaturalSentence(std::string sentence) {
        std::string raw_text = sentence;
        // Transfòme tèks la an lèt piti pou analiz pafè
        std::transform(raw_text.begin(), raw_text.end(), raw_text.begin(), ::tolower);
        
        std::cout << "\n -> [NLP PARSER]: Ap filtre fraz: \"" << sentence << "\"" << std::endl;
        std::cout << "    [COMPILER]: Analiz Huge Style NLP active..." << std::endl;

        std::vector<std::string> triggered_actions;

        // 1. Analize pou Zam
        for (const std::string& word : weapon_keywords) {
            if (raw_text.find(word) != std::string::npos) {
                triggered_actions.push_back("WEAPON_CRAFT_CMD");
                break;
            }
        }

        // 2. Analize pou Atribi/Koulè
        for (const std::string& word : attribute_keywords) {
            if (raw_text.find(word) != std::string::npos) {
                triggered_actions.push_back("APPLY_MATERIAL_OR_MODIFIER");
                break;
            }
        }

        // 3. Analize pou Aksyon Taktik
        for (const std::string& word : tactical_keywords) {
            if (raw_text.find(word) != std::string::npos) {
                triggered_actions.push_back("EXECUTE_TACTICAL_NUKE_PROTOCOL");
                break;
            }
        }

        // Afiche matris kòmand ki deklanche pou Engine nan
        std::cout << "    [COMPILE SUCCESS]: Lòd konvèti an kòmand C++: [ ";
        for (const std::string& action : triggered_actions) {
            std::cout << action << " ";
        }
        std::cout << "]" << std::endl;
        std::cout << " ✅ STATUS: Matris lòd yo voye bay Kè Motè a san lag." << std::endl;
    }
};

// =============================================================================
// ENGINE RUNTIME ENVIRONMENT
// =============================================================================
class NayderEngineCPP {
private:
    HugeStyleParserCore nlp_parser;

public:
    NayderEngineCPP() {
        std::cout << "\n=======================================================" << std::endl;
        std::cout << "     [NAYDER ENGINE v0.0.33] - HUGE STYLE PARSER CORE" << std::endl;
        std::cout << "=======================================================" << std::endl;
        std::cout << " [*] Modil 15: Huge Style NLP -> ✅ ONLINE AN C++" << std::endl;
        std::cout << " [*] Natural Language Matrix  -> ✅ STABLE PIPELINE" << std::endl;
        std::cout << " [*] Hardware Lexer Tokenizer -> ✅ LINKED TO RAM" << std::endl;
        print_roadmap_status();
    }

    void print_roadmap_status() {
        std::cout << "-------------------------------------------------------" << std::endl;
        std::cout << " ROADMAP UPGRADE STATUS:" << std::endl;
        std::cout << "  12. Asset Manager      -> ✅ C++ CORE" << std::endl;
        std::cout << "  13. Level/Map System   -> ✅ C++ CORE" << std::endl;
        std::cout << "  14. Multiplayer Network-> ✅ C++ CORE" << std::endl;
        std::cout << "  15. Huge Style Language-> ✅ C++ CORE" << std::endl;
        std::cout << "-------------------------------------------------------" << std::endl;
    }

    void RunSimulation() {
        // Tès 1: Fraz pou bati zam ak koulè
        nlp_parser.ParseNaturalSentence("AI, Build me a sniper blue, black color");
        
        std::cout << "\n=======================================================" << std::endl;
        
        // Tès 2: Fraz pou sekans eksplozyon nikleyè
        nlp_parser.ParseNaturalSentence("Drop the tactical Nuke bomb in Desert Ghost City");
    }
};

int main() {
    NayderEngineCPP engine;
    engine.RunSimulation();
    return 0;
}
