import os

class AssetLoader:
    def __init__(self):
        self.base_assets_path = "Assets"
        self.loaded_models = {}
        self.loaded_audio = {}
        print("\n=======================================================")
        print("     [NAYDER ENGINE v0.0.2] - ASSET LOADER ONLINE")
        print("=======================================================")

    def load_model_3d(self, model_name, file_format):
        # Simulation chajman fichye .fbx oswa .obj menm jan ak UE5
        file_name = f"{model_name}.{file_format}"
        print(f" -> [ASSET LOADER]: Analiz fichye 3D: '{file_name}'...")
        
        # Simulation verifikasyon si katab la egziste
        print(f"    [RAM]: Alokasyon memwa pou moso triyang {model_name}...")
        self.loaded_models[model_name] = f"Engine/Assets/Models/{file_name}"
        print(f" ✅ STATUS: '{file_name}' chaje 100% nan VRAM kat grafik la.")
        return True

    def load_audio_effect(self, audio_name, file_format):
        # Simulation chajman son sirèn oswa bal zam yo
        file_name = f"{audio_name}.{file_format}"
        print(f" -> [ASSET LOADER]: Chaje son: '{file_name}'...")
        self.loaded_audio[audio_name] = f"Engine/Assets/Audio/{file_name}"
        print(f" ✅ STATUS: Son '{file_name}' pare nan sistèm odyo a.")
        return True

if __name__ == "__main__":
    # Teste manadjè a lokalman
    loader = AssetLoader()
    print("-------------------------------------------------------")
    loader.load_model_3d("haitian_soldier_heavy", "fbx")
    loader.load_model_3d("cyberpunk_building_tower", "obj")
    loader.load_model_3d("chopper_military", "fbx")
    print("-------------------------------------------------------")
    loader.load_audio_effect("nuclear_siren_alarm", "wav")
    loader.load_audio_effect("heavy_laser_gunfire", "mp3")
    print("=======================================================")
