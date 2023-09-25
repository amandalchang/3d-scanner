'''
f = open("myfile.txt", "w") # mode x is to create new file
file_path = 'myfile.txt'
#input = 
data = "hi"

with open(file_path, mode='w') as file:
    file.write(data)
'''
import csv #imports the csv module
import os
file_path = 'myTest.csv'

if not os.path.isfile(file_path):
    # File does not exist, create it
    with open(file_path, mode='w') as file:
        file.write("This will create the file.")
else:
    # File already exists, handle accordingly
    print("The file already exists.")


data = '1,2'

# for a new data point???
#def split():
#    data.split(",")
new = list(map(lambda x: x.split(","), data)) #write the new values to the vars

'''
f = open("myTest.csv", "x") # mode x is to create new file
file_path = 'myTest.csv'

'''
with open(file_path, mode='w', newline='') as file: # mode w is write mode
    csv_writer = csv.writer(file)
    
    #Write header row
    header = ['r', 'tilt', 'Pan']
    csv_writer.writerow(header)

    csv_writer.writerow(new)

