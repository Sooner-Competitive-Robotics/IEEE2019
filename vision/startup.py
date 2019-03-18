import vision
import startup
from gpiozero import Button
from time import sleep
from picamera import PiCamera
import RPi.GPIO as GPIO

camera = PiCamera()
camera.resolution = (1000, 1000)
camera.rotation = 180


start_button = Button(start_button_pin)
