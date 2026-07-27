import pygame
import sys
from pygame.locals import *
from OpenGL.GL import *
from OpenGL.GLU import *

# Done Jewometri 3D pou Jwè a ak Platfòm Evakiyasyon an (Escape Harbor Matrix)
vertices = ((1,-1,-1), (1,1,-1), (-1,1,-1), (-1,-1,-1), (1,-1,1), (1,1,1), (-1,-1,1), (-1,1,1))
edges = ((0,1), (0,3), (0,4), (2,1), (2,3), (2,7), (6,3), (6,4), (6,7), (5,1), (5,4), (5,7))
surfaces = ((0,1,2,3), (3,2,7,6), (6,7,5,4), (4,5,1,0), (1,5,7,2), (4,0,3,6))

is_firing_laser = False
escape_vehicle_z = -15.0 # Kòmanse byen lwen nan forè a
mission_success = False

def Configured_Neon_Lighting():
    glEnable(GL_LIGHTING)
    glEnable(GL_LIGHT0)
    glEnable(GL_COLOR_MATERIAL)
    glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE)
    glLightfv(GL_LIGHT0, GL_POSITION, [0.0, 10.0, 5.0, 1.0])
    glLightfv(GL_LIGHT0, GL_DIFFUSE, [0.0, 0.8, 1.0, 1.0])

def Desine_Escape_Vehicle(z_pos):
    # Desine machin 10 jwè yo k ap deplase pou sove kò yo
    glPushMatrix()
    glTranslatef(0.0, 0.0, z_pos)
    glBegin(GL_QUADS)
    for surface in surfaces:
        glColor3fv((220, 50, 50)) # Koulè Neon Wouj pou machin nan
        for vertex in surface: glVertex3fv(vertices[vertex])
    glEnd()
    glPopMatrix()

def Desine_Escape_Harbor_Dock():
    # Desine Gwo Pò Sekirite Evakiyasyon an (Harbor Safe Zone Base)
    glPushMatrix()
    glTranslatef(0.0, -1.0, 5.0) # Plase dwat devan jwè a
    glScalef(3.0, 0.2, 3.0)     # Fè l parèt gwo tankou yon vrè waf bato
    glBegin(GL_QUADS)
    for surface in surfaces:
        glColor3fv((0, 255, 128)) # Koulè Neon Vèt pou Pò Sekirite a!
        for vertex in surface: glVertex3fv(vertices[vertex])
    glEnd()
    glPopMatrix()

def Desine_Laser_Beam(z_pos):
    if is_firing_laser:
        glDisable(GL_LIGHTING)
        glLineWidth(6.0)
        glColor3fv((255, 255, 0)) # Lazè a tounen Koulè Jòn k ap briye nan fènwa a
        glBegin(GL_LINES)
        glVertex3f(0.0, 0.0, z_pos)
        glVertex3f(0.0, 0.0, z_pos + 20.0)
        glEnd()
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

    # 🟥 Header Tit: NEON FALL 17 - ESCAPE LAND PROTOCOL
    glColor3fv((220, 50, 50))
    glBegin(GL_QUADS); glVertex2f(30, 530); glVertex2f(380, 530); glVertex2f(380, 570); glVertex2f(30, 570); glEnd()

    # 🟩 Si machin nan rive nan pò a, afiche panno Viktwa a nèt ale!
    if mission_success:
        glColor3fv((0, 255, 128)) # Panno Viktwa Vèt klere
        glBegin(GL_QUADS); glVertex2f(200, 250); glVertex2f(600, 250); glVertex2f(600, 350); glVertex2f(200, 350); glEnd()

    glEnable(GL_DEPTH_TEST); glEnable(GL_LIGHTING)
    glMatrixMode(GL_PROJECTION); glPopMatrix(); glMatrixMode(GL_MODELVIEW); glPopMatrix()

def main():
    global is_firing_laser, escape_vehicle_z, mission_success
    pygame.init()
    LÈT, WOTÈ = 800, 600
    pygame.display.set_mode((LÈT, WOTÈ), DOUBLEBUF | OPENGL)
    pygame.display.set_caption("NAYDER ENGINE v0.0.51 - Escape Harbor 3D Viewport")
    clock = pygame.time.Clock()

    gluPerspective(45, (LÈT / WOTÈ), 0.1, 50.0)

    print("\n=======================================================")
    print("    [NAYDER ENGINE v0.0.51] - ESCAPE LAND VIEWPORT CORE")
    print("=======================================================")
    print(" [*] Harbor Zone Target  -> ✅ STABLE IN 3D SPACE")
    print(" [*] Escape Vehicle Loop -> ✅ MOVING ON ACCELERATOR CLUSTER")
    print(" -> KENBE 'W' POU MACHIN LAN AVANSE NAN PÒ A, PEZE 'SPACEBAR' POU TIRE!")
    print("=======================================================")

    while True:
        for event in pygame.event.get():
            if event.type == pygame.QUIT: pygame.quit(); sys.exit()

        keys = pygame.key.get_pressed()
        
        # Lojik deplasman machin nan sou aks Z pou l kouri antre nan pò a
        if keys[pygame.K_w] or keys[pygame.K_UP]:
            if escape_vehicle_z < 3.0:
                escape_vehicle_z += 0.15 # Machin nan ap kouri byen rapid sou 107 FPS!
            else:
                if not mission_success:
                    mission_success = True
                    print("\n🎉🎉🎉 [MISSION ACCOMPLISHED] 🎉🎉🎉")
                    print(" -> Skayad 10 jwè a rive nan pò sekirite a pafè!")
                    print(" -> Bato evakiyasyon an demare! Ou chape anba Zombie Zone lan!")

        if keys[pygame.K_s] or keys[pygame.K_DOWN]:  escape_vehicle_z -= 0.15
        if keys[pygame.K_SPACE]: is_firing_laser = True
        else:                    is_firing_laser = False

        glLoadIdentity()
        gluPerspective(45, (LÈT / WOTÈ), 0.1, 50.0)
        
        # Kamera a swiv machin nan dousman nan background nan
        gluLookAt(0.0, 4.0, escape_vehicle_z - 10.0, 0.0, 0.0, escape_vehicle_z, 0.0, 1.0, 0.0)

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT)
        glEnable(GL_DEPTH_TEST)

        Configured_Neon_Lighting()
        Desine_Terrain_Grid()
        Desine_Escape_Harbor_Dock() # Desine vrè pò sekirite a nan sèn nan
        Desine_Escape_Vehicle(escape_vehicle_z) # Desine machin k ap kouri a
        Desine_Laser_Beam(escape_vehicle_z)
        render_procedural_hud()

        pygame.display.flip()
        clock.tick(107)

if __name__ == "__main__":
    main()
