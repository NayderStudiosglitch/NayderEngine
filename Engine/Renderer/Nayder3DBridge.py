import pygame
import sys
from pygame.locals import *
from OpenGL.GL import *
from OpenGL.GLU import *

vertices = ((1,-1,-1), (1,1,-1), (-1,1,-1), (-1,-1,-1), (1,-1,1), (1,1,1), (-1,-1,1), (-1,1,1))
edges = ((0,1), (0,3), (0,4), (2,1), (2,3), (2,7), (6,3), (6,4), (6,7), (5,1), (5,4), (5,7))
colors = ((0,210,255), (220,50,50), (0,255,128), (230,180,40), (150,0,255), (255,0,150))
surfaces = ((0,1,2,3), (3,2,7,6), (6,7,5,4), (4,5,1,0), (1,5,7,2), (4,0,3,6))
normals = ((0,0,-1), (-1,0,0), (0,0,1), (1,0,0), (0,1,0), (0,-1,0))

is_firing_laser = False

def Configured_Neon_Lighting():
    glEnable(GL_LIGHTING)
    glEnable(GL_LIGHT0)
    glEnable(GL_COLOR_MATERIAL)
    glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE)
    glLightfv(GL_LIGHT0, GL_POSITION, [0.0, 5.0, 5.0, 1.0])
    glLightfv(GL_LIGHT0, GL_AMBIENT, [0.2, 0.2, 0.3, 1.0])
    glLightfv(GL_LIGHT0, GL_DIFFUSE, [0.0, 0.8, 1.0, 1.0])

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

# =============================================================================
# MODIL 3D WEAPON FIRE SIMULATION (LASER RAYCAST MATRIX)
# =============================================================================
def Desine_Laser_Beam():
    if is_firing_laser:
        glDisable(GL_LIGHTING)
        glLineWidth(5.0) # Gwo liy reyon lazè ki dou
        glColor3fv((255, 0, 50)) # Hot Neon Wouj
        glBegin(GL_LINES)
        glVertex3f(0.0, 0.0, 0.0)    # Soti nan mitan jwè a
        glVertex3f(0.0, 0.0, 15.0)   # Tire dwat devan an 3D pa 15 mèt!
        glEnd()
        glLineWidth(1.0)
        glEnable(GL_LIGHTING)

def Desine_Terrain_Grid():
    glDisable(GL_LIGHTING)
    glColor3fv((0, 150, 200))
    glBegin(GL_LINES)
    for i in range(-20, 21, 2):
        glVertex3f(i, -1, -20); glVertex3f(i, -1, 20)
        glVertex3f(-20, -1, i); glVertex3f(20, -1, i)
    glEnd()
    glEnable(GL_LIGHTING)

def render_procedural_hud():
    glMatrixMode(GL_PROJECTION); glPushMatrix(); glLoadIdentity(); gluOrtho2D(0, 800, 0, 600)
    glMatrixMode(GL_MODELVIEW); glPushMatrix(); glLoadIdentity()
    glDisable(GL_LIGHTING); glDisable(GL_DEPTH_TEST)

    # Header Gwòch (Tit)
    glColor3fv((220, 50, 50))
    glBegin(GL_QUADS); glVertex2f(30, 530); glVertex2f(280, 530); glVertex2f(280, 570); glVertex2f(30, 570); glEnd()

    # Header Dwat (Profil)
    glColor3fv((230, 180, 40))
    glBegin(GL_QUADS); glVertex2f(500, 540); glVertex2f(770, 540); glVertex2f(770, 565); glVertex2f(500, 565); glEnd()

    # Layout Bouton yo anba a
    glColor3fv((0, 210, 255)); glBegin(GL_LINE_LOOP); glVertex2f(40, 30); glVertex2f(220, 30); glVertex2f(220, 70); glVertex2f(40, 70); glEnd()
    glColor3fv((0, 255, 128)); glBegin(GL_LINE_LOOP); glVertex2f(250, 30); glVertex2f(430, 30); glVertex2f(430, 70); glVertex2f(250, 70); glEnd()

    glEnable(GL_DEPTH_TEST); glEnable(GL_LIGHTING)
    glMatrixMode(GL_PROJECTION); glPopMatrix(); glMatrixMode(GL_MODELVIEW); glPopMatrix()

def main():
    global is_firing_laser
    pygame.init()
    LÈT, WOTÈ = 800, 600
    pygame.display.set_mode((LÈT, WOTÈ), DOUBLEBUF | OPENGL)
    pygame.display.set_caption("NAYDER ENGINE v0.0.44 - 3D Raycast Laser Strike")
    clock = pygame.time.Clock()

    gluPerspective(45, (LÈT / WOTÈ), 0.1, 50.0)
    cam_x, cam_y, cam_z = 0.0, 0.0, -8.0

    print("\n=======================================================")
    print("    [NAYDER ENGINE v0.0.44] - 3D WEAPON LASER PIPELINE")
    print("=======================================================")
    print(" [*] Raycast Weapon Core -> ✅ ONLINE")
    print(" [*] Spacebar Mapping    -> ✅ LINKED TO GPU TRIGGERS")
    print(" -> PEZE BUTTON SPACEBAR POU TI REYON LAZÈ LOU AN!")
    print("=======================================================")

    while True:
        for event in pygame.event.get():
            if event.type == pygame.QUIT: pygame.quit(); sys.exit()

        keys = pygame.key.get_pressed()
        if keys[pygame.K_w] or keys[pygame.K_UP]:    cam_z += 0.1
        if keys[pygame.K_s] or keys[pygame.K_DOWN]:  cam_z -= 0.1
        if keys[pygame.K_a] or keys[pygame.K_LEFT]:  cam_x += 0.1
        if keys[pygame.K_d] or keys[pygame.K_RIGHT]: cam_x -= 0.1

        # Tcheke si jwè a ap peze Spacebar pou tire
        if keys[pygame.K_SPACE]: is_firing_laser = True
        else:                    is_firing_laser = False

        glLoadIdentity()
        gluPerspective(45, (LÈT / WOTÈ), 0.1, 50.0)
        glTranslatef(cam_x, cam_y, cam_z)
        glRotatef(1, 0, 1, 0)

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT)
        glEnable(GL_DEPTH_TEST)

        NayderRenderPipeline = Configured_Neon_Lighting()
        Desine_Terrain_Grid()
        Desine_Player_3D()
        Desine_Laser_Beam() # Kalkile epi desine reyon lazè a si Spacebar enfonse
        render_procedural_hud()

        pygame.display.flip()
        clock.tick(107)

if __name__ == "__main__":
    main()
