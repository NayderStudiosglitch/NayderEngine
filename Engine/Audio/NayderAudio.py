class AudioChannel:
    def __init__(self, channel_id):
        self.channel_id = channel_id
        self.is_playing = False
        self.volume = 1.0

    def set_volume(self, volume_level):
        self.volume = max(0.0, min(1.0, volume_level))
        print(f"    [AUDIO CHANNEL {self.channel_id}]: Volume locked sou {int(self.volume * 100)}%")

class NayderAudioEngine:
    def __init__(self):
        print("\n=======================================================")
        print("         [NAYDER ENGINE v0.0.5] - AUDIO ENGINE ONLINE")
        print("=======================================================")
        self.channels = {1: AudioChannel(1), 2: AudioChannel(2)}
        self.sound_registry = {}

    def register_sound(self, sound_id, file_path):
        # Simulation anrejistreman fichye odyo (.wav/.mp3) nan manadjè a
        print(f" -> [AUDIO REGISTRY]: Map son '{sound_id}' depi {file_path}...")
        self.sound_registry[sound_id] = file_path
        return True

    def play_sound_spatial(self, sound_id, channel_id, looping=False):
        # Simulation deklanchman son an
        if sound_id in self.sound_registry:
            channel = self.channels.get(channel_id)
            if channel:
                channel.is_playing = True
                loop_msg = "an bouk (LOOP)" if looping else "yon sèl fwa"
                print(f" 🚨 [AUDIO PLAYBACK]: Ap jwe '{sound_id}' sou Kanal {channel_id} {loop_msg}...")
                if sound_id == "nuclear_siren":
                    print("    -> SOUND EFFECTS LOGS: (🚨 BEEP... 🚨 BEEP... 🚨 BEEP...)")
                elif sound_id == "ui_hover_beep":
                    print("    -> UI SOUND EFFECTS LOGS: (🎵 Tik! )")
                return True
        print(f" ⚠️ Erè: Son '{sound_id}' pa anrejistre nan motè a.")
        return False

if __name__ == "__main__":
    # Teste modil odyo a lokalman
    audio_core = NayderAudioEngine()
    print("-------------------------------------------------------")
    
    # 1. Anrejistre son yo nan memwa odyo a
    audio_core.register_sound("nuclear_siren", "Assets/Audio/nuclear_siren.wav")
    audio_core.register_sound("ui_hover_beep", "Assets/Audio/ui_click.mp3")
    
    print("-------------------------------------------------------")
    # 2. Tès konfigirasyon volim ak deklanchman son (Aksyon!)
    # -> Simulation ti bip lè sourit pase sou bouton
    audio_core.channels[2].set_volume(0.3)
    audio_core.play_sound_spatial("ui_hover_beep", channel_id=2, looping=False)
    
    print("-------------------------------------------------------")
    # -> Simulation sirèn nikleyè a lè 20,000 pwen rive
    audio_core.channels[1].set_volume(1.0)
    audio_core.play_sound_spatial("nuclear_siren", channel_id=1, looping=True)
    print("=======================================================")
