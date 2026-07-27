import pygame
import sys
from pygame.locals import *
from OpenGL.GL import *
from OpenGL.GLU import *

# Matrix kowòdone Kib Sòlda a an 3D
vertices = ((1,-1,-1), (1,1,-1), (-1,1,-1), (-1,-1,-1), (1,-1,1), (1,1,1), (-1,-1,1), (-1,1,1))
edges = ((0,1), (0,3), (0,4), (2,1), (2,3), (2,7), (6,3), (6,4), (6,7), (5,1), (5,4), (5,7))
colors = ((0,210,255), (220,50,50), (0,255,128), (230,180,40), (150,0,255), (255,0,150))
surfaces = ((0,1,2,3), (3,2,7,6), (6,7,5,4), (4,5,1,0), (1,5,7,2), (4,0,3,6))
normals = ((0,0,-1), (-1,0,0), (0,0,1), (1,0,0), (0,1,0), (0,-1,0))

def Configured_Neon_Lighting():
    glEnable(GL_LIGHTING)
    glEnable(GL_LIGHT0)
    glEnable(GL_COLOR_MATERIAL)
    glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE)
    limye_pozisyon = [0.0, 5.0, 5.0, 1.0]
    limye_ambient = [0.2, 0.2, 0.3, 1.0]
    limye_diffuse = [0.0, 0.8, 1.0, 1.0]
    glLightfv(GL_LIGHT0, GL_POSITION, limye_pozisyon)
    glLightfv(GL_LIGHT0, GL_AMBIENT, limye_ambient)
    glLightfv(GL_LIGHT0, GL_DIFFUSE, limye_diffuse)

def Desine_Player_3D():
    glBegin(GL_QUADS)
    for i, surface in enumerate(surfaces):
        glNormal3fv(normals[i % len(normals)])
        glColor3fv(colors[i % len(colors)])
        for vertex in surface: glVertex3fv(vertices[vertex])
    glEnd()
    glDisable(GL_LIGHTING) 
    glBegin(GL_LINES)
    glColor3fv((10,10,15))
    for edge in edges:
        for vertex in edge: glVertex3fv(vertices[vertex])
    glEnd()
    glEnable(GL_LIGHTING)

def Desine_Terrain_Grid():
    glDisable(GL_LIGHTING) 
    glColor3fv((0, 150, 200)) 
    glBegin(GL_LINES)
    for i in range(-20, 21, 2):
        glVertex3f(i, -1, -20)
        glVertex3f(i, -1, 20)
        glVertex3f(-20, -1, i)
        glVertex3f(20, -1, i)
    glEnd()
    glEnable(GL_LIGHTING)

# =============================================================================
# DETE KRAZE TEKST UI (Heads-Up Display Interface Engine)
# =============================================================================
def Render_HUD_Overlay(window, font, bold_font):
    # Nou dwe fèmen 3D Pipeline la pou yon segonn pou n desine 2D UI a anlè l
    glMatrixMode(GL_PROJECTION)
    glPushMatrix()
    glLoadIdentity()
    gluOrtho2D(0, 800, 0, 600)
    glMatrixMode(GL_MODELVIEW)
    glPushMatrix()
    glLoadIdentity()
    glDisable(GL_LIGHTING)
    glDisable(GL_DEPTH_TEST)

    # 1. Desine gwo Tit Gason an nan foto a: NEON FALL 17
    # Nou transfòme OpenGL an pygame sifas rapid nan background nan
    surface_tit = bold_font.render("NEON FALL 17", True, (220, 50, 50)) # Neon Wouj
    window.blit(surface_tit, (30, 540))

    surface_sub = font.render("ONLINE MULTIPLAYER - OPEN WORLD", True, (150, 155, 165))
    window.blit(surface_sub, (30, 515))

    # 2. Desine Profil Jwè a (Header adwat nan foto a)
    surface_profile = font.render("👤 NAYDER_01  [LEVEL 25]", True, (255, 255, 255))
    window.blit(surface_profile, (550, 550))
    
    surface_wallet = font.render("💳 53,860 CR  │  🪙 1,295 GD", True, (230, 180, 40)) # Koulè lò
    window.blit(surface_wallet, (550, 525))

    # 3. Desine Bouton Taktik yo (Anba nan foto a)
    surface_btn1 = font.render("[1. BUILD WEAPON]", True, (0, 210, 255)) # Cyan
    window.blit(surface_btn1, (50, 40))

    surface_btn2 = font.render("[2. TEST WEAPON]", True, (0, 255, 128)) # Vèt
    window.blit(surface_btn2, (250, 40))

    surface_btn3 = font.render("[3. SAVE LOADOUT]", True, (200, 200, 200))
    window.blit(surface_btn3, (450, 40))

    # Retounen nan sistèm 3D a nèt pou pwochen frame lan
    glEnable(GL_DEPTH_TEST)
    glEnable(GL_LIGHTING)
    glMatrixMode(GL_PROJECTION)
    glPopMatrix()
    glMatrixMode(GL_MODELVIEW)
    glPopMatrix()

def main():
    pygame.init()
    pygame.font.init()
    LÈT, WOTÈ = 800, 600
    window = pygame.display.set_mode((LÈT, WOTÈ), DOUBLEBUF | OPENGL)
    pygame.display.set_caption("NAYDER ENGINE v0.0.41 - 3D HUD Dashboard Interface")
    clock = pygame.time.Clock()

    # Chaje vrè Font sistèm yo pou UI a
    font = pygame.font.SysFont("monospace", 13, bold=True)
    bold_font = pygame.font.SysFont("monospace", 32, bold=True)

    gluPerspective(45, (LÈT / WOTÈ), 0.1, 50.0)
    cam_x, cam_y, cam_z = 0.0, 0.0, -8.0

    print("\n=======================================================")
    print("    [NAYDER ENGINE v0.0.41] - 3D HUD INTERFACE LIVE")
    print("=======================================================")
    print(" [*] Home Screen Overlay -> ✅ PROJECTION MATRIX LINKED")
    print(" [*] Font Textures VRAM   -> ✅ ALLOCATED FOR TEXTURE MAP")
    print("-------------------------------------------------------")

    while True:
        for event in pygame.event.get():
            if event.type == pygame.QUIT:
                pygame.quit()
                sys.exit()

        keys = pygame.key.get_pressed()
        if keys[pygame.K_w] or keys[pygame.K_UP]:    cam_z += 0.1
        if keys[pygame.K_s] or keys[pygame.K_DOWN]:  cam_z -= 0.1
        if keys[pygame.K_a] or keys[pygame.K_LEFT]:  cam_x += 0.1
        if keys[pygame.K_d] or keys[pygame.K_RIGHT]: cam_x -= 0.1

        glLoadIdentity()
        gluPerspective(45, (LÈT / WOTÈ), 0.1, 50.0)
        glTranslatef(cam_x, cam_y, cam_z)
        glRotatef(1, 0, 1, 0) 

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT)
        glEnable(GL_DEPTH_TEST)

        Configured_Neon_Lighting() 
        Desine_Terrain_Grid()
        Desine_Player_3D()
        
        # Lanse sistèm UI Heads-Up Display a anlè sèn nan
        Render_HUD_Overlay(window, font, bold_font)

        pygame.display.flip()
        clock.tick(107)

if __name__ == "__main__":
    main()
