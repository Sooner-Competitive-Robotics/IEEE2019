import cv2
import numpy as np

# Returns true if cube is found. Otherwise false

def main():
	findShape()


def findShape(name):
	# Read image
	img = cv2.imread(name)
	
	# RGB to Gray scale conversion
	img_gray = cv2.cvtColor(img,cv2.COLOR_RGB2GRAY)
	
	# Noise removal with iterative bilateral filter(removes noise while preserving edges)
	noise_removal = cv2.bilateralFilter(img_gray,9,75,75)
	
	# Thresholding the image
	ret,thresh_image = cv2.threshold(noise_removal,200,255,cv2.THRESH_BINARY)
	
	# Applying Canny Edge detection
	canny_image = cv2.Canny(thresh_image,250,255)
	canny_image = cv2.convertScaleAbs(canny_image)
	
	# dilation to strengthen the edges
	kernel = np.ones((3,3), np.uint8)
	# Creating the kernel for dilation
	dilated_image = cv2.dilate(canny_image,kernel,iterations=1)
	contours, h = cv2.findContours(dilated_image, 1, 2)
	contours = sorted(contours, key = cv2.contourArea, reverse = True)[:1]
	pt = (180, 3 * img.shape[0] // 4)
	
	for cnt in contours:
		approx = cv2.approxPolyDP(cnt,0.01*cv2.arcLength(cnt,True),True)
	
		if len(approx) > 0 and len(approx) <= 6:
			isCube = True
			cv2.drawContours(img,[cnt],-1,(255,0,0),3)
			
		else:
			isCube = False
	
	corners = cv2.goodFeaturesToTrack(thresh_image,6,0.06,25)
	corners = np.float32(corners)
	for item in corners:
		x,y = item[0]
		cv2.circle(img,(x,y),10,255,-1)
	
	return isCube