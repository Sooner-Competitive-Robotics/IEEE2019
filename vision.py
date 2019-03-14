import pytesseract
import cv2
import random
import LetterRecognition
import ShapeDetection
import Centerpoint

#This class contains static methods for analyzing pictures for object recognition.
class vision:

	def getLetter(image):
		return findImage(image)

	def isCube(image):
		return findShape(image)

	def getCenter(image):
		return center(image)

	def 
