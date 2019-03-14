import pytesseract
import cv2
import random

# using version 4
#pytesseract.pytesseract.tesseract_cmd = r"C:\Program Files (x86)\Tesseract-OCR\tesseract.exe"


def findImage(name):
	# list of letters we are looking for
	letters = ['A', 'B', 'C', 'D', 'E', 'F']
	
	# read image
	image = cv2.imread(name)
	
	# convert image to grayscale
	gray_image = cv2.cvtColor(image, cv2.COLOR_BGR2GRAY)
	gray_image = crop(gray_image)
	gray_image = cv2.medianBlur(gray_image, 5)
	gray_image = cv2.bilateralFilter(gray_image,9,75,75)
	gray_image = resize(gray_image)
	ret,thresh = cv2.threshold(gray_image, 100, 255, cv2.THRESH_BINARY) #optimal threshold 103
	
	# read the picture using Tesseract
	text = pytesseract.image_to_string(thresh, config='--psm 10')

    # rotates image until it recognizes it as a letter. Max rotation of 4
	counter = 0
	while text not in letters and counter < 4:
		thresh = rotate(thresh)
		text = pytesseract.image_to_string(thresh, config='--psm 10')
        
		counter = counter + 1
	
	if text not in letters:
		num = random.randint(1, 6)
		
		switcher = {
			1: "A",
			2: "B",
			3: "C",
			4: "D",
			5: "E",
			6: "F"
		}
		text = switcher.get(num)
		
	return text

# rotates image 90 degrees
def rotate(image):
    # get image height and width
    (h, w) = image.shape[:2]
    # get the center of the image
    center = (w/2, h/2)

    scale = 1.0

    m = cv2.getRotationMatrix2D(center, 90, scale)
    rotated90 = cv2.warpAffine(image, m, (w, h))

    return rotated90

# crops outer edges
def crop(image):
    # image dimensions
    (x,y) = image.shape[:2]
    numCrop = 50

    # crop image
    cropped = image[numCrop:x-numCrop, numCrop:y-numCrop]

    return cropped

# Resize images to make them smaller
def resize(image):
    resizeFactor = 0.4

    (width, height) = image.shape[:2]
    new_size = int(width*resizeFactor), int(height*resizeFactor)
    image = cv2.resize(image, new_size)
    return image