import cv2
import imutils

# https://www.pyimagesearch.com/2016/02/01/opencv-center-of-contour/

# Returns -1 if object is to the left
#			0 if object is in the center
#			1 if object is to the right

	
def center(imagename):
	image = cv2.imread(imagename)
	gray = cv2.cvtColor(image, cv2.COLOR_BGR2GRAY)
	blurred = cv2.GaussianBlur(gray, (5, 5), 0)
	thresh = cv2.threshold(blurred, 200, 255, cv2.THRESH_BINARY)[1]
	
	cnts = cv2.findContours(thresh.copy(), cv2.RETR_EXTERNAL, cv2.CHAIN_APPROX_SIMPLE)
	cnts = imutils.grab_contours(cnts)
	
	for c in cnts:
		M = cv2.moments(c)
		cX = int(M["m10"] / M["m00"])
		cY = int(M["m01"] / M["m00"])
		
		#cv2.drawContours(image, [c], -1, (0, 255, 0), 2)
		#cv2.circle(image, (cX, cY), 7, (0, 0, 255), -1)
		#cv2.putText(image, "center", (cX - 20, cY - 20),
		#cv2.FONT_HERSHEY_SIMPLEX, 0.5, (0, 0, 255), 2)
		
	
	# image dim
	width, height = image.shape[:2]
	
	
	# Get the x coord difference
	diff = cX - width/2
	
	#####################################################
	#    Use this value to change radius tolerance      #
	#####################################################
	CENTER_RANGE = 50
	
	if diff > CENTER_RANGE:
		return 1
	elif diff < -CENTER_RANGE:
		return -1
	else:
		return 0