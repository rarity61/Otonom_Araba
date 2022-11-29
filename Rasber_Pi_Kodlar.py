import cv2
import RPi.GPIO as GPIO
import time

faceCascade = cv2.CascadeClassifier('Cascades/haarcascade_frontalface_default.xml')
cap = cv2.VideoCapture(0)
cap.set(3, 640)  # set Width
cap.set(4, 480)  # set Height
kordinatX = 0
kordinatY = 0
while True:

    GPIO.setmode(GPIO.BOARD)
    GPIO.setup(40, GPIO.OUT)
    GPIO.setup(36, GPIO.OUT)
    GPIO.setup(38, GPIO.OUT)
    GPIO.setup(37, GPIO.OUT)
    ret, img = cap.read()
    img = cv2.flip(img, 1)
    gray = cv2.cvtColor(img, cv2.COLOR_BGR2GRAY)
    faces = faceCascade.detectMultiScale(
        gray,
        scaleFactor=1.2,
        minNeighbors=5,
        minSize=(20, 20)
    )
    for (x, y, w, h) in faces:
        cv2.rectangle(img, (x, y), (x + w, y + h), (255, 0, 0), 2)
        roi_gray = gray[y:y + h, x:x + w]
        roi_color = img[y:y + h, x:x + w]
        kordinatX = x
        kordinatY = h

        GPIO.output(40, GPIO.LOW)
        GPIO.output(38, GPIO.LOW)
        GPIO.output(37, GPIO.LOW)
        GPIO.output(36, GPIO.LOW)

        if (kordinatY > 100):
            GPIO.output(40, GPIO.HIGH)
            print("geri")
            GPIO.output(38, GPIO.LOW)
            GPIO.output(37, GPIO.LOW)
            GPIO.output(36, GPIO.LOW)

        elif (kordinatX < 140 and kordinatY < 120):
            GPIO.output(38, GPIO.HIGH)
            print("sol ileri")
            GPIO.output(40, GPIO.LOW)
            GPIO.output(37, GPIO.LOW)
            GPIO.output(36, GPIO.LOW)

        elif (kordinatX > 350 and kordinatY < 120):
            GPIO.output(37, GPIO.HIGH)
            print("sağ ileri")
            GPIO.output(38, GPIO.LOW)
            GPIO.output(40, GPIO.LOW)
            GPIO.output(36, GPIO.LOW)

        elif (kordinatY < 80):
            GPIO.output(36, GPIO.HIGH)
            print("ileri")
            GPIO.output(38, GPIO.LOW)
            GPIO.output(37, GPIO.LOW)
            GPIO.output(40, GPIO.LOW)

    cv2.imshow('video', img)
    k = cv2.waitKey(30) & 0xff
    if k == 27:  # press 'ESC' to quit

        GPIO.output(40, GPIO.LOW)
        GPIO.output(38, GPIO.LOW)
        GPIO.output(37, GPIO.LOW)
        GPIO.output(36, GPIO.LOW)

        break
cap.release()
cv2.destroyAllWindows()


