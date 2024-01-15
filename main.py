# import serial  # Commented out as serial is not being used
import pygame
import time
import serial

# Adjust the port as needed (for example, if your Arduino is on COM3)
serArduino = serial.Serial('COM1', 9600)
time.sleep(2)  # Wait for Arduino to initialize


# Function to send movement commands to Arduino
def send_command(command):
    serArduino.write(command.encode())
    time.sleep(0.1)


try:
    pygame.init()
    pygame.joystick.init()

    joystick_count = pygame.joystick.get_count()
    if joystick_count == 0:
        print("No joystick detected.")
        exit()

    joystick = pygame.joystick.Joystick(0)
    joystick.init()

    last_command_time = time.time()

    while True:
        for event in pygame.event.get():
            if event.type == pygame.JOYAXISMOTION:
                x_left, y_left = joystick.get_axis(0), joystick.get_axis(1)
                x_right, y_right = joystick.get_axis(2), joystick.get_axis(3)
                if time.time() - last_command_time >= 0.2:
                    # Handle commands for the left stick
                    if x_left < -0.9:
                        print('Z')  # LEWO JOYSTICK LEFT
                        send_command('Z')
                    elif x_left > 0.9:
                        print('X')  # PRAWO JOYSTICK LEFT
                        send_command('X')
                    if y_left > 0.9:
                        print('C')  # DOL JOYSTICK LEFT
                        send_command('C')
                    elif y_left < -0.9:
                        print('V')  # GORA JOYSTICK LEFT
                        send_command('V')

                    # Handle commands for the right stick
                    if x_right < -0.9:
                        print('Q')  # LEWO JOYSTICK RIGHT
                        send_command('Q')
                    elif x_right > 0.9:
                        print('W')  # PRAWO JOYSTICK RIGHT
                        send_command('W')
                    if y_right > 0.9:
                        print('R')  # DOL JOYSTICK RIGHT
                        send_command('R')
                    elif y_right < -0.9:
                        print('T')  # GORA JOYSTICK RIGHT
                        send_command('T')
                    last_command_time = time.time()  # Update the last command time

            elif event.type == pygame.JOYBUTTONDOWN:
                if joystick.get_button(2):  # 'X' button on Xbox One controller
                    send_command('G')  # Open gripper
                    print('G')
                elif joystick.get_button(1):  # 'B' button on Xbox One controller
                    print('H')
                    send_command('H')  # Close gripper
                elif joystick.get_button(3):  # 'A' button on Xbox One controller
                    print('J')
                    send_command('J')
                elif joystick.get_button(0):  # 'Y' button on Xbox One controller
                    print('K')
                    send_command('K')
            elif joystick.get_button(4):  # LB (Left Bumper)
                print('P')
                send_command('P')
            elif joystick.get_button(5):  # RB (Right Bumper)
                print('O')
                send_command('O')
            elif event.type == pygame.JOYBUTTONUP:
                # Additional logic for when a button is released, if needed
                pass

            elif event.type == pygame.QUIT:
                pygame.quit()
                exit()

        time.sleep(0.1)

finally:
    serArduino.close()
    pygame.quit()