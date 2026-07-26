import pygame
import sys
from pygame.locals import *
from OpenGL.GL import *
from OpenGL.GLU import *

# 1. Defini 8 Pwen Kowòdone yon Kib nan espas 3D (X, Y, Z Matrices)
vertices = (
    ( 1, -1, -1), ( 1,  1, -1), (-1,  1, -1), (-1, -1, -1),
    ( 1, -1,  1), ( 1,  1,  1), (-1, -1,  1), (-1,  1,  1)
)

# 2. Liy ki konekte pwen yo pou fòme bwat la
edges = (
    (0,1), (0,3), (0,4), (2,1), (2,3), (2,7),
    (6,3), (6,4), (6,7), (5,1), (5,4), (5,7)
)

# 3. Koulè Neon Cyberpunk pou 6 fas kib la (RGB format)
colors = (
    (0, 210, 255),  # Neon Cyan
    (220, 50, 50),  # Neon Wouj
    (0, 255, 128),  # Neon Vèt
    (230, 180, 40), # Neon Lò
    (150, 0, 255),  # Cyberpunk Purple
    (255, 0, 150)   # Hot Pink
)

# 4. Sifas (Faces) kib la pou l ka ranpli ak vrè koulè solid, pa sèlman fil liy
surfaces = (
    (0,1,2,3), (3,2,7,6), (6,7,5,4), (4,5,1,0), (1,5,7,2), (4,0,3,6)
)

def Desine_Kib_3D():
    # Desine fas yo ak gwo koulè solid k ap klere
    glBegin(GL_QUADS)
    for i, surface in enumerate(surfaces):
        glColor3fv(colors[i % len(colors)])
        for vertex in surface:
            glVertex3fv(vertices[vertex])
    glEnd()

    # Desine liy fil nwa yo sou bòb bwat la pou l parèt byen pwòp
    glBegin(GL_LINES)
    glColor3fv((10, 10, 15)) # Koulè liy yo
    for edge in edges:
        for vertex in edge:
            glVertex3fv(vertices[vertex])
    glEnd()

def main():
    pygame.init()
    LÈT, WOTÈ = 800, 600
    # DOUBLEBUF ak OPENGL mande kòd la pou l kouri sou kat grafik la dirèkteman
    pygame.display.set_mode((LÈT, WOTÈ), DOUBLEBUF | OPENGL)
    pygame.display.set_caption("NAYDER ENGINE v0.0.20 - Real 3D Renderer Core")
    clock = pygame.time.Clock()

    # Konfigirasyon Lantiy Kamera 3D a (Field of View: 45, Aspect Ratio, Perspective clipping)
    gluPerspective(45, (LÈT / WOTÈ), 0.1, 50.0)
    
    # Deplase kamera a bak pa 5 mèt pou n ka wè tout kib la (Z axis movement)
    glTranslatef(0.0, 0.0, -5.0)

    print("\n=======================================================")
    print("    [NAYDER ENGINE v0.0.20] - VRÈ MATRIX GRAPHICS 3D")
    print("=======================================================")
    print(" [*] Modil 5: Real 3D Window   -> ✅ DEBLOKE NÈT!")
    print(" [*] Modil 6: Renderer Upgrade -> ✅ OPENGL PIPELINE ACTIVE")
    print("-------------------------------------------------------")

    # Game Loop grafik la
    while True:
        for event in pygame.event.get():
            if event.type == pygame.QUIT:
                pygame.quit()
                sys.exit()

        # 5. MATRIS VIRE (3D Rotation Core System - vire sou 3 aks X, Y, Z anmenmtan)
        glRotatef(1, 1, 1, 0.5)
        
        # Netwaye ekran an ak memwa pwofondè z-buffer a
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT)
        glEnable(GL_DEPTH_TEST) # Anpeche fas ki dèyè yo parèt devan

        # Rele gwo fonksyon kreyasyon an
        Desine_Kib_3D()

        pygame.display.flip()
        clock.tick(107) # Lock sou 107 FPS taktik motè a

if __name__ == "__main__":
    main()
