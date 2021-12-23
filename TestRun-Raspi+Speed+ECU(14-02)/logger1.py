import serial, csv


ser = serial.Serial('/dev/ttyACM1', 9600)
reading_list = []

while 1:
    if(ser.in_waiting >0):
        line = ser.readline()
        try:
            string = str(line)
        except:
            string = ""
            pass

        



        with open('output1.csv', 'a') as outputFile:
            writer = csv.writer(outputFile)
            writer.writerow(string)



