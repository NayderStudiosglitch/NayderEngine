import pygame
import sys
from pygame.locals import *
from OpenGL.GL import *
from OpenGL.GLU import *

# 1. Kowòdone Kib 3D
vertices = (
    ( 1, -1, -1), ( 1,  1, -1), (-1,  1, -1), (-1, -1, -1),
    ( 1, -1,  1), ( 1,  1,  1), (-1, -1,  1), (-1,  1,  1)
)

edges = (
    (0,1), (0,3), (0,4), (2,1), (2,3), (2,7),
    (6,3), (6,4), (6,7), (5,1), (5,4), (5,7)
)

colors = (
    (0, 210, 255),  # Neon Cyan
    (220, 50, 50),  # Neon Wouj
    (0, 255, 128),  # Neon Vèt
    (230, 180, 40), # Neon Lò
    (150, 0, 255),  # Cyberpunk Purple
    (255, 0, 150)   # Hot Pink
)

surfaces = (
    (0,1,2,3), (3,2,7,6), (6,7,5,4), (4,5,1,0), (1,5,7,2), (4,0,3,6)
)

def Desine_Kib_3D():
    glBegin(GL_QUADS)
    for i, surface in enumerate(surfaces):
        glColor3fv(colors[i % len(colors)])
        for vertex in surface:
            glVertex3fv(vertices[vertex])
    glEnd()

    glBegin(GL_LINES)
    glColor3fv((10, 10, 15))
    for edge in edges:
        for vertex in edge:
            glVertex3fv(vertices[vertex])
    glEnd()

def main():
    pygame.init()
    LÈT, WOTÈ = 800, 600
    pygame.display.set_mode((LÈT, WOTÈ), DOUBLEBUF | OPENGL)
    pygame.display.set_caption("NAYDER ENGINE v0.0.21 - 3D Input Camera Matrix")
    clock = pygame.time.Clock()

    gluPerspective(45, (LÈT / WOTÈ), 0.1, 50.0)
    
    # Variab Pozisyon Kamera 3D (X, Y, Z Axis)
    cam_x = 0.0
    cam_y = 0.0
    cam_z = -5.0  # Kòmanse nan 5 mèt dèyè

    print("\n=======================================================")
    print("    [NAYDER ENGINE v0.0.21] - 3D INPUT & CAMERA MATRIX")
    print("=======================================================")
    print(" [*] Modil 4: Input System    -> ✅ UPGRADED TO 3D MATRIX")
    print(" [*] Modil 5: 3D Camera Focus -> ✅ ACTIVE")
    print("-------------------------------------------------------")
    print(" KONTWÒL YON REYÈL (AKSYON KLAVYE):")
    print("  -> Peze W / S pou Zoom In / Zoom Out Kamera a (Z-Axis)")
    print("  -> Peze FLÈCH YO pou w deplase kib la sou kote (X/Y-Axis)")
    print("-------------------------------------------------------")

    while True:
        for event in pygame.event.get():
            if event.type == pygame.QUIT:
                pygame.quit()
                sys.exit()

        # 2. SISTÈM KOUTE KLAVYE 3D (Real-Time Hardware Input Pipeline)
        keys = pygame.key.get_pressed()
        
        # Jere Zoom Z-Axis
        if keys[pygame.K_w]: cam_z += 0.1   # Pwoche pi pre
        if keys[pygame.K_s]: cam_z -= 0.1   # Rale dèyè
        
        # Jere Deplasman X ak Y Axis
        if keys[pygame.K_LEFT]:  cam_x += 0.05
        if keys[pygame.K_RIGHT]: cam_x -= 0.05
        if keys[pygame.K_UP]:    cam_y -= 0.05
        if keys[pygame.K_DOWN]:  cam_y += 0.05

        # Sove Matris la epi re-kalkile pozisyon an an tan reyèl
        glLoadIdentity()
        gluPerspective(45, (LÈT / WOTÈ), 0.1, 50.0)
        glTranslatef(cam_x, cam_y, cam_z)

        # Matris vire dousman nan background nan
        glRotatef(1, 1, 1, 0.5)
        
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT)
        glEnable(GL_DEPTH_TEST)

        Desine_Kib_3D()

        pygame.display.flip()
        clock.tick(107)

if __name__ == "__main__":
    main()
