import re

class HugeStyleLanguageParser:
    def __init__(self):
        print("\n=======================================================")
        print("     [NAYDER ENGINE v0.0.8] - HUGE STYLE NLP PARSER")
        print("=======================================================")
        # Diksyonè mo kle sekirite yo
        self.vocabulary = {
            "weapons": ["smg", "rifle", "sniper", "zam", "lou"],
            "attributes": ["fast", "vit", "low recoil", "silansye", "sekwe"],
            "tactical": ["nuclear", "bomb", "nikleyè", "peze n", "crater"]
        }

    def parse_natural_sentence(self, sentence):
        text = sentence.lower()
        print(f"\n -> [NLP ANALYZER]: Filtre tèks: \"{sentence}\"")
        
        actions = []
        
        # 1. Tcheke si gen lòd pou Zam
        if any(word in text for word in self.vocabulary["weapons"]):
            actions.append("WEAPON_CRAFT_REQUEST")
            
        # 2. Tcheke si gen lòd pou Atribi Zam
        if any(word in text for word in self.vocabulary["attributes"]):
            actions.append("APPLY_WEAPON_MODIFIERS")
            
        # 3. Tcheke si gen lòd pou Aksyon Nikleyè
        if any(word in text for word in self.vocabulary["tactical"]):
            actions.append("EXECUTE_NUCLEAR_SIREN_PROTOCOL")

        print(f"    [COMPILER MATRIX]: Lòd deklanche pou Engine C++ lan: {actions}")
        return actions

if __name__ == "__main__":
    # Teste parser a lokalman
    nlp_engine = HugeStyleLanguageParser()
    print("-------------------------------------------------------")
    
    # Tès 1: Fraz an Angle pou kreye zam
    nlp_engine.parse_natural_sentence("AI, Build me a fast SMG with low recoil")
    print("-------------------------------------------------------")
    
    # Tès 2: Fraz an Kreyòl pou deklanche sekans bonm nan
    nlp_engine.parse_natural_sentence("Peze N pou drop gwo Nuclear bomb nan City Ruins")
    print("=======================================================")
