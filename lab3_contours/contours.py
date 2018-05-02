import cv2
import math
import numpy as np
from matplotlib import pyplot as plt
################################################################################
imgFile = 'img.jpg'
img = cv2.imread(imgFile)
# color value range
cRange = 256
rows, cols, channels = img.shape
################################################################################
# convert color space from bgr to gray
imgGray = cv2.cvtColor(img, cv2.COLOR_BGR2GRAY)
cv2.imshow('imgGray', imgGray)

element = cv2.getStructuringElement(cv2.MORPH_CROSS, (20, 20))
imgerode = cv2.erode(imgGray, element)
cv2.imshow('imgerode', imgerode)

element = cv2.getStructuringElement(cv2.MORPH_CROSS, (10, 10))
imgdilate = cv2.dilate(imgerode, element)
cv2.imshow('imgdilate', imgdilate)

image, contours, hierarchy = cv2.findContours(
    imgdilate, cv2.RETR_TREE, cv2.CHAIN_APPROX_SIMPLE)  # 检索模式为树形cv2.RETR_TREE，
# 轮廓存储模式为简单模式cv2.CHAIN_APPROX_SIMPLE，如果设置为 cv2.CHAIN_APPROX_NONE，所有的边界点都会被存储。

imgContour = cv2.drawContours(
    img, contours, -1, (0, 255, 0), 3)  # 此时是将轮廓绘制到了原始图像上
# 第三个参数是轮廓的索引（在绘制独立轮廓是很有用，当设置为 -1 时绘制所有轮廓）。接下来的参数是轮廓的颜色和厚度等
cv2.imshow('imgContour', imgContour)
################################################################################
num = 0
for i in range(rows):
    for j in range(cols):
        if imgdilate[i, j] >= 190:
            num = num + 1
print("The area of black is", num)
print("The percentage of black area is", num / (rows * cols))
plt.show()
cv2.waitKey(0)
