#include <iostream>
#include <string>
#include <map>
#include <algorithm>

// =============================================================================
// MODIL: MULTI-LANGUAGE LOCALIZATION CORE (8 LANGS MATRIX)
// =============================================================================
class NayderLocalizationSystem {
private:
    // Diksyonè 2D k ap kenbe tout tradiksyon yo pou tout 8 lang yo nèt
    std::map<std::string, std::map<std::string, std::string>> language_matrix;

public:
    NayderLocalizationSystem() {
        // 1. HAITIAN CREOLE
        language_matrix["ht"]["nuke_ready"] = "ALÈT NIKLEYÈ: Bonm Nikleyè a pare pou l detwi tout lènmi!";
        language_matrix["ht"]["welcome"] = "Byenveni sòlda nan NAYDER ENGINE. Pwogram nan sou li.";

        // 2. ENGLISH
        language_matrix["en"]["nuke_ready"] = "NUCLEAR ALERT: Tactical Nuke is ready to destroy all enemies!";
        language_matrix["en"]["welcome"] = "Welcome soldier to NAYDER ENGINE. Core systems online.";

        // 3. FRENCH
        language_matrix["fr"]["nuke_ready"] = "ALERTE NUCLÉAIRE: La bombe nucléaire est prête à tout détruire!";
        language_matrix["fr"]["welcome"] = "Bienvenue soldat dans NAYDER ENGINE. Systèmes en ligne.";

        // 4. SPANISH
        language_matrix["es"]["nuke_ready"] = "ALERTA NUCLEAR: ¡La bomba nuclear está lista para destruir todo!";
        language_matrix["es"]["welcome"] = "Bienvenido soldado a NAYDER ENGINE. Sistemas en línea.";

        // 5. PORTUGUESE
        language_matrix["pt"]["nuke_ready"] = "ALERTA NUCLEAR: A bomba nuclear está pronta para destruir tudo!";
        language_matrix["pt"]["welcome"] = "Bem-vindo soldado ao NAYDER ENGINE. Sistemas online.";

        // 6. RUSSIAN
        language_matrix["ru"]["nuke_ready"] = "ЯДЕРНАЯ ТРЕВОГА: Тактическая ядерная бомба готова к детонации!";
        language_matrix["ru"]["welcome"] = "Добро пожаловать, солдат, в NAYDER ENGINE. Системы активны.";

        // 7. CHINESE
        language_matrix["zh"]["nuke_ready"] = "核警报：战术核弹已准备就绪，即将摧毁所有敌人！";
        language_matrix["zh"]["welcome"] = "欢迎士兵来到 NAYDER 引擎。核心系统已上线。";

        // 8. NORTH KOREAN (Chosŏn-gŏ Tonal Style)
        language_matrix["kp"]["nuke_ready"] = "핵경보: 전술핵탄이 모든 원쑤들을 소멸할 준비가 되였습니다!";
        language_matrix["kp"]["welcome"] = "전사여, NAYDER 기지에 들어선것을 환영한다. 체계 가동.";
    }

    void DisplayTranslatedMessage(std::string lang_code, std::string message_key) {
        // Tcheke si lang lan ak mo a egziste nan matris motè a
        if (language_matrix.find(lang_code) != language_matrix.end() && 
            language_matrix[lang_code].find(message_key) != language_matrix[lang_code].end()) {
            
            std::cout << " -> [" << lang_code << " LOGS]: " << language_matrix[lang_code][message_key] << std::endl;
        } else {
            std::cout << " ⚠️ Error: Language code or key not found in localization engine." << std::endl;
        }
    }
};

// =============================================================================
// ENGINE RUNTIME SETUP
// =============================================================================
class NayderEngineCPP {
private:
    NayderLocalizationSystem localization;

public:
    NayderEngineCPP() {
        std::cout << "\n=======================================================" << std::endl;
        std::cout << "     [NAYDER ENGINE v0.0.26] - 8 LANGUAGES SYSTEM CORE" << std::endl;
        std::cout << "=======================================================" << std::endl;
        std::cout << " [*] Global Localization -> ✅ 8 INTERNATIONAL LANGUAGES ONLINE" << std::endl;
        std::cout << " [*] Core Dictionary     -> ✅ STABLE STRING MATRIX LINKED" << std::endl;
        std::cout << "-------------------------------------------------------" << std::endl;
    }

    void TestAllLanguages() {
        std::cout << " -> [LOCALIZATION ENGINE]: Ap verifye apèl sistèm nan tout 8 lang yo:" << std::endl;
        std::cout << "-------------------------------------------------------" << std::endl;
        
        // Kouri tradiksyon mesaj Alèt Nikleyè a nan tout 8 lang yo nèt ale!
        localization.DisplayTranslatedMessage("ht", "nuke_ready");
        localization.DisplayTranslatedMessage("en", "nuke_ready");
        localization.DisplayTranslatedMessage("fr", "nuke_ready");
        localization.DisplayTranslatedMessage("es", "nuke_ready");
        localization.DisplayTranslatedMessage("pt", "nuke_ready");
        localization.DisplayTranslatedMessage("ru", "nuke_ready");
        localization.DisplayTranslatedMessage("zh", "nuke_ready");
        localization.DisplayTranslatedMessage("kp", "nuke_ready");
    }
};

int main() {
    NayderEngineCPP engine;
    engine.TestAllLanguages();
    return 0;
}
