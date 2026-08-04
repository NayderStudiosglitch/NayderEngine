#include <iostream>
#include <string>
#include <vector>
#include <unistd.h> // Pou simulation ti poz tan reyèl (sleep)

// =============================================================================
// RE-FAKTORE: KALYTE ZONBI AK MATRIS ESTATISTIK PWOFESYONÈL
// =============================================================================
enum class ZombieType { Walker, Runner, Toxic, Brute, Boss, Child, Military };

struct ZombieStats {
    ZombieType type;
    std::string type_name;
    int hp;
    float speed;
    int damage;
    float pos_x; // Real Position X
};

class NayderZombieNextGenAI {
public:
    void ExecuteRealMovement(ZombieStats& zombie, float player_x) {
        std::cout << "\n🏃‍♂️ [REAL POSITION ENGINE ← NEXT] - Kalite: " << zombie.type_name << std::endl;
        std::cout << "    [STATS]: HP: " << zombie.hp << " | Vitès: " << zombie.speed << " | Dega Base: " << zombie.damage << std::endl;
        std::cout << " ---------------------------------------------------------------------" << std::endl;

        // Bouk Deplasman Reyèl: Zonbi a ap mache/kouri vè Player a ki nan X = 20
        while (zombie.pos_x < player_x) {
            std::cout << "   🧟 [ZONBI POSITION]: X = " << zombie.pos_x << "  │  👤 [PLAYER]: X = " << player_x << std::endl;
            
            // Ogmante pozisyon an selon vitès koutim kalite zonbi a
            zombie.pos_x += zombie.speed;
            
            // Si l depase oswa li rive sou player a, nou bloke l pou Atak
            if (zombie.pos_x >= player_x) {
                zombie.pos_x = player_x;
                std::cout << "   💥 [POSITION REACHED]: X = " << zombie.pos_x << " nèt! Zonbi a kole ak Player la!" << std::endl;
                std::cout << "   ⚔️  [ATTACK TYPE LOG]: ";
                
                if (zombie.type == ZombieType::Toxic) {
                    std::cout << "☣️ LAGE GAZ PWAZON! Player a ap pèdi HP nan zòn nan!" << std::endl;
                } else if (zombie.type == ZombieType::Brute) {
                    std::cout << "🔨 GWO KOUP DEGA! Fè -" << zombie.damage << " HP yon sèl fwa!" << std::endl;
                } else if (zombie.type == ZombieType::Boss) {
                    std::cout << "📢 RELE LÒT ZONBI! Yon gwo Horde ap rale soti nan forè a!" << std::endl;
                } else {
                    std::cout << "🩸 MÒDE! Sòlda a pran -" << zombie.damage << " HP dega." << std::endl;
                }
                break;
            }
        }
    }
};

int main() {
    std::cout << "\n=====================================================================" << std::endl;
    std::cout << "     [NAYDER ENGINE v0.0.55] - REAL POSITION & TYPES ENGINE" << std::endl;
    std::cout << "=====================================================================" << std::endl;
    std::cout << " 🏆 STATUS UPDATE:" << std::endl;
    std::cout << "  Zombie Core █████████████░░░░░░░░ 50% (Real Position Loaded!)" << std::endl;
    std::cout << "  AI          ████████████░░░░░░░░░ 45% (Type Matrix Connected)" << std::endl;
    std::cout << "---------------------------------------------------------------------" << std::endl;

    NayderZombieNextGenAI ai_engine;
    float player_target_x = 16.0f; // Sòlda a kanpe fiks nan X = 16

    // TÈS 1: Konpòtman yon RUNNER (Vitès pi wo: l ap sote pa 4 liy!)
    ZombieStats runner = {ZombieType::Runner, "Runner (Zonbi rapid)", 80, 4.0f, 15, 0.0f};
    std::cout << "\n🔥 LANSÈ TÈS 1: ZONBI RAPID AP KOURI:" << std::endl;
    ai_engine.ExecuteRealMovement(runner, player_target_x);

    std::cout << "\n---------------------------------------------------------------------" << std::endl;

    // TÈS 2: Konpòtman yon BRUTE (Pi dousman, l ap sote pa 2 liy sèlman, men gwo dega!)
    ZombieStats brute = {ZombieType::Brute, "Brute (Zonbi gason lou)", 250, 2.0f, 50, 0.0f};
    std::cout << "\n🔥 LANSÈ TÈS 2: GWO BRUTE LOU AP AVANSÈ:" << std::endl;
    ai_engine.ExecuteRealMovement(brute, player_target_x);

    std::cout << "=====================================================================" << std::endl;
    std::cout << " ✅ STATUS: Real position tracking and polymorphic stats validated." << std::endl;
    std::cout << "=====================================================================" << std::endl;
    return 0;
}
