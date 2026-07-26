class AnimationState:
    def __init__(self, state_name, total_frames):
        self.state_name = state_name
        self.total_frames = total_frames
        self.current_frame = 0

    def step_frame(self):
        self.current_frame = (self.current_frame + 1) % self.total_frames
        return self.current_frame

class NayderAnimationEngine:
    def __init__(self):
        print("\n=======================================================")
        print("     [NAYDER ENGINE v0.0.11] - SKELETAL ANIMATION CORE")
        print("=======================================================")
        self.blend_weight = 0.0  # 0.0 = Idle nèt, 1.0 = Run nèt
        self.active_state = "IDLE"
        self.states = {
            "IDLE": AnimationState("Idle_Pose", 30),
            "RUN": AnimationState("Run_Cycle", 24),
            "AIM_DOWN_SIGHTS": AnimationState("ADS_Pose", 10)
        }

    def update_animation_blend(self, current_speed, is_aiming):
        print(f" -> [ANIMATION MATRIX]: Ap kalkile mouvman Sòlda a...")
        
        # Lojik Blending pwofesyonèl selon vitès ak aksyon jwè a
        if is_aiming:
            self.active_state = "AIM_DOWN_SIGHTS"
            self.blend_weight = 0.0
            print("    [ADS]: Sòlda a ap vize ak zam nan. Bloke pozisyon bra an liy.")
        elif current_speed > 0:
            self.active_state = "RUN"
            self.blend_weight = min(1.0, current_speed / 7.0)
            print(f"    [BLEND]: Sòlda a ap kouri. Blend Weight: {self.blend_weight:.2f} -> Chaje Run_Cycle.")
        else:
            self.active_state = "IDLE"
            self.blend_weight = 0.0
            print("    [IDLE]: Sòlda a kanpe fiks. Loading breathing bone matrix.")

        # Prann ti ankadreman (frame) an tan reyèl
        frame = self.states[self.active_state].step_frame()
        print(f" ✅ STATUS: Frame {frame}/{self.states[self.active_state].total_frames} anrejistre pou GPU Skeletal Mesh la.")
        return self.active_state

if __name__ == "__main__":
    # Teste pipeline animasyon an lokalman
    anim_core = NayderAnimationEngine()
    print("-------------------------------------------------------")
    
    # Simulation 1: Sòlda a kanpe nan baz la (Idle)
    anim_core.update_animation_blend(current_speed=0.0, is_aiming=False)
    print("-------------------------------------------------------")
    
    # Simulation 2: Sòlda a kòmanse kouri pou l al pran yon zòn (Run)
    anim_core.update_animation_blend(current_speed=6.5, is_aiming=False)
    print("-------------------------------------------------------")
    
    # Simulation 3: Sòlda a bloke pozisyon l pou l tire yon lènmi (ADS)
    anim_core.update_animation_blend(current_speed=1.2, is_aiming=True)
    print("=======================================================")
