from tkinter import *

#creating root window
root = Tk()
root.title("To-Do-List - Santino - Version 1.2")

#List box
mylistbox = Listbox(width = 50, height = 45)
mylistbox.grid(row=0,column = 0, columnspan=5)

# Text entry
entrybox_task = Entry(root, width=32)
entrybox_date = Entry(root, width=15)

# Funktions
def add():
    result = entrybox_task.get()
    fileappender(result)
    load()
    entrybox_task.delete(0, END)

def clear():
    entrybox_task.delete(0, END)
    entrybox_date.delete(0, END)

def safetofile(x):
	x #still to do!

def filereader():
	f = open("todolist.txt", "r")
	return f

def fileappender(var):
	if var > "":
		f = open("todolist.txt", "a")
		f.write("\n")
		f.write(var)
	else:
		NONE

def load():
	mylistbox.delete(0, END)
	#creating array and then adding the todos to the array
	todo_array = []
	f = filereader()
	todo_array = f.read().split("\n")

	for item in todo_array:
		mylistbox.insert(END, item)
	return todo_array

# Button
button_add = Button(root, text="ADD", padx=40, pady=10, command=add)
button_del = Button(root, text="DELETE", padx=40, pady=10, state=DISABLED)
button_save = Button(root, text="SAVE", padx=40, pady=10)
button_load = Button(root, text="LOAD", padx=40, pady=10, command=load)
button_submit = Button(root, text="SUBMIT", padx=7, command=add)
button_clear = Button(root, text="CLEAR", padx=7, command=clear)

# Put the Buttons on the screen
button_add.grid(row=2, column=0)
button_del.grid(row=2, column=1)
button_save.grid(row=2, column=2)
button_load.grid(row=2, column=3, columnspan=2)
button_submit.grid(row=1, column=3)
button_clear.grid(row=1, column=4)

# Put the entrybox on the screen
entrybox_task.grid(row=1, column=0, columnspan=2)
entrybox_date.grid(row=1, column=2, columnspan=1)

# Output_field grid
#output_field.grid(row=0, column=0, columnspan=5)

#start the main events loop
root.mainloop()