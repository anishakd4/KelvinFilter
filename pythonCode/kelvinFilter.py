import cv2
import numpy as np
import sys

#read input image
image = cv2.imread("../assets/anish.jpg")

#check if image exists
if image is None:
    print("can not find image")
    sys.exit()

#create a copy of input image to work on
output = image.copy()

#split the channels
blueChannel, greenChannel, redChannel = cv2.split(output)

#Interpolation values
redValuesOriginal = np.array([0, 60, 110, 150, 235, 255])
redValues =         np.array([0, 102, 185, 220, 245, 245 ])
greenValuesOriginal = np.array([0, 68, 105, 190, 255])
greenValues =         np.array([0, 68, 120, 220, 255 ])
blueValuesOriginal = np.array([0, 88, 145, 185, 255])
blueValues =         np.array([0, 12, 140, 212, 255])

#create lookup table
allValues = np.arange(0, 256)
#Creating the lookuptable for blue channel
blueLookuptable = np.interp(allValues, blueValuesOriginal, blueValues)
#Creating the lookuptable for green channel
greenLookuptable = np.interp(allValues, greenValuesOriginal, greenValues)
#Creating the lookuptable for red channel
redLookuptable = np.interp(allValues, redValuesOriginal, redValues)

#Apply the mapping for blue channel
blueChannel = cv2.LUT(blueChannel, blueLookuptable)
#Apply the mapping for green channel
greenChannel = cv2.LUT(greenChannel, greenLookuptable)
#Apply the mapping for red channel
redChannel = cv2.LUT(redChannel, redLookuptable)

#merging back the channels
output = cv2.merge([blueChannel, greenChannel, redChannel])

#convert to uint8
output = np.uint8(output)

#create windows to display images
cv2.namedWindow("image", cv2.WINDOW_AUTOSIZE)
cv2.namedWindow("Kelvin", cv2.WINDOW_AUTOSIZE)

#display images
cv2.imshow("image", image)
cv2.imshow("Kelvin", output)

#press esc to exit the program
cv2.waitKey(0)

#destroy all windows
cv2.destroyAllWindows()