import pygame
import sys
from pygame.locals import *
from OpenGL.GL import *
from OpenGL.GLU import *

# =============================================================================
# NWAYO DONE 3D (GEOMETRY SHADER VECTORS)
# =============================================================================
vertices = ((1,-1,-1), (1,1,-1), (-1,1,-1), (-1,-1,-1), (1,-1,1), (1,1,1), (-1,-1,1), (-1,1,1))
edges = ((0,1), (0,3), (0,4), (2,1), (2,3), (2,7), (6,3), (6,4), (6,7), (5,1), (5,4), (5,7))
colors = ((0,210,255), (220,50,50), (0,255,128), (230,180,40), (150,0,255), (255,0,150))
surfaces = ((0,1,2,3), (3,2,7,6), (6,7,5,4), (4,5,1,0), (1,5,7,2), (4,0,3,6))
normals = ((0,0,-1), (-1,0,0), (0,0,1), (1,0,0), (0,1,0), (0,-1,0))

class NayderRenderPipeline:
    @staticmethod
    def initialize_hardware_lighting():
        glEnable(GL_LIGHTING)
        glEnable(GL_LIGHT0)
        glEnable(GL_COLOR_MATERIAL)
        glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE)
        glLightfv(GL_LIGHT0, GL_POSITION, [0.0, 5.0, 5.0, 1.0])
        glLightfv(GL_LIGHT0, GL_AMBIENT, [0.2, 0.2, 0.3, 1.0])
        glLightfv(GL_LIGHT0, GL_DIFFUSE, [0.0, 0.8, 1.0, 1.0])

    @staticmethod
    def draw_player_mesh():
        glBegin(GL_QUADS)
        for i, surface in enumerate(surfaces):
            glNormal3fv(normals[i % len(normals)])
            glColor3fv(colors[i % len(colors)])
            for vertex in surface: glVertex3fv(vertices[vertex])
        glEnd()
        
        # Desine liy fil nwa yo (Wireframe Outline)
        glDisable(GL_LIGHTING)
        glBegin(GL_LINES)
        glColor3fv((10,10,15))
        for edge in edges:
            for vertex in edge: glVertex3fv(vertices[vertex])
        glEnd()
        glEnable(GL_LIGHTING)

    @staticmethod
    def draw_world_grid():
        glDisable(GL_LIGHTING)
        glColor3fv((0, 150, 200)) # Neon Blue
        glBegin(GL_LINES)
        for i in range(-20, 21, 2):
            glVertex3f(i, -1, -20); glVertex3f(i, -1, 20)
            glVertex3f(-20, -1, i); glVertex3f(20, -1, i)
        glEnd()
        glEnable(GL_LIGHTING)

    # =============================================================================
    # MULTI-BOX HUD GENERATOR MATRIX (KÒD PWOFESYONÈL SAN OKENN LIBRERI MANKE)
    # =============================================================================
    @staticmethod
    def render_procedural_hud():
        # Transfòme pwojeksyon an nan fòma Ortho 2D
        glMatrixMode(GL_PROJECTION); glPushMatrix(); glLoadIdentity(); gluOrtho2D(0, 800, 0, 600)
        glMatrixMode(GL_MODELVIEW); glPushMatrix(); glLoadIdentity()
        glDisable(GL_LIGHTING); glDisable(GL_DEPTH_TEST)

        # 🟥 1. HEADER GWÒCH (Tit: NEON FALL 17 Layout Frame)
        glColor3fv((220, 50, 50)) # Neon Wouj Solid
        glBegin(GL_QUADS)
        glVertex2f(30, 530); glVertex2f(280, 530); glVertex2f(280, 570); glVertex2f(30, 570)
        glEnd()
        
        # Liy fann taktik anba tit la (Sub-Bar UI Edge)
        glColor3fv((150, 155, 165))
        glBegin(GL_LINES)
        glVertex2f(30, 520); glVertex2f(350, 520)
        glEnd()

        # 🟨 2. HEADER DWAT (Profil: NAYDER_01 Level 25 Wallet Frame)
        glColor3fv((230, 180, 40)) # Koulè Lò Solid
        glBegin(GL_QUADS)
        glVertex2f(500, 540); glVertex2f(770, 540); glVertex2f(770, 565); glVertex2f(500, 565)
        glEnd()
        
        # Ti liy blennde anba kont jwè a
        glColor3fv((200, 200, 200))
        glBegin(GL_LINES)
        glVertex2f(500, 530); glVertex2f(770, 530)
        glEnd()

        # 🟦 3. BOUTON INTERAKTIF ANBA (Build Weapon & Test Weapon UI Grid)
        # Bwat Bouton 1: BUILD WEAPON
        glColor3fv((0, 210, 255)) # Cyan Matrix
        glBegin(GL_LINE_LOOP)
        glVertex2f(40, 30); glVertex2f(220, 30); glVertex2f(220, 70); glVertex2f(40, 70)
        glEnd()

        # Bwat Bouton 2: TEST WEAPON
        glColor3fv((0, 255, 128)) # Neon Vèt Matrix
        glBegin(GL_LINE_LOOP)
        glVertex2f(250, 30); glVertex2f(430, 30); glVertex2f(430, 70); glVertex2f(250, 70)
        glEnd()

        # Bwat Bouton 3: SAVE LOADOUT
        glColor3fv((120, 125, 135)) # Grey Steel
        glBegin(GL_LINE_LOOP)
        glVertex2f(460, 30); glVertex2f(640, 30); glVertex2f(640, 70); glVertex2f(460, 70)
        glEnd()

        # Retounen nan sistèm grafik 3D a
        glEnable(GL_DEPTH_TEST); glEnable(GL_LIGHTING)
        glMatrixMode(GL_PROJECTION); glPopMatrix()
        glMatrixMode(GL_MODELVIEW); glPopMatrix()

def main():
    pygame.init()
    LÈT, WOTÈ = 800, 600
    pygame.display.set_mode((LÈT, WOTÈ), DOUBLEBUF | OPENGL)
    pygame.display.set_caption("NAYDER ENGINE v0.0.43 - Pure Hardware UI Layout Pipeline")
    clock = pygame.time.Clock()

    gluPerspective(45, (LÈT / WOTÈ), 0.1, 50.0)
    cam_x, cam_y, cam_z = 0.0, 0.0, -8.0

    while True:
        for event in pygame.event.get():
            if event.type == pygame.QUIT: pygame.quit(); sys.exit()

        # Koute pyebwa kòmand klavye yo
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

        NayderRenderPipeline.initialize_hardware_lighting()
        NayderRenderPipeline.draw_world_grid()
        NayderRenderPipeline.draw_player_mesh()
        
        # Lanse sistèm desen UI Vektoryèl la anlè sèn nan
        NayderRenderPipeline.render_procedural_hud()

        pygame.display.flip()
        clock.tick(107)

if __name__ == "__main__":
    main()
